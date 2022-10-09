#include "script_interpreter.hpp"
#include "tools.hpp"

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

	int startingIndex = 0;

	if(valueString[0] == '-')
	{
		startingIndex = 1;
	}

	unsigned dotCount = 0;

	for(int index = startingIndex; index < static_cast<int>(valueString.size()); index++)
	{
		if(!isdigit(valueString[index]) && valueString[index] != '.')
		{
			return false;
		}

		if(valueString[index] == '.')
		{
			dotCount++;
		}
	}

	return (valueString.size() >= 3) && (isdigit(valueString[startingIndex]) && isdigit(valueString.back())) && (dotCount == 1);
}

const bool ScriptInterpreter::_isIntegerValue(const string & valueString) const
{
	return Tools::isInteger(valueString);
}

const bool ScriptInterpreter::_isBooleanValue(const string & valueString) const
{
	return (valueString == "<true>") || (valueString == "<false>");
}

const int ScriptInterpreter::_extractListIndexFromString(const string & valueString, bool & isAccessingList)
{
	const auto openingBracketIterator = find(valueString.begin(), valueString.end(), '[');
	const auto closingBracketIterator = find(valueString.begin(), valueString.end(), ']');

	if(openingBracketIterator == valueString.end() || closingBracketIterator == valueString.end())
	{
		return -1;
	}

	const auto openingBracketIndex = static_cast<int>(distance(valueString.begin(), openingBracketIterator));
	const auto closingBracketIndex = static_cast<int>(distance(valueString.begin(), closingBracketIterator));

	if((openingBracketIndex == 0) || (closingBracketIndex == 0) || (openingBracketIndex > closingBracketIndex))
	{
		return -1;
	}

	const auto indexString = valueString.substr(static_cast<size_t>(openingBracketIndex + 1), (valueString.size() - static_cast<size_t>(openingBracketIndex + 1) - 1));

	if(_isIntegerValue(indexString))
	{
		isAccessingList = true;

		return stoi(_limitIntegerString(indexString));
	}
	else
	{
		if(!_isLocalVariableExisting(indexString) && !_isGlobalVariableExisting(indexString))
		{
			_throwRuntimeError("invalid syntax or statement");

			return -1;
		}

		const auto variable = (_isLocalVariableExisting(indexString) ? _getLocalVariable(indexString) : _getGlobalVariable(indexString));

		if((variable->getType() == ScriptVariableType::MULTIPLE) || variable->getValue(0)->getType() != ScriptValueType::INTEGER)
		{
			_throwRuntimeError("invalid syntax or statement");

			return -1;
		}

		isAccessingList = true;

		return variable->getValue(0)->getInteger();
	}
}

const bool ScriptInterpreter::_validateKeyInputString(const string & inputString)
{
	if(keyboard_key_types.find(inputString) == keyboard_key_types.end())
	{
		_throwRuntimeError("invalid keyboard key");

		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateMouseInputString(const string & inputString)
{
	if(mouse_button_types.find(inputString) == mouse_button_types.end())
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
		if(valueString.size() >= to_string(INT_MIN).size())
		{
			return to_string(MIN_STRING_INTEGER);
		}
	}
	else
	{
		if(valueString.size() >= to_string(INT_MAX).size())
		{
			return to_string(MAX_STRING_INTEGER);
		}
	}

	return valueString;
}

const string ScriptInterpreter::_limitDecimalString(const string & valueString) const
{
	const auto dotIndex = static_cast<int>(valueString.find('.'));
	const auto intString = valueString.substr(0, dotIndex);

	if(valueString[0] == '-')
	{
		if(intString.size() >= to_string(INT_MIN).size())
		{
			return to_string(MIN_STRING_DECIMAL);
		}
	}
	else
	{
		if(intString.size() >= to_string(INT_MAX).size())
		{
			return to_string(MAX_STRING_DECIMAL);
		}
	}

	return valueString;
}