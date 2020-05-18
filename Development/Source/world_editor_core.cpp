#include "world_editor.hpp"

WorldEditor::WorldEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void WorldEditor::initializeGUI()
{
	// Private window instance of left viewport
	_window = _gui->getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - worldManagement
	_window->addScreen("worldManagement");
	_window->getScreen("worldManagement")->addButton("sky", vec2(0.0f, 0.63f), vec2(0.65f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Sky", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("worldManagement")->addButton("terrain", vec2(0.0f, 0.21), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Terrain", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("worldManagement")->addButton("water", vec2(0.0f, -0.21), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Water", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("worldManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - skyManagement
	_window->addScreen("skyManagement");
	_window->getScreen("skyManagement")->addButton("mesh", vec2(0.0f, 0.475f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "3D mesh", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("skyManagement")->addButton("options", vec2(0.0f, 0.0f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Options", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("skyManagement")->addButton("back", vec2(0.0f, -0.475f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - skyMesh
	_window->addScreen("skyMesh");
	_window->getScreen("skyMesh")->addScrollingList("textureList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));
	_window->getScreen("skyMesh")->getScrollingList("textureList")->addButton("leftTexture", "Left texture");
	_window->getScreen("skyMesh")->getScrollingList("textureList")->addButton("rightTexture", "Right texture");
	_window->getScreen("skyMesh")->getScrollingList("textureList")->addButton("frontTexture", "Front texture");
	_window->getScreen("skyMesh")->getScrollingList("textureList")->addButton("backTexture", "Back texture");
	_window->getScreen("skyMesh")->getScrollingList("textureList")->addButton("topTexture", "Top texture");
	_window->getScreen("skyMesh")->getScrollingList("textureList")->addButton("bottomTexture", "Bottom texture");
	_window->getScreen("skyMesh")->addButton("load", vec2(0.0f, -0.7f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Load", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("skyMesh")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - skyOptions
	_window->addScreen("skyOptions");
	_window->getScreen("skyOptions")->addButton("back", vec2(0.0f, -0.475f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - terrainManagement
	_window->addScreen("terrainManagement");
	_window->getScreen("terrainManagement")->addButton("mesh", vec2(0.0f, 0.475f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "3D mesh", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("terrainManagement")->addButton("blendmap", vec2(0.0f, 0.0f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Blendmap", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("terrainManagement")->addButton("back", vec2(0.0f, -0.475f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - terrainMesh
	_window->addScreen("terrainMesh");
	_window->getScreen("terrainMesh")->addScrollingList("terrainList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));
	_window->getScreen("terrainMesh")->getScrollingList("terrainList")->addButton("heightmap", "Load heightmap");
	_window->getScreen("terrainMesh")->getScrollingList("terrainList")->addButton("diffusemap", "Load diffusemap");
	_window->getScreen("terrainMesh")->getScrollingList("terrainList")->addButton("size", "Set size");
	_window->getScreen("terrainMesh")->getScrollingList("terrainList")->addButton("maxHeight", "Set height");
	_window->getScreen("terrainMesh")->getScrollingList("terrainList")->addButton("uvRepeat", "UV repeat");
	_window->getScreen("terrainMesh")->addButton("load", vec2(0.0f, -0.7f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Load", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("terrainMesh")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - terrainBlendmap
	_window->addScreen("terrainBlendmap");
	_window->getScreen("terrainBlendmap")->addScrollingList("blendmapList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));
	_window->getScreen("terrainBlendmap")->getScrollingList("blendmapList")->addButton("blendmap", "Load blendmap");
	_window->getScreen("terrainBlendmap")->getScrollingList("blendmapList")->addButton("red", "Red texture");
	_window->getScreen("terrainBlendmap")->getScrollingList("blendmapList")->addButton("green", "Green texture");
	_window->getScreen("terrainBlendmap")->getScrollingList("blendmapList")->addButton("blue", "Blue texture");
	_window->getScreen("terrainBlendmap")->getScrollingList("blendmapList")->addButton("redRepeat", "Red UV");
	_window->getScreen("terrainBlendmap")->getScrollingList("blendmapList")->addButton("greenRepeat", "Green UV");
	_window->getScreen("terrainBlendmap")->getScrollingList("blendmapList")->addButton("blueRepeat", "Blue UV");
	_window->getScreen("terrainBlendmap")->addButton("load", vec2(0.0f, -0.7f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Load", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("terrainBlendmap")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
}

void WorldEditor::loadProject()
{
	// Camera
	_fe3d.camera_load(90.0f, 0.1f, 1000.0f, vec3(0.0f), 0.0f, 0.0f);

	// Graphics
	_fe3d.gfx_addAmbientLighting(0.75f);
	_fe3d.gfx_addDirectionalLighting(vec3(1000.0f), 0.75f);
	_fe3d.gfx_addMSAA();

	// Other
	_skyTexturePaths = { "", "", "", "", "", "" };
	_isLoaded = true;
}

void WorldEditor::saveProject()
{

}

void WorldEditor::unloadProject()
{
	_fe3d.gfx_removeAmbientLighting();
	_fe3d.gfx_removeDirectionalLighting();
	_fe3d.gfx_removeMSAA();

	// Delete sky
	if (_fe3d.skyEntity_isExisting("@sky"))
	{
		_fe3d.skyEntity_delete("@sky");
	}

	// Delete terrain
	if (_fe3d.skyEntity_isExisting("@terrain"))
	{
		_fe3d.skyEntity_delete("@terrain");
	}

	// Delete water
	if (_fe3d.skyEntity_isExisting("@water"))
	{
		_fe3d.skyEntity_delete("@water");
	}

	// Clear variables
	_currentWorldPart = WorldPart::NONE;
	_currentProjectName = "";
	_terrainHeightmapPath = "";
	_terrainDiffusemapPath = "";
	_activeWritefield = "";
	_terrainBlendmapPath = "";
	_terrainRedPath = "";
	_terrainGreenPath = "";
	_terrainBluePath = "";
	_terrainSize = 0.0f;
	_maxTerrainHeight = 0.0f;
	_terrainUvRepeat = 0.0f;
	_redUvRepeat = 0.0f;
	_greenUvRepeat = 0.0f;
	_blueUvRepeat = 0.0f;
	_cameraRotationSpeed = 0.0f;
	_cameraDistance = 0.0f;
	_cameraHeight = 0.0f;
	_totalCameraRotation = 0.0f;
	_skyTexturePaths.clear();
	_isLoaded = false;
}

void WorldEditor::update(float delta)
{
	if (_isLoaded)
	{
		auto screen = _window->getScreen("worldManagement");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("sky")->isHovered())
			{
				_window->setActiveScreen("skyManagement");
				_currentWorldPart = WorldPart::SKY;
			}
			else if (screen->getButton("terrain")->isHovered())
			{
				_window->setActiveScreen("terrainManagement");
				_currentWorldPart = WorldPart::TERRAIN;
			}
			else if (screen->getButton("water")->isHovered())
			{
				_currentWorldPart = WorldPart::WATER;
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("main");
				unloadProject();
			}
		}

		// Update sub-menus
		_upateSkyManagement();
		_upateTerrainManagement();
		_upateWaterManagement();
	}
}