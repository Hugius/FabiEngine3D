#include <filesystem>
#include <fstream>
#include <sstream>

#include "model_editor.hpp"

ModelEditor::ModelEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	_fe3d(fe3d),
	_gui(gui)
{
	// Load all OBJ filenames from assets folder
	_loadObjFileNames();
}

void ModelEditor::initialize()
{
	// Global window instance of left viewport
	_window = _gui->getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - modelManagement
	_window->addScreen("modelManagement");
	_window->getScreen("modelManagement")->addButton("addModel", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Add model", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("modelManagement")->addButton("editModel", vec2(0.0f, 0.21), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Edit model", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("modelManagement")->addButton("deleteModel", vec2(0.0f, -0.21), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Delete model", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("modelManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - modelChoice
	_window->addScreen("modelChoice");
	_window->getScreen("modelChoice")->addScrollingList("modelList", vec2(0.0f, 0.1f), vec2(1.8, 1.75f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.25f, 0.1f));
	_window->getScreen("modelChoice")->addButton("back", vec2(0.0f, -0.9f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - modelEditingMain
	_window->addScreen("modelEditingMain");
	_window->getScreen("modelEditingMain")->addButton("mesh", vec2(0.0f, 0.63f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "3D mesh", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("modelEditingMain")->addButton("options", vec2(0.0f, 0.21), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Options", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("modelEditingMain")->addButton("size", vec2(0.0f, -0.21), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Size", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("modelEditingMain")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - modelEditingMesh
	_window->addScreen("modelEditingMesh");
	_window->getScreen("modelEditingMesh")->addButton("loadOBJ", vec2(0.0f, 0.7f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Load OBJ", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("modelEditingMesh")->addButton("loadDiffuseMap", vec2(0.0f, 0.35f), vec2(1.6f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Diffusemap", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("modelEditingMesh")->addButton("loadLightMap", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Lightmap", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("modelEditingMesh")->addButton("loadReflectionMap", vec2(0.0f, -0.35f), vec2(1.6f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Reflectmap", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("modelEditingMesh")->addButton("back", vec2(0.0f, -0.7f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	
	// Left-viewport: mainWindow - modelEditingOptions
	_window->addScreen("modelEditingOptions");
	_window->getScreen("modelEditingOptions")->addScrollingList("optionsList", vec2(0.0f, 0.1f), vec2(1.8, 1.75f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));
	_window->getScreen("modelEditingOptions")->getScrollingList("optionsList")->addButton("faceculled", "Culling: OFF");
	_window->getScreen("modelEditingOptions")->getScrollingList("optionsList")->addButton("shadowed", "Shadowed : ON");
	_window->getScreen("modelEditingOptions")->getScrollingList("optionsList")->addButton("transparent", "No-white: OFF");
	_window->getScreen("modelEditingOptions")->getScrollingList("optionsList")->addButton("specular", "Specular: OFF");
	_window->getScreen("modelEditingOptions")->getScrollingList("optionsList")->addButton("setColor", "Set color");
	_window->getScreen("modelEditingOptions")->getScrollingList("optionsList")->addButton("uvRepeat", "Set UV-repeat");
	_window->getScreen("modelEditingOptions")->addButton("back", vec2(0.0f, -0.9f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - modelEditingSize
	_window->addScreen("modelEditingSize");
	_window->getScreen("modelEditingSize")->addButton("setSize", vec2(0.0f, 0.7f), vec2(1.6f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Set mesh size", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("modelEditingSize")->addButton("toggleResizeMesh", vec2(0.0f, 0.35f), vec2(1.6f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Mesh resize: OFF", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("modelEditingSize")->addButton("toggleBoxView", vec2(0.0f, 0.0f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Hitbox: ON", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("modelEditingSize")->addButton("toggleResizeBox", vec2(0.0f, -0.35f), vec2(1.6f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Box resize: OFF", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("modelEditingSize")->addButton("back", vec2(0.0f, -0.7f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
}

void ModelEditor::load()
{
	// Camera
	_fe3d.camera_load(90.0f, 0.1f, 1000.0f, vec3(_startingCameraPos), -90.0f, 0.0f);
	_fe3d.camera_enableLookat(vec3(0.0f));

	// Graphics
	_fe3d.gfx_addAmbientLighting(0.75f);
	_fe3d.gfx_addDirectionalLighting(vec3(1000.0f), 0.75f);
	_fe3d.gfx_addLightMapping();
	_fe3d.gfx_addSkyReflections(0.25f);
	_fe3d.gfx_addMSAA();
	_fe3d.gfx_addSceneReflections(0.0f, 0.25f);
	_fe3d.gfx_addShadows(vec3(50.0f, 50.0f, 0.0f), vec3(0.0f), 100.0f, 150.0);
	_fe3d.gfx_addSpecularLighting(16.0f);
	
	// 3D Environment
	_fe3d.gameEntity_add("@modelEditorGrid", "Engine\\OBJs\\plane", vec3(0.0f), vec3(0.0f), vec3(100.0f, 1.0f, 100.0f));
	_fe3d.gameEntity_setDiffuseMap("@modelEditorGrid", "Engine\\Textures\\metal");
	_fe3d.gameEntity_setUvRepeat("@modelEditorGrid", 25.0f);
	_fe3d.gameEntity_setSceneReflective("@modelEditorGrid", true);
	_fe3d.gameEntity_setSpecularLighted("@modelEditorGrid", true);
	_fe3d.gameEntity_add("@cube", "Engine\\OBJs\\cube", vec3(5.0f, 0.0f, 0.0f), vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
	_fe3d.gameEntity_setDiffuseMap("@cube", "Engine\\Textures\\cube");
	_fe3d.gameEntity_setFaceCulled("@cube", true);
	_fe3d.skyEntity_add("@modelEditorSky", 0.1f, "Engine\\Textures\\Skybox\\");
	_fe3d.skyEntity_select("@modelEditorSky");

	// Other
	_gui->getGlobalScreen()->addTextfield("currentModelName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_loaded = true;

	// Load models file
	std::ifstream file;
	file.open(_fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\models.fe3d");
	string line;

	// Read model data
	while (std::getline(file, line))
	{
		string modelName, objName, diffuseName, lightName, reflectionName;
		float width, height, depth;
		std::istringstream iss(line);

		// Extract from file
		iss >> modelName >> objName >> diffuseName >> lightName >> reflectionName >> width >> height >> depth;
		objName = (objName == "-") ? "" : objName;
		diffuseName = (diffuseName == "-") ? "" : diffuseName;
		lightName = (lightName == "-") ? "" : lightName;
		reflectionName = (reflectionName == "-") ? "" : reflectionName;

		// Add new model
		addModel(modelName, objName, diffuseName, lightName, reflectionName, vec3(width, height, depth));
	}

	// Close file
	file.close();
}

void ModelEditor::unload()
{
	// Graphics
	_fe3d.gfx_removeAmbientLighting();
	_fe3d.gfx_removeDirectionalLighting();
	_fe3d.gfx_removeLightMapping();
	_fe3d.gfx_removeSkyReflections();
	_fe3d.gfx_removeMSAA();
	_fe3d.gfx_removeSceneReflections();
	_fe3d.gfx_removeShadows();
	_fe3d.gfx_removeSpecularLighting();

	// 3D environment
	_fe3d.gameEntity_delete("@modelEditorGrid");
	_fe3d.gameEntity_delete("@cube");
	_fe3d.skyEntity_delete("@modelEditorSky");

	// Delete models
	for (auto& modelName : _modelNames)
	{
		if (_fe3d.gameEntity_isExisting(modelName))
		{
			_fe3d.gameEntity_delete(modelName);
		}
	}
	_modelNames.clear();

	// Delete model name textfield & scrolling list buttons
	_gui->getGlobalScreen()->deleteTextfield("currentModelName");
	_gui->getViewport("left")->getWindow("main")->getScreen("modelChoice")->getScrollingList("modelList")->deleteButtons();

	// Other
	_modelCreationEnabled = false;
	_modelChoosingEnabled = false;
	_modelEditingEnabled = false;
	_modelResizingEnabled = false;
	_modelRemovalEnabled = false;
	_loaded = false;
	_cameraDistance = 5.0f;
}

void ModelEditor::addModel(string modelName, string objName, string diffuseMapName, string lightMapName, string reflectionMapName, vec3 size)
{
	// If modelname not existing yet
	if (std::find(_modelNames.begin(), _modelNames.end(), modelName) == _modelNames.end())
	{
		// Add model name
		_modelNames.push_back(modelName);

		// Add 3D model
		if (objName != "")
		{
			_fe3d.gameEntity_add(modelName, objName, vec3(0.0f), vec3(0.0f), size, false);

			// Diffuse map
			if (diffuseMapName != "")
			{
				_fe3d.gameEntity_setDiffuseMap(modelName, diffuseMapName);
			}

			// Light map
			if (lightMapName != "")
			{
				_fe3d.gameEntity_setLightMap(modelName, lightMapName);
			}

			// Reflection map
			if (reflectionMapName != "")
			{
				_fe3d.gameEntity_setReflectionMap(modelName, reflectionMapName);
			}
		}

		// Add scrolling list button
		_gui->getViewport("left")->getWindow("main")->getScreen("modelChoice")->getScrollingList("modelList")->addButton(modelName, modelName);
	}
	else
	{
		_fe3d.logger_throwWarning("Modelname \"" + modelName + "\" is already in use!");
	}
}