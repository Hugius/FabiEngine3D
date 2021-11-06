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

	// Booleans
	const bool loadSettingsFromFile() const;
	const bool saveSettingsToFile() const;
	const bool isLoaded() const;

private:
	// Voids
	void _loadGUI();
	void _unloadGUI();

	// Strings
	string _currentProjectID = "";

	// Decimals
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;

	// Booleans
	bool _isEditorLoaded = false;

	// Miscellaneous
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
};