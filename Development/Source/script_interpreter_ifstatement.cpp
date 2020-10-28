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
			// Determine if element is a variable or a raw value
			if (_isLocalVariableExisting(elementString))
			{
				comparisonValues.push_back(_getLocalVariable(elementString).getValue());
			}
			else if (_isStringValue(elementString))
			{
				comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, elementString));
			}
			else if (_isDecimalValue(elementString))
			{
				comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(elementString)));
			}
			else if (_isIntegerValue(elementString))
			{
				comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(elementString)));
			}
			else if (_isBooleanValue(elementString))
			{
				comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, (elementString == "<true>")));
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

	return false;
}

bool ScriptInterpreter::_validateCondition(ScriptValue& firstValue, string comparisonOperator, ScriptValue& secondValue)
{
	if (firstValue.getType() != secondValue.getType())
	{
		_throwScriptError("compared values not of the same type!");
		return false;
	}

	return true;
}

bool ScriptInterpreter::_checkConditionResult(ScriptValue& firstValue, string comparisonOperator, ScriptValue& secondValue)
{
	if (comparisonOperator == _isKeyword)
	{
		
	}
	else if (comparisonOperator == _notKeyword)
	{

	}
	else if (comparisonOperator == _moreKeyword)
	{

	}
	else if (comparisonOperator == _lessKeyword)
	{

	}
}