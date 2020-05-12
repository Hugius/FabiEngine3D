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
	vector<string>& getModelNames();

	void initialize();
	void loadEnvironment();
	void unloadEnvironment();
	void update(float delta);
	void addModel(string modelName, string objName, string diffuseMapName, string lightMapName, string reflectionMapName, vec3 size);

	bool isLoaded();

private:
	void _loadObjFileNames();
	void _loadOBJ();
	void _loadDiffuseMap();
	void _loadLightMap();
	void _loadReflectionMap();
	void _updateModelManagement();
	void _updateModelCreation();
	void _updateModelChoosing();
	void _updateModelEditing();
	void _updateModelEditingMain();
	void _updateModelEditingMesh();
	void _updateModelEditingOptions();
	void _updateModelRemoval();
	void _updateMiscellaneous();

	bool _modelCreationEnabled = false;
	bool _modelChoosingEnabled = false;
	bool _modelEditingEnabled = false;
	bool _modelResizingEnabled = false;
	bool _modelRemovalEnabled = false;
	bool _loaded = false;

	const vec3 _startingCameraPos = vec3(0.0f, 5.0f, 5.0f);

	float _cameraDistance = 5.0f;
	const float _minCameraDistance = 1.0f;
	const float _maxCameraDistance = 50.0f;
	const float _minCameraHeight = 1.0f;
	const float _cameraSpeed = 0.1f;

	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui;

	shared_ptr<EngineGuiWindow> _window;
	
	string _currentModelName = "";
	vector<string> _modelNames;
	vector<string> _objFileNamesList;
};