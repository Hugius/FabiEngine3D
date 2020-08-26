#include "model_editor.hpp"
#include "left_viewport_controller.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

#define GW(text) LVC::calcTextWidth(text, 0.15f, 1.8f)

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
	_leftWindow->getScreen("modelEditorMenuMain")->addButton("addModel", vec2(0.0f, 0.63f), vec2(GW("Add model"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Add model", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMain")->addButton("editModel", vec2(0.0f, 0.21), vec2(GW("Edit model"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Edit model", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMain")->addButton("deleteModel", vec2(0.0f, -0.21), vec2(GW("Delete model"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Delete model", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - modelEditingMain
	_leftWindow->addScreen("modelEditorMenuChoice");
	_leftWindow->getScreen("modelEditorMenuChoice")->addButton("mesh", vec2(0.0f, 0.7f), vec2(GW("3D mesh"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "3D mesh", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuChoice")->addButton("options", vec2(0.0f, 0.35f), vec2(GW("Options"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Options", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuChoice")->addButton("lighting", vec2(0.0f, 0.0f), vec2(GW("Lighting"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Lighting", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuChoice")->addButton("size", vec2(0.0f, -0.35f), vec2(GW("Size"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Size", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuChoice")->addButton("back", vec2(0.0f, -0.7f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - modelEditorMenuMesh
	_leftWindow->addScreen("modelEditorMenuMesh");
	_leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadOBJ", vec2(0.0f, 0.7f), vec2(GW("Load OBJ"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Load OBJ", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadDiffuseMap", vec2(0.0f, 0.35f), vec2(GW("DiffuseMap"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "DiffuseMap", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadLightMap", vec2(0.0f, 0.0f), vec2(GW("LightMap"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "LightMap", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadReflectionMap", vec2(0.0f, -0.35f), vec2(GW("Reflectmap"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Reflectmap", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMesh")->addButton("back", vec2(0.0f, -0.7f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);
	
	// Left-viewport: mainWindow - modelEditorMenuOptions
	_leftWindow->addScreen("modelEditorMenuOptions");
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("isFaceculled", vec2(0.0f, 0.7f), vec2(GW("Culling: OFF"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Culling: OFF", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("isTransparent", vec2(0.0f, 0.35f), vec2(GW("No-white: OFF"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "No-white: OFF", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("setColor", vec2(0.0f, 0.0f), vec2(GW("Set color"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Set color", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("uvRepeat", vec2(0.0f, -0.35f), vec2(GW("Set UV-repeat"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Set UV-repeat", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("back", vec2(0.0f, -0.7f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - modelEditorMenuLighting
	_leftWindow->addScreen("modelEditorMenuLighting");
	_leftWindow->getScreen("modelEditorMenuLighting")->addButton("isSpecular", vec2(0.0f, 0.7875f), vec2(GW("Specular: OFF"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Specular: OFF", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuLighting")->addButton("specularFactor", vec2(0.0f, 0.525f), vec2(GW("Specular factor"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Specular factor", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuLighting")->addButton("specularIntensity", vec2(0.0f, 0.2625f), vec2(GW("Specular intensity"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Specular power", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuLighting")->addButton("modelLightness", vec2(0.0f, 0.0f), vec2(GW("Lightness"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Lightness", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuLighting")->addButton("isShadowed", vec2(0.0f, -0.2625f), vec2(GW("Shadowed : ON"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Shadowed : ON", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuLighting")->addButton("isReflectiveSurface", vec2(0.0f, -0.525f), vec2(GW("Reflective : ON"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Reflective : ON", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuLighting")->addButton("back", vec2(0.0f, -0.7875f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - modelEditorMenuSize
	_leftWindow->addScreen("modelEditorMenuSize");
	_leftWindow->getScreen("modelEditorMenuSize")->addButton("setSize", vec2(0.0f, 0.75f), vec2(GW("Set mesh size"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Set mesh size", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuSize")->addButton("toggleResizeMesh", vec2(0.0f, 0.45f), vec2(GW("Mesh resize: OFF"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Mesh resize: OFF", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuSize")->addButton("toggleBoxView", vec2(0.0f, 0.15f), vec2(GW("Hitbox: OFF"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Hitbox: OFF", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuSize")->addButton("toggleResizeBox", vec2(0.0f, -0.15f), vec2(GW("Box resize: OFF"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Box resize: OFF", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuSize")->addButton("resizeBoxDir", vec2(0.0f, -0.45f), vec2(GW("Direction: X"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Direction: X", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuSize")->addButton("back", vec2(0.0f, -0.75f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);
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
	_fe3d.gfx_enableSceneReflections(0.25f);
	_fe3d.gfx_enableSkyReflections(0.5f);
	_fe3d.gfx_enableLightMapping();
	_fe3d.gfx_enableSpecularLighting();
	
	// 3D Environment
	_fe3d.skyEntity_select("@@editorSky");
	_fe3d.gameEntity_add("@@cube", "Engine\\OBJs\\cube.obj", vec3(0.0f), vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
	_fe3d.gameEntity_setDiffuseMap("@@cube", "Engine\\Textures\\cube.png");
	_fe3d.gameEntity_setFaceCulled("@@cube", true);

	// Other
	loadModels();
	_gui->getGlobalScreen()->addTextfield("selectedModelName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_gui->getViewport("bottom")->getWindow("controls")->setActiveScreen("modelEditor");
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
			float uvRepeat, specularFactor, specularIntensity, lightness;
			bool isFaceCulled, isShadowed, isTransparent, isSpecular, isReflective;
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
				isFaceCulled >>
				isShadowed >>
				isTransparent >>
				isReflective >>
				isSpecular >>
				specularFactor >>
				specularIntensity >>
				lightness >>
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
			_addModel(modelName, objPath, diffuseMapPath, lightMapPath, reflectionMapPath, modelSize, isFaceCulled, isShadowed, 
				isTransparent, isReflective, isSpecular, specularFactor, specularIntensity, lightness, 
				vec3(color.r, color.g, color.b), uvRepeat, vec3(boxSize.x, boxSize.y, boxSize.z));
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
				auto isFaceCulled = _fe3d.gameEntity_isFaceCulled(modelName);
				auto isShadowed = _fe3d.gameEntity_isShadowed(modelName);
				auto isTransparent = _fe3d.gameEntity_isTransparent(modelName);
				auto isReflective = _fe3d.gameEntity_isSceneReflective(modelName);
				auto isSpecular = _fe3d.gameEntity_isSpecularLighted(modelName);
				auto specularFactor = _fe3d.gameEntity_getSpecularFactor(modelName);
				auto specularStrength = _fe3d.gameEntity_getSpecularIntensity(modelName);
				auto lightness = _fe3d.gameEntity_getLightness(modelName);
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
					isFaceCulled << " " <<
					isShadowed << " " << 
					isTransparent << " " <<
					isReflective << " " << 
					isSpecular << " " <<
					specularFactor << " " <<
					specularStrength << " " <<
					lightness << " " <<
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
	_fe3d.gfx_disableSkyReflections();
	_fe3d.gfx_disableLightMapping();
	_fe3d.gfx_disableSpecularLighting();

	// 3D environment
	_fe3d.skyEntity_select("@@defaultSky");
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
	_fe3d.skyEntity_select("@@defaultSky");

	// Other
	_modelCreationEnabled = false;
	_modelChoosingEnabled = false;
	_modelEditingEnabled = false;
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
	_gui->getViewport("bottom")->getWindow("controls")->setActiveScreen("mainMenu");
}