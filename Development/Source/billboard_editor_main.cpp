#include "billboard_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

#define CW(text) VPC::calculateTextWidth(text, 0.115f)

constexpr auto TH = 0.0875f;

BillboardEditor::BillboardEditor(FabiEngine3D& fe3d, EngineGuiManager& gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void BillboardEditor::_loadGUI()
{
	// Private window instance of left viewport
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - billboardEditorMenuMain
	leftWindow->addScreen("billboardEditorMenuMain");
	leftWindow->getScreen("billboardEditorMenuMain")->addButton("addBillboard", Vec2(0.0f, 0.63f), Vec2(CW("Add Board"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Add Board", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMain")->addButton("editBillboard", Vec2(0.0f, 0.21f), Vec2(CW("Edit Board"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Board", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMain")->addButton("deleteBillboard", Vec2(0.0f, -0.21f), Vec2(CW("Delete Board"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Board", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMain")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	
	// Left-viewport: mainWindow - billboardEditorMenuChoice
	leftWindow->addScreen("billboardEditorMenuChoice");
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("mesh", Vec2(0.0f, 0.7f), Vec2(CW("Mesh"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("appearance", Vec2(0.0f, 0.35f), Vec2(CW("Appearance"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Appearance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("animation", Vec2(0.0f, 0.0f), Vec2(CW("Animation"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("text", Vec2(0.0f, -0.35f), Vec2(CW("Text"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Text", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("back", Vec2(0.0f, -0.7f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - billboardEditorMenuMesh
	leftWindow->addScreen("billboardEditorMenuMesh");
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("size", Vec2(0.0f, 0.7875f), Vec2(CW("Size"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("facingX", Vec2(0.0f, 0.525f), Vec2(CW("Facing X: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Facing X: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("facingY", Vec2(0.0f, 0.2625f), Vec2(CW("Facing Y: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Facing Y: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("isShadowed", Vec2(0.0f, 0.0f), Vec2(CW("Shadowed: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Shadowed: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("isReflected", Vec2(0.0f, -0.2625f), Vec2(CW("Reflected: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflected: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("isBloomed", Vec2(0.0f, -0.525f), Vec2(CW("Bloomed: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Bloomed: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("back", Vec2(0.0f, -0.7875f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);


	// Left-viewport: mainWindow - billboardEditorMenuAppearance
	leftWindow->addScreen("billboardEditorMenuAppearance");
	leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("lightness", Vec2(0.0f, 0.7f), Vec2(CW("Lightness"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("color", Vec2(0.0f, 0.35f), Vec2(CW("Color"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("texture", Vec2(0.0f, 0.0f), Vec2(CW("Texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("isTransparent", Vec2(0.0f, -0.35f), Vec2(CW("Alpha: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Alpha: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("back", Vec2(0.0f, -0.7f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - billboardEditorMenuAnimation
	leftWindow->addScreen("billboardEditorMenuAnimation");
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("rows", Vec2(0.0f, 0.7f), Vec2(CW("Rows"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rows", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("columns", Vec2(0.0f, 0.35f), Vec2(CW("Columns"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Columns", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("speed", Vec2(0.0f, 0.0f), Vec2(CW("Framestep"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Framestep", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("animate", Vec2(0.0f, -0.35f), Vec2(CW("Animate"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Animate", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("back", Vec2(0.0f, -0.7f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	
	// Left-viewport: mainWindow - billboardEditorMenuText
	leftWindow->addScreen("billboardEditorMenuText");
	leftWindow->getScreen("billboardEditorMenuText")->addButton("font", Vec2(0.0f, 0.63f), Vec2(CW("Font"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Font", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuText")->addButton("color", Vec2(0.0f, 0.21f), Vec2(CW("Color"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuText")->addButton("content", Vec2(0.0f, -0.21f), Vec2(CW("Content"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Content", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuText")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void BillboardEditor::_unloadGUI()
{
	auto leftWindow = _gui.getViewport("left")->getWindow("main");
	leftWindow->deleteScreen("billboardEditorMenuMain");
	leftWindow->deleteScreen("billboardEditorMenuChoice");
	leftWindow->deleteScreen("billboardEditorMenuMesh");
	leftWindow->deleteScreen("billboardEditorMenuAppearance");
	leftWindow->deleteScreen("billboardEditorMenuAnimation");
	leftWindow->deleteScreen("billboardEditorMenuText");
}

void BillboardEditor::load()
{
	// GUI
	_loadGUI();

	// Camera
	_fe3d.camera_load(Config::DEFAULT_CAMERA_FOV, Config::DEFAULT_CAMERA_NEAR, Config::DEFAULT_CAMERA_FAR, CAMERA_POSITION, -90.0f, 0.0f);
	_fe3d.camera_enableLookatView();

	// Enable default graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 1.0f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(1000.0f), Vec3(1.0f), 1.5f);
	_fe3d.gfx_enableBloom(BloomType::PARTS, 1.0f, 5);
	
	// 3D Environment
	_fe3d.modelEntity_add("@@cube", "engine_assets\\meshes\\cube.obj", Vec3(0.0f), Vec3(0.0f), Vec3(1.0f, 1.0f, 1.0f));
	_fe3d.modelEntity_setDiffuseMap("@@cube", "engine_assets\\textures\\cube.png");
	_fe3d.modelEntity_setFaceCulled("@@cube", true);
	_fe3d.modelEntity_add("@@grid", "engine_assets\\meshes\\plane.obj", Vec3(0.0f), Vec3(0.0f), Vec3(50.0f, 1.0f, 50.0f));
	_fe3d.modelEntity_setDiffuseMap("@@grid", "engine_assets\\textures\\grid.png");
	_fe3d.modelEntity_setUvRepeat("@@grid", 5.0f);
	_fe3d.modelEntity_setTransparent("@@grid", true);

	// Load billboards from file
	loadBillboardEntitiesFromFile();

	// Miscellaneous
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_gui.getGlobalScreen()->addTextfield("selectedBillboardName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("billboardEditorControls");
	_isEditorLoaded = true;
}

void BillboardEditor::unload()
{
	// GUI
	_unloadGUI();

	// Camera
	_fe3d.camera_disableLookatView();

	// Disable default graphics
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableBloom(true);

	// 3D environment
	_fe3d.modelEntity_delete("@@cube");
	_fe3d.modelEntity_delete("@@grid");

	// Delete billboards
	_fe3d.billboardEntity_deleteAll();

	// Delete billboard name textfield
	_gui.getGlobalScreen()->deleteTextfield("selectedBillboardName");

	// Reset editor properties
	_isCreatingBillboard = false;
	_isChoosingBillboard = false;
	_isEditingBillboard = false;
	_isRemovingBillboard = false;
	_cameraAcceleration = 0.0f;
	_totalCameraRotation = 0.0f;
	_hoveredBillboardID = "";
	_currentBillboardID = "";
	_loadedBillboardIDs.clear();

	// Miscellaneous
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	if (_fe3d.misc_isDebugRenderingEnabled())
	{
		_fe3d.misc_disableDebugRendering();
	}
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_fe3d.input_setKeyTogglingLocked(false);
	_isEditorLoaded = false;
}
