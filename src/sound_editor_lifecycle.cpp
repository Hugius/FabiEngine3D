#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "sound_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void SoundEditor::_load()
{
	_fe3d->quad3d_create("@@status", true);
	_fe3d->quad3d_setPosition("@@status", STATUS_QUAD3D_POSITION);
	_fe3d->quad3d_setDiffuseMap("@@status", "engine\\assets\\image\\diffuse_map\\stop.tga");
	_fe3d->quad3d_setBright("@@status", true);

	_fe3d->graphics_setAntiAliasingEnabled(true);
	_fe3d->graphics_setAnisotropicFilteringQuality(16);
	_fe3d->graphics_setBloomEnabled(true);
	_fe3d->graphics_setBloomType(BloomType::PARTS);
	_fe3d->graphics_setBloomIntensity(1.0f);
	_fe3d->graphics_setBloomBlurCount(5);
	_fe3d->graphics_setBloomQuality(5);

	_fe3d->camera_setYaw(270.0f);

	_gui->getOverlay()->createTextField("soundId", fvec2(0.0f, 0.85f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
}

void SoundEditor::_unload()
{
	for(const auto & soundId : _loadedSoundIds)
	{
		_fe3d->sound2d_delete(soundId);
	}

	_fe3d->quad3d_delete("@@status");

	_fe3d->graphics_setAntiAliasingEnabled(false);
	_fe3d->graphics_setAnisotropicFilteringQuality(0);
	_fe3d->graphics_setBloomEnabled(false);
	_fe3d->graphics_setBloomType(BloomType::EVERYTHING);
	_fe3d->graphics_setBloomIntensity(0.0f);
	_fe3d->graphics_setBloomBlurCount(0);
	_fe3d->graphics_setBloomQuality(0);

	_fe3d->camera_reset();

	_gui->getOverlay()->deleteTextField("soundId");

	_loadedSoundIds.clear();
}

void SoundEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = Mathematics::calculateDistributedPositions(4, CH, false);
	leftWindow->createScreen("soundEditorMenuMain");
	leftWindow->getScreen("soundEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create Sound"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Sound", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Sound"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Sound", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), TEXT_SIZE("Delete Sound"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Sound", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(5, CH, false);
	leftWindow->createScreen("soundEditorMenuChoice");
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("play", fvec2(0.0f, positions[0]), TEXT_SIZE("Play"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Play", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("pause", fvec2(0.0f, positions[1]), TEXT_SIZE("Pause"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Pause", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("resume", fvec2(0.0f, positions[2]), TEXT_SIZE("Resume"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Resume", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("stop", fvec2(0.0f, positions[3]), TEXT_SIZE("Stop"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Stop", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[4]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);
}

void SoundEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("soundEditorMenuMain");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("soundEditorMenuChoice");
}

void SoundEditor::update()
{
	if(isLoaded())
	{
		_updateMainMenu();
	}
	if(isLoaded())
	{
		_updateChoiceMenu();
	}
	if(isLoaded())
	{
		_updateSoundCreating();
	}
	if(isLoaded())
	{
		_updateSoundChoosing();
	}
	if(isLoaded())
	{
		_updateSoundDeleting();
	}
	if(isLoaded())
	{
		_updateMiscellaneous();
	}
}