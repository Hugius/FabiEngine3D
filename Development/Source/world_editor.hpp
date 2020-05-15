#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class WorldEditor final
{
public:
	WorldEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui);
	~WorldEditor() = default;

	void initializeGUI();
	void loadProject();
	void saveProject();
	void unloadProject();
	void update(float delta);
	void setCurrentProjectName(string projectName);

	bool isLoaded();

private:
	bool _isLoaded = false;

	string _currentProjectName = "";

	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui;

	shared_ptr<EngineGuiWindow> _window;
};