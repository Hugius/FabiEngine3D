#include "script_interpreter.hpp"
#include "logger.hpp"

void ScriptInterpreter::_processVariableAlteration(const string & scriptLine)
{
	string words[2] = {"", ""};

	int wordIndex = 0;

	for(const auto & character : scriptLine.substr(EDIT_KEYWORD.size() + 1))
	{
		if(character == ' ')
		{
			wordIndex++;

			if(wordIndex == 2)
			{
				break;
			}
		}
		else
		{
			words[wordIndex] += character;
		}
	}

	auto nameString = words[0];

	const auto equalSignString = words[1];

	if(nameString.empty())
	{
		_throwRuntimeError("variable name missing");

		return;
	}

	if(equalSignString != "=")
	{
		_throwRuntimeError("equal sign missing");

		return;
	}

	auto minLineSize = (scriptLine.find('=') + 3);

	if(scriptLine.size() < minLineSize)
	{
		_throwRuntimeError("value missing");

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
		_throwRuntimeError("variable \"" + nameString + "\" does not exist");

		return;
	}

	const auto leftVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	if(leftVariable->isConstant())
	{
		_throwRuntimeError("CONST variables cannot be changed");

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
	const auto isStringVariable = (leftVariable->getValue(leftValueIndex)->getType() == ScriptValueType::STRING);
	const auto isDecimalVariable = (leftVariable->getValue(leftValueIndex)->getType() == ScriptValueType::DECIMAL);
	const auto isIntegerVariable = (leftVariable->getValue(leftValueIndex)->getType() == ScriptValueType::INTEGER);
	const auto isBooleanVariable = (leftVariable->getValue(leftValueIndex)->getType() == ScriptValueType::BOOLEAN);

	if(leftVariable->getType() == ScriptVariableType::MULTIPLE && _isListValue(valueString))
	{
		const auto listString = valueString.substr(1, (valueString.size() - 2));
		const auto values = _extractValuesFromListString(listString);

		leftVariable->setValues(values);
	}
	else if(isSingleVariable && isStringVariable && _isStringValue(valueString))
	{
		valueString.erase(valueString.begin());
		valueString.pop_back();

		leftVariable->getValue(leftValueIndex)->setString(valueString);
	}
	else if(isSingleVariable && isDecimalVariable && _isDecimalValue(valueString))
	{
		leftVariable->getValue(leftValueIndex)->setDecimal(stof(_limitDecimalString(valueString)));
	}
	else if(isSingleVariable && isIntegerVariable && _isIntegerValue(valueString))
	{
		leftVariable->getValue(leftValueIndex)->setInteger(stoi(_limitIntegerString(valueString)));
	}
	else if(isSingleVariable && isBooleanVariable && _isBooleanValue(valueString))
	{
		leftVariable->getValue(leftValueIndex)->setBoolean(valueString == "<true>");
	}
	else if(isSingleVariable && isBooleanVariable && ((valueString.front() == '(') && (valueString.back() == ')')))
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
				_throwRuntimeError("function returned empty value");

				return;
			}
		}

		if(leftVariable->getType() == ScriptVariableType::MULTIPLE)
		{
			leftVariable->setValues(returnValues);
		}
		else if(returnValues.empty())
		{
			_throwRuntimeError("function returned no values");

			return;
		}
		else if(returnValues.size() > 1)
		{
			_throwRuntimeError("function returned too many values");

			return;
		}
		else if(returnValues[0]->getType() == ScriptValueType::EMPTY)
		{
			_throwRuntimeError("function must return value");

			return;
		}
		else if(isSingleVariable && isStringVariable && (returnValues[0]->getType() == ScriptValueType::STRING))
		{
			leftVariable->getValue(leftValueIndex)->setString(returnValues[0]->getString());
		}
		else if(isSingleVariable && isDecimalVariable && (returnValues[0]->getType() == ScriptValueType::DECIMAL))
		{
			leftVariable->getValue(leftValueIndex)->setDecimal(returnValues[0]->getDecimal());
		}
		else if(isSingleVariable && isIntegerVariable && (returnValues[0]->getType() == ScriptValueType::INTEGER))
		{
			leftVariable->getValue(leftValueIndex)->setInteger(returnValues[0]->getInteger());
		}
		else if(isSingleVariable && isBooleanVariable && (returnValues[0]->getType() == ScriptValueType::BOOLEAN))
		{
			leftVariable->getValue(leftValueIndex)->setBoolean(returnValues[0]->getBoolean());
		}
		else
		{
			_throwRuntimeError("function returned incorrect value type");

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
			_throwRuntimeError("variable \"" + valueString + "\" does not exist");

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

		if((leftVariable->getType() == ScriptVariableType::MULTIPLE) && (rightVariable->getType() == ScriptVariableType::MULTIPLE))
		{
			vector<shared_ptr<ScriptValue>> values = {};

			for(int index = 0; index < rightVariable->getValueCount(); index++)
			{
				values.push_back(rightVariable->getValue(index));
			}

			leftVariable->setValues(values);
		}
		else if(leftVariable->getValue(leftValueIndex)->getType() == rightVariable->getValue(rightValueIndex)->getType())
		{
			switch(rightVariable->getValue(rightValueIndex)->getType())
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
			_throwRuntimeError("value types not matching");

			return;
		}
	}
}