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
	
	// Left-viewport: mainWindow - skyMenu
	_window->addScreen("skyMenu");
	_window->getScreen("skyMenu")->addButton("create", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Create sky", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("skyMenu")->addButton("edit", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Edit sky", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("skyMenu")->addButton("remove", vec2(0.0f, -0.21f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Remove sky", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("skyMenu")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - skyManagement
	_window->addScreen("skyManagement");
	_window->getScreen("skyManagement")->addButton("mesh", vec2(0.0f, 0.475f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "3D mesh", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("skyManagement")->addButton("options", vec2(0.0f, 0.0f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Options", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("skyManagement")->addButton("back", vec2(0.0f, -0.475f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - skyMesh
	_window->addScreen("skyMesh");
	_window->getScreen("skyMesh")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));
	_window->getScreen("skyMesh")->getScrollingList("buttonList")->addButton("leftTexture", "Left texture");
	_window->getScreen("skyMesh")->getScrollingList("buttonList")->addButton("rightTexture", "Right texture");
	_window->getScreen("skyMesh")->getScrollingList("buttonList")->addButton("frontTexture", "Front texture");
	_window->getScreen("skyMesh")->getScrollingList("buttonList")->addButton("backTexture", "Back texture");
	_window->getScreen("skyMesh")->getScrollingList("buttonList")->addButton("topTexture", "Top texture");
	_window->getScreen("skyMesh")->getScrollingList("buttonList")->addButton("bottomTexture", "Bottom texture");
	_window->getScreen("skyMesh")->addButton("load", vec2(0.0f, -0.7f), vec2(0.8f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Load", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("skyMesh")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - skyOptions
	_window->addScreen("skyOptions");
	_window->getScreen("skyOptions")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));
	_window->getScreen("skyOptions")->getScrollingList("buttonList")->addButton("rotationSpeed", "Rotation speed");
	_window->getScreen("skyOptions")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - terrainMenu
	_window->addScreen("terrainMenu");
	_window->getScreen("terrainMenu")->addButton("create", vec2(0.0f, 0.63f), vec2(1.8f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Create terain", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("terrainMenu")->addButton("edit", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Edit terrain", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("terrainMenu")->addButton("remove", vec2(0.0f, -0.21f), vec2(1.85f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Remove terrain", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("terrainMenu")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - terrainManagement
	_window->addScreen("terrainManagement");
	_window->getScreen("terrainManagement")->addButton("mesh", vec2(0.0f, 0.475f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "3D mesh", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("terrainManagement")->addButton("blendmap", vec2(0.0f, 0.0f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Blendmap", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("terrainManagement")->addButton("back", vec2(0.0f, -0.475f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - terrainMesh
	_window->addScreen("terrainMesh");
	_window->getScreen("terrainMesh")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));
	_window->getScreen("terrainMesh")->getScrollingList("buttonList")->addButton("heightmap", "Height map");
	_window->getScreen("terrainMesh")->getScrollingList("buttonList")->addButton("diffusemap", "Diffuse map");
	_window->getScreen("terrainMesh")->getScrollingList("buttonList")->addButton("size", "Size");
	_window->getScreen("terrainMesh")->getScrollingList("buttonList")->addButton("maxHeight", "Max height");
	_window->getScreen("terrainMesh")->getScrollingList("buttonList")->addButton("uvRepeat", "UV repeat");
	_window->getScreen("terrainMesh")->addButton("load", vec2(0.0f, -0.7f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Load", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("terrainMesh")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - terrainBlendmap
	_window->addScreen("terrainBlendmap");
	_window->getScreen("terrainBlendmap")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));
	_window->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("blendmap", "Blend map");
	_window->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("red", "Red texture");
	_window->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("green", "Green texture");
	_window->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("blue", "Blue texture");
	_window->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("redRepeat", "Red UV");
	_window->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("greenRepeat", "Green UV");
	_window->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("blueRepeat", "Blue UV");
	_window->getScreen("terrainBlendmap")->addButton("load", vec2(0.0f, -0.7f), vec2(0.8f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Load", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("terrainBlendmap")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - waterMenu
	_window->addScreen("waterMenu");
	_window->getScreen("waterMenu")->addButton("create", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Create water", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("waterMenu")->addButton("edit", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Edit water", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("waterMenu")->addButton("remove", vec2(0.0f, -0.21f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Remove water", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("waterMenu")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - waterManagement
	_window->addScreen("waterManagement");
	_window->getScreen("waterManagement")->addButton("mesh", vec2(0.0f, 0.63f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "3D mesh", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("waterManagement")->addButton("effects", vec2(0.0f, 0.21f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Effects", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("waterManagement")->addButton("options", vec2(0.0f, -0.21f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Options", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("waterManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - waterMesh
	_window->addScreen("waterMesh");
	_window->getScreen("waterMesh")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));
	_window->getScreen("waterMesh")->getScrollingList("buttonList")->addButton("size", "Size");
	_window->getScreen("waterMesh")->getScrollingList("buttonList")->addButton("height", "Height");
	_window->getScreen("waterMesh")->getScrollingList("buttonList")->addButton("up", "Move up");
	_window->getScreen("waterMesh")->getScrollingList("buttonList")->addButton("down", "Move down");
	_window->getScreen("waterMesh")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - waterEffects
	_window->addScreen("waterEffects");
	_window->getScreen("waterEffects")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));
	_window->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("uvRepeat", "UV repeat");
	_window->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("dudvmap", "Dudv map");
	_window->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("normalmap", "Normal map");
	_window->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("reflective", "Reflective: OFF");
	_window->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("refractive", "Refractive: OFF");
	_window->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("waving", "Waving: OFF");
	_window->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("rippling", "Rippling: OFF");
	_window->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("specular", "Specular: OFF");
	_window->getScreen("waterEffects")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - waterOptions
	_window->addScreen("waterOptions");
	_window->getScreen("waterOptions")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));
	_window->getScreen("waterOptions")->getScrollingList("buttonList")->addButton("speed", "Water speed");
	_window->getScreen("waterOptions")->getScrollingList("buttonList")->addButton("transparency", "Transparency");
	_window->getScreen("waterOptions")->getScrollingList("buttonList")->addButton("color", "Color");
	_window->getScreen("waterOptions")->getScrollingList("buttonList")->addButton("shininess", "Shininess");
	_window->getScreen("waterOptions")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
}

void WorldEditor::load()
{
	// Camera
	_fe3d.camera_load(90.0f, 0.1f, 1000.0f, vec3(0.0f), 0.0f, 0.0f);

	// Graphics
	_fe3d.gfx_enableAmbientLighting(0.75f);
	_fe3d.gfx_enableDirectionalLighting(vec3(1000.0f), 0.75f);
	_fe3d.gfx_enableMSAA();
	_fe3d.gfx_enableWaterEffects();

	// Other
	_isLoaded = true;

	// Core
	loadSkyEntity();
	loadTerrainEntity();
	loadWaterEntity();
}

void WorldEditor::save()
{
	_saveSkyData();
	_saveTerrainData();
	_saveWaterData();
}

void WorldEditor::unload()
{
	// Disable graphics
	_fe3d.gfx_disableAmbientLighting();
	_fe3d.gfx_disableDirectionalLighting();
	_fe3d.gfx_disableMSAA();
	_fe3d.gfx_disableWaterEffects();

	// Clear variables
	_isLoaded = false;
	_currentWorldPart = WorldPart::NONE;
	_cameraRotationSpeed = 0.0f;
	_totalCameraRotation = 0.0f;

	// Core
	_unloadSkyData();
	_unloadTerrainData();
	_unloadWaterData();
}