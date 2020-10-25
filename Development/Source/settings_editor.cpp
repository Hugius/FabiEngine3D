#include "settings_editor.hpp"
#include "left_viewport_controller.hpp"

#include <fstream>
#include <sstream>

#define GW(text) LVPC::calcTextWidth(text, 0.15f, 1.8f)

SettingsEditor::SettingsEditor(FabiEngine3D& fe3d, EngineGuiManager& gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void SettingsEditor::initializeGUI()
{
	// Private window instance of GUI windows
	_leftWindow = _gui.getViewport("left")->getWindow("main");
	string screenID;

	// Left-viewport: mainWindow - settingsEditorMenuMain
	screenID = "settingsEditorMenuMain";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("mouseSensitivity", vec2(0.0f, 0.7875f), vec2(GW("Mouse speed"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Mouse speed", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("msaaQuality", vec2(0.0f, 0.525f), vec2(GW("MSAA"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "MSAA", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("shadowQuality", vec2(0.0f, 0.2625f), vec2(GW("Shadows"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Shadows", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("reflectionQuality", vec2(0.0f, 0.0f), vec2(GW("Reflections"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Reflections", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("refractionQuality", vec2(0.0f, -0.2625f), vec2(GW("Refractions"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Refractions", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("maxAudioChannels", vec2(0.0f, -0.525f), vec2(GW("Audio"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Audio", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.7875f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
}

void SettingsEditor::load()
{
	string filePath = _fe3d.misc_getRootDirectory() + "user\\settings.fe3d";

	// Check if settings file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Open settings file
		std::ifstream file(filePath);
		string line;
		std::getline(file, line);
		std::istringstream iss(line);

		// Extract values from file
		float mouseSpeed;
		int msaaQuality, shadowQuality, reflectionQuality, refractionQuality, audioChannels;
		iss >> mouseSpeed >> msaaQuality >> shadowQuality >> reflectionQuality >> refractionQuality >> audioChannels;

		// Set values
		_fe3d.camera_setMouseSensitivity(mouseSpeed);
		_fe3d.gfx_setMsaaQuality(msaaQuality);
		_fe3d.gfx_setShadowQuality(shadowQuality);
		_fe3d.gfx_setReflectionQuality(reflectionQuality);
		_fe3d.gfx_setRefractionQuality(refractionQuality);
		_fe3d.audio_setMaxChannels(audioChannels);

		// Close file
		file.close();
	}

	_isLoaded = true;
}

void SettingsEditor::save()
{
	// Overwrite (or create) settings file
	std::ofstream file;
	file.open(_fe3d.misc_getRootDirectory() + "user\\settings.fe3d");

	// Get values
	float mouseSpeed = _fe3d.camera_getMouseSensitivity();
	int msaaQuality = _fe3d.gfx_getMsaaQuality();
	int shadowQuality = _fe3d.gfx_getShadowQuality();
	int reflectionQuality = _fe3d.gfx_getReflectionQuality();
	int refractionQuality = _fe3d.gfx_getRefractionQuality();
	int audioChannels = _fe3d.audio_getMaxChannels();

	// Write to file
	file << 
		mouseSpeed << " " << 
		msaaQuality << " " << 
		shadowQuality << " " << 
		reflectionQuality << " " <<
		refractionQuality << " " << 
		audioChannels;

	// Close file
	file.close();
}

void SettingsEditor::update()
{
	if (_isLoaded)
	{
		if (_leftWindow->getActiveScreen()->getID() == "settingsEditorMenuMain")
		{
			auto screen = _leftWindow->getScreen("settingsEditorMenuMain");
			float mouseSpeed = _fe3d.camera_getMouseSensitivity();
			int msaaQuality = _fe3d.gfx_getMsaaQuality();
			int shadowQuality = _fe3d.gfx_getShadowQuality();
			int reflectionQuality = _fe3d.gfx_getReflectionQuality();
			int refractionQuality = _fe3d.gfx_getRefractionQuality();
			int audioChannels = _fe3d.audio_getMaxChannels();

			// GUI management
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("mouseSensitivity")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("mouseSensitivity", "Mouse sensitivity", mouseSpeed, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("msaaQuality")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("msaaQuality", "MSAA quality", msaaQuality, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("shadowQuality")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("shadowQuality", "Shadow quality", shadowQuality, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("reflectionQuality")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("reflectionQuality", "Reflection quality", reflectionQuality, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("refractionQuality")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("refractionQuality", "Refraction quality", refractionQuality, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("maxAudioChannels")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("maxAudioChannels", "Max audio channels", audioChannels, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("back")->isHovered())
				{
					_leftWindow->setActiveScreen("main");
				}
			}

			// Update forms
			if (_gui.getGlobalScreen()->checkValueForm("mouseSensitivity", mouseSpeed, {}))
			{
				_fe3d.camera_setMouseSensitivity(mouseSpeed);
				save();
			}
			else if (_gui.getGlobalScreen()->checkValueForm("msaaQuality", msaaQuality, {}))
			{
				_fe3d.gfx_setMsaaQuality(msaaQuality);
				save();
			}
			else if (_gui.getGlobalScreen()->checkValueForm("shadowQuality", shadowQuality, {}))
			{
				_fe3d.gfx_setShadowQuality(shadowQuality);
				save();
			}
			else if (_gui.getGlobalScreen()->checkValueForm("reflectionQuality", reflectionQuality, {}))
			{
				_fe3d.gfx_setReflectionQuality(reflectionQuality);
				save();
			}
			else if (_gui.getGlobalScreen()->checkValueForm("refractionQuality", refractionQuality, {}))
			{
				_fe3d.gfx_setRefractionQuality(refractionQuality);
				save();
			}
			else if (_gui.getGlobalScreen()->checkValueForm("maxAudioChannels", audioChannels, {}))
			{
				_fe3d.audio_setMaxChannels(audioChannels);
				save();
			}
		}
	}
}