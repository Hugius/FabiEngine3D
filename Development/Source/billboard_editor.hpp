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
	void loadBillboards();

	bool isLoaded();

	vector<string>& getBillboardNames();

private:
	void _updateBillboardManagement();
	void _updateBillboardCreation();
	void _updateBillboardChoosing();
	void _updateBillboardEditing();
	void _updateBillboardRemoval();
	void _updateBillboardCamera();
	void _updateMiscellaneous();

	// Booleans
	bool _billboardCreationEnabled = false;
	bool _billboardChoosingEnabled = false;
	bool _billboardEditingEnabled = false;
	bool _billboardRemovalEnabled = false;
	bool _isLoaded = false;

	// Vectors
	const vec3 _defaultCameraPosition = vec3(0.0f, 2.5f, 5.0f);
	const vec3 _billboardPosition = vec3(0.0f, 2.5f, 0.0f);

	// Floats
	const float _scrollWheelDivider = 250.0f;
	float _cameraRotationSpeed = 0.0f;
	float _totalCameraRotation = 0.0f;

	// Core
	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui = nullptr;
	
	// Strings
	string _hoveredBillboardID = "";
	string _currentBillboardID = "";
	string _currentProjectName = "";
	vector<string> _billboardNames;
};