#include "script_interpreter.hpp"

void ScriptInterpreter::_executeScript(const string& scriptID, ScriptType scriptType)
{
	// Save ID of script currently being executed
	_localVariablesStack.push_back({});
	_currentScriptStackIDs.push_back(scriptID);
	_currentLineStackIndices.push_back(0);

	// Retrieve script file
	auto scriptFile = _script.getScriptFile(scriptID);

	// Interpret every line from top to bottom in script
	for (size_t lineIndex = 0; lineIndex < scriptFile->getLineCount(); lineIndex++)
	{
		// Skip the following lines of code if the last run caused an error
		if (_hasThrownError)
		{
			break;
		}

		// Save index of line of script currently being executed
		_currentLineStackIndices.back() = lineIndex;

		// Retrieve line text
		string scriptLine = scriptFile->getLineText(lineIndex);

		// Check if line is not empty or META text
		if (scriptLine.empty() || scriptLine.substr(0, _metaKeyword.size()) == _metaKeyword)
		{
			continue;
		}

		// Determine keyword type
		if (scriptLine.substr(0, 5) == "fe3d:") // Engine function
		{
			_processEngineFunctionCall(scriptLine);
		}
		else if (scriptLine.substr(0, _ifKeyword.size() + 1) == _ifKeyword + " ") // If statement
		{
			// Check if if statement ends with colon
			if (scriptLine.back() == ':')
			{
				if (_checkIfStatement(scriptLine.substr(3, scriptLine.size() - 4)))
				{

				}
				else
				{

				}
			}
			else
			{
				_throwScriptError("if statement must end with colon!");
			}
		}
		else if // Local variable
			(
				scriptLine.substr(0, _stringKeyword.size() + 1) == _stringKeyword + " " ||
				scriptLine.substr(0, _decimalKeyword.size() + 1) == _decimalKeyword + " " ||
				scriptLine.substr(0, _integerKeyword.size() + 1) == _integerKeyword + " " ||
				scriptLine.substr(0, _booleanKeyword.size() + 1) == _booleanKeyword + " "
			)
		{
			_processVariableDefinition(scriptLine, ScriptVariableScope::LOCAL);
		}
		else if (scriptLine.substr(0, _globalKeyword.size() + 1) == _globalKeyword + " ") // Global variable
		{
			_processVariableDefinition(scriptLine, ScriptVariableScope::GLOBAL);
		}
		else
		{
			_throwScriptError("unknown keyword!");
			break;
		}
	}

	// End of this script file's execution
	_localVariablesStack.pop_back();
	_currentScriptStackIDs.pop_back();
	_currentLineStackIndices.pop_back();
}