#include "billboard_editor.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVPC::calcTextWidth(text, 0.15f, 1.8f)

BillboardEditor::BillboardEditor(FabiEngine3D& fe3d, EngineGuiManager& gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void BillboardEditor::initializeGUI()
{
	// Private window instance of left viewport
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - billboardManagement
	leftWindow->addScreen("billboardEditorMenuMain");
	leftWindow->getScreen("billboardEditorMenuMain")->addButton("addBillboard", Vec2(0.0f, 0.63f), Vec2(GW("Add board"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Add board", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuMain")->addButton("editBillboard", Vec2(0.0f, 0.21f), Vec2(GW("Edit board"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit board", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuMain")->addButton("deleteBillboard", Vec2(0.0f, -0.21f), Vec2(GW("Delete board"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Delete board", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuMain")->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - billboardEditingMain
	leftWindow->addScreen("billboardEditorMenuChoice");
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("mesh", Vec2(0.0f, 0.7f), Vec2(GW("Mesh"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Mesh", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("appearance", Vec2(0.0f, 0.35f), Vec2(GW("Appearance"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Appearance", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("animation", Vec2(0.0f, 0.0f), Vec2(GW("Animation"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Animation", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("text", Vec2(0.0f, -0.35f), Vec2(GW("Text"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Text", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("back", Vec2(0.0f, -0.7f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - billboardEditingMesh
	leftWindow->addScreen("billboardEditorMenuMesh");
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("size", Vec2(0.0f, 0.63f), Vec2(GW("Size"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Size", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("facingX", Vec2(0.0f, 0.21f), Vec2(GW("Facing X: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Facing X: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("facingY", Vec2(0.0f, -0.21f), Vec2(GW("Facing Y: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Facing Y: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - billboardEditingAppearance
	leftWindow->addScreen("billboardEditorMenuAppearance");
	leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("color", Vec2(0.0f, 0.63f), Vec2(GW("Color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Color", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("texture", Vec2(0.0f, 0.21f), Vec2(GW("Texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Texture", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("isTransparent", Vec2(0.0f, -0.21f), Vec2(GW("Alpha: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Alpha: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - billboardEditingAnimation
	leftWindow->addScreen("billboardEditorMenuAnimation");
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("rows", Vec2(0.0f, 0.7f), Vec2(GW("Rows"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Rows", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("columns", Vec2(0.0f, 0.35f), Vec2(GW("Columns"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Columns", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("speed", Vec2(0.0f, 0.0f), Vec2(GW("Frame step"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Frame step", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("animate", Vec2(0.0f, -0.35f), Vec2(GW("Animate"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Animate", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("back", Vec2(0.0f, -0.7f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - billboardEditingText
	leftWindow->addScreen("billboardEditorMenuText");
	leftWindow->getScreen("billboardEditorMenuText")->addButton("font", Vec2(0.0f, 0.63f), Vec2(GW("Font"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Font", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuText")->addButton("color", Vec2(0.0f, 0.21f), Vec2(GW("Color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Color", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuText")->addButton("content", Vec2(0.0f, -0.21f), Vec2(GW("Content"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Content", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuText")->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
}

void BillboardEditor::load()
{
	// Camera
	_fe3d.camera_load(90.0f, 0.1f, 10000.0f, _defaultCameraPosition, -90.0f);
	_fe3d.camera_enableLookat(_billboardPosition);

	// Enable graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 0.45f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(1000.0f), Vec3(1.0f), 1.0f);
	_fe3d.gfx_enableShadows(Vec3(10.0f, 10.0f, 10.0f), Vec3(0.0f), 25.0f, 50.0f, false);
	
	// 3D Environment
	_fe3d.gameEntity_add("@@cube", "engine\\models\\cube.obj", Vec3(5.0f, 0.0f, 0.0f), Vec3(0.0f), Vec3(1.0f, 1.0f, 1.0f));
	_fe3d.gameEntity_setDiffuseMap("@@cube", "engine\\textures\\cube.png");
	_fe3d.gameEntity_setFaceCulled("@@cube", true);
	_fe3d.gameEntity_add("@@grid", "engine\\models\\plane.obj", Vec3(0.0f), Vec3(0.0f), Vec3(50.0f, 1.0f, 50.0f));
	_fe3d.gameEntity_setDiffuseMap("@@grid", "engine\\textures\\grid.png");
	_fe3d.gameEntity_setUvRepeat("@@grid", 5.0f);
	_fe3d.gameEntity_setTransparent("@@grid", true);

	// Load billboards from file
	loadBillboardEntitiesFromFile();

	// Miscellaneous
	_gui.getGlobalScreen()->addTextfield("selectedBillboardName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("billboardEditorControls");
	_isLoaded = true;
}

void BillboardEditor::unload()
{
	// Disable graphics
	_fe3d.gfx_disableAmbientLighting();
	_fe3d.gfx_disableDirectionalLighting();
	_fe3d.gfx_disableShadows();

	// 3D environment
	_fe3d.gameEntity_delete("@@cube");
	_fe3d.gameEntity_delete("@@grid");

	// Delete billboards
	_fe3d.billboardEntity_deleteAll();

	// Delete billboard name textfield
	_gui.getGlobalScreen()->deleteTextfield("selectedBillboardName");

	// Reset variables
	isCreatingBillboard = false;
	_isChoosingBillboard = false;
	_isEditingBillboard = false;
	_isRemovingBillboard = false;
	_cameraRotationSpeed = 0.0f;
	_totalCameraRotation = 0.0f;
	_hoveredBillboardID = "";
	_currentBillboardID = "";
	_billboardNames.clear();

	// Miscellaneous
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	_isLoaded = false;
}
