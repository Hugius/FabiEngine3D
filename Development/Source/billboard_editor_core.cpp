#include "billboard_editor.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVPC::calcTextWidth(text, 0.15f, 1.8f)

BillboardEditor::BillboardEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void BillboardEditor::initializeGUI()
{
	// Private window instance of left viewport
	auto leftWindow = _gui->getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - billboardManagement
	leftWindow->addScreen("billboardEditorMenuMain");
	leftWindow->getScreen("billboardEditorMenuMain")->addButton("addBillboard", vec2(0.0f, 0.63f), vec2(GW("Add board"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Add board", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuMain")->addButton("editBillboard", vec2(0.0f, 0.21), vec2(GW("Edit board"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit board", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuMain")->addButton("deleteBillboard", vec2(0.0f, -0.21), vec2(GW("Delete board"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Delete board", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - billboardEditingMain
	leftWindow->addScreen("billboardEditorMenuChoice");
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("mesh", vec2(0.0f, 0.7f), vec2(GW("Mesh"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Mesh", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("appearance", vec2(0.0f, 0.35f), vec2(GW("Appearance"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Appearance", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("animation", vec2(0.0f, 0.0f), vec2(GW("Animation"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Animation", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("text", vec2(0.0f, -0.35f), vec2(GW("Text"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Text", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuChoice")->addButton("back", vec2(0.0f, -0.7f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - billboardEditingMesh
	leftWindow->addScreen("billboardEditorMenuMesh");
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("size", vec2(0.0f, 0.63f), vec2(GW("Size"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Size", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("facingX", vec2(0.0f, 0.21), vec2(GW("Facing X: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Facing X: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("facingY", vec2(0.0f, -0.21), vec2(GW("Facing Y: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Facing Y: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuMesh")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - billboardEditingAppearance
	leftWindow->addScreen("billboardEditorMenuAppearance");
	leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("color", vec2(0.0f, 0.63f), vec2(GW("Color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Color", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("texture", vec2(0.0f, 0.21), vec2(GW("Texture"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Texture", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("isTransparent", vec2(0.0f, -0.21), vec2(GW("Alpha: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Alpha: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuAppearance")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - billboardEditingAnimation
	leftWindow->addScreen("billboardEditorMenuAnimation");
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("rows", vec2(0.0f, 0.7f), vec2(GW("Rows"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Rows", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("columns", vec2(0.0f, 0.35f), vec2(GW("Columns"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Columns", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("speed", vec2(0.0f, 0.0f), vec2(GW("Frame step"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Frame step", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("animate", vec2(0.0f, -0.35f), vec2(GW("Animate"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Animate", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuAnimation")->addButton("back", vec2(0.0f, -0.7f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - billboardEditingText
	leftWindow->addScreen("billboardEditorMenuText");
	leftWindow->getScreen("billboardEditorMenuText")->addButton("font", vec2(0.0f, 0.63f), vec2(GW("Font"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Font", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuText")->addButton("color", vec2(0.0f, 0.21), vec2(GW("Color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Color", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuText")->addButton("content", vec2(0.0f, -0.21), vec2(GW("Content"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Content", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("billboardEditorMenuText")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
}

void BillboardEditor::load()
{
	// Camera
	_fe3d.camera_load(90.0f, 0.1f, 10000.0f, _defaultCameraPosition, -90.0f);
	_fe3d.camera_enableLookat(_billboardPosition);

	// Enable graphics
	_fe3d.gfx_enableAmbientLighting(vec3(1.0f), 0.45f);
	_fe3d.gfx_enableDirectionalLighting(vec3(1000.0f), vec3(1.0f), 1.0f);
	_fe3d.gfx_enableShadows(vec3(10.0f, 10.0f, 10.0f), vec3(0.0f), 25.0f, 50.0f, false);
	
	// 3D Environment
	_fe3d.gameEntity_add("@@cube", "engine\\models\\cube.obj", vec3(5.0f, 0.0f, 0.0f), vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
	_fe3d.gameEntity_setDiffuseMap("@@cube", "engine\\textures\\cube.png");
	_fe3d.gameEntity_setFaceCulled("@@cube", true);

	// Load billboards from file
	loadBillboards();

	// Other
	_gui->getGlobalScreen()->addTextfield("selectedBillboardName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
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

	// Delete billboards
	_fe3d.billboardEntity_deleteAll();

	// Delete billboard name textfield
	_gui->getGlobalScreen()->deleteTextfield("selectedBillboardName");

	// Reset variables
	_billboardCreationEnabled = false;
	_billboardChoosingEnabled = false;
	_billboardEditingEnabled = false;
	_billboardRemovalEnabled = false;
	_cameraRotationSpeed = 0.0f;
	_totalCameraRotation = 0.0f;
	_hoveredBillboardID = "";
	_currentBillboardID = "";
	_billboardNames.clear();

	// Miscellaneous
	_isLoaded = false;
}
