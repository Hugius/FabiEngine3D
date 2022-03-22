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
			_throwStartupError("no`script_type` found in script \"" + scriptId + "\"");
			return;
		}

		if(scriptFile->getLineCount() < 2)
		{
			_throwStartupError("no`script_state` found in script \"" + scriptId + "\"");
			return;
		}

		string scriptType = "";
		if(scriptFile->getLine(0) == (META_KEYWORD + " script_type_initialize"))
		{
			_initializeScriptIds.push_back(scriptId);
			scriptType = "script_type_initialize";
		}
		else if(scriptFile->getLine(0) == (META_KEYWORD + " script_type_update"))
		{
			_updateScriptIds.push_back(scriptId);
			scriptType = "script_type_update";
		}
		else if(scriptFile->getLine(0) == (META_KEYWORD + " script_type_terminate"))
		{
			_terminateScriptIds.push_back(scriptId);
			scriptType = "script_type_terminate";
		}
		else
		{
			_throwStartupError("incorrect `script_type` in script \"" + scriptId + "\"");
			return;
		}

		if(scriptFile->getLine(1) == (META_KEYWORD + " script_state_entry"))
		{
			if(scriptType == "script_type_initialize")
			{
				if(_initEntryId.empty())
				{
					_initEntryId = _initializeScriptIds.back();
				}
				else
				{
					_throwStartupError("too many `script_state_entry` found for `script_type_initialize` scripts");
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
					_throwStartupError("too many `script_state_entry` found for `script_type_update` scripts");
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
					_throwStartupError("too many `script_state_entry` found for `script_type_terminate` scripts");
					return;
				}
			}
		}
		else if(scriptFile->getLine(1) == (META_KEYWORD + " script_state_wait"))
		{
			// Purposely left blank
		}
		else
		{
			_throwStartupError("incorrect `script_state` in script \"" + scriptId + "\"");
			return;
		}
	}

	if(_initializeScriptIds.empty())
	{
		_throwStartupError("no`script_type_initialize` scripts found");
		return;
	}
	if(_updateScriptIds.empty())
	{
		_throwStartupError("no`script_type_update` scripts found");
		return;
	}
	if(_terminateScriptIds.empty())
	{
		_throwStartupError("no`script_type_terminate` scripts found");
		return;
	}

	if(_initEntryId.empty())
	{
		_throwStartupError("no`script_state_entry` found for `script_type_initialize` scripts");
		return;
	}
	if(_updateEntryId.empty())
	{
		_throwStartupError("no`script_state_entry` found for `script_type_update` scripts");
		return;
	}
	if(_terminateEntryId.empty())
	{
		_throwStartupError("no`script_state_entry` found for `script_type_terminate` scripts");
		return;
	}

	for(const auto& scriptId : _script->getScriptFileIds())
	{
		auto scriptFile = _script->getScriptFile(scriptId);

		for(unsigned int lineIndex = 0; lineIndex < scriptFile->getLineCount(); lineIndex++)
		{
			auto scriptLineText = scriptFile->getLine(lineIndex);
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

				scriptFile->editLine(lineIndex, scriptLineText.substr(charIndex));
			}
		}
	}

	if(Configuration::getInst().isApplicationExported())
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

	_skyEditor->loadEntitiesFromFile();
	_terrainEditor->loadEntitiesFromFile();
	_waterEditor->loadEntitiesFromFile();
	_modelEditor->loadEntitiesFromFile();
	_quad3dEditor->loadEntitiesFromFile();
	_quad2dEditor->loadEntitiesFromFile();
	_text2dEditor->loadEntitiesFromFile();
	_animation2dEditor->loadAnimationsFromFile();
	_animation3dEditor->loadAnimationsFromFile();
	_soundEditor->loadSoundsFromFile();

	_fe3d->camera_reset();

	if(_fe3d->misc_isVsyncEnabled())
	{
		_fe3d->misc_setVsyncEnabled(false);
	}
	_fe3d->misc_setCursorVisible(true);

	_checkEngineWarnings(lastLoggerMessageCount);

	_fe3d->clock_create("scriptDebug");
}

void ScriptInterpreter::unload()
{
	if(!_worldEditor->getLoadedWorldId().empty())
	{
		_worldEditor->clearLoadedWorld();
	}

	_skyEditor->deleteLoadedEntities();
	_terrainEditor->deleteLoadedEntities();
	_waterEditor->deleteLoadedEntities();
	_modelEditor->deleteLoadedEntities();
	_quad3dEditor->deleteLoadedEntities();
	_quad2dEditor->deleteLoadedEntities();
	_text2dEditor->deleteLoadedEntities();
	_animation2dEditor->deleteLoadedAnimations();
	_animation3dEditor->deleteLoadedAnimations();
	_soundEditor->deleteLoadedSounds();

	for(const auto& id : _fe3d->sky_getIds())
	{
		_fe3d->sky_delete(id);
	}

	for(const auto& id : _fe3d->terrain_getIds())
	{
		_fe3d->terrain_delete(id);
	}

	for(const auto& id : _fe3d->water_getIds())
	{
		_fe3d->water_delete(id);
	}

	for(const auto& id : _fe3d->model_getIds())
	{
		_fe3d->model_delete(id);
	}

	for(const auto& id : _fe3d->quad3d_getIds())
	{
		_fe3d->quad3d_delete(id);
	}

	for(const auto& id : _fe3d->quad2d_getIds())
	{
		if(id[0] != '@')
		{
			_fe3d->quad2d_delete(id);
		}
	}

	for(const auto& id : _fe3d->text3d_getIds())
	{
		_fe3d->text3d_delete(id);
	}

	for(const auto& id : _fe3d->text2d_getIds())
	{
		if(id[0] != '@')
		{
			_fe3d->text2d_delete(id);
		}
	}

	for(const auto& id : _fe3d->aabb_getIds())
	{
		_fe3d->aabb_delete(id);
	}

	for(const auto& id : _fe3d->pointlight_getIds())
	{
		_fe3d->pointlight_delete(id);
	}

	for(const auto& id : _fe3d->spotlight_getIds())
	{
		_fe3d->spotlight_delete(id);
	}

	for(const auto& id : _fe3d->reflection_getIds())
	{
		_fe3d->reflection_delete(id);
	}

	for(const auto& id : _fe3d->animation3d_getIds())
	{
		_fe3d->animation3d_delete(id);
	}

	for(const auto& id : _fe3d->animation2d_getIds())
	{
		_fe3d->animation2d_delete(id);
	}

	for(const auto& id : _fe3d->sound3d_getIds())
	{
		_fe3d->sound3d_delete(id);
	}

	for(const auto& id : _fe3d->sound2d_getIds())
	{
		_fe3d->sound2d_delete(id);
	}

	_fe3d->camera_reset();

	_fe3d->collision_setCameraBox(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	_fe3d->collision_setCameraAabbResponseEnabled(false, false, false);
	_fe3d->collision_setCameraTerrainResponseEnabled(false);

	_fe3d->raycast_setTerrainIntersectionEnabled(false);

	_fe3d->graphics_setAntiAliasingEnabled(false);
	_fe3d->graphics_setAmbientLightingEnabled(false);
	_fe3d->graphics_setDirectionalLightingEnabled(false);
	_fe3d->graphics_setFogEnabled(false);
	_fe3d->graphics_setShadowsEnabled(false);
	_fe3d->graphics_setSkyExposureEnabled(false);
	_fe3d->graphics_setDofEnabled(false);
	_fe3d->graphics_setMotionBlurEnabled(false);
	_fe3d->graphics_setLensFlareEnabled(false);
	_fe3d->graphics_setBloomEnabled(false);
	_fe3d->graphics_setAmbientLightingColor(fvec3(0.0f));
	_fe3d->graphics_setAmbientLightingIntensity(0.0f);
	_fe3d->graphics_setDirectionalLightingPosition(fvec3(0.0f));
	_fe3d->graphics_setDirectionalLightingColor(fvec3(0.0f));
	_fe3d->graphics_setDirectionalLightingIntensity(0.0f);
	_fe3d->graphics_setFogColor(fvec3(0.0f));
	_fe3d->graphics_setFogThickness(0.0f);
	_fe3d->graphics_setFogMinDistance(0.0f);
	_fe3d->graphics_setFogMaxDistance(0.0f);
	_fe3d->graphics_setShadowCircleEnabled(false);
	_fe3d->graphics_setShadowPositionOffset(fvec3(0.0f));
	_fe3d->graphics_setShadowLookatOffset(fvec3(0.0f));
	_fe3d->graphics_setShadowSize(0.0f);
	_fe3d->graphics_setShadowLightness(0.0f);
	_fe3d->graphics_setShadowQuality(0);
	_fe3d->graphics_setShadowInterval(0);
	_fe3d->graphics_setShadowFollowingCamera(false);
	_fe3d->graphics_setBloomIntensity(0.0f);
	_fe3d->graphics_setBloomBlurCount(0);
	_fe3d->graphics_setBloomType(BloomType::EVERYTHING);
	_fe3d->graphics_setBloomQuality(0);
	_fe3d->graphics_setSkyExposureIntensity(0.0f);
	_fe3d->graphics_setSkyExposureSpeed(0.0f);
	_fe3d->graphics_setDofDynamicDistance(0.0f);
	_fe3d->graphics_setDofBlurDistance(0.0f);
	_fe3d->graphics_setDofDynamic(false);
	_fe3d->graphics_setDofQuality(0);
	_fe3d->graphics_setMotionBlurIntensity(0.0f);
	_fe3d->graphics_setMotionBlurQuality(0);
	_fe3d->graphics_setLensFlareMap("");
	_fe3d->graphics_setLensFlareIntensity(0.0f);
	_fe3d->graphics_setLensFlareSensitivity(0.0f);
	_fe3d->graphics_setCubeReflectionQuality(0);
	_fe3d->graphics_setPlanarReflectionQuality(0);
	_fe3d->graphics_setPlanarRefractionQuality(0);
	_fe3d->graphics_setAnisotropicFilteringQuality(0);
	_fe3d->graphics_setPlanarReflectionHeight(0.0f);

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

	for(const auto& clockId : _fe3d->clock_getIds())
	{
		_fe3d->clock_delete(clockId);
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