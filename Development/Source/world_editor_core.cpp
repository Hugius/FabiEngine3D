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
	_leftWindow->addScreen("skyEditorMenuMain");
	_leftWindow->getScreen("skyEditorMenuMain")->addButton("create", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Create sky", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMain")->addButton("edit", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Edit sky", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMain")->addButton("remove", vec2(0.0f, -0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Remove sky", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - skyMenuChoice
	_leftWindow->addScreen("skyEditorMenuChoice");
	_leftWindow->getScreen("skyEditorMenuChoice")->addButton("mesh", vec2(0.0f, 0.475f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "3D mesh", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuChoice")->addButton("options", vec2(0.0f, 0.0f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Options", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuChoice")->addButton("back", vec2(0.0f, -0.475f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - skyMenuMesh
	_leftWindow->addScreen("skyEditorMenuMesh");
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("leftTexture", vec2(0.0f, 0.7875f), vec2(1.7f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Left texture", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("rightTexture", vec2(0.0f, 0.525f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Right texture", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("frontTexture", vec2(0.0f, 0.2625f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Front texture", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("backTexture", vec2(0.0f, 0.0f), vec2(1.7f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Back texture", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("topTexture", vec2(0.0f, -0.2625f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Top texture", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("bottomTexture", vec2(0.0f, -0.525f), vec2(1.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Bottom texture", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("back", vec2(0.0f, -0.7875f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - skyMenuOptions
	_leftWindow->addScreen("skyEditorMenuOptions");
	_leftWindow->getScreen("skyEditorMenuOptions")->addButton("rotationSpeed", vec2(0.0f, 0.63f), vec2(1.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Rotation speed", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuOptions")->addButton("lightness", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "lightness", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuOptions")->addButton("color", vec2(0.0f, -0.21f), vec2(0.9f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Color", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuOptions")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuMain
	_leftWindow->addScreen("terrainEditorMenuMain");
	_leftWindow->getScreen("terrainEditorMenuMain")->addButton("create", vec2(0.0f, 0.63f), vec2(1.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Create terain", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMain")->addButton("edit", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Edit terrain", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMain")->addButton("remove", vec2(0.0f, -0.21f), vec2(1.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Remove terrain", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuChoice
	_leftWindow->addScreen("terrainEditorMenuChoice");
	_leftWindow->getScreen("terrainEditorMenuChoice")->addButton("mesh", vec2(0.0f, 0.475f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "3D mesh", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuChoice")->addButton("blendMap", vec2(0.0f, 0.0f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "BlendMap", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuChoice")->addButton("back", vec2(0.0f, -0.475f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuMesh
	_leftWindow->addScreen("terrainEditorMenuMesh");
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("heightMap", vec2(0.0f, 0.75f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Height map", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("diffuseMap", vec2(0.0f, 0.45f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Diffuse map", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("maxHeight", vec2(0.0f, 0.15f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Max height", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("uvRepeat", vec2(0.0f, -0.15f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "UV repeat", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("lightness", vec2(0.0f, -0.45f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Lightness", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("back", vec2(0.0f, -0.75f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuBlendMap
	_leftWindow->addScreen("terrainEditorMenuBlendMap");
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("blendMap", vec2(0.0f, 0.83f), vec2(1.7f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Blend map", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("red", vec2(0.0f, 0.59f), vec2(1.7f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Red texture", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("green", vec2(0.0f, 0.36f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Green texture", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("blue", vec2(0.0f, 0.13f), vec2(1.7f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Blue texture", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("redRepeat", vec2(0.0f, -0.1f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Red UV", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("greenRepeat", vec2(0.0f, -0.33f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Green UV", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("blueRepeat", vec2(0.0f, -0.56f), vec2(1.3f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Blue UV", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("back", vec2(0.0f, -0.79f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	
	// Left-viewport: mainWindow - waterMenuMain
	_leftWindow->addScreen("waterEditorMenuMain");
	_leftWindow->getScreen("waterEditorMenuMain")->addButton("create", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Create water", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMain")->addButton("edit", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Edit water", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMain")->addButton("remove", vec2(0.0f, -0.21f), vec2(1.7f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Remove water", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - waterManagement
	_leftWindow->addScreen("waterEditorMenuChoice");
	_leftWindow->getScreen("waterEditorMenuChoice")->addButton("mesh", vec2(0.0f, 0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "3D mesh", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuChoice")->addButton("effects", vec2(0.0f, 0.21f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Effects", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuChoice")->addButton("options", vec2(0.0f, -0.21f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Options", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuChoice")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - waterMenuMesh
	_leftWindow->addScreen("waterEditorMenuMesh");
	_leftWindow->getScreen("waterEditorMenuMesh")->addButton("position", vec2(0.0f, 0.7f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Position", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMesh")->addButton("size", vec2(0.0f, 0.35f), vec2(0.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Size", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMesh")->addButton("up", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Move up", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMesh")->addButton("down", vec2(0.0f, -0.35f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Move down", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMesh")->addButton("back", vec2(0.0f, -0.7f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - waterMenuEffects
	_leftWindow->addScreen("waterEditorMenuEffects");
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("uvRepeat", vec2(0.0f, 0.859f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "UV repeat", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("dudvMap", vec2(0.0f, 0.668f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Dudv map", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("normalMap", vec2(0.0f, 0.477f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Normal map", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("displaceMap", vec2(0.0f, 0.286f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Displace map", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("isReflective", vec2(0.0f, 0.095f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Reflective: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("isRefractive", vec2(0.0f, -0.096f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Refractive: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("isWaving", vec2(0.0f, -0.287f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Waving: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("isRippling", vec2(0.0f, -0.478f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Rippling: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("isSpecular", vec2(0.0f, -0.669f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Specular: OFF", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("back", vec2(0.0f, -0.86f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - waterMenuOptions
	_leftWindow->addScreen("waterEditorMenuOptions");
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("speed", vec2(0.0f, 0.7875f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Water speed", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("transparency", vec2(0.0f, 0.525f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Transparency", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("color", vec2(0.0f, 0.2625f), vec2(0.9f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Color", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("specularFactor", vec2(0.0f, 0.0f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Specular factor", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("specularIntensity", vec2(0.0f, -0.2625f), vec2(1.8f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Specular intensity", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("waveHeight", vec2(0.0f, -0.525f), vec2(1.7f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Wave height", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("back", vec2(0.0f, -0.7875f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);
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

	// Delete water entity
	if (_fe3d.waterEntity_isExisting("@water"))
	{
		_fe3d.waterEntity_delete("@water");
	}

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