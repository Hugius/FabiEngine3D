#include "script_interpreter.hpp"

const vector<ScriptValue> ScriptInterpreter::_extractValuesFromListString(const string& listString)
{
	// Temporary variables
	vector<ScriptValue> valueList;
	bool isBuildingString = false;
	bool isBuildingNumber = false;
	bool isBuildingDecimal = false;
	bool isBuildingBoolean = false;
	bool isBuildingVariable = false;
	bool hasFinishedValue = false;
	string currentValueString = "";

	// List string cannot be empty
	if(listString.empty())
	{
		return {};
	}

	// List string cannot start with a comma
	if(listString.front() == ',')
	{
		_throwScriptError("cannot start value with a comma!");
		return {};
	}

	// For every character in list string
	unsigned int index = 0;
	for(const auto& c : listString)
	{
		if(hasFinishedValue) // First character after a value has been extracted
		{
			if(c == ',') // Ready for next value extraction
			{
				hasFinishedValue = false;
			}
			else if(c != ' ') // After a value has been extracted, a comma must ALWAYS follow
			{
				_throwScriptError("values must be separated by commas!");
				return {};
			}
		}
		else
		{
			// Starting build of new value
			if(!isBuildingString && !isBuildingNumber && !isBuildingBoolean && !isBuildingVariable)
			{
				if(c == '"') // String
				{
					currentValueString = "";
					isBuildingString = true;
				}
				else if(isdigit(c) || c == '-') // Number
				{
					currentValueString = "";
					currentValueString.push_back(c);
					isBuildingNumber = true;
				}
				else if(c == '<') // Boolean
				{
					currentValueString = "";
					currentValueString.push_back(c);
					isBuildingBoolean = true;
				}
				else if(c == ' ') // Space
				{
					currentValueString = "";
				}
				else // Possible variable
				{
					currentValueString = "";
					currentValueString.push_back(c);
					isBuildingVariable = true;
				}

				if(index != (listString.size() - 1) || (isBuildingString || isBuildingBoolean)) // Skip to next character
				{
					index++;
					continue;
				}
				else // This is the last character, handle the building
				{
					currentValueString = "";
				}
			}

			if(isBuildingString) // Processing string value
			{
				if(c == '"') // Add new string value
				{
					valueList.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, currentValueString));
					isBuildingString = false;
					hasFinishedValue = true;
				}
				else // Keep building string
				{
					currentValueString += c;
				}
			}
			else if(isBuildingNumber) // Processing number value
			{
				if(c == '-') // Negative number
				{
					if(!currentValueString.empty())
					{
						_throwScriptError("invalid DEC syntax!");
						return {};
					}
					else
					{
						currentValueString += c;
					}
				}
				else if(isdigit(c)) // Keep building number
				{
					currentValueString += c;
				}
				else if(c == '.' && !isBuildingDecimal) // Start building decimal
				{
					currentValueString += c;
					isBuildingDecimal = true;
				}
				else if(c != ',' && c != ' ')
				{
					_throwScriptError("invalid character in number value!");
					return {};
				}

				// Check if number building finished
				if(c == ',' || (index == listString.size() - 1) || c == ' ')
				{
					if(isBuildingDecimal) // Convert to decimal
					{
						// Check if decimal value is valid
						if(currentValueString.back() == '.')
						{
							_throwScriptError("invalid DEC syntax!");
							return {};
						}
						else
						{
							valueList.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(_limitDecimalString(currentValueString))));
							isBuildingNumber = false;
							isBuildingDecimal = false;

							// Check if next comma still needs to be found
							if(c != ',')
							{
								hasFinishedValue = true;
							}
						}
					}
					else // Convert to integer
					{
						valueList.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(_limitIntegerString(currentValueString))));
						isBuildingNumber = false;

						// Check if next comma still needs to be found
						if(c != ',')
						{
							hasFinishedValue = true;
						}
					}
				}
			}
			else if(isBuildingBoolean) // Processing boolean value
			{
				// Build value
				currentValueString += c;

				// Check if value is true, false, or invalid
				if(currentValueString.size() == 6)
				{
					if(currentValueString == "<true>") // Add new boolean value
					{
						valueList.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, true));
						isBuildingBoolean = false;
						hasFinishedValue = true;
					}
					else if(currentValueString != "<false") // Must be "<false" if 6 letter string
					{
						_throwScriptError("invalid BOOL syntax!");
						return {};
					}
				}
				else if(currentValueString.size() == 7 && currentValueString == "<false>") // Add new boolean value
				{
					valueList.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, false));
					isBuildingBoolean = false;
					hasFinishedValue = true;
				}
				else if(currentValueString.size() > 7) // Invalid boolean string
				{
					_throwScriptError("invalid BOOL syntax!");
					return {};
				}
			}
			else if(isBuildingVariable) // Processing variable value
			{
				// Build value
				if(c != ',' && c != ' ')
				{
					currentValueString += c;
				}

				// Check if variable building finished
				if(c == ',' || (index == listString.size() - 1) || c == ' ')
				{
					// Prepare list access
					bool isAccessingList = false;
					auto listIndex = _extractListIndexFromString(currentValueString, isAccessingList);

					// Check if any error was thrown
					if(_hasThrownError)
					{
						return {};
					}

					// Remove list accessing characters
					if(isAccessingList)
					{
						auto isOpeningBracketFound = find(currentValueString.begin(), currentValueString.end(), '[');
						auto bracketIndex = static_cast<unsigned int>(distance(currentValueString.begin(), isOpeningBracketFound));
						currentValueString = currentValueString.substr(0, bracketIndex);
					}

					// Check if the specified variable name exists
					if(_isLocalVariableExisting(currentValueString) || _isGlobalVariableExisting(currentValueString))
					{
						// Retrieve value
						auto variable = (_isLocalVariableExisting(currentValueString) ? _getLocalVariable(currentValueString) : _getGlobalVariable(currentValueString));

						if(isAccessingList) // List[index]
						{
							// Check if list index is valid
							if(_validateListIndex(variable, listIndex))
							{
								valueList.push_back(variable.getValue(listIndex));
							}
							else // Error
							{
								return {};
							}
						}
						else if(variable.getType() == ScriptVariableType::SINGLE) // Normal value
						{
							valueList.push_back(variable.getValue());
						}
						else // Cannot be list variable
						{
							_throwScriptError("LIST cannot be used inside another LIST!");
							return {};
						}

						isBuildingVariable = false;

						// Check if needs to be found yet
						if(c != ',')
						{
							hasFinishedValue = true;
						}
					}
					else
					{
						_throwScriptError("variable not existing!");
						return {};
					}
				}
			}
		}

		index++;
	}

	// Check if not still building any values
	if(!isBuildingString && !isBuildingNumber && !isBuildingBoolean && !isBuildingVariable && hasFinishedValue)
	{
		return valueList;
	}
	else // Syntax is wrong
	{
		_throwScriptError("invalid value(s) syntax!");
		return {};
	}
}