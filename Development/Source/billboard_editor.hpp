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
	void setCurrentProjectName(const string& projectName);

	bool isLoaded();

private:
	void _loadBillboards();
	void _updateBillboardManagement();
	void _updateBillboardCreation();
	void _updateBillboardChoosing();
	void _updateBillboardEditing();
	void _updateBillboardRemoval();
	void _updateBillboardCamera();

	bool _billboardCreationEnabled = false;
	bool _billboardChoosingEnabled = false;
	bool _billboardEditingEnabled = false;
	bool _billboardRemovalEnabled = false;
	bool _isLoaded = false;

	const vec3 _defaultCameraPosition = vec3(0.0f, 1.5f, 5.0f);
	const vec3 _billboardPosition = vec3(0.0f, 1.5f, 0.0f);
	const float _scrollWheelDivider = 250.0f;
	float _cameraRotationSpeed = 0.0f;
	float _totalCameraRotation = 0.0f;

	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui = nullptr;
	shared_ptr<EngineGuiWindow> _leftWindow = nullptr;
	
	string _hoveredBillboardID = "";
	string _currentBillboardID = "";
	string _currentProjectName = "";
	vector<string> _billboardNames;
};