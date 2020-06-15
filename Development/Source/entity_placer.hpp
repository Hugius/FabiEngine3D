#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "model_editor.hpp"
#include "world_editor.hpp"

class EntityPlacer final
{
public:
	EntityPlacer(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui, ModelEditor& modelEditor, WorldEditor& worldEditor);
	~EntityPlacer() = default;

	void initializeGUI();
	void load();
	void save();
	void unload();
	void update();
	void setCurrentProjectName(string projectName);

	bool isLoaded();

private:
	void _updateManagementScreen();
	void _updateModelScreen();
	void _updateBillboardScreen();
	void _updateLightScreen();
	void _updateCamera();

	bool _isLoaded = false;

	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui;
	ModelEditor& _modelEditor;
	WorldEditor& _worldEditor;

	shared_ptr<EngineGuiWindow> _leftWindow;
	shared_ptr<EngineGuiWindow> _rightWindow;
	
	string _currentProjectName = "";
};