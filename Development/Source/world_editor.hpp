#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

enum class WorldPart { NONE, SKY, TERRAIN, WATER };

class WorldEditor final
{
public:
	WorldEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui);
	~WorldEditor() = default;

	void initializeGUI();
	void loadProject();
	void saveProject();
	void unloadProject();
	void update(float delta);
	void setCurrentProjectName(string projectName);

	bool isLoaded();

private:
	// General functions
	void _addValueForm(string ID, string title, float value);
	void _checkValueForm(string ID, float& value);
	void _removeValueForm();

	// General variables
	bool _isLoaded = false;
	WorldPart _currentWorldPart = WorldPart::NONE;
	float _delta = 0.0f;
	float _cameraRotationSpeed = 0.0f;
	float _totalCameraRotation = 0.0f;
	string _currentProjectName = "";
	string _activeWritefieldID = "";
	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui;
	shared_ptr<EngineGuiWindow> _window;

	// Sky functions
	void _updateSkyCamera();
	void _upateSkyManagement();
	void _updateSkyMesh();
	void _updateSkyOptions();

	// Sky variables
	vector<string> _skyTexturePaths;

	// Terrain function
	void _updateTerrainCamera();
	void _upateTerrainManagement();
	void _updateTerrainMesh();
	void _updateTerrainBlendmap();

	// Terrain variables
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
	float _terrainCameraHeight = 0.0f;
	float _terrainCameraDistance = 0.0f;

	// Water functions
	void _loadWaterPlane();
	void _updateWaterCamera();
	void _upateWaterManagement();
	void _updateWaterMesh();
	void _updateWaterEffects();
	void _updateWaterOptions();
	
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
};