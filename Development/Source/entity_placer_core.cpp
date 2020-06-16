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
	_leftWindow->getScreen("placeManagement")->addButton("placeModel", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Place model", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_leftWindow->getScreen("placeManagement")->addButton("placeBillboard", vec2(0.0f, 0.21), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Place billboard", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_leftWindow->getScreen("placeManagement")->addButton("placeLight", vec2(0.0f, -0.21), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Place light", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_leftWindow->getScreen("placeManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	
	// Left-viewport: mainWindow - modelPlaceManagement
	_leftWindow->addScreen("modelPlaceManagement");
	_leftWindow->getScreen("modelPlaceManagement")->addScrollingList("modelList", vec2(0.0f, 0.1f), vec2(1.8, 1.75f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));

	// Left-viewport: mainWindow - billboardPlaceManagement
	_leftWindow->addScreen("billboardPlaceManagement");

	// Left-viewport: mainWindow - lightPlaceManagement
	_leftWindow->addScreen("lightPlaceManagement");
}

void EntityPlacer::load()
{
	// Graphics
	_fe3d.gfx_enableAmbientLighting(0.75f);
	_fe3d.gfx_enableDirectionalLighting(vec3(1000.0f), 0.75f);
	_fe3d.gfx_enableMSAA();
	_fe3d.gfx_enableWaterEffects();

	// Load world entities
	_worldEditor.loadSkyEntity();
	_worldEditor.loadTerrainEntity();
	_worldEditor.loadWaterEntity();

	// Show world entities
	_fe3d.skyEntity_show("@sky");
	_fe3d.terrainEntity_show("@terrain");
	_fe3d.waterEntity_show("@water");

	// Camera
	if (_fe3d.terrainEntity_isExisting("@terrain"))
	{
		float height = _fe3d.terrainEntity_getMaxHeight("@terrain");
		_fe3d.camera_load(90.0f, 0.1f, 1000.0f, vec3(0.0f, height, 0.0f), 0.0f, 0.0f);
	}
	else
	{
		if (_fe3d.waterEntity_isExisting("@water"))
		{
			float size =  _fe3d.waterEntity_getSize("@water") / 2.0f;
			float height = _fe3d.waterEntity_getSurfaceHeight("@water") + (size / 10.0f);
			_fe3d.camera_load(90.0f, 0.1f, 1000.0f, vec3(0.0f, height, 0.0f), 0.0f, 0.0f);
		}
	}

	// Model loading
	_modelEditor.loadModels();
	for (auto& modelName : _modelEditor.getModelNames())
	{
		_leftWindow->getScreen("modelPlaceManagement")->getScrollingList("modelList")->addButton("@" + modelName, modelName);
		_counterMap.insert(std::make_pair(modelName, 0));
	}

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
	_fe3d.gfx_disableMSAA();
	_fe3d.gfx_disableWaterEffects();

	// Entities
	_fe3d.skyEntity_delete("@sky");
	_fe3d.terrainEntity_delete("@terrain");
	_fe3d.waterEntity_delete("@water");

	// Other
	_isLoaded = false;
}