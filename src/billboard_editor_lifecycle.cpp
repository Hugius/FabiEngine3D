#include "billboard_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

#define TW(text) VPC::calculateTextWidth(text, CW)

BillboardEditor::BillboardEditor(FabiEngine3D& fe3d, GuiManager& gui)
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
	_fe3d.camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d.camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d.camera_enableThirdPersonView(INITIAL_CAMERA_YAW, INITIAL_CAMERA_PITCH);
	_fe3d.camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);
	_fe3d.camera_setThirdPersonLookat(fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));

	// Default graphics
	_fe3d.gfx_enableAmbientLighting();
	_fe3d.gfx_setAmbientLightingColor(fvec3(1.0f));
	_fe3d.gfx_setAmbientLightingIntensity(1.0f);
	_fe3d.gfx_enableDirectionalLighting();
	_fe3d.gfx_setDirectionalLightingColor(fvec3(1.0f));
	_fe3d.gfx_setDirectionalLightingPosition(fvec3(10000.0f));
	_fe3d.gfx_setDirectionalLightingIntensity(3.0f);
	_fe3d.gfx_enableBloom();
	_fe3d.gfx_setBloomType(BloomType::PARTS);
	_fe3d.gfx_setBloomIntensity(1.0f);
	_fe3d.gfx_setBloomBlurCount(5);
	_fe3d.gfx_setBloomQuality(Config::MAX_BLOOM_QUALITY);
	_fe3d.gfx_enableShadows();
	_fe3d.gfx_setShadowLightness(0.25f);
	_fe3d.gfx_setShadowQuality(Config::MAX_SHADOW_QUALITY);

	// Editor models
	_fe3d.model_create("@@box", "engine\\assets\\mesh\\box.obj");
	_fe3d.model_setBasePosition("@@box", fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.model_setDiffuseMap("@@box", "", "engine\\assets\\texture\\box.png");
	_fe3d.model_setFaceCulled("@@box", true);
	_fe3d.model_create("@@grid", "engine\\assets\\mesh\\plane.obj");
	_fe3d.model_setBasePosition("@@grid", fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.model_setBaseSize("@@grid", fvec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d.model_setDiffuseMap("@@grid", "", "engine\\assets\\texture\\grid.png");
	_fe3d.model_setTextureRepeat("@@grid", "", GRID_UV);
	_fe3d.model_setShadowed("@@grid", false);

	// Miscellaneous
	_gui.getOverlay()->createTextField("billboardID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true, false);
	_isEditorLoaded = true;
}

void BillboardEditor::unload()
{
	// GUI
	_unloadGUI();

	// Camera
	if(_fe3d.camera_isThirdPersonViewEnabled())
	{
		_fe3d.camera_disableThirdPersonView();
	}

	// Default graphics
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableBloom(true);
	_fe3d.gfx_disableShadows(true);

	// Delete models
	_fe3d.model_deleteAll();

	// Delete billboards
	_fe3d.billboard_deleteAll();

	// Delete billboard ID TextField
	_gui.getOverlay()->deleteTextField("billboardID");

	// Reset editor properties
	_loadedBillboardIDs.clear();
	_hoveredBillboardID = "";
	_currentBillboardID = "";
	_isCreatingBillboard = false;
	_isChoosingBillboard = false;
	_isDeletingBillboard = false;
	_isEditorLoaded = false;

	// Miscellaneous
	if(_fe3d.misc_isDebugRenderingEnabled())
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
	leftWindow->getScreen("billboardEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create Billboard"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Billboard", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit Billboard"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Billboard", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete Billboard"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Billboard", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: billboardEditorMenuChoice
	positions = VPC::calculateButtonPositions(6, CH);
	leftWindow->createScreen("billboardEditorMenuChoice");
	leftWindow->getScreen("billboardEditorMenuChoice")->createButton("size", fvec2(0.0f, positions[0]), fvec2(TW("Size"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuChoice")->createButton("texturing", fvec2(0.0f, positions[1]), fvec2(TW("Texturing"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Texturing", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuChoice")->createButton("lighting", fvec2(0.0f, positions[2]), fvec2(TW("Lighting"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lighting", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuChoice")->createButton("miscellaneous", fvec2(0.0f, positions[3]), fvec2(TW("Miscellaneous"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Miscellaneous", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[4]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: billboardEditorMenuTexturing
	positions = VPC::calculateButtonPositions(7, CH);
	leftWindow->createScreen("billboardEditorMenuTexturing");
	leftWindow->getScreen("billboardEditorMenuTexturing")->createButton("font", fvec2(0.0f, positions[0]), fvec2(TW("Font"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Font", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuTexturing")->createButton("textContent", fvec2(0.0f, positions[1]), fvec2(TW("Text Content"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Text Content", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuTexturing")->createButton("diffuseMap", fvec2(0.0f, positions[2]), fvec2(TW("Diffuse Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Diffuse Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuTexturing")->createButton("emissionMap", fvec2(0.0f, positions[3]), fvec2(TW("Emission Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Emission Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuTexturing")->createButton("clearMaps", fvec2(0.0f, positions[4]), fvec2(TW("Clear Maps"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Clear Maps", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuTexturing")->createButton("textureRepeat", fvec2(0.0f, positions[5]), fvec2(TW("Texture Repeat"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Texture Repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuTexturing")->createButton("back", fvec2(0.0f, positions[6]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: billboardEditorMenuLighting
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("billboardEditorMenuLighting");
	leftWindow->getScreen("billboardEditorMenuLighting")->createButton("color", fvec2(0.0f, positions[0]), fvec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuLighting")->createButton("lightness", fvec2(0.0f, positions[1]), fvec2(TW("Lightness"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuLighting")->createButton("isShadowed", fvec2(0.0f, positions[2]), fvec2(TW("Shadowed: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Shadowed: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuLighting")->createButton("isReflected", fvec2(0.0f, positions[3]), fvec2(TW("Reflected: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflected: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuLighting")->createButton("back", fvec2(0.0f, positions[4]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: billboardEditorMenuMiscellaneous
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("billboardEditorMenuMiscellaneous");
	leftWindow->getScreen("billboardEditorMenuMiscellaneous")->createButton("isFacingX", fvec2(0.0f, positions[0]), fvec2(TW("Facing X: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Facing X: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuMiscellaneous")->createButton("isFacingY", fvec2(0.0f, positions[1]), fvec2(TW("Facing Y: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Facing Y: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("billboardEditorMenuMiscellaneous")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
}

void BillboardEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("billboardEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("billboardEditorMenuChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("billboardEditorMenuTexturing");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("billboardEditorMenuLighting");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("billboardEditorMenuMiscellaneous");
}

void BillboardEditor::update()
{
	if(_isEditorLoaded)
	{
		_updateMainMenu();
	}
	if(_isEditorLoaded)
	{
		_updateChoiceMenu();
	}
	if(_isEditorLoaded)
	{
		_updateTexturingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateLightingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneousMenu();
	}
	if(_isEditorLoaded)
	{
		_updateBillboardCreating();
	}
	if(_isEditorLoaded)
	{
		_updateBillboardChoosing();
	}
	if(_isEditorLoaded)
	{
		_updateBillboardDeleting();
	}
	if(_isEditorLoaded)
	{
		_updateCamera();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}