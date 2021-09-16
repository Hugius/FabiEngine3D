#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class SkyEditor final
{
public:
	SkyEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	// Voids
	void setCurrentProjectID(const string& projectID);
	void load();
	void update();
	void unload();
	void unloadSkyEntities();

	// Strings
	const vector<array<string, 6>> getAllTexturePathsFromFile();
	const vector<string>& getLoadedSkyIDs();

	// Booleans
	bool loadSkyEntitiesFromFile();
	bool saveSkyEntitiesToFile();
	bool isLoaded();

private:
	// Voids
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

	// Instances
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;

	// Strings
	vector <string> _loadedSkyIDs;
	string _currentProjectID = "";
	string _currentSkyID = "";

	// Floats
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
	static inline const float MOUSE_SENSITIVITY = 0.025f;

	// Booleans
	bool _isCreatingSky = false;
	bool _isChoosingSky = false;
	bool _isDeletingSky = false;
	bool _isEditorLoaded = false;
};