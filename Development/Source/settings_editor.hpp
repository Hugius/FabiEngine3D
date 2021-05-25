#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class SettingsEditor final
{
public:
	SettingsEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	void loadSettings();
	void load();
	void unload();
	void update();
	void setCurrentProjectID(const string& projectName);
	void save(bool newFile);

private:
	void _loadGUI();
	void _unloadGUI();

	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;

	bool _isEditorLoaded = false;

	string _currentProjectID = "";
};