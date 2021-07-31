#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class SkyEditor final
{
public:
	SkyEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	void setCurrentProjectID(const string& projectID);
	void load();
	void update();
	void unload();
	void unloadSkyEntities();
	bool loadSkyEntitiesFromFile();
	bool saveSkyEntitiesToFile();

	const vector<array<string, 6>> getAllTexturePathsFromFile();
	const vector<string>& getLoadedSkyIDs();

	bool isLoaded();

private:
	// Functions
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateMeshMenu();
	void _updateOptionsMenu();
	void _updateSkyCreating();
	void _updateSkyChoosing();
	void _updateSkyDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
	static inline const float MOUSE_SENSITIVITY = 0.025f;
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
	string _currentProjectID = "";
	Vec3 _cameraLookatPosition = Vec3(0.0f);
	float _terrainCameraDistance = 0.0f;
	bool _isEditorLoaded = false;
	vector <string> _loadedSkyIDs;
	string _currentSkyID = "";
	bool _isCreatingSky = false;
	bool _isChoosingSky = false;
	bool _isEditingSky = false;
	bool _isDeletingSky = false;
};