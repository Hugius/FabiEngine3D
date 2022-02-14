#include "script_interpreter.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <sstream>

using std::istringstream;

void ScriptInterpreter::load()
{
	auto lastLoggerMessageCount = Logger::getMessageCount();

	for(const auto& scriptId : _script->getScriptFileIds())
	{
		auto scriptFile = _script->getScriptFile(scriptId);

		if(scriptFile->getLineCount() == 0)
		{
			_throwStartupError("No `script_type` found in script \"" + scriptId + "\"");
			return;
		}

		if(scriptFile->getLineCount() < 2)
		{
			_throwStartupError("No `script_state` found in script \"" + scriptId + "\"");
			return;
		}

		string scriptType = "";
		if(scriptFile->getLineText(0) == (META_KEYWORD + " script_type_initialize"))
		{
			_initializeScriptIds.push_back(scriptId);
			scriptType = "script_type_initialize";
		}
		else if(scriptFile->getLineText(0) == (META_KEYWORD + " script_type_update"))
		{
			_updateScriptIds.push_back(scriptId);
			scriptType = "script_type_update";
		}
		else if(scriptFile->getLineText(0) == (META_KEYWORD + " script_type_terminate"))
		{
			_terminateScriptIds.push_back(scriptId);
			scriptType = "script_type_terminate";
		}
		else
		{
			_throwStartupError("Incorrect `script_type` in script \"" + scriptId + "\"");
			return;
		}

		if(scriptFile->getLineText(1) == (META_KEYWORD + " script_state_entry"))
		{
			if(scriptType == "script_type_initialize")
			{
				if(_initEntryId.empty())
				{
					_initEntryId = _initializeScriptIds.back();
				}
				else
				{
					_throwStartupError("Too many `script_state_entry` found for `script_type_initialize` scripts");
					return;
				}
			}
			if(scriptType == "script_type_update")
			{
				if(_updateEntryId.empty())
				{
					_updateEntryId = _updateScriptIds.back();
				}
				else
				{
					_throwStartupError("Too many `script_state_entry` found for `script_type_update` scripts");
					return;
				}
			}
			if(scriptType == "script_type_terminate")
			{
				if(_terminateEntryId.empty())
				{
					_terminateEntryId = _terminateScriptIds.back();
				}
				else
				{
					_throwStartupError("Too many `script_state_entry` found for `script_type_terminate` scripts");
					return;
				}
			}
		}
		else if(scriptFile->getLineText(1) == (META_KEYWORD + " script_state_wait"))
		{
			// Purposely left blank
		}
		else
		{
			_throwStartupError("Incorrect `script_state` in script \"" + scriptId + "\"");
			return;
		}
	}

	if(_initializeScriptIds.empty())
	{
		_throwStartupError("No `script_type_initialize` scripts found");
		return;
	}
	if(_updateScriptIds.empty())
	{
		_throwStartupError("No `script_type_update` scripts found");
		return;
	}
	if(_terminateScriptIds.empty())
	{
		_throwStartupError("No `script_type_terminate` scripts found");
		return;
	}

	if(_initEntryId.empty())
	{
		_throwStartupError("No `script_state_entry` found for `script_type_initialize` scripts");
		return;
	}
	if(_updateEntryId.empty())
	{
		_throwStartupError("No `script_state_entry` found for `script_type_update` scripts");
		return;
	}
	if(_terminateEntryId.empty())
	{
		_throwStartupError("No `script_state_entry` found for `script_type_terminate` scripts");
		return;
	}

	for(const auto& scriptId : _script->getScriptFileIds())
	{
		auto scriptFile = _script->getScriptFile(scriptId);

		for(unsigned int lineIndex = 0; lineIndex < scriptFile->getLineCount(); lineIndex++)
		{
			auto scriptLineText = scriptFile->getLineText(lineIndex);
			auto scriptLineTextStream = istringstream(scriptLineText);
			string noWhiteSpace;
			scriptLineTextStream >> noWhiteSpace;

			if(noWhiteSpace.substr(0, 3) == "///")
			{
				unsigned int charIndex;
				for(charIndex = 0; charIndex < scriptLineText.size(); charIndex++)
				{
					if(scriptLineText[charIndex] != ' ')
					{
						break;
					}
				}

				scriptFile->setLineText(lineIndex, scriptLineText.substr(charIndex));
			}
		}
	}

	if(Config::getInst().isApplicationExported())
	{
		auto skyImagePaths = _skyEditor->getImagePathsFromFile();
		auto terrainImagePaths = _terrainEditor->getImagePathsFromFile();
		auto waterImagePaths = _waterEditor->getImagePathsFromFile();
		auto modelMeshPaths = _modelEditor->getMeshPathsFromFile();
		auto modelImagePaths = _modelEditor->getImagePathsFromFile();
		auto quad3dImagePaths = _quad3dEditor->getImagePathsFromFile();
		auto text3dImagePaths = _text3dEditor->getImagePathsFromFile();
		auto quad2dImagePaths = _quad2dEditor->getImagePathsFromFile();
		auto text2dImagePaths = _text2dEditor->getImagePathsFromFile();
		auto audioPaths = _soundEditor->getAudioPathsFromFile();

		_fe3d->misc_cacheMeshes(modelMeshPaths, false);

		_fe3d->misc_cacheImages(terrainImagePaths, false);

		vector<string> imagePaths;
		imagePaths.insert(imagePaths.end(), skyImagePaths.begin(), skyImagePaths.end());
		imagePaths.insert(imagePaths.end(), terrainImagePaths.begin(), terrainImagePaths.end());
		imagePaths.insert(imagePaths.end(), waterImagePaths.begin(), waterImagePaths.end());
		imagePaths.insert(imagePaths.end(), modelImagePaths.begin(), modelImagePaths.end());
		imagePaths.insert(imagePaths.end(), quad3dImagePaths.begin(), quad3dImagePaths.end());
		imagePaths.insert(imagePaths.end(), text3dImagePaths.begin(), text3dImagePaths.end());
		imagePaths.insert(imagePaths.end(), quad2dImagePaths.begin(), quad2dImagePaths.end());
		imagePaths.insert(imagePaths.end(), text2dImagePaths.begin(), text2dImagePaths.end());
		_fe3d->misc_cacheImages(imagePaths, false);

		_fe3d->misc_cacheAudios(audioPaths, false);
	}

	_skyEditor->loadFromFile();
	_terrainEditor->loadFromFile();
	_waterEditor->loadFromFile();
	_modelEditor->loadFromFile();
	_quad3dEditor->loadFromFile();
	_quad2dEditor->loadFromFile();
	_text2dEditor->loadFromFile();
	_animation2dEditor->loadFromFile();
	_animation3dEditor->loadFromFile();
	_soundEditor->loadFromFile();

	_fe3d->camera_reset();

	if(_fe3d->misc_isVsyncEnabled())
	{
		_fe3d->misc_setVsyncEnabled(false);
	}
	_fe3d->misc_setCursorVisible(true);

	_checkEngineWarnings(lastLoggerMessageCount);
}

void ScriptInterpreter::unload()
{
	_worldEditor->clearLoadedWorld();

	_fe3d->sky_deleteAll();
	_fe3d->terrain_deleteAll();
	_fe3d->water_deleteAll();
	_fe3d->model_deleteAll();
	_fe3d->quad3d_deleteAll();
	_fe3d->aabb_deleteAll();
	_fe3d->sound2d_deleteAll();
	_fe3d->sound3d_deleteAll();
	_fe3d->pointlight_deleteAll();
	_fe3d->spotlight_deleteAll();
	_fe3d->reflection_deleteAll();
	_fe3d->animation3d_deleteAll();
	_fe3d->animation2d_deleteAll();

	for(const auto& id : _fe3d->quad2d_getIds())
	{
		if(id[0] != '@')
		{
			_fe3d->quad2d_delete(id);
		}
	}

	for(const auto& id : _fe3d->text2d_getIds())
	{
		if(id[0] != '@')
		{
			_fe3d->text2d_delete(id);
		}
	}

	for(const auto& id : _quad2dEditor->getLoadedEntityIds())
	{
		_fe3d->quad2d_delete(id);
	}

	for(const auto& id : _text2dEditor->getLoadedEntityIds())
	{
		_fe3d->text2d_delete(id);
	}

	_fe3d->camera_reset();

	_fe3d->collision_setCameraBox(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	_fe3d->collision_setCameraAabbResponseEnabled(false, false, false);
	_fe3d->collision_setCameraTerrainResponseEnabled(false);

	_fe3d->raycast_setTerrainIntersectionEnabled(false);

	_fe3d->gfx_setAntiAliasingEnabled(false);
	_fe3d->gfx_setAmbientLightingEnabled(false);
	_fe3d->gfx_setDirectionalLightingEnabled(false);
	_fe3d->gfx_setFogEnabled(false);
	_fe3d->gfx_setShadowsEnabled(false);
	_fe3d->gfx_setSkyExposureEnabled(false);
	_fe3d->gfx_setDofEnabled(false);
	_fe3d->gfx_setMotionBlurEnabled(false);
	_fe3d->gfx_setLensFlareEnabled(false);
	_fe3d->gfx_setBloomEnabled(false);
	_fe3d->gfx_setAmbientLightingColor(fvec3(0.0f));
	_fe3d->gfx_setAmbientLightingIntensity(0.0f);
	_fe3d->gfx_setDirectionalLightingPosition(fvec3(0.0f));
	_fe3d->gfx_setDirectionalLightingColor(fvec3(0.0f));
	_fe3d->gfx_setDirectionalLightingIntensity(0.0f);
	_fe3d->gfx_setFogColor(fvec3(0.0f));
	_fe3d->gfx_setFogThickness(0.0f);
	_fe3d->gfx_setFogMinDistance(0.0f);
	_fe3d->gfx_setFogMaxDistance(0.0f);
	_fe3d->gfx_setShadowCircleEnabled(false);
	_fe3d->gfx_setShadowPositionOffset(fvec3(0.0f));
	_fe3d->gfx_setShadowLookatOffset(fvec3(0.0f));
	_fe3d->gfx_setShadowSize(0.0f);
	_fe3d->gfx_setShadowLightness(0.0f);
	_fe3d->gfx_setShadowQuality(0);
	_fe3d->gfx_setShadowInterval(0);
	_fe3d->gfx_setShadowFollowingCamera(false);
	_fe3d->gfx_setBloomIntensity(0.0f);
	_fe3d->gfx_setBloomBlurCount(0);
	_fe3d->gfx_setBloomType(BloomType::EVERYTHING);
	_fe3d->gfx_setBloomQuality(0);
	_fe3d->gfx_setSkyExposureIntensity(0.0f);
	_fe3d->gfx_setSkyExposureSpeed(0.0f);
	_fe3d->gfx_setDofDynamicDistance(0.0f);
	_fe3d->gfx_setDofBlurDistance(0.0f);
	_fe3d->gfx_setDofDynamic(false);
	_fe3d->gfx_setDofQuality(0);
	_fe3d->gfx_setMotionBlurIntensity(0.0f);
	_fe3d->gfx_setMotionBlurQuality(0);
	_fe3d->gfx_setLensFlareMap("");
	_fe3d->gfx_setLensFlareIntensity(0.0f);
	_fe3d->gfx_setLensFlareSensitivity(0.0f);
	_fe3d->gfx_setCubeReflectionQuality(0);
	_fe3d->gfx_setPlanarReflectionQuality(0);
	_fe3d->gfx_setPlanarRefractionQuality(0);
	_fe3d->gfx_setAnisotropicFilteringQuality(0);
	_fe3d->gfx_setPlanarReflectionHeight(0.0f);

	if(_fe3d->server_isRunning())
	{
		_fe3d->server_stop();
	}

	if(_fe3d->client_isRunning())
	{
		_fe3d->client_stop();
	}

	if(!_fe3d->misc_isVsyncEnabled())
	{
		_fe3d->misc_setVsyncEnabled(true);
	}
	if(_fe3d->misc_isMillisecondTimerStarted())
	{
		_fe3d->misc_stopMillisecondTimer();
	}
	_fe3d->misc_setCursorVisible(false);

	_debuggingTimes.clear();
	_localVariables.clear();
	_globalVariables.clear();
	_currentScriptIdsStack.clear();
	_lineStringStreams.clear();
	_initializeScriptIds.clear();
	_updateScriptIds.clear();
	_terminateScriptIds.clear();
	_currentLineIndexStack.clear();
	_initEntryId = "";
	_updateEntryId = "";
	_terminateEntryId = "";
	_engineFunctionCallCount = 0;
	_executionDepth = 0;
	_hasThrownError = false;
	_mustStopApplication = false;
	_hasPassedLoopStatement = false;
	_hasPassedIfStatement = false;
	_hasPassedElifStatement = false;
	_hasPassedElseStatement = false;
	_mustIgnoreDeeperScope = false;
	_isDebugging = false;
	_isExecutingInitialization = false;
	_isExecutingUpdate = false;
	_isExecutingTerminate = false;
}