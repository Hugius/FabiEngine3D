#include "script_interpreter.hpp"

#include <algorithm>

using std::clamp;

using SVT = ScriptValueType;

const vector<shared_ptr<ScriptValue>> ScriptInterpreter::_processMathFunctionCall(const string& scriptLine)
{
	auto openingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), '(');
	auto closingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), ')');

	if((openingParanthesisFound == scriptLine.end()) || (closingParanthesisFound == scriptLine.end()))
	{
		_throwRuntimeError("invalid syntax");
		return {};
	}

	if(scriptLine.back() != ')')
	{
		_throwRuntimeError("invalid syntax");
		return {};
	}

	auto parenthesisIndex = static_cast<unsigned int>(distance(scriptLine.begin(), openingParanthesisFound));
	string argumentString = scriptLine.substr(static_cast<size_t>(parenthesisIndex + 1));
	argumentString.pop_back();
	vector<shared_ptr<ScriptValue>> returnValues;
	auto args = _extractValuesFromListString(argumentString);

	if(_hasThrownError)
	{
		return {};
	}

	auto functionName = scriptLine.substr(0, parenthesisIndex);

	if(functionName == "math:tan")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = tan(Math::convertToRadians(args[0]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:sin")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = sin(Math::convertToRadians(args[0]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:cos")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = cos(Math::convertToRadians(args[0]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:atan")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = Math::convertToDegrees(atan(args[0]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:asin")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = Math::convertToDegrees(asin(args[0]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:acos")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = Math::convertToDegrees(acos(args[0]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:atan2")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = Math::convertToDegrees(atan2(args[0]->getDecimal(), args[1]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:pow")
	{
		if(_validateArgumentCount(args, 2))
		{
			if(args[0]->getType() == SVT::INTEGER && args[1]->getType() == SVT::INTEGER)
			{
				const auto result = static_cast<int>(pow(args[0]->getInteger(), args[1]->getInteger()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
			else if(args[0]->getType() == SVT::DECIMAL && args[1]->getType() == SVT::INTEGER)
			{
				const auto result = static_cast<float>(pow(args[0]->getDecimal(), args[1]->getInteger()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
			else
			{
				_throwRuntimeError("wrong argument type(s)");
				return {};
			}
		}
	}
	else if(functionName == "math:min")
	{
		if(_validateArgumentCount(args, 2))
		{
			if(args[0]->getType() == SVT::INTEGER && args[1]->getType() == SVT::INTEGER)
			{
				const auto result = min(args[0]->getInteger(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
			else if(args[0]->getType() == SVT::DECIMAL && args[1]->getType() == SVT::DECIMAL)
			{
				const auto result = min(args[0]->getDecimal(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
			else
			{
				_throwRuntimeError("wrong argument type(s)");
				return {};
			}
		}
	}
	else if(functionName == "math:max")
	{
		if(_validateArgumentCount(args, 2))
		{
			if(args[0]->getType() == SVT::INTEGER && args[1]->getType() == SVT::INTEGER)
			{
				const auto result = max(args[0]->getInteger(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
			else if(args[0]->getType() == SVT::DECIMAL && args[1]->getType() == SVT::DECIMAL)
			{
				const auto result = max(args[0]->getDecimal(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
			else
			{
				_throwRuntimeError("wrong argument type(s)");
				return {};
			}
		}
	}
	else if(functionName == "math:round")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = round(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:floor")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = floor(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:ceil")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = ceil(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:clamp")
	{
		if(_validateArgumentCount(args, 3))
		{
			if(args[0]->getType() == SVT::INTEGER && args[2]->getType() == SVT::INTEGER && args[3]->getType() == SVT::INTEGER)
			{
				const auto result = clamp(args[0]->getInteger(), args[1]->getInteger(), args[2]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
			else if(args[0]->getType() == SVT::DECIMAL && args[1]->getType() == SVT::DECIMAL && args[2]->getType() == SVT::DECIMAL)
			{
				const auto result = clamp(args[0]->getDecimal(), args[1]->getDecimal(), args[2]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
			else
			{
				_throwRuntimeError("wrong argument type(s)");
				return {};
			}
		}
	}
	else if(functionName == "math:sqrt")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = sqrtf(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:abs")
	{
		if(_validateArgumentCount(args, 1))
		{
			if(args[0]->getType() == SVT::INTEGER)
			{
				const auto result = abs(args[0]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
			else if(args[0]->getType() == SVT::DECIMAL)
			{
				const auto result = fabsf(args[0]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
			else
			{
				_throwRuntimeError("wrong argument type(s)");
				return {};
			}
		}
	}
	else if(functionName == "math:pi")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = Math::getPI();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:is_even")
	{
		auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = ((args[0]->getInteger() % 2) == 0);

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "math:angle_difference")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = Math::calculateAngleDifference(args[0]->getDecimal(), args[1]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:reference_angle")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = Math::calculateReferenceAngle(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:vector_distance")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto first = fvec3(args[0]->getDecimal(), args[1]->getDecimal(), args[2]->getDecimal());
			const auto second = fvec3(args[3]->getDecimal(), args[4]->getDecimal(), args[5]->getDecimal());
			const auto result = Math::calculateDistance(first, second);

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else
	{
		_throwRuntimeError("math function does not exist");
		return {};
	}

	return returnValues;
}