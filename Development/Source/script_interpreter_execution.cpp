#include "script_interpreter.hpp"

void ScriptInterpreter::_executeScript(const string& scriptID, ScriptType scriptType)
{
	// Temporary local values for this script run
	vector<unsigned int> loopLineIndices;
	vector<unsigned int> loopScopeDepths;
	vector<ScriptConditionStatement> conditionStatements;
	unsigned int scopeDepth = 0;
	unsigned int totalLoops = 0;

	// Set current script run data
	_currentScriptIDsStack.push_back(scriptID);
	_currentLineIndexStack.push_back(0);
	_localVariablesStack.push_back({});

	// Increase execution depth
	_executionDepth++;

	// Detect infinite recursion
	if (_executionDepth >= _maxExecutionDepth)
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

	// Retrieve script file
	auto scriptFile = _script.getScriptFile(scriptID);

	// Interpret every line from top to bottom in script
	for (unsigned int lineIndex = 0; lineIndex < scriptFile->getLineCount(); lineIndex++)
	{
		// Save current amount of logged messages
		_lastLoggerMessageCount = _fe3d.logger_getMessageStack().size();

		// Save index of line of script currently being executed
		_currentLineIndexStack.back() = lineIndex;

		// Retrieve line text
		string scriptLineText = scriptFile->getLineText(lineIndex);
		stringstream scriptLineTextStream = stringstream(scriptLineText);
		string noWhiteSpace;
		scriptLineTextStream >> noWhiteSpace;

		// Ignore comments
		if (noWhiteSpace.substr(0, 3) == "///")
		{
			continue;
		}
		
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

		// Calculate current scope depth
		unsigned int currentLineScopeDepth = countedSpaces / _spacesPerIndent;
		
		// Detect end of loop
		bool endOfLoop = false;
		if (!loopLineIndices.empty())
		{
			if (currentLineScopeDepth <= loopScopeDepths.back()) // End of current loop scope
			{
				if (totalLoops >= _maxLoopsPerFrame) // Infinite loop
				{
					_throwScriptError("maximum amount of loops reached, perhaps infinite looping?");
					return;
				}
				else // Normal loop
				{
					// Go back to current loop's beginning
					lineIndex = loopLineIndices.back();
					scopeDepth = loopScopeDepths.back() + 1;
					totalLoops++;
					continue;
				}
			}
			else if (lineIndex == scriptFile->getLineCount() - 1) // End of script
			{
				if (totalLoops >= _maxLoopsPerFrame) // Infinite loop
				{
					_throwScriptError("maximum amount of loops reached, perhaps infinite looping?");
					return;
				}
				else // Normal loop
				{
					endOfLoop = true; // Go back to current loop's beginning after executing current scriptline
				}
			}
		}

		// Validate a potentional scope change
		bool scopeChangeValidation = _validateScopeChange(countedSpaces, scriptLineText, scopeDepth);
		if (_hasThrownError) // Check if an error was thrown
		{
			return;
		}
		else if (!scopeChangeValidation) // Current line outside of scope, skip
		{
			continue;
		}
		else // Current line in correct scope
		{
			_passedScopeChanger = false;
		}

		// Ignore empty lines
		if (scriptLineText.empty())
		{
			continue;
		}

		// Cannot start a new statement at the end of the script
		if (lineIndex == scriptFile->getLineCount() - 1 &&
			(scriptLineText.substr(0, _loopKeyword.size()) == _loopKeyword || scriptLineText.substr(0, _ifKeyword.size()) == _ifKeyword ||
			scriptLineText.substr(0, _elifKeyword.size()) == _elifKeyword || scriptLineText.substr(0, _elseKeyword.size()) == _elseKeyword))
		{
			_throwScriptError("no statement allowed as the last line!");
			return;
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

			// Check if script is of the same type
			if 
				(
					(scriptType == ScriptType::INIT &&
					(std::find(_updateScriptIDs.begin(), _updateScriptIDs.end(), scriptToExecute) != _updateScriptIDs.end() ||
					std::find(_destroyScriptIDs.begin(), _destroyScriptIDs.end(), scriptToExecute) != _destroyScriptIDs.end()))
					||
					(scriptType == ScriptType::UPDATE &&
					(std::find(_initScriptIDs.begin(), _initScriptIDs.end(), scriptToExecute) != _initScriptIDs.end() ||
					std::find(_destroyScriptIDs.begin(), _destroyScriptIDs.end(), scriptToExecute) != _destroyScriptIDs.end()))
					||
					(scriptType == ScriptType::DESTROY &&
					(std::find(_initScriptIDs.begin(), _initScriptIDs.end(), scriptToExecute) != _initScriptIDs.end() ||
					std::find(_updateScriptIDs.begin(), _updateScriptIDs.end(), scriptToExecute) != _updateScriptIDs.end()))
				)
			{
				_throwScriptError("script \"" + scriptToExecute + "\" is not of the same type!");
				return;
			}

			// Check if script exists
			auto& scriptList = (scriptType == ScriptType::INIT) ? _initScriptIDs :
				(scriptType == ScriptType::UPDATE) ? _updateScriptIDs : _destroyScriptIDs;
			if (std::find(scriptList.begin(), scriptList.end(), scriptToExecute) != scriptList.end())
			{
				_executeScript(scriptToExecute, scriptType);
			}
			else
			{
				_throwScriptError("script \"" + scriptToExecute + "\" does not exist!");
				return;
			}
		}
		else if (scriptLineText.substr(0, _loopKeyword.size()) == _loopKeyword) // Loop statement
		{
			// Check if "loop" statement ends with colon
			if (scriptLineText == (_loopKeyword + ":"))
			{
				loopScopeDepths.push_back(scopeDepth); // Save loop's scope depth
				loopLineIndices.push_back(lineIndex); // Save loop's line index
				scopeDepth++; // New depth layer
				_scopeHasChanged = true;
			}
			else
			{
				_throwScriptError("loop statement must end with colon!");
				return;
			}
		}
		else if (scriptLineText.substr(0, _ifKeyword.size() + 1) == _ifKeyword + " ") // If statement
		{
			// Check if "if" statement ends with colon
			if (scriptLineText.back() == ':')
			{
				// Extract condition string
				string conditionString = scriptLineText.substr((_ifKeyword.size() + 1), scriptLineText.size() - (_ifKeyword.size() + 2));

				// Check the condition of the if statement
				if (_checkConditionString(conditionString))
				{
					_scopeHasChanged = true;
					conditionStatements.push_back(ScriptConditionStatement(scopeDepth, true));
					scopeDepth++;
				}
				else
				{
					_passedScopeChanger = true;
					conditionStatements.push_back(ScriptConditionStatement(scopeDepth, false));
				}
			}
			else
			{
				_throwScriptError("if statement must end with colon!");
				return;
			}
		}
		else if (scriptLineText.substr(0, _elifKeyword.size() + 1) == _elifKeyword + " ") // Else if statement
		{
			// Check if "elif" statement ends with colon
			if (scriptLineText.back() == ':')
			{
				// Check if in sequence with if statement
				if (_getLastConditionStatement(conditionStatements, scopeDepth) != nullptr &&
					(_getLastConditionStatement(conditionStatements, scopeDepth)->type == ScriptConditionType::IF ||
					_getLastConditionStatement(conditionStatements, scopeDepth)->type == ScriptConditionType::ELIF))
				{

					// Extract condition string
					string conditionString = scriptLineText.substr((_elifKeyword.size() + 1), scriptLineText.size() - (_elifKeyword.size() + 2));

					// Set to elif statement
					_getLastConditionStatement(conditionStatements, scopeDepth)->type = ScriptConditionType::ELIF;

					// Check the condition of the elif statements
					if (!_getLastConditionStatement(conditionStatements, scopeDepth)->conditionResult && _checkConditionString(conditionString))
					{
						_scopeHasChanged = true;
						_getLastConditionStatement(conditionStatements, scopeDepth)->conditionResult = true;
						scopeDepth++;
					}
					else
					{
						_passedScopeChanger = true;
					}

				}
				else
				{
					_throwScriptError("elif statement can only come after if or elif statement!");
					return;
				}
			}
			else
			{
				_throwScriptError("elif statement must end with colon!");
				return;
			}
		}
		else if (scriptLineText.substr(0, _elseKeyword.size()) == _elseKeyword) // Else statement
		{
			// Check if "else" statement ends with colon
			if (scriptLineText.back() == ':')
			{
				// Check if in sequence with if or elif statement
				if (_getLastConditionStatement(conditionStatements, scopeDepth) != nullptr &&
					(_getLastConditionStatement(conditionStatements, scopeDepth)->type == ScriptConditionType::IF ||
						_getLastConditionStatement(conditionStatements, scopeDepth)->type == ScriptConditionType::ELIF))
				{

					// Check if the statement does not have a condition
					if (scriptLineText.size() == (_elseKeyword.size() + 1))
					{
						// Set to else statement
						_getLastConditionStatement(conditionStatements, scopeDepth)->type = ScriptConditionType::ELSE;

						// Check if all previous conditions failed
						if (!_getLastConditionStatement(conditionStatements, scopeDepth)->conditionResult)
						{
							scopeDepth++;
							_scopeHasChanged = true;
						}
						else
						{
							_passedScopeChanger = true;
						}
					}
					else
					{
						_throwScriptError("else statement cannot have a condition!");
						return;
					}

				}
				else
				{
					_throwScriptError("else statement can only come after if or elif statement!");
					return;
				}
			}
			else
			{
				_throwScriptError("else statement must end with colon!");
				return;
			}
		}
		else if // Create local variable
			(
				scriptLineText.substr(0, _constKeyword.size()   + 1) == _constKeyword   + " " ||
				scriptLineText.substr(0, _listKeyword.size()    + 1) == _listKeyword    + " " ||
				scriptLineText.substr(0, _vec3Keyword.size()    + 1) == _vec3Keyword    + " " ||
				scriptLineText.substr(0, _stringKeyword.size()  + 1) == _stringKeyword  + " " ||
				scriptLineText.substr(0, _decimalKeyword.size() + 1) == _decimalKeyword + " " ||
				scriptLineText.substr(0, _integerKeyword.size() + 1) == _integerKeyword + " " ||
				scriptLineText.substr(0, _booleanKeyword.size() + 1) == _booleanKeyword + " "
			)
		{
			_processVariableCreation(scriptLineText, ScriptVariableScope::LOCAL);
		}
		else if (scriptLineText.substr(0, _globalKeyword.size() + 1) == _globalKeyword + " ") // Create global variable
		{
			_processVariableCreation(scriptLineText, ScriptVariableScope::GLOBAL);
		}
		else if (scriptLineText.substr(0, _editKeyword.size() + 1) == _editKeyword + " ") // Edit existing variable
		{
			_processVariableAlteration(scriptLineText);
		}
		else if //Variable arithmetic
			(
				scriptLineText.substr(0, _additionKeyword.size() + 1) == _additionKeyword + " "				||
				scriptLineText.substr(0, _subtractionKeyword.size() + 1) == _subtractionKeyword + " "		||
				scriptLineText.substr(0, _multiplicationKeyword.size() + 1) == _multiplicationKeyword + " " ||
				scriptLineText.substr(0, _divisionKeyword.size() + 1) == _divisionKeyword + " "				||
				scriptLineText.substr(0, _negationKeyword.size() + 1) == _negationKeyword + " "
			)
		{
			_processVariableArithmetic(scriptLineText);
		}
		else if (scriptLineText.substr(0, _castingKeyword.size() + 1) == _castingKeyword + " ") // Variable type casting
		{
			_processVariableTypecast(scriptLineText);
		}
		else if (scriptLineText.substr(0, _pushingKeyword.size() + 1) == _pushingKeyword + " ") // Adding to list
		{
			_processListPush(scriptLineText);
		}
		else if (scriptLineText.substr(0, _pullingKeyword.size() + 1) == _pullingKeyword + " ") // Removing from list
		{
			_processListPull(scriptLineText);
		}
		else if (scriptLineText == _breakKeyword) // Breaking out of loop
		{
			scopeDepth = loopScopeDepths.back();
			loopLineIndices.pop_back();
			loopScopeDepths.pop_back();
			_passedScopeChanger = true;
		}
		else if (scriptLineText == _passKeyword) // Passing current script line
		{
			// <--- Purposely left blank
		}
		else // Invalid keyword
		{
			_throwScriptError("invalid statement!");
			return;
		}

		// Check if any engine warnings were thrown
		_checkEngineWarnings();

		// Skip the following lines of code if the last run caused an error
		if (_hasThrownError)
		{
			return;
		}
		
		// Go back to current loops beginning
		if (endOfLoop)
		{
			lineIndex = loopLineIndices.back();
			scopeDepth = loopScopeDepths.back() + 1;
			totalLoops++;
		}
	}

	// End of current script file's execution
	_currentScriptIDsStack.pop_back();
	_currentLineIndexStack.pop_back();
	_localVariablesStack.pop_back();
	_executionDepth--;
}