#include "script_interpreter.hpp"

bool ScriptInterpreter::_checkConditionString(string conditionString)
{
	// Check if condition is not empty
	if (conditionString.empty())
	{
		_throwScriptError("no condition found!");
		return false;
	}

	// Temporary values
	vector<string> elements;
	string elementBuild = "";
	unsigned int index = 0;
	bool buildingString = false;
	bool buildingVec3 = false;

	// Extract all invidual elements of the if statement
	for(auto& c : conditionString)
	{
		if (c == ' ' && elementBuild.empty() && !buildingString && !buildingVec3) // Check for useless whitespace
		{
			index++;
			continue;
		}
		else if(index == conditionString.size() - 1) // Check if last character
		{
			elementBuild += c;
			elements.push_back(elementBuild);
		}
		else if (c == ' ' && !buildingString && !buildingVec3) // Check for whitespace
		{
			elements.push_back(elementBuild);
			elementBuild.clear();
		}
		else // Keep building element string
		{
			if (c == '"' && !buildingString)
			{
				buildingString = true;
			}
			else if (c == '"' && buildingString)
			{
				buildingString = false;
			}
			else if (c == '[')
			{
				buildingVec3 = true;
			}
			else if (c == ']')
			{
				buildingVec3 = false;
			}

			// Add character
			elementBuild += c;
		}

		index++;
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
			if (_isVec3Value(elementString)) // VEC3
			{
				comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, _extractVec3FromString(elementString)));
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
			else // VARIABLE
			{
				// Check if accessing individual value from list variable
				bool isAccessingList = false;
				auto listIndex = _extractListIndexFromString(elementString, isAccessingList);

				// Check if accessing individual float from vec3 variable
				auto vec3Parts = _extractVec3PartFromString(elementString);

				// Check if any error was thrown
				if (_hasThrownError)
				{
					return false;
				}

				// Remove vec3 part characters
				if (vec3Parts != Ivec3(0))
				{
					elementString.pop_back();
					elementString.pop_back();
				}

				// Remove list accessing characters
				if (isAccessingList)
				{
					auto openingBracketFound = std::find(elementString.begin(), elementString.end(), '[');
					unsigned int bracketIndex = std::distance(elementString.begin(), openingBracketFound);
					elementString = elementString.substr(0, bracketIndex);
				}

				// Check if using a variable as value
				if (_isLocalVariableExisting(elementString) || _isGlobalVariableExisting(elementString))
				{
					// Retrieve variable value
					auto variable = _isLocalVariableExisting(elementString) ? _getLocalVariable(elementString) :
						_getGlobalVariable(elementString);

					if (vec3Parts.x) // Vec3.x
					{
						comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, variable.getValue().getVec3().x));
					}
					else if (vec3Parts.y) // Vec3.y
					{
						comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, variable.getValue().getVec3().y));
					}
					else if (vec3Parts.z) // Vec3.z
					{
						comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, variable.getValue().getVec3().z));
					}
					else if (isAccessingList) // List[index]
					{
						// Check if list index is valid
						if (_validateListIndex(variable, listIndex))
						{
							comparisonValues.push_back(variable.getValue(listIndex));
						}
						else // Error
						{
							return false;
						}
					}
					else if (variable.getType() == ScriptVariableType::SINGLE) // Normal variable
					{
						comparisonValues.push_back(variable.getValue());
					}
					else // Cannot be list variable
					{
						_throwScriptError("list variable cannot be used in a condition!");
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
			if (comparisonValues.size() == 2)
			{
				// Check if condition is possible at all
				if (_validateCondition(comparisonValues.front(), comparisonOperator, comparisonValues.back()))
				{
					conditions.push_back(_compareValues(comparisonValues.front(), comparisonOperator, comparisonValues.back()));
					comparisonValues.clear();
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
			if (elementString == _andKeyword || elementString == _orKeyword)
			{
				logicalOperators.push_back(elementString);
				mustBeLogicalOperator = false;
				mustBeValue = true;
			}
			else
			{
				_throwScriptError("invalid logical operator!");
				return false;
			}
		}
	}

	// Single condition
	if (conditions.size() == 1)
	{
		return conditions.front();
	}

	// Multiple conditions
	bool finalCondition = conditions[0];
	string currentLogicalOperator = "";
	for (unsigned int i = 1; i < conditions.size(); i++)
	{
		if (currentLogicalOperator.empty()) // Save logical operator
		{
			currentLogicalOperator = logicalOperators[i - 1];
		}
		else if (currentLogicalOperator != logicalOperators[i - 1]) // Check logical operator
		{
			_throwScriptError("cannot use different logical operators!");
			return false;
		}

		if (logicalOperators[i - 1] == _andKeyword) // AND
		{
			finalCondition = finalCondition && conditions[i];
		}
		else if(logicalOperators[i - 1] == _orKeyword) // OR
		{
			finalCondition = finalCondition || conditions[i];
		}
	}

	return finalCondition;
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

	// Check if not trying to compare boolean values with the wrong operator
	if ((comparisonOperator == _moreKeyword || comparisonOperator == _lessKeyword) && firstValue.getType() == ScriptValueType::BOOLEAN)
	{
		_throwScriptError("invalid comparison operator for boolean values!");
		return false;
	}

	// Condition is valid
	return true;
}

bool ScriptInterpreter::_compareValues(ScriptValue& firstValue, string comparisonOperator, ScriptValue& secondValue)
{
	if (comparisonOperator == _isKeyword)
	{
		if (firstValue.getType() == ScriptValueType::VEC3)
		{
			return (firstValue.getVec3() == secondValue.getVec3());
		}
		else if (firstValue.getType() == ScriptValueType::STRING)
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
		if (firstValue.getType() == ScriptValueType::VEC3)
		{
			return (firstValue.getVec3() != secondValue.getVec3());
		}
		else if (firstValue.getType() == ScriptValueType::STRING)
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

	_fe3d.logger_throwError("This error should not be thrown...");
	return false;
}