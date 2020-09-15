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
	shared_ptr<EngineGuiManager> _gui = nullptr;
	shared_ptr<EngineGuiWindow> _leftWindow = nullptr;

	// Sky functions
	void _saveSkyData();
	void _loadSkyEntity();
	void _updateSkyMenuMain();
	void _updateSkyMenuChoice();
	void _updateSkyMenuMesh();
	void _updateSkyMenuOptions();
	void _updateSkyCamera();

	// Terrain function
	void _saveTerrainData();
	void _loadTerrainEntity(const string& heightMapPath);
	void _updateTerrainMenuMain();
	void _updateTerrainMenuChoice();
	void _updateTerrainMenuMesh();
	void _updateTerrainMenuBlendMap();
	void _updateTerrainCamera();

	// Water functions
	void _saveWaterData();
	void _loadWaterEntity();
	void _updateWaterMenuMain();
	void _updateWaterMenuChoice();
	void _updateWaterMenuMesh();
	void _updateWaterMenuEffects();
	void _updateWaterMenuOptions();
	void _updateWaterCamera();
};