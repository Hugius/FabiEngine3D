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
	void _upateSkyManagement();
	void _updateSkyCamera();
	void _updateSkyMesh();
	void _updateSkyOptions();
	void _upateTerrainManagement();
	void _updateTerrainCamera();
	void _updateTerrainMesh();
	void _updateTerrainBlendmap();
	void _upateWaterManagement();
	void _addValueForm(string ID, float value);
	void _checkValueForm(string ID, float& value);
	void _removeValueForm();

	bool _isLoaded = false;

	WorldPart _currentWorldPart = WorldPart::NONE;

	string _currentProjectName = "";
	string _terrainHeightmapPath = "";
	string _terrainDiffusemapPath = "";
	string _activeWritefield = "";
	string _terrainBlendmapPath = "";
	string _terrainRedPath = "";
	string _terrainGreenPath = "";
	string _terrainBluePath = "";

	float _terrainSize = 0.0f;
	float _maxTerrainHeight = 0.0f;
	float _terrainUvRepeat = 0.0f;
	float _redUvRepeat = 0.0f;
	float _greenUvRepeat = 0.0f;
	float _blueUvRepeat = 0.0f;
	float _cameraRotationSpeed = 0.0f;
	float _cameraDistance = 0.0f;
	float _cameraHeight = 0.0f;
	float _totalCameraRotation = 0.0f;

	vector<string> _skyTexturePaths;

	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui;
	shared_ptr<EngineGuiWindow> _window;
};