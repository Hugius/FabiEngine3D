#include "settings_editor.hpp"
#include "left_viewport_controller.hpp"
#include "logger.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

#define TW(text) VPC::calculateTextWidth(text, CW)

SettingsEditor::SettingsEditor(FabiEngine3D& fe3d, EngineGuiManager& gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void SettingsEditor::load()
{
	// GUI
	_loadGUI();
	
	// Miscellaneous
	_fe3d.gfx_enableBloom(BloomType::PARTS, 1.0f, 5);
	_fe3d.billboardEntity_create("@@icon", "engine_assets\\textures\\settings.png", 
		Vec3(0.0f, -0.5f, -1.5f), Vec3(0.0f), Vec2(1.0f), true, false, false);
	_fe3d.billboardEntity_setBright("@@icon", true);
	_fe3d.camera_reset();
	_fe3d.camera_setYaw(-90.0f);
	_isEditorLoaded = true;
}

void SettingsEditor::unload()
{
	// GUI
	_unloadGUI();

	// Miscellaneous
	_fe3d.gfx_disableBloom(true);
	_fe3d.billboardEntity_delete("@@icon");
	_isEditorLoaded = false;
}

void SettingsEditor::update()
{
	if (_isEditorLoaded)
	{
		// Temporary values
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "settingsEditorMenuMain")
		{
			// Temporary values
			auto isFxaaEnabled = _fe3d.gfx_isFxaaEnabled();
			auto anisotropicQuality = _fe3d.gfx_getAnisotropicFilteringQuality();
			auto shadowQuality = _fe3d.gfx_getShadowQuality();
			auto reflectionQuality = _fe3d.gfx_getReflectionQuality();
			auto refractionQuality = _fe3d.gfx_getRefractionQuality();
			auto maxAudioChannels = _fe3d.misc_getMaxAudioChannelCount();

			// Check if input received
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getGlobalScreen()->addAnswerForm("exit", "Save Changes?", Vec2(0.0f, 0.25f));
				}
				else if (screen->getButton("isFxaaEnabled")->isHovered())
				{
					isFxaaEnabled = !isFxaaEnabled;
					isFxaaEnabled ? _fe3d.gfx_enableFXAA() : _fe3d.gfx_disableFXAA();
				}
				else if (screen->getButton("anisotropicQuality")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("anisotropicQuality", "Anisotropic Filtering Quality", anisotropicQuality, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
				else if (screen->getButton("shadowQuality")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("shadowQuality", "Shadow Quality", shadowQuality, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
				else if (screen->getButton("reflectionQuality")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("reflectionQuality", "Reflection Quality", reflectionQuality, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
				else if (screen->getButton("refractionQuality")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("refractionQuality", "Refraction Quality", refractionQuality, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
				else if (screen->getButton("maxAudioChannels")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("maxAudioChannels", "Max Audio Channels", maxAudioChannels, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
			}

			// Update forms
			if (_gui.getGlobalScreen()->checkValueForm("anisotropicQuality", anisotropicQuality, {}))
			{
				_fe3d.gfx_setAnisotropicFilteringQuality(std::clamp(anisotropicQuality,
					Config::MIN_ANISOTROPIC_FILTERING_QUALITY,
					Config::MAX_ANISOTROPIC_FILTERING_QUALITY));
			}
			else if (_gui.getGlobalScreen()->checkValueForm("shadowQuality", shadowQuality, {}))
			{
				_fe3d.gfx_setShadowQuality(std::clamp(shadowQuality,
					Config::MIN_SHADOW_QUALITY,
					Config::MAX_SHADOW_QUALITY));
			}
			else if (_gui.getGlobalScreen()->checkValueForm("reflectionQuality", reflectionQuality, {}))
			{
				_fe3d.gfx_setReflectionQuality(std::clamp(reflectionQuality,
					Config::MIN_REFLECTION_QUALITY,
					Config::MAX_REFLECTION_QUALITY));
			}
			else if (_gui.getGlobalScreen()->checkValueForm("refractionQuality", refractionQuality, {}))
			{
				_fe3d.gfx_setRefractionQuality(std::clamp(refractionQuality,
					Config::MIN_REFRACTION_QUALITY,
					Config::MAX_REFRACTION_QUALITY));
			}
			else if (_gui.getGlobalScreen()->checkValueForm("maxAudioChannels", maxAudioChannels, {}))
			{
				_fe3d.misc_setMaxAudioChannels(std::clamp(maxAudioChannels,
					Config::MIN_AUDIO_CHANNELS,
					Config::MAX_AUDIO_CHANNELS));
			}

			// Update button contents
			screen->getButton("isFxaaEnabled")->changeTextContent(isFxaaEnabled ? "FXAA: ON" : "FXAA: OFF");

			// Miscellaneous
			_fe3d.billboardEntity_rotate("@@icon", Vec3(0.0f, 0.5f, 0.0f));

			// Check if user wants to save changes
			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exit"))
			{
				saveSettingsToFile();
				unload();
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("exit"))
			{
				unload();
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			}
		}
	}
}

void SettingsEditor::loadDefaultSettings()
{
	_fe3d.gfx_isFxaaEnabled() ? _fe3d.gfx_disableFXAA() : void();
	_fe3d.gfx_setAnisotropicFilteringQuality(Config::MIN_ANISOTROPIC_FILTERING_QUALITY);
	_fe3d.gfx_setShadowQuality(Config::MIN_SHADOW_QUALITY);
	_fe3d.gfx_setReflectionQuality(Config::MIN_REFLECTION_QUALITY);
	_fe3d.gfx_setRefractionQuality(Config::MIN_REFRACTION_QUALITY);
	_fe3d.misc_setMaxAudioChannels(Config::MIN_AUDIO_CHANNELS);
}

bool SettingsEditor::loadSettingsFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("SettingsEditor::loadSettings() ---> no current project loaded!");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\settings.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: \"settings.fe3d\" file missing!");
		return false;
	}

	// Load settings file
	std::ifstream file(filePath);

	// Load settings data
	string line;
	std::getline(file, line);
	std::istringstream iss(line);

	// Extract values from file
	unsigned int anisotropicQuality, shadowQuality, reflectionQuality, refractionQuality, audioChannels;
	bool isFxaaEnabled;
	iss >> isFxaaEnabled >> anisotropicQuality >> shadowQuality >> reflectionQuality >> refractionQuality >> audioChannels;

	// Disable FXAA
	if (_fe3d.gfx_isFxaaEnabled())
	{
		_fe3d.gfx_disableFXAA(true);
	}

	// Set values
	isFxaaEnabled ? _fe3d.gfx_enableFXAA() : void();
	_fe3d.gfx_setAnisotropicFilteringQuality(anisotropicQuality);
	_fe3d.gfx_setShadowQuality(shadowQuality);
	_fe3d.gfx_setReflectionQuality(reflectionQuality);
	_fe3d.gfx_setRefractionQuality(refractionQuality);
	_fe3d.misc_setMaxAudioChannels(audioChannels);

	// Close file
	file.close();

	// Return
	return true;
}

bool SettingsEditor::saveSettingsToFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("SettingsEditor::save() ---> no current project loaded!");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\settings.fe3d";

	// Create or overwrite settings file
	std::ofstream file(filePath);

	// Get values
	auto isFxaaEnabled = _fe3d.gfx_isFxaaEnabled();
	auto anisotropicQuality = _fe3d.gfx_getAnisotropicFilteringQuality();
	auto shadowQuality = _fe3d.gfx_getShadowQuality();
	auto reflectionQuality = _fe3d.gfx_getReflectionQuality();
	auto refractionQuality = _fe3d.gfx_getRefractionQuality();
	auto audioChannels = _fe3d.misc_getMaxAudioChannelCount();

	// Write to file
	file <<
		isFxaaEnabled << " " <<
		anisotropicQuality << " " <<
		shadowQuality << " " <<
		reflectionQuality << " " <<
		refractionQuality << " " <<
		audioChannels;

	// Close file
	file.close();

	// Return
	return true;
}

void SettingsEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

bool SettingsEditor::isLoaded()
{
	return _isEditorLoaded;
}

void SettingsEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: settingsEditorMenuMain
	auto positions = VPC::calculateButtonPositions(7, CH);
	leftWindow->createScreen("settingsEditorMenuMain");
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("isFxaaEnabled", Vec2(0.0f, positions[0]), Vec2(TW("FXAA: ON"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "FXAA: ON", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("anisotropicQuality", Vec2(0.0f, positions[1]), Vec2(TW("Anisotropic"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Anisotropic", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("shadowQuality", Vec2(0.0f, positions[2]), Vec2(TW("Shadow"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Shadow", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("reflectionQuality", Vec2(0.0f, positions[3]), Vec2(TW("Reflection"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflection", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("refractionQuality", Vec2(0.0f, positions[4]), Vec2(TW("Refraction"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Refraction", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("maxAudioChannels", Vec2(0.0f, positions[5]), Vec2(TW("Audio"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Audio", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("back", Vec2(0.0f, positions[6]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void SettingsEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("settingsEditorMenuMain");
}