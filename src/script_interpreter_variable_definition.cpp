#include "script_interpreter.hpp"
#include "logger.hpp"

using std::initializer_list;

void ScriptInterpreter::_processVariableDefinition(const string & scriptLine)
{
	const auto forbiddenVariableNames =
	{
		META_KEYWORD,
		PASS_KEYWORD,
		EXIT_KEYWORD,
		CRASH_KEYWORD,
		EXECUTE_KEYWORD,
		DEFINE_KEYWORD,
		ALTER_KEYWORD,
		GLOBAL_KEYWORD,
		FINAL_KEYWORD,
		LIST_KEYWORD,
		STRING_KEYWORD,
		DECIMAL_KEYWORD,
		INTEGER_KEYWORD,
		BOOLEAN_KEYWORD,
		CAST_KEYWORD,
		PUSH_KEYWORD,
		PULL_KEYWORD,
		ADD_KEYWORD,
		SUBTRACT_KEYWORD,
		MULTIPLY_KEYWORD,
		DIVIDE_KEYWORD,
		MODULO_KEYWORD,
		NEGATE_KEYWORD,
		IF_KEYWORD,
		ELIF_KEYWORD,
		ELSE_KEYWORD,
		IS_KEYWORD,
		NOT_KEYWORD,
		MORE_KEYWORD,
		LESS_KEYWORD,
		AND_KEYWORD,
		OR_KEYWORD,
		LOOP_KEYWORD,
		CONTINUE_KEYWORD,
		BREAK_KEYWORD,
	};

	const auto possibleGlobalKeyword = scriptLine.substr(0, (GLOBAL_KEYWORD.size() + 1));
	const auto scope = ((possibleGlobalKeyword == (GLOBAL_KEYWORD + " ")) ? ScriptScopeType::GLOBAL : ScriptScopeType::LOCAL);

	bool isFinal;

	switch(scope)
	{
		case ScriptScopeType::GLOBAL:
		{
			const auto possibleConstKeyword = scriptLine.substr(GLOBAL_KEYWORD.size(), FINAL_KEYWORD.size() + 2);

			isFinal = (possibleConstKeyword == (" " + FINAL_KEYWORD + " "));

			break;
		}
		case ScriptScopeType::LOCAL:
		{
			const auto possibleConstKeyword = scriptLine.substr(0, FINAL_KEYWORD.size() + 1);

			isFinal = (possibleConstKeyword == (FINAL_KEYWORD + " "));

			break;
		}
	}

	string words[3] = {"", "", ""};

	int typeIndex = 0;
	int wordIndex = 0;

	typeIndex += ((scope == ScriptScopeType::GLOBAL) ? static_cast<int>(GLOBAL_KEYWORD.size() + 1) : 0);
	typeIndex += (isFinal ? static_cast<int>(FINAL_KEYWORD.size() + 1) : 0);

	for(const auto & character : scriptLine.substr(typeIndex))
	{
		if(character == ' ')
		{
			wordIndex++;

			if(wordIndex == 3)
			{
				break;
			}
		}
		else
		{
			words[wordIndex] += character;
		}
	}

	const auto typeString = words[0];
	const auto nameString = words[1];
	const auto equalSignString = words[2];

	if(typeString.empty())
	{
		_throwRuntimeError("variable type missing");

		return;
	}

	if(nameString.empty())
	{
		_throwRuntimeError("variable name missing");

		return;
	}

	if(typeString != LIST_KEYWORD &&
	   typeString != STRING_KEYWORD &&
	   typeString != DECIMAL_KEYWORD &&
	   typeString != INTEGER_KEYWORD &&
	   typeString != BOOLEAN_KEYWORD)
	{
		_throwRuntimeError("invalid variable type");

		return;
	}

	auto isValidName =
		(
		!nameString.empty() &&
		nameString.substr(0, 5) != "fe3d:" &&
		nameString.substr(0, 5) != "math:" &&
		nameString.substr(0, 5) != "misc:" &&
		!isdigit(nameString[0]) &&
		(isalnum(nameString[0]) || nameString[0] == '_')
		);

	for(const auto & word : forbiddenVariableNames)
	{
		isValidName = (isValidName && (nameString != word));
	}

	for(const auto & character : nameString)
	{
		if(character != '_' && !isalnum(character))
		{
			isValidName = false;
		}
	}

	if(scope == ScriptScopeType::GLOBAL && nameString[0] != '_')
	{
		_throwRuntimeError("global variables must start with '_'");

		return;
	}

	if(scope == ScriptScopeType::LOCAL && nameString[0] == '_')
	{
		_throwRuntimeError("local variables cannot start with '_'");

		return;
	}

	if(!isValidName)
	{
		_throwRuntimeError("forbidden variable name");

		return;
	}

	auto & variableList = ((scope == ScriptScopeType::LOCAL) ? _localVariables[_executionDepth] : _globalVariables);

	if(((scope == ScriptScopeType::LOCAL) && _isLocalVariableExisting(nameString))
	   ||
	   ((scope == ScriptScopeType::GLOBAL) && _isGlobalVariableExisting(nameString)))
	{
		_throwRuntimeError("variable \"" + nameString + "\" already defined");

		return;
	}

	if(equalSignString != "=")
	{
		_throwRuntimeError("equal sign missing");

		return;
	}

	const auto minLineSize = (scriptLine.find('=') + 3);

	if(scriptLine.size() < minLineSize)
	{
		_throwRuntimeError("value missing");

		return;
	}

	auto valueString = scriptLine.substr(minLineSize - 1);

	if((typeString == LIST_KEYWORD) && _isListValue(valueString))
	{
		const auto listString = valueString.substr(1, (valueString.size() - 2));
		const auto values = _extractValuesFromListString(listString);

		variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::MULTIPLE, isFinal, values)});
	}
	else if((typeString == STRING_KEYWORD) && _isStringValue(valueString))
	{
		valueString.erase(valueString.begin());
		valueString.pop_back();

		const auto value = make_shared<ScriptValue>(ScriptValueType::STRING, valueString);

		variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isFinal, initializer_list{value})});
	}
	else if((typeString == DECIMAL_KEYWORD) && _isDecimalValue(valueString))
	{
		const auto value = make_shared<ScriptValue>(ScriptValueType::DECIMAL, stof(_limitDecimalString(valueString)));

		variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isFinal, initializer_list{value})});
	}
	else if((typeString == INTEGER_KEYWORD) && _isIntegerValue(valueString))
	{
		const auto value = make_shared<ScriptValue>(ScriptValueType::INTEGER, stoi(_limitIntegerString(valueString)));

		variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isFinal, initializer_list{value})});
	}
	else if((typeString == BOOLEAN_KEYWORD) && _isBooleanValue(valueString))
	{
		const auto value = make_shared<ScriptValue>(ScriptValueType::BOOLEAN, (valueString == "<true>"));

		variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isFinal, initializer_list{value})});
	}
	else if((typeString == BOOLEAN_KEYWORD) && (valueString[0] == '(' && valueString.back() == ')'))
	{
		valueString.erase(valueString.begin());
		valueString.pop_back();

		const auto value = make_shared<ScriptValue>(ScriptValueType::BOOLEAN, _checkConditionString(valueString));

		variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isFinal, initializer_list{value})});
	}
	else if((valueString.substr(0, 5) == "fe3d:") || (valueString.substr(0, 5) == "math:") || (valueString.substr(0, 5) == "misc:"))
	{
		const auto loggerMessageCount = Logger::getMessageCount();
		const auto returnValues =
			(valueString.substr(0, 5) == "fe3d:") ? _processFe3dFunctionCall(valueString) :
			(valueString.substr(0, 5) == "math:") ? _processMathFunctionCall(valueString) :
			_processMiscFunctionCall(valueString);

		_checkEngineWarnings(loggerMessageCount);

		if(_hasThrownError)
		{
			return;
		}

		for(const auto & value : returnValues)
		{
			if(value->getType() == ScriptValueType::EMPTY)
			{
				_throwRuntimeError("function returned empty value");

				return;
			}
		}

		if(typeString == LIST_KEYWORD)
		{
			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::MULTIPLE, isFinal, returnValues)});
		}
		else if(returnValues.empty())
		{
			_throwRuntimeError("function returned no values");

			return;
		}
		else if(returnValues.size() > 1)
		{
			_throwRuntimeError("function returned too many values");

			return;
		}
		else if(returnValues[0]->getType() == ScriptValueType::EMPTY)
		{
			_throwRuntimeError("function must return value");

			return;
		}
		else if((typeString == STRING_KEYWORD) && (returnValues[0]->getType() == ScriptValueType::STRING))
		{
			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isFinal, returnValues)});
		}
		else if((typeString == DECIMAL_KEYWORD) && (returnValues[0]->getType() == ScriptValueType::DECIMAL))
		{
			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isFinal, returnValues)});
		}
		else if((typeString == INTEGER_KEYWORD) && (returnValues[0]->getType() == ScriptValueType::INTEGER))
		{
			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isFinal, returnValues)});
		}
		else if((typeString == BOOLEAN_KEYWORD) && (returnValues[0]->getType() == ScriptValueType::BOOLEAN))
		{
			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isFinal, returnValues)});
		}
		else
		{
			_throwRuntimeError("function returned incorrect value type");

			return;
		}
	}
	else
	{
		bool isAccessingList = false;

		const auto listIndex = _extractListIndexFromString(valueString, isAccessingList);

		if(_hasThrownError)
		{
			return;
		}

		if(isAccessingList)
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

		int valueIndex = 0;

		if(isAccessingList)
		{
			if(!_validateListIndex(rightVariable, listIndex))
			{
				return;
			}

			valueIndex = listIndex;
		}

		if((typeString == LIST_KEYWORD) && (rightVariable->getType() == ScriptVariableType::MULTIPLE))
		{
			vector<shared_ptr<ScriptValue>> values = {};

			for(int index = 0; index < rightVariable->getValueCount(); index++)
			{
				const auto value = rightVariable->getValue(index);

				switch(value->getType())
				{
					case ScriptValueType::STRING:
					{
						values.push_back(make_shared<ScriptValue>(ScriptValueType::STRING, value->getString()));

						break;
					}
					case ScriptValueType::DECIMAL:
					{
						values.push_back(make_shared<ScriptValue>(ScriptValueType::DECIMAL, value->getDecimal()));

						break;
					}
					case ScriptValueType::INTEGER:
					{
						values.push_back(make_shared<ScriptValue>(ScriptValueType::INTEGER, value->getInteger()));

						break;
					}
					case ScriptValueType::BOOLEAN:
					{
						values.push_back(make_shared<ScriptValue>(ScriptValueType::BOOLEAN, value->getBoolean()));

						break;
					}
				}
			}

			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::MULTIPLE, isFinal, values)});
		}
		else if((typeString == STRING_KEYWORD) && (rightVariable->getValue(valueIndex)->getType() == ScriptValueType::STRING))
		{
			const auto values = initializer_list{make_shared<ScriptValue>(ScriptValueType::STRING, rightVariable->getValue(valueIndex)->getString())};

			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isFinal, values)});
		}
		else if((typeString == DECIMAL_KEYWORD) && (rightVariable->getValue(valueIndex)->getType() == ScriptValueType::DECIMAL))
		{
			const auto values = initializer_list{make_shared<ScriptValue>(ScriptValueType::DECIMAL, rightVariable->getValue(valueIndex)->getDecimal())};

			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isFinal, values)});
		}
		else if((typeString == INTEGER_KEYWORD) && (rightVariable->getValue(valueIndex)->getType() == ScriptValueType::INTEGER))
		{
			const auto values = initializer_list{make_shared<ScriptValue>(ScriptValueType::INTEGER, rightVariable->getValue(valueIndex)->getInteger())};

			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isFinal, values)});
		}
		else if((typeString == BOOLEAN_KEYWORD) && (rightVariable->getValue(valueIndex)->getType() == ScriptValueType::BOOLEAN))
		{
			const auto values = initializer_list{make_shared<ScriptValue>(ScriptValueType::BOOLEAN, rightVariable->getValue(valueIndex)->getBoolean())};

			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isFinal, values)});
		}
		else
		{
			_throwRuntimeError("value types not matching");

			return;
		}
	}
}