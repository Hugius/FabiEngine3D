#include "script_interpreter.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <sstream>

void ScriptInterpreter::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

bool ScriptInterpreter::hasThrownError()
{
	return _hasThrownError;
}

bool ScriptInterpreter::gameMustStop()
{
	return _mustStopApplication;
}

unsigned int ScriptInterpreter::_countFrontSpaces(const string& scriptLineText)
{
	int countedSpaces = 0;

	// For every character
	for (size_t i = 0; i < scriptLineText.size(); i++)
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

bool ScriptInterpreter::_validateScopeChange(unsigned int countedSpaces, const string& scriptLineText, unsigned int& scopeDepth)
{
	// Temporary values
	const unsigned int currentLineScopeDepth = (countedSpaces / SPACES_PER_INDENT);
	const bool isScopeDepthInvalid = (currentLineScopeDepth != (scopeDepth + static_cast<int>(_mustIgnoreDeeperScope)));

	if (_hasPassedLoopStatement && isScopeDepthInvalid) // Passed loop statement
	{
		_throwScriptError("incorrect indentation after LOOP statement!");
		return false;
	}
	else if (_hasPassedIfStatement && isScopeDepthInvalid) // Passed if statement
	{
		_throwScriptError("incorrect indentation after IF statement!");
		return false;
	}
	else if (_hasPassedElifStatement && isScopeDepthInvalid) // Passed elif statement
	{
		_throwScriptError("incorrect indentation after ELIF statement!");
		return false;
	}
	else if (_hasPassedElseStatement && isScopeDepthInvalid) // Passed else statement
	{
		_throwScriptError("incorrect indentation after ELSE statement!");
		return false;
	}
	else if (currentLineScopeDepth < scopeDepth) // End of current scope
	{
		scopeDepth = currentLineScopeDepth;
	}
	else if (currentLineScopeDepth > scopeDepth) // Outside of current scope
	{
		if (_mustIgnoreDeeperScope) // Skip current line
		{
			return false;
		}
		else // Useless indentation
		{
			_throwScriptError("useless indentation before statement!"); 
			return false;
		}
	}
	else
	{
		_mustIgnoreDeeperScope = false;
	}

	return true;
}

bool ScriptInterpreter::_validateSavesDirectory()
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("ScriptInterpreter::_validateSavesDirectory");
	}

	// Check if saves directory still exists
	auto directoryPath = Tools::getRootDirectory() + (_fe3d.application_isExported() ? "" : ("projects\\" + _currentProjectID)) + "\\saves\\";
	if (!Tools::isDirectoryExisting(directoryPath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: directory `saves\\` missing!");
		return false;
	}

	return true;
}

ScriptConditionStatement* ScriptInterpreter::_getLastConditionStatement(vector<ScriptConditionStatement>& statements, unsigned int scopeDepth)
{
	// Temporary values
	unsigned int index = static_cast<unsigned int>(statements.size());

	// Loop through conditions backwards
	while (index--)
	{
		// Check if scope depth matches
		if (statements[index].getScopeDepth() == scopeDepth)
		{
			return &statements[index];
		}
	}

	// No condition statement
	return nullptr;
}

void ScriptInterpreter::_throwScriptError(const string& message)
{
	Logger::throwWarning("ERROR @ script \"" + _currentScriptIDsStack.back() + "\" @ line " +
		to_string(_currentLineIndexStack.back() + 1) + ": " + message);
	_hasThrownError = true;
}

void ScriptInterpreter::_checkEngineWarnings(unsigned int lastLoggerMessageCount)
{
	// Check if any new messages were logged
	auto messageCount = Logger::getMessageCount();
	if (messageCount > lastLoggerMessageCount)
	{
		// Retrieve all logged messages
		auto messageQueue = Logger::getMessageQueue();

		// Iterate through all new messages
		for (unsigned int i = lastLoggerMessageCount - 1; i < messageCount; i++)
		{
			// Check if logged message is a warning
			if (messageQueue[i].substr(0, string("[Warn]").size()) == "[Warn]")
			{
				_hasThrownError = true;
			}
		}
	}
}

Vec2 ScriptInterpreter::_convertGuiPositionToViewport(Vec2 position)
{
	if (!_fe3d.application_isExported())
	{
		auto sizeMultiplier = Vec2(Config::getInst().getViewportSize()) /
			Vec2(static_cast<float>(Config::getInst().getWindowSize().x), static_cast<float>(Config::getInst().getWindowSize().y));
		auto positionMultiplier = Vec2(Config::getInst().getViewportPosition()) /
			Vec2(static_cast<float>(Config::getInst().getWindowSize().x), static_cast<float>(Config::getInst().getWindowSize().y));
		position *= sizeMultiplier;
		auto offset = Vec2(1.0f) - Vec2((positionMultiplier.x * 2.0f) + sizeMultiplier.x, (positionMultiplier.y * 2.0f) + sizeMultiplier.y);
		position += Vec2(fabsf(offset.x), fabsf(offset.y));
	}

	return position;
}

Vec2 ScriptInterpreter::_convertGuiPositionFromViewport(Vec2 position)
{
	if (!_fe3d.application_isExported())
	{
		auto sizeMultiplier = Vec2(Config::getInst().getViewportSize()) /
			Vec2(static_cast<float>(Config::getInst().getWindowSize().x), static_cast<float>(Config::getInst().getWindowSize().y));
		auto positionMultiplier = Vec2(Config::getInst().getViewportPosition()) /
			Vec2(static_cast<float>(Config::getInst().getWindowSize().x), static_cast<float>(Config::getInst().getWindowSize().y));
		auto offset = Vec2(1.0f) - Vec2((positionMultiplier.x * 2.0f) + sizeMultiplier.x, (positionMultiplier.y * 2.0f) + sizeMultiplier.y);
		position -= Vec2(fabsf(offset.x), fabsf(offset.y));
		sizeMultiplier = Vec2(static_cast<float>(Config::getInst().getWindowSize().x), static_cast<float>(Config::getInst().getWindowSize().y)) /
			Vec2(Config::getInst().getViewportSize());
		positionMultiplier = Vec2(static_cast<float>(Config::getInst().getWindowSize().x), static_cast<float>(Config::getInst().getWindowSize().y)) /
			Vec2(Config::getInst().getViewportPosition());
		position *= sizeMultiplier;
	}

	return position;
}

Vec2 ScriptInterpreter::_convertGuiSizeToViewport(Vec2 size)
{
	if (!_fe3d.application_isExported())
	{
		auto sizeMultiplier = Vec2(Config::getInst().getViewportSize()) /
			Vec2(static_cast<float>(Config::getInst().getWindowSize().x), static_cast<float>(Config::getInst().getWindowSize().y));
		size *= sizeMultiplier;
	}

	return size;
}

Vec2 ScriptInterpreter::_convertGuiSizeFromViewport(Vec2 size)
{
	if (!_fe3d.application_isExported())
	{
		auto sizeMultiplier = Vec2(Config::getInst().getViewportSize()) /
			Vec2(static_cast<float>(Config::getInst().getWindowSize().x), static_cast<float>(Config::getInst().getWindowSize().y));
		size /= sizeMultiplier;
	}

	return size;
}