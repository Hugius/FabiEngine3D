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
						_throwScriptError("invalid INT or DEC syntax!");
						return {};
					}

					// Add character
					currentValueString += c;
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
				else if(c != ',' && c != ' ') // Invalid character
				{
					_throwScriptError("invalid INT or DEC syntax!");
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

						// Add value
						valueList.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(_limitDecimalString(currentValueString))));
						isBuildingNumber = false;
						isBuildingDecimal = false;

						// Check if next comma still needs to be found
						if(c != ',')
						{
							hasFinishedValue = true;
						}
					}
					else // Convert to integer
					{
						// Add value
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
				// Add character
				currentValueString += c;

				// Check if value is true/false/invalid
				if(currentValueString == "<true>")
				{
					valueList.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, true));
					isBuildingBoolean = false;
					hasFinishedValue = true;
				}
				else if(currentValueString == "<false>")
				{
					valueList.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, false));
					isBuildingBoolean = false;
					hasFinishedValue = true;
				}
				else if(currentValueString.size() > string("<false>").size())
				{
					_throwScriptError("invalid BOOL syntax!");
					return {};
				}
			}
			else if(isBuildingVariable) // Processing variable value
			{
				// Add character
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

					// Check if variable is not existing
					if(!_isLocalVariableExisting(currentValueString) && !_isGlobalVariableExisting(currentValueString))
					{
						_throwScriptError("variable not existing!");
						return {};
					}

					// Retrieve variable
					const auto& variable = (_isLocalVariableExisting(currentValueString) ? _getLocalVariable(currentValueString) : _getGlobalVariable(currentValueString));

					// Validate list access
					unsigned int valueIndex = 0;
					if(isAccessingList)
					{
						// Check if list index is invalid
						if(!_validateListIndex(variable, listIndex))
						{
							return {};
						}

						// Copy list index
						valueIndex = listIndex;
					}

					// Check if variable is a list
					if(variable.getType() == ScriptVariableType::MULTIPLE)
					{
						_throwScriptError("LIST cannot be used inside another LIST!");
						return {};
					}

					// Add value
					valueList.push_back(variable.getValue(valueIndex));
					isBuildingVariable = false;

					// Check if needs to be found yet
					if(c != ',')
					{
						hasFinishedValue = true;
					}
				}
			}
		}

		// Increment index
		index++;
	}

	// Check if still building any values
	if(isBuildingString || isBuildingNumber || isBuildingBoolean || isBuildingVariable)
	{
		_throwScriptError("invalid value(s) syntax!");
		return {};
	}

	// Return values
	return valueList;
}