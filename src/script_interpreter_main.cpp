#include "script_interpreter.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <sstream>

using std::istringstream;

ScriptInterpreter::ScriptInterpreter(FabiEngine3D& fe3d, Script& script, SkyEditor& skyEditor, TerrainEditor& terrainEditor, WaterEditor& waterEditor, ModelEditor& modelEditor, AnimationEditor& animationEditor, BillboardEditor& billboardEditor, AudioEditor& audioEditor, SceneEditor& sceneEditor)
	:
	_fe3d(fe3d),
	_script(script),
	_skyEditor(skyEditor),
	_terrainEditor(terrainEditor),
	_waterEditor(waterEditor),
	_modelEditor(modelEditor),
	_animationEditor(animationEditor),
	_billboardEditor(billboardEditor),
	_audioEditor(audioEditor),
	_sceneEditor(sceneEditor)
{

}

void ScriptInterpreter::load()
{
	// Save current amount of logged messages
	auto lastLoggerMessageCount = Logger::getMessageCount();

	// For every scriptfile
	for(const auto& scriptID : _script.getAllScriptFileIDs())
	{
		auto scriptFile = _script.getScriptFile(scriptID);

		// Determine script type
		string scriptType = "";
		if(scriptFile->getLineText(0) == (META_KEYWORD + " script_type_init"))
		{
			_initScriptIDs.push_back(scriptID);
			scriptType = "script_type_init";
		}
		else if(scriptFile->getLineText(0) == (META_KEYWORD + " script_type_update"))
		{
			_updateScriptIDs.push_back(scriptID);
			scriptType = "script_type_update";
		}
		else if(scriptFile->getLineText(0) == (META_KEYWORD + " script_type_destroy"))
		{
			_destroyScriptIDs.push_back(scriptID);
			scriptType = "script_type_destroy";
		}
		else
		{
			Logger::throwWarning("No script_type META found on line 1 @ script \"" + scriptID + "\"");
			_hasThrownError = true;
			return;
		}

		// Determine execution type
		if(scriptFile->getLineText(1) == (META_KEYWORD + " script_execution_entry"))
		{
			// Set entry point
			if(scriptType == "script_type_init" && _initEntryID.empty())
			{
				_initEntryID = _initScriptIDs.back();
			}
			else if(scriptType == "script_type_update" && _updateEntryID.empty())
			{
				_updateEntryID = _updateScriptIDs.back();
			}
			else if(scriptType == "script_type_destroy" && _destroyEntryID.empty())
			{
				_destroyEntryID = _destroyScriptIDs.back();
			}
			else
			{
				Logger::throwWarning("Entry point for " + scriptType + " defined multiple times!");
				_hasThrownError = true;
				return;
			}
		}
		else if(scriptFile->getLineText(1) == (META_KEYWORD + " script_execution_waiting"))
		{
			// <--- Purposely left blank
		}
		else
		{
			Logger::throwWarning("No script_execution META found on line 2 @ script \"" + scriptID + "\"");
			_hasThrownError = true;
			return;
		}
	}

	// No entry point errors
	if(_initEntryID.empty() && !_initScriptIDs.empty())
	{
		Logger::throwWarning("No script_execution_entry META defined for INIT script(s)!");
		_hasThrownError = true;
		return;
	}
	if(_updateEntryID.empty() && !_updateScriptIDs.empty())
	{
		Logger::throwWarning("No script_execution_entry META defined for UPDATE script(s)!");
		_hasThrownError = true;
		return;
	}
	if(_destroyEntryID.empty() && !_destroyScriptIDs.empty())
	{
		Logger::throwWarning("No script_execution_entry META defined for DESTROY script(s)!");
		_hasThrownError = true;
		return;
	}

	// Comment optimization for runtime execution
	for(const auto& scriptID : _script.getAllScriptFileIDs())
	{
		auto scriptFile = _script.getScriptFile(scriptID);

		// Loop through every line
		for(unsigned int lineIndex = 0; lineIndex < scriptFile->getLineCount(); lineIndex++)
		{
			// Remove trailing whitespace of comments
			auto scriptLineText = scriptFile->getLineText(lineIndex);
			auto scriptLineTextStream = istringstream(scriptLineText);
			string noWhiteSpace;
			scriptLineTextStream >> noWhiteSpace;

			// Check if line is comment
			if(noWhiteSpace.substr(0, 3) == "///")
			{
				unsigned int charIndex;
				for(charIndex = 0; charIndex < scriptLineText.size(); charIndex++)
				{
					// Check if character found
					if(scriptLineText[charIndex] != ' ')
					{
						break;
					}
				}

				// Update line text (any whitespace before indented comments is removed)
				scriptFile->setLineText(lineIndex, scriptLineText.substr(charIndex));
			}
		}
	}

	// Load all editor assets of this project if in application preview
	if(Config::getInst().isApplicationExported())
	{
		// Gather all file paths
		auto skyTexturePaths = _skyEditor.getAllTexturePathsFromFile();
		auto terrainTexturePaths = _terrainEditor.getAllTerrainTexturePathsFromFile();
		auto terrainBitmapPaths = _terrainEditor.getAllTerrainBitmapPathsFromFile();
		auto waterTexturePaths = _waterEditor.getAllWaterTexturePathsFromFile();
		auto modelMeshPaths = _modelEditor.getAllMeshPathsFromFile();
		auto modelTexturePaths = _modelEditor.getAllTexturePathsFromFile();
		auto billboardTexturePaths = _billboardEditor.getAllTexturePathsFromFile();
		auto billboardFontPaths = _billboardEditor.getAllFontPathsFromFile();
		auto audioPaths = _audioEditor.getAllAudioPathsFromFile();

		// Cache meshes
		_fe3d.misc_cacheMeshesMultiThreaded(modelMeshPaths);

		// Cache 2D textures
		vector<string> texturePaths;
		texturePaths.insert(texturePaths.end(), terrainTexturePaths.begin(), terrainTexturePaths.end());
		texturePaths.insert(texturePaths.end(), waterTexturePaths.begin(), waterTexturePaths.end());
		texturePaths.insert(texturePaths.end(), modelTexturePaths.begin(), modelTexturePaths.end());
		texturePaths.insert(texturePaths.end(), billboardTexturePaths.begin(), billboardTexturePaths.end());
		_fe3d.misc_cacheTexturesMultiThreaded2D(texturePaths);

		// Cache 3D textures
		_fe3d.misc_cacheTexturesMultiThreaded3D(skyTexturePaths);

		// Cache bitmaps
		_fe3d.misc_cacheBitmapsMultiThreaded(terrainBitmapPaths);

		// Cache fonts
		_fe3d.misc_cacheFontsMultiThreaded(billboardFontPaths);

		// Cache sounds
		_fe3d.misc_cacheSoundsMultiThreaded(audioPaths);
	}

	// No sky at default
	_fe3d.skyEntity_selectMainSky("");

	// Load preview skies
	_skyEditor.loadSkyEntitiesFromFile();

	// Load preview terrains
	_terrainEditor.loadTerrainEntitiesFromFile();

	// Load preview waters
	_waterEditor.loadWaterEntitiesFromFile();

	// Load preview models
	_modelEditor.loadModelEntitiesFromFile();

	// Load preview animations
	_animationEditor.loadAnimationsFromFile(false);

	// Load preview billboards
	_billboardEditor.loadBillboardEntitiesFromFile();

	// Load preview audio
	_audioEditor.loadAudioEntitiesFromFile();

	// Camera
	_fe3d.camera_reset();

	// Default graphics
	_fe3d.gfx_setPlanarReflectionHeight(0.0f);

	// Directional light source
	const string texturePath = "engine\\textures\\light_source.png";
	_fe3d.billboardEntity_create("@@lightSource");
	_fe3d.billboardEntity_setSize("@@lightSource", Vec2(0.0f));
	_fe3d.billboardEntity_setDiffuseMap("@@lightSource", texturePath);
	_fe3d.billboardEntity_setDepthMapIncluded("@@lightSource", false);
	_fe3d.billboardEntity_setShadowed("@@lightSource", false);
	_fe3d.billboardEntity_setReflected("@@lightSource", true);
	_fe3d.billboardEntity_setBright("@@lightSource", true);
	_fe3d.billboardEntity_setCameraFacingX("@@lightSource", true);
	_fe3d.billboardEntity_setCameraFacingY("@@lightSource", true);

	// Miscellaneous
	if(_fe3d.misc_isVsyncEnabled())
	{
		_fe3d.misc_disableVsync();
	}
	_fe3d.misc_setCursorVisible(true);

	// Check if any engine warnings were thrown
	_checkEngineWarnings(lastLoggerMessageCount);
}

void ScriptInterpreter::executeInitialization()
{
	if(_initEntryID != "")
	{
		_isExecutingInitialization = true;

		_executeScript(_initEntryID, ScriptType::INIT);

		_isExecutingInitialization = false;
	}
}

void ScriptInterpreter::executeUpdate(bool debug)
{
	if(_updateEntryID != "")
	{
		_isExecutingUpdate = true;

		// Start debugging if specified
		_isDebugging = debug;
		_debuggingTimes.clear();

		// Execute update scripting
		_executeScript(_updateEntryID, ScriptType::UPDATE);

		// Log debugging results
		if(_isDebugging)
		{
			// Calculate total debugging time
			float totalTime = 0.0f;
			for(const auto& [scriptID, time] : _debuggingTimes)
			{
				totalTime += time;
			}

			// Print times
			Logger::throwDebug("Debugging results:");
			for(const auto& [scriptID, time] : _debuggingTimes)
			{
				float percentage = (time / totalTime) * 100.0f;
				Logger::throwDebug("Script \"" + scriptID + "\" ---> " + to_string(percentage) + "%");
			}
			Logger::throwDebug("");
		}

		_isExecutingUpdate = false;
	}
}

void ScriptInterpreter::executeDestruction()
{
	if(_destroyEntryID != "")
	{
		_isExecutingDestruction = true;

		_executeScript(_destroyEntryID, ScriptType::DESTROY);

		_isExecutingDestruction = false;
	}
}

void ScriptInterpreter::unload()
{
	// Delete all sky entities except the engine background
	for(const auto& ID : _fe3d.skyEntity_getAllIDs())
	{
		if(ID != "@@engineBackground")
		{
			_fe3d.skyEntity_delete(ID);
		}
	}
	_fe3d.skyEntity_selectMixSky("");
	_fe3d.skyEntity_setMixValue(0.0f);

	// Select engine background again
	if(!Config::getInst().isApplicationExported())
	{
		_fe3d.skyEntity_selectMainSky("@@engineBackground");
	}

	// Reset audio
	if(!_fe3d.misc_isSoundsEnabled())
	{
		_fe3d.misc_enableSounds();
	}
	if(!_fe3d.misc_isMusicEnabled())
	{
		_fe3d.misc_enableMusic();
	}
	_fe3d.music_clearPlaylist();

	// Stop animations
	_animationEditor.stopAllAnimations();

	// Delete all other entities
	_fe3d.terrainEntity_deleteAll();
	_fe3d.waterEntity_deleteAll();
	_fe3d.modelEntity_deleteAll();
	_fe3d.billboardEntity_deleteAll();
	_fe3d.aabbEntity_deleteAll();
	_fe3d.sound_deleteAll();
	_fe3d.pointlightEntity_deleteAll();
	_fe3d.spotlightEntity_deleteAll();
	_fe3d.reflectionEntity_deleteAll();

	// Delete game image entities
	for(const auto& ID : _fe3d.imageEntity_getAllIDs())
	{
		// Cannot delete engine image entities
		if(ID.front() != '@')
		{
			_fe3d.imageEntity_delete(ID);
		}
	}

	// Delete game text entities
	for(const auto& ID : _fe3d.textEntity_getAllIDs())
	{
		// Cannot delete engine text entities
		if(ID.front() != '@')
		{
			_fe3d.textEntity_delete(ID);
		}
	}

	// Reset camera
	_fe3d.camera_reset();

	// Reset collision
	_fe3d.collision_setCameraBox(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	if(_fe3d.collision_isCameraResponseEnabled())
	{
		_fe3d.collision_disableCameraResponse();
	}
	if(_fe3d.collision_isTerrainResponseEnabled())
	{
		_fe3d.collision_disableTerrainResponse();
	}

	// Reset raycasting
	if(_fe3d.raycast_isTerrainPointingEnabled())
	{
		_fe3d.raycast_disableTerrainPointing();
	}

	// Reset graphics
	if(_fe3d.gfx_isAmbientLightingEnabled())
	{
		_fe3d.gfx_disableAmbientLighting(true);
	}
	if(_fe3d.gfx_isDirectionalLightingEnabled())
	{
		_fe3d.gfx_disableDirectionalLighting(true);
	}
	if(_fe3d.gfx_isFogEnabled())
	{
		_fe3d.gfx_disableFog(true);
	}
	if(_fe3d.gfx_isShadowsEnabled())
	{
		_fe3d.gfx_disableShadows(true);
	}
	if(_fe3d.gfx_isSkyExposureEnabled())
	{
		_fe3d.gfx_disableSkyExposure(true);
	}
	if(_fe3d.gfx_isDofEnabled())
	{
		_fe3d.gfx_disableDOF(true);
	}
	if(_fe3d.gfx_isMotionBlurEnabled())
	{
		_fe3d.gfx_disableMotionBlur(true);
	}
	if(_fe3d.gfx_isLensFlareEnabled())
	{
		_fe3d.gfx_disableLensFlare(true);
	}
	if(_fe3d.gfx_isBloomEnabled())
	{
		_fe3d.gfx_disableBloom(true);
	}

	// Reset networking server
	if(_fe3d.networkServer_isRunning())
	{
		_fe3d.networkServer_stop();
	}

	// Reset networking client
	if(_fe3d.networkClient_isRunning())
	{
		_fe3d.networkClient_stop();
	}

	// Miscellaneous
	if(_fe3d.misc_isAabbFrameRenderingEnabled())
	{
		_fe3d.misc_disableAabbFrameRendering();
	}
	if(_fe3d.misc_isWireFrameRenderingEnabled())
	{
		_fe3d.misc_disableWireFrameRendering();
	}
	if(!_fe3d.misc_isVsyncEnabled())
	{
		_fe3d.misc_enableVsync();
	}
	if(_fe3d.misc_isMillisecondTimerStarted())
	{
		_fe3d.misc_stopMillisecondTimer();
	}
	_fe3d.misc_setCursorVisible(false);

	// Reset all variables
	_debuggingTimes.clear();
	_localVariables.clear();
	_currentScriptIDsStack.clear();
	_currentLineIndexStack.clear();
	_initScriptIDs.clear();
	_updateScriptIDs.clear();
	_destroyScriptIDs.clear();
	_globalVariables.clear();
	_initEntryID = "";
	_updateEntryID = "";
	_destroyEntryID = "";
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
}