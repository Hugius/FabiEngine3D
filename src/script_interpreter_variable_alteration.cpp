#include "script_interpreter.hpp"
#include "logger.hpp"

void ScriptInterpreter::_processVariableAlteration(const string & scriptLine)
{
	string parts[2] = {"", ""};

	int partIndex = 0;

	for(const auto & character : scriptLine.substr(ALTER_KEYWORD.size() + 1))
	{
		if(character == ' ')
		{
			partIndex++;

			if(partIndex == 2)
			{
				break;
			}
		}
		else
		{
			parts[partIndex] += character;
		}
	}

	auto nameString = parts[0];

	const auto equalSignString = parts[1];

	if(nameString.empty())
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	if(equalSignString != "=")
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	const auto minLineSize = (scriptLine.find('=') + 3);

	if(scriptLine.size() < minLineSize)
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	auto valueString = scriptLine.substr(minLineSize - 1);

	bool isAccessingLeftList = false;

	const auto leftListIndex = _extractListIndexFromString(nameString, isAccessingLeftList);

	if(_hasThrownError)
	{
		return;
	}

	if(isAccessingLeftList)
	{
		const auto isOpeningBracketFound = find(nameString.begin(), nameString.end(), '[');
		const auto bracketIndex = static_cast<int>(distance(nameString.begin(), isOpeningBracketFound));

		nameString = nameString.substr(0, bracketIndex);
	}

	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	const auto leftVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	if(leftVariable->isFinal())
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	int leftValueIndex = 0;

	if(isAccessingLeftList)
	{
		if(_validateListIndex(leftVariable, leftListIndex))
		{
			leftValueIndex = leftListIndex;
		}
		else
		{
			return;
		}
	}

	const auto isSingleVariable = (leftVariable->getType() == ScriptVariableType::SINGLE || isAccessingLeftList);
	const auto isStringVariable = (isSingleVariable && (leftVariable->getValue(leftValueIndex)->getType() == ScriptValueType::STRING));
	const auto isDecimalVariable = (isSingleVariable && (leftVariable->getValue(leftValueIndex)->getType() == ScriptValueType::DECIMAL));
	const auto isIntegerVariable = (isSingleVariable && (leftVariable->getValue(leftValueIndex)->getType() == ScriptValueType::INTEGER));
	const auto isBooleanVariable = (isSingleVariable && (leftVariable->getValue(leftValueIndex)->getType() == ScriptValueType::BOOLEAN));

	if(leftVariable->getType() == ScriptVariableType::MULTIPLE && _isListValue(valueString))
	{
		const auto listString = valueString.substr(1, (valueString.size() - 2));
		const auto values = _extractValuesFromListString(listString);

		leftVariable->setValues(values);
	}
	else if(isStringVariable && _isStringValue(valueString))
	{
		valueString.erase(valueString.begin());
		valueString.pop_back();

		leftVariable->getValue(leftValueIndex)->setString(valueString);
	}
	else if(isDecimalVariable && _isDecimalValue(valueString))
	{
		leftVariable->getValue(leftValueIndex)->setDecimal(stof(_limitDecimalString(valueString)));
	}
	else if(isIntegerVariable && _isIntegerValue(valueString))
	{
		leftVariable->getValue(leftValueIndex)->setInteger(stoi(_limitIntegerString(valueString)));
	}
	else if(isBooleanVariable && _isBooleanValue(valueString))
	{
		leftVariable->getValue(leftValueIndex)->setBoolean(valueString == "<true>");
	}
	else if(isBooleanVariable && ((valueString.front() == '(') && (valueString.back() == ')')))
	{
		valueString.erase(valueString.begin());
		valueString.pop_back();

		leftVariable->getValue(leftValueIndex)->setBoolean(_checkConditionString(valueString));
	}
	else if(valueString.substr(0, 5) == "fe3d:" || valueString.substr(0, 5) == "math:" || valueString.substr(0, 5) == "misc:")
	{
		const auto loggerMessageCount = Logger::getMessageCount();
		const auto returnValues =
			(valueString.substr(0, 5) == "fe3d:") ? _processFe3dFunctionCall(valueString) :
			(valueString.substr(0, 5) == "math:") ? _processMathFunctionCall(valueString) :
			_processMiscFunctionCall(valueString);

		_checkEngineWarnings(loggerMessageCount);

		if(_hasThrownError)
		{
			return;
		}

		for(const auto & value : returnValues)
		{
			if(value->getType() == ScriptValueType::EMPTY)
			{
				_throwRuntimeError("invalid syntax or statement");

				return;
			}
		}

		if(leftVariable->getType() == ScriptVariableType::MULTIPLE)
		{
			leftVariable->setValues(returnValues);
		}
		else if(returnValues.empty())
		{
			_throwRuntimeError("invalid syntax or statement");

			return;
		}
		else if(returnValues.size() > 1)
		{
			_throwRuntimeError("invalid syntax or statement");

			return;
		}
		else if(returnValues[0]->getType() == ScriptValueType::EMPTY)
		{
			_throwRuntimeError("invalid syntax or statement");

			return;
		}
		else if(isStringVariable && (returnValues[0]->getType() == ScriptValueType::STRING))
		{
			leftVariable->getValue(leftValueIndex)->setString(returnValues[0]->getString());
		}
		else if(isDecimalVariable && (returnValues[0]->getType() == ScriptValueType::DECIMAL))
		{
			leftVariable->getValue(leftValueIndex)->setDecimal(returnValues[0]->getDecimal());
		}
		else if(isIntegerVariable && (returnValues[0]->getType() == ScriptValueType::INTEGER))
		{
			leftVariable->getValue(leftValueIndex)->setInteger(returnValues[0]->getInteger());
		}
		else if(isBooleanVariable && (returnValues[0]->getType() == ScriptValueType::BOOLEAN))
		{
			leftVariable->getValue(leftValueIndex)->setBoolean(returnValues[0]->getBoolean());
		}
		else
		{
			_throwRuntimeError("invalid syntax or statement");

			return;
		}
	}
	else
	{
		bool isAccessingRightList = false;

		const auto rightListIndex = _extractListIndexFromString(valueString, isAccessingRightList);

		if(_hasThrownError)
		{
			return;
		}

		if(isAccessingRightList)
		{
			const auto isOpeningBracketFound = find(valueString.begin(), valueString.end(), '[');
			const auto bracketIndex = static_cast<int>(distance(valueString.begin(), isOpeningBracketFound));

			valueString = valueString.substr(0, bracketIndex);
		}

		if(!_isLocalVariableExisting(valueString) && !_isGlobalVariableExisting(valueString))
		{
			_throwRuntimeError("invalid syntax or statement");

			return;
		}

		const auto rightVariable = (_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) : _getGlobalVariable(valueString));

		int rightValueIndex = 0;

		if(isAccessingRightList)
		{
			if(!_validateListIndex(rightVariable, rightListIndex))
			{
				return;
			}

			rightValueIndex = rightListIndex;
		}

		const auto isLeftListValue = ((leftVariable->getType() == ScriptVariableType::MULTIPLE) && !isAccessingLeftList);
		const auto isRightListValue = ((rightVariable->getType() == ScriptVariableType::MULTIPLE) && !isAccessingRightList);

		if(isLeftListValue && isRightListValue)
		{
			vector<shared_ptr<ScriptValue>> values = {};

			for(int index = 0; index < rightVariable->getValueCount(); index++)
			{
				const auto value = rightVariable->getValue(index);

				switch(value->getType())
				{
					case ScriptValueType::STRING:
					{
						values.push_back(make_shared<ScriptValue>(ScriptValueType::STRING, value->getString()));

						break;
					}
					case ScriptValueType::DECIMAL:
					{
						values.push_back(make_shared<ScriptValue>(ScriptValueType::DECIMAL, value->getDecimal()));

						break;
					}
					case ScriptValueType::INTEGER:
					{
						values.push_back(make_shared<ScriptValue>(ScriptValueType::INTEGER, value->getInteger()));

						break;
					}
					case ScriptValueType::BOOLEAN:
					{
						values.push_back(make_shared<ScriptValue>(ScriptValueType::BOOLEAN, value->getBoolean()));

						break;
					}
				}
			}

			leftVariable->setValues(values);
		}
		else if((leftVariable->getValue(leftValueIndex)->getType() == rightVariable->getValue(rightValueIndex)->getType()) && !isLeftListValue && !isRightListValue)
		{
			switch(leftVariable->getValue(leftValueIndex)->getType())
			{
				case ScriptValueType::STRING:
				{
					leftVariable->setValue(make_shared<ScriptValue>(ScriptValueType::STRING, rightVariable->getValue(rightValueIndex)->getString()), leftValueIndex);

					break;
				}
				case ScriptValueType::DECIMAL:
				{
					leftVariable->setValue(make_shared<ScriptValue>(ScriptValueType::DECIMAL, rightVariable->getValue(rightValueIndex)->getDecimal()), leftValueIndex);

					break;
				}
				case ScriptValueType::INTEGER:
				{
					leftVariable->setValue(make_shared<ScriptValue>(ScriptValueType::INTEGER, rightVariable->getValue(rightValueIndex)->getInteger()), leftValueIndex);

					break;
				}
				case ScriptValueType::BOOLEAN:
				{
					leftVariable->setValue(make_shared<ScriptValue>(ScriptValueType::BOOLEAN, rightVariable->getValue(rightValueIndex)->getBoolean()), leftValueIndex);

					break;
				}
			}
		}
		else
		{
			_throwRuntimeError("invalid syntax or statement");

			return;
		}
	}
}