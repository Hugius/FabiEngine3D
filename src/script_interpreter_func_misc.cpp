#include "script_interpreter.hpp"
#include "tools.hpp"

using SVT = ScriptValueType;

const vector<ScriptValue> ScriptInterpreter::_processMiscellaneousFunctionCall(const string& scriptLine)
{
	// Temporary values
	vector<ScriptValue> returnValues;
	auto openingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), '(');
	auto closingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), ')');

	// Check if function call has no opening & closing parentheses
	if((openingParanthesisFound == scriptLine.end()) && (closingParanthesisFound == scriptLine.end()))
	{
		_throwScriptError("invalid '()' syntax!");
	}

	// Check if function call does not end with a paranthesis
	if(scriptLine.back() != ')')
	{
		_throwScriptError("function call must end with ')'!");
	}

	// Extract arguments
	auto parenthesisIndex = static_cast<unsigned int>(distance(scriptLine.begin(), openingParanthesisFound));
	string argumentString = scriptLine.substr(static_cast<size_t>(parenthesisIndex + 1));
	argumentString.pop_back();
	auto args = _extractValuesFromListString(argumentString);

	// Check if argument extraction went wrong
	if(_hasThrownError)
	{
		return {};
	}

	// Temporary values
	auto functionName = scriptLine.substr(0, parenthesisIndex);

	// Determine type of function
	if(functionName == "misc:list_concat")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			// Temporary values
			auto firstName = args[0].getString();
			auto secondName = args[1].getString();

			// Check if first variable not existing
			if(!_isLocalVariableExisting(firstName) && !_isGlobalVariableExisting(firstName))
			{
				_throwScriptError("variable \"" + firstName + "\" not existing!");
				return returnValues;
			}

			// Check if second variable not existing
			if(!_isLocalVariableExisting(secondName) && !_isGlobalVariableExisting(secondName))
			{
				_throwScriptError("variable \"" + secondName + "\" not existing!");
				return returnValues;
			}

			// Check if first variable is a list
			auto firstListVariable = (_isLocalVariableExisting(firstName) ? _getLocalVariable(firstName) : _getGlobalVariable(firstName));
			if(firstListVariable.getType() == ScriptVariableType::SINGLE)
			{
				_throwScriptError("variable \"" + firstName + "\" is not of type LIST!");
				return returnValues;
			}

			// Check if second variable is a list
			auto secondListVariable = (_isLocalVariableExisting(secondName) ? _getLocalVariable(secondName) : _getGlobalVariable(secondName));
			if(secondListVariable.getType() == ScriptVariableType::SINGLE)
			{
				_throwScriptError("variable \"" + secondName + "\" is not of type LIST!");
				return returnValues;
			}

			// Return concatenated lists
			for(unsigned int i = 0; i < firstListVariable.getValueCount(); i++)
			{
				returnValues.push_back(firstListVariable.getValue(i));
			}
			for(unsigned int i = 0; i < secondListVariable.getValueCount(); i++)
			{
				returnValues.push_back(secondListVariable.getValue(i));
			}
		}
	}
	else if(functionName == "misc:list_size")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			// Temporary values
			auto listName = args[0].getString();

			// Check if variable not existing
			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwScriptError("variable \"" + listName + "\" not existing!");
				return returnValues;
			}

			// Check if variable is not a list
			auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
			if(listVariable.getType() == ScriptVariableType::SINGLE)
			{
				_throwScriptError("variable \"" + listName + "\" is not of type LIST!");
				return returnValues;
			}

			// Return list size
			auto result = listVariable.getValueCount();
			returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
		}
	}
	else if(functionName == "misc:list_contains")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, 2))
		{
			// List name must be string
			if(args[0].getType() != SVT::STRING)
			{
				_throwScriptError("incorrect argument type!");
				return returnValues;
			}

			// Check if variable does not exist
			auto listName = args[0].getString();
			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwScriptError("variable \"" + listName + "\" not existing!");
				return returnValues;
			}

			// Check if variable is not a list
			auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
			if(listVariable.getType() == ScriptVariableType::SINGLE)
			{
				_throwScriptError("variable \"" + listName + "\" is not of type LIST!");
				return returnValues;
			}

			// Try to find value
			bool hasFoundValue = false;
			for(unsigned int i = 0; i < listVariable.getValueCount(); i++)
			{
				// String
				if((listVariable.getValue(i).getType() == SVT::STRING) &&
				   (args[1].getType() == SVT::STRING) &&
				   (listVariable.getValue(i).getString() == args[1].getString()))
				{
					hasFoundValue = true;
					break;
				}

				// Decimal
				if((listVariable.getValue(i).getType() == SVT::DECIMAL) &&
				   (args[1].getType() == SVT::DECIMAL) &&
				   (listVariable.getValue(i).getDecimal() == args[1].getDecimal()))
				{
					hasFoundValue = true;
					break;
				}

				// Integer
				if((listVariable.getValue(i).getType() == SVT::INTEGER) &&
				   (args[1].getType() == SVT::INTEGER) &&
				   (listVariable.getValue(i).getInteger() == args[1].getInteger()))
				{
					hasFoundValue = true;
					break;
				}

				// Boolean
				if((listVariable.getValue(i).getType() == SVT::BOOLEAN) &&
				   (args[1].getType() == SVT::BOOLEAN) &&
				   (listVariable.getValue(i).getBoolean() == args[1].getBoolean()))
				{
					hasFoundValue = true;
					break;
				}
			}

			// Return find result
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, hasFoundValue));
		}
	}
	else if(functionName == "misc:list_index")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, 2))
		{
			// List name must be string
			if(args[0].getType() != SVT::STRING)
			{
				_throwScriptError("incorrect argument type!");
				return returnValues;
			}

			// Check if variable does not exist
			auto listName = args[0].getString();
			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwScriptError("variable \"" + listName + "\" not existing!");
				return returnValues;
			}

			// Check if variable is not a list
			auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
			if(listVariable.getType() == ScriptVariableType::SINGLE)
			{
				_throwScriptError("variable \"" + listName + "\" is not of type LIST!");
				return returnValues;
			}

			// Try to find value index
			int foundIndex = -1;
			for(unsigned int i = 0; i < listVariable.getValueCount(); i++)
			{
				// String
				if((listVariable.getValue(i).getType() == SVT::STRING) &&
				   (args[1].getType() == SVT::STRING) &&
				   (listVariable.getValue(i).getString() == args[1].getString()))
				{
					foundIndex = i;
					break;
				}

				// Decimal
				if((listVariable.getValue(i).getType() == SVT::DECIMAL) &&
				   (args[1].getType() == SVT::DECIMAL) &&
				   (listVariable.getValue(i).getDecimal() == args[1].getDecimal()))
				{
					foundIndex = i;
					break;
				}

				// Integer
				if((listVariable.getValue(i).getType() == SVT::INTEGER) &&
				   (args[1].getType() == SVT::INTEGER) &&
				   (listVariable.getValue(i).getInteger() == args[1].getInteger()))
				{
					foundIndex = i;
					break;
				}

				// Boolean
				if((listVariable.getValue(i).getType() == SVT::BOOLEAN) &&
				   (args[1].getType() == SVT::BOOLEAN) &&
				   (listVariable.getValue(i).getBoolean() == args[1].getBoolean()))
				{
					foundIndex = i;
					break;
				}
			}

			// Return find result
			returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, foundIndex));
		}
	}
	else if(functionName == "misc:list_min")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			// Temporary values
			auto listName = args[0].getString();

			// Check if variable not existing
			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwScriptError("variable \"" + listName + "\" not existing!");
				return returnValues;
			}

			// Check if variable is not a list
			auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
			if(listVariable.getType() == ScriptVariableType::SINGLE)
			{
				_throwScriptError("variable \"" + listName + "\" is not of type LIST!");
				return returnValues;
			}

			// Check if list is empty
			if(listVariable.getValueCount() == 0)
			{
				_throwScriptError("LIST \"" + listName + "\" is empty!");
				return returnValues;
			}

			// Check if list values are of different types
			auto type = listVariable.getValue(0).getType();
			for(unsigned int i = 0; i < listVariable.getValueCount(); i++)
			{
				if(listVariable.getValue(i).getType() != type)
				{
					_throwScriptError("values inside LIST \"" + listName + "\" not of same type!");
					return returnValues;
				}
			}

			// Determine type of list values
			if(type == ScriptValueType::INTEGER)
			{
				// Compose raw values
				vector<int> rawValues;
				for(unsigned int i = 0; i < listVariable.getValueCount(); i++)
				{
					rawValues.push_back(listVariable.getValue(i).getInteger());
				}

				// Return
				auto result = *min_element(begin(rawValues), end(rawValues));
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
			}
			else if(type == ScriptValueType::DECIMAL)
			{
				// Compose raw values
				vector<float> rawValues;
				for(unsigned int i = 0; i < listVariable.getValueCount(); i++)
				{
					rawValues.push_back(listVariable.getValue(i).getDecimal());
				}

				// Return
				auto result = *min_element(begin(rawValues), end(rawValues));
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
			else
			{
				_throwScriptError("values inside LIST \"" + listName + "\" must be INT or DEC!");
				return returnValues;
			}
		}
	}
	else if(functionName == "misc:list_max")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			// Temporary values
			auto listName = args[0].getString();

			// Check if variable not existing
			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwScriptError("variable \"" + listName + "\" not existing!");
				return returnValues;
			}

			// Check if variable is not a list
			auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
			if(listVariable.getType() == ScriptVariableType::SINGLE)
			{
				_throwScriptError("variable \"" + listName + "\" is not of type LIST!");
				return returnValues;
			}

			// Check if list is empty
			if(listVariable.getValueCount() == 0)
			{
				_throwScriptError("LIST \"" + listName + "\" is empty!");
				return returnValues;
			}

			// Check if list values are of different types
			auto type = listVariable.getValue(0).getType();
			for(unsigned int i = 0; i < listVariable.getValueCount(); i++)
			{
				if(listVariable.getValue(i).getType() != type)
				{
					_throwScriptError("values inside LIST \"" + listName + "\" not of same type!");
					return returnValues;
				}
			}

			// Determine type of list values
			if(type == ScriptValueType::INTEGER)
			{
				// Compose raw values
				vector<int> rawValues;
				for(unsigned int i = 0; i < listVariable.getValueCount(); i++)
				{
					rawValues.push_back(listVariable.getValue(i).getInteger());
				}

				// Return
				auto result = *max_element(begin(rawValues), end(rawValues));
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
			}
			else if(type == ScriptValueType::DECIMAL)
			{
				// Compose raw values
				vector<float> rawValues;
				for(unsigned int i = 0; i < listVariable.getValueCount(); i++)
				{
					rawValues.push_back(listVariable.getValue(i).getDecimal());
				}

				// Return
				auto result = *max_element(begin(rawValues), end(rawValues));
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
			else
			{
				_throwScriptError("values inside LIST \"" + listName + "\" must be INT or DEC!");
				return returnValues;
			}
		}
	}
	else if(functionName == "misc:list_reverse")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			// Temporary values
			auto listName = args[0].getString();

			// Check if variable not existing
			if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
			{
				_throwScriptError("variable \"" + listName + "\" not existing!");
				return returnValues;
			}

			// Check if variable is not a list
			auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
			if(listVariable.getType() == ScriptVariableType::SINGLE)
			{
				_throwScriptError("variable \"" + listName + "\" is not of type LIST!");
				return returnValues;
			}

			// Return values in reversed order
			vector<ScriptValue> values = {};
			for(int i = (static_cast<int>(listVariable.getValueCount()) - 1); i > -1; i--)
			{
				returnValues.push_back(listVariable.getValue(i));
			}
		}
	}
	else if(functionName == "misc:string_concat")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, args[0].getString() + args[1].getString()));
		}
	}
	else if(functionName == "misc:string_get_size")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto result = args[0].getString().size();
			returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
		}
	}
	else if(functionName == "misc:string_contains")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto result = (args[0].getString().find(args[1].getString()) != string::npos);
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "misc:string_get_part")
	{
		auto types = {SVT::STRING, SVT::INTEGER, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			// Validate index
			if((args[1].getInteger() < 0) ||
			   (args[1].getInteger() > static_cast<int>(args[0].getString().size())) ||
			   (args[2].getInteger() < 0))
			{
				_throwScriptError("incorrect string part index/indices!");
				return returnValues;
			}

			auto result = args[0].getString().substr(args[1].getInteger(), args[2].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if(functionName == "misc:string_split")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			// Validate splitter
			if((args[1].getString().size() > 1) || (args[0].getString().find(args[1].getString()) == string::npos))
			{
				_throwScriptError("string splitter not found!");
				return returnValues;
			}

			// Return all split string parts
			string fullString = args[0].getString();
			string splitter = args[1].getString();
			string stringPart = "";
			for(size_t i = 0; i < fullString.size(); i++)
			{
				if(fullString[i] == splitter.back()) // Found splitter
				{
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, stringPart));
					stringPart = "";
				}
				else if(i == (fullString.size() - 1)) // End of string
				{
					stringPart += fullString[i];
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, stringPart));
				}
				else // Add to string part
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
			// Compose string in reverse
			string result = "";
			string content = args[0].getString();
			reverse(content.begin(), content.end());
			for(const auto& character : content)
			{
				result += character;
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if(functionName == "misc:get_random_integer")
	{
		auto types = {SVT::INTEGER, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto result = Math::getRandomNumber(args[0].getInteger(), args[1].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
		}
	}
	else if(functionName == "misc:get_random_decimal")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto result = Math::getRandomNumber(args[0].getDecimal(), args[1].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else
	{
		_throwScriptError("misc function not existing!");
	}

	return returnValues;
}