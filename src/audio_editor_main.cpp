#include "audio_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

#define TW(text) VPC::calculateTextWidth(text, CW)

AudioEditor::AudioEditor(FabiEngine3D& fe3d, EngineGuiManager& gui)
	:
	_fe3d(fe3d),
	_gui(gui)
{

}

void AudioEditor::load()
{
	// GUI
	_loadGUI();

	// Default graphics
	_fe3d.gfx_enableBloom();
	_fe3d.gfx_setBloomType(BloomType::PARTS);
	_fe3d.gfx_setBloomIntensity(1.0f);
	_fe3d.gfx_setBloomBlurCount(5);

	// Camera
	_fe3d.camera_reset();
	_fe3d.camera_setYaw(270.0f);

	// Editor billboards
	_fe3d.billboardEntity_create("@@icon");
	_fe3d.billboardEntity_setPosition("@@icon", Vec3(0.0f, -0.5f, -1.5f));
	_fe3d.billboardEntity_setDiffuseMap("@@icon", "engine\\textures\\stop.png");
	_fe3d.billboardEntity_setBright("@@icon", true);

	// Miscellaneous
	_gui.getGlobalScreen()->createTextField("audioID", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f), true, false);
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("audioEditorControls");
	_isEditorLoaded = true;
}

void AudioEditor::unload()
{
	// GUI
	_unloadGUI();

	// Default graphics
	_fe3d.gfx_disableBloom(true);

	// Delete created entities
	_fe3d.sound_deleteAll();
	_fe3d.billboardEntity_delete("@@icon");

	// Reset editor properties
	_loadedAudioIDs.clear();
	_currentAudioID = "";
	_hoveredAudioID = "";
	_isEditorLoaded = false;
	_isCreatingAudio = false;
	_isChoosingAudio = false;
	_isDeletingAudio = false;

	// Miscellaneous
	_gui.getGlobalScreen()->deleteTextField("audioID");
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
}

void AudioEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: audioEditorMenuMain
	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("audioEditorMenuMain");
	leftWindow->getScreen("audioEditorMenuMain")->createButton("create", Vec2(0.0f, positions[0]), Vec2(TW("Create Audio"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Audio", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("audioEditorMenuMain")->createButton("edit", Vec2(0.0f, positions[1]), Vec2(TW("Edit Audio"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Audio", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("audioEditorMenuMain")->createButton("delete", Vec2(0.0f, positions[2]), Vec2(TW("Delete Audio"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Audio", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("audioEditorMenuMain")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: audioEditorMenuChoice
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("audioEditorMenuChoice");
	leftWindow->getScreen("audioEditorMenuChoice")->createButton("play", Vec2(0.0f, positions[0]), Vec2(TW("Play"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Play", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("audioEditorMenuChoice")->createButton("resume", Vec2(0.0f, positions[1]), Vec2(TW("Resume"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Resume", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("audioEditorMenuChoice")->createButton("pause", Vec2(0.0f, positions[2]), Vec2(TW("Pause"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Pause", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("audioEditorMenuChoice")->createButton("stop", Vec2(0.0f, positions[3]), Vec2(TW("Stop"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Stop", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("audioEditorMenuChoice")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
}

void AudioEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("audioEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("audioEditorMenuChoice");
}