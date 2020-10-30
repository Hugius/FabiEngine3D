#include "script_interpreter.hpp"

void ScriptInterpreter::_executeScript(const string& scriptID, ScriptType scriptType)
{
	// Save local state of script currently being executed
	_localVariablesStack.push_back({});
	_currentScriptStackIDs.push_back(scriptID);
	_currentLineStackIndices.push_back(0);
	_scopeDepthStack.push_back(0);

	// Retrieve script file
	auto scriptFile = _script.getScriptFile(scriptID);

	// Interpret every line from top to bottom in script
	for (size_t lineIndex = 0; lineIndex < scriptFile->getLineCount(); lineIndex++)
	{
		// Save index of line of script currently being executed
		_currentLineStackIndices.back() = lineIndex;

		// Retrieve line text
		string scriptLineText = scriptFile->getLineText(lineIndex);

		// Count front spaces
		unsigned int countedSpaces = 0;
		for (unsigned int i = 0; i < scriptLineText.size(); i++)
		{
			// Check if current character is a space
			if (scriptLineText[i] == ' ')
			{
				// Check if any text comes after the last space character
				if (i == (scriptLineText.size() - 1))
				{
					_throwScriptError("useless indentation!");
					return;
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
		
		// Check if indentation syntax is correct
		if ((countedSpaces % _spacesPerIndent) == 0)
		{
			scriptLineText.erase(0, countedSpaces); // Remove front spaces
		}
		else
		{
			_throwScriptError("invalid indentation!");
			return;
		}

		// Detect scope changes
		unsigned int currentLineScopeDepth = countedSpaces / _spacesPerIndent;
		if((currentLineScopeDepth != _scopeDepthStack.back()) && _scopeHasChanged) // Check syntax after scope change
		{
			_throwScriptError("no indented code after scope change!");
			return;
		}
		else if(currentLineScopeDepth < _scopeDepthStack.back()) // End of current scope
		{
			_scopeDepthStack.back() = currentLineScopeDepth;
		}
		else if (currentLineScopeDepth > _scopeDepthStack.back()) // Outside of current scope
		{
			continue;
		}
		_scopeHasChanged = false;

		// Empty lines are ignored
		if (scriptLineText.empty())
		{
			continue;
		}

		// Comments are ignored
		if (scriptLineText.substr(0, 3) == "///")
		{
			continue;
		}

		// Determine keyword type
		if (scriptLineText.substr(0, 5) == "fe3d:") // Engine function
		{
			_processEngineFunctionCall(scriptLineText);
		}
		else if (scriptLineText.substr(0, _ifKeyword.size() + 1) == _ifKeyword + " ") // If statement
		{
			// Check if if statement ends with colon
			if (scriptLineText.back() == ':')
			{
				if (_checkIfStatement(scriptLineText.substr(3, scriptLineText.size() - 4)))
				{
					_scopeDepthStack.back()++;
					_scopeHasChanged = true;
				}
			}
			else
			{
				_throwScriptError("if statement must end with colon!");
				return;
			}
		}
		else if // Local variable
			(
				scriptLineText.substr(0, _stringKeyword.size()  + 1) == _stringKeyword  + " " ||
				scriptLineText.substr(0, _decimalKeyword.size() + 1) == _decimalKeyword + " " ||
				scriptLineText.substr(0, _integerKeyword.size() + 1) == _integerKeyword + " " ||
				scriptLineText.substr(0, _booleanKeyword.size() + 1) == _booleanKeyword + " "
			)
		{
			_processVariableDefinition(scriptLineText, ScriptVariableScope::LOCAL);
		}
		else if (scriptLineText.substr(0, _globalKeyword.size() + 1) == _globalKeyword + " ") // Global variable
		{
			_processVariableDefinition(scriptLineText, ScriptVariableScope::GLOBAL);
		}
		else
		{
			_throwScriptError("unknown keyword!");
			return;
		}

		// Skip the following lines of code if the last run caused an error
		if (_hasThrownError)
		{
			return;
		}
	}

	// End of this script file's execution
	_localVariablesStack.pop_back();
	_currentScriptStackIDs.pop_back();
	_currentLineStackIndices.pop_back();
	_scopeDepthStack.pop_back();
}