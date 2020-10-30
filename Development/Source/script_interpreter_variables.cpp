#include "script_interpreter.hpp"

void ScriptInterpreter::_processVariableDefinition(const string& scriptLine, ScriptVariableScope scope)
{
	// Temporary values
	std::istringstream iss(scriptLine);
	string variableScope = "";
	string variableType = "";
	string variableID = "";
	string equalSign = "";
	string variableValue = "";

	// Extract GLOB keyword
	if (scope == ScriptVariableScope::GLOBAL)
	{
		string keyword;
		iss >> keyword;
	}

	// Extract CONST keyword
	string possibleConstKeyword;
	iss >> possibleConstKeyword;
	bool isConstant = (possibleConstKeyword == "CONST");

	// Extract other variable data
	if (isConstant)
	{
		iss >> variableType >> variableID >> equalSign >> variableValue;
	}
	else
	{
		variableType = possibleConstKeyword;
		iss >> variableID >> equalSign >> variableValue;
	}

	// Check if variable type is valid
	if (variableType == _stringKeyword || variableType == _decimalKeyword || variableType == _integerKeyword || variableType == _booleanKeyword)
	{
		// Validate variable name
		bool validName = !variableID.empty() && variableID.substr(0, 5) != "fe3d:" && !isdigit(variableID.front() && isalnum(variableID.front())) &&
			variableID != "<true>" && variableID != "<false>";

		// Forbidden variable names
		for (auto& word : { _metaKeyword, _executeKeyword, _ifKeyword, _elseifKeyword, _elseKeyword, _globalKeyword,
			_constKeyword, _stringKeyword, _decimalKeyword, _integerKeyword, _booleanKeyword, _isKeyword,
			_notKeyword, _andKeyword, _orKeyword, _moreKeyword, _lessKeyword })
		{
			validName = validName && (variableID != word);
		}

		// Check if variable name is valid
		if (validName)
		{
			// Retrieve the repsective list of variables
			auto& variableList = (scope == ScriptVariableScope::LOCAL) ? _localVariablesStack.back() : _globalVariables;

			// Check if a local variable has already been defined
			if (scope == ScriptVariableScope::LOCAL)
			{
				if (_isLocalVariableExisting(variableID))
				{
					_throwScriptError("local variable \"" + variableID + "\" already defined!");
					return;
				}
			}
			else // Global variable
			{
				if (_isGlobalVariableExisting(variableID))
				{
					return;
				}
			}

			// Check if equal sign is valid
			if (equalSign == "=")
			{
				// Check if value is not empty
				if (variableValue.empty())
				{
					_throwScriptError("no variable type found!");
				}
				else
				{
					// Check if value is of the right type
					if (variableType == _stringKeyword && _isStringValue(variableValue))
					{
						// Removing the "" around the string content
						variableValue.erase(variableValue.begin());
						variableValue.pop_back();

						// Add new string variable
						auto value = ScriptValue(_fe3d, ScriptValueType::STRING, variableValue);
						variableList.push_back(ScriptVariable(_fe3d, scope, variableID, isConstant, value));
					}
					else if (variableType == _decimalKeyword && _isDecimalValue(variableValue))
					{
						// Add new string variable
						auto value = ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(variableValue));
						variableList.push_back(ScriptVariable(_fe3d, scope, variableID, isConstant, value));
					}
					else if (variableType == _integerKeyword && _isIntegerValue(variableValue))
					{
						// Add new string variable
						auto value = ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(variableValue));
						variableList.push_back(ScriptVariable(_fe3d, scope, variableID, isConstant, value));
					}
					else if (variableType == _booleanKeyword && _isBooleanValue(variableValue))
					{
						// Add new string variable
						auto value = ScriptValue(_fe3d, ScriptValueType::BOOLEAN, (variableValue == "<true>"));
						variableList.push_back(ScriptVariable(_fe3d, scope, variableID, isConstant, value));
					}
					else if (variableValue.substr(0, 5) == "fe3d:")
					{
						auto value = _processEngineFunctionCall(variableValue).back();

						// Check if value is of the right type
						if ((variableType == _stringKeyword && value.getType() == ScriptValueType::STRING) ||
							(variableType == _decimalKeyword && value.getType() == ScriptValueType::DECIMAL) ||
							(variableType == _integerKeyword && value.getType() == ScriptValueType::INTEGER) ||
							(variableType == _booleanKeyword && value.getType() == ScriptValueType::BOOLEAN))
						{
							variableList.push_back(ScriptVariable(_fe3d, scope, variableID, isConstant, value));
						}
						else
						{
							_throwScriptError("invalid variable value!");
						}
					}
					else
					{
						_throwScriptError("invalid variable value!");
					}
				}
			}
			else
			{
				_throwScriptError("invalid variable syntax!");
			}
		}
		else
		{
			_throwScriptError("invalid variable name!");
		}
	}
	else
	{
		_throwScriptError("invalid variable type!");
	}

	// No characters allowed after variable creation statement
	string temp;
	if ((iss >> temp) || scriptLine.back() == ' ')
	{
		_throwScriptError("invalid variable creation syntax!");
	}
}