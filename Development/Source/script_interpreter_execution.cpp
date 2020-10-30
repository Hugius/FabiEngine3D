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
		unsigned int countedSpaces = _countFrontSpaces(scriptLineText);
		if (_hasThrownError) // Check if an error was thrown
		{
			return;
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

		// Validate a potentional scope change
		bool scopeChangeValidation = _validateScopeChange(countedSpaces, scriptLineText);
		if (_hasThrownError) // Check if an error was thrown
		{
			return;
		}
		else if (!scopeChangeValidation) // Current line outside of scope, skip
		{
			continue;
		}

		// Ignore empty lines
		if (scriptLineText.empty())
		{
			continue;
		}

		// Ignore comments
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