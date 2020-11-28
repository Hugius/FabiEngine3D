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
			if ((variable.getValue().getType() == ScriptValueType::VEC3) && _isVec3Value(valueString)) // VEC3
			{
				variable.getValue().setVec3(_extractVec3FromString(valueString));
			}
			else if ((variable.getValue().getType() == ScriptValueType::STRING) && _isStringValue(valueString)) // STRING
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
			else if ((variable.getValue().getType() == ScriptValueType::BOOLEAN) && _isBooleanValue(valueString)) // BOOLEAN - normal
			{
				variable.getValue().setBoolean(valueString == "<true>");
			}
			else if // BOOLEAN - condition
				(
					(variable.getValue().getType() == ScriptValueType::BOOLEAN) && 
					(valueString.front() == '(' && valueString.back() == ')')
				)
			{
				valueString.erase(valueString.begin());
				valueString.pop_back();
				variable.getValue().setBoolean(_checkConditionString(valueString));
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
					if ((variable.getValue().getType() == ScriptValueType::VEC3) && (values[0].getType() == ScriptValueType::VEC3))
					{
						variable.getValue().setVec3(values[0].getVec3());
					}
					else if ((variable.getValue().getType() == ScriptValueType::STRING) && (values[0].getType() == ScriptValueType::STRING))
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
			else
			{
				// Check if accessing individual float from vec3 variable
				auto parts = _checkVec3Part(valueString);

				// Remove vec3 part text
				if (parts != Ivec3(0))
				{
					valueString.pop_back();
					valueString.pop_back();
				}

				// Check if using another variable as value
				if (_isLocalVariableExisting(valueString) || _isGlobalVariableExisting(valueString))
				{
					// Retrieve other value
					auto otherVariable = _isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) :
						_getGlobalVariable(valueString);

					// Check if value is from vec3 variable
					if (variable.getValue().getType() == ScriptValueType::DECIMAL && parts != Ivec3(0))
					{
						if (parts.x && otherVariable.getValue().getType() == ScriptValueType::VEC3)
						{
							variable.getValue().setDecimal(otherVariable.getValue().getVec3().x);
						}
						else if (parts.y && otherVariable.getValue().getType() == ScriptValueType::VEC3)
						{
							variable.getValue().setDecimal(otherVariable.getValue().getVec3().y);
						}
						else if (parts.z && otherVariable.getValue().getType() == ScriptValueType::VEC3)
						{
							variable.getValue().setDecimal(otherVariable.getValue().getVec3().z);
						}
					}
					else if (variable.getValue().getType() == otherVariable.getValue().getType()) // Normal value
					{
						variable.getValue().setVec3(otherVariable.getValue().getVec3());
						variable.getValue().setString(otherVariable.getValue().getString());
						variable.getValue().setDecimal(otherVariable.getValue().getDecimal());
						variable.getValue().setInteger(otherVariable.getValue().getInteger());
						variable.getValue().setBoolean(otherVariable.getValue().getBoolean());
					}
					else
					{
						_throwScriptError("variable types do not match!");
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
		if (typeString == _vec3Keyword || 
			typeString == _stringKeyword || 
			typeString == _decimalKeyword || 
			typeString == _integerKeyword || 
			typeString == _booleanKeyword)
		{
			// Validate variable name
			bool validName = !nameString.empty() && nameString.substr(0, 5) != "fe3d:" && nameString.substr(0, 5) != "math:" &&
				nameString.substr(0, 5) != "misc:" && !isdigit(nameString.front() && isalnum(nameString.front())) &&
				nameString != "<true>" && nameString != "<false>";

			// Forbidden variable names
			for (auto& word : { _metaKeyword, _executeKeyword, _ifKeyword, _elifKeyword, _elseKeyword, _globalKeyword,
				_constKeyword, _editKeyword, _vec3Keyword, _stringKeyword, _decimalKeyword, _integerKeyword, _booleanKeyword, _isKeyword,
				_notKeyword, _andKeyword, _orKeyword, _moreKeyword, _lessKeyword, _additionKeyword, _subtractionKeyword, _multiplicationKeyword, _divisionKeyword })
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
						if (typeString == _vec3Keyword && _isVec3Value(valueString)) // VEC3
						{
							auto value = ScriptValue(_fe3d, ScriptValueType::VEC3, _extractVec3FromString(valueString));
							variableList.push_back(ScriptVariable(_fe3d, scope, nameString, isConstant, value));
						}
						else if (typeString == _stringKeyword && _isStringValue(valueString)) // STRING
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
						else if (typeString == _booleanKeyword && _isBooleanValue(valueString)) // BOOLEAN - normal
						{
							auto value = ScriptValue(_fe3d, ScriptValueType::BOOLEAN, (valueString == "<true>"));
							variableList.push_back(ScriptVariable(_fe3d, scope, nameString, isConstant, value));
						}
						else if (typeString == _booleanKeyword && (valueString.front() == '(' && valueString.back() == ')')) // BOOLEAN - condition
						{
							// Removing the ( ) around the string content
							valueString.erase(valueString.begin());
							valueString.pop_back();

							// Add new boolean variable
							auto value = ScriptValue(_fe3d, ScriptValueType::BOOLEAN, _checkConditionString(valueString));
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
								if (((typeString == _vec3Keyword)	 && (values[0].getType() == ScriptValueType::VEC3)) || 
									((typeString == _stringKeyword)  && (values[0].getType() == ScriptValueType::STRING))  ||
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
						else
						{
							// Check if accessing individual float from vec3 variable
							auto parts = _checkVec3Part(valueString);

							// Remove vec3 part text
							if (parts != Ivec3(0))
							{
								valueString.pop_back();
								valueString.pop_back();
							}

							// Check if using another variable as value
							if (_isLocalVariableExisting(valueString) || _isGlobalVariableExisting(valueString))
							{
								// Retrieve other variable
								auto otherVariable = _isLocalVariableExisting(valueString) ?
									_getLocalVariable(valueString) : _getGlobalVariable(valueString);

								// Check if using part of vec3 variable as value
								if (typeString == _decimalKeyword && parts != Ivec3(0))
								{
									// Determine part of vec3 variable
									if (parts.x)
									{
										auto newValue = ScriptValue(_fe3d, ScriptValueType::DECIMAL, otherVariable.getValue().getVec3().x);
										variableList.push_back(ScriptVariable(_fe3d, scope, nameString, isConstant, newValue));
									}
									else if (parts.y)
									{
										auto newValue = ScriptValue(_fe3d, ScriptValueType::DECIMAL, otherVariable.getValue().getVec3().y);
										variableList.push_back(ScriptVariable(_fe3d, scope, nameString, isConstant, newValue));
									}
									else if (parts.z)
									{
										auto newValue = ScriptValue(_fe3d, ScriptValueType::DECIMAL, otherVariable.getValue().getVec3().z);
										variableList.push_back(ScriptVariable(_fe3d, scope, nameString, isConstant, newValue));
									}
								}
								else if // Check if the value is of the right type
									(((typeString == _vec3Keyword) && (otherVariable.getValue().getType() == ScriptValueType::VEC3)) ||
									((typeString == _stringKeyword) && (otherVariable.getValue().getType() == ScriptValueType::STRING)) ||
									((typeString == _decimalKeyword) && (otherVariable.getValue().getType() == ScriptValueType::DECIMAL)) ||
									((typeString == _integerKeyword) && (otherVariable.getValue().getType() == ScriptValueType::INTEGER)) ||
									((typeString == _booleanKeyword) && (otherVariable.getValue().getType() == ScriptValueType::BOOLEAN)))
								{
									variableList.push_back(ScriptVariable(_fe3d, scope, nameString, isConstant, otherVariable.getValue()));
								}
								else
								{
									_throwScriptError("variable value types don't match!");
								}
							}
							else
							{
								_throwScriptError("invalid value!");
							}
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