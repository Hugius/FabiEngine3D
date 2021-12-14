#include "script_interpreter.hpp"
#include "logger.hpp"

void ScriptInterpreter::_processVariableCreation(const string& scriptLine, ScriptVariableScope scope)
{
	// Temporary values
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
		NEGATION_KEYWORD,
		CASTING_KEYWORD,
		PUSHING_KEYWORD,
		PULLING_KEYWORD,
		PASS_KEYWORD
	};

	// Extract optional CONST keyword
	bool isConstant = false;
	if(scope == ScriptVariableScope::GLOBAL)
	{
		string possibleConstKeyword = scriptLine.substr(GLOBAL_KEYWORD.size(), CONST_KEYWORD.size() + 2);
		isConstant = (possibleConstKeyword == (" " + CONST_KEYWORD + " "));
	}
	else
	{
		string possibleConstKeyword = scriptLine.substr(0, CONST_KEYWORD.size() + 1);
		isConstant = (possibleConstKeyword == (CONST_KEYWORD + " "));
	}

	// Extract type, name, equal sign
	string words[3] = {"", "", ""};
	unsigned int typeIndex = 0;
	unsigned int wordIndex = 0;
	typeIndex += static_cast<unsigned int>((scope == ScriptVariableScope::GLOBAL) ? (GLOBAL_KEYWORD.size() + 1) : 0);
	typeIndex += static_cast<unsigned int>(isConstant ? (CONST_KEYWORD.size() + 1) : 0);
	for(const auto& c : scriptLine.substr(typeIndex))
	{
		if(c == ' ') // Current word ended
		{
			// Next word
			wordIndex++;

			// Check if words extracted
			if(wordIndex == 3)
			{
				break;
			}
		}
		else // Add to word
		{
			words[wordIndex] += c;
		}
	}
	string typeString = words[0];
	string nameString = words[1];
	string equalSignString = words[2];

	// Check if variable type is missing
	if(typeString.empty())
	{
		_throwScriptError("variable type missing!");
		return;
	}

	// Check if variable name is missing
	if(nameString.empty())
	{
		_throwScriptError("variable name missing!");
		return;
	}

	// Check if variable type is invalid
	if(typeString != LIST_KEYWORD &&
	   typeString != STRING_KEYWORD &&
	   typeString != DECIMAL_KEYWORD &&
	   typeString != INTEGER_KEYWORD &&
	   typeString != BOOLEAN_KEYWORD)
	{
		_throwScriptError("invalid variable type!");
		return;
	}

	// Validate variable name
	bool isValidName = !nameString.empty() &&
		nameString.substr(0, 5) != "fe3d:" &&
		nameString.substr(0, 5) != "math:" &&
		nameString.substr(0, 5) != "misc:" &&
		!isdigit(nameString[0]) &&
		(isalnum(nameString[0]) || nameString[0] == '_');

	// Validate name
	for(const auto& word : forbiddenVariableNames)
	{
		isValidName = (isValidName && (nameString != word));
	}

	// Validate variable individual characters
	for(const auto& c : nameString)
	{
		// Only non-alphanumeric character '_'
		if(c != '_' && !isalnum(c))
		{
			isValidName = false;
		}
	}

	// Check if global variable starts with '_'
	if(scope == ScriptVariableScope::GLOBAL && nameString[0] != '_')
	{
		_throwScriptError("global variables must start with '_'!");
		return;
	}

	// Check if local variable does not start with '_'
	if(scope == ScriptVariableScope::LOCAL && nameString[0] == '_')
	{
		_throwScriptError("local variables cannot start with '_'!");
		return;
	}

	// Check if variable name is valid
	if(!isValidName)
	{
		_throwScriptError("forbidden variable name!");
		return;
	}

	// Retrieve the repsective list of variables
	auto& variableList = ((scope == ScriptVariableScope::LOCAL) ? _localVariables[_executionDepth] : _globalVariables);

	// Check if variable is already defined
	if((scope == ScriptVariableScope::LOCAL && _isLocalVariableExisting(nameString)) ||
	   (scope == ScriptVariableScope::GLOBAL && _isGlobalVariableExisting(nameString)))
	{
		_throwScriptError("variable \"" + nameString + "\" already defined!");
		return;
	}

	// Check if equal sign is missing
	if(equalSignString != "=")
	{
		_throwScriptError("equal sign missing!");
		return;
	}

	// Check if value is missing
	auto minLineSize = (scriptLine.find('=') + 3);
	if(scriptLine.size() < minLineSize)
	{
		_throwScriptError("value missing!");
		return;
	}

	// Extract value
	string valueString = scriptLine.substr(minLineSize - 1);

	// Determine value type
	if((typeString == LIST_KEYWORD) && _isListValue(valueString))
	{
		// Remove the []
		string listString = valueString.substr(1);
		listString.pop_back();

		// Extract values
		auto values = _extractValuesFromListString(listString);

		// Add variable
		variableList.insert(make_pair(nameString,
							ScriptVariable(_fe3d, scope, ScriptVariableType::MULTIPLE, nameString, isConstant, values)));
	}
	else if((typeString == STRING_KEYWORD) && _isStringValue(valueString))
	{
		// Remove the ""
		valueString.erase(valueString.begin());
		valueString.pop_back();

		// Compose values
		auto values = {ScriptValue(_fe3d, ScriptValueType::STRING, valueString)};

		// Add variable
		variableList.insert(make_pair(nameString,
							ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, values)));
	}
	else if((typeString == DECIMAL_KEYWORD) && _isDecimalValue(valueString))
	{
		// Compose values
		auto values = {ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(_limitDecimalString(valueString)))};

		// Add variable
		variableList.insert(make_pair(nameString,
							ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, values)));
	}
	else if((typeString == INTEGER_KEYWORD) && _isIntegerValue(valueString))
	{
		// Compose values
		auto values = {ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(_limitIntegerString(valueString)))};

		// Add variable
		variableList.insert(make_pair(nameString,
							ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, values)));
	}
	else if((typeString == BOOLEAN_KEYWORD) && _isBooleanValue(valueString))
	{
		// Compose values
		auto values = {ScriptValue(_fe3d, ScriptValueType::BOOLEAN, (valueString == "<true>"))};

		// Add variable
		variableList.insert(make_pair(nameString,
							ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, values)));
	}
	else if((typeString == BOOLEAN_KEYWORD) && (valueString[0] == '(' && valueString.back() == ')'))
	{
		// Removing the ()
		valueString.erase(valueString.begin());
		valueString.pop_back();

		// Compose values
		auto value = ScriptValue(_fe3d, ScriptValueType::BOOLEAN, _checkConditionString(valueString));

		// Add variable
		variableList.insert(make_pair(nameString,
							ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, {value})));
	}
	else if((valueString.substr(0, 5) == "fe3d:") || (valueString.substr(0, 5) == "math:") || (valueString.substr(0, 5) == "misc:"))
	{
		// Save current logger message count
		auto loggerMessageCount = Logger::getMessageCount();

		// Call function
		auto returnValues =
			(valueString.substr(0, 5) == "fe3d:") ? _processEngineFunctionCall(valueString) :
			(valueString.substr(0, 5) == "math:") ? _processMathematicsFunctionCall(valueString) :
			_processMiscellaneousFunctionCall(valueString);

		// Check if any error was thrown
		_checkEngineWarnings(loggerMessageCount);
		if(_hasThrownError)
		{
			return;
		}

		// Check if function returned any empty values
		for(const auto& value : returnValues)
		{
			if(value.getType() == ScriptValueType::EMPTY)
			{
				_throwScriptError("function returned empty value!");
				return;
			}
		}

		// Process return values
		if(typeString == LIST_KEYWORD)
		{
			variableList.insert(make_pair(nameString, ScriptVariable(_fe3d, scope, ScriptVariableType::MULTIPLE, nameString, isConstant, returnValues)));
		}
		else if(returnValues.empty())
		{
			_throwScriptError("function returned no values!");
			return;
		}
		else if(returnValues.size() > 1)
		{
			_throwScriptError("function returned too many values!");
			return;
		}
		else if(returnValues[0].getType() == ScriptValueType::EMPTY)
		{
			_throwScriptError("function must return value!");
			return;
		}
		else if((typeString == STRING_KEYWORD) && (returnValues[0].getType() == ScriptValueType::STRING))
		{
			variableList.insert(make_pair(nameString, ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, returnValues)));
		}
		else if((typeString == DECIMAL_KEYWORD) && (returnValues[0].getType() == ScriptValueType::DECIMAL))
		{
			variableList.insert(make_pair(nameString, ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, returnValues)));
		}
		else if((typeString == INTEGER_KEYWORD) && (returnValues[0].getType() == ScriptValueType::INTEGER))
		{
			variableList.insert(make_pair(nameString, ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, returnValues)));
		}
		else if((typeString == BOOLEAN_KEYWORD) && (returnValues[0].getType() == ScriptValueType::BOOLEAN))
		{
			variableList.insert(make_pair(nameString, ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, returnValues)));
		}
		else
		{
			_throwScriptError("function returned incorrect value type!");
			return;
		}
	}
	else
	{
		// Prepare list access
		bool isAccessingList = false;
		auto listIndex = _extractListIndexFromString(valueString, isAccessingList);

		// Check if any error was thrown
		if(_hasThrownError)
		{
			return;
		}

		// Remove list accessing characters
		if(isAccessingList)
		{
			auto isOpeningBracketFound = find(valueString.begin(), valueString.end(), '[');
			auto bracketIndex = static_cast<unsigned int>(distance(valueString.begin(), isOpeningBracketFound));
			valueString = valueString.substr(0, bracketIndex);
		}

		// Check if right variable is not existing
		if(!_isLocalVariableExisting(valueString) && !_isGlobalVariableExisting(valueString))
		{
			_throwScriptError("variable \"" + valueString + "\" not existing!");
			return;
		}

		// Retrieve right variable
		const auto& rightVariable = (_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) : _getGlobalVariable(valueString));

		// Validate list access
		unsigned int valueIndex = 0;
		if(isAccessingList)
		{
			// Check if list index is invalid
			if(!_validateListIndex(rightVariable, listIndex))
			{
				return;
			}

			// Copy list index
			valueIndex = listIndex;
		}

		// Determine right variable type
		if((typeString == LIST_KEYWORD) && (rightVariable.getType() == ScriptVariableType::MULTIPLE))
		{
			// Extract values
			vector<ScriptValue> values = {};
			for(unsigned int i = 0; i < rightVariable.getValueCount(); i++)
			{
				values.push_back(rightVariable.getValue(i));
			}

			// Add variable
			variableList.insert(make_pair(nameString, ScriptVariable(_fe3d, scope, ScriptVariableType::MULTIPLE, nameString, isConstant, values)));
		}
		else if((typeString == STRING_KEYWORD) && (rightVariable.getValue(valueIndex).getType() == ScriptValueType::STRING))
		{
			// Compose values
			auto values = {rightVariable.getValue(valueIndex)};

			// Add variable
			variableList.insert(make_pair(nameString, ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, values)));
		}
		else if((typeString == DECIMAL_KEYWORD) && (rightVariable.getValue(valueIndex).getType() == ScriptValueType::DECIMAL))
		{
			// Compose values
			auto values = {rightVariable.getValue(valueIndex)};

			// Add variable
			variableList.insert(make_pair(nameString, ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, values)));
		}
		else if((typeString == INTEGER_KEYWORD) && (rightVariable.getValue(valueIndex).getType() == ScriptValueType::INTEGER))
		{
			// Compose values
			auto values = {rightVariable.getValue(valueIndex)};

			// Add variable
			variableList.insert(make_pair(nameString, ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, values)));
		}
		else if((typeString == BOOLEAN_KEYWORD) && (rightVariable.getValue(valueIndex).getType() == ScriptValueType::BOOLEAN))
		{
			// Compose values
			auto values = {rightVariable.getValue(valueIndex)};

			// Add variable
			variableList.insert(make_pair(nameString, ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, values)));
		}
		else
		{
			_throwScriptError("value types not matching!");
			return;
		}
	}
}