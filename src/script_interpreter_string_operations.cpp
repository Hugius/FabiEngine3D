#include "script_interpreter.hpp"
#include "logger.hpp"

#include <sstream>

const bool ScriptInterpreter::_isListValue(const string& valueString) const
{
	if(valueString.empty())
	{
		return false;
	}

	if(valueString[0] != '{' || valueString.back() != '}')
	{
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_isStringValue(const string& valueString) const
{
	if(valueString.empty())
	{
		return false;
	}

	return (valueString.size() >= 2) && (valueString[0] == '"') && (valueString.back() == '"');
}

const bool ScriptInterpreter::_isDecimalValue(const string& valueString) const
{
	if(valueString.empty())
	{
		return false;
	}

	unsigned int startingIndex = 0;
	if(valueString[0] == '-')
	{
		startingIndex = 1;
	}

	unsigned dots = 0;
	for(size_t i = startingIndex; i < valueString.size(); i++)
	{
		if(!isdigit(valueString[i]) && valueString[i] != '.')
		{
			return false;
		}

		if(valueString[i] == '.')
		{
			dots++;
		}
	}

	return (valueString.size() >= 3) && (isdigit(valueString[startingIndex]) && isdigit(valueString.back())) && (dots == 1);
}

const bool ScriptInterpreter::_isIntegerValue(const string& valueString) const
{
	if(valueString.empty())
	{
		return false;
	}

	unsigned int startingIndex = 0;
	if(valueString[0] == '-')
	{
		startingIndex = 1;
	}

	for(size_t i = startingIndex; i < valueString.size(); i++)
	{
		if(!isdigit(valueString[i]))
		{
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_isBooleanValue(const string& valueString) const
{
	return (valueString == "<true>") || (valueString == "<false>");
}

const int ScriptInterpreter::_extractListIndexFromString(const string& valueString, bool& isAccessingList)
{
	auto isOpeningBracketFound = find(valueString.begin(), valueString.end(), '[');
	auto closingBracketFound = find(valueString.begin(), valueString.end(), ']');
	if(isOpeningBracketFound == valueString.end() || closingBracketFound == valueString.end())
	{
		return -1;
	}

	auto openingBracketIndex = static_cast<unsigned int>(distance(valueString.begin(), isOpeningBracketFound));
	auto closingBracketIndex = static_cast<unsigned int>(distance(valueString.begin(), isOpeningBracketFound));
	if((openingBracketIndex == 0) || (closingBracketIndex == 0) || (openingBracketIndex > closingBracketIndex))
	{
		return -1;
	}

	string indexString = valueString.substr(static_cast<size_t>(openingBracketIndex + 1));
	indexString.pop_back();
	if(_isIntegerValue(indexString))
	{
		isAccessingList = true;
		return stoi(_limitIntegerString(indexString));
	}
	else
	{
		if(!_isLocalVariableExisting(indexString) && !_isGlobalVariableExisting(indexString))
		{
			_throwScriptError("variable \"" + indexString + "\" not existing!");
			return -1;
		}

		auto& variable = (_isLocalVariableExisting(indexString) ? _getLocalVariable(indexString) : _getGlobalVariable(indexString));

		if((variable.getType() == ScriptVariableType::MULTIPLE) || variable.getValue().getType() != ScriptValueType::INTEGER)
		{
			_throwScriptError("LIST index must be of type INT!");
			return -1;
		}

		isAccessingList = true;
		return variable.getValue().getInteger();
	}
}

const bool ScriptInterpreter::_validateKeyInputString(const string& inputString)
{
	if(KEY_INPUT_STRING_MAP.find(inputString) == KEY_INPUT_STRING_MAP.end())
	{
		_throwScriptError("invalid keyboard key!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateMouseInputString(const string& inputString)
{
	if(MOUSE_INPUT_STRING_MAP.find(inputString) == MOUSE_INPUT_STRING_MAP.end())
	{
		_throwScriptError("invalid mouse button!");
		return false;
	}

	return true;
}

const string ScriptInterpreter::_limitIntegerString(const string& valueString) const
{
	if(valueString[0] == '-')
	{
		if(valueString.size() >= 11)
		{
			return "-1000000000";
		}
	}
	else
	{
		if(valueString.size() >= 10)
		{
			return "1000000000";
		}
	}

	return valueString;
}

const string ScriptInterpreter::_limitDecimalString(const string& valueString) const
{
	auto dotIndex = static_cast<unsigned int>(valueString.find('.'));
	string intString = valueString.substr(0, dotIndex);

	if(valueString[0] == '-')
	{
		if(intString.size() >= 11)
		{
			return "-1000000000.0";
		}
	}
	else
	{
		if(intString.size() >= 10)
		{
			return "1000000000.0";
		}
	}

	return valueString;
}