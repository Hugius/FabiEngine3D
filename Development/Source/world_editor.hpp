#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

enum class WorldPart
{
	NONE, 
	SKY, 
	TERRAIN, 
	WATER 
};

class WorldEditor final
{
public:
	WorldEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui);
	~WorldEditor() = default;

	void initializeGUI();
	void load();
	void save();
	void unload();
	void update();
	void setCurrentProjectName(const string& projectName);
	void loadSkyEntities();
	void loadTerrainEntities();
	void loadWaterEntities();
	void unloadSkyEntities();
	void unloadTerrainEntities();
	void unloadWaterEntities();

	bool isLoaded();

private:
	// General variables
	bool _isLoaded = false;
	WorldPart _currentWorldPart = WorldPart::NONE;
	const float _scrollWheelDivider = 250.0f;
	float _cameraRotationSpeed = 0.0f;
	float _totalCameraRotation = 0.0f;
	string _currentProjectName = "";
	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui = nullptr;
	shared_ptr<EngineGuiWindow> _leftWindow = nullptr;

	// Sky variables
	vector <string> _skyNames;
	string _currentSkyID = "";
	string _hoveredSkyID = "";
	bool _skyCreationEnabled = false;
	bool _skyChoosingEnabled = false;
	bool _skyEditingEnabled = false;
	bool _skyRemovalEnabled = false;

	// Terrain variables
	vector <string> _terrainNames;
	string _currentTerrainID = "";
	string _hoveredTerrainID = "";
	bool _terrainCreationEnabled = false;
	bool _terrainChoosingEnabled = false;
	bool _terrainEditingEnabled = false;
	bool _terrainRemovalEnabled = false;

	// Water variables
	vector <string> _waterNames;
	string _currentWaterID = "";
	string _hoveredWaterID = "";
	bool _waterCreationEnabled = false;
	bool _waterChoosingEnabled = false;
	bool _waterEditingEnabled = false;
	bool _waterRemovalEnabled = false;

	// Sky functions
	void _saveSkyData();
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
	void _saveTerrainData();
	void _updateTerrainEditor();
	void _updateTerrainMenuMain();
	void _updateTerrainMenuChoice();
	void _updateTerrainMenuMesh();
	void _updateTerrainMenuBlendMap();
	void _updateTerrainCreation();
	void _updateTerrainChoosing();
	void _updateTerrainRemoval();
	void _updateTerrainCamera();

	// Water functions
	void _saveWaterData();
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
};