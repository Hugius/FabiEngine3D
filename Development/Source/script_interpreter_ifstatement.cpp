#include "script_interpreter.hpp"

bool ScriptInterpreter::_checkIfStatement(string conditionString)
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
		if(index == conditionString.size() - 1) // Check if last character
		{
			elementBuild += c;
			elements.push_back(elementBuild);
		}
		else if ((c == ' ' && !buildingString && !buildingVec3)) // Check if whitespace
		{
			elements.push_back(elementBuild);
			elementBuild = "";
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
				// Check if accessing individual float from vec3 variable
				auto parts = _checkVec3Part(elementString);
				
				// Remove vec3 part text
				if (parts != Ivec3(0))
				{
					elementString.pop_back();
					elementString.pop_back();
				}

				// Check if using a variable as value
				if (_isLocalVariableExisting(elementString) || _isGlobalVariableExisting(elementString))
				{
					// Retrieve variable value
					auto variable = _isLocalVariableExisting(elementString) ? _getLocalVariable(elementString) :
						_getGlobalVariable(elementString);

					if (parts.x) // Vec3.x
					{
						comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, variable.getValue().getVec3().x));
					}
					else if (parts.y) // Vec3.y
					{
						comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, variable.getValue().getVec3().y));
					}
					else if (parts.z) // Vec3.z
					{
						comparisonValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, variable.getValue().getVec3().z));
					}
					else // Normal variable
					{
						comparisonValues.push_back(variable.getValue());
					}
				}
				else
				{
					_throwScriptError("invalid comparison value or variable!");
					return false;
				}
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