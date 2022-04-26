#include "script_interpreter.hpp"
#include "logger.hpp"

using std::initializer_list;

void ScriptInterpreter::_processVariableCreation(const string & scriptLine, ScriptScopeType scope)
{
	auto forbiddenVariableNames = {
		META_KEYWORD,
		EXECUTE_KEYWORD,
		LOOP_KEYWORD,
		CONTINUE_KEYWORD,
		BREAK_KEYWORD,
		IF_KEYWORD,
		ELIF_KEYWORD,
		ELSE_KEYWORD,
		GLOBAL_KEYWORD,
		CONST_KEYWORD,
		EDIT_KEYWORD,
		LIST_KEYWORD,
		STRING_KEYWORD,
		DECIMAL_KEYWORD,
		INTEGER_KEYWORD,
		BOOLEAN_KEYWORD,
		IS_KEYWORD,
		NOT_KEYWORD,
		AND_KEYWORD,
		OR_KEYWORD,
		MORE_KEYWORD,
		LESS_KEYWORD,
		ADDITION_KEYWORD,
		SUBTRACTION_KEYWORD,
		MULTIPLICATION_KEYWORD,
		DIVISION_KEYWORD,
		MODULO_KEYWORD,
		NEGATION_KEYWORD,
		CASTING_KEYWORD,
		PUSHING_KEYWORD,
		PULLING_KEYWORD,
		PASS_KEYWORD
	};

	bool isConstant = false;
	if(scope == ScriptScopeType::GLOBAL)
	{
		string possibleConstKeyword = scriptLine.substr(GLOBAL_KEYWORD.size(), CONST_KEYWORD.size() + 2);
		isConstant = (possibleConstKeyword == (" " + CONST_KEYWORD + " "));
	}
	else
	{
		string possibleConstKeyword = scriptLine.substr(0, CONST_KEYWORD.size() + 1);
		isConstant = (possibleConstKeyword == (CONST_KEYWORD + " "));
	}

	string words[3] = {"", "", ""};
	unsigned int typeIndex = 0;
	unsigned int wordIndex = 0;
	typeIndex += static_cast<unsigned int>((scope == ScriptScopeType::GLOBAL) ? (GLOBAL_KEYWORD.size() + 1) : 0);
	typeIndex += static_cast<unsigned int>(isConstant ? (CONST_KEYWORD.size() + 1) : 0);
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
	string typeString = words[0];
	string nameString = words[1];
	string equalSignString = words[2];

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

	bool isValidName = !nameString.empty() &&
		nameString.substr(0, 5) != "fe3d:" &&
		nameString.substr(0, 5) != "math:" &&
		nameString.substr(0, 5) != "misc:" &&
		!isdigit(nameString[0]) &&
		(isalnum(nameString[0]) || nameString[0] == '_');

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

	if((scope == ScriptScopeType::LOCAL && _isLocalVariableExisting(nameString)) ||
	   (scope == ScriptScopeType::GLOBAL && _isGlobalVariableExisting(nameString)))
	{
		_throwRuntimeError("variable \"" + nameString + "\" already defined");

		return;
	}

	if(equalSignString != "=")
	{
		_throwRuntimeError("equal sign missing");

		return;
	}

	auto minLineSize = (scriptLine.find('=') + 3);
	if(scriptLine.size() < minLineSize)
	{
		_throwRuntimeError("value missing");

		return;
	}

	string valueString = scriptLine.substr(minLineSize - 1);

	if((typeString == LIST_KEYWORD) && _isListValue(valueString))
	{
		string listString = valueString.substr(1);
		listString.pop_back();

		auto values = _extractValuesFromListString(listString);

		variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::MULTIPLE, isConstant, values)});
	}
	else if((typeString == STRING_KEYWORD) && _isStringValue(valueString))
	{
		valueString.erase(valueString.begin());
		valueString.pop_back();

		auto value = make_shared<ScriptValue>(ScriptValueType::STRING, valueString);

		variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isConstant, initializer_list{value})});
	}
	else if((typeString == DECIMAL_KEYWORD) && _isDecimalValue(valueString))
	{
		auto value = make_shared<ScriptValue>(ScriptValueType::DECIMAL, stof(_limitDecimalString(valueString)));

		variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isConstant, initializer_list{value})});
	}
	else if((typeString == INTEGER_KEYWORD) && _isIntegerValue(valueString))
	{
		auto value = make_shared<ScriptValue>(ScriptValueType::INTEGER, stoi(_limitIntegerString(valueString)));

		variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isConstant, initializer_list{value})});
	}
	else if((typeString == BOOLEAN_KEYWORD) && _isBooleanValue(valueString))
	{
		auto value = make_shared<ScriptValue>(ScriptValueType::BOOLEAN, (valueString == "<true>"));

		variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isConstant, initializer_list{value})});
	}
	else if((typeString == BOOLEAN_KEYWORD) && (valueString[0] == '(' && valueString.back() == ')'))
	{
		valueString.erase(valueString.begin());
		valueString.pop_back();

		auto value = make_shared<ScriptValue>(ScriptValueType::BOOLEAN, _checkConditionString(valueString));

		variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isConstant, initializer_list{value})});
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
			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::MULTIPLE, isConstant, returnValues)});
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
			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isConstant, returnValues)});
		}
		else if((typeString == DECIMAL_KEYWORD) && (returnValues[0]->getType() == ScriptValueType::DECIMAL))
		{
			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isConstant, returnValues)});
		}
		else if((typeString == INTEGER_KEYWORD) && (returnValues[0]->getType() == ScriptValueType::INTEGER))
		{
			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isConstant, returnValues)});
		}
		else if((typeString == BOOLEAN_KEYWORD) && (returnValues[0]->getType() == ScriptValueType::BOOLEAN))
		{
			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isConstant, returnValues)});
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
		auto listIndex = _extractListIndexFromString(valueString, isAccessingList);

		if(_hasThrownError)
		{
			return;
		}

		if(isAccessingList)
		{
			auto isOpeningBracketFound = find(valueString.begin(), valueString.end(), '[');
			auto bracketIndex = static_cast<unsigned int>(distance(valueString.begin(), isOpeningBracketFound));
			valueString = valueString.substr(0, bracketIndex);
		}

		if(!_isLocalVariableExisting(valueString) && !_isGlobalVariableExisting(valueString))
		{
			_throwRuntimeError("variable \"" + valueString + "\" does not exist");

			return;
		}

		const auto rightVariable = (_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) : _getGlobalVariable(valueString));

		unsigned int valueIndex = 0;
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
			for(unsigned int index = 0; index < rightVariable->getValueCount(); index++)
			{
				values.push_back(rightVariable->getValue(index));
			}

			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::MULTIPLE, isConstant, values)});
		}
		else if((typeString == STRING_KEYWORD) && (rightVariable->getValue(valueIndex)->getType() == ScriptValueType::STRING))
		{
			auto value = rightVariable->getValue(valueIndex);

			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isConstant, initializer_list{value})});
		}
		else if((typeString == DECIMAL_KEYWORD) && (rightVariable->getValue(valueIndex)->getType() == ScriptValueType::DECIMAL))
		{
			auto value = rightVariable->getValue(valueIndex);

			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isConstant, initializer_list{value})});
		}
		else if((typeString == INTEGER_KEYWORD) && (rightVariable->getValue(valueIndex)->getType() == ScriptValueType::INTEGER))
		{
			auto value = rightVariable->getValue(valueIndex);

			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isConstant, initializer_list{value})});
		}
		else if((typeString == BOOLEAN_KEYWORD) && (rightVariable->getValue(valueIndex)->getType() == ScriptValueType::BOOLEAN))
		{
			auto value = rightVariable->getValue(valueIndex);

			variableList.insert({nameString, make_shared<ScriptVariable>(nameString, scope, ScriptVariableType::SINGLE, isConstant, initializer_list{value})});
		}
		else
		{
			_throwRuntimeError("value types not matching");

			return;
		}
	}
}