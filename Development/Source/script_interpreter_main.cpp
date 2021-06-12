#include "script_interpreter.hpp"

#include <sstream>

ScriptInterpreter::ScriptInterpreter(FabiEngine3D& fe3d, Script& script, SceneEditor& sceneEditor,
	ModelEditor& modelEditor, AnimationEditor& animationEditor, BillboardEditor& billboardEditor, 
	AudioEditor& audioEditor, EnvironmentEditor& environmentEditor) :
	_fe3d(fe3d),
	_script(script),
	_sceneEditor(sceneEditor),
	_modelEditor(modelEditor),
	_animationEditor(animationEditor),
	_billboardEditor(billboardEditor),
	_audioEditor(audioEditor),
	_environmentEditor(environmentEditor)
{
	
}

void ScriptInterpreter::load()
{
	// Save current amount of logged messages
	_lastLoggerMessageCount = _fe3d.logger_getMessageCount();

	// For every scriptfile
	for (const auto& scriptID : _script.getAllScriptFileIDs())
	{
		auto scriptFile = _script.getScriptFile(scriptID);

		// Determine script type
		string scriptType = "";
		if (scriptFile->getLineText(0) == (META_KEYWORD + " script_type_init"))
		{
			_initScriptIDs.push_back(scriptID);
			scriptType = "script_type_init";
		}
		else if (scriptFile->getLineText(0) == (META_KEYWORD + " script_type_update"))
		{
			_updateScriptIDs.push_back(scriptID);
			scriptType = "script_type_update";
		}
		else if (scriptFile->getLineText(0) == (META_KEYWORD + " script_type_destroy"))
		{
			_destroyScriptIDs.push_back(scriptID);
			scriptType = "script_type_destroy";
		}
		else
		{
			_fe3d.logger_throwWarning("No script_type META found on line 1 @ script \"" + scriptID + "\"");
			_hasThrownError = true;
			return;
		}

		// Determine execution type
		if (scriptFile->getLineText(1) == (META_KEYWORD + " script_execution_entry"))
		{
			// Set entry point
			if (scriptType == "script_type_init" && _initEntryID == "")
			{
				_initEntryID = _initScriptIDs.back();
			}
			else if (scriptType == "script_type_update" && _updateEntryID == "")
			{
				_updateEntryID = _updateScriptIDs.back();
			}
			else if (scriptType == "script_type_destroy" && _destroyEntryID == "")
			{
				_destroyEntryID = _destroyScriptIDs.back();
			}
			else
			{
				_fe3d.logger_throwWarning("Entry point for " + scriptType + " defined multiple times!");
				_hasThrownError = true;
				return;
			}
		}
		else if (scriptFile->getLineText(1) == (META_KEYWORD + " script_execution_waiting"))
		{
			// <--- Purposely left blank
		}
		else
		{
			_fe3d.logger_throwWarning("No script_execution META found on line 2 @ script \"" + scriptID + "\"");
			_hasThrownError = true;
			return;
		}
	}

	// No entry point errors
	if (_initEntryID == "" && !_initScriptIDs.empty())
	{
		_fe3d.logger_throwWarning("No script_execution_entry META defined for INIT script(s)!");
		_hasThrownError = true;
		return;
	}
	if (_updateEntryID == "" && !_updateScriptIDs.empty())
	{
		_fe3d.logger_throwWarning("No script_execution_entry META defined for UPDATE script(s)!");
		_hasThrownError = true;
		return;
	}
	if (_destroyEntryID == "" && !_destroyScriptIDs.empty())
	{
		_fe3d.logger_throwWarning("No script_execution_entry META defined for DESTROY script(s)!");
		_hasThrownError = true;
		return;
	}

	// Comment optimization for runtime
	for (const auto& scriptID : _script.getAllScriptFileIDs())
	{
		auto scriptFile = _script.getScriptFile(scriptID);

		// Loop through every line
		for (unsigned int lineIndex = 0; lineIndex < scriptFile->getLineCount(); lineIndex++)
		{
			// Remove trailing whitespace of comments
			auto scriptLineText = scriptFile->getLineText(lineIndex);
			auto scriptLineTextStream = std::istringstream(scriptLineText);
			string noWhiteSpace;
			scriptLineTextStream >> noWhiteSpace;

			// Update line text
			if (noWhiteSpace.substr(0, 3) == "///")
			{
				unsigned int charIndex;
				for (charIndex = 0; charIndex < scriptLineText.size(); charIndex++)
				{
					if (scriptLineText[charIndex] != ' ')
					{
						break;
					}
				}
				scriptFile->setLineText(lineIndex, scriptLineText.substr(charIndex));
			}
		}
	}

	// Preload all big assets of this project, only in game preview
	if (_fe3d.engine_isGameExported())
	{
		vector<string> texturePaths;

		auto skyTextures = _environmentEditor.getAllSkyTexturePathsFromFile();
		auto terrainTextures = _environmentEditor.getAllTerrainTexturePathsFromFile();
		auto waterTextures = _environmentEditor.getAllWaterTexturePathsFromFile();
		auto modelTextures = _modelEditor.getAllTexturePathsFromFile(); // This function already pre-caches all mesh files
		auto billboardTextures = _billboardEditor.getAllTexturePathsFromFile();
		auto audioPaths = _audioEditor.getAllAudioPathsFromFile();

		texturePaths.insert(texturePaths.end(), terrainTextures.begin(), terrainTextures.end());
		texturePaths.insert(texturePaths.end(), waterTextures.begin(), waterTextures.end());
		texturePaths.insert(texturePaths.end(), modelTextures.begin(), modelTextures.end());
		texturePaths.insert(texturePaths.end(), billboardTextures.begin(), billboardTextures.end());

		_fe3d.misc_cacheTexturesMultiThreaded2D(texturePaths); // Pre-cache 2D texture files
		_fe3d.misc_cacheTexturesMultiThreaded3D(skyTextures); // Pre-cache 3D texture files
		_fe3d.misc_cacheAudioMultiThreaded(audioPaths); // Pre-cache audio files
	}

	// No sky at default
	_fe3d.skyEntity_select("");

	// Load preview environments
	_environmentEditor.loadSkyEntitiesFromFile();
	_environmentEditor.loadTerrainEntitiesFromFile();
	_environmentEditor.loadWaterEntitiesFromFile();

	// Load preview models
	_modelEditor.loadModelEntitiesFromFile();

	// Load preview animations
	_animationEditor.loadAnimationsFromFile();

	// Load preview billboards
	_billboardEditor.loadBillboardEntitiesFromFile();

	// Load preview audio
	_audioEditor.loadAudioEntitiesFromFile();

	// Default camera
	_fe3d.camera_load(90.0f, 0.1f, 10000.0f, Vec3(0.0f));

	// Directional light source
	const string texturePath = "engine_assets\\textures\\light_source.png";
	_fe3d.billboardEntity_add("@@lightSource", texturePath, Vec3(0.0f), Vec3(0.0f), Vec2(0.0f), true, true, true, true);
	_fe3d.billboardEntity_setDepthMapIncluded("@@lightSource", false);
	_fe3d.billboardEntity_setLightness("@@lightSource", 10000.0f);

	// Default graphics
	_fe3d.gfx_enableSpecularLighting();
	_fe3d.gfx_enablePointLighting();
	_fe3d.gfx_enableSkyReflections(0.5f);
	_fe3d.gfx_enableSceneReflections(0.5f);
	_fe3d.gfx_enableLightMapping();
	_fe3d.gfx_enableNormalMapping();
	_fe3d.gfx_enableWaterEffects();

	// Miscellaneous
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_fe3d.misc_setVsync(false);

	// Check if any engine warnings were thrown
	_checkEngineWarnings();
}

void ScriptInterpreter::executeInitialization()
{
	if (_initEntryID != "")
	{
		_isExecutingInitialization = true;

		_executeScript(_initEntryID, ScriptType::INIT);

		_isExecutingInitialization = false;
	}
}

void ScriptInterpreter::executeUpdate(bool debug)
{
	if (_updateEntryID != "")
	{
		_isExecutingUpdate = true;

		// Start debugging if specified
		_isDebugging = debug;
		_debuggingTimes.clear();

		// Execute update scripting
		_executeScript(_updateEntryID, ScriptType::UPDATE);

		// Log debugging results
		if (_isDebugging)
		{
			// Calculate total debugging time
			float totalTime = 0.0f;
			for (const auto& [scriptID, time] : _debuggingTimes)
			{
				totalTime += time;
			}

			// Print times
			_fe3d.logger_throwDebug("Debugging results:");
			for (const auto& [scriptID, time] : _debuggingTimes)
			{
				float percentage = (time / totalTime) * 100.0f;
				_fe3d.logger_throwDebug("Script \"" + scriptID + "\" ---> " + to_string(percentage) + "%");
			}
			_fe3d.logger_throwDebug("");
		}

		_isExecutingUpdate = false;
	}
}

void ScriptInterpreter::executeDestruction()
{
	if (_destroyEntryID != "")
	{
		_isExecutingDestruction = true;

		_executeScript(_destroyEntryID, ScriptType::DESTROY);

		_isExecutingDestruction = false;
	}
}

void ScriptInterpreter::unload()
{
	// Delete all sky entities except the engine background
	for (const auto& ID : _fe3d.skyEntity_getAllIDs())
	{
		if (ID != "@@engineBackground")
		{
			_fe3d.skyEntity_delete(ID);
		}
	}
	_fe3d.skyEntity_mixWithSelected("");
	_fe3d.skyEntity_setMixValue(0.0f);

	// Choose engine background again
	_fe3d.skyEntity_select("@@engineBackground");

	// Reset camera
	_fe3d.camera_load(90.0f, 0.1f, 10000.0f, Vec3(0.0f));

	// Reset audio
	_fe3d.misc_setSoundsEnabled(true);
	_fe3d.misc_setMusicEnabled(true);

	// Stop animations
	_animationEditor.stopAllAnimations();

	// Delete all other entities
	_fe3d.terrainEntity_deleteAll();
	_fe3d.waterEntity_deleteAll();
	_fe3d.modelEntity_deleteAll();
	_fe3d.billboardEntity_deleteAll();
	_fe3d.aabbEntity_deleteAll();
	_fe3d.lightEntity_deleteAll();
	_fe3d.soundEntity_deleteAll();
	_fe3d.music_clearPlaylist();

	// Disable collision response
	_fe3d.collision_disableCameraTerrainResponse();
	_fe3d.collision_disableCameraResponse();
	_fe3d.collision_setCameraBoxSize(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	// Disable graphics
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableSpecularLighting(true);
	_fe3d.gfx_disablePointLighting(true);
	_fe3d.gfx_disableSpotLighting(true);
	_fe3d.gfx_disableFog(true);
	_fe3d.gfx_disableSkyReflections(true);
	_fe3d.gfx_disableSceneReflections(true);
	_fe3d.gfx_disableLightMapping(true);
	_fe3d.gfx_disableNormalMapping(true);
	_fe3d.gfx_disableShadows(true);
	_fe3d.gfx_disableWaterEffects(true);
	_fe3d.gfx_disableSkyHDR(true);
	_fe3d.gfx_disableDOF(true);
	_fe3d.gfx_disableMotionBlur(true);
	_fe3d.gfx_disableLensFlare(true);

	// Delete game image entities
	for (const auto& ID : _fe3d.imageEntity_getAllIDs())
	{
		// Cannot delete engine image entities
		if (ID.front() != '@')
		{
			_fe3d.imageEntity_delete(ID);
		}
	}

	// Delete game text entities
	for (const auto& ID : _fe3d.textEntity_getAllIDs())
	{
		// Cannot delete engine text entities
		if (ID.front() != '@')
		{
			_fe3d.textEntity_delete(ID);
		}
	}

	// Stop networking server
	if (_fe3d.networkServer_isRunning())
	{
		_fe3d.networkServer_stop();
	}

	// Stop networking client
	if (_fe3d.networkClient_isRunning())
	{
		_fe3d.networkClient_stop();
	}

	// Miscellaneous
	_fe3d.misc_disableAabbFrameRendering();
	_fe3d.misc_disableWireframeRendering();
	_fe3d.misc_disableTerrainRaycasting();
	_fe3d.misc_stopMillisecondTimer();
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_fe3d.input_setKeyTogglingLocked(false);
	_fe3d.misc_setVsync(true);

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
	_lastLoggerMessageCount = 0;
	_engineFunctionCallCount = 0;
	_executionDepth = 0;
	_hasThrownError = false;
	_gameMustStop = false;
	_scopeHasChanged = false;
	_passedScopeChanger = false;
	_isDebugging = false;
}