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
	_leftWindow->getScreen("worldEditorMenu")->addButton("sky", vec2(0.0f, 0.63f), vec2(0.65f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Sky", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("worldEditorMenu")->addButton("terrain", vec2(0.0f, 0.21), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Terrain", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("worldEditorMenu")->addButton("water", vec2(0.0f, -0.21), vec2(1.0f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Water", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("worldEditorMenu")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);
	
	// Left-viewport: mainWindow - skyMenuMain
	_leftWindow->addScreen("skyEditorMenuMain");
	_leftWindow->getScreen("skyEditorMenuMain")->addButton("create", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Create sky", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMain")->addButton("edit", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Edit sky", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMain")->addButton("remove", vec2(0.0f, -0.21f), vec2(1.5f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Remove sky", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - skyMenuChoice
	_leftWindow->addScreen("skyEditorMenuChoice");
	_leftWindow->getScreen("skyEditorMenuChoice")->addButton("mesh", vec2(0.0f, 0.475f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "3D mesh", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuChoice")->addButton("options", vec2(0.0f, 0.0f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Options", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuChoice")->addButton("back", vec2(0.0f, -0.475f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - skyMenuMesh
	_leftWindow->addScreen("skyEditorMenuMesh");
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("leftTexture", vec2(0.0f, 0.7875f), vec2(1.7f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Left texture", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("rightTexture", vec2(0.0f, 0.525f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Right texture", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("frontTexture", vec2(0.0f, 0.2625f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Front texture", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("backTexture", vec2(0.0f, 0.0f), vec2(1.7f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Back texture", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("topTexture", vec2(0.0f, -0.2625f), vec2(1.5f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Top texture", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("bottomTexture", vec2(0.0f, -0.525f), vec2(1.8f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Bottom texture", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("back", vec2(0.0f, -0.7875f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - skyMenuOptions
	_leftWindow->addScreen("skyEditorMenuOptions");
	_leftWindow->getScreen("skyEditorMenuOptions")->addButton("rotationSpeed", vec2(0.0f, 0.63f), vec2(1.8f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Rotation speed", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuOptions")->addButton("lightness", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "lightness", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuOptions")->addButton("color", vec2(0.0f, -0.21f), vec2(0.9f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Color", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuOptions")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuMain
	_leftWindow->addScreen("terrainEditorMenuMain");
	_leftWindow->getScreen("terrainEditorMenuMain")->addButton("create", vec2(0.0f, 0.63f), vec2(1.8f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Create terain", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMain")->addButton("edit", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Edit terrain", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMain")->addButton("remove", vec2(0.0f, -0.21f), vec2(1.8f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Remove terrain", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuChoice
	_leftWindow->addScreen("terrainEditorMenuChoice");
	_leftWindow->getScreen("terrainEditorMenuChoice")->addButton("mesh", vec2(0.0f, 0.475f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "3D mesh", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuChoice")->addButton("blendMap", vec2(0.0f, 0.0f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "BlendMap", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuChoice")->addButton("back", vec2(0.0f, -0.475f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuMesh
	_leftWindow->addScreen("terrainEditorMenuMesh");
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("heightMap", vec2(0.0f, 0.75f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Height map", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("diffuseMap", vec2(0.0f, 0.45f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Diffuse map", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("maxHeight", vec2(0.0f, 0.15f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Max height", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("uvRepeat", vec2(0.0f, -0.15f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "UV repeat", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("lightness", vec2(0.0f, -0.45f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Lightness", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("back", vec2(0.0f, -0.75f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuBlendMap
	_leftWindow->addScreen("terrainEditorMenuBlendMap");
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("blendMap", vec2(0.0f, 0.83f), vec2(1.7f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Blend map", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("red", vec2(0.0f, 0.59f), vec2(1.7f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Red texture", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("green", vec2(0.0f, 0.36f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Green texture", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("blue", vec2(0.0f, 0.13f), vec2(1.7f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Blue texture", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("redRepeat", vec2(0.0f, -0.1f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Red UV", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("greenRepeat", vec2(0.0f, -0.33f), vec2(1.5f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Green UV", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("blueRepeat", vec2(0.0f, -0.56f), vec2(1.3f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Blue UV", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("back", vec2(0.0f, -0.79f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);
	
	// Left-viewport: mainWindow - waterMenuMain
	_leftWindow->addScreen("waterEditorMenuMain");
	_leftWindow->getScreen("waterEditorMenuMain")->addButton("create", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Create water", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMain")->addButton("edit", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Edit water", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMain")->addButton("remove", vec2(0.0f, -0.21f), vec2(1.7f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Remove water", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - waterManagement
	_leftWindow->addScreen("waterEditorMenuChoice");
	_leftWindow->getScreen("waterEditorMenuChoice")->addButton("mesh", vec2(0.0f, 0.63f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "3D mesh", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuChoice")->addButton("effects", vec2(0.0f, 0.21f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Effects", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuChoice")->addButton("options", vec2(0.0f, -0.21f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Options", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuChoice")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - waterMenuMesh
	_leftWindow->addScreen("waterEditorMenuMesh");
	_leftWindow->getScreen("waterEditorMenuMesh")->addButton("position", vec2(0.0f, 0.7f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Position", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMesh")->addButton("size", vec2(0.0f, 0.35f), vec2(0.8f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Size", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMesh")->addButton("up", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Move up", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMesh")->addButton("down", vec2(0.0f, -0.35f), vec2(1.5f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Move down", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMesh")->addButton("back", vec2(0.0f, -0.7f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - waterMenuEffects
	_leftWindow->addScreen("waterEditorMenuEffects");
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("uvRepeat", vec2(0.0f, 0.859f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "UV repeat", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("dudvMap", vec2(0.0f, 0.668f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Dudv map", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("normalMap", vec2(0.0f, 0.477f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Normal map", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("displaceMap", vec2(0.0f, 0.286f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Displace map", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("isReflective", vec2(0.0f, 0.095f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Reflective: OFF", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("isRefractive", vec2(0.0f, -0.096f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Refractive: OFF", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("isWaving", vec2(0.0f, -0.287f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Waving: OFF", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("isRippling", vec2(0.0f, -0.478f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Rippling: OFF", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("isSpecular", vec2(0.0f, -0.669f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Specular: OFF", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("back", vec2(0.0f, -0.86f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - waterMenuOptions
	_leftWindow->addScreen("waterEditorMenuOptions");
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("speed", vec2(0.0f, 0.7875f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Water speed", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("transparency", vec2(0.0f, 0.525f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Transparency", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("color", vec2(0.0f, 0.2625f), vec2(0.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Color", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("specularFactor", vec2(0.0f, 0.0f), vec2(1.75f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Specular factor", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("specularIntensity", vec2(0.0f, -0.2625f), vec2(1.8f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Specular intensity", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("waveHeight", vec2(0.0f, -0.525f), vec2(1.7f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Wave height", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("back", vec2(0.0f, -0.7875f), vec2(1.25f, 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);
}

void WorldEditor::load()
{
	// Camera
	_fe3d.camera_setPosition(vec3(0.0f));
	
	// Enable graphics
	_fe3d.gfx_enableAmbientLighting(vec3(1.0f), 0.75f);
	_fe3d.gfx_enableDirectionalLighting(vec3(1000.0f), vec3(1.0f), 0.75f);

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