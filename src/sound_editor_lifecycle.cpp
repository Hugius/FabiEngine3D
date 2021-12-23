#include "sound_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

#define TW(text) VPC::calculateTextWidth(text, CW)

SoundEditor::SoundEditor(FabiEngine3D& fe3d, GuiManager& gui)
	:
	_fe3d(fe3d),
	_gui(gui)
{

}

void SoundEditor::load()
{
	// GUI
	_loadGUI();

	// Graphics
	_fe3d.gfx_enableAntiAliasing();
	_fe3d.gfx_setAnisotropicFilteringQuality(Config::MAX_ANISOTROPIC_FILTERING_QUALITY);
	_fe3d.gfx_enableBloom();
	_fe3d.gfx_setBloomType(BloomType::PARTS);
	_fe3d.gfx_setBloomIntensity(1.0f);
	_fe3d.gfx_setBloomBlurCount(5);
	_fe3d.gfx_setBloomQuality(Config::MAX_BLOOM_QUALITY);

	// Camera
	_fe3d.camera_reset();
	_fe3d.camera_setYaw(270.0f);

	// Editor billboards
	_fe3d.billboard_create("@@icon");
	_fe3d.billboard_setPosition("@@icon", fvec3(0.0f, -0.5f, -1.5f));
	_fe3d.billboard_setDiffuseMap("@@icon", "engine\\assets\\texture\\stop.png");
	_fe3d.billboard_setBright("@@icon", true);

	// Miscellaneous
	_gui.getOverlay()->createTextField("soundID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true, false);
	_isEditorLoaded = true;
}

void SoundEditor::unload()
{
	// GUI
	_unloadGUI();

	// Graphics
	_fe3d.gfx_disableAntiAliasing(true);
	_fe3d.gfx_setAnisotropicFilteringQuality(Config::MIN_ANISOTROPIC_FILTERING_QUALITY);
	_fe3d.gfx_disableBloom(true);

	// Billboards
	_fe3d.billboard_deleteAll();

	// Sounds
	_fe3d.sound2d_deleteAll();

	// Editor properties
	_loadedSoundIDs.clear();
	_currentSoundID = "";
	_hoveredSoundID = "";
	_isEditorLoaded = false;
	_isCreatingSound = false;
	_isChoosingSound = false;
	_isDeletingSound = false;

	// Miscellaneous
	_gui.getOverlay()->deleteTextField("soundID");
}

void SoundEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: soundEditorMenuMain
	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("soundEditorMenuMain");
	leftWindow->getScreen("soundEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create Sound"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Sound", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("soundEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit Sound"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Sound", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("soundEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete Sound"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Sound", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("soundEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: soundEditorMenuChoice
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("soundEditorMenuChoice");
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("play", fvec2(0.0f, positions[0]), fvec2(TW("Play"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Play", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("resume", fvec2(0.0f, positions[1]), fvec2(TW("Resume"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Resume", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("pause", fvec2(0.0f, positions[2]), fvec2(TW("Pause"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Pause", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("stop", fvec2(0.0f, positions[3]), fvec2(TW("Stop"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Stop", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[4]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
}

void SoundEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("soundEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("soundEditorMenuChoice");
}

void SoundEditor::update()
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
		_updateSoundCreating();
	}
	if(_isEditorLoaded)
	{
		_updateSoundChoosing();
	}
	if(_isEditorLoaded)
	{
		_updateSoundDeleting();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}