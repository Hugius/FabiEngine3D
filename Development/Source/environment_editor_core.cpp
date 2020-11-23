#include "environment_editor.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVPC::calcTextWidth(text, 0.15f, 1.8f)

EnvironmentEditor::EnvironmentEditor(FabiEngine3D& fe3d, EngineGuiManager& gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void EnvironmentEditor::initializeGUI()
{
	// Private window instance of left viewport
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - environmentEditorMenu
	leftWindow->addScreen("environmentEditorMenu");
	leftWindow->getScreen("environmentEditorMenu")->addButton("sky", Vec2(0.0f, 0.63f), Vec2(GW("Sky"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Sky", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("environmentEditorMenu")->addButton("terrain", Vec2(0.0f, 0.21f), Vec2(GW("Terrain"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Terrain", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("environmentEditorMenu")->addButton("water", Vec2(0.0f, -0.21f), Vec2(GW("Water"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Water", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("environmentEditorMenu")->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - skyMenuMain
	leftWindow->addScreen("skyEditorMenuMain");
	leftWindow->getScreen("skyEditorMenuMain")->addButton("create", Vec2(0.0f, 0.63f), Vec2(GW("Create sky"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Create sky", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("skyEditorMenuMain")->addButton("edit", Vec2(0.0f, 0.21f), Vec2(GW("Edit sky"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit sky", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("skyEditorMenuMain")->addButton("delete", Vec2(0.0f, -0.21f), Vec2(GW("Remove sky"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Remove sky", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("skyEditorMenuMain")->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - skyMenuChoice
	leftWindow->addScreen("skyEditorMenuChoice");
	leftWindow->getScreen("skyEditorMenuChoice")->addButton("mesh", Vec2(0.0f, 0.475f), Vec2(GW("3D mesh"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "3D mesh", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("skyEditorMenuChoice")->addButton("options", Vec2(0.0f, 0.0f), Vec2(GW("Options"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Options", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("skyEditorMenuChoice")->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - skyMenuMesh
	leftWindow->addScreen("skyEditorMenuMesh");
	leftWindow->getScreen("skyEditorMenuMesh")->addButton("leftTexture", Vec2(0.0f, 0.7875f), Vec2(GW("Left texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Left texture", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("skyEditorMenuMesh")->addButton("rightTexture", Vec2(0.0f, 0.525f), Vec2(GW("Right texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Right texture", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("skyEditorMenuMesh")->addButton("frontTexture", Vec2(0.0f, 0.2625f), Vec2(GW("Front texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Front texture", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("skyEditorMenuMesh")->addButton("backTexture", Vec2(0.0f, 0.0f), Vec2(GW("Back texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Back texture", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("skyEditorMenuMesh")->addButton("topTexture", Vec2(0.0f, -0.2625f), Vec2(GW("Top texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Top texture", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("skyEditorMenuMesh")->addButton("bottomTexture", Vec2(0.0f, -0.525f), Vec2(GW("Bottom texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Bottom texture", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("skyEditorMenuMesh")->addButton("back", Vec2(0.0f, -0.7875f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - skyMenuOptions
	leftWindow->addScreen("skyEditorMenuOptions");
	leftWindow->getScreen("skyEditorMenuOptions")->addButton("rotationSpeed", Vec2(0.0f, 0.63f), Vec2(GW("Rotation speed"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Rotation speed", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("skyEditorMenuOptions")->addButton("lightness", Vec2(0.0f, 0.21f), Vec2(GW("Lightness"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Lightness", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("skyEditorMenuOptions")->addButton("color", Vec2(0.0f, -0.21f), Vec2(GW("Color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Color", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("skyEditorMenuOptions")->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuMain
	leftWindow->addScreen("terrainEditorMenuMain");
	leftWindow->getScreen("terrainEditorMenuMain")->addButton("create", Vec2(0.0f, 0.63f), Vec2(GW("Create terain"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Create terain", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuMain")->addButton("edit", Vec2(0.0f, 0.21f), Vec2(GW("Edit terrain"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit terrain", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuMain")->addButton("delete", Vec2(0.0f, -0.21f), Vec2(GW("Remove terrain"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Remove terrain", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuMain")->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuChoice
	leftWindow->addScreen("terrainEditorMenuChoice");
	leftWindow->getScreen("terrainEditorMenuChoice")->addButton("mesh", Vec2(0.0f, 0.475f), Vec2(GW("3D mesh"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "3D mesh", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuChoice")->addButton("blendMap", Vec2(0.0f, 0.0f), Vec2(GW("BlendMap"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "BlendMap", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuChoice")->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuMesh
	leftWindow->addScreen("terrainEditorMenuMesh");
	leftWindow->getScreen("terrainEditorMenuMesh")->addButton("heightMap", Vec2(0.0f, 0.83f), Vec2(GW("Height map"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Height map", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuMesh")->addButton("diffuseMap", Vec2(0.0f, 0.59f), Vec2(GW("Diffuse map"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Diffuse map", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuMesh")->addButton("maxHeight", Vec2(0.0f, 0.36f), Vec2(GW("Max height"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Max height", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuMesh")->addButton("uvRepeat", Vec2(0.0f, 0.13f), Vec2(GW("UV repeat"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "UV repeat", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuMesh")->addButton("isSpecular", Vec2(0.0f, -0.1f), Vec2(GW("Specular: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuMesh")->addButton("specularIntensity", Vec2(0.0f, -0.33f), Vec2(GW("Specular intensity"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular intensity", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuMesh")->addButton("lightness", Vec2(0.0f, -0.56f), Vec2(GW("Lightness"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Lightness", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuMesh")->addButton("back", Vec2(0.0f, -0.79f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - terrainMenuBlendMap
	leftWindow->addScreen("terrainEditorMenuBlendMap");
	leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("blendMap", Vec2(0.0f, 0.83f), Vec2(GW("Blend map"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Blend map", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("red", Vec2(0.0f, 0.59f), Vec2(GW("Red texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Red texture", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("green", Vec2(0.0f, 0.36f), Vec2(GW("Green texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Green texture", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("blue", Vec2(0.0f, 0.13f), Vec2(GW("Blue texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Blue texture", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("redRepeat", Vec2(0.0f, -0.1f), Vec2(GW("Red UV"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Red UV", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("greenRepeat", Vec2(0.0f, -0.33f), Vec2(GW("Green UV"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Green UV", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("blueRepeat", Vec2(0.0f, -0.56f), Vec2(GW("Blue UV"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Blue UV", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("back", Vec2(0.0f, -0.79f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - waterMenuMain
	leftWindow->addScreen("waterEditorMenuMain");
	leftWindow->getScreen("waterEditorMenuMain")->addButton("create", Vec2(0.0f, 0.63f), Vec2(GW("Create water"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Create water", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuMain")->addButton("edit", Vec2(0.0f, 0.21f), Vec2(GW("Edit water"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit water", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuMain")->addButton("delete", Vec2(0.0f, -0.21f), Vec2(GW("Remove water"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Remove water", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuMain")->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - waterManagement
	leftWindow->addScreen("waterEditorMenuChoice");
	leftWindow->getScreen("waterEditorMenuChoice")->addButton("terrain", Vec2(0.0f, 0.7f), Vec2(GW("Terrain"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Terrain", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuChoice")->addButton("mesh", Vec2(0.0f, 0.35f), Vec2(GW("3D mesh"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "3D mesh", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuChoice")->addButton("effects", Vec2(0.0f, 0.0f), Vec2(GW("Effects"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Effects", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuChoice")->addButton("options", Vec2(0.0f, -0.35f), Vec2(GW("Options"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Options", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuChoice")->addButton("back", Vec2(0.0f, -0.7f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - waterMenuMesh
	leftWindow->addScreen("waterEditorMenuMesh");
	leftWindow->getScreen("waterEditorMenuMesh")->addButton("position", Vec2(0.0f, 0.7f), Vec2(GW("Position"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Position", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuMesh")->addButton("size", Vec2(0.0f, 0.35f), Vec2(GW("Size"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Size", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuMesh")->addButton("up", Vec2(0.0f, 0.0f), Vec2(GW("Move up"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Move up", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuMesh")->addButton("down", Vec2(0.0f, -0.35f), Vec2(GW("Move down"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Move down", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuMesh")->addButton("back", Vec2(0.0f, -0.7f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - waterMenuEffects
	leftWindow->addScreen("waterEditorMenuEffects");
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("uvRepeat", Vec2(0.0f, 0.859f), Vec2(GW("UV repeat"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "UV repeat", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("dudvMap", Vec2(0.0f, 0.668f), Vec2(GW("Dudv map"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Dudv map", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("normalMap", Vec2(0.0f, 0.477f), Vec2(GW("Normal map"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Normal map", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("displaceMap", Vec2(0.0f, 0.286f), Vec2(GW("Displace map"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Displace map", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("isReflective", Vec2(0.0f, 0.095f), Vec2(GW("Reflective: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Reflective: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("isRefractive", Vec2(0.0f, -0.096f), Vec2(GW("Refractive: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Refractive: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("isWaving", Vec2(0.0f, -0.287f), Vec2(GW("Waving: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Waving: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("isRippling", Vec2(0.0f, -0.478f), Vec2(GW("Rippling: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Rippling: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("isSpecular", Vec2(0.0f, -0.669f), Vec2(GW("Specular: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("back", Vec2(0.0f, -0.86f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - waterMenuOptions
	leftWindow->addScreen("waterEditorMenuOptions");
	leftWindow->getScreen("waterEditorMenuOptions")->addButton("speed", Vec2(0.0f, 0.7875f), Vec2(GW("Water speed"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Water speed", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuOptions")->addButton("transparency", Vec2(0.0f, 0.525f), Vec2(GW("Transparency"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Transparency", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuOptions")->addButton("color", Vec2(0.0f, 0.2625f), Vec2(GW("Color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Color", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuOptions")->addButton("specularFactor", Vec2(0.0f, 0.0f), Vec2(GW("Specular factor"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular factor", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuOptions")->addButton("specularIntensity", Vec2(0.0f, -0.2625f), Vec2(GW("Specular intensity"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular intensity", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuOptions")->addButton("waveHeight", Vec2(0.0f, -0.525f), Vec2(GW("Wave height"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Wave height", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("waterEditorMenuOptions")->addButton("back", Vec2(0.0f, -0.7875f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
}

void EnvironmentEditor::load()
{
	// Default camera
	_fe3d.camera_load(90.0f, 0.1f, 10000.0f, Vec3(0.0f));
	
	// Enable graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 0.75f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(1000.0f), Vec3(1.0f), 0.75f);
	_fe3d.gfx_enableSpecularLighting();
	_fe3d.gfx_enableWaterEffects();

	// Core
	loadSkyEntitiesFromFile();
	loadTerrainEntitiesFromFile();
	loadWaterEntitiesFromFile();

	// Miscellaneous
	_gui.getGlobalScreen()->addTextfield("selectedSkyName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedTerrainName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedWaterName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_fe3d.input_clearKeyToggles();
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("environmentEditorControls");
	_isLoaded = true;
}

void EnvironmentEditor::save()
{
	saveSkyEntitiesToFile();
	saveTerrainEntitiesToFile();
	saveWaterEntitiesToFile();
}

void EnvironmentEditor::unload()
{
	// Disable graphics
	_fe3d.gfx_disableAmbientLighting();
	_fe3d.gfx_disableDirectionalLighting();
	_fe3d.gfx_disableSpecularLighting();
	_fe3d.gfx_disableWaterEffects();

	// Delete entities
	unloadSkyEntities();
	unloadTerrainEntities();
	unloadWaterEntities();

	// Reset variables
	_skyNames.clear();
	_terrainNames.clear();
	_waterNames.clear();
	_currentEnvironmentType = EnvironmentType::NONE;
	_cameraRotationSpeed = 0.0f;
	_totalCameraRotation = 0.0f;
	_currentSkyID = "";
	_hoveredSkyID = "";
	_currentTerrainID = "";
	_hoveredTerrainID = "";
	_currentWaterID = "";
	_hoveredWaterID = "";
	_skyCreationEnabled = false;
	_skyChoosingEnabled = false;
	_skyEditingEnabled = false;
	_skyRemovalEnabled = false;
	_terrainCreationEnabled = false;
	_terrainChoosingEnabled = false;
	_terrainEditingEnabled = false;
	_terrainRemovalEnabled = false;
	_waterCreationEnabled = false;
	_waterChoosingEnabled = false;
	_waterEditingEnabled = false;
	_waterRemovalEnabled = false;

	// Miscellaneous
	_gui.getGlobalScreen()->deleteTextfield("selectedSkyName");
	_gui.getGlobalScreen()->deleteTextfield("selectedTerrainName");
	_gui.getGlobalScreen()->deleteTextfield("selectedWaterName");
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	_isLoaded = false;
}