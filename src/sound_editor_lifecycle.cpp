#define TW(text) VPC::calculateTextWidth(text, CW)

#include "sound_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

SoundEditor::SoundEditor(EngineInterface& fe3d, GuiManager& gui)
	:
	_fe3d(fe3d),
	_gui(gui)
{

}

void SoundEditor::load()
{
	_loadGUI();

	_fe3d->gfx_enableAntiAliasing();
	_fe3d->gfx_setAnisotropicFilteringQuality(Config::MAX_ANISOTROPIC_FILTERING_QUALITY);
	_fe3d->gfx_enableBloom();
	_fe3d->gfx_setBloomType(BloomType::PARTS);
	_fe3d->gfx_setBloomIntensity(1.0f);
	_fe3d->gfx_setBloomBlurCount(5);
	_fe3d->gfx_setBloomQuality(Config::MAX_BLOOM_QUALITY);

	_fe3d->camera_reset();
	_fe3d->camera_setYaw(270.0f);

	_fe3d->billboard_create("@@icon", true);
	_fe3d->billboard_setPosition("@@icon", ICON_BILLBOARD_POSITION);
	_fe3d->billboard_setDiffuseMap("@@icon", "engine\\assets\\image\\diffuse_map\\stop.tga");
	_fe3d->billboard_setBright("@@icon", true);

	_gui->getOverlay()->createTextField("soundID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(0.0f), true);

	_isEditorLoaded = true;
}

void SoundEditor::unload()
{
	for(const auto& ID : _loadedSoundIDs)
	{
		_fe3d->sound2d_delete(ID);
	}

	_unloadGUI();

	_fe3d->gfx_disableAntiAliasing(true);
	_fe3d->gfx_setAnisotropicFilteringQuality(Config::MIN_ANISOTROPIC_FILTERING_QUALITY);
	_fe3d->gfx_disableBloom(true);

	_fe3d->billboard_delete("@@icon");

	_gui->getOverlay()->deleteTextField("soundID");

	_loadedSoundIDs.clear();
	_currentSoundID = "";
	_hoveredSoundID = "";
	_isEditorLoaded = false;
	_isCreatingSound = false;
	_isChoosingSound = false;
	_isDeletingSound = false;
}

void SoundEditor::_loadGUI()
{
	auto leftWindow = _gui->getViewport("left")->getWindow("main");

	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("soundEditorMenuMain");
	leftWindow->getScreen("soundEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create Sound"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Sound", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit Sound"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Sound", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete Sound"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Sound", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("soundEditorMenuChoice");
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("play", fvec2(0.0f, positions[0]), fvec2(TW("Play"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Play", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("resume", fvec2(0.0f, positions[1]), fvec2(TW("Resume"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Resume", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("pause", fvec2(0.0f, positions[2]), fvec2(TW("Pause"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Pause", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("stop", fvec2(0.0f, positions[3]), fvec2(TW("Stop"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Stop", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[4]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
}

void SoundEditor::_unloadGUI()
{
	_gui->getViewport("left")->getWindow("main")->deleteScreen("soundEditorMenuMain");
	_gui->getViewport("left")->getWindow("main")->deleteScreen("soundEditorMenuChoice");
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