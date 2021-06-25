#include "script_interpreter.hpp"

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
	return _applicationMustStop;
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
	// Calculate scope depth of current scriptline
	unsigned int currentLineScopeDepth = countedSpaces / SPACES_PER_INDENT;

	// Check if there is any code right after a scope change
	if (_scopeHasChanged && ((currentLineScopeDepth != scopeDepth) || scriptLineText.substr(0, 3) == "///"))
	{
		_throwScriptError("no indented code after scope change!");
		return false;
	}
	else if (currentLineScopeDepth < scopeDepth) // End of current scope
	{
		scopeDepth = currentLineScopeDepth;
	}
	else if (currentLineScopeDepth > scopeDepth) // Outside of current scope
	{
		if (_passedScopeChanger) // Skip current line
		{
			return false;
		}
		else // Useless indented statement
		{
			_throwScriptError("useless indentation before statement!"); 
			return false;
		}
	}

	_scopeHasChanged = false;
	return true;
}

bool ScriptInterpreter::_validateCurrentProject()
{
	// Error checking
	if (_currentProjectID == "")
	{
		_fe3d.logger_throwError("No current project loaded --> ScriptInterpreter::_validateCurrentProject()");
	}

	// Check if saves folder still exists
	auto directoryPath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isApplicationExported() ? "" : ("projects\\" + _currentProjectID)) + "\\saves\\";
	if (!_fe3d.misc_isDirectoryExisting(directoryPath))
	{
		_fe3d.logger_throwError("Project \"" + _currentProjectID + "\" corrupted: \"saves\\\" folder missing!");
		return false;
	}

	return true;
}

ScriptConditionStatement* ScriptInterpreter::_getLastConditionStatement(vector<ScriptConditionStatement>& statements, unsigned int scopeDepth)
{
	auto i = static_cast<unsigned int>(statements.size());

	while (i--)
	{
		if (statements[i].scopeDepth == scopeDepth)
		{
			return &statements[i];
		}
	}

	return nullptr;
}

void ScriptInterpreter::_throwScriptError(const string& message)
{
	_fe3d.logger_throwWarning("ERROR @ script \"" + _currentScriptIDsStack.back() + "\" @ line " +
		to_string(_currentLineIndexStack.back() + 1) + ": " + message);
	_hasThrownError = true;
}

void ScriptInterpreter::_checkEngineWarnings(unsigned int lastLoggerMessageCount)
{
	// Check if any new messages were logged
	auto messageCount = _fe3d.logger_getMessageCount();
	if (messageCount > lastLoggerMessageCount)
	{
		// Retrieve all logged messages
		auto messageQueue = _fe3d.logger_getMessageQueue();

		// Loop over all new messages
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
	if (!_fe3d.engine_isApplicationExported())
	{
		auto sizeMultiplier = Vec2(_fe3d.misc_getViewportSize()) /
			Vec2(static_cast<float>(_fe3d.misc_getWindowSize().x), static_cast<float>(_fe3d.misc_getWindowSize().y));
		auto positionMultiplier = Vec2(_fe3d.misc_getViewportPosition()) /
			Vec2(static_cast<float>(_fe3d.misc_getWindowSize().x), static_cast<float>(_fe3d.misc_getWindowSize().y));
		position *= sizeMultiplier;
		auto offset = Vec2(1.0f) - Vec2((positionMultiplier.x * 2.0f) + sizeMultiplier.x, (positionMultiplier.y * 2.0f) + sizeMultiplier.y);
		position += Vec2(fabsf(offset.x), fabsf(offset.y));
	}

	return position;
}

Vec2 ScriptInterpreter::_convertGuiPositionFromViewport(Vec2 position)
{
	if (!_fe3d.engine_isApplicationExported())
	{
		auto sizeMultiplier = Vec2(_fe3d.misc_getViewportSize()) /
			Vec2(static_cast<float>(_fe3d.misc_getWindowSize().x), static_cast<float>(_fe3d.misc_getWindowSize().y));
		auto positionMultiplier = Vec2(_fe3d.misc_getViewportPosition()) /
			Vec2(static_cast<float>(_fe3d.misc_getWindowSize().x), static_cast<float>(_fe3d.misc_getWindowSize().y));
		auto offset = Vec2(1.0f) - Vec2((positionMultiplier.x * 2.0f) + sizeMultiplier.x, (positionMultiplier.y * 2.0f) + sizeMultiplier.y);
		position -= Vec2(fabsf(offset.x), fabsf(offset.y));
		sizeMultiplier = Vec2(static_cast<float>(_fe3d.misc_getWindowSize().x), static_cast<float>(_fe3d.misc_getWindowSize().y)) /
			Vec2(_fe3d.misc_getViewportSize());
		positionMultiplier = Vec2(static_cast<float>(_fe3d.misc_getWindowSize().x), static_cast<float>(_fe3d.misc_getWindowSize().y)) /
			Vec2(_fe3d.misc_getViewportPosition());
		position *= sizeMultiplier;
	}

	return position;
}

Vec2 ScriptInterpreter::_convertGuiSizeToViewport(Vec2 size)
{
	if (!_fe3d.engine_isApplicationExported())
	{
		auto sizeMultiplier = Vec2(_fe3d.misc_getViewportSize()) /
			Vec2(static_cast<float>(_fe3d.misc_getWindowSize().x), static_cast<float>(_fe3d.misc_getWindowSize().y));
		size = size * sizeMultiplier;
	}

	return size;
}

Vec2 ScriptInterpreter::_convertGuiSizeFromViewport(Vec2 size)
{
	if (!_fe3d.engine_isApplicationExported())
	{
		auto sizeMultiplier = Vec2(static_cast<float>(_fe3d.misc_getWindowSize().x), static_cast<float>(_fe3d.misc_getWindowSize().y)) /
			Vec2(_fe3d.misc_getViewportSize());
		size = size * sizeMultiplier;
	}

	return size;
}