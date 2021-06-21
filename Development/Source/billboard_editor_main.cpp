#include "billboard_editor.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVPC::calcTextWidth(text, 0.15f, 1.7f)

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
	leftWindow->getScreen("billboardEditorMenuMain")->addButton("addBillboard", Vec2(0.0f, 0.63f), Vec2(GW("Add board"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Add board", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMain")->addButton("editBillboard", Vec2(0.0f, 0.21f), Vec2(GW("Edit board"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit board", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMain")->addButton("deleteBillboard", Vec2(0.0f, -0.21f), Vec2(GW("Delete board"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete board", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMain")->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	
	// Left-viewport: mainWindow - billboardEditorMenuChoice
	leftWindow->addScreen("billboardEditorMenuChoice");
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("mesh", Vec2(0.0f, 0.7f), Vec2(GW("Mesh"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("appearance", Vec2(0.0f, 0.35f), Vec2(GW("Appearance"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Appearance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("animation", Vec2(0.0f, 0.0f), Vec2(GW("Animation"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("text", Vec2(0.0f, -0.35f), Vec2(GW("Text"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Text", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("back", Vec2(0.0f, -0.7f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - billboardEditorMenuMesh
	leftWindow->addScreen("billboardEditorMenuMesh");
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("size", Vec2(0.0f, 0.63f), Vec2(GW("Size"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("facingX", Vec2(0.0f, 0.21f), Vec2(GW("Facing X: OFF"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Facing X: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("facingY", Vec2(0.0f, -0.21f), Vec2(GW("Facing Y: OFF"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Facing Y: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - billboardEditorMenuAppearance
	leftWindow->addScreen("billboardEditorMenuAppearance");
	leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("lightness", Vec2(0.0f, 0.7f), Vec2(GW("Lightness"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("color", Vec2(0.0f, 0.35f), Vec2(GW("Color"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("texture", Vec2(0.0f, 0.0f), Vec2(GW("Texture"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("isTransparent", Vec2(0.0f, -0.35f), Vec2(GW("Alpha: OFF"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Alpha: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("back", Vec2(0.0f, -0.7f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - billboardEditorMenuAnimation
	leftWindow->addScreen("billboardEditorMenuAnimation");
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("rows", Vec2(0.0f, 0.7f), Vec2(GW("Rows"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rows", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("columns", Vec2(0.0f, 0.35f), Vec2(GW("Columns"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Columns", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("speed", Vec2(0.0f, 0.0f), Vec2(GW("Frame step"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Frame step", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("animate", Vec2(0.0f, -0.35f), Vec2(GW("Animate"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Animate", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("back", Vec2(0.0f, -0.7f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	
	// Left-viewport: mainWindow - billboardEditorMenuText
	leftWindow->addScreen("billboardEditorMenuText");
	leftWindow->getScreen("billboardEditorMenuText")->addButton("font", Vec2(0.0f, 0.63f), Vec2(GW("Font"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Font", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuText")->addButton("color", Vec2(0.0f, 0.21f), Vec2(GW("Color"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuText")->addButton("content", Vec2(0.0f, -0.21f), Vec2(GW("Content"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Content", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuText")->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
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
	_fe3d.camera_load(90.0f, 0.1f, 10000.0f, CAMERA_POSITION, -90.0f, 0.0f);
	_fe3d.camera_enableLookatView();

	// Enable graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 0.45f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(1000.0f), Vec3(1.0f), 1.0f);
	_fe3d.gfx_enableShadows(Vec3(10.0f, 10.0f, 10.0f), Vec3(0.0f), 25.0f, 50.0f, 0.5, false, true, 0);
	
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

	// Disable graphics
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableShadows(true);

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
	_fe3d.misc_disableDebugRendering();
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_fe3d.input_setKeyTogglingLocked(false);
	_isEditorLoaded = false;
}
