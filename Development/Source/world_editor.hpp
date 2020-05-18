#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

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
	void _updateWorldManagement();
	void _upateSkyManagement();
	void _updateSkyMesh();
	void _updateSkyOptions();
	void _upateTerrainManagement();
	void _updateTerrainCamera();
	void _updateTerrainMesh();
	void _updateTerrainBlendmap();
	void _upateWaterManagement();

	bool _isLoaded = false;

	string _currentProjectName = "";
	string _terrainHeightmapPath = "";
	string _terrainDiffusemapPath = "";
	string _activeWritefield = "";

	float _terrainSize = 384.0f;
	float _maxTerrainHeight = 50.0f;
	float _terrainUvRepeat = 10.0f;
	float _cameraRotationSpeed = 0.0f;
	float _cameraDistance = 0.0f;
	float _cameraHeight = 0.0f;
	float _totalCameraRotation = 0.0f;

	vector<string> _skyTexturePaths;

	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui;

	shared_ptr<EngineGuiWindow> _window;
};