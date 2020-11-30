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
	std::istringstream iss(valueString.substr(1, valueString.size() - 2));

	// Extract XYZ
	string x, y, z;
	iss >> x >> y >> z;

	// Check if value is a valid vec3
	return (_isDecimalValue(x) && _isDecimalValue(y) && _isDecimalValue(z));
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
	std::istringstream iss(valueString.substr(1, valueString.size() - 2));

	// Extract XYZ
	string x, y, z;
	iss >> x >> y >> z;

	return Vec3(stof(x), stof(y), stof(z));
}

Ivec3 ScriptInterpreter::_extractVec3PartFromString(const string& valueString)
{
	Ivec3 parts = Ivec3(0);

	if (valueString.size() > 2 &&
		(valueString.substr(valueString.size() - 2) == ".x" || valueString.substr(valueString.size() - 2) == ".r"))
	{
		parts.x = 1;
	}
	else if (valueString.size() > 2 &&
		(valueString.substr(valueString.size() - 2) == ".y" || valueString.substr(valueString.size() - 2) == ".g"))
	{
		parts.y = 1;
	}
	else if (valueString.size() > 2 &&
		(valueString.substr(valueString.size() - 2) == ".z" || valueString.substr(valueString.size() - 2) == ".b"))
	{
		parts.z = 1;
	}

	return parts;
}

int ScriptInterpreter::_extractListIndexFromString(const string& valueString, bool& isAccessingList)
{
	auto openingBracketFound = std::find(valueString.begin(), valueString.end(), '[');
	auto closingBracketFound = std::find(valueString.begin(), valueString.end(), ']');

	// Check if brackets are in string
	if (openingBracketFound != valueString.end() && closingBracketFound != valueString.end())
	{
		unsigned int bracketIndex = std::distance(valueString.begin(), openingBracketFound);
		string indexString = valueString.substr(bracketIndex + 1);
		indexString.pop_back();

		// Check if index is a number
		if (_isIntegerValue(indexString))
		{
			isAccessingList = true;
			return stoi(indexString);
		}
		else
		{
			_throwScriptError("invalid list indexing syntax!");
		}
	}

	return -1;
}

unsigned int ScriptInterpreter::_countFrontSpaces(const string& scriptLineText)
{
	int countedSpaces = 0;

	// For every character
	for (unsigned int i = 0; i < scriptLineText.size(); i++)
	{
		// Check if current character is a space
		if (scriptLineText[i] == ' ')
		{
			// Check if any text comes after the last space character
			if (i == (scriptLineText.size() - 1))
			{
				_throwScriptError("useless indentation!");
				return 0;
			}
			else
			{
				countedSpaces++;
			}
		}
		else
		{
			break;
		}
	}

	return countedSpaces;
}

bool ScriptInterpreter::_validateScopeChange(unsigned int countedSpaces, const string& scriptLineText)
{
	unsigned int currentLineScopeDepth = countedSpaces / _spacesPerIndent;

	// Check if there is any code right after a scope change
	if (_scopeHasChanged && ((currentLineScopeDepth != _scopeDepthStack.back()) || scriptLineText.substr(0, 3) == "///"))
	{
		_throwScriptError("no indented code after scope change!");
	}
	else if (currentLineScopeDepth < _scopeDepthStack.back()) // End of current scope
	{
		_scopeDepthStack.back() = currentLineScopeDepth;
	}
	else if (currentLineScopeDepth > _scopeDepthStack.back()) // Outside of current scope
	{
		if (_passedScopeChanger) // Skip current line
		{
			return false;
		}
		else // Useless indented statement
		{
			_throwScriptError("invalid indentation!");
		}
	}

	_scopeHasChanged = false;
	return true;
}

void ScriptInterpreter::_throwScriptError(const string& message)
{
	_fe3d.logger_throwWarning("ERROR @ script \"" + _currentScriptStackIDs.back() + "\" @ line " + to_string(_currentLineStackIndices.back() + 1) + ": " + message);
	_hasThrownError = true;
}

void ScriptInterpreter::_checkEngineWarnings()
{
	auto messageStack = _fe3d.logger_getMessageStack();

	// Check if any new messages were logged
	if (messageStack.size() > _lastLoggerMessageCount)
	{
		// Loop over all new messages
		for (unsigned int i = _lastLoggerMessageCount - 1; i < messageStack.size(); i++)
		{
			// Check if logged message is a warning
			if (messageStack[i].substr(0, string("[Warn]").size()) == "[Warn]")
			{
				_hasThrownError = true;
			}
		}
	}
}

bool ScriptInterpreter::hasThrownError()
{
	return _hasThrownError;
}