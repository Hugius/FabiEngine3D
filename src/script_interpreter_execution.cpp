#include "script_interpreter.hpp"
#include "logger.hpp"

void ScriptInterpreter::executeInitializeScripts()
{
	if(!_initEntryID.empty())
	{
		_isExecutingInitialization = true;

		_executeScript(_initEntryID, ScriptType::INITIALIZE);

		_isExecutingInitialization = false;
	}
}

void ScriptInterpreter::executeUpdateScripts(bool isDebugging)
{
	if(!_updateEntryID.empty())
	{
		_isExecutingUpdate = true;

		_isDebugging = isDebugging;
		_debuggingTimes.clear();

		_executeScript(_updateEntryID, ScriptType::UPDATE);

		if(_isDebugging)
		{
			float totalTime = 0.0f;
			for(const auto& [key, time] : _debuggingTimes)
			{
				totalTime += time;
			}

			Logger::throwDebug("Debugging results:");
			for(const auto& [key, time] : _debuggingTimes)
			{
				float percentage = (time / totalTime) * 100.0f;
				Logger::throwDebug("Script \"" + key + "\" ---> " + to_string(percentage) + "%");
			}
			Logger::throwDebug("");
		}

		_isExecutingUpdate = false;
	}
}

void ScriptInterpreter::executeTerminateScripts()
{
	if(!_terminateEntryID.empty())
	{
		_isExecutingTerminate = true;

		_executeScript(_terminateEntryID, ScriptType::TERMINATE);

		_isExecutingTerminate = false;
	}
}

void ScriptInterpreter::_executeScript(const string& scriptID, ScriptType scriptType)
{
	if(_isDebugging)
	{
		if(_debuggingTimes.find(scriptID) == _debuggingTimes.end())
		{
			_debuggingTimes.insert(make_pair(scriptID, 0.0f));
		}

		_fe3d->misc_startMillisecondTimer();
	}

	vector<unsigned int> loopScopeDepths;
	vector<unsigned int> loopLineIndices;
	vector<unsigned int> loopIterationCounts;
	vector<ScriptConditionStatement> conditionStatements;
	unsigned int scopeDepth = 0;

	_executionDepth++;
	_currentScriptIDsStack.push_back(scriptID);
	_currentLineIndexStack.push_back(0);
	_localVariables[_executionDepth] = {};

	if(_executionDepth >= MAX_EXECUTION_DEPTH)
	{
		_throwScriptError("maximum amount of execution layers reached, perhaps infinite recursion?");
		return;
	}

	if(_hasThrownError || _mustStopApplication)
	{
		return;
	}

	auto scriptFile = _script->getScriptFile(scriptID);

	for(unsigned int lineIndex = 0; lineIndex < scriptFile->getLineCount(); lineIndex++)
	{
		auto lastLoggerMessageCount = Logger::getMessageCount();

		_currentLineIndexStack.back() = lineIndex;

		string scriptLineText = scriptFile->getLineText(lineIndex);

		if(lineIndex == 0 || lineIndex == 1)
		{
			continue;
		}

		if(scriptLineText.substr(0, 3) == "///")
		{
			continue;
		}

		unsigned int countedSpaces = _countLeadingSpaces(scriptLineText);
		if(_hasThrownError)
		{
			return;
		}

		if((countedSpaces % SPACES_PER_INDENT) == 0)
		{
			scriptLineText.erase(0, countedSpaces);
		}
		else
		{
			_throwScriptError("invalid indentation!");
			return;
		}

		unsigned int currentLineScopeDepth = countedSpaces / SPACES_PER_INDENT;

		bool isEndOfLoop = false;
		if(!loopLineIndices.empty())
		{
			if(currentLineScopeDepth <= loopScopeDepths.back())
			{
				if(loopIterationCounts.back() >= MAX_ITERATIONS_PER_LOOP)
				{
					_throwScriptError("maximum amount of LOOP iterations reached, perhaps infinite looping?");
					return;
				}
				else
				{
					lineIndex = loopLineIndices.back();
					scopeDepth = (loopScopeDepths.back() + 1);
					loopIterationCounts.back()++;
					continue;
				}
			}
			else if(lineIndex == scriptFile->getLineCount() - 1)
			{
				if(loopIterationCounts.back() >= MAX_ITERATIONS_PER_LOOP)
				{
					_throwScriptError("maximum amount of LOOP iterations reached, perhaps infinite looping?");
					return;
				}
				else
				{
					isEndOfLoop = true;
				}
			}
		}

		bool scopeChangeValidation = _validateScopeChange(countedSpaces, scriptLineText, scopeDepth);
		_hasPassedLoopStatement = false;
		_hasPassedIfStatement = false;
		_hasPassedElifStatement = false;
		_hasPassedElseStatement = false;

		if(_hasThrownError)
		{
			return;
		}

		if(!scopeChangeValidation)
		{
			continue;
		}

		if(scriptLineText.empty())
		{
			continue;
		}

		if(lineIndex == (scriptFile->getLineCount() - 1))
		{
			if(scriptLineText.substr(0, LOOP_KEYWORD.size()) == LOOP_KEYWORD ||
			   scriptLineText.substr(0, IF_KEYWORD.size()) == IF_KEYWORD ||
			   scriptLineText.substr(0, ELIF_KEYWORD.size()) == ELIF_KEYWORD ||
			   scriptLineText.substr(0, ELSE_KEYWORD.size()) == ELSE_KEYWORD)
			{
				_throwScriptError("no LOOP/IF/ELIF/ELSE statement allowed as last line!");
				return;
			}
		}

		if(scriptLineText.substr(0, META_KEYWORD.size()) == META_KEYWORD)
		{
			_throwScriptError("META keyword is only allowed on line 1 and 2!");
			return;
		}
		else if(scriptLineText.substr(0, 5) == "fe3d:")
		{
			_processFe3dFunctionCall(scriptLineText);
		}
		else if(scriptLineText.substr(0, 5) == "math:")
		{
			_processMathFunctionCall(scriptLineText);
		}
		else if(scriptLineText.substr(0, 5) == "misc:")
		{
			_processMiscFunctionCall(scriptLineText);
		}
		else if(scriptLineText.substr(0, EXECUTE_KEYWORD.size() + 1) == EXECUTE_KEYWORD + " ")
		{
			string scriptToExecute = scriptLineText.substr(EXECUTE_KEYWORD.size() + 1);

			if
				(
				(scriptType == ScriptType::INITIALIZE &&
				(find(_updateScriptIDs.begin(), _updateScriptIDs.end(), scriptToExecute) != _updateScriptIDs.end() ||
				find(_terminateScriptIDs.begin(), _terminateScriptIDs.end(), scriptToExecute) != _terminateScriptIDs.end()))
				||
				(scriptType == ScriptType::UPDATE &&
				(find(_initializeScriptIDs.begin(), _initializeScriptIDs.end(), scriptToExecute) != _initializeScriptIDs.end() ||
				find(_terminateScriptIDs.begin(), _terminateScriptIDs.end(), scriptToExecute) != _terminateScriptIDs.end()))
				||
				(scriptType == ScriptType::TERMINATE &&
				(find(_initializeScriptIDs.begin(), _initializeScriptIDs.end(), scriptToExecute) != _initializeScriptIDs.end() ||
				find(_updateScriptIDs.begin(), _updateScriptIDs.end(), scriptToExecute) != _updateScriptIDs.end()))
				)
			{
				_throwScriptError("script \"" + scriptToExecute + "\" is not of the same type!");
				return;
			}

			auto& scriptList =
				(scriptType == ScriptType::INITIALIZE) ? _initializeScriptIDs :
				(scriptType == ScriptType::UPDATE) ? _updateScriptIDs :
				_terminateScriptIDs;

			if(find(scriptList.begin(), scriptList.end(), scriptToExecute) != scriptList.end())
			{
				if(_isDebugging)
				{
					_debuggingTimes[scriptID] += _fe3d->misc_stopMillisecondTimer();
				}

				_executeScript(scriptToExecute, scriptType);

				if(_isDebugging)
				{
					_fe3d->misc_startMillisecondTimer();
				}
			}
			else
			{
				_throwScriptError("script \"" + scriptToExecute + "\" not existing!");
				return;
			}
		}
		else if(scriptLineText.substr(0, LOOP_KEYWORD.size()) == LOOP_KEYWORD)
		{
			if(scriptLineText == (LOOP_KEYWORD + ":"))
			{
				loopScopeDepths.push_back(scopeDepth);
				loopLineIndices.push_back(lineIndex);
				loopIterationCounts.push_back(0);
				scopeDepth++;
				_hasPassedLoopStatement = true;
			}
			else
			{
				_throwScriptError("LOOP statement must end with ':'!");
				return;
			}
		}
		else if(scriptLineText.substr(0, IF_KEYWORD.size() + 1) == IF_KEYWORD + " ")
		{
			if(scriptLineText.back() == ':')
			{
				string conditionString = scriptLineText.substr((IF_KEYWORD.size() + 1), scriptLineText.size() - (IF_KEYWORD.size() + 2));

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
				_throwScriptError("IF statement must end with ':'!");
				return;
			}
		}
		else if(scriptLineText.substr(0, ELIF_KEYWORD.size() + 1) == ELIF_KEYWORD + " ")
		{
			if(scriptLineText.back() == ':')
			{
				if(_getLastConditionStatement(conditionStatements, scopeDepth) != nullptr &&
				   (_getLastConditionStatement(conditionStatements, scopeDepth)->getType() == ScriptConditionType::IF ||
				   _getLastConditionStatement(conditionStatements, scopeDepth)->getType() == ScriptConditionType::ELIF))
				{
					string conditionString = scriptLineText.substr((ELIF_KEYWORD.size() + 1), scriptLineText.size() - (ELIF_KEYWORD.size() + 2));

					_getLastConditionStatement(conditionStatements, scopeDepth)->setType(ScriptConditionType::ELIF);

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
					_throwScriptError("ELIF statement can only come after IF or ELIF statement!");
					return;
				}
			}
			else
			{
				_throwScriptError("ELIF statement must end with ':'!");
				return;
			}
		}
		else if(scriptLineText.substr(0, ELSE_KEYWORD.size()) == ELSE_KEYWORD)
		{
			if(scriptLineText.back() == ':')
			{
				if(_getLastConditionStatement(conditionStatements, scopeDepth) != nullptr &&
				   (_getLastConditionStatement(conditionStatements, scopeDepth)->getType() == ScriptConditionType::IF ||
				   _getLastConditionStatement(conditionStatements, scopeDepth)->getType() == ScriptConditionType::ELIF))
				{

					if(scriptLineText.size() == (ELSE_KEYWORD.size() + 1))
					{
						_getLastConditionStatement(conditionStatements, scopeDepth)->setType(ScriptConditionType::ELSE);

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
						_throwScriptError("ELSE statement cannot have condition!");
						return;
					}
				}
				else
				{
					_throwScriptError("ELSE statement can only come after IF or ELIF statement!");
					return;
				}
			}
			else
			{
				_throwScriptError("ELSE statement must end with ':'!");
				return;
			}
		}
		else if
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
		else if
			(
			scriptLineText.substr(0, ADDITION_KEYWORD.size() + 1) == ADDITION_KEYWORD + " " ||
			scriptLineText.substr(0, SUBTRACTION_KEYWORD.size() + 1) == SUBTRACTION_KEYWORD + " " ||
			scriptLineText.substr(0, MULTIPLICATION_KEYWORD.size() + 1) == MULTIPLICATION_KEYWORD + " " ||
			scriptLineText.substr(0, DIVISION_KEYWORD.size() + 1) == DIVISION_KEYWORD + " " ||
			scriptLineText.substr(0, MODULO_KEYWORD.size() + 1) == MODULO_KEYWORD + " " ||
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
			if(loopIterationCounts.back() >= MAX_ITERATIONS_PER_LOOP)
			{
				_throwScriptError("maximum amount of LOOP iterations reached, perhaps infinite looping?");
				return;
			}
			else
			{
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
		}
		else
		{
			_throwScriptError("invalid statement!");
			return;
		}

		_checkEngineWarnings(lastLoggerMessageCount);

		if(_hasThrownError || _mustStopApplication)
		{
			return;
		}

		if(isEndOfLoop)
		{
			lineIndex = loopLineIndices.back();
			scopeDepth = (loopScopeDepths.back() + 1);
			loopIterationCounts.back()++;
		}
	}

	_currentScriptIDsStack.pop_back();
	_currentLineIndexStack.pop_back();
	_localVariables.erase(_executionDepth);
	_executionDepth--;

	if(_isDebugging)
	{
		_debuggingTimes[scriptID] += _fe3d->misc_stopMillisecondTimer();
	}
}