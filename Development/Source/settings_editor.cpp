#include "settings_editor.hpp"
#include "left_viewport_controller.hpp"

#include <fstream>
#include <sstream>

#define GET_WIDTH(text) LVC::calcTextWidth(text, 0.15f, 1.8f)

SettingsEditor::SettingsEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void SettingsEditor::initializeGUI()
{
	// Private window instance of GUI windows
	_leftWindow = _gui->getViewport("left")->getWindow("main");
	string screenID;

	// Left-viewport: mainWindow - settingsEditorMenuMain
	screenID = "settingsEditorMenuMain";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("mouseSensitivity", vec2(0.0f, 0.7875f), vec2(GET_WIDTH("Mouse speed"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Mouse speed", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("msaaQuality", vec2(0.0f, 0.525f), vec2(GET_WIDTH("MSAA"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "MSAA", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("shadowQuality", vec2(0.0f, 0.2625f), vec2(GET_WIDTH("Shadows"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Shadows", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("reflectionQuality", vec2(0.0f, 0.0f), vec2(GET_WIDTH("Reflections"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Reflections", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("refractionQuality", vec2(0.0f, -0.2625f), vec2(GET_WIDTH("Refractions"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Refractions", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("maxAudioChannels", vec2(0.0f, -0.525f), vec2(GET_WIDTH("Audio"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Audio", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.7875f), vec2(GET_WIDTH("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);
}

void SettingsEditor::load()
{
	string filePath = _fe3d.misc_getRootDirectory() + "User\\Settings.fe3d";

	// Check if settings file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Open settings file
		std::ifstream file(filePath);
		string line;
		std::getline(file, line);
		std::istringstream iss(line);

		// Extract values from file
		float mouse;
		int msaa, shadow, reflection, refraction, audio;
		iss >> mouse >> msaa >> shadow >> reflection >> refraction >> audio;

		// Set values
		_fe3d.camera_setMouseSensitivity(mouse);
		_fe3d.gfx_setMsaaQuality(msaa);
		_fe3d.gfx_setShadowQuality(shadow);
		_fe3d.gfx_setReflectionQuality(reflection);
		_fe3d.gfx_setRefractionQuality(refraction);
		_fe3d.audio_setMaxChannels(audio);
		std::cout << _fe3d.gfx_getShadowQuality();

		// Close file
		file.close();
	}

	_isLoaded = true;
}

void SettingsEditor::save()
{
	// Overwrite (or create) settings file
	std::ofstream file;
	file.open(_fe3d.misc_getRootDirectory() + "User\\Settings.fe3d");

	// Get values
	float mouse = _fe3d.camera_getMouseSensitivity();
	int msaa = _fe3d.gfx_getMsaaQuality();
	int shadow = _fe3d.gfx_getShadowQuality();
	int reflection = _fe3d.gfx_getReflectionQuality();
	int refraction = _fe3d.gfx_getRefractionQuality();
	int audio = _fe3d.audio_getMaxChannels();

	// Write to file
	file << mouse << " " << msaa << " " << shadow << " " << reflection << " " << refraction << " " << audio;

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
			float mouse = _fe3d.camera_getMouseSensitivity();
			int msaa = _fe3d.gfx_getMsaaQuality();
			int shadow = _fe3d.gfx_getShadowQuality();
			int reflection = _fe3d.gfx_getReflectionQuality();
			int refraction = _fe3d.gfx_getRefractionQuality();
			int audio = _fe3d.audio_getMaxChannels();

			// GUI management
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("mouseSensitivity")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("mouseSensitivity", "Mouse sensitivity", mouse, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("msaaQuality")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("msaaQuality", "MSAA quality", msaa, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("shadowQuality")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("shadowQuality", "Shadow quality", shadow, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("reflectionQuality")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("reflectionQuality", "Reflection quality", reflection, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("refractionQuality")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("refractionQuality", "Refraction quality", refraction, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("maxAudioChannels")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("maxAudioChannels", "Max audio channels", audio, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("back")->isHovered())
				{
					_leftWindow->setActiveScreen("main");
				}
			}

			// Update forms
			if (_gui->getGlobalScreen()->checkValueForm("mouseSensitivity", mouse, {}))
			{
				_fe3d.camera_setMouseSensitivity(mouse);
				save();
			}
			else if (_gui->getGlobalScreen()->checkValueForm("msaaQuality", msaa, {}))
			{
				_fe3d.gfx_setMsaaQuality(msaa);
				save();
			}
			else if (_gui->getGlobalScreen()->checkValueForm("shadowQuality", shadow, {}))
			{
				_fe3d.gfx_setShadowQuality(shadow);
				save();
			}
			else if (_gui->getGlobalScreen()->checkValueForm("reflectionQuality", reflection, {}))
			{
				_fe3d.gfx_setReflectionQuality(reflection);
				save();
			}
			else if (_gui->getGlobalScreen()->checkValueForm("refractionQuality", refraction, {}))
			{
				_fe3d.gfx_setRefractionQuality(refraction);
				save();
			}
			else if (_gui->getGlobalScreen()->checkValueForm("maxAudioChannels", audio, {}))
			{
				_fe3d.audio_setMaxChannels(audio);
				save();
			}
		}
	}
}