#include "script_interpreter.hpp"
#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <sstream>

using std::istringstream;

void ScriptInterpreter::load()
{
	const auto lastLoggerMessageCount = Logger::getMessageCount();

	for(const auto & scriptId : _script->getScriptFileIds())
	{
		const auto scriptFile = _script->getScriptFile(scriptId);

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

		string scriptType;
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
			else if(scriptType == "script_type_update")
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
			else if(scriptType == "script_type_terminate")
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

	for(const auto & scriptId : _script->getScriptFileIds())
	{
		const auto scriptFile = _script->getScriptFile(scriptId);

		for(int lineIndex = 0; lineIndex < scriptFile->getLineCount(); lineIndex++)
		{
			const auto scriptLineText = scriptFile->getLine(lineIndex);

			auto scriptLineTextStream = istringstream(scriptLineText);

			string noWhiteSpace;
			scriptLineTextStream >> noWhiteSpace;

			if(noWhiteSpace.substr(0, 3) == "///")
			{
				int characterIndex = 0;

				for(characterIndex; characterIndex < static_cast<int>(scriptLineText.size()); characterIndex++)
				{
					if(scriptLineText[characterIndex] != ' ')
					{
						break;
					}
				}

				scriptFile->editLine(lineIndex, scriptLineText.substr(characterIndex));
			}
		}
	}

	_skyEditor->loadSkiesFromFile();
	_terrainEditor->loadTerrainsFromFile();
	_waterEditor->loadWatersFromFile();
	_modelEditor->loadModelsFromFile();
	_quad3dEditor->loadQuad3dsFromFile();
	_quad2dEditor->loadQuad2dsFromFile();
	_text3dEditor->loadText3dsFromFile();
	_text2dEditor->loadText2dsFromFile();
	_animation3dEditor->loadAnimation3dsFromFile();
	_animation2dEditor->loadAnimation2dsFromFile();
	_aabbEditor->loadAabbsFromFile();
	_pointlightEditor->loadPointlightsFromFile();
	_spotlightEditor->loadSpotlightsFromFile();
	_captorEditor->loadCaptorsFromFile();
	_sound3dEditor->loadSound3dsFromFile();
	_sound2dEditor->loadSound2dsFromFile();

	_fe3d->camera_reset();

	_fe3d->clock_create("scriptDebug");

	_fe3d->misc_setVsyncEnabled(false);

	_checkEngineWarnings(lastLoggerMessageCount);
}

void ScriptInterpreter::unload()
{
	if(!_worldEditor->getLoadedWorldId().empty())
	{
		_worldEditor->clearLoadedWorld();
	}

	_skyEditor->deleteLoadedSkies();
	_terrainEditor->deleteLoadedTerrains();
	_waterEditor->deleteLoadedWaters();
	_modelEditor->deleteLoadedModels();
	_quad3dEditor->deleteLoadedQuad3ds();
	_quad2dEditor->deleteLoadedQuad2ds();
	_text3dEditor->deleteLoadedText3ds();
	_text2dEditor->deleteLoadedText2ds();
	_animation3dEditor->deleteLoadedAnimation3ds();
	_animation2dEditor->deleteLoadedAnimation2ds();
	_aabbEditor->deleteLoadedAabbs();
	_pointlightEditor->deleteLoadedPointlights();
	_spotlightEditor->deleteLoadedSpotlights();
	_captorEditor->deleteLoadedCaptors();
	_sound3dEditor->deleteLoadedSound3ds();
	_sound2dEditor->deleteLoadedSound2ds();

	for(const auto & skyId : _fe3d->sky_getIds())
	{
		_fe3d->sky_delete(skyId);
	}

	for(const auto & terrainId : _fe3d->terrain_getIds())
	{
		_fe3d->terrain_delete(terrainId);
	}

	for(const auto & waterId : _fe3d->water_getIds())
	{
		_fe3d->water_delete(waterId);
	}

	for(const auto & modelId : _fe3d->model_getIds())
	{
		_fe3d->model_delete(modelId);
	}

	for(const auto & quad3dId : _fe3d->quad3d_getIds())
	{
		_fe3d->quad3d_delete(quad3dId);
	}

	for(const auto & quad2dId : _fe3d->quad2d_getIds())
	{
		if(quad2dId.substr(0, 2) != "@@")
		{
			_fe3d->quad2d_delete(quad2dId);
		}
	}

	for(const auto & text3dId : _fe3d->text3d_getIds())
	{
		_fe3d->text3d_delete(text3dId);
	}

	for(const auto & text2dId : _fe3d->text2d_getIds())
	{
		if(text2dId.substr(0, 2) != "@@")
		{
			_fe3d->text2d_delete(text2dId);
		}
	}

	for(const auto & animation3dId : _fe3d->animation3d_getIds())
	{
		_fe3d->animation3d_delete(animation3dId);
	}

	for(const auto & animation2dId : _fe3d->animation2d_getIds())
	{
		_fe3d->animation2d_delete(animation2dId);
	}

	for(const auto & aabbId : _fe3d->aabb_getIds())
	{
		_fe3d->aabb_delete(aabbId);
	}

	for(const auto & pointlightId : _fe3d->pointlight_getIds())
	{
		_fe3d->pointlight_delete(pointlightId);
	}

	for(const auto & spotlightId : _fe3d->spotlight_getIds())
	{
		_fe3d->spotlight_delete(spotlightId);
	}

	for(const auto & captorId : _fe3d->captor_getIds())
	{
		_fe3d->captor_delete(captorId);
	}

	for(const auto & sound3dId : _fe3d->sound3d_getIds())
	{
		_fe3d->sound3d_delete(sound3dId);
	}

	for(const auto & sound2dId : _fe3d->sound2d_getIds())
	{
		_fe3d->sound2d_delete(sound2dId);
	}

	for(const auto & clockId : _fe3d->clock_getIds())
	{
		_fe3d->clock_delete(clockId);
	}

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
	_fe3d->graphics_setAmbientLightingColor(fvec3(1.0f));
	_fe3d->graphics_setAmbientLightingIntensity(1.0f);
	_fe3d->graphics_setDirectionalLightingPosition(fvec3(0.0f));
	_fe3d->graphics_setDirectionalLightingColor(fvec3(1.0f));
	_fe3d->graphics_setDirectionalLightingIntensity(1.0f);
	_fe3d->graphics_setFogColor(fvec3(1.0f));
	_fe3d->graphics_setFogThickness(1.0f);
	_fe3d->graphics_setFogMinDistance(0.0f);
	_fe3d->graphics_setFogMaxDistance(0.0f);
	_fe3d->graphics_setShadowCircleEnabled(false);
	_fe3d->graphics_setShadowPositionOffset(fvec3(0.0f));
	_fe3d->graphics_setShadowLookatOffset(fvec3(0.0f));
	_fe3d->graphics_setShadowSize(0.0f);
	_fe3d->graphics_setShadowLightness(0.0f);
	_fe3d->graphics_setShadowQuality(0);
	_fe3d->graphics_setShadowInterval(0);
	_fe3d->graphics_setShadowFollowingCameraX(false);
	_fe3d->graphics_setShadowFollowingCameraY(false);
	_fe3d->graphics_setShadowFollowingCameraZ(false);
	_fe3d->graphics_setBloomIntensity(1.0f);
	_fe3d->graphics_setBloomBlurCount(0);
	_fe3d->graphics_setBloomType(BloomType::EVERYTHING);
	_fe3d->graphics_setBloomQuality(0);
	_fe3d->graphics_setSkyExposureIntensity(1.0f);
	_fe3d->graphics_setSkyExposureSpeed(0.0f);
	_fe3d->graphics_setDofDynamicDistance(0.0f);
	_fe3d->graphics_setDofBlurDistance(0.0f);
	_fe3d->graphics_setDofDynamic(false);
	_fe3d->graphics_setDofQuality(0);
	_fe3d->graphics_setMotionBlurIntensity(1.0f);
	_fe3d->graphics_setMotionBlurQuality(0);
	_fe3d->graphics_setLensFlareMap("");
	_fe3d->graphics_setLensFlareIntensity(1.0f);
	_fe3d->graphics_setLensFlareSensitivity(1.0f);
	_fe3d->graphics_setPlanarReflectionHeight(0.0f);
	_fe3d->graphics_setPlanarReflectionQuality(0);
	_fe3d->graphics_setPlanarRefractionHeight(0.0f);
	_fe3d->graphics_setPlanarRefractionQuality(0);
	_fe3d->graphics_setAnisotropicFilteringQuality(0);

	_fe3d->camera_reset();

	_fe3d->raycast_setTerrainIntersectionEnabled(false);

	_fe3d->collision_setCameraBox(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	_fe3d->collision_setCameraAabbResponseEnabled(false, false, false);
	_fe3d->collision_setCameraTerrainResponseEnabled(false);

	if(_fe3d->server_isRunning())
	{
		_fe3d->server_stop();
	}

	if(_fe3d->client_isRunning())
	{
		_fe3d->client_stop();
	}

	_fe3d->misc_setVsyncEnabled(true);

	_customWorldBuilder->resetBuild();
	_customWorldBuilder->clearLoadedWorld();

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