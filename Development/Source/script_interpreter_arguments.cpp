#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateArgumentAmount(vector<ScriptValue> arguments, unsigned int amount)
{
	if (arguments.size() == amount) // Check if argument amount is correct
	{
		return true;
	}
	else if (arguments.size() < amount) // Not enough arguments
	{
		_throwScriptError("not enough arguments!");
		return false;
	}
	else // Too many arguments
	{
		_throwScriptError("too many arguments!");
		return false;
	}
}

bool ScriptInterpreter::_validateArgumentTypes(vector<ScriptValue> arguments, vector<ScriptValueType> types)
{
	for (unsigned int i = 0; i < arguments.size(); i++)
	{
		if (arguments[i].getType() != types[i])
		{
			_throwScriptError("wrong argument type(s)!");
			return false;
		}
	}

	return true;
}

vector<ScriptValue> ScriptInterpreter::_extractArguments(string argumentString)
{
	// Temporary variables
	vector<ScriptValue> argumentList;
	bool buildingVec3 = false;
	bool buildingString = false;
	bool buildingNumber = false;
	bool buildingDecimal = false;
	bool buildingBoolean = false;
	bool buildingVariable = false;
	bool finishedArgument = false;
	string currentArgument = "";

	// Argument string cannot be empty
	if (argumentString.empty())
	{
		return {};
	}

	// Argument string cannot start with a comma
	if (argumentString.front() == ',')
	{
		_throwScriptError("cannot start argument with a comma!");
		return {};
	}

	// For every character in argument string
	unsigned int index = 0;
	for (auto& c : argumentString)
	{
		if (finishedArgument) // First character after an argument has been extracted
		{
			if (c == ',') // Ready for next argument extraction
			{
				finishedArgument = false;
			}
			else if (c != ' ') // After an argument has been extracted, a comma must ALWAYS follow
			{
				_throwScriptError("arguments must be separated by commas!");
				return {};
			}
		}
		else
		{
			// Starting build of new argument
			if(!buildingVec3 && !buildingString && !buildingNumber && !buildingBoolean && !buildingVariable)
			{
				if (c == '[') // VEC3
				{
					currentArgument = "";
					currentArgument.push_back(c);
					buildingVec3 = true;
				}
				else if (c == '"') // STRING
				{
					currentArgument = "";
					buildingString = true;
				}
				else if (isdigit(c) || c == '-') // NUMBER
				{
					currentArgument = "";
					currentArgument.push_back(c);
					buildingNumber = true;
				}
				else if (c == '<') // BOOLEAN
				{
					currentArgument = "";
					currentArgument.push_back(c);
					buildingBoolean = true;
				}
				else if (c == ' ') // SPACE
				{
					currentArgument = "";
				}
				else // Possible VARIABLE
				{
					currentArgument = "";
					currentArgument.push_back(c);
					buildingVariable = true;
				}

				if (index != (argumentString.size() - 1) || (buildingString || buildingBoolean)) // Skip to next character
				{
					index++;
					continue;
				}
				else // This is the last character, handle the building
				{
					currentArgument = "";
				}
			}

			if (buildingVec3) // Processing VEC3 argument
			{
				if (c == ']') // Add new vec3 argument
				{
					currentArgument += c;

					// Check if filled in vec3 value is correct
					if (_isVec3Value(currentArgument))
					{
						argumentList.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, _extractVec3FromString(currentArgument)));
						buildingVec3 = false;
						finishedArgument = true;
					}
					else
					{
						_throwScriptError("invalid vec3 syntax!");
					}
				}
				else // Keep building vec3
				{
					currentArgument += c;
				}
			}
			else if (buildingString) // Processing STRING argument
			{
				if (c == '"') // Add new string argument
				{
					argumentList.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, currentArgument));
					buildingString = false;
					finishedArgument = true;
				}
				else // Keep building string
				{
					currentArgument += c;
				}
			}
			else if (buildingNumber) // Processing NUMBER argument
			{
				if (c == '-') // Negative number
				{
					if (!currentArgument.empty())
					{
						_throwScriptError("invalid decimal syntax!");
						return {};
					}
					else
					{
						currentArgument += c;
					}
				}
				else if (isdigit(c)) // Keep building number
				{
					currentArgument += c;
				}
				else if (c == '.' && !buildingDecimal) // Start building decimal
				{
					currentArgument += c;
					buildingDecimal = true;
				}
				else if (c != ',' && c != ' ')
				{
					_throwScriptError("invalid character in number value!");
					return {};
				}

				// Check if number building finished
				if (c == ',' || (index == argumentString.size() - 1) || c == ' ')
				{
					if (buildingDecimal) // Convert to decimal
					{
						// Check if decimal argument is valid
						if (currentArgument.back() == '.')
						{
							_throwScriptError("invalid decimal syntax!");
							return {};
						}
						else
						{
							argumentList.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(currentArgument)));
							buildingNumber = false;
							buildingDecimal = false;

							// Check if next comma still needs to be found
							if (c != ',')
							{
								finishedArgument = true;
							}
						}
					}
					else // Convert to integer
					{
						argumentList.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(currentArgument)));
						buildingNumber = false;

						// Check if next comma still needs to be found
						if (c != ',')
						{
							finishedArgument = true;
						}
					}
				}
			}
			else if (buildingBoolean) // Processing BOOLEAN argument
			{
				// Build argument
				currentArgument += c;

				// Check if argument is true, false, or invalid
				if (currentArgument.size() == 6)
				{
					if (currentArgument == "<true>") // Add new boolean argument
					{
						argumentList.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, true));
						buildingBoolean = false;
						finishedArgument = true;
					}
					else if (currentArgument != "<false") // Must be "<false" if 6 letter string
					{
						_throwScriptError("invalid boolean syntax!");
						return {};
					}
				}
				else if (currentArgument.size() == 7 && currentArgument == "<false>") // Add new boolean argument
				{
					argumentList.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, false));
					buildingBoolean = false;
					finishedArgument = true;
				}
				else if (currentArgument.size() > 7) // Invalid boolean string
				{
					_throwScriptError("invalid boolean syntax!");
					return {};
				}
			}
			else if (buildingVariable) // Processing VARIABLE argument
			{
				// Build argument
				if (c != ',')
				{
					currentArgument += c;
				}

				// Check if variable building finished
				if (c == ',' || (index == argumentString.size() - 1) || c == ' ')
				{
					// Check if accessing individual float from vec3 variable
					auto parts = _checkVec3Part(currentArgument);

					// Remove vec3 part text
					if (parts != Ivec3(0))
					{
						currentArgument.pop_back();
						currentArgument.pop_back();
					}

					// Check if the specified variable name exists
					if (_isLocalVariableExisting(currentArgument) || _isGlobalVariableExisting(currentArgument))
					{
						// Retrieve value
						auto variableValue = _isLocalVariableExisting(currentArgument) ? _getLocalVariable(currentArgument).getValue() :
							_getGlobalVariable(currentArgument).getValue();

						// Check if accessing a part of vec3 value
						if (parts.x && variableValue.getType() == ScriptValueType::VEC3)
						{
							argumentList.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, variableValue.getVec3().x));
						}
						else if (parts.y && variableValue.getType() == ScriptValueType::VEC3)
						{
							argumentList.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, variableValue.getVec3().y));
						}
						else if (parts.z && variableValue.getType() == ScriptValueType::VEC3)
						{
							argumentList.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, variableValue.getVec3().z));
						}
						else // Normal value
						{
							argumentList.push_back(variableValue);
						}

						buildingVariable = false;

						// Check if needs to be found yet
						if (c != ',')
						{
							finishedArgument = true;
						}
					}
					else
					{
						_throwScriptError("variable \"" + currentArgument + "\" does not exist!");
						return {};
					}
				}
			}
		}

		index++;
	}
	
	// Check if not still building any arguments
	if (!buildingString && !buildingNumber && !buildingBoolean && !buildingVariable && finishedArgument)
	{
		return argumentList;
	}
	else // Syntax is wrong
	{
		_throwScriptError("invalid argument(s) syntax!");
		return {};
	}
}