#include "script_interpreter.hpp"
#include "logger.hpp"

void ScriptInterpreter::_processVariableCreation(const string& scriptLine, ScriptVariableScope scope)
{
	// Temporary values
	string typeString = "";
	string nameString = "";
	string equalSignString = "";
	string valueString = "";
	bool isConstant = false;

	// Extract optional CONST keyword
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
	typeString = words[0];
	nameString = words[1];
	equalSignString = words[2];

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
		!isdigit(nameString.front()) &&
		(isalnum(nameString.front()) || nameString.front() == '_');

	// Forbidden variable names
	for(const auto& word : {META_KEYWORD, EXECUTE_KEYWORD, LOOP_KEYWORD, CONTINUE_KEYWORD, BREAK_KEYWORD, IF_KEYWORD, ELIF_KEYWORD, ELSE_KEYWORD, GLOBAL_KEYWORD,
		CONST_KEYWORD, EDIT_KEYWORD, LIST_KEYWORD, STRING_KEYWORD, DECIMAL_KEYWORD, INTEGER_KEYWORD, BOOLEAN_KEYWORD, IS_KEYWORD,
		NOT_KEYWORD, AND_KEYWORD, OR_KEYWORD, MORE_KEYWORD, LESS_KEYWORD, ADDITION_KEYWORD, SUBTRACTION_KEYWORD, MULTIPLICATION_KEYWORD,
		DIVISION_KEYWORD, NEGATION_KEYWORD, CASTING_KEYWORD, PUSHING_KEYWORD, PULLING_KEYWORD, PASS_KEYWORD})
	{
		isValidName = isValidName && (nameString != word);
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
	if(scope == ScriptVariableScope::GLOBAL && nameString.front() != '_')
	{
		_throwScriptError("global variables must start with an underscore!");
		return;
	}

	// Check if local variable does not start with '_'
	if(scope == ScriptVariableScope::LOCAL && nameString.front() == '_')
	{
		_throwScriptError("local variables cannot start with an underscore!");
		return;
	}

	// Check if variable name is valid
	if(!isValidName)
	{
		_throwScriptError("forbidden variable name!");
		return;
	}

	// Retrieve the repsective list of variables
	auto& variableList = (scope == ScriptVariableScope::LOCAL) ? _localVariables[_executionDepth] : _globalVariables;

	// Check if variable has been defined already
	if((scope == ScriptVariableScope::LOCAL && _isLocalVariableExisting(nameString)) ||
	   (scope == ScriptVariableScope::GLOBAL && _isGlobalVariableExisting(nameString)))
	{
		_throwScriptError("variable already defined!");
		return;
	}

	// Check if equal sign is present
	if(equalSignString != "=")
	{
		_throwScriptError("equal sign missing!");
		return;
	}

	// Check if value is present
	if(scriptLine.size() - 1 >= scriptLine.find('=') + 2)
	{
		// Extract remaining text (value)
		valueString = scriptLine.substr(scriptLine.find('=') + 2);
	}
	else
	{
		_throwScriptError("value missing!");
		return;
	}

	// Check if value is of the right type
	if(typeString == LIST_KEYWORD && _isListValue(valueString)) // LIST
	{
		// Removing the "" around the string content
		string listString = valueString.substr(1);
		listString.pop_back();

		// Extract the values
		auto values = _extractValuesFromListString(listString);
		variableList.insert(make_pair(nameString,
							ScriptVariable(_fe3d, scope, ScriptVariableType::MULTIPLE, nameString, isConstant, values)));
	}
	else if(typeString == STRING_KEYWORD && _isStringValue(valueString)) // STRING
	{
		// Removing the "" around the string content
		valueString.erase(valueString.begin());
		valueString.pop_back();

		// Add new string variable
		auto value = ScriptValue(_fe3d, ScriptValueType::STRING, valueString);
		variableList.insert(make_pair(nameString,
							ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, {value})));
	}
	else if(typeString == DECIMAL_KEYWORD && _isDecimalValue(valueString)) // DECIMAL
	{
		auto value = ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(_limitDecimalString(valueString)));
		variableList.insert(make_pair(nameString,
							ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, {value})));
	}
	else if(typeString == INTEGER_KEYWORD && _isIntegerValue(valueString)) // INTEGER
	{
		auto value = ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(_limitIntegerString(valueString)));
		variableList.insert(make_pair(nameString,
							ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, {value})));
	}
	else if(typeString == BOOLEAN_KEYWORD && _isBooleanValue(valueString)) // BOOLEAN - normal
	{
		auto value = ScriptValue(_fe3d, ScriptValueType::BOOLEAN, (valueString == "<true>"));
		variableList.insert(make_pair(nameString,
							ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, {value})));
	}
	else if(typeString == BOOLEAN_KEYWORD && (valueString.front() == '(' && valueString.back() == ')')) // BOOLEAN - condition
	{
		// Removing the ( ) around the string content
		valueString.erase(valueString.begin());
		valueString.pop_back();

		// Add new boolean variable
		auto value = ScriptValue(_fe3d, ScriptValueType::BOOLEAN, _checkConditionString(valueString));
		variableList.insert(make_pair(nameString,
							ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, {value})));
	}
	else if(valueString.substr(0, 5) == "fe3d:" || valueString.substr(0, 5) == "math:" || valueString.substr(0, 5) == "misc:")
	{
		// Save current logger message count
		auto loggerMessageCount = Logger::getMessageCount();

		// Call function
		auto values =
			(valueString.substr(0, 5) == "fe3d:") ? _processEngineFunctionCall(valueString) :
			(valueString.substr(0, 5) == "math:") ? _processMathematicalFunctionCall(valueString) :
			_processMiscellaneousFunctionCall(valueString);

		// Check if any error was thrown
		_checkEngineWarnings(loggerMessageCount);
		if(_hasThrownError)
		{
			return;
		}

		// Temporary values
		bool isStringValue = ((typeString == STRING_KEYWORD) && (values[0].getType() == ScriptValueType::STRING));
		bool isDecimalValue = ((typeString == DECIMAL_KEYWORD) && (values[0].getType() == ScriptValueType::DECIMAL));
		bool isIntegerValue = ((typeString == INTEGER_KEYWORD) && (values[0].getType() == ScriptValueType::INTEGER));
		bool isBooleanValue = ((typeString == BOOLEAN_KEYWORD) && (values[0].getType() == ScriptValueType::BOOLEAN));

		if(typeString == LIST_KEYWORD) // Variable is a list
		{
			// Check if function returned any empty values
			for(const auto& value : values)
			{
				if(value.getType() == ScriptValueType::EMPTY)
				{
					_throwScriptError("function cannot return empty values!");
					return;
				}
			}

			// Add list values
			variableList.insert(make_pair(nameString, ScriptVariable(_fe3d, scope, ScriptVariableType::MULTIPLE, nameString, isConstant, values)));
		}
		else if(values.empty()) // Function returned no values
		{
			_throwScriptError("function did not return any values!");
			return;
		}
		else if(values.size() > 1) // Function returned too many values
		{
			_throwScriptError("function returned too many values!");
			return;
		}
		else if(values[0].getType() == ScriptValueType::EMPTY) // Function returned an empty value
		{
			_throwScriptError("function must return a value!");
			return;
		}
		else if(isStringValue || isDecimalValue || isIntegerValue || isBooleanValue)
		{
			variableList.insert(make_pair(nameString, ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, values)));
		}
		else
		{
			_throwScriptError("function value type does not match the variable type!");
			return;
		}
	}
	else
	{
		// Temporary values
		unsigned int valueIndex = 0;

		// Check if accessing individual value from list variable
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
			auto openingBracketFound = find(valueString.begin(), valueString.end(), '[');
			auto bracketIndex = static_cast<unsigned int>(distance(valueString.begin(), openingBracketFound));
			valueString = valueString.substr(0, bracketIndex);
		}

		// Check if using another variable as value
		if(!_isLocalVariableExisting(valueString) && !_isGlobalVariableExisting(valueString))
		{
			_throwScriptError("invalid value!");
			return;
		}

		// Retrieve other variable
		auto otherVariable = (_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) : _getGlobalVariable(valueString));

		// Validate list access
		if(isAccessingList)
		{
			// Check if list index is valid
			if(_validateListIndex(otherVariable, listIndex))
			{
				valueIndex = listIndex;
			}
			else // Error
			{
				return;
			}
		}

		// Temporary values
		bool isSingleVariable = (otherVariable.getType() == ScriptVariableType::SINGLE || isAccessingList);
		bool isStringVariable = ((typeString == STRING_KEYWORD) && (otherVariable.getValue(valueIndex).getType() == ScriptValueType::STRING));
		bool isDecimalVariable = ((typeString == DECIMAL_KEYWORD) && (otherVariable.getValue(valueIndex).getType() == ScriptValueType::DECIMAL));
		bool isIntegerVariable = ((typeString == INTEGER_KEYWORD) && (otherVariable.getValue(valueIndex).getType() == ScriptValueType::INTEGER));
		bool isBooleanVariable = ((typeString == BOOLEAN_KEYWORD) && (otherVariable.getValue(valueIndex).getType() == ScriptValueType::BOOLEAN));

		// Check if the value types match
		if(isSingleVariable && isStringVariable && isDecimalVariable && isIntegerVariable && isBooleanVariable)
		{
			variableList.insert(make_pair(nameString,
								ScriptVariable(_fe3d, scope, ScriptVariableType::SINGLE, nameString, isConstant, {otherVariable.getValue(valueIndex)})));
		}
		else
		{
			_throwScriptError("variable value types don't match!");
			return;
		}
	}
}