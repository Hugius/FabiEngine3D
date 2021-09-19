#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "reflection_type.hpp"

class ModelEditor final
{
public:
	ModelEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	void setCurrentProjectID(const string& projectID);
	void load();
	void unload();
	void update();
	bool loadModelEntitiesFromFile();
	bool saveModelEntitiesToFile();

	bool isLoaded();

	const vector<string> getAllMeshPathsFromFile();
	const vector<string> getAllTexturePathsFromFile();
	const vector<string>& getLoadedModelIDs();

private:
	void _loadGUI();
	void _unloadGUI();
	void _loadDiffuseMap();
	void _loadEmissionMap();
	void _loadReflectionMap();
	void _loadNormalMap();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateMeshMenu();
	void _updateLightingMenu();
	void _updateOptionsMenu();
	void _updateMainAabbMenu();
	void _updateChoiceAabbMenu();
	void _updateModelCreating();
	void _updateModelChoosing();
	void _updateModelDeleting();
	void _updateAabbCreating();
	void _updateAabbChoosing();
	void _updateAabbDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	// Instances
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;

	// Strings
	vector<string> _loadedModelIDs;
	string _currentModelID = "";
	string _currentAabbID = "";
	string _currentProjectID = "";
	string _hoveredModelID = "";

	// Floats
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
	static inline const float MOUSE_SENSITIVITY = 0.025f;
	static inline const float INITIAL_CAMERA_YAW = 45.0f;
	static inline const float INITIAL_CAMERA_PITCH = 45.0f;
	static inline const float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline const float MIN_CAMERA_PITCH = 1.0f;
	static inline const float GRID_Y_OFFSET = 0.001f;
	static inline const float GRID_SIZE = 60.0f;
	static inline const float GRID_UV = 6.0f;
	static inline const float MIN_CAMERA_DISTANCE = 0.5f;
	static inline const float CAMERA_DISTANCE_SPEED = 0.25f;
	static inline const float CAMERA_LOOKAT_SPEED = 0.025f;

	// Booleans
	bool _isCreatingModel = false;
	bool _isChoosingModel = false;
	bool _isDeletingModel = false;
	bool _isCreatingAabb = false;
	bool _isChoosingAabb = false;
	bool _isDeletingAabb = false;
	bool _isEditorLoaded = false;
};