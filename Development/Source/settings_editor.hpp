#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class SettingsEditor final
{
public:
	SettingsEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui);
	~SettingsEditor() = default;

	void initializeGUI();
	void load();
	void save();
	void update();

private:
	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui;
	shared_ptr<EngineGuiWindow> _leftWindow;

	bool _isLoaded = false;
};