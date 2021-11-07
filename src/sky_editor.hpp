#pragma once

#include "fe3d.hpp"
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
	const vector<array<string, 6>> getAllTexturePathsFromFile() const;
	const vector<string>& getLoadedSkyIDs();

	// Booleans
	const bool loadSkyEntitiesFromFile();
	const bool saveSkyEntitiesToFile() const;
	const bool isLoaded() const;

private:
	// Voids
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateTexturingMenu();
	void _updateMiscellaneousMenu();
	void _updateSkyCreating();
	void _updateSkyChoosing();
	void _updateSkyDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	// Strings
	vector <string> _loadedSkyIDs;
	string _currentProjectID = "";
	string _currentSkyID = "";

	// Decimals
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
	static inline const float CURSOR_SENSITIVITY = 0.025f;

	// Booleans
	bool _isCreatingSky = false;
	bool _isChoosingSky = false;
	bool _isDeletingSky = false;
	bool _isEditorLoaded = false;

	// Miscellaneous
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
};