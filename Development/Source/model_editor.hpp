#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

enum class Direction
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

	void initializeGUI();
	void load();
	void save();
	void unload();
	void update();
	void setCurrentProjectName(string projectName);

	bool isLoaded();

private:
	void _addModel(string modelName, string objName, string diffuseMapName, string lightMapName, string reflectionMapName, vec3 size,
		bool faceCulled, bool shadowed, bool transparent, bool specular, vec3 color, float uvRepeat, vec3 aabbSize);
	void _loadObjFileNames();
	void _loadOBJ();
	void _loadDiffuseMap();
	void _loadLightMap();
	void _loadReflectionMap();
	void _updateModelManagement();
	void _updateModelCreation();
	void _updateModelChoosing();
	void _updateModelEditing();
	void _updateModelEditingCamera();
	void _updateModelEditingMesh();
	void _updateModelEditingOptions();
	void _updateModelEditingSize();
	void _updateModelRemoval();
	void _updateMiscellaneous();

	bool _modelCreationEnabled = false;
	bool _modelChoosingEnabled = false;
	bool _modelEditingEnabled = false;
	bool _modelResizingEnabled = false;
	bool _modelColorPicking = false;
	bool _meshResizingToggled = false;
	bool _boxResizingToggled = false;  
	bool _settingModelUvRepeat = false;
	bool _modelRemovalEnabled = false;
	bool _aabbRenderingEnabled = false;
	bool _isLoaded = false;

	const vec3 _defaultCameraPosition = vec3(0.0f, 5.0f, 5.0f);

	Direction _modelResizeDirection = Direction::X;

	float _cameraDistance = 5.0f;
	const float _minCameraDistance = 1.0f;
	const float _maxCameraDistance = 50.0f;
	const float _minCameraHeight = 1.0f;
	const float _cameraSpeed = 0.15f;
	const float _scrollWheelDivider = 15.0f;

	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui;

	shared_ptr<EngineGuiWindow> _window;
	
	string _currentModelName = "";
	string _currentProjectName = "";
	vector<string> _modelNames;
	vector<string> _objFileNamesList;
};