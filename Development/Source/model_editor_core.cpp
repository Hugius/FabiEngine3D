#include "model_editor.hpp"
#include "left_viewport_controller.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

ModelEditor::ModelEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void ModelEditor::initializeGUI()
{
	// Private window instance of left viewport
	_leftWindow = _gui->getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - modelManagement
	_leftWindow->addScreen("modelEditorMenuMain");
	_leftWindow->getScreen("modelEditorMenuMain")->addButton("addModel", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Add model", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMain")->addButton("editModel", vec2(0.0f, 0.21), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Edit model", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMain")->addButton("deleteModel", vec2(0.0f, -0.21), vec2(1.7f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Delete model", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - modelEditingMain
	_leftWindow->addScreen("modelEditorMenuChoice");
	_leftWindow->getScreen("modelEditorMenuChoice")->addButton("mesh", vec2(0.0f, 0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "3D mesh", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuChoice")->addButton("options", vec2(0.0f, 0.21), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Options", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuChoice")->addButton("size", vec2(0.0f, -0.21), vec2(0.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Size", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuChoice")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - modelEditingMesh
	_leftWindow->addScreen("modelEditorMenuMesh");
	_leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadOBJ", vec2(0.0f, 0.7f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Load OBJ", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadDiffuseMap", vec2(0.0f, 0.35f), vec2(1.6f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "DiffuseMap", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadLightMap", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "LightMap", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadReflectionMap", vec2(0.0f, -0.35f), vec2(1.6f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Reflectmap", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMesh")->addButton("back", vec2(0.0f, -0.7f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	
	// Left-viewport: mainWindow - modelEditingOptions
	_leftWindow->addScreen("modelEditorMenuOptions");
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("isFaceculled", vec2(0.0f, 0.83f), vec2(1.4f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Culling: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("isShadowed", vec2(0.0f, 0.59f), vec2(1.6f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Shadowed : ON", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("isTransparent", vec2(0.0f, 0.36f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "No-white: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("isSpecular", vec2(0.0f, 0.13f), vec2(1.7f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Specular: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("specularFactor", vec2(0.0f, -0.1f), vec2(1.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Specular factor", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("setColor", vec2(0.0f, -0.33f), vec2(1.6f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Set color", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("uvRepeat", vec2(0.0f, -0.56f), vec2(1.6f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Set UV-repeat", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("back", vec2(0.0f, -0.79f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - modelEditingSize
	_leftWindow->addScreen("modelEditorMenuSize");
	_leftWindow->getScreen("modelEditorMenuSize")->addButton("setSize", vec2(0.0f, 0.75f), vec2(1.6f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Set mesh size", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuSize")->addButton("toggleResizeMesh", vec2(0.0f, 0.45f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Mesh resize: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuSize")->addButton("toggleBoxView", vec2(0.0f, 0.15f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Hitbox: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuSize")->addButton("toggleResizeBox", vec2(0.0f, -0.15f), vec2(1.7f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Box resize: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuSize")->addButton("resizeBoxDir", vec2(0.0f, -0.45f), vec2(1.6f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Direction: X", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuSize")->addButton("back", vec2(0.0f, -0.75f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);
}

void ModelEditor::load()
{
	// Load all OBJ filenames from assets folder
	_loadObjFileNames();

	// Camera
	_fe3d.camera_setPosition(_defaultCameraPosition);
	_fe3d.camera_enableLookat(vec3(0.0f));

	// Enable graphics
	_fe3d.gfx_enableAmbientLighting(vec3(1.0f), 0.75f);
	_fe3d.gfx_enableDirectionalLighting(vec3(1000.0f), vec3(1.0f), 0.5f);
	_fe3d.gfx_enableShadows(vec3(100.0f, 75.0f, 0.0f), vec3(0.0f), 200.0f, 200.0f);
	_fe3d.gfx_enableSceneReflections(0.0f, 0.25f);
	
	// 3D Environment
	_fe3d.gameEntity_add("@@grid", "Engine\\OBJs\\plane.obj", vec3(0.0f), vec3(0.0f), vec3(100.0f, 1.0f, 100.0f));
	_fe3d.gameEntity_setDiffuseMap("@@grid", "Engine\\Textures\\marble.png");
	_fe3d.gameEntity_setUvRepeat("@@grid", 25.0f);
	_fe3d.gameEntity_setLightness("@@grid", 0.95f);
	_fe3d.gameEntity_setSceneReflective("@@grid", true);
	_fe3d.gameEntity_add("@@cube", "Engine\\OBJs\\cube.obj", vec3(5.0f, 0.0f, 0.0f), vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
	_fe3d.gameEntity_setDiffuseMap("@@cube", "Engine\\Textures\\cube.png");
	_fe3d.gameEntity_setFaceCulled("@@cube", true);

	// Other
	loadModels();
	_gui->getGlobalScreen()->addTextfield("selectedModelName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_isLoaded = true;
}

void ModelEditor::loadModels()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}
	
	// Clear modelnames list from previous loads
	_modelNames.clear();

	// Compose full models folder path
	string filePath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\Data\\models.fe3d";

	// Load models file
	if (_fe3d.misc_isFileExisting(filePath)) // Check if models file exists
	{
		std::ifstream file(filePath);
		string line;

		// Read model data
		while (std::getline(file, line))
		{
			// Placeholder variables
			string modelName, objPath, diffuseMapPath, lightMapPath, reflectionMapPath;
			float uvRepeat, specularFactor;
			bool faceCulled, shadowed, transparent, specular;
			vec3 modelSize, color, boxSize;

			// For item extraction
			std::istringstream iss(line);

			// Extract from file
			iss >> 
				modelName >>
				objPath >>
				diffuseMapPath >>
				lightMapPath >>
				reflectionMapPath >>
				modelSize.x >>
				modelSize.y >>
				modelSize.z >>
				faceCulled >>
				shadowed >>
				transparent >>
				specular >>
				specularFactor >>
				color.r >> 
				color.g >> 
				color.b >>
				uvRepeat >>
				boxSize.x >> 
				boxSize.y >> 
				boxSize.z;

			// Perform empty string & space conversions
			objPath = (objPath == "?") ? "" : objPath;
			diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
			lightMapPath = (lightMapPath == "?") ? "" : lightMapPath;
			reflectionMapPath = (reflectionMapPath == "?") ? "" : reflectionMapPath;
			std::replace(objPath.begin(), objPath.end(), '?', ' ');
			std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
			std::replace(lightMapPath.begin(), lightMapPath.end(), '?', ' ');
			std::replace(reflectionMapPath.begin(), reflectionMapPath.end(), '?', ' ');

			// Add new model
			_addModel(modelName, objPath, diffuseMapPath, lightMapPath, reflectionMapPath, modelSize, faceCulled, shadowed, transparent,
				specular, specularFactor, vec3(color.r, color.g, color.b), uvRepeat, vec3(boxSize.x, boxSize.y, boxSize.z));
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Model data from project \"" + _currentProjectName + "\" loaded!");
	}
}

void ModelEditor::save()
{
	if (_isLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		// Create or overwrite models file
		std::ofstream file;
		file.open(_fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\Data\\models.fe3d");

		// Write model data into file
		for (auto& modelName : _modelNames)
		{
			// Check if a 3D entity for this model is existing
			if (_fe3d.gameEntity_isExisting(modelName))
			{
				auto objPath = _fe3d.gameEntity_getObjPath(modelName);
				auto diffuseMapPath = _fe3d.gameEntity_getDiffuseMapPath(modelName);
				auto lightMapPath = _fe3d.gameEntity_getLightMapPath(modelName);
				auto reflectionMapPath = _fe3d.gameEntity_getReflectionMapPath(modelName);
				auto modelSize = _fe3d.gameEntity_getSize(modelName);
				auto faceCulled = _fe3d.gameEntity_isFaceCulled(modelName);
				auto shadowed = _fe3d.gameEntity_isShadowed(modelName);
				auto transparent = _fe3d.gameEntity_isTransparent(modelName);
				auto specular = _fe3d.gameEntity_isSpecularLighted(modelName);
				auto specularFactor = _fe3d.gameEntity_getSpecularFactor(modelName);
				auto color = _fe3d.gameEntity_getColor(modelName);
				auto uvRepeat = _fe3d.gameEntity_getUvRepeat(modelName);
				auto boxSize = _fe3d.aabbEntity_getSize(modelName);

				// Perform empty string & space conversions
				objPath = (objPath == "") ? "?" : objPath;
				diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
				lightMapPath = (lightMapPath == "") ? "?" : lightMapPath;
				reflectionMapPath = (reflectionMapPath == "") ? "?" : reflectionMapPath;
				std::replace(objPath.begin(), objPath.end(), ' ', '?');
				std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
				std::replace(lightMapPath.begin(), lightMapPath.end(), ' ', '?');
				std::replace(reflectionMapPath.begin(), reflectionMapPath.end(), ' ', '?');

				// 1 model -> 1 line in file
				file << 
					modelName << " " <<
					objPath << " " <<
					diffuseMapPath << " " <<
					lightMapPath << " " <<
					reflectionMapPath << " " <<
					modelSize.x << " " <<
					modelSize.y << " " <<
					modelSize.z << " " <<
					faceCulled << " " <<
					shadowed << " " << 
					transparent << " " <<
					specular << " " <<
					specularFactor << " " <<
					color.r << " " <<
					color.g << " " <<
					color.b << " " <<
					uvRepeat << " " <<
					boxSize.x << " " <<
					boxSize.y << " " <<
					boxSize.z << std::endl;
			}
			else
			{
				file << modelName << " ? ? ? ? 0.0 0.0 0.0 0 0 0 0 0.0 0.0 0.0 0.0 0 0.0 0.0 0.0\n";
			}
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Model data from project \"" + _currentProjectName + "\" saved!");
	}
}

void ModelEditor::unload()
{
	// Disable graphics
	_fe3d.gfx_disableAmbientLighting();
	_fe3d.gfx_disableDirectionalLighting();
	_fe3d.gfx_disableShadows();
	_fe3d.gfx_disableSceneReflections();

	// 3D environment
	_fe3d.gameEntity_delete("@@grid");
	_fe3d.gameEntity_delete("@@cube");

	// Delete models
	_fe3d.gameEntity_deleteAll();

	// Delete model name textfield
	_gui->getGlobalScreen()->deleteTextfield("selectedModelName");

	// Camera
	_fe3d.camera_setPosition(vec3(0.0f));
	_fe3d.camera_setYaw(0.0f);
	_fe3d.camera_setPitch(0.0f);
	_fe3d.camera_disableLookat();

	// Enable default sky
	_fe3d.skyEntity_select("@@sky");

	// Other
	_modelCreationEnabled = false;
	_modelChoosingEnabled = false;
	_modelEditingEnabled = false;
	_modelResizingEnabled = false;
	_meshResizingToggled = false;
	_boxResizingToggled = false;
	_modelRemovalEnabled = false;
	_aabbRenderingEnabled = false;
	_isLoaded = false;
	_totalCursorDifference = vec2(0.0f);
	_cameraAcceleration = vec2(0.0f);
	_lastCursorPos = vec2(0.0f);
	_modelResizeDirection = Direction::X;
	_cameraDistance = 5.0f;
	_currentModelName = "";
	_modelNames.clear();
	_objFileNamesList.clear();
}