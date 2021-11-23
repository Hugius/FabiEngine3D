#include "script_interpreter.hpp"

void ScriptInterpreter::_processVariableArithmetic(const string& scriptLine)
{
	// Temporary values
	string operatorString = "";
	string nameString = "";
	string valueString = "";

	// Extract operator & name
	string words[2] = {"", "" };
	unsigned int wordIndex = 0;
	for(const auto& c : scriptLine)
	{
		if(c == ' ') // Current word ended
		{
			// Next word
			wordIndex++;

			// Check if words extracted
			if(wordIndex == 2)
			{
				break;
			}
		}
		else // Add to word
		{
			words[wordIndex] += c;
		}
	}
	operatorString = words[0];
	nameString = words[1];

	// Check if variable name is missing
	if(nameString.empty())
	{
		_throwScriptError("variable name missing!");
		return;
	}

	// Only extract value if not negating
	if(operatorString != NEGATION_KEYWORD)
	{
		// Check if value is present
		if(scriptLine.size() >= (operatorString.size() + nameString.size() + 3))
		{
			// Extract remaining text (value)
			valueString = scriptLine.substr(operatorString.size() + nameString.size() + 2);
		}
		else
		{
			_throwScriptError("value missing!");
			return;
		}
	}

	// Check if valid arithmetic keyword
	if(operatorString != ADDITION_KEYWORD && operatorString != SUBTRACTION_KEYWORD && operatorString != MULTIPLICATION_KEYWORD &&
	   operatorString != DIVISION_KEYWORD && operatorString != NEGATION_KEYWORD)
	{
		_throwScriptError("invalid arithmetic operator!");
		return;
	}

	// Check if accessing individual value from list variable
	bool isAccessingListOne = false;
	auto listIndexOne = _extractListIndexFromString(nameString, isAccessingListOne);
	unsigned int valueIndexOne = 0;

	// Check if any error was thrown
	if(_hasThrownError)
	{
		return;
	}

	// Remove list accessing characters
	if(isAccessingListOne)
	{
		auto openingBracketFound = find(nameString.begin(), nameString.end(), '[');
		auto bracketIndex = static_cast<unsigned int>(distance(nameString.begin(), openingBracketFound));
		nameString = nameString.substr(0, bracketIndex);
	}

	// Check if variable exists
	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("variable not existing!");
		return;
	}

	// Retrieve variable
	auto& variableOne = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	// Validate list access
	if(isAccessingListOne)
	{
		// Check if list index is valid
		if(_validateListIndex(variableOne, listIndexOne))
		{
			valueIndexOne = listIndexOne;
		}
		else // Error
		{
			return;
		}
	}

	// Check if variable is not a list
	if(variableOne.getType() == ScriptVariableType::MULTIPLE && !isAccessingListOne)
	{
		_throwScriptError("arithmetic is not allowed on a list!");
		return;
	}

	// Check if variable is of the correct type
	if(!(variableOne.getValue(valueIndexOne).getType() == ScriptValueType::INTEGER) &&
	   !(variableOne.getValue(valueIndexOne).getType() == ScriptValueType::DECIMAL))
	{
		_throwScriptError("arithmetic is only allowed on number values!");
		return;
	}

	// Check if variable can be changed
	if(variableOne.isConstant())
	{
		_throwScriptError("variable cannot be changed, it is constant!");
		return;
	}

	// Negation arithmetic operation
	if(operatorString == NEGATION_KEYWORD)
	{
		if(variableOne.getValue(valueIndexOne).getType() == ScriptValueType::INTEGER) // INTEGER variable
		{
			variableOne.getValue(valueIndexOne).setInteger(variableOne.getValue(valueIndexOne).getInteger() * -1);
		}
		else if(variableOne.getValue(valueIndexOne).getType() == ScriptValueType::DECIMAL) // DECIMAL variable
		{
			variableOne.getValue(valueIndexOne).setDecimal(variableOne.getValue(valueIndexOne).getDecimal() * -1.0f);
		}
	}
	else // Other arithmetic operations
	{
		// Check if value is not empty
		if(valueString.empty())
		{
			_throwScriptError("no arithmetic value found!");
			return;
		}

		// Prepare list access for value
		bool isAccessingListTwo = false;
		auto listIndexTwo = _extractListIndexFromString(valueString, isAccessingListTwo);
		
		// Check if any error was thrown
		if(_hasThrownError)
		{
			return;
		}

		// Remove list accessing characters
		if(isAccessingListTwo)
		{
			auto openingBracketFound = find(valueString.begin(), valueString.end(), '[');
			auto bracketIndex = static_cast<unsigned int>(distance(valueString.begin(), openingBracketFound));
			valueString = valueString.substr(0, bracketIndex);
		}

		// Retrieve value variable
		ScriptVariable* variableTwo = nullptr;
		if(isAccessingListTwo)
		{
			// Check if variable exists
			if(!_isLocalVariableExisting(valueString) && !_isGlobalVariableExisting(valueString))
			{
				_throwScriptError("variable not existing!");
				return;
			}

			// Retreve variable
			variableTwo = &(_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) : _getGlobalVariable(valueString));
		}

		// Validate list access
		unsigned int valueIndexTwo = 0;
		if(isAccessingListTwo)
		{
			// Check if list index is valid
			if(_validateListIndex(*variableTwo, listIndexTwo))
			{
				valueIndexTwo = listIndexTwo;

				// Check if list item value is valid
				if(!(variableTwo->getValue(valueIndexTwo).getType() == ScriptValueType::INTEGER) &&
				   !(variableTwo->getValue(valueIndexTwo).getType() == ScriptValueType::DECIMAL))
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
			_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString).getValue(valueIndexTwo) : // Local variable
			_isGlobalVariableExisting(valueString) ? _getGlobalVariable(valueString).getValue(valueIndexTwo) : // Global variable
			_isIntegerValue(valueString) ? ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(_limitIntegerString(valueString))) : // Integer
			_isDecimalValue(valueString) ? ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(_limitDecimalString(valueString))) : // Decimal
			ScriptValue(_fe3d, ScriptValueType::EMPTY); // Empty

		// Check if arithmetic value is valid
		if(value.getType() == ScriptValueType::EMPTY)
		{
			_throwScriptError("invalid arithmetic value!");
			return;
		}

		// Execute arithmetic operation
		if((variableOne.getValue(valueIndexOne).getType() == ScriptValueType::INTEGER) && value.getType() == ScriptValueType::INTEGER) // INTEGER
		{
			// Retrieve current variable value
			int result = variableOne.getValue(valueIndexOne).getInteger();

			// Determine arithmetic type
			if(operatorString == ADDITION_KEYWORD)
			{
				result += value.getInteger();
			}
			else if(operatorString == SUBTRACTION_KEYWORD)
			{
				result -= value.getInteger();
			}
			else if(operatorString == MULTIPLICATION_KEYWORD)
			{
				result *= value.getInteger();
			}
			else if(operatorString == DIVISION_KEYWORD)
			{
				result /= value.getInteger();
			}

			// Limit integer
			result = ((result < 0) ? max(result, -1000000000) : min(result, 1000000000));

			// Set resulting value
			variableOne.getValue(valueIndexOne).setInteger(result);
		}
		else if((variableOne.getValue(valueIndexOne).getType() == ScriptValueType::DECIMAL) && value.getType() == ScriptValueType::DECIMAL) // DECIMAL
		{
			// Retrieve current variable value
			float result = variableOne.getValue(valueIndexOne).getDecimal();

			// Determine arithmetic type
			if(operatorString == ADDITION_KEYWORD)
			{
				result += value.getDecimal();
			}
			else if(operatorString == SUBTRACTION_KEYWORD)
			{
				result -= value.getDecimal();
			}
			else if(operatorString == MULTIPLICATION_KEYWORD)
			{
				result *= value.getDecimal();
			}
			else if(operatorString == DIVISION_KEYWORD)
			{
				result /= value.getDecimal();
			}

			// Limit decimal
			result = ((result < 0) ? max(result, -1000000000.0f) : min(result, 1000000000.0f));

			// Set resulting value
			variableOne.getValue(valueIndexOne).setDecimal(result);
		}
		else
		{
			_throwScriptError("arithmetic value not applicable to this variable!");
			return;
		}
	}
}