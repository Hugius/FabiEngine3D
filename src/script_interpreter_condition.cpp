#include "script_interpreter.hpp"
#include "logger.hpp"

const bool ScriptInterpreter::_checkConditionString(const string& conditionString)
{
	// Check if condition is not empty
	if(conditionString.empty())
	{
		_throwScriptError("no condition found!");
		return false;
	}

	// Temporary values
	vector<string> elements;
	string elementBuild = "";
	unsigned int index = 0;
	bool buildingString = false;

	// Extract all invidual elements of the if statement
	for(const auto& c : conditionString)
	{
		if(c == ' ' && elementBuild.empty() && !buildingString) // Check for useless whitespace
		{
			index++;
			continue;
		}
		else if(index == conditionString.size() - 1) // Check if last character
		{
			elementBuild += c;
			elements.push_back(elementBuild);
		}
		else if(c == ' ' && !buildingString) // Check for whitespace
		{
			elements.push_back(elementBuild);
			elementBuild.clear();
		}
		else // Keep building element string
		{
			if(c == '"' && !buildingString)
			{
				buildingString = true;
			}
			else if(c == '"' && buildingString)
			{
				buildingString = false;
			}

			// Add character
			elementBuild += c;
		}

		index++;
	}

	// Check if there at least 3 elements
	if(elements.size() < 3)
	{
		_throwScriptError("not enough elements in condition!");
		return false;
	}

	// Values needed for final boolean return
	vector<bool> conditions;
	vector<string> logicOperators;

	// Temporary values
	bool mustBeValue = true;
	bool mustBeComparisonOperator = false;
	bool mustBeLogicOperator = false;
	vector<ScriptValue> comparisonValues;
	string comparisonOperator = "";

	// Process every element
	for(auto& elementString : elements)
	{
		if(mustBeValue)
		{
			if(_isStringValue(elementString)) // STRING
			{
				elementString.erase(elementString.begin());
				elementString.pop_back();
				comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, elementString));
			}
			else if(_isDecimalValue(elementString)) // DECIMAL
			{
				comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(_limitDecimalString(elementString))));
			}
			else if(_isIntegerValue(elementString)) // INTEGER
			{
				comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(_limitIntegerString(elementString))));
			}
			else if(_isBooleanValue(elementString)) // BOOLEAN
			{
				comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, (elementString == "<true>")));
			}
			else // VARIABLE
			{
				// Check if accessing individual value from list variable
				bool isAccessingList = false;
				auto listIndex = _extractListIndexFromString(elementString, isAccessingList);

				// Check if any error was thrown
				if(_hasThrownError)
				{
					return false;
				}

				// Remove list accessing characters
				if(isAccessingList)
				{
					auto openingBracketFound = find(elementString.begin(), elementString.end(), '[');
					auto bracketIndex = static_cast<unsigned int>(distance(elementString.begin(), openingBracketFound));
					elementString = elementString.substr(0, bracketIndex);
				}

				// Check if using a variable as value
				if(_isLocalVariableExisting(elementString) || _isGlobalVariableExisting(elementString))
				{
					// Retrieve variable value
					auto variable = (_isLocalVariableExisting(elementString) ? _getLocalVariable(elementString) : _getGlobalVariable(elementString));

					if(isAccessingList) // List[index]
					{
						// Check if list index is valid
						if(_validateListIndex(variable, listIndex))
						{
							comparisonValues.push_back(variable.getValue(listIndex));
						}
						else // Error
						{
							return false;
						}
					}
					else if(variable.getType() == ScriptVariableType::SINGLE) // Normal variable
					{
						comparisonValues.push_back(variable.getValue());
					}
					else // Cannot be list variable
					{
						_throwScriptError("LIST variable cannot be used in a condition!");
						return false;
					}
				}
				else
				{
					_throwScriptError("invalid comparison value!");
					return false;
				}
			}

			// Check if current condition is fully composed
			if(comparisonValues.size() == 2)
			{
				// Check if condition is possible at all
				if(_validateCondition(comparisonValues.front(), comparisonOperator, comparisonValues.back()))
				{
					conditions.push_back(_compareValues(comparisonValues.front(), comparisonOperator, comparisonValues.back()));
					comparisonValues.clear();
					mustBeValue = false;
					mustBeLogicOperator = true;
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
			if(elementString == NOT_KEYWORD || elementString == IS_KEYWORD || elementString == MORE_KEYWORD || elementString == LESS_KEYWORD)
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
		else if(mustBeLogicOperator)
		{
			if(elementString == AND_KEYWORD || elementString == OR_KEYWORD)
			{
				logicOperators.push_back(elementString);
				mustBeLogicOperator = false;
				mustBeValue = true;
			}
			else
			{
				_throwScriptError("invalid logic operator!");
				return false;
			}
		}
	}

	// Check if condition did not end with a logic operator
	if(mustBeValue || mustBeComparisonOperator)
	{
		_throwScriptError("condition is incomplete!");
		return false;
	}

	// Single condition
	if(conditions.size() == 1)
	{
		return conditions.front();
	}

	// Multiple conditions
	bool finalCondition = conditions[0];
	string currentLogicOperator = "";
	for(size_t i = 1; i < conditions.size(); i++)
	{
		if(currentLogicOperator.empty()) // Save logic operator
		{
			currentLogicOperator = logicOperators[i - 1];
		}
		else if(currentLogicOperator != logicOperators[i - 1]) // Check logic operator
		{
			_throwScriptError("cannot use different logic operators!");
			return false;
		}

		if(logicOperators[i - 1] == AND_KEYWORD) // AND
		{
			finalCondition = finalCondition && conditions[i];
		}
		else if(logicOperators[i - 1] == OR_KEYWORD) // OR
		{
			finalCondition = finalCondition || conditions[i];
		}
	}

	return finalCondition;
}

const bool ScriptInterpreter::_validateCondition(ScriptValue& firstValue, const string& comparisonOperator, ScriptValue& secondValue)
{
	// Check if comparison values are of the same type
	if(firstValue.getType() != secondValue.getType())
	{
		_throwScriptError("compared values not of the same type!");
		return false;
	}

	// Check if not trying to compare string values with the wrong operator
	if((comparisonOperator == MORE_KEYWORD || comparisonOperator == LESS_KEYWORD) && firstValue.getType() == ScriptValueType::STRING)
	{
		_throwScriptError("invalid comparison operator for STR values!");
		return false;
	}

	// Check if not trying to compare boolean values with the wrong operator
	if((comparisonOperator == MORE_KEYWORD || comparisonOperator == LESS_KEYWORD) && firstValue.getType() == ScriptValueType::BOOLEAN)
	{
		_throwScriptError("invalid comparison operator for BOOL values!");
		return false;
	}

	// Condition is valid
	return true;
}

const bool ScriptInterpreter::_compareValues(ScriptValue& firstValue, const string& comparisonOperator, ScriptValue& secondValue) const
{
	if(comparisonOperator == IS_KEYWORD)
	{
		if(firstValue.getType() == ScriptValueType::STRING)
		{
			return (firstValue.getString() == secondValue.getString());
		}
		else if(firstValue.getType() == ScriptValueType::DECIMAL)
		{
			return (firstValue.getDecimal() == secondValue.getDecimal());
		}
		else if(firstValue.getType() == ScriptValueType::INTEGER)
		{
			return (firstValue.getInteger() == secondValue.getInteger());
		}
		else if(firstValue.getType() == ScriptValueType::BOOLEAN)
		{
			return (firstValue.getBoolean() == secondValue.getBoolean());
		}
	}
	else if(comparisonOperator == NOT_KEYWORD)
	{
		if(firstValue.getType() == ScriptValueType::STRING)
		{
			return (firstValue.getString() != secondValue.getString());
		}
		else if(firstValue.getType() == ScriptValueType::DECIMAL)
		{
			return (firstValue.getDecimal() != secondValue.getDecimal());
		}
		else if(firstValue.getType() == ScriptValueType::INTEGER)
		{
			return (firstValue.getInteger() != secondValue.getInteger());
		}
		else if(firstValue.getType() == ScriptValueType::BOOLEAN)
		{
			return (firstValue.getBoolean() != secondValue.getBoolean());
		}
	}
	else if(comparisonOperator == MORE_KEYWORD)
	{
		if(firstValue.getType() == ScriptValueType::DECIMAL)
		{
			return (firstValue.getDecimal() > secondValue.getDecimal());
		}
		else if(firstValue.getType() == ScriptValueType::INTEGER)
		{
			return (firstValue.getInteger() > secondValue.getInteger());
		}
	}
	else if(comparisonOperator == LESS_KEYWORD)
	{
		if(firstValue.getType() == ScriptValueType::DECIMAL)
		{
			return (firstValue.getDecimal() < secondValue.getDecimal());
		}
		else if(firstValue.getType() == ScriptValueType::INTEGER)
		{
			return (firstValue.getInteger() < secondValue.getInteger());
		}
	}
	else
	{
		Logger::throwError("ScriptInterpreter::_compareValues");
	}

	return false;
}