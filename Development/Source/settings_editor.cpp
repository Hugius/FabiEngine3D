#include "settings_editor.hpp"
#include "left_viewport_controller.hpp"
#include "logger.hpp"
#include "configuration.hpp"

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

	// Camera
	_fe3d.camera_reset();
	_fe3d.camera_setYaw(270.0f);

	// Editor billboards
	_fe3d.billboardEntity_create("@@icon");
	_fe3d.billboardEntity_setPosition("@@icon", Vec3(0.0f, -0.5f, -1.5f));
	_fe3d.billboardEntity_setDiffuseMap("@@icon", "engine_assets\\textures\\settings.png");
	_fe3d.billboardEntity_setBright("@@icon", true);

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
	_fe3d.billboardEntity_delete("@@icon");

	// Reset editor properties
	_isEditorLoaded = false;
}

void SettingsEditor::update()
{
	// Only if editor is loaded
	if (!_isEditorLoaded)
	{
		return;
	}

	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "settingsEditorMenuMain")
	{
		// Temporary values
		auto isAntiAliasingEnabled = _fe3d.gfx_isAntiAliasingEnabled();
		auto bloomSize = _fe3d.gfx_getBloomSize();
		auto dofSize = _fe3d.gfx_getDofSize();
		auto motionBlurSize = _fe3d.gfx_getMotionBlurSize();
		auto anisotropicFilteringQuality = _fe3d.gfx_getAnisotropicFilteringQuality();
		auto shadowQuality = _fe3d.gfx_getShadowQuality();
		auto cubeReflectionQuality = _fe3d.gfx_getCubeReflectionQuality();
		auto planarReflectionQuality = _fe3d.gfx_getPlanarReflectionQuality();
		auto refractionQuality = _fe3d.gfx_getRefractionQuality();
		auto maxAudioChannels = _fe3d.misc_getMaxAudioChannelCount();

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getGlobalScreen()->createAnswerForm("back", "Save Changes?", Vec2(0.0f, 0.25f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isAntiAliasingEnabled")->isHovered())
		{
			_gui.getGlobalScreen()->createAnswerForm("isAntiAliasingEnabled", "Anti Aliasing?", Vec2(0.0f, 0.25f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("bloomSize")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("bloomSize", "Bloom Size", bloomSize, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("dofSize")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("dofSize", "DOF Size", dofSize, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("motionBlurSize")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("motionBlurSize", "Motion Blur Size", motionBlurSize, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("anisotropicFilteringQuality")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("anisotropicFilteringQuality", "Anisotropic Filtering Quality", anisotropicFilteringQuality, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("shadowQuality")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("shadowQuality", "Shadow Quality", shadowQuality, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("cubeReflectionQuality")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("cubeReflectionQuality", "Cube Reflection Quality", cubeReflectionQuality, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("planarReflectionQuality")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("planarReflectionQuality", "Planar Reflection Quality", planarReflectionQuality, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("refractionQuality")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("refractionQuality", "Refraction Quality", refractionQuality, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("maxAudioChannels")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("maxAudioChannels", "Max Audio Channels", maxAudioChannels, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}

		// Update answer forms
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveSettingsToFile();
			unload();
			return;
		}
		if (_gui.getGlobalScreen()->isAnswerFormDenied("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("isAntiAliasingEnabled") && !_fe3d.gfx_isAntiAliasingEnabled())
		{
			_fe3d.gfx_enableAntiAliasing();
		}
		if (_gui.getGlobalScreen()->isAnswerFormDenied("isAntiAliasingEnabled") && _fe3d.gfx_isAntiAliasingEnabled())
		{
			_fe3d.gfx_disableAntiAliasing();
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("bloomSize", bloomSize, {}))
		{
			_fe3d.gfx_setBloomSize(bloomSize);
		}
		if (_gui.getGlobalScreen()->checkValueForm("dofSize", dofSize, {}))
		{
			_fe3d.gfx_setDofSize(dofSize);
		}
		if (_gui.getGlobalScreen()->checkValueForm("motionBlurSize", motionBlurSize, {}))
		{
			_fe3d.gfx_setMotionBlurSize(motionBlurSize);
		}
		if (_gui.getGlobalScreen()->checkValueForm("anisotropicFilteringQuality", anisotropicFilteringQuality, {}))
		{
			_fe3d.gfx_setAnisotropicFilteringQuality(anisotropicFilteringQuality);
		}
		if (_gui.getGlobalScreen()->checkValueForm("shadowQuality", shadowQuality, {}))
		{
			_fe3d.gfx_setShadowQuality(shadowQuality);
		}
		if (_gui.getGlobalScreen()->checkValueForm("cubeReflectionQuality", cubeReflectionQuality, {}))
		{
			_fe3d.gfx_setCubeReflectionQuality(cubeReflectionQuality);
		}
		if (_gui.getGlobalScreen()->checkValueForm("planarReflectionQuality", planarReflectionQuality, {}))
		{
			_fe3d.gfx_setPlanarReflectionQuality(planarReflectionQuality);
		}
		if (_gui.getGlobalScreen()->checkValueForm("refractionQuality", refractionQuality, {}))
		{
			_fe3d.gfx_setRefractionQuality(refractionQuality);
		}
		if (_gui.getGlobalScreen()->checkValueForm("maxAudioChannels", maxAudioChannels, {}))
		{
			_fe3d.misc_setMaxAudioChannelCount(maxAudioChannels);
		}

		// Miscellaneous
		_fe3d.billboardEntity_rotate("@@icon", Vec3(0.0f, 0.5f, 0.0f));
	}
}

void SettingsEditor::loadDefaultSettings()
{
	_fe3d.gfx_isAntiAliasingEnabled() ? _fe3d.gfx_disableAntiAliasing() : void();
	_fe3d.gfx_setBloomSize(Config::MIN_BLOOM_SIZE);
	_fe3d.gfx_setDofSize(Config::MIN_DOF_SIZE);
	_fe3d.gfx_setMotionBlurSize(Config::MIN_MOTION_BLUR_SIZE);
	_fe3d.gfx_setAnisotropicFilteringQuality(Config::MIN_ANISOTROPIC_FILTERING_QUALITY);
	_fe3d.gfx_setShadowQuality(Config::MIN_SHADOW_QUALITY);
	_fe3d.gfx_setCubeReflectionQuality(Config::MIN_REFLECTION_QUALITY);
	_fe3d.gfx_setPlanarReflectionQuality(Config::MIN_REFLECTION_QUALITY);
	_fe3d.gfx_setRefractionQuality(Config::MIN_REFRACTION_QUALITY);
	_fe3d.misc_setMaxAudioChannelCount(Config::MIN_AUDIO_CHANNELS);
}

bool SettingsEditor::loadSettingsFromFile()
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("SettingsEditor::loadSettingsFromFile");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\settings.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `settings.fe3d` missing!");
		return false;
	}

	// Load settings file
	ifstream file(filePath);

	// Load settings data
	string line;
	getline(file, line);
	istringstream iss(line);

	// Extract values from file
	unsigned int bloomSize, dofSize, motionBlurSize, anisotropicFilteringQuality, shadowQuality, cubeReflectionQuality, planarReflectionQuality, refractionQuality, audioChannels;
	bool isAntiAliasingEnabled;
	iss >>
		isAntiAliasingEnabled >>
		bloomSize >>
		dofSize >>
		motionBlurSize >>
		anisotropicFilteringQuality >>
		shadowQuality >>
		cubeReflectionQuality >>
		planarReflectionQuality >>
		refractionQuality >>
		audioChannels;

	// Disable anti aliasing
	if (_fe3d.gfx_isAntiAliasingEnabled())
	{
		_fe3d.gfx_disableAntiAliasing(true);
	}

	// Set values
	isAntiAliasingEnabled ? _fe3d.gfx_enableAntiAliasing() : void();
	_fe3d.gfx_setBloomSize(bloomSize);
	_fe3d.gfx_setDofSize(dofSize);
	_fe3d.gfx_setMotionBlurSize(motionBlurSize);
	_fe3d.gfx_setAnisotropicFilteringQuality(anisotropicFilteringQuality);
	_fe3d.gfx_setShadowQuality(shadowQuality);
	_fe3d.gfx_setCubeReflectionQuality(cubeReflectionQuality);
	_fe3d.gfx_setPlanarReflectionQuality(planarReflectionQuality);
	_fe3d.gfx_setRefractionQuality(refractionQuality);
	_fe3d.misc_setMaxAudioChannelCount(audioChannels);

	// Close file
	file.close();

	// Return
	return true;
}

bool SettingsEditor::saveSettingsToFile()
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("SettingsEditor::saveSettingsToFile");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\settings.fe3d";

	// Create or overwrite settings file
	ofstream file(filePath);

	// Get values
	auto isAntiAliasingEnabled = _fe3d.gfx_isAntiAliasingEnabled();
	auto bloomSize = _fe3d.gfx_getBloomSize();
	auto dofSize = _fe3d.gfx_getDofSize();
	auto motionBlurSize = _fe3d.gfx_getMotionBlurSize();
	auto anisotropicFilteringQuality = _fe3d.gfx_getAnisotropicFilteringQuality();
	auto shadowQuality = _fe3d.gfx_getShadowQuality();
	auto cubeReflectionQuality = _fe3d.gfx_getCubeReflectionQuality();
	auto planarReflectionQuality = _fe3d.gfx_getPlanarReflectionQuality();
	auto refractionQuality = _fe3d.gfx_getRefractionQuality();
	auto audioChannels = _fe3d.misc_getMaxAudioChannelCount();

	// Write to file
	file <<
		isAntiAliasingEnabled << " " <<
		bloomSize << " " <<
		dofSize << " " <<
		motionBlurSize << " " <<
		anisotropicFilteringQuality << " " <<
		shadowQuality << " " <<
		cubeReflectionQuality << " " <<
		planarReflectionQuality << " " <<
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
	auto positions = VPC::calculateButtonPositions(11, CH);
	leftWindow->createScreen("settingsEditorMenuMain");
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("isAntiAliasingEnabled", Vec2(0.0f, positions[0]), Vec2(TW("Anti Aliasing"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Anti Aliasing", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("bloomSize", Vec2(0.0f, positions[1]), Vec2(TW("Bloom"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Bloom", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("dofSize", Vec2(0.0f, positions[2]), Vec2(TW("DOF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "DOF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("motionBlurSize", Vec2(0.0f, positions[3]), Vec2(TW("Motion Blur"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Motion Blur", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("anisotropicFilteringQuality", Vec2(0.0f, positions[4]), Vec2(TW("Aniso Filtering"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Aniso Filtering", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("shadowQuality", Vec2(0.0f, positions[5]), Vec2(TW("Shadow"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Shadow", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("cubeReflectionQuality", Vec2(0.0f, positions[6]), Vec2(TW("Cube Reflection"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Cube Reflection", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("planarReflectionQuality", Vec2(0.0f, positions[7]), Vec2(TW("Planar Reflection"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Planar Reflection", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("refractionQuality", Vec2(0.0f, positions[8]), Vec2(TW("Refraction"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Refraction", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("maxAudioChannels", Vec2(0.0f, positions[9]), Vec2(TW("Audio"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Audio", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("settingsEditorMenuMain")->createButton("back", Vec2(0.0f, positions[10]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void SettingsEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("settingsEditorMenuMain");
}