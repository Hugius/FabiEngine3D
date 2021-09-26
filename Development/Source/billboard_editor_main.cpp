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
	_fe3d.camera_enableThirdPersonView(INITIAL_CAMERA_YAW, INITIAL_CAMERA_PITCH);
	_fe3d.camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);
	_fe3d.camera_setThirdPersonLookat(Vec3(0.0f, -GRID_Y_OFFSET, 0.0f));

	// Default graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 1.0f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(10000.0f), Vec3(1.0f), 3.0f);
	_fe3d.gfx_enableBloom(BloomType::PARTS, 1.0f, 5);
	_fe3d.gfx_enableMotionBlur(0.1f);
	
	// Editor models
	_fe3d.modelEntity_create("@@cube", "engine_assets\\meshes\\cube.obj");
	_fe3d.modelEntity_setBasePosition("@@cube", Vec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.modelEntity_setDiffuseMap("@@cube", "", "engine_assets\\textures\\cube.png");
	_fe3d.modelEntity_setFaceCulled("@@cube", true);
	_fe3d.modelEntity_create("@@grid", "engine_assets\\meshes\\plane.obj");
	_fe3d.modelEntity_setBasePosition("@@grid", Vec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.modelEntity_setBaseSize("@@grid", Vec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d.modelEntity_setDiffuseMap("@@grid", "", "engine_assets\\textures\\grid.png");
	_fe3d.modelEntity_setUvRepeat("@@grid", "", GRID_UV);
	_fe3d.modelEntity_setShadowed("@@grid", false);

	// Miscellaneous
	_gui.getGlobalScreen()->createTextField("billboardID", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
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

	// Delete billboards
	_fe3d.billboardEntity_deleteAll();

	// Editor models
	_fe3d.modelEntity_deleteAll();

	// Delete billboard ID TextField
	_gui.getGlobalScreen()->deleteTextField("billboardID");

	// Reset editor properties
	_loadedBillboardIDs.clear();
	_hoveredBillboardID = "";
	_currentBillboardID = "";
	_isCreatingBillboard = false;
	_isChoosingBillboard = false;
	_isDeletingBillboard = false;
	_isEditorLoaded = false;

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
	leftWindow->getScreen("billboardEditorMenuMain")->createButton("create", Vec2(0.0f, positions[0]), Vec2(TW("Create Billboard"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Billboard", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMain")->createButton("edit", Vec2(0.0f, positions[1]), Vec2(TW("Edit Billboard"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Billboard", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMain")->createButton("delete", Vec2(0.0f, positions[2]), Vec2(TW("Delete Billboard"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Billboard", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMain")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: billboardEditorMenuChoice
	positions = VPC::calculateButtonPositions(6, CH);
	leftWindow->createScreen("billboardEditorMenuChoice");
	leftWindow->getScreen("billboardEditorMenuChoice")->createButton("size", Vec2(0.0f, positions[0]), Vec2(TW("Size"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuChoice")->createButton("texturing", Vec2(0.0f, positions[1]), Vec2(TW("Texturing"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Texturing", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuChoice")->createButton("animation", Vec2(0.0f, positions[2]), Vec2(TW("Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuChoice")->createButton("lighting", Vec2(0.0f, positions[3]), Vec2(TW("Lighting"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lighting", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuChoice")->createButton("miscellaneous", Vec2(0.0f, positions[4]), Vec2(TW("Miscellaneous"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Miscellaneous", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuChoice")->createButton("back", Vec2(0.0f, positions[5]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: billboardEditorMenuTexturing
	positions = VPC::calculateButtonPositions(7, CH);
	leftWindow->createScreen("billboardEditorMenuTexturing");
	leftWindow->getScreen("billboardEditorMenuTexturing")->createButton("font", Vec2(0.0f, positions[0]), Vec2(TW("Font"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Font", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuTexturing")->createButton("textContent", Vec2(0.0f, positions[1]), Vec2(TW("Text Content"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Text Content", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuTexturing")->createButton("diffuseMap", Vec2(0.0f, positions[2]), Vec2(TW("Diffuse Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Diffuse Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuTexturing")->createButton("emissionMap", Vec2(0.0f, positions[3]), Vec2(TW("Emission Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Emission Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuTexturing")->createButton("clearMaps", Vec2(0.0f, positions[4]), Vec2(TW("Clear Maps"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Clear Maps", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuTexturing")->createButton("uvRepeat", Vec2(0.0f, positions[5]), Vec2(TW("UV Repeat"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "UV Repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuTexturing")->createButton("back", Vec2(0.0f, positions[6]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: billboardEditorMenuAnimation
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("billboardEditorMenuAnimation");
	leftWindow->getScreen("billboardEditorMenuAnimation")->createButton("rows", Vec2(0.0f, positions[0]), Vec2(TW("Rows"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rows", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAnimation")->createButton("columns", Vec2(0.0f, positions[1]), Vec2(TW("Columns"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Columns", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAnimation")->createButton("speed", Vec2(0.0f, positions[2]), Vec2(TW("Framestep"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Framestep", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAnimation")->createButton("animate", Vec2(0.0f, positions[3]), Vec2(TW("Animate"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Animate", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuAnimation")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: billboardEditorMenuLighting
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("billboardEditorMenuLighting");
	leftWindow->getScreen("billboardEditorMenuLighting")->createButton("color", Vec2(0.0f, positions[0]), Vec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuLighting")->createButton("lightness", Vec2(0.0f, positions[1]), Vec2(TW("Lightness"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuLighting")->createButton("isShadowed", Vec2(0.0f, positions[2]), Vec2(TW("Shadowed: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Shadowed: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuLighting")->createButton("isReflected", Vec2(0.0f, positions[3]), Vec2(TW("Reflected: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflected: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuLighting")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: billboardEditorMenuMiscellaneous
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("billboardEditorMenuMiscellaneous");
	leftWindow->getScreen("billboardEditorMenuMiscellaneous")->createButton("facingX", Vec2(0.0f, positions[0]), Vec2(TW("Facing X: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Facing X: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMiscellaneous")->createButton("facingY", Vec2(0.0f, positions[1]), Vec2(TW("Facing Y: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Facing Y: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("billboardEditorMenuMiscellaneous")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void BillboardEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("billboardEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("billboardEditorMenuChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("billboardEditorMenuTexturing");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("billboardEditorMenuAnimation");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("billboardEditorMenuLighting");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("billboardEditorMenuMiscellaneous");
}