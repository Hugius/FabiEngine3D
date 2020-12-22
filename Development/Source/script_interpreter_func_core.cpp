#include "script_interpreter.hpp"

#include <algorithm>

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
			auto arguments = _extractValuesFromListString(argumentString);

			// Check if argument extraction went well
			if (!_hasThrownError)
			{
				auto functionName = scriptLine.substr(0, parenthesisIndex);
				bool executed = false;

				// Possibly execute FE3D function
				executed = executed || _executeFe3dInputFunction(functionName, arguments, returnValues);
				executed = executed || _executeFe3dCameraFunction(functionName, arguments, returnValues);
				executed = executed || _executeFe3dSkyEntityFunction(functionName, arguments, returnValues);
				executed = executed || _executeFe3dTerrainEntityFunction(functionName, arguments, returnValues);
				executed = executed || _executeFe3dWaterEntityFunction(functionName, arguments, returnValues);
				executed = executed || _executeFe3dGameEntityFunction(functionName, arguments, returnValues);
				executed = executed || _executeFe3dBillboardEntityFunction(functionName, arguments, returnValues);
				executed = executed || _executeFe3dAabbEntityFunction(functionName, arguments, returnValues);
				executed = executed || _executeFe3dLightEntityFunction(functionName, arguments, returnValues);
				executed = executed || _executeFe3dGuiEntityFunction(functionName, arguments, returnValues);
				executed = executed || _executeFe3dTextEntityFunction(functionName, arguments, returnValues);
				executed = executed || _executeFe3dAudioEntityFunction(functionName, arguments, returnValues);
				executed = executed || _executeFe3dAnimationFunction(functionName, arguments, returnValues);
				executed = executed || _executeFe3dPhysicsFunction(functionName, arguments, returnValues);
				executed = executed || _executeFe3dLightingFunction(functionName, arguments, returnValues);
				executed = executed || _executeFe3dMusicFunction(functionName, arguments, returnValues);
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
			auto arguments = _extractValuesFromListString(argumentString);

			// Check if argument extraction went well
			if (!_hasThrownError)
			{
				auto functionName = scriptLine.substr(0, parenthesisIndex);

				// Determine type of function	
				if (functionName == "math:tan") // TAN
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
					{
						float angle = _fe3d.misc_degreesToRadians(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, std::tan(angle)));
					}
				}
				else if (functionName == "math:sin") // SIN
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
					{
						float angle = _fe3d.misc_degreesToRadians(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, std::sin(angle)));
					}
				}
				else if (functionName == "math:cos") // COS
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
					{
						float angle = _fe3d.misc_degreesToRadians(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, std::cos(angle)));
					}
				}
				else if (functionName == "math:pow") // POWER
				{
					if (_validateListValueAmount(arguments, 2))
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
				else if (functionName == "math:min") // MIN
				{
					if (_validateListValueAmount(arguments, 2))
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
				else if (functionName == "math:max") // MAX
				{
					if (_validateListValueAmount(arguments, 2))
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
				else if (functionName == "math:clamp") // CLAMP
				{
					if (_validateListValueAmount(arguments, 3))
					{
						if (arguments[0].getType() == ScriptValueType::INTEGER && 
							arguments[2].getType() == ScriptValueType::INTEGER &&
							arguments[3].getType() == ScriptValueType::INTEGER)
						{
							int result = std::clamp(arguments[0].getInteger(), arguments[1].getInteger(), arguments[2].getInteger());
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
						}
						else if (
							arguments[0].getType() == ScriptValueType::DECIMAL && 
							arguments[1].getType() == ScriptValueType::DECIMAL &&
							arguments[2].getType() == ScriptValueType::DECIMAL)
						{
							float result = std::clamp(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal());
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
						}
						else
						{
							_throwScriptError("wrong argument type(s)!");
						}
					}
				}
				else if (functionName == "math:sqrt") // SQUAREROOT
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, std::sqrtf(arguments[0].getDecimal())));
					}
				}
				else if (functionName == "math:abs") // ABSOLUTE
				{
					// Validate amount of arguments
					if (_validateListValueAmount(arguments, 1))
					{
						// Determine type of value
						if (arguments[0].getType() == ScriptValueType::INTEGER)
						{
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, abs(arguments[0].getInteger())));
						}
						else if (arguments[0].getType() == ScriptValueType::DECIMAL)
						{
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, fabsf(arguments[0].getDecimal())));
						}
						else
						{
							_throwScriptError("wrong argument type(s)!");
						}
					}
				}
				else if (functionName == "math:distance") // DISTANCE
				{
					auto types = { ScriptValueType::VEC3, ScriptValueType::VEC3 };

					if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
					{
						// Save positions
						Vec3 firstPos = arguments[0].getVec3();
						Vec3 secondPos = arguments[1].getVec3();

						// Calculate distances
						float xDistance = fabsf(firstPos.x - secondPos.x);
						float yDistance = fabsf(firstPos.y - secondPos.y);
						float zDistance = fabsf(firstPos.z - secondPos.z);

						// Calculate absolute distance
						float result = sqrtf((xDistance * xDistance) + (yDistance * yDistance) + (zDistance * zDistance));
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
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
			auto arguments = _extractValuesFromListString(argumentString);

			// Check if argument extraction went well
			if (!_hasThrownError)
			{
				auto functionName = scriptLine.substr(0, parenthesisIndex);

				// Determine type of function
				if (functionName == "misc:to_string")
				{
					if (_validateListValueAmount(arguments, 1))
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

					if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
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