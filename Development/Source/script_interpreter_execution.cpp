#include "script_interpreter.hpp"

void ScriptInterpreter::_executeScript(const string& scriptID, ScriptType scriptType)
{
	// Detect infinite recursion
	if (_localVariablesStack.size() >= 100)
	{
		_fe3d.logger_throwWarning("too many script execution layers, perhaps infinite recursion?");
	}

	// Check if any engine warnings were thrown
	_checkEngineWarnings();

	// Skip the following lines of code if the last run caused an error
	if (_hasThrownError)
	{
		return;
	}

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
		// Save current amount of logged messages
		_lastLoggerMessageCount = _fe3d.logger_getMessageStack().size();

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
			_passedScopeChanger = false;
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
		else if (scriptLineText.substr(0, 5) == "math:") // Mathematical function
		{
			_processMathematicalFunctionCall(scriptLineText);
		}
		else if (scriptLineText.substr(0, 5) == "misc:") // Miscellaneous function
		{
			_processMiscellaneousFunctionCall(scriptLineText);
		}
		else if (scriptLineText.substr(0, _executeKeyword.size() + 1) == _executeKeyword + " ") // Execute another script
		{
			// Determine scriptname to execute and current script type
			std::istringstream iss(scriptLineText);
			string scriptToExecute;
			iss >> scriptToExecute >> scriptToExecute;
			auto& scriptList = (scriptType == ScriptType::INIT) ? _initScriptIDs : (scriptType == ScriptType::UPDATE) ? _updateScriptIDs : _destroyScriptIDs;
			
			// Check if script exists
			if (std::find(scriptList.begin(), scriptList.end(), scriptToExecute) != scriptList.end())
			{
				_executeScript(scriptToExecute, scriptType);
			}
			else
			{
				_throwScriptError("script \"" + scriptToExecute + "\" not found!");
				return;
			}
		}
		else if (scriptLineText.substr(0, _ifKeyword.size() + 1) == _ifKeyword + " ") // If statement
		{
			// Check if if statement ends with colon
			if (scriptLineText.back() == ':')
			{
				string conditionString = scriptLineText.substr((_ifKeyword.size() + 1), scriptLineText.size() - (_ifKeyword.size() + 2));

				// Check the condition of the if statement
				if (_checkConditionString(conditionString))
				{
					_scopeDepthStack.back()++;
					_scopeHasChanged = true;
					_lastConditionResult = true;
				}
				else
				{
					_passedScopeChanger = true;
					_lastConditionResult = false;
				}
				_lastScopeChanger = ScriptScopeChanger::IF;
			}
			else
			{
				_throwScriptError("if statement must end with colon!");
				return;
			}
		}
		else if (scriptLineText.substr(0, _elifKeyword.size() + 1) == _elifKeyword + " ") // Else if statement
		{
			// Check if in sequence with if statement
			if (_lastScopeChanger == ScriptScopeChanger::IF)
			{
				// Check if elif statement ends with colon
				if (scriptLineText.back() == ':')
				{
					string conditionString = scriptLineText.substr((_elifKeyword.size() + 1), scriptLineText.size() - (_elifKeyword.size() + 2));

					// Check the condition of the elif statement
					if (!_lastConditionResult && _checkConditionString(conditionString))
					{
						_scopeDepthStack.back()++;
						_scopeHasChanged = true;
						_lastConditionResult = true;
					}
					else
					{
						_passedScopeChanger = true;
					}
					_lastScopeChanger = ScriptScopeChanger::ELIF;
				}
				else
				{
					_throwScriptError("elif statement must end with colon!");
					return;
				}
			}
			else
			{
				_throwScriptError("elif statement can only come after if statement!");
				return;
			}
		}
		else if (scriptLineText.substr(0, _elseKeyword.size()) == _elseKeyword) // Else statement
		{
			// Check if in sequence with if or elif statement
			if (_lastScopeChanger == ScriptScopeChanger::IF || _lastScopeChanger == ScriptScopeChanger::ELIF)
			{
				// Check if if statement ends with colon
				if (scriptLineText.back() == ':')
				{
					if (scriptLineText.size() == (_elseKeyword.size() + 1))
					{
						// Check if all previous conditions failed
						if (!_lastConditionResult)
						{
							_scopeDepthStack.back()++;
							_scopeHasChanged = true;
						}
						else
						{
							_passedScopeChanger = true;
						}
						_lastScopeChanger = ScriptScopeChanger::ELSE;
					}
					else
					{
						_throwScriptError("else statement cannot have a condition!");
						return;
					}
				}
				else
				{
					_throwScriptError("else statement must end with colon!");
					return;
				}
			}
			else
			{
				_throwScriptError("else statement can only come after if or elif statement!");
				return;
			}
		}
		else if // Create local variable
			(
				scriptLineText.substr(0, _vec3Keyword.size() + 1) == _vec3Keyword + " " ||
				scriptLineText.substr(0, _stringKeyword.size()  + 1) == _stringKeyword  + " " ||
				scriptLineText.substr(0, _decimalKeyword.size() + 1) == _decimalKeyword + " " ||
				scriptLineText.substr(0, _integerKeyword.size() + 1) == _integerKeyword + " " ||
				scriptLineText.substr(0, _booleanKeyword.size() + 1) == _booleanKeyword + " "
			)
		{
			_processVariableDefinition(scriptLineText, ScriptVariableScope::LOCAL, false);
		}
		else if (scriptLineText.substr(0, _globalKeyword.size() + 1) == _globalKeyword + " ") // Create global variable
		{
			_processVariableDefinition(scriptLineText, ScriptVariableScope::GLOBAL, false);
		}
		else if (scriptLineText.substr(0, _editKeyword.size() + 1) == _editKeyword + " ") // Edit existing variable
		{
			_processVariableDefinition(scriptLineText, ScriptVariableScope::UNKNOWN, true);
		}
		else if //Variable arithmetic
			(
				scriptLineText.substr(0, _additionKeyword.size() + 1) == _additionKeyword + " " ||
				scriptLineText.substr(0, _subtractionKeyword.size() + 1) == _subtractionKeyword + " " ||
				scriptLineText.substr(0, _multiplicationKeyword.size() + 1) == _multiplicationKeyword + " " ||
				scriptLineText.substr(0, _divisionKeyword.size() + 1) == _divisionKeyword + " " ||
				scriptLineText.substr(0, _negationKeyword.size() + 1) == _negationKeyword + " "
			)
		{
			_processVariableArithmetic(scriptLineText);
		}
		else if (scriptLineText.substr(0, _castingKeyword.size() + 1) == _castingKeyword + " ") // Variable type casting
		{
			_processVariableTypecast(scriptLineText);
		}
		else if (scriptLineText.substr(0, _concatenationKeyword.size() + 1) == _concatenationKeyword + " ") // String concatenation
		{
			_processStringConcatenation(scriptLineText);
		}
		else // Invalid keyword
		{
			_throwScriptError("unknown keyword!");
			return;
		}

		// Check if any engine warnings were thrown
		_checkEngineWarnings();

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