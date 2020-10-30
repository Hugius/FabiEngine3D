#include "script_interpreter.hpp"

bool ScriptInterpreter::_isStringValue(const string& value)
{
	// Check if value has characters at all
	if (value.empty())
	{
		return false;
	}

	return value.size() >= 2 && (value.front() == '"' && value.back() == '"');
}

bool ScriptInterpreter::_isDecimalValue(const string& value)
{
	// Check if value has characters at all
	if (value.empty())
	{
		return false;
	}

	// Check if value is perhaps negative
	unsigned int startingIndex = 0;
	if (value.front() == '-')
	{
		startingIndex = 1;
	}

	// Validate every character
	unsigned dots = 0;
	for (unsigned int i = startingIndex; i < value.size(); i++)
	{
		if (!isdigit(value[i]) && value[i] != '.')
		{
			return false;
		}

		// Count dots in value
		if (value[i] == '.')
		{
			dots++;
		}
	}

	// Check if value is a valid decimal
	return (value.size() >= 3) && (isdigit(value.front()) && isdigit(value.back())) && (dots == 1);
}

bool ScriptInterpreter::_isIntegerValue(const string& value)
{
	// Check if value has characters at all
	if (value.empty())
	{
		return false;
	}

	// Check if value is perhaps negative
	unsigned int startingIndex = 0;
	if (value.front() == '-')
	{
		startingIndex = 1;
	}

	// Check if every character is a digit
	for (unsigned int i = startingIndex; i < value.size(); i++)
	{
		if (!isdigit(value[i]))
		{
			return false;
		}
	}

	return true;
}

bool ScriptInterpreter::_isBooleanValue(const string& value)
{
	return (value == "<true>" || value == "<false>");
}

bool ScriptInterpreter::_isLocalVariableExisting(const string& variableID)
{
	for (auto& variable : _localVariablesStack.back())
	{
		if (variableID == variable.getID())
		{
			return true;
		}
	}

	return false;
}

bool ScriptInterpreter::_isGlobalVariableExisting(const string& variableID)
{
	for (auto& variable : _globalVariables)
	{
		if (variableID == variable.getID())
		{
			return true;
		}
	}

	return false;
}

ScriptVariable& ScriptInterpreter::_getLocalVariable(const string& variableID)
{
	for (auto& variable : _localVariablesStack.back())
	{
		if (variableID == variable.getID())
		{
			return variable;
		}
	}

	_fe3d.logger_throwError("Local script variable \"" + variableID + "\" not found!"); 
}

ScriptVariable& ScriptInterpreter::_getGlobalVariable(const string& variableID)
{
	for (auto& variable : _globalVariables)
	{
		if (variableID == variable.getID())
		{
			return variable;
		}
	}

	_fe3d.logger_throwError("Global script variable \"" + variableID + "\" not found!");
}

unsigned int ScriptInterpreter::_countFrontSpaces(const string& scriptLineText)
{
	int countedSpaces = 0;

	// For every character
	for (unsigned int i = 0; i < scriptLineText.size(); i++)
	{
		// Check if current character is a space
		if (scriptLineText[i] == ' ')
		{
			// Check if any text comes after the last space character
			if (i == (scriptLineText.size() - 1))
			{
				_throwScriptError("useless indentation!");
				return 0;
			}
			else
			{
				countedSpaces++;
			}
		}
		else
		{
			break;
		}
	}

	return countedSpaces;
}

bool ScriptInterpreter::_validateScopeChange(unsigned int countedSpaces, const string& scriptLineText)
{
	unsigned int currentLineScopeDepth = countedSpaces / _spacesPerIndent;

	// Check if there is any code right after a scope change
	if (_scopeHasChanged && ((currentLineScopeDepth != _scopeDepthStack.back()) || scriptLineText.substr(0, 3) == "///"))
	{
		_throwScriptError("no indented code after scope change!");
	}
	else if (currentLineScopeDepth < _scopeDepthStack.back()) // End of current scope
	{
		_scopeDepthStack.back() = currentLineScopeDepth;
	}
	else if (currentLineScopeDepth > _scopeDepthStack.back()) // Outside of current scope, so don't execute current line
	{
		return false;
	}

	_scopeHasChanged = false;
	return true;
}

void ScriptInterpreter::_throwScriptError(const string& message)
{
	_fe3d.logger_throwWarning("ERROR @ script \"" + _currentScriptStackIDs.back() + "\" @ line " + to_string(_currentLineStackIndices.back() + 1) + ": " + message);
	_hasThrownError = true;
}

bool ScriptInterpreter::hasThrownError()
{
	return _hasThrownError;
}