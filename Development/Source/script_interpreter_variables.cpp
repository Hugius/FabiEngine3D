#include "script_interpreter.hpp"

void ScriptInterpreter::_processVariableDefinition(const string& scriptLine, ScriptVariableScope scope, bool editExisting)
{
	// Temporary values
	std::istringstream iss(scriptLine);
	string variableType = "";
	string variableID = "";
	string equalSign = "";
	string variableValue = "";
	bool isConstant = false;

	if (editExisting) // Editing existing variable value
	{
		// Extract text values
		string keyword;
		iss >> keyword >> variableID >> equalSign >> variableValue;

		// Check if variable exists
		if(!_isLocalVariableExisting(variableID) && !_isGlobalVariableExisting(variableID))
		{
			_throwScriptError("variable \"" + variableID + "\" not found!");
			return;
		}

		// Retrieve variable
		auto& variable = _isLocalVariableExisting(variableID) ? _getLocalVariable(variableID) : _getGlobalVariable(variableID);

		// A constant variable should not be changed
		if (variable.isConstant())
		{
			_throwScriptError("variable \"" + variableID + "\" cannot be changed, it is constant!");
			return;
		}

		// Check if equal sign is valid
		if (equalSign == "=")
		{
			if ((variable.getValue().getType() == ScriptValueType::STRING) && _isStringValue(variableValue)) // String
			{
				variableValue.erase(variableValue.begin());
				variableValue.pop_back();
				variable.getValue().setString(variableValue);
			}
			else if ((variable.getValue().getType() == ScriptValueType::DECIMAL) && _isDecimalValue(variableValue)) // Decimal
			{
				variable.getValue().setDecimal(stof(variableValue));
			}
			else if ((variable.getValue().getType() == ScriptValueType::INTEGER) && _isIntegerValue(variableValue)) // Integer
			{
				variable.getValue().setInteger(stoi(variableValue));
			}
			else if ((variable.getValue().getType() == ScriptValueType::BOOLEAN) && _isBooleanValue(variableValue)) // Boolean
			{
				variable.getValue().setBoolean(variableValue == "<true>");
			}
			else if (variableValue.substr(0, 5) == "fe3d:") // FE3D function result
			{
				auto value = _processEngineFunctionCall(variableValue).back();

				// Check if returned value is of the right type
				if ((variableType == _stringKeyword) && (value.getType() == ScriptValueType::STRING))
				{
					variable.getValue().setString(variableValue);
				}
				else if ((variableType == _decimalKeyword) && (value.getType() == ScriptValueType::DECIMAL))
				{
					variable.getValue().setDecimal(stof(variableValue));
				}
				else if ((variableType == _integerKeyword) && (value.getType() == ScriptValueType::INTEGER))
				{
					variable.getValue().setInteger(stoi(variableValue));
				}
				else if ((variableType == _booleanKeyword) && (value.getType() == ScriptValueType::BOOLEAN))
				{
					variable.getValue().setBoolean(variableValue == "<true>");
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
			iss >> variableType >> variableID >> equalSign >> variableValue;
		}
		else
		{
			variableType = possibleConstKeyword;
			iss >> variableID >> equalSign >> variableValue;
		}


		// Check if variable type is valid
		if (variableType == _stringKeyword || variableType == _decimalKeyword || variableType == _integerKeyword || variableType == _booleanKeyword)
		{
			// Validate variable name
			bool validName = !variableID.empty() && variableID.substr(0, 5) != "fe3d:" && !isdigit(variableID.front() && isalnum(variableID.front())) &&
				variableID != "<true>" && variableID != "<false>";

			// Forbidden variable names
			for (auto& word : { _metaKeyword, _executeKeyword, _ifKeyword, _elseifKeyword, _elseKeyword, _globalKeyword,
				_constKeyword, _stringKeyword, _decimalKeyword, _integerKeyword, _booleanKeyword, _isKeyword,
				_notKeyword, _andKeyword, _orKeyword, _moreKeyword, _lessKeyword })
			{
				validName = validName && (variableID != word);
			}

			// Check if variable name is valid
			if (validName)
			{
				// Retrieve the repsective list of variables
				auto& variableList = (scope == ScriptVariableScope::LOCAL) ? _localVariablesStack.back() : _globalVariables;

				// Check if a local variable has already been defined
				if (scope == ScriptVariableScope::LOCAL)
				{
					if (_isLocalVariableExisting(variableID))
					{
						_throwScriptError("local variable \"" + variableID + "\" already defined!");
						return;
					}
				}
				else // Global variable
				{
					if (_isGlobalVariableExisting(variableID))
					{
						_throwScriptError("global variable \"" + variableID + "\" already defined!");
						return;
					}
				}

				// Check if equal sign is valid
				if (equalSign == "=")
				{
					// Check if value is not empty
					if (variableValue.empty())
					{
						_throwScriptError("no variable type found!");
					}
					else
					{
						// Check if value is of the right type
						if (variableType == _stringKeyword && _isStringValue(variableValue)) // String
						{
							// Removing the "" around the string content
							variableValue.erase(variableValue.begin());
							variableValue.pop_back();

							// Add new string variable
							auto value = ScriptValue(_fe3d, ScriptValueType::STRING, variableValue);
							variableList.push_back(ScriptVariable(_fe3d, scope, variableID, isConstant, value));
						}
						else if (variableType == _decimalKeyword && _isDecimalValue(variableValue)) // Decimal
						{
							auto value = ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(variableValue));
							variableList.push_back(ScriptVariable(_fe3d, scope, variableID, isConstant, value));
						}
						else if (variableType == _integerKeyword && _isIntegerValue(variableValue)) // Integer
						{
							auto value = ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(variableValue));
							variableList.push_back(ScriptVariable(_fe3d, scope, variableID, isConstant, value));
						}
						else if (variableType == _booleanKeyword && _isBooleanValue(variableValue)) // Boolean
						{
							auto value = ScriptValue(_fe3d, ScriptValueType::BOOLEAN, (variableValue == "<true>"));
							variableList.push_back(ScriptVariable(_fe3d, scope, variableID, isConstant, value));
						}
						else if (variableValue.substr(0, 5) == "fe3d:") // FE3D function result
						{
							auto value = _processEngineFunctionCall(variableValue).back();

							// Check if returned value is of the right type
							if (((variableType == _stringKeyword)  && (value.getType() == ScriptValueType::STRING)) ||
								((variableType == _decimalKeyword) && (value.getType() == ScriptValueType::DECIMAL)) ||
								((variableType == _integerKeyword) && (value.getType() == ScriptValueType::INTEGER)) ||
								((variableType == _booleanKeyword) && (value.getType() == ScriptValueType::BOOLEAN)))
							{
								variableList.push_back(ScriptVariable(_fe3d, scope, variableID, isConstant, value));
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