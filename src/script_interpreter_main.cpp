#include "script_interpreter.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <sstream>

using std::istringstream;

ScriptInterpreter::ScriptInterpreter(FabiEngine3D& fe3d, Script& script, SkyEditor& skyEditor, TerrainEditor& terrainEditor, WaterEditor& waterEditor, ModelEditor& modelEditor, BillboardEditor& billboardEditor, MeshAnimationEditor& meshAnimationEditor, AudioEditor& audioEditor, WorldEditor& worldEditor)
	:
	_fe3d(fe3d),
	_script(script),
	_skyEditor(skyEditor),
	_terrainEditor(terrainEditor),
	_waterEditor(waterEditor),
	_modelEditor(modelEditor),
	_billboardEditor(billboardEditor),
	_audioEditor(audioEditor),
	_meshAnimationEditor(meshAnimationEditor),
	_worldEditor(worldEditor)
{

}

void ScriptInterpreter::load()
{
	// Save current amount of logged messages
	auto lastLoggerMessageCount = Logger::getMessageCount();

	// Iterate through script files
	for(const auto& scriptID : _script.getAllScriptFileIDs())
	{
		auto scriptFile = _script.getScriptFile(scriptID);

		// Determine script type
		string scriptType = "";
		if(scriptFile->getLineText(0) == (META_KEYWORD + " script_type_initialize"))
		{
			_initializeScriptIDs.push_back(scriptID);
			scriptType = "script_type_initialize";
		}
		else if(scriptFile->getLineText(0) == (META_KEYWORD + " script_type_update"))
		{
			_updateScriptIDs.push_back(scriptID);
			scriptType = "script_type_update";
		}
		else if(scriptFile->getLineText(0) == (META_KEYWORD + " script_type_terminate"))
		{
			_terminateScriptIDs.push_back(scriptID);
			scriptType = "script_type_terminate";
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
			if(scriptType == "script_type_initialize" && _initEntryID.empty())
			{
				_initEntryID = _initializeScriptIDs.back();
			}
			else if(scriptType == "script_type_update" && _updateEntryID.empty())
			{
				_updateEntryID = _updateScriptIDs.back();
			}
			else if(scriptType == "script_type_terminate" && _terminateEntryID.empty())
			{
				_terminateEntryID = _terminateScriptIDs.back();
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
	if(_initEntryID.empty() && !_initializeScriptIDs.empty())
	{
		Logger::throwWarning("No script_execution_entry META defined for INITIALIZE script(s)!");
		_hasThrownError = true;
		return;
	}
	if(_updateEntryID.empty() && !_updateScriptIDs.empty())
	{
		Logger::throwWarning("No script_execution_entry META defined for UPDATE script(s)!");
		_hasThrownError = true;
		return;
	}
	if(_terminateEntryID.empty() && !_terminateScriptIDs.empty())
	{
		Logger::throwWarning("No script_execution_entry META defined for TERMINATE script(s)!");
		_hasThrownError = true;
		return;
	}

	// Comment optimization for runtime execution
	for(const auto& scriptID : _script.getAllScriptFileIDs())
	{
		// Retrieve script file
		auto scriptFile = _script.getScriptFile(scriptID);

		// Iterate through every line
		for(unsigned int lineIndex = 0; lineIndex < scriptFile->getLineCount(); lineIndex++)
		{
			// Remove trailing whitespace from comments
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

	// No sky by default
	_fe3d.sky_selectMainSky("");

	// Load preview skies
	_skyEditor.loadSkyEntitiesFromFile();

	// Load preview terrains
	_terrainEditor.loadTerrainEntitiesFromFile();

	// Load preview waters
	_waterEditor.loadWaterEntitiesFromFile();

	// Load preview models
	_modelEditor.loadModelEntitiesFromFile();

	// Load preview animations
	_meshAnimationEditor.loadAnimationsFromFile(false);

	// Load preview billboards
	_billboardEditor.loadBillboardEntitiesFromFile();

	// Load preview audio
	_audioEditor.loadAudioEntitiesFromFile();

	// Camera
	_fe3d.camera_reset();

	// Default graphics
	_fe3d.gfx_setPlanarReflectionHeight(0.0f);

	// Miscellaneous
	if(_fe3d.misc_isVsyncEnabled())
	{
		_fe3d.misc_disableVsync();
	}
	_fe3d.misc_setCursorVisible(true);

	// Check if any engine warnings were thrown
	_checkEngineWarnings(lastLoggerMessageCount);
}

void ScriptInterpreter::executeInitializeScripts()
{
	if(_initEntryID != "")
	{
		_isExecutingInitialization = true;

		_executeScript(_initEntryID, ScriptType::INITIALIZE);

		_isExecutingInitialization = false;
	}
}

void ScriptInterpreter::executeUpdateScripts(bool isDebugging)
{
	if(_updateEntryID != "")
	{
		_isExecutingUpdate = true;

		// Start debugging if specified
		_isDebugging = isDebugging;
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

void ScriptInterpreter::executeTerminateScripts()
{
	if(_terminateEntryID != "")
	{
		_isExecutingTerminate = true;

		_executeScript(_terminateEntryID, ScriptType::TERMINATE);

		_isExecutingTerminate = false;
	}
}

void ScriptInterpreter::unload()
{
	// Reset sky
	_fe3d.sky_selectMixSky("");
	_fe3d.sky_setMixValue(0.0f);

	// Select background
	if (!Config::getInst().isApplicationExported())
	{
		_fe3d.sky_selectMainSky("@@background");
	}

	// Delete all sky entities except the background
	for(const auto& ID : _fe3d.sky_getAllIDs())
	{
		if(ID != "@@background")
		{
			_fe3d.sky_delete(ID);
		}
	}

	// Reset audio
	_fe3d.music_clearPlaylist();

	// Stop mesh animations
	_meshAnimationEditor.stopAllAnimations();

	// Delete all other entities
	_fe3d.terrain_deleteAll();
	_fe3d.water_deleteAll();
	_fe3d.model_deleteAll();
	_fe3d.billboard_deleteAll();
	_fe3d.aabb_deleteAll();
	_fe3d.sound2D_deleteAll();
	_fe3d.sound3D_deleteAll();
	_fe3d.pointlight_deleteAll();
	_fe3d.spotlight_deleteAll();
	_fe3d.reflection_deleteAll();

	// Delete game image entities
	for(const auto& ID : _fe3d.image_getAllIDs())
	{
		// Cannot delete engine image entities
		if(ID[0] != '@')
		{
			_fe3d.image_delete(ID);
		}
	}

	// Delete game text entities
	for(const auto& ID : _fe3d.text_getAllIDs())
	{
		// Cannot delete engine text entities
		if(ID[0] != '@')
		{
			_fe3d.text_delete(ID);
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
	if(_fe3d.server_isRunning())
	{
		_fe3d.server_stop();
	}

	// Reset networking client
	if(_fe3d.client_isRunning())
	{
		_fe3d.client_stop();
	}

	// Miscellaneous
	if(_fe3d.misc_isAabbFrameRenderingEnabled())
	{
		_fe3d.misc_disableAabbFrameRendering();
	}
	if(_fe3d.misc_isWireframeRenderingEnabled())
	{
		_fe3d.misc_disableWireframeRendering();
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
	_initializeScriptIDs.clear();
	_updateScriptIDs.clear();
	_terminateScriptIDs.clear();
	_globalVariables.clear();
	_initEntryID = "";
	_updateEntryID = "";
	_terminateEntryID = "";
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