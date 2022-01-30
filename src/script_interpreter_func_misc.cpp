#include "script_interpreter.hpp"
#include "tools.hpp"

using SVT = ScriptValueType;

const vector<shared_ptr<ScriptValue>> ScriptInterpreter::_processMiscFunctionCall(const string& scriptLine)
{
	vector<shared_ptr<ScriptValue>> returnValues;
	auto openingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), '(');
	auto closingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), ')');

	if((openingParanthesisFound == scriptLine.end()) && (closingParanthesisFound == scriptLine.end()))
	{
		_throwScriptError("invalid '()' syntax!");
		return {};
	}

	if(scriptLine.back() != ')')
	{
		_throwScriptError("function call must end with ')'!");
		return {};
	}

	auto parenthesisIndex = static_cast<unsigned int>(distance(scriptLine.begin(), openingParanthesisFound));
	string argumentString = scriptLine.substr(static_cast<size_t>(parenthesisIndex + 1));
	argumentString.pop_back();
	auto args = _extractValuesFromListString(argumentString);

	if(_hasThrownError)
	{
		return {};
	}

	auto functionName = scriptLine.substr(0, parenthesisIndex);

	if(functionName == "misc:list_concat")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto firstName = args[0]->getString();
			const auto secondName = args[1]->getString();

			if(!_isLocalVariableExisting(firstName) && !_isGlobalVariableExisting(firstName))
			{
				_throwScriptError("variable \"" + firstName + "\" not existing!");
				return {};
			}

			if(!_isLocalVariableExisting(secondName) && !_isGlobalVariableExisting(secondName))
			{
				_throwScriptError("variable \"" + secondName + "\" not existing!");
				return {};
			}

			auto firstListVariable = (_isLocalVariableExisting(firstName) ? _getLocalVariable(firstName) : _getGlobalVariable(firstName));
			if(firstListVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwScriptError("variable \"" + firstName + "\" is not of type LIST!");
				return {};
			}

			auto secondListVariable = (_isLocalVariableExisting(secondName) ? _getLocalVariable(secondName) : _getGlobalVariable(secondName));
			if(secondListVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwScriptError("variable \"" + secondName + "\" is not of type LIST!");
				return {};
			}

			for(unsigned int i = 0; i < firstListVariable->getValueCount(); i++)
			{
				returnValues.push_back(firstListVariable->getValue(i));
			}
			for(unsigned int i = 0; i < secondListVariable->getValueCount(); i++)
			{
				returnValues.push_back(secondListVariable->getValue(i));
			}
		}
	}
	else if(functionName == "misc:list_size")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto listName = args[0]->getString();

			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwScriptError("variable \"" + listName + "\" not existing!");
				return {};
			}

			auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
			if(listVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwScriptError("variable \"" + listName + "\" is not of type LIST!");
				return {};
			}

			const auto result = listVariable->getValueCount();

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, static_cast<int>(result)));
		}
	}
	else if(functionName == "misc:list_contains")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, 2))
		{
			if(args[0]->getType() != SVT::STRING)
			{
				_throwScriptError("incorrect argument type!");
				return {};
			}

			auto listName = args[0]->getString();
			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwScriptError("variable \"" + listName + "\" not existing!");
				return {};
			}

			auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
			if(listVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwScriptError("variable \"" + listName + "\" is not of type LIST!");
				return {};
			}

			bool hasFoundValue = false;
			for(unsigned int i = 0; i < listVariable->getValueCount(); i++)
			{
				if((listVariable->getValue(i)->getType() == SVT::STRING) &&
				   (args[1]->getType() == SVT::STRING) &&
				   (listVariable->getValue(i)->getString() == args[1]->getString()))
				{
					hasFoundValue = true;
					break;
				}

				if((listVariable->getValue(i)->getType() == SVT::DECIMAL) &&
				   (args[1]->getType() == SVT::DECIMAL) &&
				   (listVariable->getValue(i)->getDecimal() == args[1]->getDecimal()))
				{
					hasFoundValue = true;
					break;
				}

				if((listVariable->getValue(i)->getType() == SVT::INTEGER) &&
				   (args[1]->getType() == SVT::INTEGER) &&
				   (listVariable->getValue(i)->getInteger() == args[1]->getInteger()))
				{
					hasFoundValue = true;
					break;
				}

				if((listVariable->getValue(i)->getType() == SVT::BOOLEAN) &&
				   (args[1]->getType() == SVT::BOOLEAN) &&
				   (listVariable->getValue(i)->getBoolean() == args[1]->getBoolean()))
				{
					hasFoundValue = true;
					break;
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, hasFoundValue));
		}
	}
	else if(functionName == "misc:list_index")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, 2))
		{
			if(args[0]->getType() != SVT::STRING)
			{
				_throwScriptError("incorrect argument type!");
				return {};
			}

			auto listName = args[0]->getString();
			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwScriptError("variable \"" + listName + "\" not existing!");
				return {};
			}

			auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
			if(listVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwScriptError("variable \"" + listName + "\" is not of type LIST!");
				return {};
			}

			int foundIndex = -1;
			for(unsigned int i = 0; i < listVariable->getValueCount(); i++)
			{
				if((listVariable->getValue(i)->getType() == SVT::STRING) &&
				   (args[1]->getType() == SVT::STRING) &&
				   (listVariable->getValue(i)->getString() == args[1]->getString()))
				{
					foundIndex = i;
					break;
				}

				if((listVariable->getValue(i)->getType() == SVT::DECIMAL) &&
				   (args[1]->getType() == SVT::DECIMAL) &&
				   (listVariable->getValue(i)->getDecimal() == args[1]->getDecimal()))
				{
					foundIndex = i;
					break;
				}

				if((listVariable->getValue(i)->getType() == SVT::INTEGER) &&
				   (args[1]->getType() == SVT::INTEGER) &&
				   (listVariable->getValue(i)->getInteger() == args[1]->getInteger()))
				{
					foundIndex = i;
					break;
				}

				if((listVariable->getValue(i)->getType() == SVT::BOOLEAN) &&
				   (args[1]->getType() == SVT::BOOLEAN) &&
				   (listVariable->getValue(i)->getBoolean() == args[1]->getBoolean()))
				{
					foundIndex = i;
					break;
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, foundIndex));
		}
	}
	else if(functionName == "misc:list_min")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto listName = args[0]->getString();

			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwScriptError("variable \"" + listName + "\" not existing!");
				return {};
			}

			auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
			if(listVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwScriptError("variable \"" + listName + "\" is not of type LIST!");
				return {};
			}

			if(listVariable->getValueCount() == 0)
			{
				_throwScriptError("LIST \"" + listName + "\" is empty!");
				return {};
			}

			auto type = listVariable->getValue(0)->getType();
			for(unsigned int i = 0; i < listVariable->getValueCount(); i++)
			{
				if(listVariable->getValue(i)->getType() != type)
				{
					_throwScriptError("values inside LIST \"" + listName + "\" not of same type!");
					return {};
				}
			}

			if(type == ScriptValueType::INTEGER)
			{
				vector<int> rawValues;
				for(unsigned int i = 0; i < listVariable->getValueCount(); i++)
				{
					rawValues.push_back(listVariable->getValue(i)->getInteger());
				}

				const auto result = *min_element(begin(rawValues), end(rawValues));

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
			else if(type == ScriptValueType::DECIMAL)
			{
				vector<float> rawValues;
				for(unsigned int i = 0; i < listVariable->getValueCount(); i++)
				{
					rawValues.push_back(listVariable->getValue(i)->getDecimal());
				}

				const auto result = *min_element(begin(rawValues), end(rawValues));

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
			else
			{
				_throwScriptError("values inside LIST \"" + listName + "\" must be INT or DEC!");
				return {};
			}
		}
	}
	else if(functionName == "misc:list_max")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto listName = args[0]->getString();

			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwScriptError("variable \"" + listName + "\" not existing!");
				return {};
			}

			auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
			if(listVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwScriptError("variable \"" + listName + "\" is not of type LIST!");
				return {};
			}

			if(listVariable->getValueCount() == 0)
			{
				_throwScriptError("LIST \"" + listName + "\" is empty!");
				return {};
			}

			auto type = listVariable->getValue(0)->getType();
			for(unsigned int i = 0; i < listVariable->getValueCount(); i++)
			{
				if(listVariable->getValue(i)->getType() != type)
				{
					_throwScriptError("values inside LIST \"" + listName + "\" not of same type!");
					return {};
				}
			}

			if(type == ScriptValueType::INTEGER)
			{
				vector<int> rawValues;
				for(unsigned int i = 0; i < listVariable->getValueCount(); i++)
				{
					rawValues.push_back(listVariable->getValue(i)->getInteger());
				}

				const auto result = *max_element(begin(rawValues), end(rawValues));

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
			else if(type == ScriptValueType::DECIMAL)
			{
				vector<float> rawValues;
				for(unsigned int i = 0; i < listVariable->getValueCount(); i++)
				{
					rawValues.push_back(listVariable->getValue(i)->getDecimal());
				}

				const auto result = *max_element(begin(rawValues), end(rawValues));

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
			else
			{
				_throwScriptError("values inside LIST \"" + listName + "\" must be INT or DEC!");
				return {};
			}
		}
	}
	else if(functionName == "misc:list_reverse")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto listName = args[0]->getString();

			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwScriptError("variable \"" + listName + "\" not existing!");
				return {};
			}

			auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
			if(listVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwScriptError("variable \"" + listName + "\" is not of type LIST!");
				return {};
			}

			for(int i = (static_cast<int>(listVariable->getValueCount()) - 1); i > -1; i--)
			{
				returnValues.push_back(listVariable->getValue(i));
			}
		}
	}
	else if(functionName == "misc:string_concat")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, args[0]->getString() + args[1]->getString()));
		}
	}
	else if(functionName == "misc:string_get_size")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = args[0]->getString().size();

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, static_cast<int>(result)));
		}
	}
	else if(functionName == "misc:string_contains")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = (args[0]->getString().find(args[1]->getString()) != string::npos);

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "misc:string_get_part")
	{
		auto types = {SVT::STRING, SVT::INTEGER, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if((args[1]->getInteger() < 0) ||
			   (args[1]->getInteger() > static_cast<int>(args[0]->getString().size())) ||
			   (args[2]->getInteger() < 0))
			{
				_throwScriptError("incorrect string part index/indices!");
				return {};
			}

			const auto result = args[0]->getString().substr(args[1]->getInteger(), args[2]->getInteger());

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else if(functionName == "misc:string_split")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if((args[1]->getString().size() > 1) || (args[0]->getString().find(args[1]->getString()) == string::npos))
			{
				_throwScriptError("string splitter not found!");
				return {};
			}

			const auto fullString = args[0]->getString();
			const auto splitter = args[1]->getString();

			string stringPart = "";
			for(size_t i = 0; i < fullString.size(); i++)
			{
				if(fullString[i] == splitter.back())
				{
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, stringPart));
					stringPart = "";
				}
				else if(i == (fullString.size() - 1))
				{
					stringPart += fullString[i];
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, stringPart));
				}
				else
				{
					stringPart += fullString[i];
				}
			}
		}
	}
	else if(functionName == "misc:string_reverse")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			string result = "";
			string content = args[0]->getString();
			reverse(content.begin(), content.end());
			for(const auto& character : content)
			{
				result += character;
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else if(functionName == "misc:get_random_integer")
	{
		auto types = {SVT::INTEGER, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = Math::getRandomNumber(args[0]->getInteger(), args[1]->getInteger());

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else if(functionName == "misc:get_random_decimal")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = Math::getRandomNumber(args[0]->getDecimal(), args[1]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else
	{
		_throwScriptError("misc function not existing!");
		return {};
	}

	return returnValues;
}