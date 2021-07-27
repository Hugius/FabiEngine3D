#include "environment_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

#define CW(text) VPC::calculateTextWidth(text, 0.115f)

constexpr auto TH = 0.0875f;

EnvironmentEditor::EnvironmentEditor(FabiEngine3D& fe3d, EngineGuiManager& gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void EnvironmentEditor::load()
{
	// GUI
	_loadGUI();

	// Camera
	_fe3d.camera_reset();
	
	// Default graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 0.75f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(1000.0f), Vec3(1.0f), 0.75f);
	_fe3d.gfx_enableSpecularLighting();
	_fe3d.gfx_enableNormalMapping();
	_fe3d.gfx_enableMotionBlur(0.1f);

	// Miscellaneous
	_gui.getGlobalScreen()->addTextfield("selectedSkyName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedTerrainName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedWaterName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("environmentEditorControls");
	_isEditorLoaded = true;
	_isInMainMenu = true;
}

void EnvironmentEditor::unload()
{
	// GUI
	_unloadGUI();

	// Default graphics
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableSpecularLighting(true);
	_fe3d.gfx_disableNormalMapping(true);
	_fe3d.gfx_disableMotionBlur(true);

	// Delete entities
	unloadSkyEntities();
	unloadTerrainEntities();
	unloadWaterEntities();

	// Reset editor properties
	_loadedSkyIDs.clear();
	_loadedTerrainIDs.clear();
	_loadedWaterIDs.clear();
	_currentSkyID = "";
	_currentTerrainID = "";
	_currentWaterID = "";
	_isCreatingSky = false;
	_isChoosingSky = false;
	_isEditingSky = false;
	_isDeletingSky = false;
	_isCreatingTerrain = false;
	_isChoosingTerrain = false;
	_isEditingTerrain = false;
	_isDeletingTerrain = false;
	_isCreatingWater = false;
	_isChoosingWater = false;
	_isEditingWater = false;
	_isDeletingWater = false;

	// Miscellaneous
	_gui.getGlobalScreen()->deleteTextfield("selectedSkyName");
	_gui.getGlobalScreen()->deleteTextfield("selectedTerrainName");
	_gui.getGlobalScreen()->deleteTextfield("selectedWaterName");
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	if (_fe3d.camera_isThirdPersonViewEnabled())
	{
		_fe3d.camera_disableThirdPersonView();
	}
	if (_fe3d.misc_isDebugRenderingEnabled())
	{
		_fe3d.misc_disableDebugRendering();
	}
	_isInMainMenu = false;
	_isEditorLoaded = false;
}

void EnvironmentEditor::_loadGUI()
{
	// Private window instance of left viewport
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - environmentEditorMenuMain
	leftWindow->addScreen("environmentEditorMenuMain");
	leftWindow->getScreen("environmentEditorMenuMain")->addButton("sky", Vec2(0.0f, 0.63f), Vec2(CW("Sky"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuMain")->addButton("terrain", Vec2(0.0f, 0.21f), Vec2(CW("Terrain"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuMain")->addButton("water", Vec2(0.0f, -0.21f), Vec2(CW("Water"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuMain")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - environmentEditorMenuSky
	leftWindow->addScreen("environmentEditorMenuSky");
	leftWindow->getScreen("environmentEditorMenuSky")->addButton("add", Vec2(0.0f, 0.63f), Vec2(CW("Add Sky"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Add Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSky")->addButton("edit", Vec2(0.0f, 0.21f), Vec2(CW("Edit Sky"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSky")->addButton("delete", Vec2(0.0f, -0.21f), Vec2(CW("Delete Sky"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSky")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - environmentEditorMenuSkyChoice
	leftWindow->addScreen("environmentEditorMenuSkyChoice");
	leftWindow->getScreen("environmentEditorMenuSkyChoice")->addButton("mesh", Vec2(0.0f, 0.475f), Vec2(CW("3D Mesh"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "3D Mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyChoice")->addButton("options", Vec2(0.0f, 0.0f), Vec2(CW("Options"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Options", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyChoice")->addButton("back", Vec2(0.0f, -0.475f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - environmentEditorMenuSkyMesh
	leftWindow->addScreen("environmentEditorMenuSkyMesh");
	leftWindow->getScreen("environmentEditorMenuSkyMesh")->addButton("leftTexture", Vec2(0.0f, 0.7875f), Vec2(CW("Left Texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Left Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyMesh")->addButton("rightTexture", Vec2(0.0f, 0.525f), Vec2(CW("Right Texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Right Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyMesh")->addButton("frontTexture", Vec2(0.0f, 0.2625f), Vec2(CW("Front Texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Front Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyMesh")->addButton("backTexture", Vec2(0.0f, 0.0f), Vec2(CW("Back Texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Back Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyMesh")->addButton("topTexture", Vec2(0.0f, -0.2625f), Vec2(CW("Top Texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Top Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyMesh")->addButton("bottomTexture", Vec2(0.0f, -0.525f), Vec2(CW("Bottom Texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Bottom Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyMesh")->addButton("back", Vec2(0.0f, -0.7875f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - environmentEditorMenuSkyOptions
	leftWindow->addScreen("environmentEditorMenuSkyOptions");
	leftWindow->getScreen("environmentEditorMenuSkyOptions")->addButton("rotationSpeed", Vec2(0.0f, 0.63f), Vec2(CW("Rotation Speed"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rotation Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyOptions")->addButton("lightness", Vec2(0.0f, 0.21f), Vec2(CW("Lightness"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyOptions")->addButton("color", Vec2(0.0f, -0.21f), Vec2(CW("Color"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyOptions")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - environmentEditorMenuTerrain
	leftWindow->addScreen("environmentEditorMenuTerrain");
	leftWindow->getScreen("environmentEditorMenuTerrain")->addButton("add", Vec2(0.0f, 0.63f), Vec2(CW("Add Terrain"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Add Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrain")->addButton("edit", Vec2(0.0f, 0.21f), Vec2(CW("Edit Terrain"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrain")->addButton("delete", Vec2(0.0f, -0.21f), Vec2(CW("Delete Terrain"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrain")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - environmentEditorMenuTerrainChoice
	leftWindow->addScreen("environmentEditorMenuTerrainChoice");
	leftWindow->getScreen("environmentEditorMenuTerrainChoice")->addButton("mesh", Vec2(0.0f, 0.63f), Vec2(CW("3D Mesh"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "3D Mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainChoice")->addButton("blendMap", Vec2(0.0f, 0.21f), Vec2(CW("BlendMap"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "BlendMap", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainChoice")->addButton("lighting", Vec2(0.0f, -0.21f), Vec2(CW("Lighting"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lighting", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainChoice")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - environmentEditorMenuTerrainMesh
	leftWindow->addScreen("environmentEditorMenuTerrainMesh");
	leftWindow->getScreen("environmentEditorMenuTerrainMesh")->addButton("heightMap", Vec2(0.0f, 0.7f), Vec2(CW("Height Map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Height Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainMesh")->addButton("diffuseMap", Vec2(0.0f, 0.35f), Vec2(CW("Diffuse Map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Diffuse Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainMesh")->addButton("maxHeight", Vec2(0.0f, 0.0f), Vec2(CW("Max Height"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Max Height", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainMesh")->addButton("uvRepeat", Vec2(0.0f, -0.35f), Vec2(CW("UV Repeat"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "UV Repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainMesh")->addButton("back", Vec2(0.0f, -0.7f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - environmentEditorMenuTerrainBlendMap
	leftWindow->addScreen("environmentEditorMenuTerrainBlendMap");
	leftWindow->getScreen("environmentEditorMenuTerrainBlendMap")->addButton("blendMap", Vec2(0.0f, 0.83f), Vec2(CW("Blend Map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blend Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainBlendMap")->addButton("red", Vec2(0.0f, 0.59f), Vec2(CW("Red Texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Red Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainBlendMap")->addButton("green", Vec2(0.0f, 0.36f), Vec2(CW("Green Texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Green Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainBlendMap")->addButton("blue", Vec2(0.0f, 0.13f), Vec2(CW("Blue Texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blue Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainBlendMap")->addButton("redRepeat", Vec2(0.0f, -0.13f), Vec2(CW("Red UV"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Red UV", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainBlendMap")->addButton("greenRepeat", Vec2(0.0f, -0.36f), Vec2(CW("Green UV"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Green UV", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainBlendMap")->addButton("blueRepeat", Vec2(0.0f, -0.59f), Vec2(CW("Blue UV"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blue UV", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainBlendMap")->addButton("back", Vec2(0.0f, -0.83f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - environmentEditorMenuTerrainLighting
	leftWindow->addScreen("environmentEditorMenuTerrainLighting");
	leftWindow->getScreen("environmentEditorMenuTerrainLighting")->addButton("normalMap", Vec2(0.0f, 0.8f), Vec2(CW("Normal Map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainLighting")->addButton("normalMapR", Vec2(0.0f, 0.6f), Vec2(CW("Red Normal Map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Red Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainLighting")->addButton("normalMapG", Vec2(0.0f, 0.4f), Vec2(CW("Green Normal Map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Green Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainLighting")->addButton("normalMapB", Vec2(0.0f, 0.2f), Vec2(CW("Blue Normal Map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blue Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainLighting")->addButton("isSpecular", Vec2(0.0f, 0.0f), Vec2(CW("Specular: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainLighting")->addButton("specularFactor", Vec2(0.0f, -0.2f), Vec2(CW("Spec Factor"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec Factor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainLighting")->addButton("specularIntensity", Vec2(0.0f, -0.4f), Vec2(CW("Spec Intensity"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainLighting")->addButton("lightness", Vec2(0.0f, -0.6f), Vec2(CW("Lightness"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainLighting")->addButton("back", Vec2(0.0f, -0.8f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - environmentEditorMenuWater
	leftWindow->addScreen("environmentEditorMenuWater");
	leftWindow->getScreen("environmentEditorMenuWater")->addButton("add", Vec2(0.0f, 0.63f), Vec2(CW("Add Water"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Add Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWater")->addButton("edit", Vec2(0.0f, 0.21f), Vec2(CW("Edit Water"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWater")->addButton("delete", Vec2(0.0f, -0.21f), Vec2(CW("Delete Water"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWater")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - environmentEditorMenuWaterChoice
	leftWindow->addScreen("environmentEditorMenuWaterChoice");
	leftWindow->getScreen("environmentEditorMenuWaterChoice")->addButton("terrain", Vec2(0.0f, 0.7f), Vec2(CW("Terrain"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterChoice")->addButton("mesh", Vec2(0.0f, 0.35f), Vec2(CW("3D mesh"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "3D mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterChoice")->addButton("effects", Vec2(0.0f, 0.0f), Vec2(CW("Effects"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Effects", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterChoice")->addButton("options", Vec2(0.0f, -0.35f), Vec2(CW("Options"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Options", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterChoice")->addButton("back", Vec2(0.0f, -0.7f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - environmentEditorMenuWaterMesh
	leftWindow->addScreen("environmentEditorMenuWaterMesh");
	leftWindow->getScreen("environmentEditorMenuWaterMesh")->addButton("position", Vec2(0.0f, 0.7f), Vec2(CW("Position"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Position", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterMesh")->addButton("size", Vec2(0.0f, 0.35f), Vec2(CW("Size"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterMesh")->addButton("up", Vec2(0.0f, 0.0f), Vec2(CW("Move Up"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Move Up", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterMesh")->addButton("down", Vec2(0.0f, -0.35f), Vec2(CW("Move Down"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Move Down", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterMesh")->addButton("back", Vec2(0.0f, -0.7f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - environmentEditorMenuWaterEffects
	leftWindow->addScreen("environmentEditorMenuWaterEffects");
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->addButton("uvRepeat", Vec2(0.0f, 0.859f), Vec2(CW("UV Repeat"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "UV Repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->addButton("dudvMap", Vec2(0.0f, 0.668f), Vec2(CW("Dudv Map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Dudv Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->addButton("normalMap", Vec2(0.0f, 0.477f), Vec2(CW("Normal Map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->addButton("displaceMap", Vec2(0.0f, 0.286f), Vec2(CW("Displace Map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Displace Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->addButton("isReflective", Vec2(0.0f, 0.095f), Vec2(CW("Reflective: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflective: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->addButton("isRefractive", Vec2(0.0f, -0.096f), Vec2(CW("Refractive: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Refractive: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->addButton("isWaving", Vec2(0.0f, -0.287f), Vec2(CW("Waving: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Waving: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->addButton("isRippling", Vec2(0.0f, -0.478f), Vec2(CW("Rippling: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rippling: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->addButton("isSpecular", Vec2(0.0f, -0.669f), Vec2(CW("Specular: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->addButton("back", Vec2(0.0f, -0.86f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - environmentEditorMenuWaterOptions
	leftWindow->addScreen("environmentEditorMenuWaterOptions");
	leftWindow->getScreen("environmentEditorMenuWaterOptions")->addButton("speed", Vec2(0.0f, 0.83f), Vec2(CW("Water Speed"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Water Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterOptions")->addButton("transparency", Vec2(0.0f, 0.59f), Vec2(CW("Transparency"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Transparency", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterOptions")->addButton("color", Vec2(0.0f, 0.36f), Vec2(CW("Color"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterOptions")->addButton("specularFactor", Vec2(0.0f, 0.13f), Vec2(CW("Spec Factor"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec Factor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterOptions")->addButton("specularIntensity", Vec2(0.0f, -0.13f), Vec2(CW("Spec Intensity"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterOptions")->addButton("waveHeight", Vec2(0.0f, -0.36f), Vec2(CW("Wave Height"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Wave Height", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterOptions")->addButton("quality", Vec2(0.0f, -0.59f), Vec2(CW("Quality"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Quality", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterOptions")->addButton("back", Vec2(0.0f, -0.83f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void EnvironmentEditor::_unloadGUI()
{
	auto leftWindow = _gui.getViewport("left")->getWindow("main");
	leftWindow->deleteScreen("environmentEditorMenuMain");
	leftWindow->deleteScreen("environmentEditorMenuSky");
	leftWindow->deleteScreen("environmentEditorMenuSkyChoice");
	leftWindow->deleteScreen("environmentEditorMenuSkyMesh");
	leftWindow->deleteScreen("environmentEditorMenuSkyOptions");
	leftWindow->deleteScreen("environmentEditorMenuTerrain");
	leftWindow->deleteScreen("environmentEditorMenuTerrainChoice");
	leftWindow->deleteScreen("environmentEditorMenuTerrainMesh");
	leftWindow->deleteScreen("environmentEditorMenuTerrainBlendMap");
	leftWindow->deleteScreen("environmentEditorMenuTerrainLighting");
	leftWindow->deleteScreen("environmentEditorMenuWater");
	leftWindow->deleteScreen("environmentEditorMenuWaterChoice");
	leftWindow->deleteScreen("environmentEditorMenuWaterMesh");
	leftWindow->deleteScreen("environmentEditorMenuWaterEffects");
	leftWindow->deleteScreen("environmentEditorMenuWaterOptions");
}