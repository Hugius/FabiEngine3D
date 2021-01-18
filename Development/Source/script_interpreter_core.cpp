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
	_lastLoggerMessageCount = _fe3d.logger_getMessageStack().size();

	// For every scriptfile
	for (auto& scriptID : _script.getAllScriptFileIDs())
	{
		auto scriptFile = _script.getScriptFile(scriptID);

		// Loop through every line
		string scriptType = "";
		for (unsigned int i = 0; i < scriptFile->getLineCount(); i++)
		{
			// Extract line content
			std::istringstream iss(scriptFile->getLineText(i));
			string type, name;
			iss >> type >> name;

			// Determine META type
			if (type == _metaKeyword && name == "script_type_init")
			{
				_initScriptIDs.push_back(scriptID);
				scriptType = "script_type_init";
			}
			else if (type == _metaKeyword && name == "script_type_update")
			{
				_updateScriptIDs.push_back(scriptID);
				scriptType = "script_type_update";
			}
			else if (type == _metaKeyword && name == "script_type_destroy")
			{
				_destroyScriptIDs.push_back(scriptID);
				scriptType = "script_type_destroy";
			}
			else if (type == _metaKeyword && name == "execution_entry")
			{
				// Check if script type is defined
				if (scriptType == "")
				{
					_fe3d.logger_throwWarning("Entry point defined before type @ script \"" + scriptID + "\"");
				}
				else
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
						_fe3d.logger_throwWarning("Entry point already defined @ script \"" + scriptID + "\"");
					}
				}
			}
		}

		// Give warning if no script type META found
		if (scriptType == "")
		{
			_fe3d.logger_throwWarning("No script_type META found @ script \"" + scriptID + "\"");
		}
	}

	// No entry point errors
	if (_initEntryID == "" && !_initScriptIDs.empty())
	{
		_fe3d.logger_throwWarning("No entry script chosen for INIT script(s)!");
	}
	if (_updateEntryID == "" && !_updateScriptIDs.empty())
	{
		_fe3d.logger_throwWarning("No entry script chosen for UPDATE script(s)!");
	}
	if (_destroyEntryID == "" && !_destroyScriptIDs.empty())
	{
		_fe3d.logger_throwWarning("No entry script chosen for DESTROY script(s)!");
	}

	// Remove META keyword lines from script for the interpretation phase
	for (auto& scriptID : _script.getAllScriptFileIDs())
	{
		auto scriptFile = _script.getScriptFile(scriptID);

		// Loop through every line
		BEGIN: for (unsigned int i = 0; i < scriptFile->getLineCount(); i++)
		{
			// Extract line content
			std::istringstream iss(scriptFile->getLineText(i));
			string possibleMetaKeyword;
			iss >> possibleMetaKeyword;

			// Check if META code
			if (possibleMetaKeyword == _metaKeyword)
			{
				scriptFile->setLineText(i, "");
				goto BEGIN;
			}
		}
	}

	// Check if any engine warnings were thrown
	_checkEngineWarnings();

	// Load skies
	_environmentEditor.loadSkyEntitiesFromFile();

	// Load models
	_modelEditor.loadGameEntitiesFromFile();

	// Load animations
	_animationEditor.loadAnimationsFromFile();

	// Load billboards
	_billboardEditor.loadBillboardEntitiesFromFile();

	// Load audio
	_audioEditor.loadAudioEntitiesFromFile();

	// Miscellaneous
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_fe3d.misc_setVsync(false);
}

void ScriptInterpreter::executeInitialization()
{
	if (_initEntryID != "")
	{
		_executeScript(_initEntryID, ScriptType::INIT);
	}
}

void ScriptInterpreter::executeUpdate()
{
	if (_updateEntryID != "")
	{
		_executeScript(_updateEntryID, ScriptType::UPDATE);
	}
}

void ScriptInterpreter::executeDestruction()
{
	if (_destroyEntryID != "")
	{
		_executeScript(_destroyEntryID, ScriptType::DESTROY);
	}
}

void ScriptInterpreter::unload()
{
	// Unload scene
	_sceneEditor.clearScene();

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

	// Delete game GUI
	for (const auto& ID : _fe3d.guiEntity_getAllIDs())
	{
		// Cannot delete engine GUI entities
		if (ID.front() != '@')
		{
			_fe3d.guiEntity_delete(ID);
		}
	}

	// Delete game text
	for (const auto& ID : _fe3d.textEntity_getAllIDs())
	{
		// Cannot delete engine GUI entities
		if (ID.front() != '@')
		{
			_fe3d.textEntity_delete(ID);
		}
	}

	// Reset camera
	_fe3d.camera_load(90.0f, 0.1f, 10000.0f, Vec3(0.0f));

	// Choose engine background again
	_fe3d.skyEntity_select("@@engineBackground");

	// Miscellaneous
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_fe3d.input_setKeyTogglingLocked(false);
	_fe3d.misc_setVsync(true);

	// Reset all variables
	_initScriptIDs.clear();
	_updateScriptIDs.clear();
	_destroyScriptIDs.clear();
	_globalVariables.clear();
	_initEntryID = "";
	_updateEntryID = "";
	_destroyEntryID = "";
	_lastLoggerMessageCount = 0;
	_hasThrownError = false;
	_scopeHasChanged = false;
	_passedScopeChanger = false;
}