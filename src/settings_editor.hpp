#pragma once

#include "fe3d.hpp"
#include "gui_manager.hpp"

class SettingsEditor final
{
public:
	SettingsEditor(FabiEngine3D& fe3d, GuiManager& gui);

	// VOID
	void setCurrentProjectID(const string& projectID);
	void load();
	void unload();
	void update();
	void loadDefaultSettings();

	// BOOL
	const bool loadSettingsFromFile() const;
	const bool saveSettingsToFile() const;
	const bool isLoaded() const;

private:
	// VOID
	void _loadGUI();
	void _unloadGUI();

	// STRING
	string _currentProjectID = "";

	// FLOAT
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;

	// BOOL
	bool _isEditorLoaded = false;

	// MISCELLANEOUS
	FabiEngine3D& _fe3d;
	GuiManager& _gui;
};