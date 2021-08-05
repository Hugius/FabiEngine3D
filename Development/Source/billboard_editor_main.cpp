#include "billboard_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

#define TW(text) VPC::calculateTextWidth(text, CW)

BillboardEditor::BillboardEditor(FabiEngine3D& fe3d, EngineGuiManager& gui)
	:
	_fe3d(fe3d),
	_gui(gui)
{

}

void BillboardEditor::load()
{
	// GUI
	_loadGUI();

	// Camera
	_fe3d.camera_reset();
	_fe3d.camera_setMouseSensitivity(MOUSE_SENSITIVITY);
	_fe3d.camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d.camera_enableThirdPersonView(INITIAL_CAMERA_YAW, INITIAL_CAMERA_PITCH, INITIAL_CAMERA_DISTANCE);

	// Default graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 1.0f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(1000.0f), Vec3(1.0f), 3.0f);
	_fe3d.gfx_enableBloom(BloomType::PARTS, 1.0f, 5);
	_fe3d.gfx_enableMotionBlur(0.1f);
	
	// 3D environment
	_fe3d.modelEntity_create("@@cube", "engine_assets\\meshes\\cube.obj");
	_fe3d.modelEntity_setDiffuseMap("@@cube", "engine_assets\\textures\\cube.png");
	_fe3d.modelEntity_setFaceCulled("@@cube", true);
	_fe3d.modelEntity_create("@@grid", "engine_assets\\meshes\\plane.obj");
	_fe3d.modelEntity_setSize("@@grid", Vec3(30.0f, 1.0f, 30.0f));
	_fe3d.modelEntity_setDiffuseMap("@@grid", "engine_assets\\textures\\grid.png");
	_fe3d.modelEntity_setUvRepeat("@@grid", 3.0f);
	_fe3d.modelEntity_setTransparent("@@grid", true);

	// Miscellaneous
	_gui.getGlobalScreen()->createTextfield("selectedBillboardName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("billboardEditorControls");
	_isEditorLoaded = true;
}

void BillboardEditor::unload()
{
	// GUI
	_unloadGUI();

	// Camera
	if (_fe3d.camera_isThirdPersonViewEnabled())
	{
		_fe3d.camera_disableThirdPersonView();
	}

	// Shadows
	if (_fe3d.gfx_isShadowsEnabled())
	{
		_fe3d.gfx_disableShadows(true);
	}

	// Default graphics
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableBloom(true);
	_fe3d.gfx_disableMotionBlur(true);

	// 3D environment
	_fe3d.modelEntity_delete("@@cube");
	_fe3d.modelEntity_delete("@@grid");

	// Delete billboards
	_fe3d.billboardEntity_deleteAll();

	// Delete billboard name textfield
	_gui.getGlobalScreen()->deleteTextfield("selectedBillboardName");

	// Reset editor properties
	_isEditorLoaded = false;
	_isCreatingBillboard = false;
	_isChoosingBillboard = false;
	_isEditingBillboard = false;
	_isDeletingBillboard = false;
	_hoveredBillboardID = "";
	_currentBillboardID = "";
	_loadedBillboardIDs.clear();

	// Miscellaneous
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	if (_fe3d.misc_isDebugRenderingEnabled())
	{
		_fe3d.misc_disableDebugRendering();
	}
}

void BillboardEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: billboardEditorMenuMain
	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("billboardEditorMenuMain");
	leftWindow->getScreen("billboardEditorMenuMain")->createButton("add", Vec2(0.0f, positions[0]), Vec2(TW("Add Board"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Add Board", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMain")->createButton("edit", Vec2(0.0f, positions[1]), Vec2(TW("Edit Board"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Board", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMain")->createButton("delete", Vec2(0.0f, positions[2]), Vec2(TW("Delete Board"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Board", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMain")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: billboardEditorMenuChoice
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("billboardEditorMenuChoice");
	leftWindow->getScreen("billboardEditorMenuChoice")->createButton("mesh", Vec2(0.0f, positions[0]), Vec2(TW("Mesh"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuChoice")->createButton("appearance", Vec2(0.0f, positions[1]), Vec2(TW("Appearance"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Appearance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuChoice")->createButton("animation", Vec2(0.0f, positions[2]), Vec2(TW("Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuChoice")->createButton("text", Vec2(0.0f, positions[3]), Vec2(TW("Text"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Text", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuChoice")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: billboardEditorMenuMesh
	positions = VPC::calculateButtonPositions(7, CH);
	leftWindow->createScreen("billboardEditorMenuMesh");
	leftWindow->getScreen("billboardEditorMenuMesh")->createButton("size", Vec2(0.0f, positions[0]), Vec2(TW("Size"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMesh")->createButton("facingX", Vec2(0.0f, positions[1]), Vec2(TW("Facing X: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Facing X: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMesh")->createButton("facingY", Vec2(0.0f, positions[2]), Vec2(TW("Facing Y: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Facing Y: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMesh")->createButton("isShadowed", Vec2(0.0f, positions[3]), Vec2(TW("Shadowed: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Shadowed: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMesh")->createButton("isReflected", Vec2(0.0f, positions[4]), Vec2(TW("Reflected: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflected: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMesh")->createButton("isBright", Vec2(0.0f, positions[5]), Vec2(TW("Bright: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Bright: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMesh")->createButton("back", Vec2(0.0f, positions[6]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);


	// Left-viewport: billboardEditorMenuAppearance
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("billboardEditorMenuAppearance");
	leftWindow->getScreen("billboardEditorMenuAppearance")->createButton("lightness", Vec2(0.0f, positions[0]), Vec2(TW("Lightness"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAppearance")->createButton("color", Vec2(0.0f, positions[1]), Vec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAppearance")->createButton("texture", Vec2(0.0f, positions[2]), Vec2(TW("Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAppearance")->createButton("isTransparent", Vec2(0.0f, positions[3]), Vec2(TW("Alpha: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Alpha: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAppearance")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: billboardEditorMenuAnimation
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("billboardEditorMenuAnimation");
	leftWindow->getScreen("billboardEditorMenuAnimation")->createButton("rows", Vec2(0.0f, positions[0]), Vec2(TW("Rows"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rows", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAnimation")->createButton("columns", Vec2(0.0f, positions[1]), Vec2(TW("Columns"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Columns", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAnimation")->createButton("speed", Vec2(0.0f, positions[2]), Vec2(TW("Framestep"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Framestep", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAnimation")->createButton("animate", Vec2(0.0f, positions[3]), Vec2(TW("Animate"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Animate", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAnimation")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: billboardEditorMenuText
	positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("billboardEditorMenuText");
	leftWindow->getScreen("billboardEditorMenuText")->createButton("font", Vec2(0.0f, positions[0]), Vec2(TW("Font"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Font", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuText")->createButton("color", Vec2(0.0f, positions[1]), Vec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuText")->createButton("content", Vec2(0.0f, positions[2]), Vec2(TW("Content"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Content", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuText")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void BillboardEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("billboardEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("billboardEditorMenuChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("billboardEditorMenuMesh");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("billboardEditorMenuAppearance");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("billboardEditorMenuAnimation");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("billboardEditorMenuText");
}