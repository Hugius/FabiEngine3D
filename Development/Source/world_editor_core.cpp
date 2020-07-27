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

	// Left-viewport: mainWindow - worldEditorMenu
	_leftWindow->addScreen("worldEditorMenu");
	_leftWindow->getScreen("worldEditorMenu")->addButton("sky", vec2(0.0f, 0.63f), vec2(0.65f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Sky", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("worldEditorMenu")->addButton("terrain", vec2(0.0f, 0.21), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Terrain", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("worldEditorMenu")->addButton("water", vec2(0.0f, -0.21), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Water", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("worldEditorMenu")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	
	// Left-viewport: mainWindow - skyMenuMain
	_leftWindow->addScreen("skyMenuMain");
	_leftWindow->getScreen("skyMenuMain")->addButton("create", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Create sky", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyMenuMain")->addButton("edit", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Edit sky", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyMenuMain")->addButton("remove", vec2(0.0f, -0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Remove sky", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - skyMenuChoice
	_leftWindow->addScreen("skyMenuChoice");
	_leftWindow->getScreen("skyMenuChoice")->addButton("mesh", vec2(0.0f, 0.475f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "3D mesh", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyMenuChoice")->addButton("options", vec2(0.0f, 0.0f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Options", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyMenuChoice")->addButton("back", vec2(0.0f, -0.475f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - skyMenuMesh
	_leftWindow->addScreen("skyMenuMesh");
	_leftWindow->getScreen("skyMenuMesh")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, LeftViewportController::textColor, LeftViewportController::textHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen("skyMenuMesh")->getScrollingList("buttonList")->addButton("leftTexture", "Left texture");
	_leftWindow->getScreen("skyMenuMesh")->getScrollingList("buttonList")->addButton("rightTexture", "Right texture");
	_leftWindow->getScreen("skyMenuMesh")->getScrollingList("buttonList")->addButton("frontTexture", "Front texture");
	_leftWindow->getScreen("skyMenuMesh")->getScrollingList("buttonList")->addButton("backTexture", "Back texture");
	_leftWindow->getScreen("skyMenuMesh")->getScrollingList("buttonList")->addButton("topTexture", "Top texture");
	_leftWindow->getScreen("skyMenuMesh")->getScrollingList("buttonList")->addButton("bottomTexture", "Bottom texture");
	_leftWindow->getScreen("skyMenuMesh")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - skyMenuOptions
	_leftWindow->addScreen("skyMenuOptions");
	_leftWindow->getScreen("skyMenuOptions")->addButton("rotationSpeed", vec2(0.0f, 0.63f), vec2(1.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Rotation speed", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyMenuOptions")->addButton("lightness", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "lightness", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyMenuOptions")->addButton("color", vec2(0.0f, -0.21f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Color", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyMenuOptions")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuMain
	_leftWindow->addScreen("terrainMenuMain");
	_leftWindow->getScreen("terrainMenuMain")->addButton("create", vec2(0.0f, 0.63f), vec2(1.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Create terain", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainMenuMain")->addButton("edit", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Edit terrain", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainMenuMain")->addButton("remove", vec2(0.0f, -0.21f), vec2(1.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Remove terrain", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuChoice
	_leftWindow->addScreen("terrainMenuChoice");
	_leftWindow->getScreen("terrainMenuChoice")->addButton("mesh", vec2(0.0f, 0.475f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "3D mesh", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainMenuChoice")->addButton("blendMap", vec2(0.0f, 0.0f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "BlendMap", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainMenuChoice")->addButton("back", vec2(0.0f, -0.475f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuMesh
	_leftWindow->addScreen("terrainMenuMesh");
	_leftWindow->getScreen("terrainMenuMesh")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, LeftViewportController::textColor, LeftViewportController::textHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen("terrainMenuMesh")->getScrollingList("buttonList")->addButton("heightMap", "Height map");
	_leftWindow->getScreen("terrainMenuMesh")->getScrollingList("buttonList")->addButton("diffuseMap", "Diffuse map");
	_leftWindow->getScreen("terrainMenuMesh")->getScrollingList("buttonList")->addButton("maxHeight", "Max height");
	_leftWindow->getScreen("terrainMenuMesh")->getScrollingList("buttonList")->addButton("uvRepeat", "UV repeat");
	_leftWindow->getScreen("terrainMenuMesh")->getScrollingList("buttonList")->addButton("lightness", "lightness");
	_leftWindow->getScreen("terrainMenuMesh")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuBlendMap
	_leftWindow->addScreen("terrainMenuBlendMap");
	_leftWindow->getScreen("terrainMenuBlendMap")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, LeftViewportController::textColor, LeftViewportController::textHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen("terrainMenuBlendMap")->getScrollingList("buttonList")->addButton("blendMap", "Blend map");
	_leftWindow->getScreen("terrainMenuBlendMap")->getScrollingList("buttonList")->addButton("red", "Red texture");
	_leftWindow->getScreen("terrainMenuBlendMap")->getScrollingList("buttonList")->addButton("green", "Green texture");
	_leftWindow->getScreen("terrainMenuBlendMap")->getScrollingList("buttonList")->addButton("blue", "Blue texture");
	_leftWindow->getScreen("terrainMenuBlendMap")->getScrollingList("buttonList")->addButton("redRepeat", "Red UV");
	_leftWindow->getScreen("terrainMenuBlendMap")->getScrollingList("buttonList")->addButton("greenRepeat", "Green UV");
	_leftWindow->getScreen("terrainMenuBlendMap")->getScrollingList("buttonList")->addButton("blueRepeat", "Blue UV");
	_leftWindow->getScreen("terrainMenuBlendMap")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - waterMenuMain
	_leftWindow->addScreen("waterMenuMain");
	_leftWindow->getScreen("waterMenuMain")->addButton("create", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Create water", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterMenuMain")->addButton("edit", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Edit water", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterMenuMain")->addButton("remove", vec2(0.0f, -0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Remove water", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - waterManagement
	_leftWindow->addScreen("waterMenuChoice");
	_leftWindow->getScreen("waterMenuChoice")->addButton("mesh", vec2(0.0f, 0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "3D mesh", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterMenuChoice")->addButton("effects", vec2(0.0f, 0.21f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Effects", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterMenuChoice")->addButton("options", vec2(0.0f, -0.21f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Options", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterMenuChoice")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - waterMenuMesh
	_leftWindow->addScreen("waterMenuMesh");
	_leftWindow->getScreen("waterMenuMesh")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, LeftViewportController::textColor, LeftViewportController::textHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen("waterMenuMesh")->getScrollingList("buttonList")->addButton("position", "Position");
	_leftWindow->getScreen("waterMenuMesh")->getScrollingList("buttonList")->addButton("size", "Size");
	_leftWindow->getScreen("waterMenuMesh")->getScrollingList("buttonList")->addButton("up", "Move up");
	_leftWindow->getScreen("waterMenuMesh")->getScrollingList("buttonList")->addButton("down", "Move down");
	_leftWindow->getScreen("waterMenuMesh")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - waterMenuEffects
	_leftWindow->addScreen("waterMenuEffects");
	_leftWindow->getScreen("waterMenuEffects")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, LeftViewportController::textColor, LeftViewportController::textHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen("waterMenuEffects")->getScrollingList("buttonList")->addButton("uvRepeat", "UV repeat");
	_leftWindow->getScreen("waterMenuEffects")->getScrollingList("buttonList")->addButton("dudvMap", "Dudv map");
	_leftWindow->getScreen("waterMenuEffects")->getScrollingList("buttonList")->addButton("normalMap", "Normal map");
	_leftWindow->getScreen("waterMenuEffects")->getScrollingList("buttonList")->addButton("displaceMap", "Displace map");
	_leftWindow->getScreen("waterMenuEffects")->getScrollingList("buttonList")->addButton("isReflective", "Reflective: OFF");
	_leftWindow->getScreen("waterMenuEffects")->getScrollingList("buttonList")->addButton("isRefractive", "Refractive: OFF");
	_leftWindow->getScreen("waterMenuEffects")->getScrollingList("buttonList")->addButton("isWaving", "Waving: OFF");
	_leftWindow->getScreen("waterMenuEffects")->getScrollingList("buttonList")->addButton("isRippling", "Rippling: OFF");
	_leftWindow->getScreen("waterMenuEffects")->getScrollingList("buttonList")->addButton("isSpecular", "Specular: OFF");
	_leftWindow->getScreen("waterMenuEffects")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - waterMenuOptions
	_leftWindow->addScreen("waterMenuOptions");
	_leftWindow->getScreen("waterMenuOptions")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, LeftViewportController::textColor, LeftViewportController::textHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen("waterMenuOptions")->getScrollingList("buttonList")->addButton("speed", "Water speed");
	_leftWindow->getScreen("waterMenuOptions")->getScrollingList("buttonList")->addButton("transparency", "Transparency");
	_leftWindow->getScreen("waterMenuOptions")->getScrollingList("buttonList")->addButton("color", "Color");
	_leftWindow->getScreen("waterMenuOptions")->getScrollingList("buttonList")->addButton("specularFactor", "Specular factor");
	_leftWindow->getScreen("waterMenuOptions")->getScrollingList("buttonList")->addButton("specularIntensity", "Specular intensity");
	_leftWindow->getScreen("waterMenuOptions")->getScrollingList("buttonList")->addButton("waveHeight", "Wave height");
	_leftWindow->getScreen("waterMenuOptions")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);
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

	// Delete sky entity
	if (_fe3d.skyEntity_isExisting("@sky"))
	{
		_fe3d.skyEntity_delete("@sky");
	}

	// Delete terrain entity
	if (_fe3d.terrainEntity_isExisting("@terrain"))
	{
		_fe3d.terrainEntity_delete("@terrain");
	}

	_unloadWaterData();

	// Enable default sky
	_fe3d.skyEntity_select("@@sky");

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

	// Select the default sky
	_fe3d.skyEntity_select("@@sky");
}