#include "script_interpreter.hpp"

const bool ScriptInterpreter::_validateListIndex(shared_ptr<ScriptVariable> list, int index)
{
	if(list->getType() == ScriptVariableType::SINGLE)
	{
		_throwRuntimeError("variable \"" + list->getId() + "\" not of type LST");

		return false;
	}

	if(index < 0)
	{
		_throwRuntimeError("LST index negative");

		return false;
	}

	if(index >= list->getValueCount())
	{
		_throwRuntimeError("LST index out of range");

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
		_throwRuntimeError("not enough arguments");

		return false;
	}
	else
	{
		_throwRuntimeError("too many arguments");

		return false;
	}
}

const bool ScriptInterpreter::_validateArgumentTypes(const vector<shared_ptr<ScriptValue>> & values, const vector<ScriptValueType> & types)
{
	for(int index = 0; index < static_cast<int>(values.size()); index++)
	{
		if(values[index]->getType() != types[index])
		{
			_throwRuntimeError("incorrect argument type");

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
		_throwRuntimeError("LST name missing");

		return;
	}

	auto minLineSize = (PUSH_KEYWORD.size() + nameString.size() + 3);

	if(scriptLine.size() < minLineSize)
	{
		_throwRuntimeError("value missing");

		return;
	}

	auto valueString = scriptLine.substr(minLineSize - 1);

	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwRuntimeError("LST does not exist");

		return;
	}

	const auto listVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	if(listVariable->isConstant())
	{
		_throwRuntimeError("cannot push to constant LST");

		return;
	}

	if(_isListValue(valueString))
	{
		_throwRuntimeError("cannot push LST to LST");

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
		if(!_isLocalVariableExisting(valueString) && !_isGlobalVariableExisting(valueString))
		{
			_throwRuntimeError("invalid value");

			return;
		}

		const auto rightVariable = (_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) : _getGlobalVariable(valueString));

		if(rightVariable->getType() == ScriptVariableType::MULTIPLE)
		{
			_throwRuntimeError("cannot push LST to LST");

			return;
		}

		listVariable->addValue(rightVariable->getValue(0));
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
		_throwRuntimeError("LST name missing");

		return;
	}

	if(scriptLine.size() < (PULL_KEYWORD.size() + nameString.size() + 3))
	{
		_throwRuntimeError("LST index missing");

		return;
	}

	auto indexString = scriptLine.substr(PULL_KEYWORD.size() + nameString.size() + 2);

	if(!_isIntegerValue(indexString) && !_isLocalVariableExisting(indexString) && !_isGlobalVariableExisting(indexString))
	{
		_throwRuntimeError("invalid LST index");

		return;
	}

	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwRuntimeError("LST does not exist");

		return;
	}

	const auto listVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	if(listVariable->isConstant())
	{
		_throwRuntimeError("cannot push to constant LST");

		return;
	}

	int index;
	if(_isIntegerValue(indexString))
	{
		index = stoi(_limitIntegerString(indexString));
	}
	else
	{
		auto indexVariable = (_isLocalVariableExisting(indexString) ? _getLocalVariable(indexString) : _getGlobalVariable(indexString));

		if(indexVariable->getValue(0)->getType() != ScriptValueType::INTEGER)
		{
			_throwRuntimeError("LST index not of type INT");

			return;
		}

		index = indexVariable->getValue(0)->getInteger();
	}

	if(!_validateListIndex(listVariable, index))
	{
		return;
	}

	listVariable->deleteValue(index);
}