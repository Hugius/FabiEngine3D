#include "sky_editor.hpp"
#include "left_viewport_controller.hpp"

#define TW(text) VPC::calculateTextWidth(text, CW)

SkyEditor::SkyEditor(FabiEngine3D& fe3d, EngineGuiManager& gui)
	:
	_fe3d(fe3d),
	_gui(gui)
{

}

void SkyEditor::load()
{
	// GUI
	_loadGUI();

	// Camera
	_fe3d.camera_reset();
	_fe3d.camera_setMouseSensitivity(MOUSE_SENSITIVITY);
	
	// Default graphics
	_fe3d.gfx_enableMotionBlur(0.1f);

	// Miscellaneous
	_gui.getGlobalScreen()->createTextField("skyID", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("skyEditorControls");
	_isEditorLoaded = true;
}

void SkyEditor::unload()
{
	// GUI
	_unloadGUI();

	// Default graphics
	_fe3d.gfx_disableMotionBlur(true);

	// Delete skies
	unloadSkyEntities();

	// Reset editor properties
	_loadedSkyIDs.clear();
	_currentSkyID = "";
	_isEditorLoaded = false;
	_isCreatingSky = false;
	_isChoosingSky = false;
	_isDeletingSky = false;

	// Miscellaneous
	_gui.getGlobalScreen()->deleteTextField("skyID");
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

void SkyEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: skyEditorMenuMain
	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("skyEditorMenuMain");
	leftWindow->getScreen("skyEditorMenuMain")->createButton("create", Vec2(0.0f, positions[0]), Vec2(TW("Create Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMain")->createButton("edit", Vec2(0.0f, positions[1]), Vec2(TW("Edit Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMain")->createButton("delete", Vec2(0.0f, positions[2]), Vec2(TW("Delete Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMain")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: skyEditorMenuChoice
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("skyEditorMenuChoice");
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("texturing", Vec2(0.0f, positions[0]), Vec2(TW("Texturing"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Texturing", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("miscellaneous", Vec2(0.0f, positions[1]), Vec2(TW("Miscellaneous"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Miscellaneous", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: skyEditorMenuTexturing
	positions = VPC::calculateButtonPositions(8, CH);
	leftWindow->createScreen("skyEditorMenuTexturing");
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("leftMap", Vec2(0.0f, positions[0]), Vec2(TW("Left Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Left Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("rightMap", Vec2(0.0f, positions[1]), Vec2(TW("Right Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Right Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("frontMap", Vec2(0.0f, positions[2]), Vec2(TW("Front Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Front Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("backMap", Vec2(0.0f, positions[3]), Vec2(TW("Back Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Back Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("topMap", Vec2(0.0f, positions[4]), Vec2(TW("Top Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Top Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("bottomMap", Vec2(0.0f, positions[5]), Vec2(TW("Bottom Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Bottom Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("clearMaps", Vec2(0.0f, positions[6]), Vec2(TW("Clear Maps"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Clear Maps", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("back", Vec2(0.0f, positions[7]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: skyEditorMenuMiscellaneous
	positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("skyEditorMenuMiscellaneous");
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("rotationSpeed", Vec2(0.0f, positions[0]), Vec2(TW("Rotation Speed"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rotation Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("lightness", Vec2(0.0f, positions[1]), Vec2(TW("Lightness"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("color", Vec2(0.0f, positions[2]), Vec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void SkyEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("skyEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("skyEditorMenuChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("skyEditorMenuTexturing");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("skyEditorMenuMiscellaneous");
}