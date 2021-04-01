#include "script_interpreter.hpp"

void ScriptInterpreter::_processVariableArithmetic(const string& scriptLine)
{
	// Temporary values
	std::istringstream iss(scriptLine);
	string operatorString = "";
	string nameString = "";
	string valueString = "";

	// Extract data
	iss >> operatorString >> nameString;

	// Check if variable name is missing
	if (nameString.empty())
	{
		_throwScriptError("variable name missing!");
		return;
	}

	// Only extract value if not negating
	if (operatorString != NEGATION_KEYWORD)
	{
		iss >> valueString;
	}

	// Check if valid arithmetic keyword
	if (operatorString != ADDITION_KEYWORD && operatorString != SUBTRACTION_KEYWORD && operatorString != MULTIPLICATION_KEYWORD &&
		operatorString != DIVISION_KEYWORD && operatorString != NEGATION_KEYWORD)
	{
		_throwScriptError("invalid arithmetic operator!");
		return;
	}

	// Check if accessing individual value from list variable
	bool isAccessingListOne = false;
	auto listIndexOne = _extractListIndexFromString(nameString, isAccessingListOne);
	unsigned int valueIndexOne = 0;

	// Check if accessing individual float from vec3 variable
	auto vec3PartsOne = _extractVec3PartFromString(nameString);

	// Check if any error was thrown
	if (_hasThrownError)
	{
		return;
	}

	// Remove vec3 part characters
	if (vec3PartsOne != Ivec3(0))
	{
		nameString.pop_back();
		nameString.pop_back();
	}

	// Remove list accessing characters
	if (isAccessingListOne)
	{
		auto openingBracketFound = std::find(nameString.begin(), nameString.end(), '[');
		unsigned int bracketIndex = std::distance(nameString.begin(), openingBracketFound);
		nameString = nameString.substr(0, bracketIndex);
	}

	// Check if variable exists
	if (!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("variable not existing!");
		return;
	}

	// Retrieve variable
	auto& variableOne = _isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString);

	// Validate vec3 access
	if (vec3PartsOne != Ivec3(0))
	{
		if (variableOne.getType() == ScriptVariableType::MULTIPLE || variableOne.getValue().getType() != ScriptValueType::VEC3)
		{
			_throwScriptError("variable is not a vec3!");
			return;
		}
	}

	// Validate list access
	if (isAccessingListOne)
	{
		// Check if list index is valid
		if (_validateListIndex(variableOne, listIndexOne))
		{
			valueIndexOne = listIndexOne;
		}
		else // Error
		{
			return;
		}
	}

	// Check if variable is not a list
	if (variableOne.getType() == ScriptVariableType::MULTIPLE && !isAccessingListOne)
	{
		_throwScriptError("arithmetic is not allowed on a list!");
		return;
	}

	// Check if variable is of the correct type
	if (!(variableOne.getValue(valueIndexOne).getType() == ScriptValueType::INTEGER) &&
		!(variableOne.getValue(valueIndexOne).getType() == ScriptValueType::DECIMAL) &&
		!(variableOne.getValue(valueIndexOne).getType() == ScriptValueType::VEC3))
	{
		_throwScriptError("arithmetic is only allowed on number values!");
		return;
	}

	// Check if variable can be changed
	if (variableOne.isConstant())
	{
		_throwScriptError("variable cannot be changed, it is constant!");
		return;
	}

	// Negation arithmetic operation
	if (operatorString == NEGATION_KEYWORD)
	{
		if (variableOne.getValue(valueIndexOne).getType() == ScriptValueType::INTEGER) // INTEGER variable
		{
			variableOne.getValue(valueIndexOne).setInteger(variableOne.getValue(valueIndexOne).getInteger() * -1);
		}
		else if (variableOne.getValue(valueIndexOne).getType() == ScriptValueType::DECIMAL) // DECIMAL variable
		{
			variableOne.getValue(valueIndexOne).setDecimal(variableOne.getValue(valueIndexOne).getDecimal() * -1.0f);
		}
		else if (variableOne.getValue(valueIndexOne).getType() == ScriptValueType::VEC3) // VEC3 variable
		{
			if (vec3PartsOne.x)
			{
				auto oldValue = variableOne.getValue(valueIndexOne).getVec3();
				variableOne.getValue(valueIndexOne).setVec3(Vec3(oldValue.x * -1.0f, oldValue.y, oldValue.z));
			}
			else if (vec3PartsOne.y)
			{
				auto oldValue = variableOne.getValue(valueIndexOne).getVec3();
				variableOne.getValue(valueIndexOne).setVec3(Vec3(oldValue.x, oldValue.y * -1.0f, oldValue.z));
			}
			else if (vec3PartsOne.z)
			{
				auto oldValue = variableOne.getValue(valueIndexOne).getVec3();
				variableOne.getValue(valueIndexOne).setVec3(Vec3(oldValue.x, oldValue.y, oldValue.z * -1.0f));
			}
			else
			{
				variableOne.getValue(valueIndexOne).setVec3(variableOne.getValue(valueIndexOne).getVec3() * -1.0f);
			}
		}
	}
	else // Other arithmetic operations
	{
		// Check if value is not empty
		if (valueString.empty())
		{
			_throwScriptError("no arithmetic value found!");
			return;
		}

		// Prepare vec3 part or list access for value
		bool isAccessingListTwo = false;
		auto listIndexTwo = _extractListIndexFromString(valueString, isAccessingListTwo);
		unsigned int valueIndexTwo = 0;
		unsigned int vec3Index = 0;
		auto vec3PartsTwo = _extractVec3PartFromString(valueString);
		if (_hasThrownError) { return; }

		// Remove vec3 part characters
		if (vec3PartsTwo != Ivec3(0))
		{
			valueString.pop_back();
			valueString.pop_back();
			vec3Index = vec3PartsTwo.x ? 0 : vec3PartsTwo.y ? 1 : 2;
		}

		// Remove list accessing characters
		if (isAccessingListTwo)
		{
			auto openingBracketFound = std::find(valueString.begin(), valueString.end(), '[');
			unsigned int bracketIndex = std::distance(valueString.begin(), openingBracketFound);
			valueString = valueString.substr(0, bracketIndex);
		}

		// Retrieve value variable
		ScriptVariable* variableTwo = nullptr;
		if (vec3PartsTwo != Ivec3(0) || isAccessingListTwo)
		{
			// Check if variable exists
			if (!_isLocalVariableExisting(valueString) && !_isGlobalVariableExisting(valueString))
			{
				_throwScriptError("variable not existing!");
				return;
			}

			// Retreve variable
			variableTwo = &(_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) : _getGlobalVariable(valueString));
		}

		// Validate vec3 access
		if (vec3PartsTwo != Ivec3(0))
		{
			if (variableTwo->getType() == ScriptVariableType::MULTIPLE || variableTwo->getValue().getType() != ScriptValueType::VEC3)
			{
				_throwScriptError("variable is not a vec3!");
				return;
			}
		}

		// Validate list access
		if (isAccessingListTwo)
		{
			// Check if list index is valid
			if (_validateListIndex(*variableTwo, listIndexTwo))
			{
				valueIndexTwo = listIndexTwo;

				// Check if list item value is valid
				if (!(variableTwo->getValue(valueIndexTwo).getType() == ScriptValueType::INTEGER) &&
					!(variableTwo->getValue(valueIndexTwo).getType() == ScriptValueType::DECIMAL) &&
					!(variableTwo->getValue(valueIndexTwo).getType() == ScriptValueType::VEC3))
				{
					_throwScriptError("arithmetic is only allowed with number values!");
					return;
				}
			}
			else // Error
			{
				return;
			}
		}

		// Retrieve arithmetic value
		auto value = isAccessingListTwo ? variableTwo->getValue(valueIndexTwo) : // List access
			vec3PartsTwo != Ivec3(0) ? ScriptValue(_fe3d, ScriptValueType::DECIMAL, variableTwo->getValue().getVec3().f[vec3Index]) : // Vec3 part
			_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString).getValue(valueIndexTwo) : // Local variable
			_isGlobalVariableExisting(valueString) ? _getGlobalVariable(valueString).getValue(valueIndexTwo) : // Global variable
			_isIntegerValue(valueString) ? ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(_limitIntegerString(valueString))) : // Integer
			_isDecimalValue(valueString) ? ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(_limitDecimalString(valueString))) : // Decimal
			_isVec3Value(valueString) ? ScriptValue(_fe3d, ScriptValueType::VEC3, _extractVec3FromString(valueString)) : // Vec3
			ScriptValue(_fe3d, ScriptValueType::EMPTY); // Empty

		// Check if arithmetic value is valid
		if (value.getType() == ScriptValueType::EMPTY)
		{
			_throwScriptError("invalid arithmetic value!");
			return;
		}

		// Execute arithmetic operation
		if ((variableOne.getValue(valueIndexOne).getType() == ScriptValueType::INTEGER) && value.getType() == ScriptValueType::INTEGER) // INTEGER
		{
			// Retrieve current variable value
			int result = variableOne.getValue(valueIndexOne).getInteger();

			// Determine arithmetic type
			if (operatorString == ADDITION_KEYWORD)
			{
				result += value.getInteger();
			}
			else if (operatorString == SUBTRACTION_KEYWORD)
			{
				result -= value.getInteger();
			}
			else if (operatorString == MULTIPLICATION_KEYWORD)
			{
				result *= value.getInteger();
			}
			else if (operatorString == DIVISION_KEYWORD)
			{
				result /= value.getInteger();
			}

			// Set resulting value
			variableOne.getValue(valueIndexOne).setInteger(result);
		}
		else if ((variableOne.getValue(valueIndexOne).getType() == ScriptValueType::DECIMAL) && value.getType() == ScriptValueType::DECIMAL) // DECIMAL
		{
			// Retrieve current variable value
			float result = variableOne.getValue(valueIndexOne).getDecimal();

			// Determine arithmetic type
			if (operatorString == ADDITION_KEYWORD)
			{
				result += value.getDecimal();
			}
			else if (operatorString == SUBTRACTION_KEYWORD)
			{
				result -= value.getDecimal();
			}
			else if (operatorString == MULTIPLICATION_KEYWORD)
			{
				result *= value.getDecimal();
			}
			else if (operatorString == DIVISION_KEYWORD)
			{
				result /= value.getDecimal();
			}

			// Set resulting value
			variableOne.getValue(valueIndexOne).setDecimal(result);
		}
		else if ((variableOne.getValue(valueIndexOne).getType() == ScriptValueType::VEC3) && value.getType() == ScriptValueType::DECIMAL) // VEC3 - decimal
		{
			// Retrieve current variable value
			Vec3 oldValue = variableOne.getValue(valueIndexOne).getVec3();
			Vec3 result = variableOne.getValue(valueIndexOne).getVec3();

			// Determine arithmetic type
			if (operatorString == ADDITION_KEYWORD)
			{
				result += value.getDecimal();
			}
			else if (operatorString == SUBTRACTION_KEYWORD)
			{
				result -= value.getDecimal();
			}
			else if (operatorString == MULTIPLICATION_KEYWORD)
			{
				result *= value.getDecimal();
			}
			else if (operatorString == DIVISION_KEYWORD)
			{
				result /= value.getDecimal();
			}

			// Set resulting value
			if (vec3PartsOne.x)
			{
				variableOne.getValue(valueIndexOne).setVec3(Vec3(result.x, oldValue.y, oldValue.z));
			}
			else if (vec3PartsOne.y)
			{
				variableOne.getValue(valueIndexOne).setVec3(Vec3(oldValue.x, result.y, oldValue.z));
			}
			else if (vec3PartsOne.z)
			{
				variableOne.getValue(valueIndexOne).setVec3(Vec3(oldValue.x, oldValue.y, result.z));
			}
			else
			{
				variableOne.getValue(valueIndexOne).setVec3(result);
			}
		}
		else if ((variableOne.getValue(valueIndexOne).getType() == ScriptValueType::VEC3) && value.getType() == ScriptValueType::VEC3) // VEC3 - vec3
		{
			// Retrieve current variable value
			Vec3 oldValue = variableOne.getValue(valueIndexOne).getVec3();
			Vec3 result = variableOne.getValue(valueIndexOne).getVec3();

			// Determine arithmetic type
			if (operatorString == ADDITION_KEYWORD)
			{
				result += value.getVec3();
			}
			else if (operatorString == SUBTRACTION_KEYWORD)
			{
				result -= value.getVec3();
			}
			else if (operatorString == MULTIPLICATION_KEYWORD)
			{
				result *= value.getVec3();
			}
			else if (operatorString == DIVISION_KEYWORD)
			{
				result /= value.getVec3();
			}

			// Set resulting value
			if (vec3PartsOne.x)
			{
				variableOne.getValue(valueIndexOne).setVec3(Vec3(result.x, oldValue.y, oldValue.z));
			}
			else if (vec3PartsOne.y)
			{
				variableOne.getValue(valueIndexOne).setVec3(Vec3(oldValue.x, result.y, oldValue.z));
			}
			else if (vec3PartsOne.z)
			{
				variableOne.getValue(valueIndexOne).setVec3(Vec3(oldValue.x, oldValue.y, result.z));
			}
			else
			{
				variableOne.getValue(valueIndexOne).setVec3(result);
			}
		}
		else
		{
			_throwScriptError("arithmetic value not applicable to this variable!");
			return;
		}
	}

	// No characters allowed after variable arithmetic
	string temp;
	if (iss >> temp || scriptLine.back() == ' ')
	{
		_throwScriptError("invalid syntax!");
		return;
	}
}