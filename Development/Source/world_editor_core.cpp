#include "world_editor.hpp"
#include "left_viewport_controller.hpp"

WorldEditor::WorldEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void WorldEditor::initializeGUI()
{
	// Private window instance of left viewport
	_leftWindow = _gui->getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - worldManagement
	_leftWindow->addScreen("worldManagement");
	_leftWindow->getScreen("worldManagement")->addButton("sky", vec2(0.0f, 0.63f), vec2(0.65f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Sky", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("worldManagement")->addButton("terrain", vec2(0.0f, 0.21), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Terrain", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("worldManagement")->addButton("water", vec2(0.0f, -0.21), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Water", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("worldManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	
	// Left-viewport: mainWindow - skyMenu
	_leftWindow->addScreen("skyMenu");
	_leftWindow->getScreen("skyMenu")->addButton("create", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Create sky", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyMenu")->addButton("edit", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Edit sky", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyMenu")->addButton("remove", vec2(0.0f, -0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Remove sky", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyMenu")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - skyManagement
	_leftWindow->addScreen("skyManagement");
	_leftWindow->getScreen("skyManagement")->addButton("mesh", vec2(0.0f, 0.475f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "3D mesh", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyManagement")->addButton("options", vec2(0.0f, 0.0f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Options", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyManagement")->addButton("back", vec2(0.0f, -0.475f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - skyMesh
	_leftWindow->addScreen("skyMesh");
	_leftWindow->getScreen("skyMesh")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, LeftViewportController::textColor, LeftViewportController::textHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen("skyMesh")->getScrollingList("buttonList")->addButton("leftTexture", "Left texture");
	_leftWindow->getScreen("skyMesh")->getScrollingList("buttonList")->addButton("rightTexture", "Right texture");
	_leftWindow->getScreen("skyMesh")->getScrollingList("buttonList")->addButton("frontTexture", "Front texture");
	_leftWindow->getScreen("skyMesh")->getScrollingList("buttonList")->addButton("backTexture", "Back texture");
	_leftWindow->getScreen("skyMesh")->getScrollingList("buttonList")->addButton("topTexture", "Top texture");
	_leftWindow->getScreen("skyMesh")->getScrollingList("buttonList")->addButton("bottomTexture", "Bottom texture");
	_leftWindow->getScreen("skyMesh")->addButton("load", vec2(0.0f, -0.7f), vec2(0.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Load", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyMesh")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - skyOptions
	_leftWindow->addScreen("skyOptions");
	_leftWindow->getScreen("skyOptions")->addButton("rotationSpeed", vec2(0.0f, 0.63f), vec2(1.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Rotation speed", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyOptions")->addButton("lightness", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "lightness", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyOptions")->addButton("color", vec2(0.0f, -0.21f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Color", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyOptions")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - terrainMenu
	_leftWindow->addScreen("terrainMenu");
	_leftWindow->getScreen("terrainMenu")->addButton("create", vec2(0.0f, 0.63f), vec2(1.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Create terain", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainMenu")->addButton("edit", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Edit terrain", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainMenu")->addButton("remove", vec2(0.0f, -0.21f), vec2(1.85f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Remove terrain", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainMenu")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - terrainManagement
	_leftWindow->addScreen("terrainManagement");
	_leftWindow->getScreen("terrainManagement")->addButton("mesh", vec2(0.0f, 0.475f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "3D mesh", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainManagement")->addButton("blendmap", vec2(0.0f, 0.0f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Blendmap", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainManagement")->addButton("back", vec2(0.0f, -0.475f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - terrainMesh
	_leftWindow->addScreen("terrainMesh");
	_leftWindow->getScreen("terrainMesh")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, LeftViewportController::textColor, LeftViewportController::textHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen("terrainMesh")->getScrollingList("buttonList")->addButton("heightmap", "Height map");
	_leftWindow->getScreen("terrainMesh")->getScrollingList("buttonList")->addButton("diffuseMap", "Diffuse map");
	_leftWindow->getScreen("terrainMesh")->getScrollingList("buttonList")->addButton("size", "Size");
	_leftWindow->getScreen("terrainMesh")->getScrollingList("buttonList")->addButton("maxHeight", "Max height");
	_leftWindow->getScreen("terrainMesh")->getScrollingList("buttonList")->addButton("uvRepeat", "UV repeat");
	_leftWindow->getScreen("terrainMesh")->getScrollingList("buttonList")->addButton("lightness", "lightness");
	_leftWindow->getScreen("terrainMesh")->addButton("load", vec2(0.0f, -0.7f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Load", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainMesh")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - terrainBlendmap
	_leftWindow->addScreen("terrainBlendmap");
	_leftWindow->getScreen("terrainBlendmap")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, LeftViewportController::textColor, LeftViewportController::textHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("blendmap", "Blend map");
	_leftWindow->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("red", "Red texture");
	_leftWindow->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("green", "Green texture");
	_leftWindow->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("blue", "Blue texture");
	_leftWindow->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("redRepeat", "Red UV");
	_leftWindow->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("greenRepeat", "Green UV");
	_leftWindow->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("blueRepeat", "Blue UV");
	_leftWindow->getScreen("terrainBlendmap")->addButton("load", vec2(0.0f, -0.7f), vec2(0.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Load", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainBlendmap")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - waterMenu
	_leftWindow->addScreen("waterMenu");
	_leftWindow->getScreen("waterMenu")->addButton("create", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Create water", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterMenu")->addButton("edit", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Edit water", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterMenu")->addButton("remove", vec2(0.0f, -0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Remove water", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterMenu")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - waterManagement
	_leftWindow->addScreen("waterManagement");
	_leftWindow->getScreen("waterManagement")->addButton("mesh", vec2(0.0f, 0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "3D mesh", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterManagement")->addButton("effects", vec2(0.0f, 0.21f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Effects", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterManagement")->addButton("options", vec2(0.0f, -0.21f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Options", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - waterMesh
	_leftWindow->addScreen("waterMesh");
	_leftWindow->getScreen("waterMesh")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, LeftViewportController::textColor, LeftViewportController::textHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen("waterMesh")->getScrollingList("buttonList")->addButton("size", "Size");
	_leftWindow->getScreen("waterMesh")->getScrollingList("buttonList")->addButton("height", "Height");
	_leftWindow->getScreen("waterMesh")->getScrollingList("buttonList")->addButton("up", "Move up");
	_leftWindow->getScreen("waterMesh")->getScrollingList("buttonList")->addButton("down", "Move down");
	_leftWindow->getScreen("waterMesh")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - waterEffects
	_leftWindow->addScreen("waterEffects");
	_leftWindow->getScreen("waterEffects")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, LeftViewportController::textColor, LeftViewportController::textHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("uvRepeat", "UV repeat");
	_leftWindow->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("dudvmap", "Dudv map");
	_leftWindow->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("normalmap", "Normal map");
	_leftWindow->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("reflective", "Reflective: OFF");
	_leftWindow->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("refractive", "Refractive: OFF");
	_leftWindow->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("waving", "Waving: OFF");
	_leftWindow->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("rippling", "Rippling: OFF");
	_leftWindow->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("specular", "Specular: OFF");
	_leftWindow->getScreen("waterEffects")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - waterOptions
	_leftWindow->addScreen("waterOptions");
	_leftWindow->getScreen("waterOptions")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, LeftViewportController::textColor, LeftViewportController::textHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen("waterOptions")->getScrollingList("buttonList")->addButton("speed", "Water speed");
	_leftWindow->getScreen("waterOptions")->getScrollingList("buttonList")->addButton("transparency", "Transparency");
	_leftWindow->getScreen("waterOptions")->getScrollingList("buttonList")->addButton("color", "Color");
	_leftWindow->getScreen("waterOptions")->getScrollingList("buttonList")->addButton("shininess", "Shininess");
	_leftWindow->getScreen("waterOptions")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);
}

void WorldEditor::load()
{
	// Camera
	_fe3d.camera_setPosition(vec3(0.0f));
	
	// Enable graphics
	_fe3d.gfx_enableAmbientLighting(vec3(1.0f), 0.75f);
	_fe3d.gfx_enableDirectionalLighting(vec3(1000.0f), vec3(1.0f), 0.75f);
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

	// Core
	_unloadSkyData();
	_unloadTerrainData();
	_unloadWaterData();

	// Enable default sky
	_fe3d.skyEntity_select("@defaultSky");

	// Camera
	_fe3d.camera_setPosition(vec3(0.0f));
	_fe3d.camera_setYaw(0.0f);
	_fe3d.camera_setPitch(0.0f);
	_fe3d.camera_disableLookat();

	// Reset variables
	_isLoaded = false;
	_currentWorldPart = WorldPart::NONE;
	_cameraRotationSpeed = 0.0f;
	_totalCameraRotation = 0.0f;
	_skyTexturePaths.clear();
	_skyRotationSpeed = 0.0f;
	_skyLightness = 1.0f;
	_skyColor = vec3(1.0f);
	_isTerrainBlendmapped = false;
	_terrainHeightmapPath = "";
	_terrainDiffusemapPath = "";
	_terrainBlendmapPath = "";
	_terrainRedPath = "";
	_terrainGreenPath = "";
	_terrainBluePath = "";
	_terrainSize = 0.0f;
	_maxTerrainHeight = 0.0f;
	_terrainUvRepeat = 0.0f;
	_terrainRedUvRepeat = 0.0f;
	_terrainGreenUvRepeat = 0.0f;
	_terrainBlueUvRepeat = 0.0f;
	_terrainLightness = 1.0f;
	_terrainCameraHeight = 0.0f;
	_terrainCameraDistance = 0.0f;
	_waterDudvmapPath = "";
	_waterNormalmapPath = "";
	_waterWavingEnabled = false;
	_waterRipplingEnabled = false;
	_waterSpecularEnabled = false;
	_waterReflectionEnabled = false;
	_waterRefractionEnabled = false;
	_waterColor = vec3(0.0f);
	_waterSize = 0.0f;
	_waterUvRepeat = 0.0f;
	_waterHeight = 0.0f;
	_waterSpeed = 0.0f;
	_waterTransparency = 0.0f;
	_waterShininess = 16.0f;
	_waterCameraHeight = 0.0f;
	_waterCameraDistance = 0.0f;
	_waterHeightSpeed = 0.1f;

	// Select the default sky
	_fe3d.skyEntity_select("@defaultSky");
}