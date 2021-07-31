#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class WaterEditor final
{
public:
	WaterEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	void setCurrentProjectID(const string& projectID);
	void load();
	void update();
	void unload();
	void unloadWaterEntities();
	bool loadWaterEntitiesFromFile();
	bool saveWaterEntitiesToFile();

	const vector<string> getAllWaterTexturePathsFromFile();
	const vector<string>& getLoadedWaterIDs();

	bool isLoaded();

private:
	// Functions
	void _loadGUI();
	void _unloadGUI();
	void _updateWaterEditor();
	void _updateWaterMenuMain();
	void _updateWaterMenuChoice();
	void _updateWaterMenuMesh();
	void _updateWaterMenuEffects();
	void _updateWaterMenuOptions();
	void _updateWaterCreating();
	void _updateWaterChoosing();
	void _updateWaterDeleting();
	void _updateWaterCamera();
	void _updateMiscellaneous();
	
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
	static inline const float MOUSE_SENSITIVITY = 0.025f;
	static inline const float LOOKAT_MOVEMENT_SPEED = 0.05f;
	static inline const float INITIAL_CAMERA_YAW = 0.0f;
	static inline const float INITIAL_CAMERA_PITCH = 45.0f;
	static inline const float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline const float MIN_CAMERA_PITCH = 1.0f;
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
	string _currentProjectID = "";
	Vec3 _cameraLookatPosition = Vec3(0.0f);
	bool _isEditorLoaded = false;
	vector <string> _loadedWaterIDs;
	string _currentWaterID = "";
	bool _isCreatingWater = false;
	bool _isChoosingWater = false;
	bool _isEditingWater = false;
	bool _isDeletingWater = false;
};