#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dSceneFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:scene_load")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_sceneEditor.clearCurrentScene();
			_sceneEditor.loadEditorSceneFromFile(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_clear")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_sceneEditor.clearCurrentScene();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_get_current_id")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _sceneEditor.getLoadedSceneID();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:scene_is_custom_existing")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Compose file path
			string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" :
				("projects\\" + _currentProjectID)) + "\\scenes\\custom\\");
			string filePath = (directoryPath + arguments[0].getString() + ".fe3d");

			// Return
			auto result = _fe3d.misc_isFileExisting(filePath);
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:scene_create_custom")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_sceneEditor.createCustomScene(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_add_custom_sky")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_sceneEditor.addSkyToCustomScene();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_add_custom_terrain")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_sceneEditor.addTerrainToCustomScene();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_add_custom_water")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_sceneEditor.addWaterToCustomScene();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_add_custom_model")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_sceneEditor.addModelToCustomScene(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_add_custom_billboard")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_sceneEditor.addBillboardToCustomScene(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_add_custom_aabb")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_sceneEditor.addAabbToCustomScene(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_add_custom_sound")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_sceneEditor.addSoundToCustomScene(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_add_custom_light")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_sceneEditor.addLightToCustomScene(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_add_custom_lighting")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_sceneEditor.addLightingToCustomScene();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_add_custom_graphics")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_sceneEditor.addGraphicsToCustomScene();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_save_custom")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_sceneEditor.saveCustomSceneToFile();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_load_custom")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_sceneEditor.clearCurrentScene();
			_sceneEditor.loadCustomSceneFromFile(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_delete_custom")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Compose file path
			string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" :
				("projects\\" + _currentProjectID)) + "\\scenes\\custom\\");
			string filePath = (directoryPath + arguments[0].getString() + ".fe3d");

			// Check if file exists
			if (_fe3d.misc_isFileExisting(filePath))
			{
				auto status = std::remove(filePath.c_str());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
			else
			{
				_throwScriptError("cannot delete custom scene \"" + arguments[0].getString() + "\"!");
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}