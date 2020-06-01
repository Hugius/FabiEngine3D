#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class BillboardEditor final
{
public:
	BillboardEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui);
	~BillboardEditor() = default;

	void initializeGUI();
	void load();
	void save();
	void unload();
	void update();
	void setCurrentProjectName(string projectName);

	bool isLoaded();

private:
	void _updateBillboardManagement();
	void _updateBillboardCreation();
	void _updateBillboardChoosing();
	void _updateBillboardEditing();

	bool _billboardCreationEnabled = false;
	bool _billboardChoosingEnabled = false;
	bool _billboardEditingEnabled = false;
	bool _billboardRemovalEnabled = false;
	bool _isLoaded = false;

	const vec3 _startingCameraPos = vec3(0.0f, 5.0f, 5.0f);

	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui;

	shared_ptr<EngineGuiWindow> _window;
	
	string _currentBillboardName = "";
	string _currentProjectName = "";
	vector<string> _billboardNames;
};