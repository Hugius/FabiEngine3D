#pragma once

#include "fe3d.hpp"
#include "engine_gui_manager.hpp"
#include "reflection_type.hpp"

class ModelEditor final
{
public:
	ModelEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	// VOID
	void setCurrentProjectID(const string& projectID);
	void load();
	void unload();
	void update();

	// STRING
	const vector<string> getAllMeshPathsFromFile() const;
	const vector<string> getAllTexturePathsFromFile() const;
	const vector<string>& getLoadedModelIDs();

	// BOOL
	const bool loadModelEntitiesFromFile();
	const bool saveModelEntitiesToFile() const;
	const bool isLoaded() const;

private:
	// VOID
	void _loadGUI();
	void _unloadGUI();
	void _tryPartChoosing(const string& nextActiveScreenID);
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateTexturingMenu();
	void _updateLightingMenu();
	void _updateMiscellaneousMenu();
	void _updateMainAabbMenu();
	void _updateChoiceAabbMenu();
	void _updateModelCreating();
	void _updateModelChoosing();
	void _updateModelDeleting();
	void _updatePartChoosing();
	void _updateAabbCreating();
	void _updateAabbChoosing();
	void _updateAabbDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	// STRING
	vector<string> _loadedModelIDs;
	string _currentModelID = "";
	string _currentPartID = "";
	string _currentAabbID = "";
	string _currentProjectID = "";
	string _hoveredModelID = "";
	string _nextActiveScreenID = "";

	// FLOAT
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
	static inline const float CURSOR_SENSITIVITY = 0.025f;
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

	// BOOL
	bool _isCreatingModel = false;
	bool _isChoosingModel = false;
	bool _isDeletingModel = false;
	bool _isChoosingPart = false;
	bool _isCreatingAabb = false;
	bool _isChoosingAabb = false;
	bool _isDeletingAabb = false;
	bool _isEditorLoaded = false;

	// MISCELLANEOUS
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
};