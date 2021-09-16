#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class BillboardEditor final
{
public:
	BillboardEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	// Voids
	void setCurrentProjectID(const string& projectID);
	void load();
	void unload();
	void update();

	// Strings
	const vector<string> getAllTexturePathsFromFile();
	const vector<string> getAllFontPathsFromFile();
	const vector<string>& getLoadedBillboardIDs();

	// Booleans
	bool loadBillboardEntitiesFromFile();
	bool saveBillboardEntitiesToFile();
	bool isLoaded();

private:
	// Voids
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateMeshMenu();
	void _updateLightingMenu();
	void _updateAnimationMenu();
	void _updateOptionsMenu();
	void _updateBillboardCreating();
	void _updateBillboardChoosing();
	void _updateBillboardDeleting();
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

	// Floats
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
	static inline const float MOUSE_SENSITIVITY = 0.025f;
	static inline const float INITIAL_CAMERA_YAW = 45.0f;
	static inline const float INITIAL_CAMERA_PITCH = 45.0f;
	static inline const float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline const float MIN_CAMERA_PITCH = 1.0f;
	static inline const float GRID_Y_OFFSET = 0.001f;
	static inline const float GRID_SIZE = 30.0f;
	static inline const float GRID_UV = 3.0f;
	static inline const float MIN_CAMERA_DISTANCE = 0.5f;
	static inline const float CAMERA_DISTANCE_SPEED = 0.125f;
	static inline const float CAMERA_LOOKAT_SPEED = 0.025f;

	// Booleans
	bool _isCreatingBillboard = false;
	bool _isChoosingBillboard = false;
	bool _isDeletingBillboard = false;
	bool _isEditorLoaded = false;
};