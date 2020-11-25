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
		// Extract text parts
		string keyword;
		iss >> keyword >> nameString >> equalSignString;

		// Extract remaining text (value)
		if (equalSignString == "=")
		{
			valueString = scriptLine.substr(scriptLine.find('=') + 2);
		}

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
			if ((variable.getValue().getType() == ScriptValueType::STRING) && _isStringValue(valueString)) // STRING
			{
				valueString.erase(valueString.begin());
				valueString.pop_back();
				variable.getValue().setString(valueString);
			}
			else if ((variable.getValue().getType() == ScriptValueType::DECIMAL) && _isDecimalValue(valueString)) // DECIMAL
			{
				variable.getValue().setDecimal(stof(valueString));
			}
			else if ((variable.getValue().getType() == ScriptValueType::INTEGER) && _isIntegerValue(valueString)) // INTEGER
			{
				variable.getValue().setInteger(stoi(valueString));
			}
			else if ((variable.getValue().getType() == ScriptValueType::BOOLEAN) && _isBooleanValue(valueString)) // BOOLEAN
			{
				variable.getValue().setBoolean(valueString == "<true>");
			}
			else if // FUNCTION
				(
					valueString.substr(0, 5) == "fe3d:" ||
					valueString.substr(0, 5) == "math:" ||
					valueString.substr(0, 5) == "misc:"
				)
			{
				// Call function
				auto values =
					(valueString.substr(0, 5) == "fe3d:") ? _processEngineFunctionCall(valueString) :
					(valueString.substr(0, 5) == "math:") ? _processMathematicalFunctionCall(valueString) :
					_processMiscellaneousFunctionCall(valueString);

				// Check if function call went well
				if (!_hasThrownError)
				{
					// Check if returned value is of the right type
					if ((variable.getValue().getType() == ScriptValueType::STRING) && (values[0].getType() == ScriptValueType::STRING))
					{
						variable.getValue().setString(values[0].getString());
					}
					else if ((variable.getValue().getType() == ScriptValueType::DECIMAL) && (values[0].getType() == ScriptValueType::DECIMAL))
					{
						variable.getValue().setDecimal(values[0].getDecimal());
					}
					else if ((variable.getValue().getType() == ScriptValueType::INTEGER) && (values[0].getType() == ScriptValueType::INTEGER))
					{
						variable.getValue().setInteger(values[0].getInteger());
					}
					else if ((variable.getValue().getType() == ScriptValueType::BOOLEAN) && (values[0].getType() == ScriptValueType::BOOLEAN))
					{
						variable.getValue().setBoolean(values[0].getBoolean());
					}
					else if (values[0].getType() == ScriptValueType::EMPTY)
					{
						_throwScriptError("function must return a value!");
					}
					else
					{
						_throwScriptError("function value type does not match the variable type!");
					}
				}
			}
			else if (_isLocalVariableExisting(valueString))
			{
				// Validate variable type
				if (variable.getValue().getType() == _getLocalVariable(valueString).getValue().getType())
				{
					// Change the value
					variable.getValue().setString(_getLocalVariable(valueString).getValue().getString());
					variable.getValue().setDecimal(_getLocalVariable(valueString).getValue().getDecimal());
					variable.getValue().setInteger(_getLocalVariable(valueString).getValue().getInteger());
					variable.getValue().setBoolean(_getLocalVariable(valueString).getValue().getBoolean());
				}
				else
				{
					_throwScriptError("variable values do not match!");
				}
			}
			else if (_isGlobalVariableExisting(valueString))
			{
				// Validate variable type
				if (variable.getValue().getType() == _getGlobalVariable(valueString).getValue().getType())
				{
					// Change the value
					variable.getValue().setString(_getGlobalVariable(valueString).getValue().getString());
					variable.getValue().setDecimal(_getGlobalVariable(valueString).getValue().getDecimal());
					variable.getValue().setInteger(_getGlobalVariable(valueString).getValue().getInteger());
					variable.getValue().setBoolean(_getGlobalVariable(valueString).getValue().getBoolean());
				}
				else
				{
					_throwScriptError("variable values do not match!");
				}
			}
			else
			{
				_throwScriptError("invalid value!");
			}
		}
		else
		{
			_throwScriptError("invalid syntax!");
		}
	}
	else // Creating a fresh new variable
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
			iss >> typeString >> nameString >> equalSignString;
		}
		else
		{
			typeString = possibleConstKeyword;
			iss >> nameString >> equalSignString;
		}

		// Extract remaining text (value)
		if (equalSignString == "=")
		{
			valueString = scriptLine.substr(scriptLine.find('=') + 2);
		}

		// Check if variable type is valid
		if (typeString == _stringKeyword || typeString == _decimalKeyword || typeString == _integerKeyword || typeString == _booleanKeyword)
		{
			// Validate variable name
			bool validName = !nameString.empty() && nameString.substr(0, 5) != "fe3d:" && nameString.substr(0, 5) != "math:" &&
				nameString.substr(0, 5) != "misc:" && !isdigit(nameString.front() && isalnum(nameString.front())) &&
				nameString != "<true>" && nameString != "<false>";

			// Forbidden variable names
			for (auto& word : { _metaKeyword, _executeKeyword, _ifKeyword, _elifKeyword, _elseKeyword, _globalKeyword,
				_constKeyword, _editKeyword, _stringKeyword, _decimalKeyword, _integerKeyword, _booleanKeyword, _isKeyword,
				_notKeyword, _andKeyword, _orKeyword, _moreKeyword, _lessKeyword, _plusKeyword, _minusKeyword, _multiplyKeyword, _divideKeyword })
			{
				validName = validName && (nameString != word);
			}

			// Validate variable individual characters
			for (auto& c : nameString)
			{
				// Only non-alphanumeric characters '_' and '-' allowed
				if (c != '_' && c != '-' && !isalnum(c))
				{
					validName = false;
				}
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
						_throwScriptError("no variable value found!");
					}
					else
					{
						// Check if value is of the right type
						if (typeString == _stringKeyword && _isStringValue(valueString)) // STRING
						{
							// Removing the "" around the string content
							valueString.erase(valueString.begin());
							valueString.pop_back();

							// Add new string variable
							auto value = ScriptValue(_fe3d, ScriptValueType::STRING, valueString);
							variableList.push_back(ScriptVariable(_fe3d, scope, nameString, isConstant, value));
						}
						else if (typeString == _decimalKeyword && _isDecimalValue(valueString)) // DECIMAL
						{
							auto value = ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(valueString));
							variableList.push_back(ScriptVariable(_fe3d, scope, nameString, isConstant, value));
						}
						else if (typeString == _integerKeyword && _isIntegerValue(valueString)) // INTEGER
						{
							auto value = ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(valueString));
							variableList.push_back(ScriptVariable(_fe3d, scope, nameString, isConstant, value));
						}
						else if (typeString == _booleanKeyword && _isBooleanValue(valueString)) // BOOLEAN
						{
							auto value = ScriptValue(_fe3d, ScriptValueType::BOOLEAN, (valueString == "<true>"));
							variableList.push_back(ScriptVariable(_fe3d, scope, nameString, isConstant, value));
						}
						else if // FUNCTION
							(
								valueString.substr(0, 5) == "fe3d:" || 
								valueString.substr(0, 5) == "math:" || 
								valueString.substr(0, 5) == "misc:"
							)
						{
							// Call function
							auto values =
								(valueString.substr(0, 5) == "fe3d:") ? _processEngineFunctionCall(valueString) :
								(valueString.substr(0, 5) == "math:") ? _processMathematicalFunctionCall(valueString) :
								_processMiscellaneousFunctionCall(valueString);

							// Check if function call went well
							if (!_hasThrownError)
							{
								// Check if returned value is of the right type
								if (((typeString == _stringKeyword)  && (values[0].getType() == ScriptValueType::STRING))  ||
									((typeString == _decimalKeyword) && (values[0].getType() == ScriptValueType::DECIMAL)) ||
									((typeString == _integerKeyword) && (values[0].getType() == ScriptValueType::INTEGER)) ||
									((typeString == _booleanKeyword) && (values[0].getType() == ScriptValueType::BOOLEAN)))
								{
									variableList.push_back(ScriptVariable(_fe3d, scope, nameString, isConstant, values[0]));
								}
								else if (values[0].getType() == ScriptValueType::EMPTY)
								{
									_throwScriptError("function must return a value!");
								}
								else
								{
									_throwScriptError("function value type does not match the variable type!");
								}
							}
						}
						else if (_isLocalVariableExisting(valueString) || _isGlobalVariableExisting(valueString)) // Variable
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
								_throwScriptError("invalid function value!");
							}
						}
						else
						{
							_throwScriptError("invalid value!");
						}
					}
				}
				else
				{
					_throwScriptError("invalid syntax!");
				}
			}
			else
			{
				_throwScriptError("forbidden variable name!");
			}
		}
		else
		{
			_throwScriptError("invalid variable type!");
		}
	}
}

void ScriptInterpreter::_processVariableArithmetic(const string& scriptLine)
{
	// Temporary values
	std::istringstream iss(scriptLine);
	string operatorString = "";
	string nameString = "";
	string valueString = "";

	// Extract data
	iss >> operatorString >> nameString >> valueString;

	// Check if valid arithmetic keyword
	if (operatorString != _plusKeyword && operatorString != _minusKeyword && operatorString != _multiplyKeyword && operatorString != _divideKeyword)
	{
		_throwScriptError("invalid arithmetic operator!");
		return;
	}

	// Check if variable exists
	if (!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("variable \"" + nameString + "\" not found!");
		return;
	}
	
	// Retrieve variable
	auto& variable = _isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString);

	// Check if variable is of the correct type
	if (!(variable.getValue().getType() == ScriptValueType::INTEGER) && !(variable.getValue().getType() == ScriptValueType::DECIMAL))
	{
		_throwScriptError("arithmetic is only allowed on integer or decimal variables!");
		return;
	}

	// Check if variable can be changed
	if (variable.isConstant())
	{
		_throwScriptError("variable \"" + nameString + "\" cannot be changed, it is constant!");
		return;
	}

	// Check if value is not empty
	if (valueString.empty())
	{
		_throwScriptError("no arithmetic value found!");
		return;
	}
	
	// Execute arithmetic operation
	if ((variable.getValue().getType() == ScriptValueType::INTEGER) && _isIntegerValue(valueString)) // Integer
	{
		// Create value
		auto value = ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(valueString));
		int result = variable.getValue().getInteger();

		// Determine arithmetic type
		if (operatorString == _plusKeyword)
		{
			result += value.getInteger();
		}
		else if (operatorString == _minusKeyword)
		{
			result -= value.getInteger();
		}
		else if (operatorString == _multiplyKeyword)
		{
			result *= value.getInteger();
		}
		else if (operatorString == _divideKeyword)
		{
			result /= value.getInteger();
		}

		// Set resulting value
		variable.getValue().setInteger(result);
	}
	else if ((variable.getValue().getType() == ScriptValueType::DECIMAL) && _isDecimalValue(valueString)) // Decimal
	{
		// Create value
		auto value = ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(valueString));
		float result = variable.getValue().getDecimal();

		// Determine arithmetic type
		if (operatorString == _plusKeyword)
		{
			result += value.getDecimal();
		}
		else if (operatorString == _minusKeyword)
		{
			result -= value.getDecimal();
		}
		else if (operatorString == _multiplyKeyword)
		{
			result *= value.getDecimal();
		}
		else if (operatorString == _divideKeyword)
		{
			result /= value.getDecimal();
		}

		// Set resulting value
		variable.getValue().setDecimal(result);
	}
	else
	{
		_throwScriptError("invalid arithmetic value!");
		return;
	}

	// No characters allowed after variable arithmetic
	string temp;
	if ((iss >> temp) || scriptLine.back() == ' ')
	{
		_throwScriptError("invalid syntax!");
		return;
	}
}

void ScriptInterpreter::_processVariableTypecast(const string& scriptLine)
{
	// Temporary values
	std::istringstream iss(scriptLine);
	string keyword = "";
	string nameString = "";
	string typeString = "";

	// Extract data
	iss >> keyword >> nameString >> typeString;

	// Check if variable exists
	if (!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("variable \"" + nameString + "\" not found!");
		return;
	}

	// Retrieve variable
	auto& variable = _isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString);

	// Check if variable can be changed
	if (variable.isConstant())
	{
		_throwScriptError("variable \"" + nameString + "\" cannot be typecasted, it is constant!");
		return;
	}

	// Check if type is not empty
	if (typeString.empty())
	{
		_throwScriptError("no new type found!");
		return;
	}

	// Determine to which new type the variable must cast
	if ((variable.getValue().getType() == ScriptValueType::INTEGER) && (typeString == _decimalKeyword)) // From integer to decimal
	{
		variable.changeValue(ScriptValue(_fe3d, ScriptValueType::DECIMAL, static_cast<float>(variable.getValue().getInteger())));
	}
	else if ((variable.getValue().getType() == ScriptValueType::DECIMAL) && (typeString == _integerKeyword)) // From decimal to integer
	{
		variable.changeValue(ScriptValue(_fe3d, ScriptValueType::INTEGER, static_cast<int>(variable.getValue().getDecimal())));
	}
	else if ((variable.getValue().getType() == ScriptValueType::BOOLEAN) && (typeString == _integerKeyword)) // From boolean to integer
	{
		variable.changeValue(ScriptValue(_fe3d, ScriptValueType::INTEGER, static_cast<int>(variable.getValue().getBoolean())));
	}
	else if ((variable.getValue().getType() == ScriptValueType::INTEGER) && (typeString == _stringKeyword)) // From integer to string
	{
		variable.changeValue(ScriptValue(_fe3d, ScriptValueType::STRING, to_string(variable.getValue().getInteger())));
	}
	else if ((variable.getValue().getType() == ScriptValueType::DECIMAL) && (typeString == _stringKeyword)) // From decimal to string
	{
		variable.changeValue(ScriptValue(_fe3d, ScriptValueType::STRING, to_string(variable.getValue().getDecimal())));
	}
	else
	{
		_throwScriptError("variable \"" + nameString + "\" cannot be typecasted, wrong type!");
		return;
	}

	// No characters allowed after variable arithmetic
	string temp;
	if ((iss >> temp) || scriptLine.back() == ' ')
	{
		_throwScriptError("invalid syntax!");
		return;
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