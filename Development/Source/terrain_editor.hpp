#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class TerrainEditor final
{
public:
	TerrainEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	// Voids
	void setCurrentProjectID(const string& projectID);
	void load();
	void update();
	void unload();
	void unloadTerrainEntities();

	// Strings
	const vector<string> getAllTerrainBitmapPathsFromFile();
	const vector<string> getAllTerrainTexturePathsFromFile();
	const vector<string>& getLoadedTerrainIDs();

	// Booleans
	bool loadTerrainEntitiesFromFile();
	bool saveTerrainEntitiesToFile();
	bool isLoaded();	

private:
	// Voids
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateMeshMenu();
	void _updateBlendMapMenu();
	void _updateNormalMapMenu();
	void _updateLightingMenu();
	void _updateTerrainCreating();
	void _updateTerrainChoosing();
	void _updateTerrainDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	// Instances
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;

	// Strings
	vector <string> _loadedTerrainIDs;
	string _currentProjectID = "";
	string _currentTerrainID = "";

	// Floats
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
	static inline const float MOUSE_SENSITIVITY = 0.025f;
	static inline const float INITIAL_CAMERA_YAW = 45.0f;
	static inline const float INITIAL_CAMERA_PITCH = 45.0f;
	static inline const float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline const float MIN_CAMERA_PITCH = 1.0f;
	static inline const float GRID_Y_OFFSET = 1.5f;
	static inline const float GRID_SIZE = 1024.0f;
	static inline const float GRID_UV = 10.0f;
	static inline const float CAMERA_DISTANCE_SPEED = 5.0f;
	static inline const float MIN_CAMERA_DISTANCE = 0.5f;

	// Booleans
	bool _isEditorLoaded = false;
	bool _isCreatingTerrain = false;
	bool _isChoosingTerrain = false;
	bool _isEditingTerrain = false;
	bool _isDeletingTerrain = false;
};