#pragma once

#include "fe3d.hpp"
#include "engine_gui_manager.hpp"

class SettingsEditor final
{
public:
	SettingsEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	// Voids
	void setCurrentProjectID(const string& projectID);
	void load();
	void unload();
	void update();
	void loadDefaultSettings();
	bool loadSettingsFromFile();
	bool saveSettingsToFile();

	// Booleans
	bool isLoaded();

private:
	// Voids
	void _loadGUI();
	void _unloadGUI();

	// Instances
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;

	// Strings
	string _currentProjectID = "";

	// Floats
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;

	// Booleans
	bool _isEditorLoaded = false;
};