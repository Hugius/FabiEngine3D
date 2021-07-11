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
	void loadBillboardEntitiesFromFile();
	void saveBillboardEntitiesToFile();
	void setCurrentProjectID(const string& projectID);

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
	void _updateCamera();
	void _updateMiscellaneous();

	// Instances
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;

	// Strings
	vector<string> _loadedBillboardIDs;
	string _hoveredBillboardID = "";
	string _currentBillboardID = "";
	string _currentProjectID = "";

	// Vectors
	static inline const Vec3 INITIAL_CAMERA_POSITION = Vec3(0.0f, 5.0f, 0.0f);

	// Floats
	static inline const float MOUSE_SENSITIVITY = 0.025f;
	static inline const float LOOKAT_MOVEMENT_SPEED = 0.05f;
	static inline const float INITIAL_CAMERA_YAW = 0.0f;
	static inline const float INITIAL_CAMERA_PITCH = 0.0f;
	static inline const float INITIAL_CAMERA_DISTANCE = 5.0f;

	// Booleans
	bool _isCreatingBillboard = false;
	bool _isChoosingBillboard = false;
	bool _isEditingBillboard = false;
	bool _isRemovingBillboard = false;
	bool _isEditorLoaded = false;
};