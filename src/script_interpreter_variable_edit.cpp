#include "script_interpreter.hpp"
#include "logger.hpp"

void ScriptInterpreter::_processVariableAlteration(const string& scriptLine)
{
	// Temporary values
	string nameString = "";
	string equalSignString = "";
	string valueString = "";
	bool isConstant = false;

	// Extract name & equal sign
	string words[2] = {"", ""};
	unsigned int wordIndex = 0;
	for(const auto& c : scriptLine.substr(EDIT_KEYWORD.size() + 1))
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
	nameString = words[0];
	equalSignString = words[1];

	// Check if variable name is missing
	if(nameString.empty())
	{
		_throwScriptError("variable name missing!");
		return;
	}

	// Check if equal string is present
	if(equalSignString == "=")
	{
		// Check if value is present
		if(scriptLine.size() - 1 >= scriptLine.find('=') + 2)
		{
			// Extract remaining text (value)
			valueString = scriptLine.substr(scriptLine.find('=') + 2);
		}
		else
		{
			_throwScriptError("value missing!");
			return;
		}
	}
	else
	{
		_throwScriptError("equal sign missing!");
		return;
	}

	// Check if changing individual value from list variable
	bool isAccessingListOne = false;
	auto listIndexOne = _extractListIndexFromString(nameString, isAccessingListOne);

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

	// A constant variable should not be changed
	if(variableOne.isConstant())
	{
		_throwScriptError("variable cannot be changed: it is constant!");
		return;
	}

	// Validate list access
	unsigned int valueIndexOne = 0;
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

	// Temporary values
	bool isSingleVariable = (variableOne.getType() == ScriptVariableType::SINGLE || isAccessingListOne);
	bool isStringVariable = (variableOne.getValue(valueIndexOne).getType() == ScriptValueType::STRING);
	bool isDecimalVariable = (variableOne.getValue(valueIndexOne).getType() == ScriptValueType::DECIMAL);
	bool isIntegerVariable = (variableOne.getValue(valueIndexOne).getType() == ScriptValueType::INTEGER);
	bool isBooleanVariable = (variableOne.getValue(valueIndexOne).getType() == ScriptValueType::BOOLEAN);

	// Determine value type
	if(variableOne.getType() == ScriptVariableType::MULTIPLE && _isListValue(valueString)) // LIST
	{
		// Removing the "" around the string content
		string listString = valueString.substr(1);
		listString.pop_back();

		// Extract the values
		auto values = _extractValuesFromListString(listString);
		variableOne.changeValues(values);
	}
	else if(isSingleVariable && isStringVariable && _isStringValue(valueString)) // STRING
	{
		valueString.erase(valueString.begin());
		valueString.pop_back();
		variableOne.getValue(valueIndexOne).setString(valueString);
	}
	else if(isSingleVariable && isDecimalVariable && _isDecimalValue(valueString)) // DECIMAL
	{
		variableOne.getValue(valueIndexOne).setDecimal(stof(_limitDecimalString(valueString)));
	}
	else if(isSingleVariable && isIntegerVariable && _isIntegerValue(valueString)) // INTEGER
	{
		variableOne.getValue(valueIndexOne).setInteger(stoi(_limitIntegerString(valueString)));
	}
	else if(isSingleVariable && isBooleanVariable && _isBooleanValue(valueString)) // BOOLEAN
	{
		variableOne.getValue(valueIndexOne).setBoolean(valueString == "<true>");
	}
	else if(isSingleVariable && isBooleanVariable && ((valueString.front() == '(') && (valueString.back() == ')'))) // BOOLEAN
	{
		valueString.erase(valueString.begin());
		valueString.pop_back();
		variableOne.getValue(valueIndexOne).setBoolean(_checkConditionString(valueString));
	}
	else if(valueString.substr(0, 5) == "fe3d:" || valueString.substr(0, 5) == "math:" || valueString.substr(0, 5) == "misc:") // FUNCTION
	{
		// Save current logger message count
		auto loggerMessageCount = Logger::getMessageCount();

		// Call function
		auto values =
			(valueString.substr(0, 5) == "fe3d:") ? _processEngineFunctionCall(valueString) :
			(valueString.substr(0, 5) == "math:") ? _processMathematicalFunctionCall(valueString) :
			_processMiscellaneousFunctionCall(valueString);

		// Check if any error was thrown
		_checkEngineWarnings(loggerMessageCount);
		if(_hasThrownError)
		{
			return;
		}

		if(variableOne.getType() == ScriptVariableType::MULTIPLE) // Variable is a list
		{
			// Check if function returned any empty values
			for(const auto& value : values)
			{
				if(value.getType() == ScriptValueType::EMPTY)
				{
					_throwScriptError("function cannot return empty values!");
					return;
				}
			}

			// Change list values
			variableOne.changeValues(values);
		}
		else if(values.empty()) // Function returned no values
		{
			_throwScriptError("function did not return any values!");
			return;
		}
		else if(values.size() > 1) // Function returned too many values
		{
			_throwScriptError("function returned too many values!");
			return;
		}
		else if(values[0].getType() == ScriptValueType::EMPTY) // Function returned an empty value
		{
			_throwScriptError("function must return a value!");
			return;
		}
		else if(isSingleVariable && isStringVariable && (values[0].getType() == ScriptValueType::STRING)) // STRING
		{
			variableOne.getValue(valueIndexOne).setString(values[0].getString());
		}
		else if(isSingleVariable && isDecimalVariable && (values[0].getType() == ScriptValueType::DECIMAL)) // DECIMAL
		{
			variableOne.getValue(valueIndexOne).setDecimal(values[0].getDecimal());
		}
		else if(isSingleVariable && isIntegerVariable && (values[0].getType() == ScriptValueType::INTEGER)) // INTEGER
		{
			variableOne.getValue(valueIndexOne).setInteger(values[0].getInteger());
		}
		else if(isSingleVariable && isBooleanVariable && (values[0].getType() == ScriptValueType::BOOLEAN)) // BOOLEAN
		{
			variableOne.getValue(valueIndexOne).setBoolean(values[0].getBoolean());
		}
		else
		{
			_throwScriptError("function type does not match the variable type!");
			return;
		}
	}
	else
	{
		// Check if accessing individual value from list variable
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

		// Check if using another variable as value
		if(!_isLocalVariableExisting(valueString) && !_isGlobalVariableExisting(valueString))
		{
			_throwScriptError("invalid value!");
			return;
		}

		// Retrieve other value
		auto variableTwo = (_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) : _getGlobalVariable(valueString));

		// Validate list access
		unsigned int valueIndexTwo = 0;
		if(isAccessingListTwo)
		{
			// Check if list index is valid
			if(_validateListIndex(variableTwo, listIndexTwo))
			{
				valueIndexTwo = listIndexTwo;
			}
			else // Error
			{
				return;
			}
		}

		// Check if the value types match
		bool isSingleVariable = (variableTwo.getType() == ScriptVariableType::SINGLE || isAccessingListTwo);
		if(isSingleVariable && (variableOne.getValue(valueIndexOne).getType() == variableTwo.getValue(valueIndexTwo).getType()))
		{
			variableOne.changeValue(variableTwo.getValue(valueIndexTwo), valueIndexOne);
		}
		else
		{
			_throwScriptError("variable types do not match!");
			return;
		}
	}
}