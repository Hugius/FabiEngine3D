#include "script_interpreter.hpp"

const bool ScriptInterpreter::_validateListIndex(shared_ptr<ScriptVariable> list, int index)
{
	if(list->getType() == ScriptVariableType::SINGLE)
	{
		_throwRuntimeError("invalid syntax or statement");

		return false;
	}

	if(index < 0)
	{
		_throwRuntimeError("invalid syntax or statement");

		return false;
	}

	if(index >= list->getValueCount())
	{
		_throwRuntimeError("invalid syntax or statement");

		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateArgumentCount(const vector<shared_ptr<ScriptValue>> & values, int count)
{
	if(values.size() == count)
	{
		return true;
	}
	else if(values.size() < count)
	{
		_throwRuntimeError("invalid syntax or statement");

		return false;
	}
	else
	{
		_throwRuntimeError("invalid syntax or statement");

		return false;
	}
}

const bool ScriptInterpreter::_validateArgumentTypes(const vector<shared_ptr<ScriptValue>> & values, const vector<ScriptValueType> & types)
{
	for(int index = 0; index < static_cast<int>(values.size()); index++)
	{
		if(values[index]->getType() != types[index])
		{
			_throwRuntimeError("invalid syntax or statement");

			return false;
		}
	}

	return true;
}

void ScriptInterpreter::_processListPush(const string & scriptLine)
{
	string nameString = "";

	for(const auto & character : scriptLine.substr(PUSH_KEYWORD.size() + 1))
	{
		if(character == ' ')
		{
			break;
		}
		else
		{
			nameString += character;
		}
	}

	if(nameString.empty())
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	const auto minLineSize = (PUSH_KEYWORD.size() + nameString.size() + 3);

	if(scriptLine.size() < minLineSize)
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	auto valueString = scriptLine.substr(minLineSize - 1);

	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	const auto listVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	if(listVariable->isFinal())
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	if(_isListValue(valueString))
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}
	else if(_isStringValue(valueString))
	{
		valueString.erase(valueString.begin());
		valueString.pop_back();

		listVariable->addValue(make_shared<ScriptValue>(ScriptValueType::STRING, valueString));
	}
	else if(_isDecimalValue(valueString))
	{
		listVariable->addValue(make_shared<ScriptValue>(ScriptValueType::DECIMAL, stof(_limitDecimalString(valueString))));
	}
	else if(_isIntegerValue(valueString))
	{
		listVariable->addValue(make_shared<ScriptValue>(ScriptValueType::INTEGER, stoi(_limitIntegerString(valueString))));
	}
	else if(_isBooleanValue(valueString))
	{
		listVariable->addValue(make_shared<ScriptValue>(ScriptValueType::BOOLEAN, (valueString == "<true>")));
	}
	else
	{
		bool isAccessingList = false;

		const auto listIndex = _extractListIndexFromString(valueString, isAccessingList);

		if(_hasThrownError)
		{
			return;
		}

		if(isAccessingList)
		{
			const auto openingBracketIterator = find(valueString.begin(), valueString.end(), '[');
			const auto openingBracketIndex = static_cast<int>(distance(valueString.begin(), openingBracketIterator));

			valueString = valueString.substr(0, openingBracketIndex);
		}

		if(!_isLocalVariableExisting(valueString) && !_isGlobalVariableExisting(valueString))
		{
			_throwRuntimeError("invalid syntax or statement");

			return;
		}

		const auto rightVariable = (_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) : _getGlobalVariable(valueString));

		int valueIndex = 0;

		if(isAccessingList)
		{
			if(!_validateListIndex(rightVariable, listIndex))
			{
				return;
			}

			valueIndex = listIndex;
		}

		if(!isAccessingList && (rightVariable->getType() == ScriptVariableType::MULTIPLE))
		{
			_throwRuntimeError("invalid syntax or statement");

			return;
		}

		switch(rightVariable->getValue(valueIndex)->getType())
		{
			case ScriptValueType::STRING:
			{
				listVariable->addValue(make_shared<ScriptValue>(ScriptValueType::STRING, rightVariable->getValue(valueIndex)->getString()));

				break;
			}
			case ScriptValueType::DECIMAL:
			{
				listVariable->addValue(make_shared<ScriptValue>(ScriptValueType::DECIMAL, rightVariable->getValue(valueIndex)->getDecimal()));

				break;
			}
			case ScriptValueType::INTEGER:
			{
				listVariable->addValue(make_shared<ScriptValue>(ScriptValueType::INTEGER, rightVariable->getValue(valueIndex)->getInteger()));

				break;
			}
			case ScriptValueType::BOOLEAN:
			{
				listVariable->addValue(make_shared<ScriptValue>(ScriptValueType::BOOLEAN, rightVariable->getValue(valueIndex)->getBoolean()));

				break;
			}
		}
	}
}

void ScriptInterpreter::_processListPull(const string & scriptLine)
{
	string nameString = "";

	for(const auto & character : scriptLine.substr(PULL_KEYWORD.size() + 1))
	{
		if(character == ' ')
		{
			break;
		}
		else
		{
			nameString += character;
		}
	}

	if(nameString.empty())
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	if(scriptLine.size() < (PULL_KEYWORD.size() + nameString.size() + 3))
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	auto indexString = scriptLine.substr(PULL_KEYWORD.size() + nameString.size() + 2);

	if(!_isIntegerValue(indexString) && !_isLocalVariableExisting(indexString) && !_isGlobalVariableExisting(indexString))
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	const auto listVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	if(listVariable->isFinal())
	{
		_throwRuntimeError("invalid syntax or statement");

		return;
	}

	int index;
	if(_isIntegerValue(indexString))
	{
		index = stoi(_limitIntegerString(indexString));
	}
	else
	{
		auto variable = (_isLocalVariableExisting(indexString) ? _getLocalVariable(indexString) : _getGlobalVariable(indexString));

		if(variable->getValue(0)->getType() != ScriptValueType::INTEGER)
		{
			_throwRuntimeError("invalid syntax or statement");

			return;
		}

		index = variable->getValue(0)->getInteger();
	}

	if(!_validateListIndex(listVariable, index))
	{
		return;
	}

	listVariable->deleteValue(index);
}