#include "script_interpreter.hpp"

const vector<ScriptValue> ScriptInterpreter::_extractValuesFromListString(const string& listString)
{
	vector<ScriptValue> valueList;
	bool isBuildingString = false;
	bool isBuildingNumber = false;
	bool isBuildingDecimal = false;
	bool isBuildingBoolean = false;
	bool isBuildingVariable = false;
	bool hasFinishedValue = false;
	string currentValueString = "";

	if(listString.empty())
	{
		return {};
	}

	if(listString[0] == ',')
	{
		_throwScriptError("cannot start value with ','!");
		return {};
	}

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
				_throwScriptError("values must be separated by ','!");
				return {};
			}
		}
		else
		{
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

				if(c == ',' || (index == listString.size() - 1) || c == ' ')
				{
					if(isBuildingDecimal) // Convert to decimal
					{
						if(currentValueString.back() == '.')
						{
							_throwScriptError("invalid DEC syntax!");
							return {};
						}

						valueList.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(_limitDecimalString(currentValueString))));
						isBuildingNumber = false;
						isBuildingDecimal = false;

						if(c != ',')
						{
							hasFinishedValue = true;
						}
					}
					else // Convert to integer
					{
						valueList.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(_limitIntegerString(currentValueString))));
						isBuildingNumber = false;

						if(c != ',')
						{
							hasFinishedValue = true;
						}
					}
				}
			}
			else if(isBuildingBoolean) // Processing boolean value
			{
				currentValueString += c;

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
				if(c != ',' && c != ' ')
				{
					currentValueString += c;
				}

				if(c == ',' || (index == listString.size() - 1) || c == ' ')
				{
					bool isAccessingList = false;
					auto listIndex = _extractListIndexFromString(currentValueString, isAccessingList);

					if(_hasThrownError)
					{
						return {};
					}

					if(isAccessingList)
					{
						auto isOpeningBracketFound = find(currentValueString.begin(), currentValueString.end(), '[');
						auto bracketIndex = static_cast<unsigned int>(distance(currentValueString.begin(), isOpeningBracketFound));
						currentValueString = currentValueString.substr(0, bracketIndex);
					}

					if(!_isLocalVariableExisting(currentValueString) && !_isGlobalVariableExisting(currentValueString))
					{
						_throwScriptError("variable \"" + currentValueString + "\" not existing!");
						return {};
					}

					const auto& variable = (_isLocalVariableExisting(currentValueString) ? _getLocalVariable(currentValueString) : _getGlobalVariable(currentValueString));

					unsigned int valueIndex = 0;
					if(isAccessingList)
					{
						if(!_validateListIndex(variable, listIndex))
						{
							return {};
						}

						valueIndex = listIndex;
					}

					if(!isAccessingList && variable.getType() == ScriptVariableType::MULTIPLE)
					{
						_throwScriptError("LIST cannot be used inside LIST!");
						return {};
					}

					valueList.push_back(variable.getValue(valueIndex));
					isBuildingVariable = false;

					if(c != ',')
					{
						hasFinishedValue = true;
					}
				}
			}
		}

		index++;
	}

	if(isBuildingString || isBuildingNumber || isBuildingBoolean || isBuildingVariable)
	{
		_throwScriptError("invalid syntax!");
		return {};
	}

	return valueList;
}