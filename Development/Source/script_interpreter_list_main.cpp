#include "script_interpreter.hpp"

vector<ScriptValue> ScriptInterpreter::_extractValuesFromListString(string listString)
{
	// Temporary variables
	vector<ScriptValue> valueList;
	bool buildingVec3 = false;
	bool buildingString = false;
	bool buildingNumber = false;
	bool buildingDecimal = false;
	bool buildingBoolean = false;
	bool buildingVariable = false;
	bool finishedValue = false;
	string currentValueString = "";

	// List string cannot be empty
	if (listString.empty())
	{
		return {};
	}

	// List string cannot start with a comma
	if (listString.front() == ',')
	{
		_throwScriptError("cannot start value with a comma!");
		return {};
	}

	// For every character in list string
	unsigned int index = 0;
	for (auto& c : listString)
	{
		if (finishedValue) // First character after a value has been extracted
		{
			if (c == ',') // Ready for next value extraction
			{
				finishedValue = false;
			}
			else if (c != ' ') // After a value has been extracted, a comma must ALWAYS follow
			{
				_throwScriptError("values must be separated by commas!");
				return {};
			}
		}
		else
		{
			// Starting build of new value
			if(!buildingVec3 && !buildingString && !buildingNumber && !buildingBoolean && !buildingVariable)
			{
				if (c == '[') // VEC3
				{
					currentValueString = "";
					currentValueString.push_back(c);
					buildingVec3 = true;
				}
				else if (c == '"') // STRING
				{
					currentValueString = "";
					buildingString = true;
				}
				else if (isdigit(c) || c == '-') // NUMBER
				{
					currentValueString = "";
					currentValueString.push_back(c);
					buildingNumber = true;
				}
				else if (c == '<') // BOOLEAN
				{
					currentValueString = "";
					currentValueString.push_back(c);
					buildingBoolean = true;
				}
				else if (c == ' ') // SPACE
				{
					currentValueString = "";
				}
				else // Possible VARIABLE
				{
					currentValueString = "";
					currentValueString.push_back(c);
					buildingVariable = true;
				}

				if (index != (listString.size() - 1) || (buildingString || buildingBoolean)) // Skip to next character
				{
					index++;
					continue;
				}
				else // This is the last character, handle the building
				{
					currentValueString = "";
				}
			}

			if (buildingVec3) // Processing VEC3 value
			{
				if (c == ']') // Add new vec3 value
				{
					currentValueString += c;

					// Check if filled in vec3 value is correct
					if (_isVec3Value(currentValueString))
					{
						valueList.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, _extractVec3FromString(currentValueString)));
						buildingVec3 = false;
						finishedValue = true;
					}
					else
					{
						_throwScriptError("invalid vec3 syntax!");
						return {};
					}
				}
				else // Keep building vec3
				{
					currentValueString += c;
				}
			}
			else if (buildingString) // Processing STRING value
			{
				if (c == '"') // Add new string value
				{
					valueList.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, currentValueString));
					buildingString = false;
					finishedValue = true;
				}
				else // Keep building string
				{
					currentValueString += c;
				}
			}
			else if (buildingNumber) // Processing NUMBER value
			{
				if (c == '-') // Negative number
				{
					if (!currentValueString.empty())
					{
						_throwScriptError("invalid decimal syntax!");
						return {};
					}
					else
					{
						currentValueString += c;
					}
				}
				else if (isdigit(c)) // Keep building number
				{
					currentValueString += c;
				}
				else if (c == '.' && !buildingDecimal) // Start building decimal
				{
					currentValueString += c;
					buildingDecimal = true;
				}
				else if (c != ',' && c != ' ')
				{
					_throwScriptError("invalid character in number value!");
					return {};
				}

				// Check if number building finished
				if (c == ',' || (index == listString.size() - 1) || c == ' ')
				{
					if (buildingDecimal) // Convert to decimal
					{
						// Check if decimal value is valid
						if (currentValueString.back() == '.')
						{
							_throwScriptError("invalid decimal syntax!");
							return {};
						}
						else
						{
							valueList.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(currentValueString)));
							buildingNumber = false;
							buildingDecimal = false;

							// Check if next comma still needs to be found
							if (c != ',')
							{
								finishedValue = true;
							}
						}
					}
					else // Convert to integer
					{
						valueList.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(currentValueString)));
						buildingNumber = false;

						// Check if next comma still needs to be found
						if (c != ',')
						{
							finishedValue = true;
						}
					}
				}
			}
			else if (buildingBoolean) // Processing BOOLEAN value
			{
				// Build value
				currentValueString += c;

				// Check if value is true, false, or invalid
				if (currentValueString.size() == 6)
				{
					if (currentValueString == "<true>") // Add new boolean value
					{
						valueList.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, true));
						buildingBoolean = false;
						finishedValue = true;
					}
					else if (currentValueString != "<false") // Must be "<false" if 6 letter string
					{
						_throwScriptError("invalid boolean syntax!");
						return {};
					}
				}
				else if (currentValueString.size() == 7 && currentValueString == "<false>") // Add new boolean value
				{
					valueList.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, false));
					buildingBoolean = false;
					finishedValue = true;
				}
				else if (currentValueString.size() > 7) // Invalid boolean string
				{
					_throwScriptError("invalid boolean syntax!");
					return {};
				}
			}
			else if (buildingVariable) // Processing VARIABLE value
			{
				// Build value
				if (c != ',' && c != ' ')
				{
					currentValueString += c;
				}

				// Check if variable building finished
				if (c == ',' || (index == listString.size() - 1) || c == ' ')
				{
					// Check if accessing individual value from list variable
					bool isAccessingList = false;
					auto listIndex = _extractListIndexFromString(currentValueString, isAccessingList);

					// Check if accessing individual float from vec3 variable
					auto vec3Parts = _extractVec3PartFromString(currentValueString);

					// Check if any error was thrown
					if (_hasThrownError)
					{
						return {};
					}

					// Remove vec3 part characters
					if (vec3Parts != Ivec3(0))
					{
						currentValueString.pop_back();
						currentValueString.pop_back();
					}

					// Remove list accessing characters
					if (isAccessingList)
					{
						auto openingBracketFound = std::find(currentValueString.begin(), currentValueString.end(), '[');
						unsigned int bracketIndex = std::distance(currentValueString.begin(), openingBracketFound);
						currentValueString = currentValueString.substr(0, bracketIndex);
					}

					// Check if the specified variable name exists
					if (_isLocalVariableExisting(currentValueString) || _isGlobalVariableExisting(currentValueString))
					{
						// Retrieve value
						auto variable = _isLocalVariableExisting(currentValueString) ? _getLocalVariable(currentValueString) :
							_getGlobalVariable(currentValueString);

						// Validate vec3 access
						if (vec3Parts != Ivec3(0))
						{
							if (variable.getType() == ScriptVariableType::MULTIPLE || variable.getValue().getType() != ScriptValueType::VEC3)
							{
								_throwScriptError("variable with ID \"" + variable.getID() + "\" is not a vec3!");
								return {};
							}
						}

						if (vec3Parts.x && variable.getValue().getType() == ScriptValueType::VEC3) // Vec3.x
						{
							valueList.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, variable.getValue().getVec3().x));
						}
						else if (vec3Parts.y && variable.getValue().getType() == ScriptValueType::VEC3) // Vec3.y
						{
							valueList.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, variable.getValue().getVec3().y));
						}
						else if (vec3Parts.z && variable.getValue().getType() == ScriptValueType::VEC3) // Vec3.z
						{
							valueList.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, variable.getValue().getVec3().z));
						}
						else if (isAccessingList) // List[index]
						{
							// Check if list index is valid
							if (_validateListIndex(variable, listIndex))
							{
								valueList.push_back(variable.getValue(listIndex));
							}
							else // Error
							{
								return {};
							}
						}
						else if (variable.getType() == ScriptVariableType::SINGLE) // Normal value
						{
							valueList.push_back(variable.getValue());
						}
						else // Cannot be list variable
						{
							_throwScriptError("list variable cannot be used inside a list!");
							return {};
						}

						buildingVariable = false;

						// Check if needs to be found yet
						if (c != ',')
						{
							finishedValue = true;
						}
					}
					else
					{
						_throwScriptError("variable \"" + currentValueString + "\" does not exist!");
						return {};
					}
				}
			}
		}

		index++;
	}
	
	// Check if not still building any values
	if (!buildingString && !buildingNumber && !buildingBoolean && !buildingVariable && finishedValue)
	{
		return valueList;
	}
	else // Syntax is wrong
	{
		_throwScriptError("invalid value(s) syntax!");
		return {};
	}
}