#include "script_interpreter.hpp"

void ScriptInterpreter::_processVariableArithmetic(const string & scriptLine)
{
	string words[2] = {"", ""};

	int wordIndex = 0;

	for(const auto & character : scriptLine)
	{
		if(character == ' ')
		{
			wordIndex++;

			if(wordIndex == 2)
			{
				break;
			}
		}
		else
		{
			words[wordIndex] += character;
		}
	}

	const auto operatorString = words[0];

	if(operatorString != ADD_KEYWORD &&
	   operatorString != SUBTRACT_KEYWORD &&
	   operatorString != MULTIPLY_KEYWORD &&
	   operatorString != DIVIDE_KEYWORD &&
	   operatorString != MODULO_KEYWORD &&
	   operatorString != NEGATE_KEYWORD)
	{
		_throwRuntimeError("invalid arithmetic operator");

		return;
	}

	auto nameString = words[1];

	if(nameString.empty())
	{
		_throwRuntimeError("variable name missing");

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
		const auto isOpeningBracketFound = find(nameString.begin(), nameString.end(), '[');
		const auto bracketIndex = static_cast<int>(distance(nameString.begin(), isOpeningBracketFound));

		nameString = nameString.substr(0, bracketIndex);
	}

	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwRuntimeError("variable \"" + nameString + "\" does not exist");

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
		_throwRuntimeError(FINAL_KEYWORD + " variables cannot be changed");

		return;
	}

	if(!isAccessingLeftList && (leftVariable->getType() == ScriptVariableType::MULTIPLE))
	{
		_throwRuntimeError("arithmetic not allowed on " + LIST_KEYWORD + " values");

		return;
	}
	else if(leftVariable->getValue(leftValueIndex)->getType() == ScriptValueType::STRING)
	{
		_throwRuntimeError("arithmetic not allowed on " + STRING_KEYWORD + " values");

		return;
	}
	else if(leftVariable->getValue(leftValueIndex)->getType() == ScriptValueType::BOOLEAN)
	{
		_throwRuntimeError("arithmetic not allowed on " + BOOLEAN_KEYWORD + " values");

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

	const auto minLineSize = (words[0].size() + words[1].size() + 3);

	if(scriptLine.size() < minLineSize)
	{
		_throwRuntimeError("value missing");

		return;
	}

	auto valueString = scriptLine.substr(minLineSize - 1);

	if(_isListValue(valueString))
	{
		_throwRuntimeError("arithmetic not allowed on " + LIST_KEYWORD + " values");

		return;
	}
	else if(_isStringValue(valueString))
	{
		_throwRuntimeError("arithmetic not allowed on " + STRING_KEYWORD + " values");

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
		_throwRuntimeError("arithmetic not allowed on " + BOOLEAN_KEYWORD + " values");

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
			const auto isOpeningBracketFound = find(valueString.begin(), valueString.end(), '[');
			const auto bracketIndex = static_cast<int>(distance(valueString.begin(), isOpeningBracketFound));

			valueString = valueString.substr(0, bracketIndex);
		}

		if(!_isLocalVariableExisting(valueString) && !_isGlobalVariableExisting(valueString))
		{
			_throwRuntimeError("variable \"" + valueString + "\" does not exist");

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
			_throwRuntimeError("arithmetic not allowed on " + LIST_KEYWORD + " values");

			return;
		}
		else if(rightVariable->getValue(rightValueIndex)->getType() == ScriptValueType::STRING)
		{
			_throwRuntimeError("arithmetic not allowed on " + STRING_KEYWORD + " values");

			return;
		}
		else if(rightVariable->getValue(rightValueIndex)->getType() == ScriptValueType::BOOLEAN)
		{
			_throwRuntimeError("arithmetic not allowed on " + BOOLEAN_KEYWORD + " values");

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
		_throwRuntimeError("value types not matching");

		return;
	}
}