#include "script_interpreter.hpp"
#include "logger.hpp"

void ScriptInterpreter::executeInitializeScripts()
{
	if(!_initEntryId.empty())
	{
		_isExecutingInitialization = true;

		_executeScript(_initEntryId, ScriptType::INITIALIZE);

		_isExecutingInitialization = false;
	}
}

void ScriptInterpreter::executeUpdateScripts(bool isDebugging)
{
	if(!_updateEntryId.empty())
	{
		_isExecutingUpdate = true;
		_isDebugging = isDebugging;

		_debuggingTimes.clear();

		_executeScript(_updateEntryId, ScriptType::UPDATE);

		if(_isDebugging)
		{
			float totalTime = 0.0f;

			for(const auto & [scriptId, time] : _debuggingTimes)
			{
				totalTime += time;
			}

			Logger::throwInfo("Debug results:");

			for(const auto & [scriptId, time] : _debuggingTimes)
			{
				const auto percentage = ((time / totalTime) * 100.0f);
				const auto percentageString = to_string(percentage);
				const auto fixedPercentageString = percentageString.substr(0, (percentageString.size() - 1));

				Logger::throwInfo("Script \"" + scriptId + "\" ---> " + fixedPercentageString + "%");
			}
		}

		_isExecutingUpdate = false;
	}
}

void ScriptInterpreter::executeTerminateScripts()
{
	if(!_terminateEntryId.empty())
	{
		_isExecutingTerminate = true;

		_executeScript(_terminateEntryId, ScriptType::TERMINATE);

		_isExecutingTerminate = false;
	}
}

void ScriptInterpreter::_executeScript(const string & scriptId, ScriptType scriptType)
{
	if(_isDebugging)
	{
		if(_debuggingTimes.find(scriptId) == _debuggingTimes.end())
		{
			_debuggingTimes.insert({scriptId, 0.0f});
		}

		_fe3d->clock_start("@@scriptDebug");
	}

	vector<ScriptConditionStatement> conditionStatements = {};
	vector<int> loopScopeDepths = {};
	vector<int> loopLineIndices = {};
	vector<int> loopIterationCounts = {};

	int targetScopeDepth = 0;

	_executionDepth++;

	_currentScriptIdsStack.push_back(scriptId);
	_currentLineIndexStack.push_back(0);

	_localVariables[_executionDepth] = {};

	if(_hasThrownError || _mustStopApplication)
	{
		return;
	}

	const auto scriptFile = _script->getScriptFile(scriptId);

	for(int lineIndex = 0; lineIndex < scriptFile->getLineCount(); lineIndex++)
	{
		_currentLineIndexStack.back() = lineIndex;

		const auto lastLoggerMessageCount = Logger::getMessageCount();

		auto scriptLine = scriptFile->getLine(lineIndex);

		if(lineIndex == 0 || lineIndex == 1)
		{
			continue;
		}

		if(scriptLine.substr(0, 3) == "///")
		{
			continue;
		}

		const auto countedSpaces = _countLeadingSpaces(scriptLine);

		if(_hasThrownError)
		{
			return;
		}

		if((countedSpaces % SPACES_PER_INDENT) == 0)
		{
			scriptLine.erase(0, countedSpaces);
		}
		else
		{
			_throwRuntimeError("invalid indentation");

			return;
		}

		const auto currentScopeDepth = (countedSpaces / SPACES_PER_INDENT);

		bool isEndOfLoop = false;

		if(!loopLineIndices.empty())
		{
			if(currentScopeDepth <= loopScopeDepths.back())
			{
				lineIndex = loopLineIndices.back();
				targetScopeDepth = (loopScopeDepths.back() + 1);

				loopIterationCounts.back()++;

				continue;
			}

			if(lineIndex == (scriptFile->getLineCount() - 1))
			{
				isEndOfLoop = true;
			}
		}

		const auto isScopeChangeValid = _validateScopeDepth(currentScopeDepth, targetScopeDepth);

		_hasPassedLoopStatement = false;
		_hasPassedIfStatement = false;
		_hasPassedElifStatement = false;
		_hasPassedElseStatement = false;

		if(_hasThrownError)
		{
			return;
		}

		if(!isScopeChangeValid)
		{
			if(isEndOfLoop)
			{
				lineIndex = loopLineIndices.back();
				targetScopeDepth = (loopScopeDepths.back() + 1);

				loopIterationCounts.back()++;
			}

			continue;
		}

		if(scriptLine.empty())
		{
			continue;
		}

		if(scriptLine == PASS_KEYWORD)
		{
			// Purposely left blank
		}
		else if(scriptLine == EXIT_KEYWORD)
		{
			break;
		}
		else if(scriptLine == CRASH_KEYWORD)
		{
			_throwRuntimeError("");
			break;
		}
		else if(scriptLine.substr(0, (EXECUTE_KEYWORD.size() + 1)) == (EXECUTE_KEYWORD + " "))
		{
			const auto scriptToExecuteId = scriptLine.substr(EXECUTE_KEYWORD.size() + 1);

			if
				(
				((scriptType == ScriptType::INITIALIZE) &&
				((find(_updateScriptIds.begin(), _updateScriptIds.end(), scriptToExecuteId) != _updateScriptIds.end()) ||
				(find(_terminateScriptIds.begin(), _terminateScriptIds.end(), scriptToExecuteId) != _terminateScriptIds.end())))
				||
				((scriptType == ScriptType::UPDATE) &&
				((find(_initializeScriptIds.begin(), _initializeScriptIds.end(), scriptToExecuteId) != _initializeScriptIds.end()) ||
				(find(_terminateScriptIds.begin(), _terminateScriptIds.end(), scriptToExecuteId) != _terminateScriptIds.end())))
				||
				((scriptType == ScriptType::TERMINATE) &&
				((find(_initializeScriptIds.begin(), _initializeScriptIds.end(), scriptToExecuteId) != _initializeScriptIds.end()) ||
				(find(_updateScriptIds.begin(), _updateScriptIds.end(), scriptToExecuteId) != _updateScriptIds.end())))
				)
			{
				_throwRuntimeError("script is not of the same type");

				return;
			}

			auto & scriptList = ((scriptType == ScriptType::INITIALIZE) ? _initializeScriptIds : (scriptType == ScriptType::UPDATE) ? _updateScriptIds : _terminateScriptIds);

			if(find(scriptList.begin(), scriptList.end(), scriptToExecuteId) != scriptList.end())
			{
				if(_isDebugging)
				{
					_fe3d->clock_stop("@@scriptDebug");

					_debuggingTimes[scriptId] += _fe3d->clock_getDeltaTime("@@scriptDebug");
				}

				_executeScript(scriptToExecuteId, scriptType);

				if(_isDebugging)
				{
					_fe3d->clock_start("@@scriptDebug");
				}
			}
			else
			{
				_throwRuntimeError("script does not exist");

				return;
			}
		}
		else if(scriptLine.substr(0, (DEFINE_KEYWORD.size() + 1)) == (DEFINE_KEYWORD + " "))
		{
			_processVariableDefinition(scriptLine);
		}
		else if(scriptLine.substr(0, (ALTER_KEYWORD.size() + 1)) == (ALTER_KEYWORD + " "))
		{
			_processVariableAlteration(scriptLine);
		}
		else if(scriptLine.substr(0, (CAST_KEYWORD.size() + 1)) == (CAST_KEYWORD + " "))
		{
			_processVariableCasting(scriptLine);
		}
		else if(scriptLine.substr(0, (PUSH_KEYWORD.size() + 1)) == (PUSH_KEYWORD + " "))
		{
			_processListPush(scriptLine);
		}
		else if(scriptLine.substr(0, (PULL_KEYWORD.size() + 1)) == (PULL_KEYWORD + " "))
		{
			_processListPull(scriptLine);
		}
		else if
			(
			scriptLine.substr(0, (ADD_KEYWORD.size() + 1)) == (ADD_KEYWORD + " ") ||
			scriptLine.substr(0, (SUBTRACT_KEYWORD.size() + 1)) == (SUBTRACT_KEYWORD + " ") ||
			scriptLine.substr(0, (MULTIPLY_KEYWORD.size() + 1)) == (MULTIPLY_KEYWORD + " ") ||
			scriptLine.substr(0, (DIVIDE_KEYWORD.size() + 1)) == (DIVIDE_KEYWORD + " ") ||
			scriptLine.substr(0, (MODULO_KEYWORD.size() + 1)) == (MODULO_KEYWORD + " ") ||
			scriptLine.substr(0, (NEGATE_KEYWORD.size() + 1)) == (NEGATE_KEYWORD + " ")
			)
		{
			_processVariableArithmetic(scriptLine);
		}
		else if(scriptLine == LOOP_KEYWORD)
		{
			if(lineIndex == (scriptFile->getLineCount() - 1))
			{
				_throwRuntimeError("no " + LOOP_KEYWORD + " statement allowed as last line");

				return;
			}

			loopScopeDepths.push_back(targetScopeDepth);
			loopLineIndices.push_back(lineIndex);
			loopIterationCounts.push_back(0);

			targetScopeDepth++;

			_hasPassedLoopStatement = true;
		}
		else if(scriptLine == CONTINUE_KEYWORD)
		{
			lineIndex = loopLineIndices.back();
			targetScopeDepth = (loopScopeDepths.back() + 1);

			loopIterationCounts.back()++;

			continue;
		}
		else if(scriptLine == BREAK_KEYWORD)
		{
			targetScopeDepth = loopScopeDepths.back();

			loopScopeDepths.pop_back();
			loopLineIndices.pop_back();
			loopIterationCounts.pop_back();

			_mustIgnoreDeeperScope = true;
		}
		else if(scriptLine.substr(0, (IF_KEYWORD.size() + 1)) == (IF_KEYWORD + " "))
		{
			if(lineIndex == (scriptFile->getLineCount() - 1))
			{
				_throwRuntimeError("no " + IF_KEYWORD + " statement allowed as last line");

				return;
			}

			const auto conditionString = scriptLine.substr(IF_KEYWORD.size() + 1);

			if(_checkConditionString(conditionString))
			{
				_hasPassedIfStatement = true;

				conditionStatements.push_back(ScriptConditionStatement(targetScopeDepth, true));

				targetScopeDepth++;
			}
			else
			{
				_hasPassedIfStatement = true;
				_mustIgnoreDeeperScope = true;

				conditionStatements.push_back(ScriptConditionStatement(targetScopeDepth, false));
			}
		}
		else if(scriptLine.substr(0, (ELIF_KEYWORD.size() + 1)) == (ELIF_KEYWORD + " "))
		{
			if(lineIndex == (scriptFile->getLineCount() - 1))
			{
				_throwRuntimeError("no " + ELIF_KEYWORD + " statement allowed as last line");

				return;
			}

			const auto lastIndex = _getLastConditionStatementIndex(conditionStatements, targetScopeDepth);

			if((lastIndex != -1) &&
			   ((conditionStatements[lastIndex].getType() == ScriptConditionType::IF) || (conditionStatements[lastIndex].getType() == ScriptConditionType::ELIF)))
			{
				const auto conditionString = scriptLine.substr(ELIF_KEYWORD.size() + 1);

				conditionStatements[lastIndex].setType(ScriptConditionType::ELIF);

				if(conditionStatements[lastIndex].isFalse() && _checkConditionString(conditionString))
				{
					conditionStatements[lastIndex].setTrue();

					targetScopeDepth++;

					_hasPassedElifStatement = true;
				}
				else
				{
					_hasPassedElifStatement = true;
					_mustIgnoreDeeperScope = true;
				}
			}
			else
			{
				_throwRuntimeError(ELIF_KEYWORD + " statement can only come after " + IF_KEYWORD + " or " + ELIF_KEYWORD + " statement");

				return;
			}
		}
		else if(scriptLine == ELSE_KEYWORD)
		{
			if(lineIndex == (scriptFile->getLineCount() - 1))
			{
				_throwRuntimeError("no " + ELSE_KEYWORD + " statement allowed as last line");

				return;
			}

			const auto lastIndex = _getLastConditionStatementIndex(conditionStatements, targetScopeDepth);

			if((lastIndex != -1) &&
			   ((conditionStatements[lastIndex].getType() == ScriptConditionType::IF) || (conditionStatements[lastIndex].getType() == ScriptConditionType::ELIF)))
			{
				if(scriptLine.size() == ELSE_KEYWORD.size())
				{
					conditionStatements[lastIndex].setType(ScriptConditionType::ELSE);

					if(conditionStatements[lastIndex].isFalse())
					{
						targetScopeDepth++;

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
					_throwRuntimeError(ELSE_KEYWORD + " statement cannot have condition");

					return;
				}
			}
			else
			{
				_throwRuntimeError(ELSE_KEYWORD + " statement can only come after " + IF_KEYWORD + " or " + ELIF_KEYWORD + " statement");

				return;
			}
		}
		else if(scriptLine.substr(0, 5) == "fe3d:")
		{
			_processFe3dFunctionCall(scriptLine);
		}
		else if(scriptLine.substr(0, 5) == "math:")
		{
			_processMathFunctionCall(scriptLine);
		}
		else if(scriptLine.substr(0, 5) == "misc:")
		{
			_processMiscFunctionCall(scriptLine);
		}
		else
		{
			_throwRuntimeError("invalid statement");

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
			targetScopeDepth = (loopScopeDepths.back() + 1);

			loopIterationCounts.back()++;
		}
	}

	_currentScriptIdsStack.pop_back();
	_currentLineIndexStack.pop_back();

	_localVariables.erase(_executionDepth);

	_executionDepth--;

	if(_isDebugging)
	{
		_fe3d->clock_stop("@@scriptDebug");

		_debuggingTimes[scriptId] += _fe3d->clock_getDeltaTime("@@scriptDebug");
	}
}