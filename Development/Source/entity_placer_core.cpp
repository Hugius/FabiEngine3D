#include "entity_placer.hpp"

#include <fstream>

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
	_leftWindow->getScreen("lightPlaceManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Right-viewport: mainWindow - entityProperties
	_rightWindow->addScreen("entityProperties");
	_rightWindow->getScreen("entityProperties")->addTextfield("transformation", vec2(0.0f, 0.85f), vec2(1.75f, 0.1f), "Transformation", vec3(1.0f));
	_rightWindow->getScreen("entityProperties")->addButton("translation", vec2(0.0f, 0.7f), vec2(0.75f, 0.2f), "translation.png", vec3(0.0f));
	_rightWindow->getScreen("entityProperties")->addButton("rotation", vec2(0.0f, 0.45f), vec2(0.75f, 0.2f), "rotation.png", vec3(0.0f));
	_rightWindow->getScreen("entityProperties")->addButton("scaling", vec2(0.0f, 0.2f), vec2(0.75f, 0.2f), "scaling.png", vec3(0.0f));
	_rightWindow->getScreen("entityProperties")->addTextfield("x", vec2(0.0f, -0.15f), vec2(0.25f, 0.1f), "X", vec3(1.0f));
	_rightWindow->getScreen("entityProperties")->addTextfield("y", vec2(0.0f, -0.4f), vec2(0.25f, 0.1f), "Y", vec3(1.0f));
	_rightWindow->getScreen("entityProperties")->addTextfield("z", vec2(0.0f, -0.65f), vec2(0.25f, 0.1f), "Z", vec3(1.0f));
	_rightWindow->getScreen("entityProperties")->addButton("xPlus", vec2(0.75f, -0.25f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("entityProperties")->addButton("yPlus", vec2(0.75f, -0.5f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("entityProperties")->addButton("zPlus", vec2(0.75f, -0.75f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("entityProperties")->addButton("xMinus", vec2(-0.75f, -0.25f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("entityProperties")->addButton("yMinus", vec2(-0.75f, -0.5f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("entityProperties")->addButton("zMinus", vec2(-0.75f, -0.75f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("entityProperties")->addWriteField("x", vec2(0.0f, -0.25f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1);
	_rightWindow->getScreen("entityProperties")->addWriteField("y", vec2(0.0f, -0.5f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1);
	_rightWindow->getScreen("entityProperties")->addWriteField("z", vec2(0.0f, -0.75f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1);
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
	_isLoaded = true;
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
				// Check if 3D entity exists
				if (_fe3d.gameEntity_isExisting(entityID))
				{
					//auto objPath = _fe3d.gameEntity_getObjPath(modelName);
					//auto diffuseMapPath = _fe3d.gameEntity_getDiffuseMapPath(modelName);
					//diffuseMapPath = (diffuseMapPath == "") ? "-" : diffuseMapPath;
					//auto lightMapPath = _fe3d.gameEntity_getLightMapPath(modelName);
					//lightMapPath = (lightMapPath == "") ? "-" : lightMapPath;
					//auto reflectionMapPath = _fe3d.gameEntity_getReflectionMapPath(modelName);
					//reflectionMapPath = (reflectionMapPath == "") ? "-" : reflectionMapPath;
					//auto modelSizeX = std::to_string(_fe3d.gameEntity_getSize(modelName).x);
					//auto modelSizeY = std::to_string(_fe3d.gameEntity_getSize(modelName).y);
					//auto modelSizeZ = std::to_string(_fe3d.gameEntity_getSize(modelName).z);
					//auto faceCulled = std::to_string(_fe3d.gameEntity_isFaceCulled(modelName));
					//auto shadowed = std::to_string(_fe3d.gameEntity_isShadowed(modelName));
					//auto transparent = std::to_string(_fe3d.gameEntity_isTransparent(modelName));
					//auto specular = std::to_string(_fe3d.gameEntity_isSpecularLighted(modelName));
					//auto specularStrength = std::to_string(_fe3d.gameEntity_getSpecularStrength(modelName));
					//auto colorR = std::to_string(_fe3d.gameEntity_getColor(modelName).x);
					//auto colorG = std::to_string(_fe3d.gameEntity_getColor(modelName).y);
					//auto colorB = std::to_string(_fe3d.gameEntity_getColor(modelName).z);
					//auto uvRepeat = std::to_string(_fe3d.gameEntity_getUvRepeat(modelName));
					//auto boxSizeX = std::to_string(_fe3d.aabbEntity_getSize(modelName).x);
					//auto boxSizeY = std::to_string(_fe3d.aabbEntity_getSize(modelName).y);
					//auto boxSizeZ = std::to_string(_fe3d.aabbEntity_getSize(modelName).z);

					//// 1 model -> 1 line in file
					//file << modelName << " " <<
					//	objPath << " " << diffuseMapPath << " " << lightMapPath << " " << reflectionMapPath << " " <<
					//	modelSizeX << " " << modelSizeY << " " << modelSizeZ << " " <<
					//	faceCulled << " " << shadowed << " " << transparent << " " << specular << " " << specularStrength << " " <<
					//	colorR << " " << colorG << " " << colorB << " " << uvRepeat << " " <<
					//	boxSizeX << " " << boxSizeY << " " << boxSizeZ << "\n";
				}
				else
				{
					//file << modelName << " - - - - 0.0 0.0 0.0 0 0 0 0 0.0 0.0 0.0 0.0 0 0.0 0.0 0.0\n";
				}
			}
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Model editor data from project \"" + _currentProjectName + "\" saved!");
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