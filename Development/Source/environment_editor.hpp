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
	void _updateSkyCreation();
	void _updateSkyChoosing();
	void _updateSkyRemoval();
	void _updateSkyCamera();

	// Terrain function
	void _updateTerrainEditor();
	void _updateTerrainMenuMain();
	void _updateTerrainMenuChoice();
	void _updateTerrainMenuMesh();
	void _updateTerrainMenuBlendMap();
	void _updateTerrainMenuLighting();
	void _updateTerrainCreation();
	void _updateTerrainChoosing();
	void _updateTerrainRemoval();
	void _updateTerrainCamera();

	// Water functions
	void _updateWaterEditor();
	void _updateWaterMenuMain();
	void _updateWaterMenuChoice();
	void _updateWaterMenuMesh();
	void _updateWaterMenuEffects();
	void _updateWaterMenuOptions();
	void _updateWaterCreation();
	void _updateWaterChoosing();
	void _updateWaterRemoval();
	void _updateWaterCamera();

	// Miscellaneous functions
	void _updateMiscellaneous();

	// General variables
	static inline const float MOUSE_SENSITIVITY = 0.025f;
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
	EnvironmentType _currentEnvironmentType = EnvironmentType();
	string _currentProjectID = "";
	bool _isEditorLoaded = false;
	bool _isInMainMenu = false;

	// Sky variables
	vector <string> _loadedSkyIDs;
	string _currentSkyID = "";
	bool _isSkyCreationEnabled = false;
	bool _isSkyChoosingEnabled = false;
	bool _isSkyEditingEnabled = false;
	bool _isSkyRemovalEnabled = false;

	// Terrain variables
	vector <string> _loadedTerrainIDs;
	string _currentTerrainID = "";
	bool _isTerrainCreationEnabled = false;
	bool _isTerrainChoosingEnabled = false;
	bool _isTerrainEditingEnabled = false;
	bool _isTerrainRemovalEnabled = false;

	// Water variables
	vector <string> _loadedWaterIDs;
	string _currentWaterID = "";
	bool _isWaterCreationEnabled = false;
	bool _isWaterChoosingEnabled = false;
	bool _isWaterEditingEnabled = false;
	bool _isWaterRemovalEnabled = false;
};