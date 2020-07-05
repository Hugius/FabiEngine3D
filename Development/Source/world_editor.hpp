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
	void setCurrentProjectName(string projectName);
	void loadSkyEntity();
	void loadTerrainEntity();
	void loadWaterEntity();

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
	shared_ptr<EngineGuiManager> _gui;
	shared_ptr<EngineGuiWindow> _leftWindow;

	// Sky functions
	void _saveSkyData();
	void _unloadSkyData();
	void _loadSkyEntity();
	void _updateSkyMenu();
	void _updateSkyManagement();
	void _updateSkyMesh();
	void _updateSkyOptions();
	void _updateSkyCamera();

	// Sky variables
	vector<string> _skyTexturePaths;
	float _skyRotationSpeed = 0.0f;
	float _skyBrightness = 1.0f;
	vec3 _skyColor = vec3(1.0f);

	// Terrain function
	void _saveTerrainData();
	void _unloadTerrainData();
	void _loadTerrainEntity();
	void _updateTerrainMenu();
	void _updateTerrainManagement();
	void _updateTerrainMesh();
	void _updateTerrainBlendmap();
	void _updateTerrainCamera();

	// Terrain variables
	bool _isTerrainBlendmapped = false;
	string _terrainHeightmapPath = "";
	string _terrainDiffusemapPath = "";
	string _terrainBlendmapPath = "";
	string _terrainRedPath = "";
	string _terrainGreenPath = "";
	string _terrainBluePath = "";
	float _terrainSize = 0.0f;
	float _maxTerrainHeight = 0.0f;
	float _terrainUvRepeat = 0.0f;
	float _terrainRedUvRepeat = 0.0f;
	float _terrainGreenUvRepeat = 0.0f;
	float _terrainBlueUvRepeat = 0.0f;
	float _terrainBrightness = 1.0f;
	float _terrainCameraHeight = 0.0f;
	float _terrainCameraDistance = 0.0f;

	// Water functions
	void _saveWaterData();
	void _unloadWaterData();
	void _loadWaterEntity();
	void _updateWaterMenu();
	void _updateWaterManagement();
	void _updateWaterMesh();
	void _updateWaterEffects();
	void _updateWaterOptions();
	void _updateWaterCamera();
	
	// Water variables
	string _waterDudvmapPath = "";
	string _waterNormalmapPath = "";
	bool _waterWavingEnabled = false;
	bool _waterRipplingEnabled = false;
	bool _waterSpecularEnabled = false;
	bool _waterReflectionEnabled = false;
	bool _waterRefractionEnabled = false;
	vec3 _waterColor = vec3(0.0f);
	float _waterSize = 0.0f;
	float _waterUvRepeat = 0.0f;
	float _waterHeight = 0.0f;
	float _waterSpeed = 0.0f;
	float _waterTransparency = 0.0f;
	float _waterShininess = 16.0f;
	float _waterCameraHeight = 0.0f;
	float _waterCameraDistance = 0.0f;
	float _waterHeightSpeed = 0.1f;
};