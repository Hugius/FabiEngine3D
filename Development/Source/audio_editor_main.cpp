#include "audio_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

#define CW(text) VPC::calculateTextWidth(text, 0.115f)

constexpr auto TH = 0.0875f;

AudioEditor::AudioEditor(FabiEngine3D& fe3d, EngineGuiManager& gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void AudioEditor::load()
{
	// GUI
	_loadGUI();

	// Miscellaneous
	_fe3d.gfx_enableBloom(BloomType::PARTS, 1.0f, 5);
	_fe3d.billboardEntity_create("@@icon", "engine_assets\\textures\\stop.png",
		Vec3(0.0f, -0.5f, -1.5f), Vec3(0.0f), Vec2(1.0f), true, false, false);
	_fe3d.billboardEntity_setBright("@@icon", true);
	_fe3d.camera_reset();
	_fe3d.camera_setYaw(-90.0f);
	_gui.getGlobalScreen()->addTextfield("selectedAudioName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("audioEditorControls");
	_isEditorLoaded = true;
}

void AudioEditor::unload()
{
	// GUI
	_unloadGUI();

	// Delete sounds
	_fe3d.soundEntity_deleteAll();

	// Miscellaneous
	_fe3d.gfx_disableBloom(true);
	_fe3d.billboardEntity_delete("@@icon");
	_gui.getGlobalScreen()->deleteTextfield("selectedAudioName");
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");

	// Reset editor properties
	_loadedAudioIDs.clear();
	_currentAudioID = "";
	_hoveredAudioID = "";
	_isCreatingAudio = false;
	_isChoosingAudio = false;
	_isEditingAudio = false;
	_isDeletingAudio = false;

	// Miscellaneous
	_isEditorLoaded = false;
}

void AudioEditor::_loadGUI()
{
	// Private window instance of left viewport
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - audioEditorMenuMain
	leftWindow->addScreen("audioEditorMenuMain");
	leftWindow->getScreen("audioEditorMenuMain")->addButton("add", Vec2(0.0f, 0.63f), Vec2(CW("Add Audio"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Add Audio", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("audioEditorMenuMain")->addButton("edit", Vec2(0.0f, 0.21f), Vec2(CW("Edit Audio"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Audio", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("audioEditorMenuMain")->addButton("delete", Vec2(0.0f, -0.21f), Vec2(CW("Delete Audio"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Audio", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("audioEditorMenuMain")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - audioEditorMenuChoice
	leftWindow->addScreen("audioEditorMenuChoice");
	leftWindow->getScreen("audioEditorMenuChoice")->addButton("load", Vec2(0.0f, 0.75f), Vec2(CW("Load WAV"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Load WAV", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("audioEditorMenuChoice")->addButton("play", Vec2(0.0f, 0.45f), Vec2(CW("Play"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Play", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("audioEditorMenuChoice")->addButton("resume", Vec2(0.0f, 0.15f), Vec2(CW("Resume"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Resume", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("audioEditorMenuChoice")->addButton("pause", Vec2(0.0f, -0.15f), Vec2(CW("Pause"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Pause", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("audioEditorMenuChoice")->addButton("stop", Vec2(0.0f, -0.45f), Vec2(CW("Stop"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Stop", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("audioEditorMenuChoice")->addButton("back", Vec2(0.0f, -0.75f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void AudioEditor::_unloadGUI()
{
	auto leftWindow = _gui.getViewport("left")->getWindow("main");
	leftWindow->deleteScreen("audioEditorMenuMain");
	leftWindow->deleteScreen("audioEditorMenuChoice");
}