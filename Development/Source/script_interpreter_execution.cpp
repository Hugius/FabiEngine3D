#include "script_interpreter.hpp"

void ScriptInterpreter::_executeScript(const string& scriptID, ScriptType scriptType)
{
	// Start debug timing
	if (_isDebugging)
	{
		// First time
		if (_debuggingTimes.find(scriptID) == _debuggingTimes.end())
		{
			_debuggingTimes.insert(make_pair(scriptID, 0.0f));
		}

		// Start timer
		_fe3d.misc_startMillisecondTimer();
	}

	// Temporary local values for this script run
	vector<unsigned int> loopLineIndices;
	vector<unsigned int> loopScopeDepths;
	vector<ScriptConditionStatement> conditionStatements;
	unsigned int scopeDepth = 0;
	unsigned int totalLoops = 0;

	// Prepare current script file's execution
	_executionDepth++;
	_currentScriptIDsStack.push_back(scriptID);
	_currentLineIndexStack.push_back(0);
	_localVariables[_executionDepth] = {};

	// Detect infinite recursion
	if (_executionDepth >= MAX_EXECUTION_DEPTH)
	{
		_throwScriptError("too many script execution layers, perhaps infinite recursion?");
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
		_lastLoggerMessageCount = _fe3d.logger_getMessageCount();

		// Save index of line of script currently being executed
		_currentLineIndexStack.back() = lineIndex;

		// Retrieve line text
		string scriptLineText = scriptFile->getLineText(lineIndex);
		
		// Ignore METAs
		if (lineIndex == 0 || lineIndex == 1)
		{
			continue;
		}

		// Ignore comments
		if (scriptLineText.substr(0, 3) == "///")
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
		if ((countedSpaces % SPACES_PER_INDENT) == 0)
		{
			scriptLineText.erase(0, countedSpaces); // Remove front spaces
		}
		else
		{
			_throwScriptError("invalid indentation!");
			return;
		}

		// Calculate current scope depth
		unsigned int currentLineScopeDepth = countedSpaces / SPACES_PER_INDENT;
		
		// Detect end of loop
		bool endOfLoop = false;
		if (!loopLineIndices.empty())
		{
			if (currentLineScopeDepth <= loopScopeDepths.back()) // End of current loop scope
			{
				if (totalLoops >= MAX_LOOPS_PER_FRAME) // Infinite loop
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
				if (totalLoops >= MAX_LOOPS_PER_FRAME) // Infinite loop
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
			(scriptLineText.substr(0, LOOP_KEYWORD.size()) == LOOP_KEYWORD || scriptLineText.substr(0, IF_KEYWORD.size()) == IF_KEYWORD ||
			scriptLineText.substr(0, ELIF_KEYWORD.size()) == ELIF_KEYWORD || scriptLineText.substr(0, ELSE_KEYWORD.size()) == ELSE_KEYWORD))
		{
			_throwScriptError("no statement allowed as the last line!");
			return;
		}

		// Determine keyword type
		if (scriptLineText.substr(0, META_KEYWORD.size()) == META_KEYWORD)
		{
			_throwScriptError("META keyword is only allowed on line 1 and 2!");
		}
		else if (scriptLineText.substr(0, 5) == "fe3d:")
		{
			_processEngineFunctionCall(scriptLineText);
		}
		else if (scriptLineText.substr(0, 5) == "math:")
		{
			_processMathematicalFunctionCall(scriptLineText);
		}
		else if (scriptLineText.substr(0, 5) == "misc:")
		{
			_processMiscellaneousFunctionCall(scriptLineText);
		}
		else if (scriptLineText.substr(0, EXECUTE_KEYWORD.size() + 1) == EXECUTE_KEYWORD + " ")
		{
			// Determine scriptname to execute
			string scriptToExecute = scriptLineText.substr(EXECUTE_KEYWORD.size() + 1);

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
				// Pause timer
				if (_isDebugging)
				{
					_debuggingTimes[scriptID] += _fe3d.misc_stopMillisecondTimer();
				}

				// Execute script
				_executeScript(scriptToExecute, scriptType);

				// Resume timer
				if (_isDebugging)
				{
					_fe3d.misc_startMillisecondTimer();
				}
			}
			else
			{
				_throwScriptError("script does not exist!");
				return;
			}
		}
		else if (scriptLineText.substr(0, LOOP_KEYWORD.size()) == LOOP_KEYWORD)
		{
			// Check if "loop" statement ends with colon
			if (scriptLineText == (LOOP_KEYWORD + ":"))
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
		else if (scriptLineText.substr(0, IF_KEYWORD.size() + 1) == IF_KEYWORD + " ")
		{
			// Check if "if" statement ends with colon
			if (scriptLineText.back() == ':')
			{
				// Extract condition string
				string conditionString = scriptLineText.substr((IF_KEYWORD.size() + 1), scriptLineText.size() - (IF_KEYWORD.size() + 2));

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
		else if (scriptLineText.substr(0, ELIF_KEYWORD.size() + 1) == ELIF_KEYWORD + " ")
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
					string conditionString = scriptLineText.substr((ELIF_KEYWORD.size() + 1), scriptLineText.size() - (ELIF_KEYWORD.size() + 2));

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
		else if (scriptLineText.substr(0, ELSE_KEYWORD.size()) == ELSE_KEYWORD)
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
					if (scriptLineText.size() == (ELSE_KEYWORD.size() + 1))
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
				scriptLineText.substr(0, CONST_KEYWORD.size()   + 1) == CONST_KEYWORD   + " " ||
				scriptLineText.substr(0, LIST_KEYWORD.size()    + 1) == LIST_KEYWORD    + " " ||
				scriptLineText.substr(0, VEC3_KEYWORD.size()    + 1) == VEC3_KEYWORD    + " " ||
				scriptLineText.substr(0, STRING_KEYWORD.size()  + 1) == STRING_KEYWORD  + " " ||
				scriptLineText.substr(0, DECIMAL_KEYWORD.size() + 1) == DECIMAL_KEYWORD + " " ||
				scriptLineText.substr(0, INTEGER_KEYWORD.size() + 1) == INTEGER_KEYWORD + " " ||
				scriptLineText.substr(0, BOOLEAN_KEYWORD.size() + 1) == BOOLEAN_KEYWORD + " "
			)
		{
			_processVariableCreation(scriptLineText, ScriptVariableScope::LOCAL);
		}
		else if (scriptLineText.substr(0, GLOBAL_KEYWORD.size() + 1) == GLOBAL_KEYWORD + " ")
		{
			_processVariableCreation(scriptLineText, ScriptVariableScope::GLOBAL);
		}
		else if (scriptLineText.substr(0, EDIT_KEYWORD.size() + 1) == EDIT_KEYWORD + " ")
		{
			_processVariableAlteration(scriptLineText);
		}
		else if // Variable arithmetic
			(
				scriptLineText.substr(0, ADDITION_KEYWORD.size() + 1) == ADDITION_KEYWORD + " "				||
				scriptLineText.substr(0, SUBTRACTION_KEYWORD.size() + 1) == SUBTRACTION_KEYWORD + " "		||
				scriptLineText.substr(0, MULTIPLICATION_KEYWORD.size() + 1) == MULTIPLICATION_KEYWORD + " " ||
				scriptLineText.substr(0, DIVISION_KEYWORD.size() + 1) == DIVISION_KEYWORD + " "				||
				scriptLineText.substr(0, NEGATION_KEYWORD.size() + 1) == NEGATION_KEYWORD + " "
			)
		{
			_processVariableArithmetic(scriptLineText);
		}
		else if (scriptLineText.substr(0, CASTING_KEYWORD.size() + 1) == CASTING_KEYWORD + " ")
		{
			_processVariableTypecast(scriptLineText);
		}
		else if (scriptLineText.substr(0, PUSHING_KEYWORD.size() + 1) == PUSHING_KEYWORD + " ")
		{
			_processListPush(scriptLineText);
		}
		else if (scriptLineText.substr(0, PULLING_KEYWORD.size() + 1) == PULLING_KEYWORD + " ")
		{
			_processListPull(scriptLineText);
		}
		else if (scriptLineText == BREAK_KEYWORD)
		{
			scopeDepth = loopScopeDepths.back();
			loopLineIndices.pop_back();
			loopScopeDepths.pop_back();
			_passedScopeChanger = true;
		}
		else if (scriptLineText == PASS_KEYWORD)
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

	// Finish current script file's execution
	_currentScriptIDsStack.pop_back();
	_currentLineIndexStack.pop_back();
	_localVariables.erase(_executionDepth);
	_executionDepth--;

	// Stop timer
	if (_isDebugging)
	{
		_debuggingTimes[scriptID] += _fe3d.misc_stopMillisecondTimer();
	}
}