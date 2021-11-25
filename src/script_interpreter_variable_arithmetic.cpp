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

	// Check if left variable is not existing
	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("variable \"" + nameString + "\" not existing!");
		return;
	}

	// Retrieve left variable
	auto& leftVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	// Check if left variable is constant
	if(leftVariable.isConstant())
	{
		_throwScriptError("constant variables cannot be changed!");
		return;
	}

	// Validate left variable
	if(leftVariable.getType() == ScriptVariableType::MULTIPLE)
	{
		_throwScriptError("arithmetic not allowed on LIST values!");
		return;
	}
	else if(leftVariable.getValue().getType() == ScriptValueType::STRING)
	{
		_throwScriptError("arithmetic not allowed on STR values!");
		return;
	}
	else if(leftVariable.getValue().getType() == ScriptValueType::BOOLEAN)
	{
		_throwScriptError("arithmetic not allowed on BOOL values!");
		return;
	}

	if(operatorString == NEGATION_KEYWORD) // Negation arithmetic
	{
		if(leftVariable.getValue().getType() == ScriptValueType::INTEGER)
		{
			auto integer = leftVariable.getValue().getInteger();
			integer *= -1;
			leftVariable.getValue().setInteger(integer);
		}
		else
		{
			auto decimal = leftVariable.getValue().getDecimal();
			decimal *= -1.0f;
			leftVariable.getValue().setDecimal(decimal);
		}
	}
	else // Other arithmetic
	{
		// Check if value is present
		if(scriptLine.size() < (nameString.size() + operatorString.size() + 3))
		{
			_throwScriptError("value missing!");
			return;
		}

		// Extract value
		string valueString = scriptLine.substr(operatorString.size() + nameString.size() + 2);

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
			_performArithmeticOperation(leftVariable.getValue(), operatorString, value);
		}
		else if(_isIntegerValue(valueString))
		{
			auto value = ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(_limitIntegerString(valueString)));
			_performArithmeticOperation(leftVariable.getValue(), operatorString, value);
		}
		else if(_isBooleanValue(valueString))
		{
			_throwScriptError("arithmetic not allowed on BOOL values!");
			return;
		}
		else
		{
			// Check if right variable is not existing
			if(!_isLocalVariableExisting(valueString) && !_isGlobalVariableExisting(valueString))
			{
				_throwScriptError("variable \"" + valueString + "\" not existing!");
				return;
			}

			// Retrieve right variable
			const auto& rightVariable = (_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) : _getGlobalVariable(valueString));

			// Validate right variable
			if(rightVariable.getType() == ScriptVariableType::MULTIPLE)
			{
				_throwScriptError("arithmetic not allowed on LIST values!");
				return;
			}
			else if(rightVariable.getValue().getType() == ScriptValueType::STRING)
			{
				_throwScriptError("arithmetic not allowed on STR values!");
				return;
			}
			else if(rightVariable.getValue().getType() == ScriptValueType::BOOLEAN)
			{
				_throwScriptError("arithmetic not allowed on BOOL values!");
				return;
			}

			// Perform arithmetic operation
			_performArithmeticOperation(leftVariable.getValue(), operatorString, rightVariable.getValue());
		}
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