#include "settings_editor.hpp"
#include "left_viewport_controller.hpp"
#include "logger.hpp"
#include "configuration.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::istringstream;

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

#define TW(text) VPC::calculateTextWidth(text, CW)

SettingsEditor::SettingsEditor(FabiEngine3D& fe3d, EngineGuiManager& gui)
	:
	_fe3d(fe3d),
	_gui(gui)
{

}

void SettingsEditor::load()
{
	// GUI
	_loadGUI();

	// Default graphics
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
	_fe3d.billboard_setDiffuseMap("@@icon", "engine\\assets\\textures\\settings.png");
	_fe3d.billboard_setBright("@@icon", true);

	// Miscellaneous
	_isEditorLoaded = true;
}

void SettingsEditor::unload()
{
	// GUI
	_unloadGUI();

	// Default graphics
	_fe3d.gfx_disableBloom(true);

	// Delete created entities
	_fe3d.billboard_delete("@@icon");

	// Reset editor properties
	_isEditorLoaded = false;
}

void SettingsEditor::update()
{
	// Only if editor is loaded
	if(!_isEditorLoaded)
	{
		return;
	}

	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "settingsEditorMenuMain")
	{
		// Temporary values
		auto isAntiAliasingEnabled = _fe3d.gfx_isAntiAliasingEnabled();
		auto anisotropicFilteringQuality = _fe3d.gfx_getAnisotropicFilteringQuality();
		auto maxAudioChannels = _fe3d.misc_getMaxAudioChannelCount();

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getGlobalScreen()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isAntiAliasingEnabled")->isHovered())
		{
			_gui.getGlobalScreen()->createAnswerForm("isAntiAliasingEnabled", "Anti Aliasing?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("anisotropicFilteringQuality")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("anisotropicFilteringQuality", "Anisotropic Filtering Quality", anisotropicFilteringQuality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("maxAudioChannels")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("maxAudioChannels", "Max Audio Channels", maxAudioChannels, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update answer forms
		if(_gui.getGlobalScreen()->isAnswerFormConfirmed("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveSettingsToFile();
			unload();
			return;
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
		if(_gui.getGlobalScreen()->isAnswerFormConfirmed("isAntiAliasingEnabled") && !_fe3d.gfx_isAntiAliasingEnabled())
		{
			_fe3d.gfx_enableAntiAliasing();
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("isAntiAliasingEnabled") && _fe3d.gfx_isAntiAliasingEnabled())
		{
			_fe3d.gfx_disableAntiAliasing(false);
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("anisotropicFilteringQuality", anisotropicFilteringQuality, {}))
		{
			_fe3d.gfx_setAnisotropicFilteringQuality(anisotropicFilteringQuality);
		}
		if(_gui.getGlobalScreen()->checkValueForm("maxAudioChannels", maxAudioChannels, {}))
		{
			_fe3d.misc_setMaxAudioChannelCount(maxAudioChannels);
		}

		// Miscellaneous
		_fe3d.billboard_rotate("@@icon", fvec3(0.0f, 0.5f, 0.0f));
	}
}

void SettingsEditor::loadDefaultSettings()
{
	_fe3d.gfx_isAntiAliasingEnabled() ? _fe3d.gfx_disableAntiAliasing(false) : void();
	_fe3d.gfx_setAnisotropicFilteringQuality(Config::MIN_ANISOTROPIC_FILTERING_QUALITY);
	_fe3d.misc_setMaxAudioChannelCount(Config::MIN_AUDIO_CHANNELS);
}

const bool SettingsEditor::loadSettingsFromFile() const
{
	// Error checking
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("SettingsEditor::loadSettingsFromFile");
	}

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\settings.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `settings.fe3d` missing!");
		return false;
	}

	// Load settings file
	ifstream file(filePath);

	// Load settings data
	string line;
	getline(file, line);
	istringstream iss(line);

	// Extract values from file
	unsigned int anisotropicFilteringQuality, audioChannels;
	bool isAntiAliasingEnabled;
	iss >>
		isAntiAliasingEnabled >>
		anisotropicFilteringQuality >>
		audioChannels;

	// Disable anti aliasing
	if(_fe3d.gfx_isAntiAliasingEnabled())
	{
		_fe3d.gfx_disableAntiAliasing(true);
	}

	// Set values
	isAntiAliasingEnabled ? _fe3d.gfx_enableAntiAliasing() : void();
	_fe3d.gfx_setAnisotropicFilteringQuality(anisotropicFilteringQuality);
	_fe3d.misc_setMaxAudioChannelCount(audioChannels);

	// Close file
	file.close();

	// Return
	return true;
}

const bool SettingsEditor::saveSettingsToFile() const
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("SettingsEditor::saveSettingsToFile");
	}

	// Create or overwrite file
	ofstream file(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\data\\settings.fe3d");

	// Get values
	auto isAntiAliasingEnabled = _fe3d.gfx_isAntiAliasingEnabled();
	auto anisotropicFilteringQuality = _fe3d.gfx_getAnisotropicFilteringQuality();
	auto audioChannels = _fe3d.misc_getMaxAudioChannelCount();

	// Write to file
	file <<
		isAntiAliasingEnabled << " " <<
		anisotropicFilteringQuality << " " <<
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

const bool SettingsEditor::isLoaded() const
{
	return _isEditorLoaded;
}

void SettingsEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: settingsEditorMenuMain
	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("settingsEditorMenuMain");
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("isAntiAliasingEnabled", fvec2(0.0f, positions[0]), fvec2(TW("Anti Aliasing"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Anti Aliasing", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("anisotropicFilteringQuality", fvec2(0.0f, positions[1]), fvec2(TW("Aniso Filtering"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Aniso Filtering", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("maxAudioChannels", fvec2(0.0f, positions[2]), fvec2(TW("Audio"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Audio", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
}

void SettingsEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("settingsEditorMenuMain");
}