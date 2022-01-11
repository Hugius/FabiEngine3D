#include "script_interpreter.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <sstream>

void ScriptInterpreter::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool ScriptInterpreter::hasThrownError() const
{
	return _hasThrownError;
}

const bool ScriptInterpreter::gameMustStop() const
{
	return _mustStopApplication;
}

const unsigned int ScriptInterpreter::_countLeadingSpaces(const string& scriptLineText)
{
	int countedSpaces = 0;

	for(size_t i = 0; i < scriptLineText.size(); i++)
	{
		if(scriptLineText[i] == ' ')
		{
			if(i == (scriptLineText.size() - 1))
			{
				_throwScriptError("unnecessary indentation!");
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

const bool ScriptInterpreter::_validateScopeChange(unsigned int countedSpaces, const string& scriptLineText, unsigned int& scopeDepth)
{
	const unsigned int currentLineScopeDepth = (countedSpaces / SPACES_PER_INDENT);
	const bool isScopeDepthInvalid = (currentLineScopeDepth != (scopeDepth + static_cast<int>(_mustIgnoreDeeperScope)));

	if(_hasPassedLoopStatement && isScopeDepthInvalid)
	{
		_throwScriptError("incorrect indentation after LOOP statement!");
		return false;
	}
	else if(_hasPassedIfStatement && isScopeDepthInvalid)
	{
		_throwScriptError("incorrect indentation after IF statement!");
		return false;
	}
	else if(_hasPassedElifStatement && isScopeDepthInvalid)
	{
		_throwScriptError("incorrect indentation after ELIF statement!");
		return false;
	}
	else if(_hasPassedElseStatement && isScopeDepthInvalid)
	{
		_throwScriptError("incorrect indentation after ELSE statement!");
		return false;
	}
	else if(currentLineScopeDepth < scopeDepth)
	{
		scopeDepth = currentLineScopeDepth;
	}
	else if(currentLineScopeDepth > scopeDepth)
	{
		if(_mustIgnoreDeeperScope)
		{
			return false;
		}
		else
		{
			_throwScriptError("unnecessary indentation before statement!");
			return false;
		}
	}
	else
	{
		_mustIgnoreDeeperScope = false;
	}

	return true;
}

const bool ScriptInterpreter::_validateSavesDirectory() const
{
	if(_currentProjectID.empty())
	{
		Logger::throwError("ScriptInterpreter::_validateSavesDirectory");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "saves\\");

	if(!Tools::isDirectoryExisting(directoryPath))
	{
		Logger::throwWarning("Project corrupted: directory `saves\\` missing!");
		return false;
	}

	return true;
}

void ScriptInterpreter::_throwScriptError(const string& message)
{
	Logger::throwWarning("ERROR @ script \"" + _currentScriptIDsStack.back() + "\" @ line " +
						 to_string(_currentLineIndexStack.back() + 1) + ": " + message);
	_hasThrownError = true;
}

void ScriptInterpreter::_checkEngineWarnings(unsigned int lastLoggerMessageCount)
{
	auto messageCount = Logger::getMessageCount();
	if(messageCount > lastLoggerMessageCount)
	{
		const auto& messageQueue = Logger::getMessageQueue();

		for(unsigned int i = lastLoggerMessageCount - 1; i < messageCount; i++)
		{
			if(messageQueue[i].substr(0, string("[Warn]").size()) == "[Warn]")
			{
				_hasThrownError = true;
			}
		}
	}
}

const fvec2 ScriptInterpreter::_convertGuiPositionToViewport(fvec2 position) const
{
	if(!Config::getInst().isApplicationExported())
	{
		auto sizeMultiplier = fvec2(Config::getInst().getViewportSize()) /
			fvec2(static_cast<float>(Config::getInst().getWindowSize().x), static_cast<float>(Config::getInst().getWindowSize().y));
		auto positionMultiplier = fvec2(Config::getInst().getViewportPosition()) /
			fvec2(static_cast<float>(Config::getInst().getWindowSize().x), static_cast<float>(Config::getInst().getWindowSize().y));
		position *= sizeMultiplier;
		auto offset = fvec2(1.0f) - fvec2((positionMultiplier.x * 2.0f) + sizeMultiplier.x, (positionMultiplier.y * 2.0f) + sizeMultiplier.y);
		position += fvec2(fabsf(offset.x), fabsf(offset.y));
	}

	return position;
}

const fvec2 ScriptInterpreter::_convertGuiPositionFromViewport(fvec2 position) const
{
	if(!Config::getInst().isApplicationExported())
	{
		auto sizeMultiplier = fvec2(Config::getInst().getViewportSize()) /
			fvec2(static_cast<float>(Config::getInst().getWindowSize().x), static_cast<float>(Config::getInst().getWindowSize().y));
		auto positionMultiplier = fvec2(Config::getInst().getViewportPosition()) /
			fvec2(static_cast<float>(Config::getInst().getWindowSize().x), static_cast<float>(Config::getInst().getWindowSize().y));
		auto offset = fvec2(1.0f) - fvec2((positionMultiplier.x * 2.0f) + sizeMultiplier.x, (positionMultiplier.y * 2.0f) + sizeMultiplier.y);
		position -= fvec2(fabsf(offset.x), fabsf(offset.y));
		sizeMultiplier = fvec2(static_cast<float>(Config::getInst().getWindowSize().x), static_cast<float>(Config::getInst().getWindowSize().y)) /
			fvec2(Config::getInst().getViewportSize());
		positionMultiplier = fvec2(static_cast<float>(Config::getInst().getWindowSize().x), static_cast<float>(Config::getInst().getWindowSize().y)) /
			fvec2(Config::getInst().getViewportPosition());
		position *= sizeMultiplier;
	}

	return position;
}

const fvec2 ScriptInterpreter::_convertGuiSizeToViewport(fvec2 size) const
{
	if(!Config::getInst().isApplicationExported())
	{
		auto sizeMultiplier = fvec2(Config::getInst().getViewportSize()) /
			fvec2(static_cast<float>(Config::getInst().getWindowSize().x), static_cast<float>(Config::getInst().getWindowSize().y));
		size *= sizeMultiplier;
	}

	return size;
}

const fvec2 ScriptInterpreter::_convertGuiSizeFromViewport(fvec2 size) const
{
	if(!Config::getInst().isApplicationExported())
	{
		auto sizeMultiplier = fvec2(Config::getInst().getViewportSize()) /
			fvec2(static_cast<float>(Config::getInst().getWindowSize().x), static_cast<float>(Config::getInst().getWindowSize().y));
		size /= sizeMultiplier;
	}

	return size;
}

void ScriptInterpreter::inject(shared_ptr<EngineInterface> fe3d)
{
	_fe3d = fe3d;
}

void ScriptInterpreter::inject(shared_ptr<Script> script)
{
	_script = script;
}

void ScriptInterpreter::inject(shared_ptr<SkyEditor> skyEditor)
{
	_skyEditor = skyEditor;
}

void ScriptInterpreter::inject(shared_ptr<TerrainEditor> terrainEditor)
{
	_terrainEditor = terrainEditor;
}

void ScriptInterpreter::inject(shared_ptr<WaterEditor> waterEditor)
{
	_waterEditor = waterEditor;
}

void ScriptInterpreter::inject(shared_ptr<ModelEditor> modelEditor)
{
	_modelEditor = modelEditor;
}

void ScriptInterpreter::inject(shared_ptr<BillboardEditor> billboardEditor)
{
	_billboardEditor = billboardEditor;
}

void ScriptInterpreter::inject(shared_ptr<Animation2dEditor> animation2dEditor)
{
	_animation2dEditor = animation2dEditor;
}

void ScriptInterpreter::inject(shared_ptr<Animation3dEditor> animation3dEditor)
{
	_animation3dEditor = animation3dEditor;
}

void ScriptInterpreter::inject(shared_ptr<SoundEditor> soundEditor)
{
	_soundEditor = soundEditor;
}

void ScriptInterpreter::inject(shared_ptr<QuadEditor> quadEditor)
{
	_quadEditor = quadEditor;
}

void ScriptInterpreter::inject(shared_ptr<WorldEditor> worldEditor)
{
	_worldEditor = worldEditor;
}