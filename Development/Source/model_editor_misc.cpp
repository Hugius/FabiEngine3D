#include <filesystem>

#include "model_editor.hpp"

ModelEditor::ModelEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	_fe3d(fe3d),
	_gui(gui)
{
	// Pre-load environment
	_loadEnvironment();
	_unloadEnvironment();

	// Load all OBJ filenames from assets folder
	_loadObjFileNames();

	// Current model name textfield
	_gui->getGlobalScreen()->addTextfield("currentModelName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_modelNameTextfieldEntityID = _gui->getGlobalScreen()->getTextfield("currentModelName")->getEntityID();
}

void ModelEditor::_loadEnvironment()
{
	_fe3d.camera_load(90.0f, 0.1f, 1000.0f, vec3(_startingCameraPos), -90.0f, 0.0f);
	_fe3d.camera_enableLookat(vec3(0.0f));
	_fe3d.gfx_addAmbientLighting(0.25f);
	_fe3d.gfx_addDirectionalLighting(vec3(1000.0f), 0.5f);
	_fe3d.gfx_addLightMapping();
	_fe3d.gfx_addSkyReflections(0.25f);
	_fe3d.gfx_addBloom(1.0f, 0.0f, 10);
	_fe3d.gfx_setSkyBrightness(0.75f);
	_fe3d.gameEntity_add("modelEditorGrid", "Engine\\OBJs\\plane", vec3(0.0f), vec3(0.0f), vec3(100.0f, 1.0f, 100.0f));
	_fe3d.gameEntity_setDiffuseMap("modelEditorGrid", "Engine\\Textures\\grass");
	_fe3d.gameEntity_setUvRepeat("modelEditorGrid", 10.0f);
	_fe3d.skyEntity_add("modelEditorSky", 0.1f, "Engine\\Textures\\Skybox\\");
	_fe3d.skyEntity_select("modelEditorSky");
}

void ModelEditor::_unloadEnvironment()
{
	_fe3d.gfx_removeAmbientLighting();
	_fe3d.gfx_removeDirectionalLighting();
	_fe3d.gfx_removeLightMapping();
	_fe3d.gfx_removeSkyReflections();
	_fe3d.gfx_removeBloom();
	_fe3d.gameEntity_delete("modelEditorGrid");
	_fe3d.skyEntity_delete("modelEditorSky");
}

void ModelEditor::_loadObjFileNames()
{
	// Remove potential previous filenames
	if (!_totalObjFileNames.empty())
	{
		_totalObjFileNames.clear();
	}

	// Get new path
	string path = _fe3d.misc_getRootDirectory() + "User\\Assets\\OBJs\\";
	int endOfNameIndex = 0;

	// Get all filenames
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		string path = string(entry.path().u8string());
		path.erase(0, 13);

		// Loop over file path
		for (unsigned int i = 0; i < path.size(); i++)
		{
			// End of file name
			if (path[i] == '.')
			{
				endOfNameIndex = i;
			}
		}
		_totalObjFileNames.push_back(path.substr(0, endOfNameIndex));
	}
}

vector<string>& ModelEditor::getTotalObjFileNames()
{
	return _totalObjFileNames;
}