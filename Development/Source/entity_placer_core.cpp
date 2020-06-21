#include "entity_placer.hpp"

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
}

void EntityPlacer::load()
{
	// Enable graphics
	_fe3d.gfx_enableAmbientLighting(0.5f);
	_fe3d.gfx_enableDirectionalLighting(vec3(1000.0f), 0.5f);
	_fe3d.gfx_enableLightMapping();
	_fe3d.gfx_enableSkyReflections(0.25f);
	_fe3d.gfx_enableMSAA();
	_fe3d.gfx_enableWaterEffects();
	//_fe3d.gfx_enableShadows(vec3(50.0f, 50.0f, 0.0f), vec3(0.0f), 100.0f, 150.0);
	_fe3d.gfx_enableSpecularLighting(16.0f);
	_fe3d.gfx_enableBloom(1.0f, 0.0f, 10);
	_fe3d.gfx_setSkyBrightness(0.75f);

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
		_leftWindow->getScreen("modelPlaceManagement")->getScrollingList("modelList")->addButton(modelName, modelName.substr(1, modelName.size()));
		_counterMap.insert(std::make_pair(modelName, 0));
	}

	// Create name textfields
	_gui->getGlobalScreen()->addTextfield("selectedModelName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));

	// Other
	_isLoaded = true;
}

void EntityPlacer::save()
{

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
	_fe3d.gfx_disableBloom();
	_fe3d.gfx_setSkyBrightness(1.0f);

	// Delete world entities
	_fe3d.skyEntity_delete("@sky");
	_fe3d.terrainEntity_delete("@terrain");
	_fe3d.waterEntity_delete("@water");

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

	// Other
	_leftWindow->getScreen("modelPlaceManagement")->getScrollingList("modelList")->deleteButtons();
	_isLoaded = false;
}