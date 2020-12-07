#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class BillboardEditor final
{
public:
	BillboardEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);
	~BillboardEditor() = default;

	void initializeGUI();
	void load();
	void unload();
	void update();
	void setCurrentProjectName(const string& projectName);
	void loadBillboardEntitiesFromFile();
	void saveBillboardEntitiesToFile();

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
	bool _isCreatingBillboard = false;
	bool _isChoosingBillboard = false;
	bool _isEditingBillboard = false;
	bool _isRemovingBillboard = false;
	bool _isEditorLoaded = false;

	// Vectors
	const Vec3 _defaultCameraPosition = Vec3(0.0f, 2.5f, 5.0f);
	const Vec3 _billboardPosition = Vec3(0.0f, 2.5f, 0.0f);

	// Floats
	const float _scrollWheelDivider = 250.0f;
	float _cameraRotationSpeed = 0.0f;
	float _totalCameraRotation = 0.0f;

	// Core
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
	
	// Strings
	string _hoveredBillboardID = "";
	string _currentBillboardID = "";
	string _currentProjectName = "";
	vector<string> _billboardIDs;
};