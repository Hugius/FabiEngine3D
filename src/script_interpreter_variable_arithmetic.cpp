#include "script_interpreter.hpp"

void ScriptInterpreter::_processVariableArithmetic(const string& scriptLine)
{
	string words[2] = {"", ""};
	unsigned int wordIndex = 0;
	for(const auto& c : scriptLine)
	{
		if(c == ' ')
		{
			wordIndex++;

			if(wordIndex == 2)
			{
				break;
			}
		}
		else
		{
			words[wordIndex] += c;
		}
	}

	string operatorString = words[0];
	if(operatorString != ADDITION_KEYWORD &&
	   operatorString != SUBTRACTION_KEYWORD &&
	   operatorString != MULTIPLICATION_KEYWORD &&
	   operatorString != DIVISION_KEYWORD &&
	   operatorString != NEGATION_KEYWORD)
	{
		_throwScriptError("invalid arithmetic operator!");
		return;
	}

	string nameString = words[1];
	if(nameString.empty())
	{
		_throwScriptError("variable name missing!");
		return;
	}

	bool isAccessingLeftList = false;
	auto leftListIndex = _extractListIndexFromString(nameString, isAccessingLeftList);

	if(_hasThrownError)
	{
		return;
	}

	if(isAccessingLeftList)
	{
		auto isOpeningBracketFound = find(nameString.begin(), nameString.end(), '[');
		auto bracketIndex = static_cast<unsigned int>(distance(nameString.begin(), isOpeningBracketFound));
		nameString = nameString.substr(0, bracketIndex);
	}

	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("variable \"" + nameString + "\" not existing!");
		return;
	}

	auto& leftVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	unsigned int leftValueIndex = 0;
	if(isAccessingLeftList)
	{
		if(!_validateListIndex(leftVariable, leftListIndex))
		{
			return;
		}

		leftValueIndex = leftListIndex;
	}

	if(leftVariable.isConstant())
	{
		_throwScriptError("CONST variables cannot be changed!");
		return;
	}

	if(!isAccessingLeftList && (leftVariable.getType() == ScriptVariableType::MULTIPLE))
	{
		_throwScriptError("arithmetic not allowed on LIST values!");
		return;
	}
	else if(leftVariable.getValue(leftValueIndex).getType() == ScriptValueType::STRING)
	{
		_throwScriptError("arithmetic not allowed on STR values!");
		return;
	}
	else if(leftVariable.getValue(leftValueIndex).getType() == ScriptValueType::BOOLEAN)
	{
		_throwScriptError("arithmetic not allowed on BOOL values!");
		return;
	}

	if(operatorString == NEGATION_KEYWORD)
	{
		if(leftVariable.getValue(leftValueIndex).getType() == ScriptValueType::INTEGER)
		{
			auto integer = leftVariable.getValue(leftValueIndex).getInteger();
			integer *= -1;
			leftVariable.getValue(leftValueIndex).setInteger(integer);
			return;
		}
		else
		{
			auto decimal = leftVariable.getValue(leftValueIndex).getDecimal();
			decimal *= -1.0f;
			leftVariable.getValue(leftValueIndex).setDecimal(decimal);
			return;
		}
	}

	auto minLineSize = (operatorString.size() + nameString.size() + (isAccessingLeftList ? (to_string(leftListIndex).size() + 2) : 0) + 3);
	if(scriptLine.size() < minLineSize)
	{
		_throwScriptError("value missing!");
		return;
	}

	string valueString = scriptLine.substr(minLineSize - 1);

	if(_isListValue(valueString))
	{
		_throwScriptError("arithmetic not allowed on LIST values!");
	}
	else if(_isStringValue(valueString))
	{
		_throwScriptError("arithmetic not allowed on STR values!");
		return;
	}
	else if(_isDecimalValue(valueString))
	{
		auto value = ScriptValue(ScriptValueType::DECIMAL, stof(_limitIntegerString(valueString)));
		_performArithmeticOperation(leftVariable.getValue(leftValueIndex), operatorString, value);
	}
	else if(_isIntegerValue(valueString))
	{
		auto value = ScriptValue(ScriptValueType::INTEGER, stoi(_limitIntegerString(valueString)));
		_performArithmeticOperation(leftVariable.getValue(leftValueIndex), operatorString, value);
	}
	else if(_isBooleanValue(valueString))
	{
		_throwScriptError("arithmetic not allowed on BOOL values!");
		return;
	}
	else
	{
		bool isAccessingRightList = false;
		auto rightListIndex = _extractListIndexFromString(valueString, isAccessingRightList);

		if(_hasThrownError)
		{
			return;
		}

		if(isAccessingRightList)
		{
			auto isOpeningBracketFound = find(valueString.begin(), valueString.end(), '[');
			auto bracketIndex = static_cast<unsigned int>(distance(valueString.begin(), isOpeningBracketFound));
			valueString = valueString.substr(0, bracketIndex);
		}

		if(!_isLocalVariableExisting(valueString) && !_isGlobalVariableExisting(valueString))
		{
			_throwScriptError("variable \"" + valueString + "\" not existing!");
			return;
		}

		const auto& rightVariable = (_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) : _getGlobalVariable(valueString));

		unsigned int rightValueIndex = 0;
		if(isAccessingRightList)
		{
			if(!_validateListIndex(rightVariable, rightListIndex))
			{
				return;
			}

			rightValueIndex = rightListIndex;
		}

		if(!isAccessingRightList && (rightVariable.getType() == ScriptVariableType::MULTIPLE))
		{
			_throwScriptError("arithmetic not allowed on LIST values!");
			return;
		}
		else if(rightVariable.getValue(rightValueIndex).getType() == ScriptValueType::STRING)
		{
			_throwScriptError("arithmetic not allowed on STR values!");
			return;
		}
		else if(rightVariable.getValue(rightValueIndex).getType() == ScriptValueType::BOOLEAN)
		{
			_throwScriptError("arithmetic not allowed on BOOL values!");
			return;
		}

		_performArithmeticOperation(leftVariable.getValue(leftValueIndex), operatorString, rightVariable.getValue(rightValueIndex));
	}
}

void ScriptInterpreter::_performArithmeticOperation(ScriptValue& leftValue, const string& operatorString, ScriptValue& rightValue)
{
	if((leftValue.getType() == ScriptValueType::INTEGER) && rightValue.getType() == ScriptValueType::INTEGER)
	{
		int result = leftValue.getInteger();

		if(operatorString == ADDITION_KEYWORD)
		{
			result += rightValue.getInteger();
		}
		else if(operatorString == SUBTRACTION_KEYWORD)
		{
			result -= rightValue.getInteger();
		}
		else if(operatorString == MULTIPLICATION_KEYWORD)
		{
			result *= rightValue.getInteger();
		}
		else if(operatorString == DIVISION_KEYWORD)
		{
			result /= rightValue.getInteger();
		}

		result = ((result < 0) ? max(result, -1000000000) : min(result, 1000000000));

		leftValue.setInteger(result);
	}
	else if((leftValue.getType() == ScriptValueType::DECIMAL) && (rightValue.getType() == ScriptValueType::DECIMAL))
	{
		float result = leftValue.getDecimal();

		if(operatorString == ADDITION_KEYWORD)
		{
			result += rightValue.getDecimal();
		}
		else if(operatorString == SUBTRACTION_KEYWORD)
		{
			result -= rightValue.getDecimal();
		}
		else if(operatorString == MULTIPLICATION_KEYWORD)
		{
			result *= rightValue.getDecimal();
		}
		else if(operatorString == DIVISION_KEYWORD)
		{
			result /= rightValue.getDecimal();
		}

		result = ((result < 0) ? max(result, -1000000000.0f) : min(result, 1000000000.0f));

		leftValue.setDecimal(result);
	}
	else
	{
		_throwScriptError("value types not matching!");
		return;
	}
}