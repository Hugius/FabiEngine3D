#include "world_editor.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVPC::calcTextWidth(text, 0.15f, 1.8f)

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
	_leftWindow->getScreen("worldEditorMenu")->addButton("sky", vec2(0.0f, 0.63f), vec2(GW("Sky"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Sky", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("worldEditorMenu")->addButton("terrain", vec2(0.0f, 0.21), vec2(GW("Terrain"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Terrain", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("worldEditorMenu")->addButton("water", vec2(0.0f, -0.21), vec2(GW("Water"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Water", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("worldEditorMenu")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - skyMenuMain
	_leftWindow->addScreen("skyEditorMenuMain");
	_leftWindow->getScreen("skyEditorMenuMain")->addButton("create", vec2(0.0f, 0.63f), vec2(GW("Create sky"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Create sky", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMain")->addButton("edit", vec2(0.0f, 0.21f), vec2(GW("Edit sky"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit sky", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMain")->addButton("remove", vec2(0.0f, -0.21f), vec2(GW("Remove sky"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Remove sky", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - skyMenuChoice
	_leftWindow->addScreen("skyEditorMenuChoice");
	_leftWindow->getScreen("skyEditorMenuChoice")->addButton("mesh", vec2(0.0f, 0.475f), vec2(GW("3D mesh"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "3D mesh", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuChoice")->addButton("options", vec2(0.0f, 0.0f), vec2(GW("Options"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Options", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuChoice")->addButton("back", vec2(0.0f, -0.475f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - skyMenuMesh
	_leftWindow->addScreen("skyEditorMenuMesh");
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("leftTexture", vec2(0.0f, 0.7875f), vec2(GW("Left texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Left texture", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("rightTexture", vec2(0.0f, 0.525f), vec2(GW("Right texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Right texture", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("frontTexture", vec2(0.0f, 0.2625f), vec2(GW("Front texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Front texture", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("backTexture", vec2(0.0f, 0.0f), vec2(GW("Back texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Back texture", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("topTexture", vec2(0.0f, -0.2625f), vec2(GW("Top texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Top texture", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("bottomTexture", vec2(0.0f, -0.525f), vec2(GW("Bottom texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Bottom texture", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuMesh")->addButton("back", vec2(0.0f, -0.7875f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - skyMenuOptions
	_leftWindow->addScreen("skyEditorMenuOptions");
	_leftWindow->getScreen("skyEditorMenuOptions")->addButton("rotationSpeed", vec2(0.0f, 0.63f), vec2(GW("Rotation speed"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Rotation speed", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuOptions")->addButton("lightness", vec2(0.0f, 0.21f), vec2(GW("Lightness"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Lightness", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuOptions")->addButton("color", vec2(0.0f, -0.21f), vec2(GW("Color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Color", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("skyEditorMenuOptions")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuMain
	_leftWindow->addScreen("terrainEditorMenuMain");
	_leftWindow->getScreen("terrainEditorMenuMain")->addButton("create", vec2(0.0f, 0.63f), vec2(GW("Create terain"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Create terain", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMain")->addButton("edit", vec2(0.0f, 0.21f), vec2(GW("Edit terrain"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit terrain", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMain")->addButton("remove", vec2(0.0f, -0.21f), vec2(GW("Remove terrain"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Remove terrain", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuChoice
	_leftWindow->addScreen("terrainEditorMenuChoice");
	_leftWindow->getScreen("terrainEditorMenuChoice")->addButton("mesh", vec2(0.0f, 0.475f), vec2(GW("3D mesh"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "3D mesh", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuChoice")->addButton("blendMap", vec2(0.0f, 0.0f), vec2(GW("BlendMap"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "BlendMap", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuChoice")->addButton("back", vec2(0.0f, -0.475f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuMesh
	_leftWindow->addScreen("terrainEditorMenuMesh");
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("heightMap", vec2(0.0f, 0.83f), vec2(GW("Height map"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Height map", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("diffuseMap", vec2(0.0f, 0.59f), vec2(GW("Diffuse map"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Diffuse map", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("maxHeight", vec2(0.0f, 0.36f), vec2(GW("Max height"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Max height", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("uvRepeat", vec2(0.0f, 0.13f), vec2(GW("UV repeat"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "UV repeat", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("isSpecular", vec2(0.0f, -0.1f), vec2(GW("Specular: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular: OFF", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("specularIntensity", vec2(0.0f, -0.33f), vec2(GW("Specular intensity"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular intensity", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("lightness", vec2(0.0f, -0.56f), vec2(GW("Lightness"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Lightness", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuMesh")->addButton("back", vec2(0.0f, -0.79f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuBlendMap
	_leftWindow->addScreen("terrainEditorMenuBlendMap");
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("blendMap", vec2(0.0f, 0.83f), vec2(GW("Blend map"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Blend map", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("red", vec2(0.0f, 0.59f), vec2(GW("Red texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Red texture", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("green", vec2(0.0f, 0.36f), vec2(GW("Green texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Green texture", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("blue", vec2(0.0f, 0.13f), vec2(GW("Blue texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Blue texture", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("redRepeat", vec2(0.0f, -0.1f), vec2(GW("Red UV"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Red UV", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("greenRepeat", vec2(0.0f, -0.33f), vec2(GW("Green UV"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Green UV", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("blueRepeat", vec2(0.0f, -0.56f), vec2(GW("Blue UV"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Blue UV", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("back", vec2(0.0f, -0.79f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - waterMenuMain
	_leftWindow->addScreen("waterEditorMenuMain");
	_leftWindow->getScreen("waterEditorMenuMain")->addButton("create", vec2(0.0f, 0.63f), vec2(GW("Create water"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Create water", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMain")->addButton("edit", vec2(0.0f, 0.21f), vec2(GW("Edit water"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit water", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMain")->addButton("remove", vec2(0.0f, -0.21f), vec2(GW("Remove water"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Remove water", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - waterManagement
	_leftWindow->addScreen("waterEditorMenuChoice");
	_leftWindow->getScreen("waterEditorMenuChoice")->addButton("mesh", vec2(0.0f, 0.63f), vec2(GW("3D mesh"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "3D mesh", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuChoice")->addButton("effects", vec2(0.0f, 0.21f), vec2(GW("Effects"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Effects", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuChoice")->addButton("options", vec2(0.0f, -0.21f), vec2(GW("Options"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Options", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuChoice")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - waterMenuMesh
	_leftWindow->addScreen("waterEditorMenuMesh");
	_leftWindow->getScreen("waterEditorMenuMesh")->addButton("position", vec2(0.0f, 0.7f), vec2(GW("Position"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Position", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMesh")->addButton("size", vec2(0.0f, 0.35f), vec2(GW("Size"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Size", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMesh")->addButton("up", vec2(0.0f, 0.0f), vec2(GW("Move up"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Move up", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMesh")->addButton("down", vec2(0.0f, -0.35f), vec2(GW("Move down"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Move down", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuMesh")->addButton("back", vec2(0.0f, -0.7f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - waterMenuEffects
	_leftWindow->addScreen("waterEditorMenuEffects");
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("uvRepeat", vec2(0.0f, 0.859f), vec2(GW("UV repeat"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "UV repeat", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("dudvMap", vec2(0.0f, 0.668f), vec2(GW("Dudv map"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Dudv map", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("normalMap", vec2(0.0f, 0.477f), vec2(GW("Normal map"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Normal map", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("displaceMap", vec2(0.0f, 0.286f), vec2(GW("Displace map"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Displace map", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("isReflective", vec2(0.0f, 0.095f), vec2(GW("Reflective: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Reflective: OFF", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("isRefractive", vec2(0.0f, -0.096f), vec2(GW("Refractive: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Refractive: OFF", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("isWaving", vec2(0.0f, -0.287f), vec2(GW("Waving: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Waving: OFF", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("isRippling", vec2(0.0f, -0.478f), vec2(GW("Rippling: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Rippling: OFF", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("isSpecular", vec2(0.0f, -0.669f), vec2(GW("Specular: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular: OFF", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuEffects")->addButton("back", vec2(0.0f, -0.86f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - waterMenuOptions
	_leftWindow->addScreen("waterEditorMenuOptions");
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("speed", vec2(0.0f, 0.7875f), vec2(GW("Water speed"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Water speed", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("transparency", vec2(0.0f, 0.525f), vec2(GW("Transparency"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Transparency", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("color", vec2(0.0f, 0.2625f), vec2(GW("Color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Color", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("specularFactor", vec2(0.0f, 0.0f), vec2(GW("Specular factor"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular factor", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("specularIntensity", vec2(0.0f, -0.2625f), vec2(GW("Specular intensity"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular intensity", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("waveHeight", vec2(0.0f, -0.525f), vec2(GW("Wave height"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Wave height", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("waterEditorMenuOptions")->addButton("back", vec2(0.0f, -0.7875f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
}

void WorldEditor::load()
{
	// Default camera
	_fe3d.camera_load(90.0f, 0.1f, 10000.0f, vec3(0.0f));
	
	// Enable graphics
	_fe3d.gfx_enableAmbientLighting(vec3(1.0f), 0.75f);
	_fe3d.gfx_enableDirectionalLighting(vec3(1000.0f), vec3(1.0f), 0.75f);
	_fe3d.gfx_enableSpecularLighting();
	_fe3d.gfx_enableWaterEffects();

	// Core
	loadSkyEntity();
	loadTerrainEntity();
	loadWaterEntity();

	// Miscellaneous
	_gui->getGlobalScreen()->addTextfield("selectedSkyName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_gui->getGlobalScreen()->addTextfield("selectedTerrainName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_gui->getGlobalScreen()->addTextfield("selectedWaterName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_isLoaded = true;
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
	_fe3d.gfx_disableSpecularLighting();
	_fe3d.gfx_disableWaterEffects();

	// Delete skies
	for (auto& name : _skyNames)
	{
		_fe3d.skyEntity_delete(name);
	}

	// Delete terrains
	for (auto& name : _terrainNames)
	{
		_fe3d.terrainEntity_delete(name);
	}

	// Delete waters
	for (auto& name : _waterNames)
	{
		_fe3d.waterEntity_delete(name);
	}

	// Reset variables
	_currentWorldPart = WorldPart::NONE;
	_cameraRotationSpeed = 0.0f;
	_totalCameraRotation = 0.0f;

	// Miscellaneous
	_gui->getGlobalScreen()->deleteTextfield("selectedSkyName");
	_gui->getGlobalScreen()->deleteTextfield("selectedTerrainName");
	_gui->getGlobalScreen()->deleteTextfield("selectedWaterName");
	_isLoaded = false;
}