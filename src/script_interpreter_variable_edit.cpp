#include "script_interpreter.hpp"
#include "logger.hpp"

void ScriptInterpreter::_processVariableAlteration(const string& scriptLine)
{
	// Extract variable name & equal sign
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
	string nameString = words[0];
	string equalSignString = words[1];

	// Check if variable name is missing
	if(nameString.empty())
	{
		_throwScriptError("variable name missing!");
		return;
	}

	// Check if equal string is missing
	if(equalSignString != "=")
	{
		_throwScriptError("equal sign missing!");
		return;
	}

	// Check if value is missing
	auto minLineSize = (scriptLine.find('=') + 3);
	if(scriptLine.size() < minLineSize)
	{
		_throwScriptError("value missing!");
		return;
	}

	// Extract value
	string valueString = scriptLine.substr(minLineSize - 1);

	// Prepare list access
	bool isAccessingLeftList = false;
	auto leftListIndex = _extractListIndexFromString(nameString, isAccessingLeftList);

	// Check if any error was thrown
	if(_hasThrownError)
	{
		return;
	}

	// Remove list accessing characters
	if(isAccessingLeftList)
	{
		auto isOpeningBracketFound = find(nameString.begin(), nameString.end(), '[');
		auto bracketIndex = static_cast<unsigned int>(distance(nameString.begin(), isOpeningBracketFound));
		nameString = nameString.substr(0, bracketIndex);
	}

	// Check if left variable existing
	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("variable \"" + nameString + "\" not existing!");
		return;
	}

	// Retrieve left variable
	auto& leftVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	// Check if left variable is constant
	if(leftVariable.isConstant())
	{
		_throwScriptError("CONST variables cannot be changed!");
		return;
	}

	// Validate list access
	unsigned int leftValueIndex = 0;
	if(isAccessingLeftList)
	{
		// Check if list index is valid
		if(_validateListIndex(leftVariable, leftListIndex))
		{
			leftValueIndex = leftListIndex;
		}
		else // Error
		{
			return;
		}
	}

	// Temporary values
	bool isSingleVariable = (leftVariable.getType() == ScriptVariableType::SINGLE || isAccessingLeftList);
	bool isStringVariable = (leftVariable.getValue(leftValueIndex).getType() == ScriptValueType::STRING);
	bool isDecimalVariable = (leftVariable.getValue(leftValueIndex).getType() == ScriptValueType::DECIMAL);
	bool isIntegerVariable = (leftVariable.getValue(leftValueIndex).getType() == ScriptValueType::INTEGER);
	bool isBooleanVariable = (leftVariable.getValue(leftValueIndex).getType() == ScriptValueType::BOOLEAN);

	// Determine value type
	if(leftVariable.getType() == ScriptVariableType::MULTIPLE && _isListValue(valueString))
	{
		// Remove the ""
		string listString = valueString.substr(1);
		listString.pop_back();

		// Extract the values
		auto values = _extractValuesFromListString(listString);
		leftVariable.setValues(values);
	}
	else if(isSingleVariable && isStringVariable && _isStringValue(valueString))
	{
		// Remove the ""
		valueString.erase(valueString.begin());
		valueString.pop_back();

		// Set value
		leftVariable.getValue(leftValueIndex).setString(valueString);
	}
	else if(isSingleVariable && isDecimalVariable && _isDecimalValue(valueString))
	{
		leftVariable.getValue(leftValueIndex).setDecimal(stof(_limitDecimalString(valueString)));
	}
	else if(isSingleVariable && isIntegerVariable && _isIntegerValue(valueString))
	{
		leftVariable.getValue(leftValueIndex).setInteger(stoi(_limitIntegerString(valueString)));
	}
	else if(isSingleVariable && isBooleanVariable && _isBooleanValue(valueString))
	{
		leftVariable.getValue(leftValueIndex).setBoolean(valueString == "<true>");
	}
	else if(isSingleVariable && isBooleanVariable && ((valueString[0] == '(') && (valueString.back() == ')')))
	{
		// Remove the ()
		valueString.erase(valueString.begin());
		valueString.pop_back();

		// Set value
		leftVariable.getValue(leftValueIndex).setBoolean(_checkConditionString(valueString));
	}
	else if(valueString.substr(0, 5) == "fe3d:" || valueString.substr(0, 5) == "math:" || valueString.substr(0, 5) == "misc:")
	{
		// Save current logger message count
		auto loggerMessageCount = Logger::getMessageCount();

		// Call function
		auto returnValues =
			(valueString.substr(0, 5) == "fe3d:") ? _processEngineFunctionCall(valueString) :
			(valueString.substr(0, 5) == "math:") ? _processMathematicalFunctionCall(valueString) :
			_processMiscellaneousFunctionCall(valueString);

		// Check if any error was thrown
		_checkEngineWarnings(loggerMessageCount);
		if(_hasThrownError)
		{
			return;
		}

		// Check if function returned any empty values
		for(const auto& value : returnValues)
		{
			if(value.getType() == ScriptValueType::EMPTY)
			{
				_throwScriptError("function returned empty value!");
				return;
			}
		}

		// Process return values
		if(leftVariable.getType() == ScriptVariableType::MULTIPLE)
		{
			leftVariable.setValues(returnValues);
		}
		else if(returnValues.empty())
		{
			_throwScriptError("function returned no values!");
			return;
		}
		else if(returnValues.size() > 1)
		{
			_throwScriptError("function returned too many values!");
			return;
		}
		else if(returnValues[0].getType() == ScriptValueType::EMPTY)
		{
			_throwScriptError("function must return value!");
			return;
		}
		else if(isSingleVariable && isStringVariable && (returnValues[0].getType() == ScriptValueType::STRING))
		{
			leftVariable.getValue(leftValueIndex).setString(returnValues[0].getString());
		}
		else if(isSingleVariable && isDecimalVariable && (returnValues[0].getType() == ScriptValueType::DECIMAL))
		{
			leftVariable.getValue(leftValueIndex).setDecimal(returnValues[0].getDecimal());
		}
		else if(isSingleVariable && isIntegerVariable && (returnValues[0].getType() == ScriptValueType::INTEGER))
		{
			leftVariable.getValue(leftValueIndex).setInteger(returnValues[0].getInteger());
		}
		else if(isSingleVariable && isBooleanVariable && (returnValues[0].getType() == ScriptValueType::BOOLEAN))
		{
			leftVariable.getValue(leftValueIndex).setBoolean(returnValues[0].getBoolean());
		}
		else
		{
			_throwScriptError("function returned incorrect value type!");
			return;
		}
	}
	else
	{
		// Prepare list access
		bool isAccessingRightList = false;
		auto rightListIndex = _extractListIndexFromString(valueString, isAccessingRightList);

		// Check if any error was thrown
		if(_hasThrownError)
		{
			return;
		}

		// Remove list accessing characters
		if(isAccessingRightList)
		{
			auto isOpeningBracketFound = find(valueString.begin(), valueString.end(), '[');
			auto bracketIndex = static_cast<unsigned int>(distance(valueString.begin(), isOpeningBracketFound));
			valueString = valueString.substr(0, bracketIndex);
		}

		// Check if right variable is not existing
		if(!_isLocalVariableExisting(valueString) && !_isGlobalVariableExisting(valueString))
		{
			_throwScriptError("variable \"" + valueString + "\" not existing!");
			return;
		}

		// Retrieve other value
		const auto& rightVariable = (_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) : _getGlobalVariable(valueString));

		// Validate list access
		unsigned int rightValueIndex = 0;
		if(isAccessingRightList)
		{
			// Check if list index is invalid
			if(!_validateListIndex(rightVariable, rightListIndex))
			{
				return;
			}

			// Copy list index
			rightValueIndex = rightListIndex;
		}

		// Determine right variable type
		if((leftVariable.getType() == ScriptVariableType::MULTIPLE) && (rightVariable.getType() == ScriptVariableType::MULTIPLE))
		{
			// Extract values
			vector<ScriptValue> values = {};
			for(unsigned int i = 0; i < rightVariable.getValueCount(); i++)
			{
				values.push_back(rightVariable.getValue(i));
			}

			// Set values
			leftVariable.setValues(values);
		}
		else if(leftVariable.getValue(leftValueIndex).getType() == rightVariable.getValue(rightValueIndex).getType())
		{
			leftVariable.setValue(rightVariable.getValue(rightValueIndex), leftValueIndex);
		}
		else
		{
			_throwScriptError("value types not matching!");
			return;
		}
	}
}