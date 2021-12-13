#include "script_interpreter.hpp"

#include <algorithm>

using std::clamp;

using SVT = ScriptValueType;

const vector<ScriptValue> ScriptInterpreter::_processMathematicalFunctionCall(const string& scriptLine)
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

	// Extract arguments from argument string
	auto parenthesisIndex = static_cast<unsigned int>(distance(scriptLine.begin(), openingParanthesisFound));
	string argumentString = scriptLine.substr(static_cast<size_t>(parenthesisIndex + 1));
	argumentString.pop_back();
	auto arguments = _extractValuesFromListString(argumentString);

	// Check if argument extraction went wrong
	if(_hasThrownError)
	{
		return {};
	}

	// Temporary values
	auto functionName = scriptLine.substr(0, parenthesisIndex);

	// Determine type of function	
	if(functionName == "math:tan")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			float angle = Math::convertToRadians(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, tan(angle)));
		}
	}
	else if(functionName == "math:sin")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			float angle = Math::convertToRadians(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, sin(angle)));
		}
	}
	else if(functionName == "math:cos")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			float angle = Math::convertToRadians(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, cos(angle)));
		}
	}
	else if(functionName == "math:atan")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			auto angle = atan(arguments[0].getDecimal());
			auto result = Math::convertToDegrees(angle);
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:asin")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			auto angle = asin(arguments[0].getDecimal());
			auto result = Math::convertToDegrees(angle);
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:acos")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			auto angle = acos(arguments[0].getDecimal());
			auto result = Math::convertToDegrees(angle);
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:atan2")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			auto angle = atan2(arguments[0].getDecimal(), arguments[1].getDecimal());
			auto result = Math::convertToDegrees(angle);
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:pow")
	{
		if(_validateArgumentCount(arguments, 2))
		{
			if(arguments[0].getType() == SVT::INTEGER && arguments[1].getType() == SVT::INTEGER)
			{
				auto result = static_cast<int>(pow(arguments[0].getInteger(), arguments[1].getInteger()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
			}
			else if(arguments[0].getType() == SVT::DECIMAL && arguments[1].getType() == SVT::INTEGER)
			{
				auto result = static_cast<float>(pow(arguments[0].getDecimal(), arguments[1].getInteger()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
			else
			{
				_throwScriptError("wrong argument type(s)!");
			}
		}
	}
	else if(functionName == "math:min")
	{
		if(_validateArgumentCount(arguments, 2))
		{
			if(arguments[0].getType() == SVT::INTEGER && arguments[1].getType() == SVT::INTEGER)
			{
				auto result = min(arguments[0].getInteger(), arguments[1].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
			}
			else if(arguments[0].getType() == SVT::DECIMAL && arguments[1].getType() == SVT::DECIMAL)
			{
				auto result = min(arguments[0].getDecimal(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
			else
			{
				_throwScriptError("wrong argument type(s)!");
			}
		}
	}
	else if(functionName == "math:max")
	{
		if(_validateArgumentCount(arguments, 2))
		{
			if(arguments[0].getType() == SVT::INTEGER && arguments[1].getType() == SVT::INTEGER)
			{
				auto result = max(arguments[0].getInteger(), arguments[1].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
			}
			else if(arguments[0].getType() == SVT::DECIMAL && arguments[1].getType() == SVT::DECIMAL)
			{
				auto result = max(arguments[0].getDecimal(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
			else
			{
				_throwScriptError("wrong argument type(s)!");
			}
		}
	}
	else if(functionName == "math:round")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, round(arguments[0].getDecimal())));
		}
	}
	else if(functionName == "math:floor")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, floor(arguments[0].getDecimal())));
		}
	}
	else if(functionName == "math:ceil")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, ceil(arguments[0].getDecimal())));
		}
	}
	else if(functionName == "math:clamp")
	{
		if(_validateArgumentCount(arguments, 3))
		{
			if(arguments[0].getType() == SVT::INTEGER && arguments[2].getType() == SVT::INTEGER && arguments[3].getType() == SVT::INTEGER)
			{
				auto result = clamp(arguments[0].getInteger(), arguments[1].getInteger(), arguments[2].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
			}
			else if(arguments[0].getType() == SVT::DECIMAL && arguments[1].getType() == SVT::DECIMAL && arguments[2].getType() == SVT::DECIMAL)
			{
				auto result = clamp(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
			else
			{
				_throwScriptError("wrong argument type(s)!");
			}
		}
	}
	else if(functionName == "math:sqrt")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, sqrtf(arguments[0].getDecimal())));
		}
	}
	else if(functionName == "math:abs")
	{
		if(_validateArgumentCount(arguments, 1))
		{
			// Determine type of value
			if(arguments[0].getType() == SVT::INTEGER)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, abs(arguments[0].getInteger())));
			}
			else if(arguments[0].getType() == SVT::DECIMAL)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, fabsf(arguments[0].getDecimal())));
			}
			else
			{
				_throwScriptError("wrong argument type(s)!");
			}
		}
	}
	else if(functionName == "math:pi")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = Math::getPI();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:is_even")
	{
		auto types = {SVT::INTEGER};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			auto result = (arguments[0].getInteger() % 2) == 0;
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "math:angle_difference")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			auto result = Math::calculateAngleDifference(arguments[0].getDecimal(), arguments[1].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:reference_angle")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			auto result = Math::calculateReferenceAngle(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:vector_distance")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			auto first = fvec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal());
			auto second = fvec3(arguments[3].getDecimal(), arguments[4].getDecimal(), arguments[5].getDecimal());
			auto result = Math::calculateDistance(first, second);
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else
	{
		_throwScriptError("math function not existing!");
	}

	return returnValues;
}