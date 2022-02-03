#include "script_interpreter.hpp"

const vector<shared_ptr<ScriptValue>> ScriptInterpreter::_extractValuesFromListString(const string& listString)
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

	unsigned int index = 0;
	for(const auto& c : listString)
	{
		if(hasFinishedValue)
		{
			if(c == ',')
			{
				hasFinishedValue = false;
			}
			else if(c != ' ')
			{
				_throwRuntimeError("values must be separated by ','");
				return {};
			}
		}
		else
		{
			if(!isBuildingString && !isBuildingNumber && !isBuildingBoolean && !isBuildingVariable)
			{
				if(c == '"')
				{
					currentValueString = "";
					isBuildingString = true;
				}
				else if(isdigit(c) || c == '-')
				{
					currentValueString = "";
					currentValueString.push_back(c);
					isBuildingNumber = true;
				}
				else if(c == '<')
				{
					currentValueString = "";
					currentValueString.push_back(c);
					isBuildingBoolean = true;
				}
				else if(c == ' ')
				{
					currentValueString = "";
				}
				else
				{
					currentValueString = "";
					currentValueString.push_back(c);
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
				if(c == '"')
				{
					valueList.push_back(make_shared<ScriptValue>(ScriptValueType::STRING, currentValueString));
					isBuildingString = false;
					hasFinishedValue = true;
				}
				else
				{
					currentValueString += c;
				}
			}
			else if(isBuildingNumber)
			{
				if(c == '-')
				{
					if(!currentValueString.empty())
					{
						_throwRuntimeError("invalid INT or DEC syntax");
						return {};
					}

					currentValueString += c;
				}
				else if(isdigit(c))
				{
					currentValueString += c;
				}
				else if(c == '.' && !isBuildingDecimal)
				{
					currentValueString += c;
					isBuildingDecimal = true;
				}
				else if(c != ',' && c != ' ')
				{
					_throwRuntimeError("invalid INT or DEC syntax");
					return {};
				}

				if(c == ',' || (index == listString.size() - 1) || c == ' ')
				{
					if(isBuildingDecimal)
					{
						if(currentValueString.back() == '.')
						{
							_throwRuntimeError("invalid DEC syntax");
							return {};
						}

						valueList.push_back(make_shared<ScriptValue>(ScriptValueType::DECIMAL, stof(_limitDecimalString(currentValueString))));
						isBuildingNumber = false;
						isBuildingDecimal = false;

						if(c != ',')
						{
							hasFinishedValue = true;
						}
					}
					else
					{
						valueList.push_back(make_shared<ScriptValue>(ScriptValueType::INTEGER, stoi(_limitIntegerString(currentValueString))));
						isBuildingNumber = false;

						if(c != ',')
						{
							hasFinishedValue = true;
						}
					}
				}
			}
			else if(isBuildingBoolean)
			{
				currentValueString += c;

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
				else if(currentValueString.size() > string("<false>").size())
				{
					_throwRuntimeError("invalid BOOL syntax");
					return {};
				}
			}
			else if(isBuildingVariable)
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
						_throwRuntimeError("variable \"" + currentValueString + "\" does not exist");
						return {};
					}

					const auto variable = (_isLocalVariableExisting(currentValueString) ? _getLocalVariable(currentValueString) : _getGlobalVariable(currentValueString));

					unsigned int valueIndex = 0;
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
						_throwRuntimeError("LIST cannot be used inside LIST");
						return {};
					}

					valueList.push_back(variable->getValue(valueIndex));
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
		_throwRuntimeError("invalid syntax");
		return {};
	}

	return valueList;
}