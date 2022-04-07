#include "script_interpreter.hpp"
#include "logger.hpp"

const bool ScriptInterpreter::_checkConditionString(const string & conditionString)
{
	vector<shared_ptr<ScriptValue>> comparisonValues;
	vector<string> elements;
	vector<string> logicOperators;
	vector<bool> conditions;
	string elementBuild = "";
	string comparisonOperator = "";
	unsigned int characterIndex = 0;
	bool isBuildingString = false;
	bool mustBeValue = true;
	bool mustBeComparisonOperator = false;
	bool mustBeLogicOperator = false;

	if(conditionString.empty())
	{
		_throwRuntimeError("no condition found");
		return false;
	}

	for(const auto & character : conditionString)
	{
		if(character == ' ' && elementBuild.empty() && !isBuildingString)
		{
			characterIndex++;
			continue;
		}
		else if(characterIndex == conditionString.size() - 1)
		{
			elementBuild += character;
			elements.push_back(elementBuild);
		}
		else if(character == ' ' && !isBuildingString)
		{
			elements.push_back(elementBuild);
			elementBuild.clear();
		}
		else
		{
			if(character == '"' && !isBuildingString)
			{
				isBuildingString = true;
			}
			else if(character == '"' && isBuildingString)
			{
				isBuildingString = false;
			}

			elementBuild += character;
		}

		characterIndex++;
	}

	if(elements.size() < 3)
	{
		_throwRuntimeError("not enough elements in condition");
		return false;
	}

	for(auto & elementString : elements)
	{
		if(mustBeValue)
		{
			if(_isListValue(elementString))
			{
				_throwRuntimeError("LIST value cannot be used in condition");
				return false;
			}
			else if(_isStringValue(elementString))
			{
				elementString.erase(elementString.begin());
				elementString.pop_back();
				comparisonValues.push_back(make_shared<ScriptValue>(ScriptValueType::STRING, elementString));
			}
			else if(_isDecimalValue(elementString))
			{
				comparisonValues.push_back(make_shared<ScriptValue>(ScriptValueType::DECIMAL, stof(_limitDecimalString(elementString))));
			}
			else if(_isIntegerValue(elementString))
			{
				comparisonValues.push_back(make_shared<ScriptValue>(ScriptValueType::INTEGER, stoi(_limitIntegerString(elementString))));
			}
			else if(_isBooleanValue(elementString))
			{
				comparisonValues.push_back(make_shared<ScriptValue>(ScriptValueType::BOOLEAN, (elementString == "<true>")));
			}
			else
			{
				bool isAccessingList = false;
				auto listIndex = _extractListIndexFromString(elementString, isAccessingList);

				if(_hasThrownError)
				{
					return {};
				}

				if(isAccessingList)
				{
					auto isOpeningBracketFound = find(elementString.begin(), elementString.end(), '[');
					auto bracketIndex = static_cast<unsigned int>(distance(elementString.begin(), isOpeningBracketFound));
					elementString = elementString.substr(0, bracketIndex);
				}

				if(!_isLocalVariableExisting(elementString) && !_isGlobalVariableExisting(elementString))
				{
					_throwRuntimeError("invalid comparison value");
					return false;
				}

				const auto variable = (_isLocalVariableExisting(elementString) ? _getLocalVariable(elementString) : _getGlobalVariable(elementString));

				unsigned int valueIndex = 0;
				if(isAccessingList)
				{
					if(!_validateListIndex(variable, listIndex))
					{
						return {};
					}

					valueIndex = listIndex;
				}

				if(!isAccessingList && variable->getType() == ScriptVariableType::MULTIPLE)
				{
					_throwRuntimeError("LIST variable cannot be used in condition");
					return false;
				}

				comparisonValues.push_back(variable->getValue(valueIndex));
			}

			if(comparisonValues.size() == 2)
			{
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
				_throwRuntimeError("invalid comparison operator");
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
				_throwRuntimeError("invalid logic operator");
				return false;
			}
		}
	}

	if(mustBeValue || mustBeComparisonOperator)
	{
		_throwRuntimeError("condition incomplete");
		return false;
	}

	if(conditions.size() == 1)
	{
		return conditions[0];
	}

	bool finalCondition = conditions[0];
	string currentLogicOperator = "";
	for(unsigned int index = 1; index < static_cast<unsigned int>(conditions.size()); index++)
	{
		if(currentLogicOperator.empty())
		{
			currentLogicOperator = logicOperators[index - 1];
		}
		else if(currentLogicOperator != logicOperators[index - 1])
		{
			_throwRuntimeError("cannot use different logic operators");
			return false;
		}

		if(logicOperators[index - 1] == AND_KEYWORD)
		{
			finalCondition = finalCondition && conditions[index];
		}
		else if(logicOperators[index - 1] == OR_KEYWORD)
		{
			finalCondition = finalCondition || conditions[index];
		}
	}

	return finalCondition;
}

const bool ScriptInterpreter::_validateCondition(shared_ptr<ScriptValue> firstValue, const string & comparisonOperator, shared_ptr<ScriptValue> secondValue)
{
	if(firstValue->getType() != secondValue->getType())
	{
		_throwRuntimeError("compared values not of the same type");
		return false;
	}

	if(((comparisonOperator == MORE_KEYWORD) || (comparisonOperator == LESS_KEYWORD)) && (firstValue->getType() == ScriptValueType::STRING))
	{
		_throwRuntimeError("invalid comparison operator for STR values");
		return false;
	}

	if(((comparisonOperator == MORE_KEYWORD) || (comparisonOperator == LESS_KEYWORD)) && (firstValue->getType() == ScriptValueType::BOOLEAN))
	{
		_throwRuntimeError("invalid comparison operator for BOOL values");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_compareValues(shared_ptr<ScriptValue> firstValue, const string & comparisonOperator, shared_ptr<ScriptValue> secondValue) const
{
	if(comparisonOperator == IS_KEYWORD)
	{
		if(firstValue->getType() == ScriptValueType::STRING)
		{
			return (firstValue->getString() == secondValue->getString());
		}
		else if(firstValue->getType() == ScriptValueType::DECIMAL)
		{
			return (firstValue->getDecimal() == secondValue->getDecimal());
		}
		else if(firstValue->getType() == ScriptValueType::INTEGER)
		{
			return (firstValue->getInteger() == secondValue->getInteger());
		}
		else if(firstValue->getType() == ScriptValueType::BOOLEAN)
		{
			return (firstValue->getBoolean() == secondValue->getBoolean());
		}
	}
	else if(comparisonOperator == NOT_KEYWORD)
	{
		if(firstValue->getType() == ScriptValueType::STRING)
		{
			return (firstValue->getString() != secondValue->getString());
		}
		else if(firstValue->getType() == ScriptValueType::DECIMAL)
		{
			return (firstValue->getDecimal() != secondValue->getDecimal());
		}
		else if(firstValue->getType() == ScriptValueType::INTEGER)
		{
			return (firstValue->getInteger() != secondValue->getInteger());
		}
		else if(firstValue->getType() == ScriptValueType::BOOLEAN)
		{
			return (firstValue->getBoolean() != secondValue->getBoolean());
		}
	}
	else if(comparisonOperator == MORE_KEYWORD)
	{
		if(firstValue->getType() == ScriptValueType::DECIMAL)
		{
			return (firstValue->getDecimal() > secondValue->getDecimal());
		}
		else if(firstValue->getType() == ScriptValueType::INTEGER)
		{
			return (firstValue->getInteger() > secondValue->getInteger());
		}
	}
	else if(comparisonOperator == LESS_KEYWORD)
	{
		if(firstValue->getType() == ScriptValueType::DECIMAL)
		{
			return (firstValue->getDecimal() < secondValue->getDecimal());
		}
		else if(firstValue->getType() == ScriptValueType::INTEGER)
		{
			return (firstValue->getInteger() < secondValue->getInteger());
		}
	}
	else
	{
		abort();
	}

	return false;
}

const int ScriptInterpreter::_getLastConditionStatementIndex(const vector<ScriptConditionStatement> & statements, unsigned int scopeDepth) const
{
	unsigned int index = static_cast<unsigned int>(statements.size());

	while(index--)
	{
		if(statements[index].getScopeDepth() == scopeDepth)
		{
			return index;
		}
	}

	return -1;
}