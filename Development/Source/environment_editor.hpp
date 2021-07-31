#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "environment_type.hpp"

class EnvironmentEditor final
{
public:
	EnvironmentEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	void setCurrentProjectID(const string& projectID);
	void load();
	void update();
	void unload();
	void unloadSkyEntities();
	void unloadTerrainEntities();
	void unloadWaterEntities();
	bool loadSkyEntitiesFromFile();
	bool loadTerrainEntitiesFromFile();
	bool loadWaterEntitiesFromFile();
	bool saveSkyEntitiesToFile();
	bool saveTerrainEntitiesToFile();
	bool saveWaterEntitiesToFile();

	const vector<array<string, 6>> getAllSkyTexturePathsFromFile();
	const vector<string> getAllTerrainTexturePathsFromFile();
	const vector<string> getAllWaterTexturePathsFromFile();
	const vector<string>& getLoadedSkyIDs();
	const vector<string>& getLoadedTerrainIDs();
	const vector<string>& getLoadedWaterIDs();

	bool isLoaded();

private:
	// Core functions
	void _loadGUI();
	void _unloadGUI();

	// Sky functions
	void _updateSkyEditor();
	void _updateSkyMenuMain();
	void _updateSkyMenuChoice();
	void _updateSkyMenuMesh();
	void _updateSkyMenuOptions();
	void _updateSkyCreating();
	void _updateSkyChoosing();
	void _updateSkyDeleting();
	void _updateSkyCamera();

	// Terrain function
	void _updateTerrainEditor();
	void _updateTerrainMenuMain();
	void _updateTerrainMenuChoice();
	void _updateTerrainMenuMesh();
	void _updateTerrainMenuBlendMap();
	void _updateTerrainMenuLighting();
	void _updateTerrainCreating();
	void _updateTerrainChoosing();
	void _updateTerrainDeleting();
	void _updateTerrainCamera();
	void _updateTerrainMiscellaneous();

	// Water functions
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

	// Miscellaneous functions
	void _updateMiscellaneous();

	// General variables
	static inline const float MOUSE_SENSITIVITY = 0.025f;
	static inline const float LOOKAT_MOVEMENT_SPEED = 0.05f;
	static inline const float INITIAL_CAMERA_YAW = 0.0f;
	static inline const float INITIAL_CAMERA_PITCH = 45.0f;
	static inline const float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline const float MIN_CAMERA_PITCH = 1.0f;
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
	EnvironmentType _currentEnvironmentType = EnvironmentType();
	string _currentProjectID = "";
	Vec3 _cameraLookatPosition = Vec3(0.0f);
	float _terrainCameraDistance = 0.0f;
	bool _isEditorLoaded = false;
	bool _isInMainMenu = false;

	// Sky variables
	vector <string> _loadedSkyIDs;
	string _currentSkyID = "";
	bool _isCreatingSky = false;
	bool _isChoosingSky = false;
	bool _isEditingSky = false;
	bool _isDeletingSky = false;

	// Terrain variables
	vector <string> _loadedTerrainIDs;
	string _currentTerrainID = "";
	static inline const float TERRAIN_Y_OFFSET = 1.0f;
	static inline const float TERRAIN_GRID_SIZE = 1024.0f;
	bool _isCreatingTerrain = false;
	bool _isChoosingTerrain = false;
	bool _isEditingTerrain = false;
	bool _isDeletingTerrain = false;

	// Water variables
	vector <string> _loadedWaterIDs;
	string _currentWaterID = "";
	bool _isCreatingWater = false;
	bool _isChoosingWater = false;
	bool _isEditingWater = false;
	bool _isDeletingWater = false;
};