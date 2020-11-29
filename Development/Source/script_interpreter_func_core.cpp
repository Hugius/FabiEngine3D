#include "script_interpreter.hpp"

vector<ScriptValue> ScriptInterpreter::_processEngineFunctionCall(const string& scriptLine)
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
			auto arguments = _extractArguments(argumentString);

			// Check if argument extraction went well
			if (!_hasThrownError)
			{
				auto functionName = scriptLine.substr(0, parenthesisIndex);
				bool executed = false;

				// Possibly execute FE3D function
				executed = executed || _executeFe3dInputFunction(functionName, arguments, returnValues);
				executed = executed || _executeFe3dCameraFunction(functionName, arguments, returnValues);
				executed = executed || _executeFe3dCollisionFunction(functionName, arguments, returnValues);
				executed = executed || _executeFe3dMiscFunction(functionName, arguments, returnValues);
				
				// Check if function call exists
				if(!executed)
				{
					_throwScriptError("FE3D function not found!");
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

vector<ScriptValue> ScriptInterpreter::_processMathematicalFunctionCall(const string& scriptLine)
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
			auto arguments = _extractArguments(argumentString);

			// Check if argument extraction went well
			if (!_hasThrownError)
			{
				auto functionName = scriptLine.substr(0, parenthesisIndex);

				// Determine type of function	
				if (functionName == "math:tan")
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						float angle = _fe3d.misc_degreesToRadians(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, std::tan(angle)));
					}
				}
				else if (functionName == "math:sin")
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						float angle = _fe3d.misc_degreesToRadians(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, std::sin(angle)));
					}
				}
				else if (functionName == "math:cos")
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						float angle = _fe3d.misc_degreesToRadians(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, std::cos(angle)));
					}
				}
				else if (functionName == "math:pow")
				{
					if (_validateArgumentAmount(arguments, 2))
					{
						if (arguments[0].getType() == ScriptValueType::INTEGER && arguments[1].getType() == ScriptValueType::INTEGER)
						{
							int result = static_cast<int>(std::pow(arguments[0].getInteger(), arguments[1].getInteger()));
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
						}
						else if (arguments[0].getType() == ScriptValueType::DECIMAL && arguments[1].getType() == ScriptValueType::INTEGER)
						{
							float result = std::pow(arguments[0].getDecimal(), arguments[1].getInteger());
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
						}
						else
						{
							_throwScriptError("wrong argument type(s)!");
						}
					}
				}
				else if (functionName == "math:min")
				{
					if (_validateArgumentAmount(arguments, 2))
					{
						if (arguments[0].getType() == ScriptValueType::INTEGER && arguments[1].getType() == ScriptValueType::INTEGER)
						{
							int result = std::min(arguments[0].getInteger(), arguments[1].getInteger());
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
						}
						else if (arguments[0].getType() == ScriptValueType::DECIMAL && arguments[1].getType() == ScriptValueType::DECIMAL)
						{
							float result = std::min(arguments[0].getDecimal(), arguments[1].getDecimal());
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
						}
						else
						{
							_throwScriptError("wrong argument type(s)!");
						}
					}
				}
				else if (functionName == "math:max")
				{
					if (_validateArgumentAmount(arguments, 2))
					{
						if (arguments[0].getType() == ScriptValueType::INTEGER && arguments[1].getType() == ScriptValueType::INTEGER)
						{
							int result = std::max(arguments[0].getInteger(), arguments[1].getInteger());
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
						}
						else if (arguments[0].getType() == ScriptValueType::DECIMAL && arguments[1].getType() == ScriptValueType::DECIMAL)
						{
							float result = std::max(arguments[0].getDecimal(), arguments[1].getDecimal());
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
						}
						else
						{
							_throwScriptError("wrong argument type(s)!");
						}
					}
				}
				else if (functionName == "math:sqrt")
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, std::sqrtf(arguments[0].getDecimal())));
					}
				}
				else
				{
					_throwScriptError("MATH function not found!");
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
			auto arguments = _extractArguments(argumentString);

			// Check if argument extraction went well
			if (!_hasThrownError)
			{
				auto functionName = scriptLine.substr(0, parenthesisIndex);

				// Determine type of function
				if (functionName == "misc:to_string")
				{
					if (_validateArgumentAmount(arguments, 1))
					{
						if (arguments[0].getType() == ScriptValueType::INTEGER)
						{
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, to_string(arguments[0].getInteger())));
						}
						else if (arguments[0].getType() == ScriptValueType::DECIMAL)
						{
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, to_string(arguments[0].getDecimal())));
						}
						else
						{
							_throwScriptError("wrong argument type(s)!");
						}
					}
				}
				else if (functionName == "misc:concat_strings")
				{
					auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, arguments[0].getString() + arguments[1].getString()));
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