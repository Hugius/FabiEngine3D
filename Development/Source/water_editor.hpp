#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class WaterEditor final
{
public:
	WaterEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	// Voids
	void setCurrentProjectID(const string& projectID);
	void load();
	void update();
	void unload();
	void unloadWaterEntities();

	// Strings
	const vector<string> getAllWaterTexturePathsFromFile();
	const vector<string>& getLoadedWaterIDs();

	// Booleans
	bool loadWaterEntitiesFromFile();
	bool saveWaterEntitiesToFile();
	bool isLoaded();

private:
	// Voids
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateMeshMenu();
	void _updateEffectsMenu();
	void _updateOptionsMenu();
	void _updateWaterCreating();
	void _updateWaterChoosing();
	void _updateWaterDeleting();
	void _updateCamera();
	void _updateMiscellaneous();
	
	// Instances
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;

	// Strings
	vector <string> _loadedWaterIDs;
	string _currentProjectID = "";
	string _currentWaterID = "";

	// Floats
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
	static inline const float MOUSE_SENSITIVITY = 0.025f;
	static inline const float LOOKAT_MOVEMENT_SPEED = 0.05f;
	static inline const float INITIAL_CAMERA_YAW = 0.0f;
	static inline const float INITIAL_CAMERA_PITCH = 45.0f;
	static inline const float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline const float MIN_CAMERA_PITCH = 1.0f;
	static inline const float GRID_Y_OFFSET = 1.0f;
	static inline const float GRID_SIZE = 1024.0f;
	static inline const float GRID_UV = 20.0f;

	// Booleans
	bool _isEditorLoaded = false;
	bool _isCreatingWater = false;
	bool _isChoosingWater = false;
	bool _isEditingWater = false;
	bool _isDeletingWater = false;
};