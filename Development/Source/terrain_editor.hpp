#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class TerrainEditor final
{
public:
	TerrainEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	void setCurrentProjectID(const string& projectID);
	void load();
	void update();
	void unload();
	void unloadTerrainEntities();
	bool loadTerrainEntitiesFromFile();
	bool saveTerrainEntitiesToFile();

	const vector<string> getAllTerrainTexturePathsFromFile();
	const vector<string>& getLoadedTerrainIDs();

	bool isLoaded();

private:
	// Functions
	void _loadGUI();
	void _unloadGUI();
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
	void _updateMiscellaneous();

	// General variables
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
	float _terrainCameraDistance = 0.0f;
	bool _isEditorLoaded = false;

	// Terrain variables
	vector <string> _loadedTerrainIDs;
	string _currentTerrainID = "";
	static inline const float TERRAIN_Y_OFFSET = 1.0f;
	static inline const float TERRAIN_GRID_SIZE = 1024.0f;
	bool _isCreatingTerrain = false;
	bool _isChoosingTerrain = false;
	bool _isEditingTerrain = false;
	bool _isDeletingTerrain = false;
};