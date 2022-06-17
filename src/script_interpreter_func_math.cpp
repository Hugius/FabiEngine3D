#include "script_interpreter.hpp"

#include <algorithm>

using std::clamp;

using SVT = ScriptValueType;

const vector<shared_ptr<ScriptValue>> ScriptInterpreter::_processMathFunctionCall(const string & scriptLine)
{
	const auto openingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), '(');
	const auto closingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), ')');

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

	const auto parenthesisIndex = static_cast<int>(distance(scriptLine.begin(), openingParanthesisFound));
	const auto functionName = scriptLine.substr(0, parenthesisIndex);
	const auto argumentString = scriptLine.substr(static_cast<size_t>(parenthesisIndex + 1), (scriptLine.size() - static_cast<size_t>(parenthesisIndex + 1) - 1));
	const auto args = _extractValuesFromListString(argumentString);

	vector<shared_ptr<ScriptValue>> returnValues = {};

	if(_hasThrownError)
	{
		return {};
	}

	if(functionName == "math:tan")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = tan(Mathematics::convertToRadians(args[0]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:sin")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = sin(Mathematics::convertToRadians(args[0]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:cos")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = cos(Mathematics::convertToRadians(args[0]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:atan")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = Mathematics::convertToDegrees(atan(args[0]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:asin")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = Mathematics::convertToDegrees(asin(args[0]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:acos")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = Mathematics::convertToDegrees(acos(args[0]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:atan2")
	{
		const auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = Mathematics::convertToDegrees(atan2(args[0]->getDecimal(), args[1]->getDecimal()));

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
			else if(args[0]->getType() == SVT::DECIMAL && args[1]->getType() == SVT::DECIMAL)
			{
				const auto result = static_cast<float>(pow(args[0]->getDecimal(), args[1]->getDecimal()));

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
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = round(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:floor")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = floor(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:ceil")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
			const auto result = Mathematics::getPI();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:even")
	{
		const auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = ((args[0]->getInteger() % 2) == 0);

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "math:angle_difference")
	{
		const auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = Mathematics::calculateAngleDifference(args[0]->getDecimal(), args[1]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:reference_angle")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = Mathematics::calculateReferenceAngle(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:vector_distance")
	{
		const auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto first = fvec3(args[0]->getDecimal(), args[1]->getDecimal(), args[2]->getDecimal());
			const auto second = fvec3(args[3]->getDecimal(), args[4]->getDecimal(), args[5]->getDecimal());
			const auto result = Mathematics::calculateDistance(first, second);

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