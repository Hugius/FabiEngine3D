#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class BillboardEditor final
{
public:
	BillboardEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	void load();
	void unload();
	void update();
	void setCurrentProjectID(const string& projectName);
	void loadBillboardEntitiesFromFile();
	void saveBillboardEntitiesToFile();

	bool isLoaded();

	const vector<string> getAllTexturePathsFromFile();
	const vector<string>& getLoadedBillboardIDs();

private:
	void _loadGUI();
	void _unloadGUI();
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
	static inline const Vec3 DEFAULT_CAMERA_POSITION = Vec3(0.0f, 2.5f, 5.0f);
	static inline const Vec3 BILLBOARD_POSITION = Vec3(0.0f, 2.5f, 0.0f);

	// Floats
	static inline const float SCROLL_WHEEL_DIVIDER = 250.0f;
	float _cameraAcceleration = 0.0f;
	float _totalCameraRotation = 0.0f;

	// Core
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
	
	// Strings
	string _hoveredBillboardID = "";
	string _currentBillboardID = "";
	string _currentProjectID = "";
	vector<string> _loadedBillboardIDs;
};