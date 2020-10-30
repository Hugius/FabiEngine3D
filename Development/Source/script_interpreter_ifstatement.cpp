#include "script_interpreter.hpp"

bool ScriptInterpreter::_checkIfStatement(string conditionString)
{
	// Check if condition is not empty
	if (conditionString.empty())
	{
		_throwScriptError("no condition found!");
		return false;
	}

	// Extract all invidual elements of the if statement
	std::istringstream iss(conditionString);
	vector<string> elements;
	string element = "";
	while (iss >> element)
	{
		elements.push_back(element);
	}

	// Values needed for final boolean return
	vector<bool> conditions;
	vector<string> logicalOperators;

	// Temporary values
	bool mustBeValue = true;
	bool mustBeComparisonOperator = false;
	bool mustBeLogicalOperator = false;
	vector<ScriptValue> comparisonValues;
	string comparisonOperator = "";

	// Process every element
	for (auto& elementString : elements)
	{
		if (mustBeValue)
		{
			if (_isLocalVariableExisting(elementString)) // LOCAL VARIABLE
			{
				comparisonValues.push_back(_getLocalVariable(elementString).getValue());
			}
			else if (_isStringValue(elementString)) // STRING
			{
				elementString.erase(elementString.begin());
				elementString.pop_back();
				comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, elementString));
			}
			else if (_isDecimalValue(elementString)) // DECIMAL
			{
				comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(elementString)));
			}
			else if (_isIntegerValue(elementString)) // INTEGER
			{
				comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(elementString)));
			}
			else if (_isBooleanValue(elementString)) // BOOLEAN
			{
				comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, (elementString == "<true>")));
			}
			else if (elementString.substr(0, 5) == "fe3d:") // FE3D FUNCTION
			{
				auto value = _processEngineFunctionCall(elementString).back();

				// Check if FE3D function returned void
				if (value.getType() == ScriptValueType::EMPTY)
				{
					_throwScriptError("FE3D function return type cannot be empty!");
					return false;
				}
				else
				{
					comparisonValues.push_back(value);
				}
			}
			else
			{
				_throwScriptError("invalid comparison value or variable!");
				return false;
			}

			// Check if current condition is fully composed
			if (comparisonValues.size() == 2)
			{
				// Check if condition is possible at all
				if (_validateCondition(comparisonValues.front(), comparisonOperator, comparisonValues.back()))
				{
					conditions.push_back(_checkConditionResult(comparisonValues.front(), comparisonOperator, comparisonValues.back()));
					mustBeValue = false;
					mustBeLogicalOperator = true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				mustBeValue = false;
				mustBeComparisonOperator = true;
			}
		}
		else if(mustBeComparisonOperator)
		{
			if (elementString == _notKeyword || elementString == _isKeyword || elementString == _moreKeyword || elementString == _lessKeyword)
			{
				comparisonOperator = elementString;
				mustBeComparisonOperator = false;
				mustBeValue = true;
			}
			else
			{
				_throwScriptError("invalid comparison operator!");
				return false;
			}
		}
		else if (mustBeLogicalOperator)
		{

		}
	}

	bool finalResult = true;

	return conditions.back();
}

bool ScriptInterpreter::_validateCondition(ScriptValue& firstValue, string comparisonOperator, ScriptValue& secondValue)
{
	// Check if comparison values are of the same type
	if (firstValue.getType() != secondValue.getType())
	{
		_throwScriptError("compared values not of the same type!");
		return false;
	}
	
	// Check if not trying to compare string values with the wrong operator
	if ((comparisonOperator == _moreKeyword || comparisonOperator == _lessKeyword) && firstValue.getType() == ScriptValueType::STRING)
	{
		_throwScriptError("invalid comparison operator for string values!");
		return false;
	}

	// Check if not trying to compare string values with the wrong operator
	if ((comparisonOperator == _moreKeyword || comparisonOperator == _lessKeyword) && firstValue.getType() == ScriptValueType::BOOLEAN)
	{
		_throwScriptError("invalid comparison operator for boolean values!");
		return false;
	}

	// Condition is valid
	return true;
}

bool ScriptInterpreter::_checkConditionResult(ScriptValue& firstValue, string comparisonOperator, ScriptValue& secondValue)
{
	if (comparisonOperator == _isKeyword)
	{
		if (firstValue.getType() == ScriptValueType::STRING)
		{
			return (firstValue.getString() == secondValue.getString());
		}
		else if (firstValue.getType() == ScriptValueType::DECIMAL)
		{
			return (firstValue.getDecimal() == secondValue.getDecimal());
		}
		else if (firstValue.getType() == ScriptValueType::INTEGER)
		{
			return (firstValue.getInteger() == secondValue.getInteger());
		}
		else if (firstValue.getType() == ScriptValueType::BOOLEAN)
		{
			return (firstValue.getBoolean() == secondValue.getBoolean());
		}
	}
	else if (comparisonOperator == _notKeyword)
	{
		if (firstValue.getType() == ScriptValueType::STRING)
		{
			return (firstValue.getString() != secondValue.getString());
		}
		else if (firstValue.getType() == ScriptValueType::DECIMAL)
		{
			return (firstValue.getDecimal() != secondValue.getDecimal());
		}
		else if (firstValue.getType() == ScriptValueType::INTEGER)
		{
			return (firstValue.getInteger() != secondValue.getInteger());
		}
		else if (firstValue.getType() == ScriptValueType::BOOLEAN)
		{
			return (firstValue.getBoolean() != secondValue.getBoolean());
		}
	}
	else if (comparisonOperator == _moreKeyword)
	{
		if (firstValue.getType() == ScriptValueType::DECIMAL)
		{
			return (firstValue.getDecimal() > secondValue.getDecimal());
		}
		else if (firstValue.getType() == ScriptValueType::INTEGER)
		{
			return (firstValue.getInteger() > secondValue.getInteger());
		}
	}
	else if (comparisonOperator == _lessKeyword)
	{
		if (firstValue.getType() == ScriptValueType::DECIMAL)
		{
			return (firstValue.getDecimal() < secondValue.getDecimal());
		}
		else if (firstValue.getType() == ScriptValueType::INTEGER)
		{
			return (firstValue.getInteger() < secondValue.getInteger());
		}
	}
	else
	{
		_fe3d.logger_throwError("This error should not be thrown...(really, it fucking shouldn't)");
	}

	return false;
}