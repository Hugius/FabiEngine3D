#include "script_interpreter.hpp"
#include "tools.hpp"

vector<ScriptValue> ScriptInterpreter::_processMiscellaneousFunctionCall(const string& scriptLine)
{
	// Temporary values
	vector<ScriptValue> returnValues;
	auto openingParanthesisFound = std::find(scriptLine.begin(), scriptLine.end(), '(');
	auto closingParanthesisFound = std::find(scriptLine.begin(), scriptLine.end(), ')');

	// Check if function call has opening & closing parentheses
	if (openingParanthesisFound != scriptLine.end() && closingParanthesisFound != scriptLine.end())
	{
		// Check if function call ends with a paranthesis
		if (scriptLine.back() != ')')
		{
			_throwScriptError("function call must end with a paranthesis!");
		}
		else
		{
			// Extract arguments from argument string
			auto parenthesisIndex = static_cast<unsigned int>(std::distance(scriptLine.begin(), openingParanthesisFound));
			string argumentString = scriptLine.substr(parenthesisIndex + 1);
			argumentString.pop_back();
			auto arguments = _extractValuesFromListString(argumentString);

			// Check if argument extraction went well
			if (!_hasThrownError)
			{
				auto functionName = scriptLine.substr(0, parenthesisIndex);

				// Determine type of function
				if (functionName == "misc:list_concat")
				{
					auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

					if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						// Temporary values
						auto firstName = arguments[0].getString();
						auto secondName = arguments[1].getString();

						// Check if first variable not existing
						if (!_isLocalVariableExisting(firstName) && !_isGlobalVariableExisting(firstName))
						{
							_throwScriptError("list variable \"" + firstName + "\" not found!");
							return returnValues;
						}

						// Check if second variable not existing
						if (!_isLocalVariableExisting(secondName) && !_isGlobalVariableExisting(secondName))
						{
							_throwScriptError("list variable \"" + secondName + "\" not found!");
							return returnValues;
						}

						// Check if first variable is a list
						auto firstListVariable = (_isLocalVariableExisting(firstName) ? _getLocalVariable(firstName) : _getGlobalVariable(firstName));
						if (firstListVariable.getType() == ScriptVariableType::SINGLE)
						{
							_throwScriptError("variable \"" + firstName + "\" is not a list!");
							return returnValues;
						}

						// Check if second variable is a list
						auto secondListVariable = (_isLocalVariableExisting(secondName) ? _getLocalVariable(secondName) : _getGlobalVariable(secondName));
						if (secondListVariable.getType() == ScriptVariableType::SINGLE)
						{
							_throwScriptError("variable \"" + secondName + "\" is not a list!");
							return returnValues;
						}

						// Return concatenated lists
						auto firstListValues = firstListVariable.getValues();
						auto secondListValues = secondListVariable.getValues();
						firstListValues.insert(firstListValues.end(), secondListValues.begin(), secondListValues.end());
						for (const auto& value : firstListValues)
						{
							returnValues.push_back(*value);
						}
					}
				}
				else if (functionName == "misc:list_get_size")
				{
					auto types = { ScriptValueType::STRING };

					if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						// Temporary values
						auto listName = arguments[0].getString();

						// Check if variable not existing
						if (!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
						{
							_throwScriptError("list variable \"" + listName + "\" not found!");
							return returnValues;
						}

						// Check if variable is not a list
						auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
						if (listVariable.getType() == ScriptVariableType::SINGLE)
						{
							_throwScriptError("variable \"" + listName + "\" is not a list!");
							return returnValues;
						}

						// Return list size
						auto result = listVariable.getValueCount();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, static_cast<int>(result)));
					}
				}
				else if (functionName == "misc:list_contains")
				{
					auto types = { ScriptValueType::STRING };

					if (_validateListValueAmount(arguments, 2))
					{
						// List name must be string
						if (arguments[0].getType() != ScriptValueType::STRING)
						{
							_throwScriptError("wrong value type(s)!");
							return returnValues;
						}

						// Check if variable does not exist
						auto listName = arguments[0].getString();
						if (!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
						{
							_throwScriptError("list variable \"" + listName + "\" not found!");
							return returnValues;
						}

						// Check if variable is not a list
						auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
						if (listVariable.getType() == ScriptVariableType::SINGLE)
						{
							_throwScriptError("variable \"" + listName + "\" is not a list!");
							return returnValues;
						}

						// Try to find value
						bool foundValue = false;
						for (const auto& value : listVariable.getValues())
						{
							if
								(
									(value->getType() == ScriptValueType::VEC3 &&
									arguments[1].getType() == ScriptValueType::VEC3 &&
									value->getVec3() == arguments[1].getVec3())

									||

									(value->getType() == ScriptValueType::STRING &&
									arguments[1].getType() == ScriptValueType::STRING &&
									value->getString() == arguments[1].getString())

									||

									(value->getType() == ScriptValueType::DECIMAL &&
									arguments[1].getType() == ScriptValueType::DECIMAL &&
									value->getDecimal() == arguments[1].getDecimal())

									||

									(value->getType() == ScriptValueType::INTEGER &&
									arguments[1].getType() == ScriptValueType::INTEGER &&
									value->getInteger() == arguments[1].getInteger())

									||

									(value->getType() == ScriptValueType::BOOLEAN &&
									arguments[1].getType() == ScriptValueType::BOOLEAN &&
									value->getBoolean() == arguments[1].getBoolean())
								)
							{
								foundValue = true;
								break;
							}
						}

						// Return find result
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, foundValue));
					}
				}
				else if (functionName == "misc:list_reverse")
				{
					auto types = { ScriptValueType::STRING };

					if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						// Temporary values
						auto listName = arguments[0].getString();

						// Check if variable not existing
						if (!_isLocalVariableExisting(listName) && !_isGlobalVariableExisting(listName))
						{
							_throwScriptError("list variable \"" + listName + "\" not found!");
							return returnValues;
						}

						// Check if variable is not a list
						auto listVariable = (_isLocalVariableExisting(listName) ? _getLocalVariable(listName) : _getGlobalVariable(listName));
						if (listVariable.getType() == ScriptVariableType::SINGLE)
						{
							_throwScriptError("variable \"" + listName + "\" is not a list!");
							return returnValues;
						}

						// Return list elements in reverse order
						auto values = listVariable.getValues();
						reverse(values.begin(), values.end());
						for (const auto& value : values)
						{
							returnValues.push_back(*value);
						}
					}
				}
				else if (functionName == "misc:string_concat")
				{
					auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

					if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, arguments[0].getString() + arguments[1].getString()));
					}
				}
				else if (functionName == "misc:string_get_size")
				{
					auto types = { ScriptValueType::STRING };

					if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						auto result = arguments[0].getString().size();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, static_cast<int>(result)));
					}
				}
				else if (functionName == "misc:string_contains")
				{
					auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

					if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						auto result = (arguments[0].getString().find(arguments[1].getString()) != string::npos);
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
					}
				}
				else if (functionName == "misc:string_get_part")
				{
					auto types = { ScriptValueType::STRING, ScriptValueType::INTEGER, ScriptValueType::INTEGER };

					if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						// Validate index
						if ((arguments[1].getInteger() < 0) ||
							(arguments[1].getInteger() > static_cast<int>(arguments[0].getString().size())) ||
							(arguments[2].getInteger() < 0))
						{
							_throwScriptError("incorrect string part index/indices!");
							return returnValues;
						}

						auto result = arguments[0].getString().substr(arguments[1].getInteger(), arguments[2].getInteger());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
					}
				}
				else if (functionName == "misc:string_split")
				{
					auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

					if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						// Validate splitter
						if ((arguments[1].getString().size() > 1) ||
							arguments[0].getString().find(arguments[1].getString()) == string::npos)
						{
							_throwScriptError("incorrect string splitter!");
							return returnValues;
						}

						// Return all split string parts
						string fullString = arguments[0].getString();
						string splitter = arguments[1].getString();
						string stringPart = "";
						for (size_t i = 0; i < fullString.size(); i++)
						{
							if (fullString[i] == splitter.back()) // Found splitter
							{
								returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, stringPart));
								stringPart = "";
							}
							else if (i == (fullString.size() - 1)) // End of string
							{
								stringPart += fullString[i];
								returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, stringPart));
							}
							else // Add to string part
							{
								stringPart += fullString[i];
							}
						}						
					}
				}
				else if (functionName == "misc:string_reverse")
				{
					auto types = { ScriptValueType::STRING };

					if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						// Compose string in reverse
						string result = "";
						string content = arguments[0].getString();
						reverse(content.begin(), content.end());
						for (const auto& character : content)
						{
							result += character;
						}

						// Return
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
					}
				}
				else if (functionName == "misc:get_random_integer")
				{
					auto types =
					{
						ScriptValueType::INTEGER, // Min
						ScriptValueType::INTEGER  // Max
					};

					if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						auto result = Tools::getRandomInteger(arguments[0].getInteger(), arguments[1].getInteger());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
					}
				}
				else if (functionName == "misc:get_random_decimal")
				{
					auto types =
					{
						ScriptValueType::DECIMAL, // Min
						ScriptValueType::DECIMAL  // Max
					};

					if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						auto result = _fe3d.misc_getRandomFloat(arguments[0].getDecimal(), arguments[1].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
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