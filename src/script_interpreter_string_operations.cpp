#include "script_interpreter.hpp"

#include <sstream>

const bool ScriptInterpreter::_isListValue(const string & valueString) const
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

const bool ScriptInterpreter::_isStringValue(const string & valueString) const
{
	if(valueString.empty())
	{
		return false;
	}

	return (valueString.size() >= 2) && (valueString[0] == '"') && (valueString.back() == '"');
}

const bool ScriptInterpreter::_isDecimalValue(const string & valueString) const
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
	for(unsigned int index = startingIndex; index < static_cast<int>(valueString.size()); index++)
	{
		if(!isdigit(valueString[index]) && valueString[index] != '.')
		{
			return false;
		}

		if(valueString[index] == '.')
		{
			dots++;
		}
	}

	return (valueString.size() >= 3) && (isdigit(valueString[startingIndex]) && isdigit(valueString.back())) && (dots == 1);
}

const bool ScriptInterpreter::_isIntegerValue(const string & valueString) const
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

	for(unsigned int index = startingIndex; index < static_cast<int>(valueString.size()); index++)
	{
		if(!isdigit(valueString[index]))
		{
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_isBooleanValue(const string & valueString) const
{
	return (valueString == "<true>") || (valueString == "<false>");
}

const int ScriptInterpreter::_extractListIndexFromString(const string & valueString, bool & isAccessingList)
{
	auto isOpeningBracketFound = find(valueString.begin(), valueString.end(), '[');
	auto closingBracketFound = find(valueString.begin(), valueString.end(), ']');
	if(isOpeningBracketFound == valueString.end() || closingBracketFound == valueString.end())
	{
		return -1;
	}

	auto openingBracketIndex = static_cast<int>(distance(valueString.begin(), isOpeningBracketFound));
	auto closingBracketIndex = static_cast<int>(distance(valueString.begin(), isOpeningBracketFound));
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
			_throwRuntimeError("variable \"" + indexString + "\" does not exist");
			return -1;
		}

		const auto variable = (_isLocalVariableExisting(indexString) ? _getLocalVariable(indexString) : _getGlobalVariable(indexString));

		if((variable->getType() == ScriptVariableType::MULTIPLE) || variable->getValue()->getType() != ScriptValueType::INTEGER)
		{
			_throwRuntimeError("LIST index must be of type INT");
			return -1;
		}

		isAccessingList = true;
		return variable->getValue()->getInteger();
	}
}

const bool ScriptInterpreter::_validateKeyInputString(const string & inputString)
{
	if(keyboard_key_typeS.find(inputString) == keyboard_key_typeS.end())
	{
		_throwRuntimeError("invalid keyboard key");

		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateMouseInputString(const string & inputString)
{
	if(mouse_button_typeS.find(inputString) == mouse_button_typeS.end())
	{
		_throwRuntimeError("invalid mouse button");

		return false;
	}

	return true;
}

const string ScriptInterpreter::_limitIntegerString(const string & valueString) const
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

const string ScriptInterpreter::_limitDecimalString(const string & valueString) const
{
	auto dotIndex = static_cast<int>(valueString.find('.'));
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