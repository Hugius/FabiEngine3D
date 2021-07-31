#include "environment_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

#define TW(text) VPC::calculateTextWidth(text, CW)

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
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 1.0f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(1000.0f), Vec3(1.0f), 3.0f);
	_fe3d.gfx_enableSpecularLighting();
	_fe3d.gfx_enableMotionBlur(0.1f);

	// Miscellaneous
	_gui.getGlobalScreen()->createTextfield("selectedSkyName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->createTextfield("selectedTerrainName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->createTextfield("selectedWaterName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
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
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: environmentEditorMenuMain
	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("environmentEditorMenuMain");
	leftWindow->getScreen("environmentEditorMenuMain")->createButton("sky", Vec2(0.0f, positions[0]), Vec2(TW("Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuMain")->createButton("terrain", Vec2(0.0f, positions[1]), Vec2(TW("Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuMain")->createButton("water", Vec2(0.0f, positions[2]), Vec2(TW("Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuMain")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: environmentEditorMenuSky
	positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("environmentEditorMenuSky");
	leftWindow->getScreen("environmentEditorMenuSky")->createButton("add", Vec2(0.0f, positions[0]), Vec2(TW("Add Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Add Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSky")->createButton("edit", Vec2(0.0f, positions[1]), Vec2(TW("Edit Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSky")->createButton("delete", Vec2(0.0f, positions[2]), Vec2(TW("Delete Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSky")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: environmentEditorMenuSkyChoice
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("environmentEditorMenuSkyChoice");
	leftWindow->getScreen("environmentEditorMenuSkyChoice")->createButton("mesh", Vec2(0.0f, positions[0]), Vec2(TW("3D Mesh"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "3D Mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyChoice")->createButton("options", Vec2(0.0f, positions[1]), Vec2(TW("Options"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Options", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyChoice")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: environmentEditorMenuSkyMesh
	positions = VPC::calculateButtonPositions(7, CH);
	leftWindow->createScreen("environmentEditorMenuSkyMesh");
	leftWindow->getScreen("environmentEditorMenuSkyMesh")->createButton("leftTexture", Vec2(0.0f, positions[0]), Vec2(TW("Left Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Left Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyMesh")->createButton("rightTexture", Vec2(0.0f, positions[1]), Vec2(TW("Right Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Right Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyMesh")->createButton("frontTexture", Vec2(0.0f, positions[2]), Vec2(TW("Front Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Front Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyMesh")->createButton("backTexture", Vec2(0.0f, positions[3]), Vec2(TW("Back Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Back Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyMesh")->createButton("topTexture", Vec2(0.0f, positions[4]), Vec2(TW("Top Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Top Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyMesh")->createButton("bottomTexture", Vec2(0.0f, positions[5]), Vec2(TW("Bottom Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Bottom Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyMesh")->createButton("back", Vec2(0.0f, positions[6]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: environmentEditorMenuSkyOptions
	positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("environmentEditorMenuSkyOptions");
	leftWindow->getScreen("environmentEditorMenuSkyOptions")->createButton("rotationSpeed", Vec2(0.0f, positions[0]), Vec2(TW("Rotation Speed"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rotation Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyOptions")->createButton("lightness", Vec2(0.0f, positions[1]), Vec2(TW("Lightness"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyOptions")->createButton("color", Vec2(0.0f, positions[2]), Vec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuSkyOptions")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: environmentEditorMenuTerrain
	positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("environmentEditorMenuTerrain");
	leftWindow->getScreen("environmentEditorMenuTerrain")->createButton("add", Vec2(0.0f, positions[0]), Vec2(TW("Add Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Add Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrain")->createButton("edit", Vec2(0.0f, positions[1]), Vec2(TW("Edit Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrain")->createButton("delete", Vec2(0.0f, positions[2]), Vec2(TW("Delete Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrain")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: environmentEditorMenuTerrainChoice
	positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("environmentEditorMenuTerrainChoice");
	leftWindow->getScreen("environmentEditorMenuTerrainChoice")->createButton("mesh", Vec2(0.0f, positions[0]), Vec2(TW("3D Mesh"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "3D Mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainChoice")->createButton("blendMap", Vec2(0.0f, positions[1]), Vec2(TW("BlendMap"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "BlendMap", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainChoice")->createButton("lighting", Vec2(0.0f, positions[2]), Vec2(TW("Lighting"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lighting", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainChoice")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: environmentEditorMenuTerrainMesh
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("environmentEditorMenuTerrainMesh");
	leftWindow->getScreen("environmentEditorMenuTerrainMesh")->createButton("heightMap", Vec2(0.0f, positions[0]), Vec2(TW("Height Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Height Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainMesh")->createButton("diffuseMap", Vec2(0.0f, positions[1]), Vec2(TW("Diffuse Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Diffuse Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainMesh")->createButton("maxHeight", Vec2(0.0f, positions[2]), Vec2(TW("Max Height"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Max Height", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainMesh")->createButton("uvRepeat", Vec2(0.0f, positions[3]), Vec2(TW("UV Repeat"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "UV Repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainMesh")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: environmentEditorMenuTerrainBlendMap
	positions = VPC::calculateButtonPositions(8, CH);
	leftWindow->createScreen("environmentEditorMenuTerrainBlendMap");
	leftWindow->getScreen("environmentEditorMenuTerrainBlendMap")->createButton("blendMap", Vec2(0.0f, positions[0]), Vec2(TW("Blend Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blend Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainBlendMap")->createButton("red", Vec2(0.0f, positions[1]), Vec2(TW("Red Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Red Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainBlendMap")->createButton("green", Vec2(0.0f, positions[2]), Vec2(TW("Green Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Green Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainBlendMap")->createButton("blue", Vec2(0.0f, positions[3]), Vec2(TW("Blue Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blue Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainBlendMap")->createButton("redRepeat", Vec2(0.0f, positions[4]), Vec2(TW("Red UV"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Red UV", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainBlendMap")->createButton("greenRepeat", Vec2(0.0f, positions[5]), Vec2(TW("Green UV"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Green UV", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainBlendMap")->createButton("blueRepeat", Vec2(0.0f, positions[6]), Vec2(TW("Blue UV"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blue UV", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainBlendMap")->createButton("back", Vec2(0.0f, positions[7]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: environmentEditorMenuTerrainLighting
	positions = VPC::calculateButtonPositions(9, CH);
	leftWindow->createScreen("environmentEditorMenuTerrainLighting");
	leftWindow->getScreen("environmentEditorMenuTerrainLighting")->createButton("normalMap", Vec2(0.0f, positions[0]), Vec2(TW("Normal Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainLighting")->createButton("normalMapR", Vec2(0.0f, positions[1]), Vec2(TW("Red Normal Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Red Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainLighting")->createButton("normalMapG", Vec2(0.0f, positions[2]), Vec2(TW("Green Normal Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Green Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainLighting")->createButton("normalMapB", Vec2(0.0f, positions[3]), Vec2(TW("Blue Normal Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blue Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainLighting")->createButton("isSpecular", Vec2(0.0f, positions[4]), Vec2(TW("Specular: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainLighting")->createButton("specularFactor", Vec2(0.0f, positions[5]), Vec2(TW("Spec Factor"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec Factor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainLighting")->createButton("specularIntensity", Vec2(0.0f, positions[6]), Vec2(TW("Spec Intensity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainLighting")->createButton("lightness", Vec2(0.0f, positions[7]), Vec2(TW("Lightness"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuTerrainLighting")->createButton("back", Vec2(0.0f, positions[8]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: environmentEditorMenuWater
	positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("environmentEditorMenuWater");
	leftWindow->getScreen("environmentEditorMenuWater")->createButton("add", Vec2(0.0f, positions[0]), Vec2(TW("Add Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Add Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWater")->createButton("edit", Vec2(0.0f, positions[1]), Vec2(TW("Edit Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWater")->createButton("delete", Vec2(0.0f, positions[2]), Vec2(TW("Delete Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWater")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: environmentEditorMenuWaterChoice
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("environmentEditorMenuWaterChoice");
	leftWindow->getScreen("environmentEditorMenuWaterChoice")->createButton("terrain", Vec2(0.0f, positions[0]), Vec2(TW("Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterChoice")->createButton("mesh", Vec2(0.0f, positions[1]), Vec2(TW("3D mesh"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "3D mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterChoice")->createButton("effects", Vec2(0.0f, positions[2]), Vec2(TW("Effects"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Effects", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterChoice")->createButton("options", Vec2(0.0f, positions[3]), Vec2(TW("Options"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Options", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterChoice")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: environmentEditorMenuWaterMesh
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("environmentEditorMenuWaterMesh");
	leftWindow->getScreen("environmentEditorMenuWaterMesh")->createButton("position", Vec2(0.0f, positions[0]), Vec2(TW("Position"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Position", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterMesh")->createButton("size", Vec2(0.0f, positions[1]), Vec2(TW("Size"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterMesh")->createButton("up", Vec2(0.0f, positions[2]), Vec2(TW("Move Up"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Move Up", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterMesh")->createButton("down", Vec2(0.0f, positions[3]), Vec2(TW("Move Down"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Move Down", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterMesh")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: environmentEditorMenuWaterEffects
	positions = VPC::calculateButtonPositions(10, CH);
	leftWindow->createScreen("environmentEditorMenuWaterEffects");
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->createButton("uvRepeat", Vec2(0.0f, positions[0]), Vec2(TW("UV Repeat"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "UV Repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->createButton("dudvMap", Vec2(0.0f, positions[1]), Vec2(TW("Dudv Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Dudv Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->createButton("normalMap", Vec2(0.0f, positions[2]), Vec2(TW("Normal Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->createButton("displaceMap", Vec2(0.0f, positions[3]), Vec2(TW("Displace Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Displace Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->createButton("isReflective", Vec2(0.0f, positions[4]), Vec2(TW("Reflective: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflective: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->createButton("isRefractive", Vec2(0.0f, positions[5]), Vec2(TW("Refractive: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Refractive: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->createButton("isWaving", Vec2(0.0f, positions[6]), Vec2(TW("Waving: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Waving: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->createButton("isRippling", Vec2(0.0f, positions[7]), Vec2(TW("Rippling: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rippling: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->createButton("isSpecular", Vec2(0.0f, positions[8]), Vec2(TW("Specular: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterEffects")->createButton("back", Vec2(0.0f, positions[9]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: environmentEditorMenuWaterOptions
	positions = VPC::calculateButtonPositions(8, CH);
	leftWindow->createScreen("environmentEditorMenuWaterOptions");
	leftWindow->getScreen("environmentEditorMenuWaterOptions")->createButton("speed", Vec2(0.0f, positions[0]), Vec2(TW("Water Speed"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Water Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterOptions")->createButton("transparency", Vec2(0.0f, positions[1]), Vec2(TW("Transparency"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Transparency", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterOptions")->createButton("color", Vec2(0.0f, positions[2]), Vec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterOptions")->createButton("specularFactor", Vec2(0.0f, positions[3]), Vec2(TW("Spec Factor"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec Factor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterOptions")->createButton("specularIntensity", Vec2(positions[4], -0.13f), Vec2(TW("Spec Intensity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterOptions")->createButton("waveHeight", Vec2(0.0f, positions[5]), Vec2(TW("Wave Height"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Wave Height", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterOptions")->createButton("quality", Vec2(0.0f, positions[6]), Vec2(TW("Quality"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Quality", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenuWaterOptions")->createButton("back", Vec2(0.0f, positions[7]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void EnvironmentEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("environmentEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("environmentEditorMenuSky");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("environmentEditorMenuSkyChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("environmentEditorMenuSkyMesh");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("environmentEditorMenuSkyOptions");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("environmentEditorMenuTerrain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("environmentEditorMenuTerrainChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("environmentEditorMenuTerrainMesh");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("environmentEditorMenuTerrainBlendMap");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("environmentEditorMenuTerrainLighting");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("environmentEditorMenuWater");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("environmentEditorMenuWaterChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("environmentEditorMenuWaterMesh");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("environmentEditorMenuWaterEffects");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("environmentEditorMenuWaterOptions");
}