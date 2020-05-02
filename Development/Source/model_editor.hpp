#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

enum class RotationType
{
	X,
	Y,
	Z
};

class ModelEditor final
{
public:
	ModelEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui);
	~ModelEditor() = default;

	vector<string>& getTotalObjFileNames();

	void update(float delta);

private:
	// Functions
	void _loadObjFileNames();
	void _loadEnvironment();
	void _unloadEnvironment();
	void _updateModelCreation();
	void _updateModelEditing();
	void _updateModelRemoval();
	void _loadOBJ();
	void _loadDiffuseMap();
	void _loadLightMap();
	void _loadReflectionMap();

	bool _modelCreationEnabled = false;
	bool _modelChoosingEnabled = false;
	bool _modelEditingEnabled = false;
	bool _modelRemovalEnabled = false;

	const vec3 _startingCameraPos = vec3(0.0f, 5.0f, 5.0f);

	float _cameraDistance = 5.0f;
	const float _minCameraDistance = 1.0f;
	const float _maxCameraDistance = 20.0f;
	const float _minCameraHeight = 1.0f;
	const float _maxCameraHeight = 25.0f;
	const float _cameraSpeed = 5.0f;

	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui;

	string _modelNameTextfieldEntityID = "";
	string _currentModelName = "";
	string _activeScreenID = "";
	string _hoveredItemID = "";
	vector<string> _modelNames;
	vector<string> _totalObjFileNames;

	unsigned int _modelIndex = 0;
	RotationType _rotationType = RotationType::Y;
};