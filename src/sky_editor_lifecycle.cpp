#include "sky_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

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
	_fe3d.camera_setCursorSensitivity(CURSOR_SENSITIVITY);

	// Default graphics
	_fe3d.gfx_enableMotionBlur();
	_fe3d.gfx_setMotionBlurStrength(0.1f);
	_fe3d.gfx_setMotionBlurQuality(Config::MAX_MOTION_BLUR_QUALITY);

	// Miscellaneous
	_gui.getGlobalScreen()->createTextField("skyID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true, false);
	_isEditorLoaded = true;
}

void SkyEditor::unload()
{
	// GUI
	_unloadGUI();

	// Default graphics
	_fe3d.gfx_disableMotionBlur(true);

	// Delete all sky entities except the background
	for (const auto& ID : _fe3d.sky_getAllIDs())
	{
		if (ID != "@@background")
		{
			_fe3d.sky_delete(ID);
		}
	}

	// Reset editor properties
	_loadedSkyIDs.clear();
	_currentSkyID = "";
	_isEditorLoaded = false;
	_isCreatingSky = false;
	_isChoosingSky = false;
	_isDeletingSky = false;

	// Miscellaneous
	_gui.getGlobalScreen()->deleteTextField("skyID");
	if(_fe3d.camera_isThirdPersonViewEnabled())
	{
		_fe3d.camera_disableThirdPersonView();
	}
	if(_fe3d.misc_isDebugRenderingEnabled())
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
	leftWindow->getScreen("skyEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("skyEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("skyEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("skyEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: skyEditorMenuChoice
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("skyEditorMenuChoice");
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("texturing", fvec2(0.0f, positions[0]), fvec2(TW("Texturing"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Texturing", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("miscellaneous", fvec2(0.0f, positions[1]), fvec2(TW("Miscellaneous"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Miscellaneous", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: skyEditorMenuTexturing
	positions = VPC::calculateButtonPositions(8, CH);
	leftWindow->createScreen("skyEditorMenuTexturing");
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("leftMap", fvec2(0.0f, positions[0]), fvec2(TW("Left Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Left Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("rightMap", fvec2(0.0f, positions[1]), fvec2(TW("Right Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Right Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("frontMap", fvec2(0.0f, positions[2]), fvec2(TW("Front Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Front Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("backMap", fvec2(0.0f, positions[3]), fvec2(TW("Back Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Back Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("topMap", fvec2(0.0f, positions[4]), fvec2(TW("Top Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Top Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("bottomMap", fvec2(0.0f, positions[5]), fvec2(TW("Bottom Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Bottom Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("clearMaps", fvec2(0.0f, positions[6]), fvec2(TW("Clear Maps"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Clear Maps", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("back", fvec2(0.0f, positions[7]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: skyEditorMenuMiscellaneous
	positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("skyEditorMenuMiscellaneous");
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("rotation", fvec2(0.0f, positions[0]), fvec2(TW("Rotation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rotation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("lightness", fvec2(0.0f, positions[1]), fvec2(TW("Lightness"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("color", fvec2(0.0f, positions[2]), fvec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
}

void SkyEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("skyEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("skyEditorMenuChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("skyEditorMenuTexturing");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("skyEditorMenuMiscellaneous");
}

void SkyEditor::update()
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
		_updateMiscellaneousMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSkyCreating();
	}
	if(_isEditorLoaded)
	{
		_updateSkyChoosing();
	}
	if(_isEditorLoaded)
	{
		_updateSkyDeleting();
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