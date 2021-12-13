#include "script_interpreter.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <sstream>

using std::istringstream;

ScriptInterpreter::ScriptInterpreter(FabiEngine3D& fe3d, Script& script, SkyEditor& skyEditor, TerrainEditor& terrainEditor, WaterEditor& waterEditor, ModelEditor& modelEditor, BillboardEditor& billboardEditor, Animation3dEditor& animation3dEditor, AudioEditor& audioEditor, WorldEditor& worldEditor)
	:
	_fe3d(fe3d),
	_script(script),
	_skyEditor(skyEditor),
	_terrainEditor(terrainEditor),
	_waterEditor(waterEditor),
	_modelEditor(modelEditor),
	_billboardEditor(billboardEditor),
	_audioEditor(audioEditor),
	_animation3dEditor(animation3dEditor),
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
		// Cache meshes
		_fe3d.misc_cacheMeshesMultiThreaded(_modelEditor.getAllMeshPathsFromFile());

		// Cache 2D textures
		vector<string> texturePaths2D;
		texturePaths2D.insert(texturePaths2D.end(),
							  _terrainEditor.getAllTexturePathsFromFile().begin(),
							  _terrainEditor.getAllTexturePathsFromFile().end());
		texturePaths2D.insert(texturePaths2D.end(),
							  _waterEditor.getAllTexturePathsFromFile().begin(),
							  _waterEditor.getAllTexturePathsFromFile().end());
		texturePaths2D.insert(texturePaths2D.end(),
							  _modelEditor.getAllTexturePathsFromFile().begin(),
							  _modelEditor.getAllTexturePathsFromFile().end());
		texturePaths2D.insert(texturePaths2D.end(),
							  _billboardEditor.getAllTexturePathsFromFile().begin(),
							  _billboardEditor.getAllTexturePathsFromFile().end());
		_fe3d.misc_cache2dTexturesMultiThreaded(texturePaths2D);

		// Cache 3D textures
		_fe3d.misc_cache3dTexturesMultiThreaded(_skyEditor.getAllTexturePathsFromFile());

		// Cache bitmaps
		_fe3d.misc_cacheBitmapsMultiThreaded(_terrainEditor.getAllBitmapPathsFromFile());

		// Cache fonts
		_fe3d.misc_cacheFontsMultiThreaded(_billboardEditor.getAllFontPathsFromFile());

		// Cache sounds
		_fe3d.misc_cacheSoundsMultiThreaded(_audioEditor.getAllAudioPathsFromFile());
	}

	// No sky by default
	_fe3d.sky_selectMainSky("");

	// Load preview skies
	_skyEditor.loadFromFile();

	// Load preview terrains
	_terrainEditor.loadFromFile();

	// Load preview waters
	_waterEditor.loadFromFile();

	// Load preview models
	_modelEditor.loadFromFile();

	// Load preview animations
	_animation3dEditor.loadFromFile(false);

	// Load preview billboards
	_billboardEditor.loadFromFile();

	// Load preview audio
	_audioEditor.loadFromFile();

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

	// Stop 3D animations
	_animation3dEditor.stopAllAnimations();

	// Delete all other entities
	_fe3d.terrain_deleteAll();
	_fe3d.water_deleteAll();
	_fe3d.model_deleteAll();
	_fe3d.billboard_deleteAll();
	_fe3d.aabb_deleteAll();
	_fe3d.sound2d_deleteAll();
	_fe3d.sound3d_deleteAll();
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