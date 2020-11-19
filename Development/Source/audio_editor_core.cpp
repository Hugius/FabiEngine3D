#include "audio_editor.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVPC::calcTextWidth(text, 0.15f, 1.8f)

AudioEditor::AudioEditor(FabiEngine3D& fe3d, EngineGuiManager& gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void AudioEditor::initializeGUI()
{
	// Private window instance of left viewport
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - audioEditorMenuMain
	leftWindow->addScreen("audioEditorMenuMain");
	leftWindow->getScreen("audioEditorMenuMain")->addButton("addAudio", vec2(0.0f, 0.63f), vec2(GW("Add audio"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Add audio", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("audioEditorMenuMain")->addButton("editAudio", vec2(0.0f, 0.21), vec2(GW("Edit audio"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit audio", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("audioEditorMenuMain")->addButton("deleteAudio", vec2(0.0f, -0.21), vec2(GW("Delete audio"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Delete audio", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("audioEditorMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - audioEditorMenuChoice
	leftWindow->addScreen("audioEditorMenuChoice");
	leftWindow->getScreen("audioEditorMenuChoice")->addButton("load", vec2(0.0f, 0.75f), vec2(GW("Load MP3"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Load MP3", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("audioEditorMenuChoice")->addButton("play", vec2(0.0f, 0.45f), vec2(GW("Play"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Play", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("audioEditorMenuChoice")->addButton("resume", vec2(0.0f, 0.15f), vec2(GW("Resume"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Resume", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("audioEditorMenuChoice")->addButton("pause", vec2(0.0f, -0.15f), vec2(GW("Pause"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Pause", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("audioEditorMenuChoice")->addButton("stop", vec2(0.0f, -0.45f), vec2(GW("Stop"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Stop", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("audioEditorMenuChoice")->addButton("back", vec2(0.0f, -0.75f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
}

void AudioEditor::load()
{
	// Load all audio entities
	loadAudioEntitiesFromFile();

	// Miscellaneous
	_fe3d.billBoardEntity_add("@@audioStatus", "engine\\textures\\stop.png", vec3(0.0f, 0.0f, -1.5f), vec3(0.0f), vec2(1.0f), true, false, false, true);
	_fe3d.camera_load(90.0f, 0.1f, 100.0f, vec3(0.0f), -90.0f);
	_gui.getGlobalScreen()->addTextfield("selectedAudioName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_isLoaded = true;
}

void AudioEditor::unload()
{
	_fe3d.billboardEntity_delete("@@audioStatus");
	_fe3d.audioEntity_deleteAll();
	_gui.getGlobalScreen()->deleteTextfield("selectedAudioName");
	_isLoaded = false;
}