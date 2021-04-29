#include "script_interpreter.hpp"

#include <sstream>

bool ScriptInterpreter::_isListValue(const string& valueString)
{
	// Check if value has enough characters
	if (valueString.empty())
	{
		return false;
	}

	// Check if value is surrounded by braces
	if (valueString.front() != '{' || valueString.back() != '}')
	{
		return false;
	}

	return true;
}

bool ScriptInterpreter::_isVec3Value(const string& valueString)
{
	// Check if value has enough characters
	if (valueString.empty())
	{
		return false;
	}

	// Check if value is surrounded by brackets
	if (valueString.front() != '[' || valueString.back() != ']')
	{
		return false;
	}

	// Remove brackets
	auto withoutBrackets = valueString.substr(1, valueString.size() - 2);

	// Extract XYZ
	string xyz[3] = { "", "","" };
	bool isExtracting = false;
	unsigned int index = 0;
	for (auto& c : withoutBrackets)
	{
		if (c == ' ' && isExtracting)
		{
			isExtracting = false;
			index++;
		}

		if (c != ' ')
		{
			xyz[index] += c;
			isExtracting = true;
		}

		if (index == 3)
		{
			return false;
		}
	}

	// Check if value is a valid vec3
	return (_isDecimalValue(xyz[0]) && _isDecimalValue(xyz[1]) && _isDecimalValue(xyz[2]));
}

bool ScriptInterpreter::_isStringValue(const string& valueString)
{
	// Check if value has characters at all
	if (valueString.empty())
	{
		return false;
	}

	return valueString.size() >= 2 && (valueString.front() == '"' && valueString.back() == '"');
}

bool ScriptInterpreter::_isDecimalValue(const string& valueString)
{
	// Check if value has characters at all
	if (valueString.empty())
	{
		return false;
	}

	// Check if value is perhaps negative
	unsigned int startingIndex = 0;
	if (valueString.front() == '-')
	{
		startingIndex = 1;
	}

	// Validate every character
	unsigned dots = 0;
	for (unsigned int i = startingIndex; i < valueString.size(); i++)
	{
		if (!isdigit(valueString[i]) && valueString[i] != '.')
		{
			return false;
		}

		// Count dots in value
		if (valueString[i] == '.')
		{
			dots++;
		}
	}

	// Check if value is a valid decimal
	return (valueString.size() >= 3) && (isdigit(valueString[startingIndex]) && isdigit(valueString.back())) && (dots == 1);
}

bool ScriptInterpreter::_isIntegerValue(const string& valueString)
{
	// Check if value has characters at all
	if (valueString.empty())
	{
		return false;
	}

	// Check if value is perhaps negative
	unsigned int startingIndex = 0;
	if (valueString.front() == '-')
	{
		startingIndex = 1;
	}

	// Check if every character is a digit
	for (unsigned int i = startingIndex; i < valueString.size(); i++)
	{
		if (!isdigit(valueString[i]))
		{
			return false;
		}
	}

	return true;
}

bool ScriptInterpreter::_isBooleanValue(const string& valueString)
{
	return (valueString == "<true>" || valueString == "<false>");
}

Vec3 ScriptInterpreter::_extractVec3FromString(const string& valueString)
{
	// Check if vec3 value
	if (!_isVec3Value(valueString))
	{
		_fe3d.logger_throwError("Tried to extract Vec3 value from non-vec3 valuestring!");
	}

	// Remove brackets
	auto withoutBrackets = valueString.substr(1, valueString.size() - 2);

	// Extract XYZ
	string xyz[3] = { "", "","" };
	bool isExtracting = false;
	unsigned int index = 0;
	for (auto& c : withoutBrackets)
	{
		if (c == ' ' && isExtracting)
		{
			isExtracting = false;
			index++;
		}

		if (c != ' ')
		{
			xyz[index] += c;
			isExtracting = true;
		}
	}

	return Vec3(stof(_limitDecimalString(xyz[0])), stof(_limitDecimalString(xyz[1])), stof(_limitDecimalString(xyz[2])));
}

Ivec3 ScriptInterpreter::_extractVec3PartFromString(const string& valueString)
{
	Ivec3 parts = Ivec3(0);
	auto stringSize = valueString.size();

	if (stringSize > 2 &&
		(valueString.substr(stringSize - 2) == ".x" || valueString.substr(stringSize - 2) == ".r"))
	{
		parts.x = 1;
	}
	else if (stringSize > 2 &&
		(valueString.substr(stringSize - 2) == ".y" || valueString.substr(stringSize - 2) == ".g"))
	{
		parts.y = 1;
	}
	else if (stringSize > 2 &&
		(valueString.substr(stringSize - 2) == ".z" || valueString.substr(stringSize - 2) == ".b"))
	{
		parts.z = 1;
	}

	return parts;
}

int ScriptInterpreter::_extractListIndexFromString(const string& valueString, bool& isAccessingList)
{
	// Check if brackets are in string
	auto openingBracketFound = std::find(valueString.begin(), valueString.end(), '[');
	auto closingBracketFound = std::find(valueString.begin(), valueString.end(), ']');
	if (openingBracketFound == valueString.end() || closingBracketFound == valueString.end())
	{
		return -1;
	}

	// Check if brackets are in the right place
	auto openingBracketIndex = static_cast<unsigned int>(std::distance(valueString.begin(), openingBracketFound));
	auto closingBracketIndex = static_cast<unsigned int>(std::distance(valueString.begin(), closingBracketFound));
	if (openingBracketIndex == 0 || closingBracketIndex != (valueString.size() - 1))
	{
		return -1;
	}

	// Check if index is a number
	string indexString = valueString.substr(openingBracketIndex + 1);
	indexString.pop_back();
	if (_isIntegerValue(indexString))
	{
		isAccessingList = true;
		return stoi(_limitIntegerString(indexString));
	}
	else if (_isLocalVariableExisting(indexString) || _isGlobalVariableExisting(indexString))
	{
		// Retrieve variable
		auto& variable = _isLocalVariableExisting(indexString) ? _getLocalVariable(indexString) : _getGlobalVariable(indexString);

		// Check if variable is an integer
		if (variable.getType() == ScriptVariableType::MULTIPLE || variable.getValue().getType() != ScriptValueType::INTEGER)
		{
			_throwScriptError("list index must be an integer!");
		}
		else
		{
			isAccessingList = true;
			return variable.getValue().getInteger();
		}
	}
	else
	{
		_throwScriptError("invalid list indexing syntax!");
	}

	return -1;
}

bool ScriptInterpreter::_validateKeyInputString(const string& inputString)
{
	if (KEY_INPUT_STRING_MAP.find(inputString) == KEY_INPUT_STRING_MAP.end())
	{
		_throwScriptError("invalid keyboard key!");
		return false;
	}

	return true;
}

bool ScriptInterpreter::_validateMouseInputString(const string& inputString)
{
	if (MOUSE_INPUT_STRING_MAP.find(inputString) == MOUSE_INPUT_STRING_MAP.end())
	{
		_throwScriptError("invalid mouse button!");
		return false;
	}

	return true;
}

string ScriptInterpreter::_limitIntegerString(const string& valueString)
{
	// Check if negative value
	if (valueString.front() == '-')
	{
		// Cannot be less than -999 999 999
		if (valueString.size() >= 11)
		{
			return "-1000000000";
		}
	}
	else // Positive value
	{
		// Cannot be more than 999 999 999
		if (valueString.size() >= 10)
		{
			return "1000000000";
		}
	}

	return valueString;
}

string ScriptInterpreter::_limitDecimalString(const string& valueString)
{
	// Cut everything after the dot
	auto dotIndex = static_cast<unsigned int>(valueString.find('.'));
	string intString = valueString.substr(0, dotIndex);

	// Check if negative value
	if (valueString.front() == '-')
	{
		// Cannot be less than -999 999 999
		if (intString.size() >= 11)
		{
			return "-1000000000.0";
		}
	}
	else // Positive value
	{
		// Cannot be more than 999 999 999
		if (intString.size() >= 10)
		{
			return "1000000000.0";
		}
	}

	return valueString;
}