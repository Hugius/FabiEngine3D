#include "terrain_editor.hpp"
#include "left_viewport_controller.hpp"

#define TW(text) VPC::calculateTextWidth(text, CW)

TerrainEditor::TerrainEditor(FabiEngine3D& fe3d, EngineGuiManager& gui)
	:
	_fe3d(fe3d),
	_gui(gui)
{

}

void TerrainEditor::load()
{
	// GUI
	_loadGUI();

	// Camera
	_fe3d.camera_reset();
	_fe3d.camera_setMouseSensitivity(MOUSE_SENSITIVITY);
	_fe3d.camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d.camera_enableThirdPersonView(INITIAL_CAMERA_YAW, INITIAL_CAMERA_PITCH);
	_fe3d.camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);
	_fe3d.camera_setThirdPersonLookat(Vec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	
	// Default graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 1.0f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(10000.0f), Vec3(1.0f), 3.0f);
	_fe3d.gfx_enableMotionBlur(0.1f);

	// Editor models
	_fe3d.modelEntity_create("@@cube", "engine_assets\\meshes\\cube.obj");
	_fe3d.modelEntity_setPosition("@@cube", "", Vec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.modelEntity_setDiffuseMap("@@cube", "engine_assets\\textures\\cube.png");
	_fe3d.modelEntity_setFaceCulled("@@cube", true);
	_fe3d.modelEntity_create("@@grid", "engine_assets\\meshes\\plane.obj");
	_fe3d.modelEntity_setPosition("@@grid", "", Vec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.modelEntity_setSize("@@grid", "", Vec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d.modelEntity_setDiffuseMap("@@grid", "engine_assets\\textures\\grid.png");
	_fe3d.modelEntity_setUvRepeat("@@grid", GRID_UV);
	_fe3d.modelEntity_setTransparent("@@grid", true);
	_fe3d.modelEntity_setShadowed("@@grid", false);

	// Miscellaneous
	_gui.getGlobalScreen()->createTextField("terrainID", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("terrainEditorControls");
	_isEditorLoaded = true;
}

void TerrainEditor::unload()
{
	// GUI
	_unloadGUI();

	// Default graphics
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableMotionBlur(true);

	// Delete terrains
	unloadTerrainEntities();

	// Editor models
	_fe3d.modelEntity_deleteAll();

	// Reset editor properties
	_loadedTerrainIDs.clear();
	_currentTerrainID = "";
	_isEditorLoaded = false;
	_isCreatingTerrain = false;
	_isChoosingTerrain = false;
	_isEditingTerrain = false;
	_isDeletingTerrain = false;

	// Miscellaneous
	_gui.getGlobalScreen()->deleteTextField("terrainID");
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	if (_fe3d.camera_isThirdPersonViewEnabled())
	{
		_fe3d.camera_disableThirdPersonView();
	}
	if (_fe3d.misc_isDebugRenderingEnabled())
	{
		_fe3d.misc_disableDebugRendering();
	}
}

void TerrainEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: terrainEditorMenuMain
	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("terrainEditorMenuMain");
	leftWindow->getScreen("terrainEditorMenuMain")->createButton("create", Vec2(0.0f, positions[0]), Vec2(TW("Create Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuMain")->createButton("edit", Vec2(0.0f, positions[1]), Vec2(TW("Edit Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuMain")->createButton("delete", Vec2(0.0f, positions[2]), Vec2(TW("Delete Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuMain")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: terrainEditorMenuChoice
	positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("terrainEditorMenuChoice");
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("mesh", Vec2(0.0f, positions[0]), Vec2(TW("3D Mesh"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "3D Mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("blendMap", Vec2(0.0f, positions[1]), Vec2(TW("Blend Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blend Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("lighting", Vec2(0.0f, positions[2]), Vec2(TW("Lighting"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lighting", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: terrainEditorMenuMesh
	positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("terrainEditorMenuMesh");
	leftWindow->getScreen("terrainEditorMenuMesh")->createButton("maxHeight", Vec2(0.0f, positions[0]), Vec2(TW("Max Height"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Max Height", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuMesh")->createButton("diffuseMap", Vec2(0.0f, positions[1]), Vec2(TW("Diffuse Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Diffuse Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuMesh")->createButton("uvRepeat", Vec2(0.0f, positions[2]), Vec2(TW("UV Repeat"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "UV Repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuMesh")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: terrainEditorMenuBlendMap
	positions = VPC::calculateButtonPositions(8, CH);
	leftWindow->createScreen("terrainEditorMenuBlendMap");
	leftWindow->getScreen("terrainEditorMenuBlendMap")->createButton("blendMap", Vec2(0.0f, positions[0]), Vec2(TW("Blend Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blend Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->createButton("red", Vec2(0.0f, positions[1]), Vec2(TW("Red Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Red Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->createButton("green", Vec2(0.0f, positions[2]), Vec2(TW("Green Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Green Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->createButton("blue", Vec2(0.0f, positions[3]), Vec2(TW("Blue Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blue Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->createButton("redRepeat", Vec2(0.0f, positions[4]), Vec2(TW("Red UV"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Red UV", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->createButton("greenRepeat", Vec2(0.0f, positions[5]), Vec2(TW("Green UV"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Green UV", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->createButton("blueRepeat", Vec2(0.0f, positions[6]), Vec2(TW("Blue UV"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blue UV", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->createButton("back", Vec2(0.0f, positions[7]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: terrainEditorMenuLighting
	positions = VPC::calculateButtonPositions(9, CH);
	leftWindow->createScreen("terrainEditorMenuLighting");
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("normalMap", Vec2(0.0f, positions[0]), Vec2(TW("Normal Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("normalMapR", Vec2(0.0f, positions[1]), Vec2(TW("Red Normal Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Red Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("normalMapG", Vec2(0.0f, positions[2]), Vec2(TW("Green Normal Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Green Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("normalMapB", Vec2(0.0f, positions[3]), Vec2(TW("Blue Normal Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blue Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("isSpecular", Vec2(0.0f, positions[4]), Vec2(TW("Specular: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("specularShininess", Vec2(0.0f, positions[5]), Vec2(TW("Spec Factor"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec Factor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("specularIntensity", Vec2(0.0f, positions[6]), Vec2(TW("Spec Intensity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("lightness", Vec2(0.0f, positions[7]), Vec2(TW("Lightness"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("back", Vec2(0.0f, positions[8]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void TerrainEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("terrainEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("terrainEditorMenuChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("terrainEditorMenuMesh");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("terrainEditorMenuBlendMap");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("terrainEditorMenuLighting");
}