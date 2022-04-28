#include "script_interpreter.hpp"

const vector<shared_ptr<ScriptValue>> ScriptInterpreter::_extractValuesFromListString(const string & listString)
{
	vector<shared_ptr<ScriptValue>> valueList;
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
		_throwRuntimeError("cannot start value with ','");
		return {};
	}

	int index = 0;
	for(const auto & character : listString)
	{
		if(hasFinishedValue)
		{
			if(character == ',')
			{
				hasFinishedValue = false;
			}
			else if(character != ' ')
			{
				_throwRuntimeError("values must be separated by ','");
				return {};
			}
		}
		else
		{
			if(!isBuildingString && !isBuildingNumber && !isBuildingBoolean && !isBuildingVariable)
			{
				if(character == '"')
				{
					currentValueString = "";
					isBuildingString = true;
				}
				else if(isdigit(character) || character == '-')
				{
					currentValueString = "";
					currentValueString.push_back(character);
					isBuildingNumber = true;
				}
				else if(character == '<')
				{
					currentValueString = "";
					currentValueString.push_back(character);
					isBuildingBoolean = true;
				}
				else if(character == ' ')
				{
					currentValueString = "";
				}
				else
				{
					currentValueString = "";
					currentValueString.push_back(character);
					isBuildingVariable = true;
				}

				if(index != (listString.size() - 1) || (isBuildingString || isBuildingBoolean))
				{
					index++;
					continue;
				}
				else
				{
					currentValueString = "";
				}
			}

			if(isBuildingString)
			{
				if(character == '"')
				{
					valueList.push_back(make_shared<ScriptValue>(ScriptValueType::STRING, currentValueString));
					isBuildingString = false;
					hasFinishedValue = true;
				}
				else
				{
					currentValueString += character;
				}
			}
			else if(isBuildingNumber)
			{
				if(character == '-')
				{
					if(!currentValueString.empty())
					{
						_throwRuntimeError("invalid syntax");
						return {};
					}

					currentValueString += character;
				}
				else if(isdigit(character))
				{
					currentValueString += character;
				}
				else if(character == '.' && !isBuildingDecimal)
				{
					currentValueString += character;
					isBuildingDecimal = true;
				}
				else if(character != ',' && character != ' ')
				{
					_throwRuntimeError("invalid syntax");
					return {};
				}

				if(character == ',' || (index == listString.size() - 1) || character == ' ')
				{
					if(isBuildingDecimal)
					{
						if(currentValueString.back() == '.')
						{
							_throwRuntimeError("invalid syntax");
							return {};
						}

						valueList.push_back(make_shared<ScriptValue>(ScriptValueType::DECIMAL, stof(_limitDecimalString(currentValueString))));
						isBuildingNumber = false;
						isBuildingDecimal = false;

						if(character != ',')
						{
							hasFinishedValue = true;
						}
					}
					else
					{
						valueList.push_back(make_shared<ScriptValue>(ScriptValueType::INTEGER, stoi(_limitIntegerString(currentValueString))));
						isBuildingNumber = false;

						if(character != ',')
						{
							hasFinishedValue = true;
						}
					}
				}
			}
			else if(isBuildingBoolean)
			{
				currentValueString += character;

				if(currentValueString == "<true>")
				{
					valueList.push_back(make_shared<ScriptValue>(ScriptValueType::BOOLEAN, true));
					isBuildingBoolean = false;
					hasFinishedValue = true;
				}
				else if(currentValueString == "<false>")
				{
					valueList.push_back(make_shared<ScriptValue>(ScriptValueType::BOOLEAN, false));
					isBuildingBoolean = false;
					hasFinishedValue = true;
				}
				else if(currentValueString.size() >= string("<false>").size())
				{
					_throwRuntimeError("invalid syntax");
					return {};
				}
			}
			else if(isBuildingVariable)
			{
				if(character != ',' && character != ' ')
				{
					currentValueString += character;
				}

				if(character == ',' || (index == listString.size() - 1) || character == ' ')
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
						auto bracketIndex = static_cast<int>(distance(currentValueString.begin(), isOpeningBracketFound));
						currentValueString = currentValueString.substr(0, bracketIndex);
					}

					if(!_isLocalVariableExisting(currentValueString) && !_isGlobalVariableExisting(currentValueString))
					{
						_throwRuntimeError("variable \"" + currentValueString + "\" does not exist");
						return {};
					}

					const auto variable = (_isLocalVariableExisting(currentValueString) ? _getLocalVariable(currentValueString) : _getGlobalVariable(currentValueString));

					int valueIndex = 0;
					if(isAccessingList)
					{
						if(!_validateListIndex(variable, listIndex))
						{
							return {};
						}

						valueIndex = listIndex;
					}

					if(!isAccessingList && variable->getType() == ScriptVariableType::MULTIPLE)
					{
						_throwRuntimeError("LST cannot be used inside LST");
						return {};
					}

					valueList.push_back(variable->getValue(valueIndex));
					isBuildingVariable = false;

					if(character != ',')
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
		_throwRuntimeError("invalid syntax");
		return {};
	}

	return valueList;
}