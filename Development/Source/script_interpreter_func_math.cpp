#include "script_interpreter.hpp"

#include <algorithm>

using std::clamp;

vector<ScriptValue> ScriptInterpreter::_processMathematicalFunctionCall(const string& scriptLine)
{
	// Temporary values
	vector<ScriptValue> returnValues;
	auto openingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), '(');
	auto closingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), ')');

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
			auto parenthesisIndex = static_cast<unsigned int>(distance(scriptLine.begin(), openingParanthesisFound));
			string argumentString = scriptLine.substr(parenthesisIndex + 1);
			argumentString.pop_back();
			auto arguments = _extractValuesFromListString(argumentString);

			// Check if argument extraction went well
			if (!_hasThrownError)
			{
				auto functionName = scriptLine.substr(0, parenthesisIndex);

				// Determine type of function	
				if (functionName == "math:tan")
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						float angle = _fe3d.misc_convertToRadians(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, tan(angle)));
					}
				}
				else if (functionName == "math:sin")
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						float angle = _fe3d.misc_convertToRadians(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, sin(angle)));
					}
				}
				else if (functionName == "math:cos")
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						float angle = _fe3d.misc_convertToRadians(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, cos(angle)));
					}
				}
				else if (functionName == "math:atan")
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						float angle = atan(arguments[0].getDecimal());
						float result = _fe3d.misc_convertToDegrees(angle);
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
					}
				}
				else if (functionName == "math:asin")
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						float angle = asin(arguments[0].getDecimal());
						float result = _fe3d.misc_convertToDegrees(angle);
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
					}
				}
				else if (functionName == "math:acos")
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						float angle = acos(arguments[0].getDecimal());
						float result = _fe3d.misc_convertToDegrees(angle);
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
					}
				}
				else if (functionName == "math:atan2")
				{
					auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

					if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						float angle = atan2(arguments[0].getDecimal(), arguments[1].getDecimal());
						float result = _fe3d.misc_convertToDegrees(angle);
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
					}
				}
				else if (functionName == "math:pow")
				{
					if (_validateListValueCount(arguments, 2))
					{
						if (arguments[0].getType() == ScriptValueType::INTEGER && arguments[1].getType() == ScriptValueType::INTEGER)
						{
							int result = static_cast<int>(pow(arguments[0].getInteger(), arguments[1].getInteger()));
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
						}
						else if (arguments[0].getType() == ScriptValueType::DECIMAL && arguments[1].getType() == ScriptValueType::INTEGER)
						{
							float result = static_cast<float>(pow(arguments[0].getDecimal(), arguments[1].getInteger()));
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
					if (_validateListValueCount(arguments, 2))
					{
						if (arguments[0].getType() == ScriptValueType::INTEGER && arguments[1].getType() == ScriptValueType::INTEGER)
						{
							int result = min(arguments[0].getInteger(), arguments[1].getInteger());
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
						}
						else if (arguments[0].getType() == ScriptValueType::DECIMAL && arguments[1].getType() == ScriptValueType::DECIMAL)
						{
							float result = min(arguments[0].getDecimal(), arguments[1].getDecimal());
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
					if (_validateListValueCount(arguments, 2))
					{
						if (arguments[0].getType() == ScriptValueType::INTEGER && arguments[1].getType() == ScriptValueType::INTEGER)
						{
							int result = max(arguments[0].getInteger(), arguments[1].getInteger());
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
						}
						else if (arguments[0].getType() == ScriptValueType::DECIMAL && arguments[1].getType() == ScriptValueType::DECIMAL)
						{
							float result = max(arguments[0].getDecimal(), arguments[1].getDecimal());
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
						}
						else
						{
							_throwScriptError("wrong argument type(s)!");
						}
					}
				}
				else if (functionName == "math:round")
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, round(arguments[0].getDecimal())));
					}
				}
				else if (functionName == "math:floor")
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, floor(arguments[0].getDecimal())));
					}
				}
				else if (functionName == "math:ceil")
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, ceil(arguments[0].getDecimal())));
					}
				}
				else if (functionName == "math:clamp")
				{
					if (_validateListValueCount(arguments, 3))
					{
						if (arguments[0].getType() == ScriptValueType::INTEGER &&
							arguments[2].getType() == ScriptValueType::INTEGER &&
							arguments[3].getType() == ScriptValueType::INTEGER)
						{
							int result = clamp(arguments[0].getInteger(), arguments[1].getInteger(), arguments[2].getInteger());
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
						}
						else if (
							arguments[0].getType() == ScriptValueType::DECIMAL &&
							arguments[1].getType() == ScriptValueType::DECIMAL &&
							arguments[2].getType() == ScriptValueType::DECIMAL)
						{
							float result = clamp(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal());
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

					if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, sqrtf(arguments[0].getDecimal())));
					}
				}
				else if (functionName == "math:abs")
				{
					// Validate amount of arguments
					if (_validateListValueCount(arguments, 1))
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
				else if (functionName == "math:pi")
				{
					if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
					{
						auto result = _fe3d.misc_getPI();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
					}
				}
				else if (functionName == "math:is_even")
				{
					auto types = { ScriptValueType::INTEGER };

					if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						auto result = (arguments[0].getInteger() % 2) == 0;
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
					}
				}
				else if (functionName == "math:angle_difference")
				{
					auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

					if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						// Calculate angle difference
						float result = Math::calculateAngleDifference(arguments[0].getDecimal(), arguments[1].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
					}
				}
				else if (functionName == "math:reference_angle")
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						// Calculate absolute distance
						float result = Math::calculateReferenceAngle(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
					}
				}
				else if (functionName == "math:vector_distance")
				{
					auto types = { ScriptValueType::VEC3, ScriptValueType::VEC3 };

					if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
					{
						// Calculate absolute distance
						float result = Math::calculateVectorDistance(arguments[0].getVec3(), arguments[1].getVec3());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
					}
				}
				else
				{
					_throwScriptError("math function not found!");
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