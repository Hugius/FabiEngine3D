#include "script_interpreter.hpp"
#include "logger.hpp"

void ScriptInterpreter::_executeScript(const string& scriptID, ScriptType scriptType)
{
	// Start debug timing
	if(_isDebugging)
	{
		// First time
		if(_debuggingTimes.find(scriptID) == _debuggingTimes.end())
		{
			_debuggingTimes.insert(make_pair(scriptID, 0.0f));
		}

		// Start timer
		_fe3d.misc_startMillisecondTimer();
	}

	// Temporary local values for this script run
	vector<unsigned int> loopScopeDepths;
	vector<unsigned int> loopLineIndices;
	vector<unsigned int> loopIterationCounts;
	vector<ScriptConditionStatement> conditionStatements;
	unsigned int scopeDepth = 0;

	// Prepare current script file's execution
	_executionDepth++;
	_currentScriptIDsStack.push_back(scriptID);
	_currentLineIndexStack.push_back(0);
	_localVariables[_executionDepth] = {};

	// Detect infinite recursion
	if(_executionDepth >= MAX_EXECUTION_DEPTH)
	{
		_throwScriptError("too many script execution layers, perhaps infinite recursion?");
		return;
	}

	// Skip the following lines of code if necessary
	if(_hasThrownError || _mustStopApplication)
	{
		return;
	}

	// Retrieve script file
	auto scriptFile = _script.getScriptFile(scriptID);

	// Interpret every line from top to bottom in script
	for(unsigned int lineIndex = 0; lineIndex < scriptFile->getLineCount(); lineIndex++)
	{
		// Save current amount of logged messages
		auto lastLoggerMessageCount = Logger::getMessageCount();

		// Save index of line of script currently being executed
		_currentLineIndexStack.back() = lineIndex;

		// Retrieve line text
		string scriptLineText = scriptFile->getLineText(lineIndex);

		// Ignore METAs
		if(lineIndex == 0 || lineIndex == 1)
		{
			continue;
		}

		// Ignore comments
		if(scriptLineText.substr(0, 3) == "///")
		{
			continue;
		}

		// Count front spaces (and check if it went well)
		unsigned int countedSpaces = _countFrontSpaces(scriptLineText);
		if(_hasThrownError)
		{
			return;
		}

		// Check if indentation syntax is correct
		if((countedSpaces % SPACES_PER_INDENT) == 0)
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
		bool isEndOfLoop = false;
		if(!loopLineIndices.empty())
		{
			if(currentLineScopeDepth <= loopScopeDepths.back()) // End of current loop scope
			{
				if(loopIterationCounts.back() >= MAX_ITERATIONS_PER_LOOP) // Infinite loop
				{
					_throwScriptError("maximum amount of loop iterations reached, perhaps infinite looping?");
					return;
				}
				else // Normal loop
				{
					// Go back to current loop's beginning
					lineIndex = loopLineIndices.back();
					scopeDepth = (loopScopeDepths.back() + 1);
					loopIterationCounts.back()++;
					continue;
				}
			}
			else if(lineIndex == scriptFile->getLineCount() - 1) // End of script
			{
				if(loopIterationCounts.back() >= MAX_ITERATIONS_PER_LOOP) // Infinite loop
				{
					_throwScriptError("maximum amount of loop iterations reached, perhaps infinite looping?");
					return;
				}
				else // Normal loop
				{
					isEndOfLoop = true; // Go back to current loop's beginning after executing current scriptline
				}
			}
		}

		// Validate scope change
		bool scopeChangeValidation = _validateScopeChange(countedSpaces, scriptLineText, scopeDepth);
		_hasPassedLoopStatement = false;
		_hasPassedIfStatement = false;
		_hasPassedElifStatement = false;
		_hasPassedElseStatement = false;

		// Check if an error was thrown
		if(_hasThrownError)
		{
			return;
		}

		// Check if current line execution must be skipped
		if(!scopeChangeValidation)
		{
			continue;
		}

		// Ignore empty lines
		if(scriptLineText.empty())
		{
			continue;
		}

		// Check if current line is the last
		if(lineIndex == (scriptFile->getLineCount() - 1))
		{
			// Check if current line is an loop/if/elif/else statement
			if(scriptLineText.substr(0, LOOP_KEYWORD.size()) == LOOP_KEYWORD ||
			   scriptLineText.substr(0, IF_KEYWORD.size()) == IF_KEYWORD ||
			   scriptLineText.substr(0, ELIF_KEYWORD.size()) == ELIF_KEYWORD ||
			   scriptLineText.substr(0, ELSE_KEYWORD.size()) == ELSE_KEYWORD)
			{
				_throwScriptError("no LOOP/IF/ELIF/ELSE statement allowed as the last line!");
				return;
			}
		}

		// Determine keyword type
		if(scriptLineText.substr(0, META_KEYWORD.size()) == META_KEYWORD)
		{
			_throwScriptError("META keyword is only allowed on line 1 and 2!");
			return;
		}
		else if(scriptLineText.substr(0, 5) == "fe3d:")
		{
			_processEngineFunctionCall(scriptLineText);
		}
		else if(scriptLineText.substr(0, 5) == "math:")
		{
			_processMathematicalFunctionCall(scriptLineText);
		}
		else if(scriptLineText.substr(0, 5) == "misc:")
		{
			_processMiscellaneousFunctionCall(scriptLineText);
		}
		else if(scriptLineText.substr(0, EXECUTE_KEYWORD.size() + 1) == EXECUTE_KEYWORD + " ")
		{
			// Determine scriptname to execute
			string scriptToExecute = scriptLineText.substr(EXECUTE_KEYWORD.size() + 1);

			// Check if script is of the same type
			if
				(
				(scriptType == ScriptType::INIT &&
				(find(_updateScriptIDs.begin(), _updateScriptIDs.end(), scriptToExecute) != _updateScriptIDs.end() ||
				find(_destroyScriptIDs.begin(), _destroyScriptIDs.end(), scriptToExecute) != _destroyScriptIDs.end()))
				||
				(scriptType == ScriptType::UPDATE &&
				(find(_initScriptIDs.begin(), _initScriptIDs.end(), scriptToExecute) != _initScriptIDs.end() ||
				find(_destroyScriptIDs.begin(), _destroyScriptIDs.end(), scriptToExecute) != _destroyScriptIDs.end()))
				||
				(scriptType == ScriptType::DESTROY &&
				(find(_initScriptIDs.begin(), _initScriptIDs.end(), scriptToExecute) != _initScriptIDs.end() ||
				find(_updateScriptIDs.begin(), _updateScriptIDs.end(), scriptToExecute) != _updateScriptIDs.end()))
				)
			{
				_throwScriptError("script \"" + scriptToExecute + "\" is not of the same type!");
				return;
			}

			// Check if script exists
			auto& scriptList = (scriptType == ScriptType::INIT) ? _initScriptIDs :
				(scriptType == ScriptType::UPDATE) ? _updateScriptIDs : _destroyScriptIDs;
			if(find(scriptList.begin(), scriptList.end(), scriptToExecute) != scriptList.end())
			{
				// Pause timer
				if(_isDebugging)
				{
					_debuggingTimes[scriptID] += _fe3d.misc_stopMillisecondTimer();
				}

				// Execute script
				_executeScript(scriptToExecute, scriptType);

				// Resume timer
				if(_isDebugging)
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
		else if(scriptLineText.substr(0, LOOP_KEYWORD.size()) == LOOP_KEYWORD)
		{
			// Check if loop statement ends with colon
			if(scriptLineText == (LOOP_KEYWORD + ":"))
			{
				loopScopeDepths.push_back(scopeDepth); // Save loop's scope depth
				loopLineIndices.push_back(lineIndex); // Save loop's line index
				loopIterationCounts.push_back(0); // Save loop's iteration count
				scopeDepth++; // New depth layer
				_hasPassedLoopStatement = true;
			}
			else
			{
				_throwScriptError("LOOP statement must end with colon!");
				return;
			}
		}
		else if(scriptLineText.substr(0, IF_KEYWORD.size() + 1) == IF_KEYWORD + " ")
		{
			// Check if "if" statement ends with colon
			if(scriptLineText.back() == ':')
			{
				// Extract condition string
				string conditionString = scriptLineText.substr((IF_KEYWORD.size() + 1), scriptLineText.size() - (IF_KEYWORD.size() + 2));

				// Check the condition of the if statement
				if(_checkConditionString(conditionString))
				{
					_hasPassedIfStatement = true;
					conditionStatements.push_back(ScriptConditionStatement(scopeDepth, true));
					scopeDepth++;
				}
				else
				{
					_hasPassedIfStatement = true;
					_mustIgnoreDeeperScope = true;
					conditionStatements.push_back(ScriptConditionStatement(scopeDepth, false));
				}
			}
			else
			{
				_throwScriptError("IF statement must end with colon!");
				return;
			}
		}
		else if(scriptLineText.substr(0, ELIF_KEYWORD.size() + 1) == ELIF_KEYWORD + " ")
		{
			// Check if "elif" statement ends with colon
			if(scriptLineText.back() == ':')
			{
				// Check if in sequence with if statement
				if(_getLastConditionStatement(conditionStatements, scopeDepth) != nullptr &&
				   (_getLastConditionStatement(conditionStatements, scopeDepth)->getType() == ScriptConditionType::IF ||
				   _getLastConditionStatement(conditionStatements, scopeDepth)->getType() == ScriptConditionType::ELIF))
				{
					// Extract condition string
					string conditionString = scriptLineText.substr((ELIF_KEYWORD.size() + 1), scriptLineText.size() - (ELIF_KEYWORD.size() + 2));

					// Set to elif statement
					_getLastConditionStatement(conditionStatements, scopeDepth)->setType(ScriptConditionType::ELIF);

					// Check the condition of the elif statement
					if(_getLastConditionStatement(conditionStatements, scopeDepth)->isFalse() && _checkConditionString(conditionString))
					{
						_hasPassedElifStatement = true;
						_getLastConditionStatement(conditionStatements, scopeDepth)->setTrue();
						scopeDepth++;
					}
					else
					{
						_hasPassedElifStatement = true;
						_mustIgnoreDeeperScope = true;
					}

				}
				else
				{
					_throwScriptError("ELIF statement can only come after if or elif statement!");
					return;
				}
			}
			else
			{
				_throwScriptError("ELIF statement must end with colon!");
				return;
			}
		}
		else if(scriptLineText.substr(0, ELSE_KEYWORD.size()) == ELSE_KEYWORD)
		{
			// Check if "else" statement ends with colon
			if(scriptLineText.back() == ':')
			{
				// Check if in sequence with if or elif statement
				if(_getLastConditionStatement(conditionStatements, scopeDepth) != nullptr &&
				   (_getLastConditionStatement(conditionStatements, scopeDepth)->getType() == ScriptConditionType::IF ||
				   _getLastConditionStatement(conditionStatements, scopeDepth)->getType() == ScriptConditionType::ELIF))
				{

					// Check if the statement does not have a condition
					if(scriptLineText.size() == (ELSE_KEYWORD.size() + 1))
					{
						// Set to else statement
						_getLastConditionStatement(conditionStatements, scopeDepth)->setType(ScriptConditionType::ELSE);

						// Check if all previous conditions failed
						if(_getLastConditionStatement(conditionStatements, scopeDepth)->isFalse())
						{
							scopeDepth++;
							_hasPassedElseStatement = true;
						}
						else
						{
							_hasPassedElseStatement = true;
							_mustIgnoreDeeperScope = true;
						}
					}
					else
					{
						_throwScriptError("ELSE statement cannot have a condition!");
						return;
					}
				}
				else
				{
					_throwScriptError("ELSE statement can only come after if or elif statement!");
					return;
				}
			}
			else
			{
				_throwScriptError("ELSE statement must end with colon!");
				return;
			}
		}
		else if // Create local variable
			(
			scriptLineText.substr(0, CONST_KEYWORD.size() + 1) == CONST_KEYWORD + " " ||
			scriptLineText.substr(0, LIST_KEYWORD.size() + 1) == LIST_KEYWORD + " " ||
			scriptLineText.substr(0, STRING_KEYWORD.size() + 1) == STRING_KEYWORD + " " ||
			scriptLineText.substr(0, DECIMAL_KEYWORD.size() + 1) == DECIMAL_KEYWORD + " " ||
			scriptLineText.substr(0, INTEGER_KEYWORD.size() + 1) == INTEGER_KEYWORD + " " ||
			scriptLineText.substr(0, BOOLEAN_KEYWORD.size() + 1) == BOOLEAN_KEYWORD + " "
			)
		{
			_processVariableCreation(scriptLineText, ScriptVariableScope::LOCAL);
		}
		else if(scriptLineText.substr(0, GLOBAL_KEYWORD.size() + 1) == GLOBAL_KEYWORD + " ")
		{
			_processVariableCreation(scriptLineText, ScriptVariableScope::GLOBAL);
		}
		else if(scriptLineText.substr(0, EDIT_KEYWORD.size() + 1) == EDIT_KEYWORD + " ")
		{
			_processVariableAlteration(scriptLineText);
		}
		else if // Variable arithmetic
			(
			scriptLineText.substr(0, ADDITION_KEYWORD.size() + 1) == ADDITION_KEYWORD + " " ||
			scriptLineText.substr(0, SUBTRACTION_KEYWORD.size() + 1) == SUBTRACTION_KEYWORD + " " ||
			scriptLineText.substr(0, MULTIPLICATION_KEYWORD.size() + 1) == MULTIPLICATION_KEYWORD + " " ||
			scriptLineText.substr(0, DIVISION_KEYWORD.size() + 1) == DIVISION_KEYWORD + " " ||
			scriptLineText.substr(0, NEGATION_KEYWORD.size() + 1) == NEGATION_KEYWORD + " "
			)
		{
			_processVariableArithmetic(scriptLineText);
		}
		else if(scriptLineText.substr(0, CASTING_KEYWORD.size() + 1) == CASTING_KEYWORD + " ")
		{
			_processVariableTypecast(scriptLineText);
		}
		else if(scriptLineText.substr(0, PUSHING_KEYWORD.size() + 1) == PUSHING_KEYWORD + " ")
		{
			_processListPush(scriptLineText);
		}
		else if(scriptLineText.substr(0, PULLING_KEYWORD.size() + 1) == PULLING_KEYWORD + " ")
		{
			_processListPull(scriptLineText);
		}
		else if(scriptLineText == CONTINUE_KEYWORD)
		{
			if(loopIterationCounts.back() >= MAX_ITERATIONS_PER_LOOP) // Infinite loop
			{
				_throwScriptError("maximum amount of loop iterations reached, perhaps infinite looping?");
				return;
			}
			else // Normal loop
			{
				// Go back to current loop's beginning
				lineIndex = loopLineIndices.back();
				scopeDepth = (loopScopeDepths.back() + 1);
				loopIterationCounts.back()++;
				continue;
			}
		}
		else if(scriptLineText == BREAK_KEYWORD)
		{
			scopeDepth = loopScopeDepths.back();
			loopScopeDepths.pop_back();
			loopLineIndices.pop_back();
			loopIterationCounts.pop_back();
			_mustIgnoreDeeperScope = true;
		}
		else if(scriptLineText == PASS_KEYWORD)
		{
			// <--- Purposely left blank
		}
		else // Invalid keyword
		{
			_throwScriptError("invalid statement!");
			return;
		}

		// Check if any engine warnings were thrown
		_checkEngineWarnings(lastLoggerMessageCount);

		// Skip the following lines of code if necessary
		if(_hasThrownError || _mustStopApplication)
		{
			return;
		}

		// Go back to current loops beginning
		if(isEndOfLoop)
		{
			lineIndex = loopLineIndices.back();
			scopeDepth = (loopScopeDepths.back() + 1);
			loopIterationCounts.back()++;
		}
	}

	// Finish current script file's execution
	_currentScriptIDsStack.pop_back();
	_currentLineIndexStack.pop_back();
	_localVariables.erase(_executionDepth);
	_executionDepth--;

	// Stop timer
	if(_isDebugging)
	{
		_debuggingTimes[scriptID] += _fe3d.misc_stopMillisecondTimer();
	}
}