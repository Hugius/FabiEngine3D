#include "script_interpreter.hpp"
#include "logger.hpp"

const bool ScriptInterpreter::_checkConditionString(const string& conditionString)
{
	// Temporary values
	vector<ScriptValue> comparisonValues;
	vector<string> elements;
	vector<string> logicOperators;
	vector<bool> conditions;
	string elementBuild = "";
	string comparisonOperator = "";
	unsigned int index = 0;
	bool isBuildingString = false;
	bool mustBeValue = true;
	bool mustBeComparisonOperator = false;
	bool mustBeLogicOperator = false;

	// Check if condition is empty
	if(conditionString.empty())
	{
		_throwScriptError("no condition found!");
		return false;
	}

	// Extract all invidual elements of the if statement
	for(const auto& c : conditionString)
	{
		if(c == ' ' && elementBuild.empty() && !isBuildingString) // Check for useless whitespace
		{
			index++;
			continue;
		}
		else if(index == conditionString.size() - 1) // Check if last character
		{
			elementBuild += c;
			elements.push_back(elementBuild);
		}
		else if(c == ' ' && !isBuildingString) // Check for whitespace
		{
			elements.push_back(elementBuild);
			elementBuild.clear();
		}
		else // Keep building element string
		{
			if(c == '"' && !isBuildingString)
			{
				isBuildingString = true;
			}
			else if(c == '"' && isBuildingString)
			{
				isBuildingString = false;
			}

			// Add character
			elementBuild += c;
		}

		// Increment index
		index++;
	}

	// Check if not enough elements
	if(elements.size() < 3)
	{
		_throwScriptError("not enough elements in condition!");
		return false;
	}

	// Process every element
	for(auto& elementString : elements)
	{
		if(mustBeValue)
		{
			if(_isListValue(elementString))
			{
				_throwScriptError("LIST value cannot be used in condition!");
				return false;
			}
			else if(_isStringValue(elementString))
			{
				elementString.erase(elementString.begin());
				elementString.pop_back();
				comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, elementString));
			}
			else if(_isDecimalValue(elementString))
			{
				comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(_limitDecimalString(elementString))));
			}
			else if(_isIntegerValue(elementString))
			{
				comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(_limitIntegerString(elementString))));
			}
			else if(_isBooleanValue(elementString))
			{
				comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, (elementString == "<true>")));
			}
			else
			{
				// Prepare list access
				bool isAccessingList = false;
				auto listIndex = _extractListIndexFromString(elementString, isAccessingList);

				// Check if any error was thrown
				if(_hasThrownError)
				{
					return {};
				}

				// Remove list accessing characters
				if(isAccessingList)
				{
					auto isOpeningBracketFound = find(elementString.begin(), elementString.end(), '[');
					auto bracketIndex = static_cast<unsigned int>(distance(elementString.begin(), isOpeningBracketFound));
					elementString = elementString.substr(0, bracketIndex);
				}

				// Check if variable is not existing
				if(!_isLocalVariableExisting(elementString) && !_isGlobalVariableExisting(elementString))
				{
					_throwScriptError("invalid comparison value!");
					return false;
				}

				// Retrieve variable
				const auto& variable = (_isLocalVariableExisting(elementString) ? _getLocalVariable(elementString) : _getGlobalVariable(elementString));

				// Validate list access
				unsigned int valueIndex = 0;
				if(isAccessingList)
				{
					// Check if list index is invalid
					if(!_validateListIndex(variable, listIndex))
					{
						return {};
					}

					// Copy list index
					valueIndex = listIndex;
				}

				// Check if variable is a list
				if(!isAccessingList && variable.getType() == ScriptVariableType::MULTIPLE)
				{
					_throwScriptError("LIST variable cannot be used in condition!");
					return false;
				}

				// Add value
				comparisonValues.push_back(variable.getValue(valueIndex));
			}

			// Check if current condition is fully composed
			if(comparisonValues.size() == 2)
			{
				// Check if condition is possible at all
				if(_validateCondition(comparisonValues[0], comparisonOperator, comparisonValues.back()))
				{
					conditions.push_back(_compareValues(comparisonValues[0], comparisonOperator, comparisonValues.back()));
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
		_throwScriptError("condition incomplete!");
		return false;
	}

	// Single condition
	if(conditions.size() == 1)
	{
		return conditions[0];
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
	// Check if comparison values are not of the same type
	if(firstValue.getType() != secondValue.getType())
	{
		_throwScriptError("compared values not of the same type!");
		return false;
	}

	// Check if trying to compare string values with the wrong operator
	if((comparisonOperator == MORE_KEYWORD || comparisonOperator == LESS_KEYWORD) && firstValue.getType() == ScriptValueType::STRING)
	{
		_throwScriptError("invalid comparison operator for STR values!");
		return false;
	}

	// Check if trying to compare boolean values with the wrong operator
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

ScriptConditionStatement* ScriptInterpreter::_getLastConditionStatement(vector<ScriptConditionStatement>& statements, unsigned int scopeDepth) const
{
	// Temporary values
	unsigned int index = static_cast<unsigned int>(statements.size());

	// Iterate through conditions backwards
	while(index--)
	{
		// Check if scope depth matches
		if(statements[index].getScopeDepth() == scopeDepth)
		{
			return &statements[index];
		}
	}

	// No condition statement
	return nullptr;
}