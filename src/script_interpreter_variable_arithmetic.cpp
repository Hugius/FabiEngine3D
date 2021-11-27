#include "script_interpreter.hpp"

void ScriptInterpreter::_processVariableArithmetic(const string& scriptLine)
{
	// Extract arithmetic operator & variable name
	string words[2] = {"", ""};
	unsigned int wordIndex = 0;
	for(const auto& c : scriptLine)
	{
		if(c == ' ') // Current word ended
		{
			// Next word
			wordIndex++;

			// Check if words extracted
			if(wordIndex == 2)
			{
				break;
			}
		}
		else // Add to word
		{
			words[wordIndex] += c;
		}
	}

	// Check if invalid arithmetic operator
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

	// Check if variable name is missing
	string nameString = words[1];
	if(nameString.empty())
	{
		_throwScriptError("variable name missing!");
		return;
	}

	// Prepare list access
	bool isAccessingLeftList = false;
	auto leftListIndex = _extractListIndexFromString(nameString, isAccessingLeftList);

	// Check if any error was thrown
	if(_hasThrownError)
	{
		return;
	}

	// Remove list accessing characters
	if(isAccessingLeftList)
	{
		auto isOpeningBracketFound = find(nameString.begin(), nameString.end(), '[');
		auto bracketIndex = static_cast<unsigned int>(distance(nameString.begin(), isOpeningBracketFound));
		nameString = nameString.substr(0, bracketIndex);
	}

	// Check if left variable is not existing
	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("variable \"" + nameString + "\" not existing!");
		return;
	}

	// Retrieve left variable
	auto& leftVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	// Validate list access
	unsigned int leftValueIndex = 0;
	if(isAccessingLeftList)
	{
		// Check if list index is invalid
		if(!_validateListIndex(leftVariable, leftListIndex))
		{
			return;
		}

		// Copy list index
		leftValueIndex = leftListIndex;
	}

	// Check if left variable is constant
	if(leftVariable.isConstant())
	{
		_throwScriptError("CONST variables cannot be changed!");
		return;
	}

	// Validate left variable
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

	// Negation arithmetic
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

	// Check if value is missing
	auto minLineSize = (operatorString.size() + nameString.size() + (isAccessingLeftList ? (to_string(leftListIndex).size() + 2) : 0) + 3);
	if(scriptLine.size() < minLineSize)
	{
		_throwScriptError("value missing!");
		return;
	}

	// Extract value
	string valueString = scriptLine.substr(minLineSize - 1);

	// Determine value type
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
		auto value = ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(_limitIntegerString(valueString)));
		_performArithmeticOperation(leftVariable.getValue(leftValueIndex), operatorString, value);
	}
	else if(_isIntegerValue(valueString))
	{
		auto value = ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(_limitIntegerString(valueString)));
		_performArithmeticOperation(leftVariable.getValue(leftValueIndex), operatorString, value);
	}
	else if(_isBooleanValue(valueString))
	{
		_throwScriptError("arithmetic not allowed on BOOL values!");
		return;
	}
	else
	{
		// Prepare list access
		bool isAccessingRightList = false;
		auto rightListIndex = _extractListIndexFromString(valueString, isAccessingRightList);

		// Check if any error was thrown
		if(_hasThrownError)
		{
			return;
		}

		// Remove list accessing characters
		if(isAccessingRightList)
		{
			auto isOpeningBracketFound = find(valueString.begin(), valueString.end(), '[');
			auto bracketIndex = static_cast<unsigned int>(distance(valueString.begin(), isOpeningBracketFound));
			valueString = valueString.substr(0, bracketIndex);
		}

		// Check if right variable is not existing
		if(!_isLocalVariableExisting(valueString) && !_isGlobalVariableExisting(valueString))
		{
			_throwScriptError("variable \"" + valueString + "\" not existing!");
			return;
		}

		// Retrieve right variable
		const auto& rightVariable = (_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) : _getGlobalVariable(valueString));

		// Validate list access
		unsigned int rightValueIndex = 0;
		if(isAccessingRightList)
		{
			// Check if list index is invalid
			if(!_validateListIndex(rightVariable, rightListIndex))
			{
				return;
			}

			// Copy list index
			rightValueIndex = rightListIndex;
		}

		// Validate right variable
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

		// Perform arithmetic operation
		_performArithmeticOperation(leftVariable.getValue(leftValueIndex), operatorString, rightVariable.getValue(rightValueIndex));
	}
}

void ScriptInterpreter::_performArithmeticOperation(ScriptValue& leftValue, const string& operatorString, ScriptValue& rightValue)
{
	if((leftValue.getType() == ScriptValueType::INTEGER) && rightValue.getType() == ScriptValueType::INTEGER)
	{
		// Retrieve left value
		int result = leftValue.getInteger();

		// Determine arithmetic type
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

		// Limit integer
		result = ((result < 0) ? max(result, -1000000000) : min(result, 1000000000));

		// Set integer
		leftValue.setInteger(result);
	}
	else if((leftValue.getType() == ScriptValueType::DECIMAL) && (rightValue.getType() == ScriptValueType::DECIMAL))
	{
		// Retrieve left value
		float result = leftValue.getDecimal();

		// Determine arithmetic type
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

		// Limit decimal
		result = ((result < 0) ? max(result, -1000000000.0f) : min(result, 1000000000.0f));

		// Set decimal
		leftValue.setDecimal(result);
	}
	else
	{
		_throwScriptError("value types not matching!");
		return;
	}
}