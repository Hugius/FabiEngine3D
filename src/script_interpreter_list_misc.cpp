#include "script_interpreter.hpp"

const bool ScriptInterpreter::_validateListIndex(const shared_ptr<ScriptVariable> list, unsigned int index)
{
	if(list->getType() == ScriptVariableType::SINGLE)
	{
		_throwRuntimeError("variable \"" + list->getId() + "\" not of type LIST!");
		return false;
	}

	if(index < 0)
	{
		_throwRuntimeError("LIST index negative!");
		return false;
	}

	if(index >= list->getValueCount())
	{
		_throwRuntimeError("LIST index out of range!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateArgumentCount(const vector<shared_ptr<ScriptValue>>& values, unsigned int count)
{
	if(values.size() == count)
	{
		return true;
	}
	else if(values.size() < count)
	{
		_throwRuntimeError("not enough arguments!");
		return false;
	}
	else
	{
		_throwRuntimeError("too many arguments!");
		return false;
	}
}

const bool ScriptInterpreter::_validateArgumentTypes(const vector<shared_ptr<ScriptValue>>& values, const vector<ScriptValueType>& types)
{
	for(size_t i = 0; i < values.size(); i++)
	{
		if(values[i]->getType() != types[i])
		{
			_throwRuntimeError("incorrect argument type!");
			return false;
		}
	}

	return true;
}

void ScriptInterpreter::_processListPush(const string& scriptLine)
{
	string nameString = "";
	for(const auto& c : scriptLine.substr(PUSHING_KEYWORD.size() + 1))
	{
		if(c == ' ')
		{
			break;
		}
		else
		{
			nameString += c;
		}
	}

	if(nameString.empty())
	{
		_throwRuntimeError("LIST name missing!");
		return;
	}

	auto minLineSize = (PUSHING_KEYWORD.size() + nameString.size() + 3);
	if(scriptLine.size() < minLineSize)
	{
		_throwRuntimeError("value missing!");
		return;
	}

	string valueString = scriptLine.substr(minLineSize - 1);

	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwRuntimeError("LIST not existing!");
		return;
	}

	auto listVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	if(listVariable->isConstant())
	{
		_throwRuntimeError("cannot push to constant LIST!");
		return;
	}

	if(_isListValue(valueString))
	{
		_throwRuntimeError("cannot push LIST to LIST!");
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
			_throwRuntimeError("invalid value!");
			return;
		}

		const auto rightVariable = (_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) : _getGlobalVariable(valueString));

		if(rightVariable->getType() == ScriptVariableType::MULTIPLE)
		{
			_throwRuntimeError("cannot push LIST to LIST!");
			return;
		}

		listVariable->addValue(rightVariable->getValue());
	}
}

void ScriptInterpreter::_processListPull(const string& scriptLine)
{
	string nameString = "";
	for(const auto& c : scriptLine.substr(PULLING_KEYWORD.size() + 1))
	{
		if(c == ' ')
		{
			break;
		}
		else
		{
			nameString += c;
		}
	}

	if(nameString.empty())
	{
		_throwRuntimeError("LIST name missing!");
		return;
	}

	if(scriptLine.size() < (PULLING_KEYWORD.size() + nameString.size() + 3))
	{
		_throwRuntimeError("LIST index missing!");
		return;
	}

	string indexString = scriptLine.substr(PULLING_KEYWORD.size() + nameString.size() + 2);

	if(!_isIntegerValue(indexString) && !_isLocalVariableExisting(indexString) && !_isGlobalVariableExisting(indexString))
	{
		_throwRuntimeError("invalid LIST index!");
		return;
	}

	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwRuntimeError("LIST not existing!");
		return;
	}

	auto listVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	if(listVariable->isConstant())
	{
		_throwRuntimeError("cannot push to constant LIST!");
		return;
	}

	unsigned int index = -1;
	if(_isIntegerValue(indexString))
	{
		index = stoi(_limitIntegerString(indexString));
	}
	else
	{
		auto indexVariable = (_isLocalVariableExisting(indexString) ? _getLocalVariable(indexString) : _getGlobalVariable(indexString));

		if(indexVariable->getValue()->getType() != ScriptValueType::INTEGER)
		{
			_throwRuntimeError("LIST index not of type INT!");
			return;
		}

		index = indexVariable->getValue()->getInteger();
	}

	if(!_validateListIndex(listVariable, index))
	{
		return;
	}

	listVariable->deleteValue(index);
}