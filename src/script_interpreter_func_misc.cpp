#include "script_interpreter.hpp"
#include "tools.hpp"

using SVT = ScriptValueType;

const vector<shared_ptr<ScriptValue>> ScriptInterpreter::_processMiscFunctionCall(const string & scriptLine)
{
	const auto openingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), '(');
	const auto closingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), ')');

	if((openingParanthesisFound == scriptLine.end()) || (closingParanthesisFound == scriptLine.end()))
	{
		_throwRuntimeError("invalid syntax or statement");

		return {};
	}

	if(scriptLine.back() != ')')
	{
		_throwRuntimeError("invalid syntax or statement");

		return {};
	}

	const auto parenthesisIndex = static_cast<int>(distance(scriptLine.begin(), openingParanthesisFound));
	const auto functionName = scriptLine.substr(0, parenthesisIndex);
	const auto argumentString = scriptLine.substr(static_cast<size_t>(parenthesisIndex + 1), (scriptLine.size() - static_cast<size_t>(parenthesisIndex + 1) - 1));
	const auto args = _extractValuesFromListString(argumentString);

	vector<shared_ptr<ScriptValue>> returnValues = {};

	if(_hasThrownError)
	{
		return {};
	}

	if(functionName == "misc:list_concat")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto firstName = args[0]->getString();
			const auto secondName = args[1]->getString();

			if(!_isLocalVariableExisting(firstName) && !_isGlobalVariableExisting(firstName))
			{
				_throwRuntimeError("variable \"" + firstName + "\" does not exist");

				return {};
			}

			if(!_isLocalVariableExisting(secondName) && !_isGlobalVariableExisting(secondName))
			{
				_throwRuntimeError("variable \"" + secondName + "\" does not exist");

				return {};
			}

			const auto firstListVariable = (_isLocalVariableExisting(firstName) ? _getLocalVariable(firstName) : _getGlobalVariable(firstName));

			if(firstListVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwRuntimeError("variable \"" + firstName + "\" is not of type " + LIST_KEYWORD);

				return {};
			}

			const auto secondListVariable = (_isLocalVariableExisting(secondName) ? _getLocalVariable(secondName) : _getGlobalVariable(secondName));

			if(secondListVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwRuntimeError("variable \"" + secondName + "\" is not of type " + LIST_KEYWORD);

				return {};
			}

			for(int index = 0; index < firstListVariable->getValueCount(); index++)
			{
				returnValues.push_back(firstListVariable->getValue(index));
			}

			for(int index = 0; index < secondListVariable->getValueCount(); index++)
			{
				returnValues.push_back(secondListVariable->getValue(index));
			}
		}
	}
	else if(functionName == "misc:list_size")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto listName = args[0]->getString();

			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwRuntimeError("variable \"" + listName + "\" does not exist");

				return {};
			}

			const auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));

			if(listVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwRuntimeError("variable \"" + listName + "\" is not of type " + LIST_KEYWORD);

				return {};
			}

			const auto result = listVariable->getValueCount();

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else if(functionName == "misc:list_empty")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto listName = args[0]->getString();

			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwRuntimeError("variable \"" + listName + "\" does not exist");

				return {};
			}

			const auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));

			if(listVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwRuntimeError("variable \"" + listName + "\" is not of type " + LIST_KEYWORD);

				return {};
			}

			const auto result = (listVariable->getValueCount() == 0);

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "misc:list_contains")
	{
		if(_validateArgumentCount(args, 2))
		{
			if(args[0]->getType() != SVT::STRING)
			{
				_throwRuntimeError("incorrect argument type");

				return {};
			}

			const auto listName = args[0]->getString();

			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwRuntimeError("variable \"" + listName + "\" does not exist");

				return {};
			}

			const auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));

			if(listVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwRuntimeError("variable \"" + listName + "\" is not of type " + LIST_KEYWORD);

				return {};
			}

			bool result = false;

			for(int index = 0; index < listVariable->getValueCount(); index++)
			{
				auto value = listVariable->getValue(index);

				if((args[1]->getType() == SVT::STRING) &&
				   (value->getType() == SVT::STRING) &&
				   (value->getString() == args[1]->getString()))
				{
					result = true;

					break;
				}

				if((args[1]->getType() == SVT::DECIMAL) &&
				   (value->getType() == SVT::DECIMAL) &&
				   (value->getDecimal() == args[1]->getDecimal()))
				{
					result = true;

					break;
				}

				if((args[1]->getType() == SVT::INTEGER) &&
				   (value->getType() == SVT::INTEGER) &&
				   (value->getInteger() == args[1]->getInteger()))
				{
					result = true;

					break;
				}

				if((args[1]->getType() == SVT::BOOLEAN) &&
				   (value->getType() == SVT::BOOLEAN) &&
				   (value->getBoolean() == args[1]->getBoolean()))
				{
					result = true;

					break;
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "misc:list_index")
	{
		if(_validateArgumentCount(args, 2))
		{
			if(args[0]->getType() != SVT::STRING)
			{
				_throwRuntimeError("incorrect argument type");

				return {};
			}

			const auto listName = args[0]->getString();

			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwRuntimeError("variable \"" + listName + "\" does not exist");

				return {};
			}

			const auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));

			if(listVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwRuntimeError("variable \"" + listName + "\" is not of type " + LIST_KEYWORD);

				return {};
			}

			int result = -1;

			for(int index = 0; index < listVariable->getValueCount(); index++)
			{
				auto value = listVariable->getValue(index);

				if((args[1]->getType() == SVT::STRING) &&
				   (value->getType() == SVT::STRING) &&
				   (value->getString() == args[1]->getString()))
				{
					result = index;

					break;
				}

				if((args[1]->getType() == SVT::DECIMAL) &&
				   (value->getType() == SVT::DECIMAL) &&
				   (value->getDecimal() == args[1]->getDecimal()))
				{
					result = index;

					break;
				}

				if((args[1]->getType() == SVT::INTEGER) &&
				   (value->getType() == SVT::INTEGER) &&
				   (value->getInteger() == args[1]->getInteger()))
				{
					result = index;

					break;
				}

				if((args[1]->getType() == SVT::BOOLEAN) &&
				   (value->getType() == SVT::BOOLEAN) &&
				   (value->getBoolean() == args[1]->getBoolean()))
				{
					result = index;

					break;
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else if(functionName == "misc:list_count")
	{
		if(_validateArgumentCount(args, 2))
		{
			if(args[0]->getType() != SVT::STRING)
			{
				_throwRuntimeError("incorrect argument type");

				return {};
			}

			const auto listName = args[0]->getString();

			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwRuntimeError("variable \"" + listName + "\" does not exist");

				return {};
			}

			const auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));

			if(listVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwRuntimeError("variable \"" + listName + "\" is not of type " + LIST_KEYWORD);

				return {};
			}

			int result = 0;

			for(int index = 0; index < listVariable->getValueCount(); index++)
			{
				auto value = listVariable->getValue(index);

				if((args[1]->getType() == SVT::STRING) &&
				   (value->getType() == SVT::STRING) &&
				   (value->getString() == args[1]->getString()))
				{
					result++;

					continue;
				}

				if((args[1]->getType() == SVT::DECIMAL) &&
				   (value->getType() == SVT::DECIMAL) &&
				   (value->getDecimal() == args[1]->getDecimal()))
				{
					result++;

					continue;
				}

				if((args[1]->getType() == SVT::INTEGER) &&
				   (value->getType() == SVT::INTEGER) &&
				   (value->getInteger() == args[1]->getInteger()))
				{
					result++;

					continue;
				}

				if((args[1]->getType() == SVT::BOOLEAN) &&
				   (value->getType() == SVT::BOOLEAN) &&
				   (value->getBoolean() == args[1]->getBoolean()))
				{
					result++;

					continue;
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else if(functionName == "misc:list_min")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto listName = args[0]->getString();

			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwRuntimeError("variable \"" + listName + "\" does not exist");

				return {};
			}

			const auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));

			if(listVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwRuntimeError("variable \"" + listName + "\" is not of type " + LIST_KEYWORD);

				return {};
			}

			if(listVariable->getValueCount() == 0)
			{
				_throwRuntimeError(LIST_KEYWORD + " \"" + listName + "\" is empty");

				return {};
			}

			const auto type = listVariable->getValue(0)->getType();

			for(int index = 0; index < listVariable->getValueCount(); index++)
			{
				if(listVariable->getValue(index)->getType() != type)
				{
					_throwRuntimeError("values inside " + LIST_KEYWORD + " \"" + listName + "\" are not of the same type");

					return {};
				}
			}

			switch(type)
			{
				case ScriptValueType::INTEGER:
				{
					vector<int> rawValues = {};

					for(int index = 0; index < listVariable->getValueCount(); index++)
					{
						rawValues.push_back(listVariable->getValue(index)->getInteger());
					}

					const auto result = *min_element(begin(rawValues), end(rawValues));

					returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));

					break;
				}
				case ScriptValueType::DECIMAL:
				{
					vector<float> rawValues = {};

					for(int index = 0; index < listVariable->getValueCount(); index++)
					{
						rawValues.push_back(listVariable->getValue(index)->getDecimal());
					}

					const auto result = *min_element(begin(rawValues), end(rawValues));

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));

					break;
				}
				default:
				{
					_throwRuntimeError("values inside " + LIST_KEYWORD + " \"" + listName + "\" must be " + INTEGER_KEYWORD + " or " + DECIMAL_KEYWORD);

					return {};
				}
			}
		}
	}
	else if(functionName == "misc:list_max")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto listName = args[0]->getString();

			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwRuntimeError("variable \"" + listName + "\" does not exist");

				return {};
			}

			const auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));

			if(listVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwRuntimeError("variable \"" + listName + "\" is not of type " + LIST_KEYWORD);

				return {};
			}

			if(listVariable->getValueCount() == 0)
			{
				_throwRuntimeError(LIST_KEYWORD + " \"" + listName + "\" is empty");

				return {};
			}

			const auto type = listVariable->getValue(0)->getType();

			for(int index = 0; index < listVariable->getValueCount(); index++)
			{
				if(listVariable->getValue(index)->getType() != type)
				{
					_throwRuntimeError("values inside " + LIST_KEYWORD + " \"" + listName + "\" are not of the same type");

					return {};
				}
			}

			switch(type)
			{
				case ScriptValueType::INTEGER:
				{
					vector<int> rawValues = {};

					for(int index = 0; index < listVariable->getValueCount(); index++)
					{
						rawValues.push_back(listVariable->getValue(index)->getInteger());
					}

					const auto result = *max_element(begin(rawValues), end(rawValues));

					returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));

					break;
				}
				case ScriptValueType::DECIMAL:
				{
					vector<float> rawValues = {};

					for(int index = 0; index < listVariable->getValueCount(); index++)
					{
						rawValues.push_back(listVariable->getValue(index)->getDecimal());
					}

					const auto result = *max_element(begin(rawValues), end(rawValues));

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));

					break;
				}
				default:
				{
					_throwRuntimeError("values inside " + LIST_KEYWORD + " \"" + listName + "\" must be " + INTEGER_KEYWORD + " or " + DECIMAL_KEYWORD);

					return {};
				}
			}
		}
	}
	else if(functionName == "misc:list_reverse")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto listName = args[0]->getString();

			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwRuntimeError("variable \"" + listName + "\" does not exist");

				return {};
			}

			const auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));

			if(listVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwRuntimeError("variable \"" + listName + "\" is not of type " + LIST_KEYWORD);

				return {};
			}

			for(int index = (listVariable->getValueCount() - 1); index > -1; index--)
			{
				returnValues.push_back(listVariable->getValue(index));
			}
		}
	}
	else if(functionName == "misc:list_to_string")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto listName = args[0]->getString();

			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwRuntimeError("variable \"" + listName + "\" does not exist");

				return {};
			}

			const auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));

			if(listVariable->getType() == ScriptVariableType::SINGLE)
			{
				_throwRuntimeError("variable \"" + listName + "\" is not of type " + LIST_KEYWORD);

				return {};
			}

			string result = "";

			result += "{";

			for(int index = 0; index < listVariable->getValueCount(); index++)
			{
				auto value = listVariable->getValue(index);

				switch(value->getType())
				{
					case ScriptValueType::BOOLEAN:
					{
						result += (value->getBoolean() ? "<true>" : "<false>");

						break;
					}
					case ScriptValueType::INTEGER:
					{
						result += to_string(value->getInteger());

						break;
					}
					case ScriptValueType::DECIMAL:
					{
						result += to_string(value->getDecimal());

						break;
					}
					case ScriptValueType::STRING:
					{
						result += "\"" + value->getString() + "\"";

						break;
					}
				}

				if((index + 1) < listVariable->getValueCount())
				{
					result += ", ";
				}
			}

			result += "}";

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else if(functionName == "misc:string_to_list")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto valueString = args[0]->getString();

			if(valueString.size() < 2)
			{
				_throwRuntimeError("invalid syntax or statement");

				return {};
			}

			valueString.erase(valueString.begin());
			valueString.pop_back();

			for(auto value : _extractValuesFromListString(valueString))
			{
				returnValues.push_back(value);
			}
		}
	}
	else if(functionName == "misc:string_concat")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = (args[0]->getString() + args[1]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else if(functionName == "misc:string_size")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = static_cast<int>(args[0]->getString().size());

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else if(functionName == "misc:string_empty")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = args[0]->getString().empty();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "misc:string_contains")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = (args[0]->getString().find(args[1]->getString()) != string::npos);

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "misc:string_part")
	{
		const auto types = {SVT::STRING, SVT::INTEGER, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if((args[1]->getInteger() < 0) ||
			   (args[1]->getInteger() > static_cast<int>(args[0]->getString().size())) ||
			   (args[2]->getInteger() < 0))
			{
				_throwRuntimeError("incorrect string part index/indices");

				return {};
			}

			const auto result = args[0]->getString().substr(args[1]->getInteger(), args[2]->getInteger());

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else if(functionName == "misc:string_split")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if((args[1]->getString().size() > 1) || (args[0]->getString().find(args[1]->getString()) == string::npos))
			{
				_throwRuntimeError("string delimiter not found");

				return {};
			}

			const auto fullString = args[0]->getString();
			const auto delimiter = args[1]->getString();

			string result = "";

			for(int index = 0; index < static_cast<int>(fullString.size()); index++)
			{
				if(fullString[index] == delimiter[0])
				{
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));

					result = "";
				}
				else if(index == (fullString.size() - 1))
				{
					result += fullString[index];

					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
				}
				else
				{
					result += fullString[index];
				}
			}
		}
	}
	else if(functionName == "misc:string_reverse")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			string result = "";

			auto content = args[0]->getString();

			reverse(content.begin(), content.end());

			for(const auto & character : content)
			{
				result += character;
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else if(functionName == "misc:string_capitalize")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto content = args[0]->getString();

			string result = "";

			if(!content.empty())
			{
				result = (static_cast<char>(toupper(content[0])) + content.substr(1));
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else if(functionName == "misc:string_zeroed_integer")
	{
		const auto types = {SVT::INTEGER, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto result = to_string(args[0]->getInteger());

			bool isNegative = false;

			if(result[0] == '-')
			{
				isNegative = true;

				result.erase(result.begin());
			}

			const auto zeroCount = (args[1]->getInteger() - static_cast<int>(result.size()));

			for(int index = 0; index < zeroCount; index++)
			{
				result.insert(result.begin(), '0');
			}

			if(isNegative)
			{
				result.insert(result.begin(), '-');
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else
	{
		_throwRuntimeError("misc function does not exist");

		return {};
	}

	return returnValues;
}