#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class SettingsEditor final
{
public:
	SettingsEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	void load();
	void unload();
	void update();
	void loadDefaultSettings();
	void loadSettingsFromFile();
	void saveSettingsToFile();
	void setCurrentProjectID(const string& projectID);

	bool isLoaded();

private:
	void _loadGUI();
	void _unloadGUI();

	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;

	string _currentProjectID = "";

	static inline const unsigned int DEFAULT_SHADOW_QUALITY = 2048;
	static inline const unsigned int DEFAULT_REFLECTION_QUALITY = 256;
	static inline const unsigned int DEFAULT_REFRACTION_QUALITY = 256;
	static inline const unsigned int DEFAULT_AUDIO_CHANNELS = 128;

	static inline const bool DEFAULT_FXAA_ENABLED = true;
	bool _isEditorLoaded = false;
};