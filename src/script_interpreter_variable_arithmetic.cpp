#include "script_interpreter.hpp"

void ScriptInterpreter::_processVariableArithmetic(const string & scriptLine)
{
	string parts[2] = {"", ""};

	int partIndex = 0;

	for(const auto & character : scriptLine)
	{
		if(character == ' ')
		{
			partIndex++;

			if(partIndex == 2)
			{
				break;
			}
		}
		else
		{
			parts[partIndex] += character;
		}
	}

	const auto operatorString = parts[0];

	if(operatorString != ADD_KEYWORD &&
	   operatorString != SUBTRACT_KEYWORD &&
	   operatorString != MULTIPLY_KEYWORD &&
	   operatorString != DIVIDE_KEYWORD &&
	   operatorString != MODULO_KEYWORD &&
	   operatorString != NEGATE_KEYWORD)
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	auto nameString = parts[1];

	if(nameString.empty())
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	bool isAccessingLeftList = false;

	const auto leftListIndex = _extractListIndexFromString(nameString, isAccessingLeftList);

	if(_hasThrownError)
	{
		return;
	}

	if(isAccessingLeftList)
	{
		const auto openingBracketIterator = find(nameString.begin(), nameString.end(), '[');
		const auto openingBracketIndex = static_cast<int>(distance(nameString.begin(), openingBracketIterator));

		nameString = nameString.substr(0, openingBracketIndex);
	}

	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	const auto leftVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	int leftValueIndex = 0;

	if(isAccessingLeftList)
	{
		if(!_validateListIndex(leftVariable, leftListIndex))
		{
			return;
		}

		leftValueIndex = leftListIndex;
	}

	if(leftVariable->isFinal())
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	if(!isAccessingLeftList && (leftVariable->getType() == ScriptVariableType::MULTIPLE))
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}
	else if(leftVariable->getValue(leftValueIndex)->getType() == ScriptValueType::STRING)
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}
	else if(leftVariable->getValue(leftValueIndex)->getType() == ScriptValueType::BOOLEAN)
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	if(operatorString == NEGATE_KEYWORD)
	{
		if(leftVariable->getValue(leftValueIndex)->getType() == ScriptValueType::INTEGER)
		{
			auto integer = leftVariable->getValue(leftValueIndex)->getInteger();

			integer *= -1;

			leftVariable->getValue(leftValueIndex)->setInteger(integer);

			return;
		}
		else
		{
			auto decimal = leftVariable->getValue(leftValueIndex)->getDecimal();

			decimal *= -1.0f;

			leftVariable->getValue(leftValueIndex)->setDecimal(decimal);

			return;
		}
	}

	const auto minLineSize = (parts[0].size() + parts[1].size() + 3);

	if(scriptLine.size() < minLineSize)
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	auto valueString = scriptLine.substr(minLineSize - 1);

	if(_isListValue(valueString))
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}
	else if(_isStringValue(valueString))
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}
	else if(_isDecimalValue(valueString))
	{
		const auto value = make_shared<ScriptValue>(ScriptValueType::DECIMAL, stof(_limitIntegerString(valueString)));

		_performArithmeticOperation(leftVariable->getValue(leftValueIndex), operatorString, value);
	}
	else if(_isIntegerValue(valueString))
	{
		const auto value = make_shared<ScriptValue>(ScriptValueType::INTEGER, stoi(_limitIntegerString(valueString)));

		_performArithmeticOperation(leftVariable->getValue(leftValueIndex), operatorString, value);
	}
	else if(_isBooleanValue(valueString))
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}
	else
	{
		bool isAccessingRightList = false;

		const auto rightListIndex = _extractListIndexFromString(valueString, isAccessingRightList);

		if(_hasThrownError)
		{
			return;
		}

		if(isAccessingRightList)
		{
			const auto openingBracketIterator = find(valueString.begin(), valueString.end(), '[');
			const auto openingBracketIndex = static_cast<int>(distance(valueString.begin(), openingBracketIterator));

			valueString = valueString.substr(0, openingBracketIndex);
		}

		if(!_isLocalVariableExisting(valueString) && !_isGlobalVariableExisting(valueString))
		{
			_throwRuntimeError("invalid syntax or statement");

			return;
		}

		const auto rightVariable = (_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) : _getGlobalVariable(valueString));

		int rightValueIndex = 0;

		if(isAccessingRightList)
		{
			if(!_validateListIndex(rightVariable, rightListIndex))
			{
				return;
			}

			rightValueIndex = rightListIndex;
		}

		if(!isAccessingRightList && (rightVariable->getType() == ScriptVariableType::MULTIPLE))
		{
			_throwRuntimeError("invalid syntax or statement");

			return;
		}
		else if(rightVariable->getValue(rightValueIndex)->getType() == ScriptValueType::STRING)
		{
			_throwRuntimeError("invalid syntax or statement");

			return;
		}
		else if(rightVariable->getValue(rightValueIndex)->getType() == ScriptValueType::BOOLEAN)
		{
			_throwRuntimeError("invalid syntax or statement");

			return;
		}

		_performArithmeticOperation(leftVariable->getValue(leftValueIndex), operatorString, rightVariable->getValue(rightValueIndex));
	}
}

void ScriptInterpreter::_performArithmeticOperation(shared_ptr<ScriptValue> leftValue, const string & operatorString, shared_ptr<ScriptValue> rightValue)
{
	if(((leftValue->getType() == ScriptValueType::INTEGER)) && (rightValue->getType() == ScriptValueType::INTEGER))
	{
		int result = leftValue->getInteger();

		if(operatorString == ADD_KEYWORD)
		{
			result += rightValue->getInteger();
		}
		else if(operatorString == SUBTRACT_KEYWORD)
		{
			result -= rightValue->getInteger();
		}
		else if(operatorString == MULTIPLY_KEYWORD)
		{
			result *= rightValue->getInteger();
		}
		else if(operatorString == DIVIDE_KEYWORD)
		{
			if(rightValue->getInteger() != 0)
			{
				result /= rightValue->getInteger();
			}
		}
		else if(operatorString == MODULO_KEYWORD)
		{
			result %= rightValue->getInteger();
		}

		result = ((result < 0) ? max(result, MIN_STRING_INTEGER) : min(result, MAX_STRING_INTEGER));

		leftValue->setInteger(result);
	}
	else if((leftValue->getType() == ScriptValueType::DECIMAL) && (rightValue->getType() == ScriptValueType::DECIMAL))
	{
		float result = leftValue->getDecimal();

		if(operatorString == ADD_KEYWORD)
		{
			result += rightValue->getDecimal();
		}
		else if(operatorString == SUBTRACT_KEYWORD)
		{
			result -= rightValue->getDecimal();
		}
		else if(operatorString == MULTIPLY_KEYWORD)
		{
			result *= rightValue->getDecimal();
		}
		else if(operatorString == DIVIDE_KEYWORD)
		{
			result /= rightValue->getDecimal();
		}
		else if(operatorString == MODULO_KEYWORD)
		{
			result = fmodf(result, rightValue->getDecimal());
		}

		result = ((result < 0) ? max(result, MIN_STRING_DECIMAL) : min(result, MAX_STRING_DECIMAL));

		leftValue->setDecimal(result);
	}
	else
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}
}