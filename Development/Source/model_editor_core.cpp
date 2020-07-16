#include "model_editor.hpp"
#include "left_viewport_controller.hpp"

#include <fstream>
#include <sstream>

ModelEditor::ModelEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	_fe3d(fe3d),
	_gui(gui)
{
	// Load all OBJ filenames from assets folder
	_loadObjFileNames();
}

void ModelEditor::initializeGUI()
{
	// Private window instance of left viewport
	_leftWindow = _gui->getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - modelManagement
	_leftWindow->addScreen("modelManagement");
	_leftWindow->getScreen("modelManagement")->addButton("addModel", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Add model", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelManagement")->addButton("editModel", vec2(0.0f, 0.21), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Edit model", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelManagement")->addButton("deleteModel", vec2(0.0f, -0.21), vec2(1.7f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Delete model", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - modelEditingMain
	_leftWindow->addScreen("modelEditingMain");
	_leftWindow->getScreen("modelEditingMain")->addButton("mesh", vec2(0.0f, 0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "3D mesh", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingMain")->addButton("options", vec2(0.0f, 0.21), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Options", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingMain")->addButton("size", vec2(0.0f, -0.21), vec2(0.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Size", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingMain")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - modelEditingMesh
	_leftWindow->addScreen("modelEditingMesh");
	_leftWindow->getScreen("modelEditingMesh")->addButton("loadOBJ", vec2(0.0f, 0.7f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Load OBJ", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingMesh")->addButton("loadDiffuseMap", vec2(0.0f, 0.35f), vec2(1.6f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Diffusemap", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingMesh")->addButton("loadLightMap", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Lightmap", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingMesh")->addButton("loadReflectionMap", vec2(0.0f, -0.35f), vec2(1.6f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Reflectmap", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingMesh")->addButton("back", vec2(0.0f, -0.7f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	
	// Left-viewport: mainWindow - modelEditingOptions
	_leftWindow->addScreen("modelEditingOptions");
	_leftWindow->getScreen("modelEditingOptions")->addButton("faceculled", vec2(0.0f, 0.83f), vec2(1.4f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Culling: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingOptions")->addButton("shadowed", vec2(0.0f, 0.59f), vec2(1.6f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Shadowed : ON", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingOptions")->addButton("transparent", vec2(0.0f, 0.36f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "No-white: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingOptions")->addButton("specular", vec2(0.0f, 0.13f), vec2(1.7f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Specular: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingOptions")->addButton("intensity", vec2(0.0f, -0.1f), vec2(1.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Specular intensity", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingOptions")->addButton("setColor", vec2(0.0f, -0.33f), vec2(1.6f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Set color", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingOptions")->addButton("uvRepeat", vec2(0.0f, -0.56f), vec2(1.6f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Set UV-repeat", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingOptions")->addButton("back", vec2(0.0f, -0.79f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - modelEditingSize
	_leftWindow->addScreen("modelEditingSize");
	_leftWindow->getScreen("modelEditingSize")->addButton("setSize", vec2(0.0f, 0.75f), vec2(1.6f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Set mesh size", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingSize")->addButton("toggleResizeMesh", vec2(0.0f, 0.45f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Mesh resize: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingSize")->addButton("toggleBoxView", vec2(0.0f, 0.15f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Hitbox: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingSize")->addButton("toggleResizeBox", vec2(0.0f, -0.15f), vec2(1.7f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Box resize: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingSize")->addButton("resizeBoxDir", vec2(0.0f, -0.45f), vec2(1.6f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Direction: X", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelEditingSize")->addButton("back", vec2(0.0f, -0.75f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);
}

void ModelEditor::load()
{
	// Camera
	_fe3d.camera_setPosition(_defaultCameraPosition);
	_fe3d.camera_enableLookat(vec3(0.0f));

	// Graphics
	_fe3d.gfx_enableAmbientLighting(vec3(1.0f), 0.75f);
	_fe3d.gfx_enableDirectionalLighting(vec3(1000.0f), vec3(1.0f), 0.5f);
	_fe3d.gfx_enableLightMapping();
	_fe3d.gfx_enableSkyReflections(0.25f);
	_fe3d.gfx_enableMSAA();
	_fe3d.gfx_enableSceneReflections(0.0f, 0.25f);
	_fe3d.gfx_enableShadows(vec3(50.0f, 50.0f, 0.0f), vec3(0.0f), 100.0f, 150.0);
	_fe3d.gfx_enableSpecularLighting(3.0f);
	
	// 3D Environment
	_fe3d.gameEntity_add("@@grid", "Engine\\OBJs\\plane.obj", vec3(0.0f), vec3(0.0f), vec3(100.0f, 1.0f, 100.0f));
	_fe3d.gameEntity_setDiffuseMap("@@grid", "Engine\\Textures\\marble.png");
	_fe3d.gameEntity_setUvRepeat("@@grid", 25.0f);
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

	_modelNames.clear();

	string modelsPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\models.fe3d";

	// Load models file
	if (_fe3d.misc_isFileExisting(modelsPath)) // Check if models file exists
	{
		std::ifstream file(modelsPath);
		string line;

		// Read model data
		while (std::getline(file, line))
		{
			// Placeholder variables
			string modelName, objName, diffuseName, lightName, reflectionName;
			float width, height, depth, uvRepeat, specularIntensity;
			bool faceCulled, shadowed, transparent, specular;
			vec3 color, boxSize;

			// For item extraction
			std::istringstream iss(line);

			// Extract from file
			iss >> modelName >> objName >> diffuseName >> lightName >> reflectionName
				>> width >> height >> depth >> faceCulled >> shadowed >> transparent >> specular >> specularIntensity
				>> color.r >> color.g >> color.b >> uvRepeat >> boxSize.x >> boxSize.y >> boxSize.z;

			// Run checks on string values
			objName = (objName == "-") ? "" : objName;
			diffuseName = (diffuseName == "-") ? "" : diffuseName;
			lightName = (lightName == "-") ? "" : lightName;
			reflectionName = (reflectionName == "-") ? "" : reflectionName;

			// Add new model
			_addModel(modelName, objName, diffuseName, lightName, reflectionName, vec3(width, height, depth),
				faceCulled, shadowed, transparent, specular, specularIntensity, vec3(color.r, color.g, color.b), uvRepeat, vec3(boxSize.x, boxSize.y, boxSize.z));
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Models from project \"" + _currentProjectName + "\" loaded!");
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
		file.open(_fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\models.fe3d");

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
				auto specularIntensity = _fe3d.gameEntity_getSpecularIntensity(modelName);
				auto color = _fe3d.gameEntity_getColor(modelName);
				auto uvRepeat = _fe3d.gameEntity_getUvRepeat(modelName);
				auto boxSize = _fe3d.aabbEntity_getSize(modelName);

				// String value corrections
				diffuseMapPath = (diffuseMapPath == "") ? "-" : diffuseMapPath;
				lightMapPath = (lightMapPath == "") ? "-" : lightMapPath;
				reflectionMapPath = (reflectionMapPath == "") ? "-" : reflectionMapPath;

				// 1 model -> 1 line in file
				file << modelName << " " <<
					objPath << " " << diffuseMapPath << " " << lightMapPath << " " << reflectionMapPath << " " <<
					modelSize.x << " " << modelSize.y << " " << modelSize.z << " " <<
					faceCulled << " " << shadowed << " " << transparent << " " << specular << " " << specularIntensity << " " <<
					color.r << " " << color.g << " " << color.b << " " << uvRepeat << " " <<
					boxSize.x << " " << boxSize.y << " " << boxSize.z << "\n";
			}
			else
			{
				file << modelName << " - - - - 0.0 0.0 0.0 0 0 0 0 0.0 0.0 0.0 0.0 0 0.0 0.0 0.0\n";
			}
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Model editor data from project \"" + _currentProjectName + "\" saved!");
	}
}

void ModelEditor::unload()
{
	// Graphics
	_fe3d.gfx_disableAmbientLighting();
	_fe3d.gfx_disableDirectionalLighting();
	_fe3d.gfx_disableLightMapping();
	_fe3d.gfx_disableSkyReflections();
	_fe3d.gfx_disableMSAA();
	_fe3d.gfx_disableSceneReflections();
	_fe3d.gfx_disableShadows();
	_fe3d.gfx_disableSpecularLighting();

	// 3D environment
	_fe3d.gameEntity_delete("@@grid");
	_fe3d.gameEntity_delete("@@cube");

	// Delete models
	_fe3d.gameEntity_deleteAll();
	_modelNames.clear();

	// Delete model name textfield
	_gui->getGlobalScreen()->deleteTextfield("selectedModelName");

	// Camera
	_fe3d.camera_setPosition(vec3(0.0f));
	_fe3d.camera_setYaw(0.0f);
	_fe3d.camera_setPitch(0.0f);
	_fe3d.camera_disableLookat();

	// Enable default sky
	_fe3d.skyEntity_select("@defaultSky");

	// Other
	_modelCreationEnabled = false;
	_modelChoosingEnabled = false;
	_modelEditingEnabled = false;
	_modelResizingEnabled = false;
	_modelColorPicking = false;
	_meshResizingToggled = false;
	_boxResizingToggled = false;
	_settingModelUvRepeat = false;
	_modelRemovalEnabled = false;
	_aabbRenderingEnabled = false;
	_isLoaded = false;
	_cameraDistance = 5.0f;
	_modelResizeDirection = Direction::X;
	_currentModelName = "";
	_totalCursorDifference = vec2(0.0f);
	_cameraAcceleration = vec2(0.0f);
	_lastCursorPos = vec2(0.0f);
}