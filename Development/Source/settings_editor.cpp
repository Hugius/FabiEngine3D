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
	// Private window instance of left viewport
	auto leftWindow = _gui.getViewport("left")->getWindow("main");
	string screenID;

	// Left-viewport: mainWindow - settingsEditorMenuMain
	screenID = "settingsEditorMenuMain";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("msaaQuality", Vec2(0.0f, 0.75f), Vec2(GW("MSAA"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "MSAA", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("shadowQuality", Vec2(0.0f, 0.45f), Vec2(GW("Shadows"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Shadows", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("reflectionQuality", Vec2(0.0f, 0.15f), Vec2(GW("Reflections"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Reflections", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("refractionQuality", Vec2(0.0f, -0.15f), Vec2(GW("Refractions"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Refractions", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("maxAudioChannels", Vec2(0.0f, -0.45f), Vec2(GW("Audio"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Audio", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.75f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
}

void SettingsEditor::load()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("No current project loaded --> SettingsEditor::load()");
	}

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\settings.fe3d";

	// Check if settings file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Open settings file
		std::ifstream file(filePath);
		string line;
		std::getline(file, line);
		std::istringstream iss(line);

		// Extract values from file
		int msaaQuality, shadowQuality, reflectionQuality, refractionQuality, audioChannels;
		iss >> msaaQuality >> shadowQuality >> reflectionQuality >> refractionQuality >> audioChannels;

		// Set values
		_fe3d.gfx_setMsaaQuality(msaaQuality);
		_fe3d.gfx_setShadowQuality(shadowQuality);
		_fe3d.gfx_setReflectionQuality(reflectionQuality);
		_fe3d.gfx_setRefractionQuality(refractionQuality);
		_fe3d.sound_setMaxChannels(audioChannels);

		// Close file
		file.close();
	}
	else
	{
		_fe3d.logger_throwWarning("Project \"" + _currentProjectName + "\" corrupted: settings.fe3d missing!");
	}

	_isEditorLoaded = true;
}

void SettingsEditor::unload()
{
	_isEditorLoaded = false;
}

void SettingsEditor::save(bool newFile)
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("No current project loaded --> SettingsEditor::save()");
	}

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\settings.fe3d";

	// Overwrite (or create) settings file
	std::ofstream file;
	file.open(filePath);

	// Get values
	int msaaQuality = _fe3d.gfx_getMsaaQuality();
	int shadowQuality = _fe3d.gfx_getShadowQuality();
	int reflectionQuality = _fe3d.gfx_getReflectionQuality();
	int refractionQuality = _fe3d.gfx_getRefractionQuality();
	int audioChannels = _fe3d.sound_getMaxChannels();

	// Default values for new file
	if (newFile)
	{
		msaaQuality = 4;
		shadowQuality = 2048;
		reflectionQuality = 128;
		refractionQuality = 128;
		audioChannels = 256;
	}

	// Write to file
	file << 
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
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		if (screen->getID() == "settingsEditorMenuMain")
		{
			// Temporary values
			int msaaQuality = _fe3d.gfx_getMsaaQuality();
			int shadowQuality = _fe3d.gfx_getShadowQuality();
			int reflectionQuality = _fe3d.gfx_getReflectionQuality();
			int refractionQuality = _fe3d.gfx_getRefractionQuality();
			int audioChannels = _fe3d.sound_getMaxChannels();

			// GUI management
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
				}
				else if (screen->getButton("msaaQuality")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("msaaQuality", "MSAA quality", msaaQuality, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("shadowQuality")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("shadowQuality", "Shadow quality", shadowQuality, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("reflectionQuality")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("reflectionQuality", "Reflection quality", reflectionQuality, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("refractionQuality")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("refractionQuality", "Refraction quality", refractionQuality, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("maxAudioChannels")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("maxAudioChannels", "Max audio channels", audioChannels, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
				}
			}

			// Update forms
			if (_gui.getGlobalScreen()->checkValueForm("msaaQuality", msaaQuality, {}))
			{
				_fe3d.gfx_setMsaaQuality(msaaQuality);
				save(false);
			}
			else if (_gui.getGlobalScreen()->checkValueForm("shadowQuality", shadowQuality, {}))
			{
				_fe3d.gfx_setShadowQuality(shadowQuality);
				save(false);
			}
			else if (_gui.getGlobalScreen()->checkValueForm("reflectionQuality", reflectionQuality, {}))
			{
				_fe3d.gfx_setReflectionQuality(reflectionQuality);
				save(false);
			}
			else if (_gui.getGlobalScreen()->checkValueForm("refractionQuality", refractionQuality, {}))
			{
				_fe3d.gfx_setRefractionQuality(refractionQuality);
				save(false);
			}
			else if (_gui.getGlobalScreen()->checkValueForm("maxAudioChannels", audioChannels, {}))
			{
				_fe3d.sound_setMaxChannels(audioChannels);
				save(false);
			}
		}
	}
}

void SettingsEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}