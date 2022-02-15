#include "script_interpreter.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <sstream>

void ScriptInterpreter::setCurrentProjectId(const string& projectId)
{
	_currentProjectId = projectId;
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
				_throwRuntimeError("unnecessary indentation");
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
		_throwRuntimeError("incorrect indentation after LOOP statement");
		return false;
	}
	else if(_hasPassedIfStatement && isScopeDepthInvalid)
	{
		_throwRuntimeError("incorrect indentation after IF statement");
		return false;
	}
	else if(_hasPassedElifStatement && isScopeDepthInvalid)
	{
		_throwRuntimeError("incorrect indentation after ELIF statement");
		return false;
	}
	else if(_hasPassedElseStatement && isScopeDepthInvalid)
	{
		_throwRuntimeError("incorrect indentation after ELSE statement");
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
			_throwRuntimeError("unnecessary indentation before statement");
			return false;
		}
	}
	else
	{
		_mustIgnoreDeeperScope = false;
	}

	return true;
}

const bool ScriptInterpreter::_validateSavesDirectory()
{
	if(_currentProjectId.empty())
	{
		abort();
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");

	if(!Tools::isDirectoryExisting(directoryPath))
	{
		_throwRuntimeError("Project corrupted: directory `saves\\` does not exist");
		return false;
	}

	return true;
}

void ScriptInterpreter::_throwStartupError(const string& message)
{
	Logger::throwWarning("ERROR @ script: " + message);
	_hasThrownError = true;
}

void ScriptInterpreter::_throwRuntimeError(const string& message)
{
	Logger::throwWarning("ERROR @ script \"" + _currentScriptIdsStack.back() + "\" @ line " + to_string(_currentLineIndexStack.back() + 1) + ": " + message);
	_hasThrownError = true;
}

void ScriptInterpreter::_checkEngineWarnings(unsigned int lastLoggerMessageCount)
{
	auto messageCount = Logger::getMessageCount();
	if(messageCount > lastLoggerMessageCount)
	{
		for(unsigned int i = lastLoggerMessageCount - 1; i < messageCount; i++)
		{
			if(Logger::getMessageQueue()[i].substr(0, string("[Warn]").size()) == "[Warn]")
			{
				_hasThrownError = true;
			}
		}
	}
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

void ScriptInterpreter::inject(shared_ptr<Quad3dEditor> quad3dEditor)
{
	_quad3dEditor = quad3dEditor;
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

void ScriptInterpreter::inject(shared_ptr<Quad2dEditor> quad2dEditor)
{
	_quad2dEditor = quad2dEditor;
}

void ScriptInterpreter::inject(shared_ptr<Text3dEditor> text3dEditor)
{
	_text3dEditor = text3dEditor;
}

void ScriptInterpreter::inject(shared_ptr<Text2dEditor> text2dEditor)
{
	_text2dEditor = text2dEditor;
}

void ScriptInterpreter::inject(shared_ptr<WorldEditor> worldEditor)
{
	_worldEditor = worldEditor;
}

void ScriptInterpreter::inject(shared_ptr<CustomWorldManager> customWorldManager)
{
	_customWorldManager = customWorldManager;
}

void ScriptInterpreter::inject(shared_ptr<WorldUtilities> worldUtilities)
{
	_worldUtilities = worldUtilities;
}