#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class SettingsEditor final
{
public:
	SettingsEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);
	~SettingsEditor() = default;

	void initializeGUI();
	void load();
	void save();
	void update();

private:
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
	shared_ptr<EngineGuiWindow> _leftWindow = nullptr;

	bool _isLoaded = false;
};