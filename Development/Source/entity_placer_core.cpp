#include "entity_placer.hpp"

#include <fstream>
#include <sstream>

EntityPlacer::EntityPlacer(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui, ModelEditor& modelEditor, WorldEditor& worldEditor) :
	_fe3d(fe3d),
	_gui(gui),
	_modelEditor(modelEditor),
	_worldEditor(worldEditor)
{

}

void EntityPlacer::initializeGUI()
{
	// Private window instance of GUI windows
	_leftWindow = _gui->getViewport("left")->getWindow("main");
	_rightWindow = _gui->getViewport("right")->getWindow("main");

	// Left-viewport: mainWindow - placeManagement
	_leftWindow->addScreen("placeManagement");
	_leftWindow->getScreen("placeManagement")->addButton("placeModel", vec2(0.0f, 0.7f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Place model", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_leftWindow->getScreen("placeManagement")->addButton("placeBillboard", vec2(0.0f, 0.35f), vec2(1.7f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Place billboard", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_leftWindow->getScreen("placeManagement")->addButton("placeLight", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Place light", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_leftWindow->getScreen("placeManagement")->addButton("setSpeed", vec2(0.0f, -0.35f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Set speed", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_leftWindow->getScreen("placeManagement")->addButton("back", vec2(0.0f, -0.7f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	
	// Left-viewport: mainWindow - modelPlaceManagement
	_leftWindow->addScreen("modelPlaceManagement");
	_leftWindow->getScreen("modelPlaceManagement")->addScrollingList("modelList", vec2(0.0f, 0.1f), vec2(1.8, 1.75f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen("modelPlaceManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - billboardPlaceManagement
	_leftWindow->addScreen("billboardPlaceManagement");
	_leftWindow->getScreen("billboardPlaceManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - lightPlaceManagement
	_leftWindow->addScreen("lightPlaceManagement");
	_leftWindow->getScreen("lightPlaceManagement")->addButton("ambient", vec2(0.0f, 0.63f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Ambient", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_leftWindow->getScreen("lightPlaceManagement")->addButton("directional", vec2(0.0f, 0.21f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Directional", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_leftWindow->getScreen("lightPlaceManagement")->addButton("point", vec2(0.0f, -0.21f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Point", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_leftWindow->getScreen("lightPlaceManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Right-viewport: mainWindow - modelProperties
	_rightWindow->addScreen("modelProperties");
	_rightWindow->getScreen("modelProperties")->addTextfield("transformation", vec2(0.0f, 0.85f), vec2(1.75f, 0.1f), "Transformation", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addButton("translation", vec2(0.0f, 0.7f), vec2(0.75f, 0.2f), "translation.png", vec3(0.0f));
	_rightWindow->getScreen("modelProperties")->addButton("rotation", vec2(0.0f, 0.45f), vec2(0.75f, 0.2f), "rotation.png", vec3(0.0f));
	_rightWindow->getScreen("modelProperties")->addButton("scaling", vec2(0.0f, 0.2f), vec2(0.75f, 0.2f), "scaling.png", vec3(0.0f));
	_rightWindow->getScreen("modelProperties")->addTextfield("x", vec2(0.0f, -0.15f), vec2(0.25f, 0.1f), "X", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addTextfield("y", vec2(0.0f, -0.4f), vec2(0.25f, 0.1f), "Y", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addTextfield("z", vec2(0.0f, -0.65f), vec2(0.25f, 0.1f), "Z", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addButton("xPlus", vec2(0.75f, -0.25f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addButton("yPlus", vec2(0.75f, -0.5f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addButton("zPlus", vec2(0.75f, -0.75f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addButton("xMinus", vec2(-0.75f, -0.25f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addButton("yMinus", vec2(-0.75f, -0.5f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addButton("zMinus", vec2(-0.75f, -0.75f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addWriteField("x", vec2(0.0f, -0.25f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1);
	_rightWindow->getScreen("modelProperties")->addWriteField("y", vec2(0.0f, -0.5f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1);
	_rightWindow->getScreen("modelProperties")->addWriteField("z", vec2(0.0f, -0.75f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1);
}

void EntityPlacer::load()
{
	// Enable graphics
	_fe3d.gfx_enableAmbientLighting(0.75f);
	_fe3d.gfx_enableDirectionalLighting(vec3(1000.0f), 0.75f);
	_fe3d.gfx_enableLightMapping();
	_fe3d.gfx_enableSkyReflections(0.25f);
	_fe3d.gfx_enableMSAA();
	_fe3d.gfx_enableWaterEffects();
	//_fe3d.gfx_enableShadows(vec3(50.0f, 50.0f, 0.0f), vec3(0.0f), 100.0f, 150.0);
	_fe3d.gfx_enableSpecularLighting();

	// Disable default skybox
	_fe3d.skyEntity_select("");

	// Load world entities
	_worldEditor.loadSkyEntity();
	_worldEditor.loadTerrainEntity();
	_worldEditor.loadWaterEntity();

	// Show sky entity
	if (_fe3d.skyEntity_isExisting("@sky"))
	{
		_fe3d.skyEntity_show("@sky");
	}

	// Show terrain entity
	if (_fe3d.terrainEntity_isExisting("@terrain"))
	{
		_fe3d.terrainEntity_show("@terrain");
	}

	// Show water entity
	if (_fe3d.waterEntity_isExisting("@water"))
	{
		_fe3d.waterEntity_show("@water");
	}

	// Camera properties
	float height = 0.0f;

	// Set camera height relative to water size
	if (_fe3d.waterEntity_isExisting("@water"))
	{
		float size = _fe3d.waterEntity_getSize("@water") / 2.0f;
		height = _fe3d.waterEntity_getSurfaceHeight("@water") + (size / 10.0f);
	}

	// Terrain can overwrite camera height
	if (_fe3d.terrainEntity_isExisting("@terrain"))
	{
		height = _fe3d.terrainEntity_getMaxHeight("@terrain");
	}

	// Load camera
	_fe3d.camera_setPosition(vec3(0.0f, height, 0.0f));

	// Model loading
	_modelEditor.loadModels();
	for (auto& modelName : _modelEditor.getModelNames())
	{
		// Check if there is a game entity present
		if (_fe3d.gameEntity_isExisting(modelName))
		{
			_leftWindow->getScreen("modelPlaceManagement")->getScrollingList("modelList")->addButton(modelName, modelName.substr(1, modelName.size()));
			_counterMap.insert(std::make_pair(modelName, 0));
		}
	}

	// Create name textfields
	_gui->getGlobalScreen()->addTextfield("selectedModelName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));

	// Other
	loadWorld();
	_isLoaded = true;
}

void EntityPlacer::loadWorld()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	string modelsPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\world.fe3d";

	// Load models file
	if (_fe3d.misc_isFileExisting(modelsPath)) // Check if models file exists
	{
		std::ifstream file(modelsPath);
		string line;

		// Read model data
		while (std::getline(file, line))
		{
			// Placeholder variables
			string entityType;

			// For item extraction
			std::istringstream iss(line);

			// Extract type from file
			iss >> entityType;

			// Load entity according to type
			if (entityType == "MODEL")
			{
				string modelID;
				vec3 position, rotation, size;

				// Load model data
				iss >> modelID >> position.x >> position.y >> position.z >> rotation.x >> rotation.y >> rotation.z >> size.x >> size.y >> size.z;

				// Extract the model name from the model ID
				string modelName = "";
				for (auto& name : _modelEditor.getModelNames())
				{
					if (modelID.substr(0, name.size() - 1) == name.substr(1, name.size()))
					{
						modelName = name;
					}
				}

				// Add the model
				_placeModel(modelID, modelName, position, rotation, size);

				// Update the counter map
				_counterMap[modelName]++;
			}
			else if (entityType == "BILLBOARD")
			{

			}
			else if (entityType == "LIGHT")
			{

			}
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Models from project \"" + _currentProjectName + "\" loaded!");
	}
}

void EntityPlacer::save()
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
		file.open(_fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\world.fe3d");

		// Write game entities data into file
		for (auto& entityID : _fe3d.gameEntity_getAllIDs())
		{
			// Check if not preview model
			if (entityID[0] != '@')
			{
				// Transformation data
				vec3 pos = _fe3d.gameEntity_getPosition(entityID);
				vec3 rot = _fe3d.gameEntity_getRotation(entityID);
				vec3 size = _fe3d.gameEntity_getSize(entityID);

				// 1 model -> 1 line in file
				file << "MODEL " << entityID << " " << pos.x << " " << pos.y << " " << pos.z << " " << 
					rot.x << " " << rot.y << " " << rot.z << " " << size.x << " " << size.y << " " << size.z << "\n";
			}
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Entity placer data from project \"" + _currentProjectName + "\" saved!");
	}
}

void EntityPlacer::unload()
{
	// Disable graphics
	_fe3d.gfx_disableAmbientLighting();
	_fe3d.gfx_disableDirectionalLighting();
	_fe3d.gfx_disableLightMapping();
	_fe3d.gfx_disableSkyReflections();
	_fe3d.gfx_disableMSAA();
	_fe3d.gfx_disableWaterEffects();
	_fe3d.gfx_disableShadows();
	_fe3d.gfx_disableSpecularLighting();

	// Delete world entities
	if (_fe3d.skyEntity_isExisting("@sky"))
	{
		_fe3d.skyEntity_delete("@sky");
	}

	// Show terrain entity
	if (_fe3d.terrainEntity_isExisting("@terrain"))
	{
		_fe3d.terrainEntity_delete("@terrain");
	}

	// Show water entity
	if (_fe3d.waterEntity_isExisting("@water"))
	{
		_fe3d.waterEntity_delete("@water");
	}

	// Delete placed entities
	_fe3d.gameEntity_deleteAll();
	_fe3d.billboardEntity_deleteAll();

	// Reset variables
	_counterMap.clear();
	_currentModelName = "";
	_cameraMovementSpeed = 10.0f;

	// Delete name textfields
	_gui->getGlobalScreen()->deleteTextfield("selectedModelName");

	// Enable default skybox
	_fe3d.skyEntity_select("@defaultSky");

	// Camera
	_fe3d.camera_setPosition(vec3(0.0f));
	_fe3d.camera_setYaw(0.0f);
	_fe3d.camera_setPitch(0.0f);
	_fe3d.camera_disableFirstPersonView();

	// Other
	_leftWindow->getScreen("modelPlaceManagement")->getScrollingList("modelList")->deleteButtons();
	_fe3d.collision_disableFrameRendering();
	_isLoaded = false;
}

void EntityPlacer::_placeModel(string modelID, string modelName, vec3 position, vec3 rotation, vec3 size)
{
	// Add game entity
	_fe3d.gameEntity_add(modelID, _fe3d.gameEntity_getObjPath(modelName), position, rotation, size);

	// Model properties
	_fe3d.gameEntity_setFaceCulled(modelID, _fe3d.gameEntity_isFaceCulled(modelName));
	_fe3d.gameEntity_setShadowed(modelID, _fe3d.gameEntity_isShadowed(modelName));
	_fe3d.gameEntity_setTransparent(modelID, _fe3d.gameEntity_isTransparent(modelName));
	_fe3d.gameEntity_setSpecularLighted(modelID, _fe3d.gameEntity_isSpecularLighted(modelName));
	_fe3d.gameEntity_setLightness(modelID, _fe3d.gameEntity_getLightness(modelName));
	_fe3d.gameEntity_setUvRepeat(modelID, _fe3d.gameEntity_getUvRepeat(modelName));
	_fe3d.gameEntity_setColor(modelID, _fe3d.gameEntity_getColor(modelName));
	_fe3d.aabbEntity_bindToGameEntity(modelID, _fe3d.aabbEntity_getSize(modelName), true);

	// Diffuse map
	if (_fe3d.gameEntity_getDiffuseMapPath(modelName) != "")
	{
		_fe3d.gameEntity_setDiffuseMap(modelID, _fe3d.gameEntity_getDiffuseMapPath(modelName));
	}

	// Light map
	if (_fe3d.gameEntity_getLightMapPath(modelName) != "")
	{
		_fe3d.gameEntity_setLightMap(modelID, _fe3d.gameEntity_getLightMapPath(modelName));
		_fe3d.gameEntity_setLightmapped(modelID, true);
	}

	// Reflection map
	if (_fe3d.gameEntity_getReflectionMapPath(modelName) != "")
	{
		_fe3d.gameEntity_setReflectionMap(modelID, _fe3d.gameEntity_getReflectionMapPath(modelName));
		_fe3d.gameEntity_setSkyReflective(modelID, true);
	}
}