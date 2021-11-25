#include "script_interpreter.hpp"
#include "tools.hpp"

using SVT = ScriptValueType;

const vector<ScriptValue> ScriptInterpreter::_processMiscellaneousFunctionCall(const string& scriptLine)
{
	// Temporary values
	vector<ScriptValue> returnValues;
	auto openingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), '(');
	auto closingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), ')');

	// Check if function call has opening & closing parentheses
	if(openingParanthesisFound != scriptLine.end() && closingParanthesisFound != scriptLine.end())
	{
		// Check if function call ends with a paranthesis
		if(scriptLine.back() != ')')
		{
			_throwScriptError("function call must end with a paranthesis!");
		}
		else
		{
			// Extract arguments from argument string
			auto parenthesisIndex = static_cast<unsigned int>(distance(scriptLine.begin(), openingParanthesisFound));
			string argumentString = scriptLine.substr(static_cast<size_t>(parenthesisIndex + 1));
			argumentString.pop_back();
			auto arguments = _extractValuesFromListString(argumentString);

			// Check if argument extraction went well
			if(!_hasThrownError)
			{
				// Temporary values
				auto functionName = scriptLine.substr(0, parenthesisIndex);

				// Determine type of function
				if(functionName == "misc:list_concat")
				{
					auto types = {SVT::STRING, SVT::STRING};

					// Validate arguments
					if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
					{
						// Temporary values
						auto firstName = arguments[0].getString();
						auto secondName = arguments[1].getString();

						// Check if first variable not existing
						if(!_isLocalVariableExisting(firstName) && !_isGlobalVariableExisting(firstName))
						{
							_throwScriptError("list variable \"" + firstName + "\" not found!");
							return returnValues;
						}

						// Check if second variable not existing
						if(!_isLocalVariableExisting(secondName) && !_isGlobalVariableExisting(secondName))
						{
							_throwScriptError("list variable \"" + secondName + "\" not found!");
							return returnValues;
						}

						// Check if first variable is a list
						auto firstListVariable = (_isLocalVariableExisting(firstName) ? _getLocalVariable(firstName) : _getGlobalVariable(firstName));
						if(firstListVariable.getType() == ScriptVariableType::SINGLE)
						{
							_throwScriptError("variable \"" + firstName + "\" is not a list!");
							return returnValues;
						}

						// Check if second variable is a list
						auto secondListVariable = (_isLocalVariableExisting(secondName) ? _getLocalVariable(secondName) : _getGlobalVariable(secondName));
						if(secondListVariable.getType() == ScriptVariableType::SINGLE)
						{
							_throwScriptError("variable \"" + secondName + "\" is not a list!");
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

					// Validate arguments
					if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
					{
						// Temporary values
						auto listName = arguments[0].getString();

						// Check if variable not existing
						if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
						{
							_throwScriptError("list variable \"" + listName + "\" not found!");
							return returnValues;
						}

						// Check if variable is not a list
						auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
						if(listVariable.getType() == ScriptVariableType::SINGLE)
						{
							_throwScriptError("variable \"" + listName + "\" is not a list!");
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

					// Validate arguments
					if(_validateArgumentCount(arguments, 2))
					{
						// List name must be string
						if(arguments[0].getType() != SVT::STRING)
						{
							_throwScriptError("wrong value type(s)!");
							return returnValues;
						}

						// Check if variable does not exist
						auto listName = arguments[0].getString();
						if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
						{
							_throwScriptError("list variable \"" + listName + "\" not found!");
							return returnValues;
						}

						// Check if variable is not a list
						auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
						if(listVariable.getType() == ScriptVariableType::SINGLE)
						{
							_throwScriptError("variable \"" + listName + "\" is not a list!");
							return returnValues;
						}

						// Try to find value
						bool hasFoundValue = false;
						for(unsigned int i = 0; i < listVariable.getValueCount(); i++)
						{
							// String
							if((listVariable.getValue(i).getType() == SVT::STRING) &&
							   (arguments[1].getType() == SVT::STRING) &&
							   (listVariable.getValue(i).getString() == arguments[1].getString()))
							{
								hasFoundValue = true;
								break;
							}

							// Decimal
							if((listVariable.getValue(i).getType() == SVT::DECIMAL) &&
							   (arguments[1].getType() == SVT::DECIMAL) &&
							   (listVariable.getValue(i).getDecimal() == arguments[1].getDecimal()))
							{
								hasFoundValue = true;
								break;
							}

							// Integer
							if((listVariable.getValue(i).getType() == SVT::INTEGER) &&
							   (arguments[1].getType() == SVT::INTEGER) &&
							   (listVariable.getValue(i).getInteger() == arguments[1].getInteger()))
							{
								hasFoundValue = true;
								break;
							}

							// Boolean
							if((listVariable.getValue(i).getType() == SVT::BOOLEAN) &&
							   (arguments[1].getType() == SVT::BOOLEAN) &&
							   (listVariable.getValue(i).getBoolean() == arguments[1].getBoolean()))
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

					// Validate arguments
					if(_validateArgumentCount(arguments, 2))
					{
						// List name must be string
						if(arguments[0].getType() != SVT::STRING)
						{
							_throwScriptError("wrong value type(s)!");
							return returnValues;
						}

						// Check if variable does not exist
						auto listName = arguments[0].getString();
						if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
						{
							_throwScriptError("list variable \"" + listName + "\" not found!");
							return returnValues;
						}

						// Check if variable is not a list
						auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
						if(listVariable.getType() == ScriptVariableType::SINGLE)
						{
							_throwScriptError("variable \"" + listName + "\" is not a list!");
							return returnValues;
						}

						// Try to find value index
						int foundIndex = -1;
						for(unsigned int i = 0; i < listVariable.getValueCount(); i++)
						{
							// String
							if((listVariable.getValue(i).getType() == SVT::STRING) &&
							   (arguments[1].getType() == SVT::STRING) &&
							   (listVariable.getValue(i).getString() == arguments[1].getString()))
							{
								foundIndex = i;
								break;
							}

							// Decimal
							if((listVariable.getValue(i).getType() == SVT::DECIMAL) &&
							   (arguments[1].getType() == SVT::DECIMAL) &&
							   (listVariable.getValue(i).getDecimal() == arguments[1].getDecimal()))
							{
								foundIndex = i;
								break;
							}

							// Integer
							if((listVariable.getValue(i).getType() == SVT::INTEGER) &&
							   (arguments[1].getType() == SVT::INTEGER) &&
							   (listVariable.getValue(i).getInteger() == arguments[1].getInteger()))
							{
								foundIndex = i;
								break;
							}

							// Boolean
							if((listVariable.getValue(i).getType() == SVT::BOOLEAN) &&
							   (arguments[1].getType() == SVT::BOOLEAN) &&
							   (listVariable.getValue(i).getBoolean() == arguments[1].getBoolean()))
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

					// Validate arguments
					if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
					{
						// Temporary values
						auto listName = arguments[0].getString();

						// Check if variable not existing
						if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
						{
							_throwScriptError("list variable \"" + listName + "\" not found!");
							return returnValues;
						}

						// Check if variable is not a list
						auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
						if(listVariable.getType() == ScriptVariableType::SINGLE)
						{
							_throwScriptError("variable \"" + listName + "\" is not a list!");
							return returnValues;
						}

						// Check if list is empty
						if(listVariable.getValueCount() == 0)
						{
							_throwScriptError("list is empty!");
							return returnValues;
						}

						// Check if list values are of different types
						auto type = listVariable.getValue(0).getType();
						for(unsigned int i = 0; i < listVariable.getValueCount(); i++)
						{
							if(listVariable.getValue(i).getType() != type)
							{
								_throwScriptError("list values are not of the same type!");
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
							auto result = *std::min_element(std::begin(rawValues), std::end(rawValues));
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
							auto result = *std::min_element(std::begin(rawValues), std::end(rawValues));
							returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
						}
						else
						{
							_throwScriptError("LIST values must be INT or DEC!");
							return returnValues;
						}
					}
				}
				else if(functionName == "misc:list_max")
				{
					auto types = {SVT::STRING};

					// Validate arguments
					if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
					{
						// Temporary values
						auto listName = arguments[0].getString();

						// Check if variable not existing
						if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
						{
							_throwScriptError("list variable \"" + listName + "\" not found!");
							return returnValues;
						}

						// Check if variable is not a list
						auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
						if(listVariable.getType() == ScriptVariableType::SINGLE)
						{
							_throwScriptError("variable \"" + listName + "\" is not a list!");
							return returnValues;
						}

						// Check if list is empty
						if(listVariable.getValueCount() == 0)
						{
							_throwScriptError("list is empty!");
							return returnValues;
						}

						// Check if list values are of different types
						auto type = listVariable.getValue(0).getType();
						for(unsigned int i = 0; i < listVariable.getValueCount(); i++)
						{
							if(listVariable.getValue(i).getType() != type)
							{
								_throwScriptError("list values are not of the same type!");
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
							auto result = *std::max_element(std::begin(rawValues), std::end(rawValues));
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
							auto result = *std::max_element(std::begin(rawValues), std::end(rawValues));
							returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
						}
						else
						{
							_throwScriptError("LIST values must be INT or DEC!");
							return returnValues;
						}
					}
				}
				else if(functionName == "misc:list_reverse")
				{
					auto types = {SVT::STRING};

					// Validate arguments
					if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
					{
						// Temporary values
						auto listName = arguments[0].getString();

						// Check if variable not existing
						if(!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
						{
							_throwScriptError("list variable \"" + listName + "\" not found!");
							return returnValues;
						}

						// Check if variable is not a list
						auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
						if(listVariable.getType() == ScriptVariableType::SINGLE)
						{
							_throwScriptError("variable \"" + listName + "\" is not a list!");
							return returnValues;
						}

						// Return values in reversed order
						vector<ScriptValue> values = {};
						for(unsigned int i = (listVariable.getValueCount() - 1); i >= 0; i--)
						{
							returnValues.push_back(listVariable.getValue(i));
						}
					}
				}
				else if(functionName == "misc:string_concat")
				{
					auto types = {SVT::STRING, SVT::STRING};

					// Validate arguments
					if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
					{
						returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, arguments[0].getString() + arguments[1].getString()));
					}
				}
				else if(functionName == "misc:string_get_size")
				{
					auto types = {SVT::STRING};

					// Validate arguments
					if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
					{
						auto result = arguments[0].getString().size();
						returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
					}
				}
				else if(functionName == "misc:string_contains")
				{
					auto types = {SVT::STRING, SVT::STRING};

					// Validate arguments
					if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
					{
						auto result = (arguments[0].getString().find(arguments[1].getString()) != string::npos);
						returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
					}
				}
				else if(functionName == "misc:string_get_part")
				{
					auto types = {SVT::STRING, SVT::INTEGER, SVT::INTEGER};

					// Validate arguments
					if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
					{
						// Validate index
						if((arguments[1].getInteger() < 0) ||
						   (arguments[1].getInteger() > static_cast<int>(arguments[0].getString().size())) ||
						   (arguments[2].getInteger() < 0))
						{
							_throwScriptError("incorrect string part index/indices!");
							return returnValues;
						}

						auto result = arguments[0].getString().substr(arguments[1].getInteger(), arguments[2].getInteger());
						returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
					}
				}
				else if(functionName == "misc:string_split")
				{
					auto types = {SVT::STRING, SVT::STRING};

					// Validate arguments
					if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
					{
						// Validate splitter
						if((arguments[1].getString().size() > 1) ||
						   (arguments[0].getString().find(arguments[1].getString()) == string::npos))
						{
							_throwScriptError("string splitter not found!");
							return returnValues;
						}

						// Return all split string parts
						string fullString = arguments[0].getString();
						string splitter = arguments[1].getString();
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

					// Validate arguments
					if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
					{
						// Compose string in reverse
						string result = "";
						string content = arguments[0].getString();
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

					// Validate arguments
					if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
					{
						auto result = Math::getRandomInteger(arguments[0].getInteger(), arguments[1].getInteger());
						returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
					}
				}
				else if(functionName == "misc:get_random_decimal")
				{
					auto types = {SVT::DECIMAL, SVT::DECIMAL};

					// Validate arguments
					if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
					{
						auto result = Math::getRandomFloat(arguments[0].getDecimal(), arguments[1].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
					}
				}
				else
				{
					_throwScriptError("misc function not found!");
				}
			}
		}
	}
	else
	{
		_throwScriptError("invalid parantheses syntax!");
	}

	return returnValues;
}