#include "script_interpreter.hpp"

void ScriptInterpreter::_processVariableArithmetic(const string& scriptLine)
{
	// Temporary values
	std::istringstream iss(scriptLine);
	string operatorString = "";
	string nameString = "";
	string valueString = "";
	unsigned int valueIndex = 0;

	// Extract data
	iss >> operatorString >> nameString;

	// Check if variable name is missing
	if (nameString.empty())
	{
		_throwScriptError("variable name missing!");
		return;
	}

	// Only extract value if not negating
	if (operatorString != _negationKeyword)
	{
		iss >> valueString;
	}

	// Check if valid arithmetic keyword
	if (operatorString != _additionKeyword && operatorString != _subtractionKeyword && operatorString != _multiplicationKeyword &&
		operatorString != _divisionKeyword && operatorString != _negationKeyword)
	{
		_throwScriptError("invalid arithmetic operator!");
		return;
	}

	// Check if accessing individual value from list variable
	bool isAccessingList = false;
	auto listIndex = _extractListIndexFromString(nameString, isAccessingList);

	// Check if accessing individual float from vec3 variable
	auto vec3Parts = _extractVec3PartFromString(nameString);

	// Check if any error was thrown
	if (_hasThrownError)
	{
		return;
	}

	// Remove vec3 part characters
	if (vec3Parts != Ivec3(0))
	{
		nameString.pop_back();
		nameString.pop_back();
	}

	// Remove list accessing characters
	if (isAccessingList)
	{
		auto openingBracketFound = std::find(nameString.begin(), nameString.end(), '[');
		unsigned int bracketIndex = std::distance(nameString.begin(), openingBracketFound);
		nameString = nameString.substr(0, bracketIndex);
	}

	// Check if variable exists
	if (!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("variable \"" + nameString + "\" not found!");
		return;
	}

	// Retrieve variable
	auto& variable = _isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString);

	// Validate vec3 access
	if (vec3Parts != Ivec3(0))
	{
		if (variable.getType() == ScriptVariableType::MULTIPLE || variable.getValue().getType() != ScriptValueType::VEC3)
		{
			_throwScriptError("variable with ID \"" + variable.getID() + "\" is not a vec3!");
			return;
		}
	}

	// Validate list access
	if (isAccessingList)
	{
		// Check if list index is valid
		if (_validateListIndex(variable, listIndex))
		{
			valueIndex = listIndex;
		}
		else // Error
		{
			return;
		}
	}

	// Check if variable is not a list
	if (variable.getType() == ScriptVariableType::MULTIPLE && !isAccessingList)
	{
		_throwScriptError("arithmetic is not allowed on a list!");
		return;
	}

	// Check if variable is of the correct type
	if (!(variable.getValue(valueIndex).getType() == ScriptValueType::INTEGER) &&
		!(variable.getValue(valueIndex).getType() == ScriptValueType::DECIMAL) &&
		!(variable.getValue(valueIndex).getType() == ScriptValueType::VEC3))
	{
		_throwScriptError("arithmetic is only allowed on number values!");
		return;
	}

	// Check if variable can be changed
	if (variable.isConstant())
	{
		_throwScriptError("variable \"" + nameString + "\" cannot be changed, it is constant!");
		return;
	}

	// Negation arithmetic operation
	if (operatorString == _negationKeyword)
	{
		if (variable.getValue(valueIndex).getType() == ScriptValueType::INTEGER) // INTEGER variable
		{
			variable.getValue(valueIndex).setInteger(variable.getValue(valueIndex).getInteger() * -1);
		}
		else if (variable.getValue(valueIndex).getType() == ScriptValueType::DECIMAL) // DECIMAL variable
		{
			variable.getValue(valueIndex).setDecimal(variable.getValue(valueIndex).getDecimal() * -1.0f);
		}
		else if (variable.getValue(valueIndex).getType() == ScriptValueType::VEC3) // VEC3 variable
		{
			if (vec3Parts.x)
			{
				auto oldValue = variable.getValue(valueIndex).getVec3();
				variable.getValue(valueIndex).setVec3(Vec3(oldValue.x * -1.0f, oldValue.y, oldValue.z));
			}
			else if (vec3Parts.y)
			{
				auto oldValue = variable.getValue(valueIndex).getVec3();
				variable.getValue(valueIndex).setVec3(Vec3(oldValue.x, oldValue.y * -1.0f, oldValue.z));
			}
			else if (vec3Parts.z)
			{
				auto oldValue = variable.getValue(valueIndex).getVec3();
				variable.getValue(valueIndex).setVec3(Vec3(oldValue.x, oldValue.y, oldValue.z * -1.0f));
			}
			else
			{
				variable.getValue(valueIndex).setVec3(variable.getValue(valueIndex).getVec3() * -1.0f);
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

		// Retrieve arithmetic value
		auto value = _isLocalVariableExisting(valueString) ? _getLocalVariable(valueString).getValue(valueIndex) : _isGlobalVariableExisting(valueString) ?
			_getGlobalVariable(nameString).getValue(valueIndex) : _isIntegerValue(valueString) ? ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(valueString)) :
			_isDecimalValue(valueString) ? ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(valueString)) : ScriptValue(_fe3d, ScriptValueType::EMPTY);

		// Check if arithmetic value is valid
		if (value.getType() == ScriptValueType::EMPTY)
		{
			_throwScriptError("invalid arithmetic value!");
			return;
		}

		// Execute arithmetic operation
		if ((variable.getValue(valueIndex).getType() == ScriptValueType::INTEGER) && value.getType() == ScriptValueType::INTEGER) // Integer
		{
			// Retrieve current variable value
			int result = variable.getValue(valueIndex).getInteger();

			// Determine arithmetic type
			if (operatorString == _additionKeyword)
			{
				result += value.getInteger();
			}
			else if (operatorString == _subtractionKeyword)
			{
				result -= value.getInteger();
			}
			else if (operatorString == _multiplicationKeyword)
			{
				result *= value.getInteger();
			}
			else if (operatorString == _divisionKeyword)
			{
				result /= value.getInteger();
			}

			// Set resulting value
			variable.getValue(valueIndex).setInteger(result);
		}
		else if ((variable.getValue(valueIndex).getType() == ScriptValueType::DECIMAL) && value.getType() == ScriptValueType::DECIMAL) // Decimal
		{
			// Retrieve current variable value
			float result = variable.getValue(valueIndex).getDecimal();

			// Determine arithmetic type
			if (operatorString == _additionKeyword)
			{
				result += value.getDecimal();
			}
			else if (operatorString == _subtractionKeyword)
			{
				result -= value.getDecimal();
			}
			else if (operatorString == _multiplicationKeyword)
			{
				result *= value.getDecimal();
			}
			else if (operatorString == _divisionKeyword)
			{
				result /= value.getDecimal();
			}

			// Set resulting value
			variable.getValue(valueIndex).setDecimal(result);
		}
		else if ((variable.getValue(valueIndex).getType() == ScriptValueType::VEC3) && value.getType() == ScriptValueType::DECIMAL) // Vec3
		{
			// Retrieve current variable value
			Vec3 oldValue = variable.getValue(valueIndex).getVec3();
			Vec3 result = variable.getValue(valueIndex).getVec3();

			// Determine arithmetic type
			if (operatorString == _additionKeyword)
			{
				result += value.getDecimal();
			}
			else if (operatorString == _subtractionKeyword)
			{
				result -= value.getDecimal();
			}
			else if (operatorString == _multiplicationKeyword)
			{
				result *= value.getDecimal();
			}
			else if (operatorString == _divisionKeyword)
			{
				result /= value.getDecimal();
			}

			// Set resulting value
			if (vec3Parts.x)
			{
				variable.getValue(valueIndex).setVec3(Vec3(result.x, oldValue.y, oldValue.z));
			}
			else if (vec3Parts.y)
			{
				variable.getValue(valueIndex).setVec3(Vec3(oldValue.x, result.y, oldValue.z));
			}
			else if (vec3Parts.z)
			{
				variable.getValue(valueIndex).setVec3(Vec3(oldValue.x, oldValue.y, result.z));
			}
			else
			{
				variable.getValue(valueIndex).setVec3(result);
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