#include "script_interpreter.hpp"

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
			unsigned int parenthesisIndex = std::distance(scriptLine.begin(), openingParanthesisFound);
			string argumentString = scriptLine.substr(parenthesisIndex + 1);
			argumentString.pop_back();
			auto arguments = _extractValuesFromListString(argumentString);

			// Check if argument extraction went well
			if (!_hasThrownError)
			{
				auto functionName = scriptLine.substr(0, parenthesisIndex);

				// Determine type of function
				if (functionName == "misc:concat_strings")
				{
					auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

					if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, arguments[0].getString() + arguments[1].getString()));
					}
				}
				else if (functionName == "misc:get_list_size") // Get the size of a list variable
				{
					auto types = { ScriptValueType::STRING };

					if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
					{
						auto nameString = arguments[0].getString();

						// Check if variable exists
						if (!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
						{
							_throwScriptError("list variable \"" + nameString + "\" not found!");
							return returnValues;
						}

						// Check if variable is not a list
						auto listVariable = _isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString);
						if (listVariable.getType() == ScriptVariableType::SINGLE)
						{
							_throwScriptError("variable \"" + nameString + "\" is not a list!");
							return returnValues;
						}

						// Return list size
						auto result = listVariable.getValueCount();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, static_cast<int>(result)));
					}
				}
				else if (functionName == "misc:get_string_size") // Get the size of a string variable
				{
					auto types = { ScriptValueType::STRING };

					if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
					{
						// Return string size
						auto result = arguments[0].getString().size();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, static_cast<int>(result)));
					}
				}
				else if (functionName == "misc:get_string_part") // Cut a part from a string
				{
					auto types = { ScriptValueType::STRING, ScriptValueType::INTEGER, ScriptValueType::INTEGER };

					if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
					{
						// Validate index
						if (arguments[1].getInteger() < static_cast<int>(arguments[0].getString().size()) && arguments[1].getInteger() >= 0)
						{
							auto result = arguments[0].getString().substr(arguments[1].getInteger(), arguments[2].getInteger());
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
						}
						else
						{
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, ""));
						}
					}
				}
				else if (functionName == "misc:get_unique_integer") // Unique integer
				{
					auto types =
					{
						ScriptValueType::INTEGER, // Min
						ScriptValueType::INTEGER  // Max
					};

					if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
					{
						auto result = _fe3d.misc_getUniqueInt(arguments[0].getInteger(), arguments[1].getInteger());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
					}
				}
				else if (functionName == "misc:get_random_integer") // Random integer
				{
					auto types =
					{
						ScriptValueType::INTEGER, // Min
						ScriptValueType::INTEGER  // Max
					};

					if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
					{
						auto result = _fe3d.misc_getRandomInt(arguments[0].getInteger(), arguments[1].getInteger());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
					}
				}
				else if (functionName == "misc:get_random_decimal") // Random float
				{
					auto types =
					{
						ScriptValueType::DECIMAL, // Min
						ScriptValueType::DECIMAL  // Max
					};

					if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
					{
						auto result = _fe3d.misc_getRandomFloat(arguments[0].getDecimal(), arguments[1].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
					}
				}
				else if (functionName == "misc:time_interval") // Time interval
				{
					auto types = { ScriptValueType::STRING, ScriptValueType::INTEGER };

					if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
					{
						auto result = _fe3d.misc_checkInterval(arguments[0].getString(), arguments[1].getInteger());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
					}
				}
				else
				{
					_throwScriptError("MISC function not found!");
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