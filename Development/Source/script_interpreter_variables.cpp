#include "script_interpreter.hpp"

void ScriptInterpreter::_processVariableDefinition(const string& scriptLine, ScriptVariableScope scope, bool editExisting)
{
	// Temporary values
	std::istringstream iss(scriptLine);
	string typeString = "";
	string nameString = "";
	string equalSignString = "";
	string valueString = "";
	bool isConstant = false;

	if (editExisting) // Editing existing variable value
	{
		// Extract text values
		string keyword;
		iss >> keyword >> nameString >> equalSignString >> valueString;

		// Check if variable exists
		if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
		{
			_throwScriptError("variable \"" + nameString + "\" not found!");
			return;
		}

		// Retrieve variable
		auto& variable = _isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString);

		// A constant variable should not be changed
		if (variable.isConstant())
		{
			_throwScriptError("variable \"" + nameString + "\" cannot be changed, it is constant!");
			return;
		}

		// Check if equal sign is valid
		if (equalSignString == "=")
		{
			if ((variable.getValue().getType() == ScriptValueType::STRING) && _isStringValue(valueString)) // String
			{
				valueString.erase(valueString.begin());
				valueString.pop_back();
				variable.getValue().setString(valueString);
			}
			else if ((variable.getValue().getType() == ScriptValueType::DECIMAL) && _isDecimalValue(valueString)) // Decimal
			{
				variable.getValue().setDecimal(stof(valueString));
			}
			else if ((variable.getValue().getType() == ScriptValueType::INTEGER) && _isIntegerValue(valueString)) // Integer
			{
				variable.getValue().setInteger(stoi(valueString));
			}
			else if ((variable.getValue().getType() == ScriptValueType::BOOLEAN) && _isBooleanValue(valueString)) // Boolean
			{
				variable.getValue().setBoolean(valueString == "<true>");
			}
			else if (valueString.substr(0, 5) == "fe3d:") // FE3D function result
			{
				auto value = _processEngineFunctionCall(valueString).back();

				// Check if returned value is of the right type
				if ((typeString == _stringKeyword) && (value.getType() == ScriptValueType::STRING))
				{
					variable.getValue().setString(valueString);
				}
				else if ((typeString == _decimalKeyword) && (value.getType() == ScriptValueType::DECIMAL))
				{
					variable.getValue().setDecimal(stof(valueString));
				}
				else if ((typeString == _integerKeyword) && (value.getType() == ScriptValueType::INTEGER))
				{
					variable.getValue().setInteger(stoi(valueString));
				}
				else if ((typeString == _booleanKeyword) && (value.getType() == ScriptValueType::BOOLEAN))
				{
					variable.getValue().setBoolean(valueString == "<true>");
				}
				else
				{
					_throwScriptError("invalid variable value!");
				}
			}
			else if (_isLocalVariableExisting(valueString))
			{
				// Validate variable type
				if (variable.getValue().getType() == _getLocalVariable(valueString).getValue().getType())
				{
					variable.changeValue(_getLocalVariable(valueString).getValue());
				}
				else
				{
					_throwScriptError("invalid variable value!");
				}
			}
			else if (_isGlobalVariableExisting(valueString))
			{
				// Validate variable type
				if (variable.getValue().getType() == _getGlobalVariable(valueString).getValue().getType())
				{
					variable.changeValue(_getGlobalVariable(valueString).getValue());
				}
				else
				{
					_throwScriptError("invalid variable value!");
				}
			}
			else
			{
				_throwScriptError("invalid variable value!");
			}
		}
		else
		{
			_throwScriptError("invalid variable syntax!");
		}
	}
	else // Creating fresh new variable
	{
		// Extract GLOB keyword
		if (scope == ScriptVariableScope::GLOBAL)
		{
			string keyword;
			iss >> keyword;
		}

		// Extract CONST keyword
		string possibleConstKeyword;
		iss >> possibleConstKeyword;
		isConstant = (possibleConstKeyword == "CONST");

		// Extract other variable data
		if (isConstant)
		{
			iss >> typeString >> nameString >> equalSignString >> valueString;
		}
		else
		{
			typeString = possibleConstKeyword;
			iss >> nameString >> equalSignString >> valueString;
		}


		// Check if variable type is valid
		if (typeString == _stringKeyword || typeString == _decimalKeyword || typeString == _integerKeyword || typeString == _booleanKeyword)
		{
			// Validate variable name
			bool validName = !nameString.empty() && nameString.substr(0, 5) != "fe3d:" && !isdigit(nameString.front() && isalnum(nameString.front())) &&
				nameString != "<true>" && nameString != "<false>";

			// Forbidden variable names
			for (auto& word : { _metaKeyword, _executeKeyword, _ifKeyword, _elifKeyword, _elseKeyword, _globalKeyword,
				_constKeyword, _stringKeyword, _decimalKeyword, _integerKeyword, _booleanKeyword, _isKeyword,
				_notKeyword, _andKeyword, _orKeyword, _moreKeyword, _lessKeyword })
			{
				validName = validName && (nameString != word);
			}

			// Check if variable name is valid
			if (validName)
			{
				// Retrieve the repsective list of variables
				auto& variableList = (scope == ScriptVariableScope::LOCAL) ? _localVariablesStack.back() : _globalVariables;

				// Check if a local variable has already been defined
				if (scope == ScriptVariableScope::LOCAL)
				{
					if (_isLocalVariableExisting(nameString))
					{
						_throwScriptError("local variable \"" + nameString + "\" already defined!");
						return;
					}
				}
				else // Global variable
				{
					if (_isGlobalVariableExisting(nameString))
					{
						_throwScriptError("global variable \"" + nameString + "\" already defined!");
						return;
					}
				}

				// Check if equal sign is valid
				if (equalSignString == "=")
				{
					// Check if value is not empty
					if (valueString.empty())
					{
						_throwScriptError("no variable type found!");
					}
					else
					{
						// Check if value is of the right type
						if (typeString == _stringKeyword && _isStringValue(valueString)) // String
						{
							// Removing the "" around the string content
							valueString.erase(valueString.begin());
							valueString.pop_back();

							// Add new string variable
							auto value = ScriptValue(_fe3d, ScriptValueType::STRING, valueString);
							variableList.push_back(ScriptVariable(_fe3d, scope, nameString, isConstant, value));
						}
						else if (typeString == _decimalKeyword && _isDecimalValue(valueString)) // Decimal
						{
							auto value = ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(valueString));
							variableList.push_back(ScriptVariable(_fe3d, scope, nameString, isConstant, value));
						}
						else if (typeString == _integerKeyword && _isIntegerValue(valueString)) // Integer
						{
							auto value = ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(valueString));
							variableList.push_back(ScriptVariable(_fe3d, scope, nameString, isConstant, value));
						}
						else if (typeString == _booleanKeyword && _isBooleanValue(valueString)) // Boolean
						{
							auto value = ScriptValue(_fe3d, ScriptValueType::BOOLEAN, (valueString == "<true>"));
							variableList.push_back(ScriptVariable(_fe3d, scope, nameString, isConstant, value));
						}
						else if (valueString.substr(0, 5) == "fe3d:") // FE3D function result
						{
							auto value = _processEngineFunctionCall(valueString).back();

							// Check if returned value is of the right type
							if (((typeString == _stringKeyword)  && (value.getType() == ScriptValueType::STRING)) ||
								((typeString == _decimalKeyword) && (value.getType() == ScriptValueType::DECIMAL)) ||
								((typeString == _integerKeyword) && (value.getType() == ScriptValueType::INTEGER)) ||
								((typeString == _booleanKeyword) && (value.getType() == ScriptValueType::BOOLEAN)))
							{
								variableList.push_back(ScriptVariable(_fe3d, scope, nameString, isConstant, value));
							}
							else
							{
								_throwScriptError("invalid variable value!");
							}
						}
						else if (_isLocalVariableExisting(valueString) || _isGlobalVariableExisting(valueString))
						{
							auto otherVariable = _isLocalVariableExisting(valueString) ? 
								_getLocalVariable(valueString) : _getGlobalVariable(valueString);

							// Check if returned value is of the right type
							if (((typeString == _stringKeyword)  && (otherVariable.getValue().getType() == ScriptValueType::STRING)) ||
								((typeString == _decimalKeyword) && (otherVariable.getValue().getType() == ScriptValueType::DECIMAL)) ||
								((typeString == _integerKeyword) && (otherVariable.getValue().getType() == ScriptValueType::INTEGER)) ||
								((typeString == _booleanKeyword) && (otherVariable.getValue().getType() == ScriptValueType::BOOLEAN)))
							{
								variableList.push_back(ScriptVariable(_fe3d, scope, nameString, isConstant, otherVariable.getValue()));
							}
							else
							{
								_throwScriptError("invalid variable value!");
							}
						}
						else
						{
							_throwScriptError("invalid variable value!");
						}
					}
				}
				else
				{
					_throwScriptError("invalid variable syntax!");
				}
			}
			else
			{
				_throwScriptError("invalid variable name!");
			}
		}
		else
		{
			_throwScriptError("invalid variable type!");
		}
	}

	// No characters allowed after variable creation or alteration statement
	string temp;
	if ((iss >> temp) || scriptLine.back() == ' ')
	{
		_throwScriptError("invalid variable creation syntax!");
	}
}

bool ScriptInterpreter::_isLocalVariableExisting(const string& variableID)
{
	for (auto& variable : _localVariablesStack.back())
	{
		if (variableID == variable.getID())
		{
			return true;
		}
	}

	return false;
}

bool ScriptInterpreter::_isGlobalVariableExisting(const string& variableID)
{
	for (auto& variable : _globalVariables)
	{
		if (variableID == variable.getID())
		{
			return true;
		}
	}

	return false;
}

ScriptVariable& ScriptInterpreter::_getLocalVariable(const string& variableID)
{
	for (auto& variable : _localVariablesStack.back())
	{
		if (variableID == variable.getID())
		{
			return variable;
		}
	}

	_fe3d.logger_throwError("Local script variable \"" + variableID + "\" not found!");
}

ScriptVariable& ScriptInterpreter::_getGlobalVariable(const string& variableID)
{
	for (auto& variable : _globalVariables)
	{
		if (variableID == variable.getID())
		{
			return variable;
		}
	}

	_fe3d.logger_throwError("Global script variable \"" + variableID + "\" not found!");
}