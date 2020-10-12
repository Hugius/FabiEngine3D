#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

enum class TransformationDirection
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

	void initializeGUI();
	void load();
	void save();
	void unload();
	void update();
	void setCurrentProjectName(const string& projectName);
	void loadModels();

	bool isLoaded();

	vector<string>& getTotalObjFileNames();
	vector<string>& getModelNames();

private:
	bool _addModel(const string& modelName, string objName, string diffuseMapName, string lightMapName, string reflectionMapName, string normalMapName,
		vec3 size, bool isFaceCulled, bool isShadowed, bool isTransparent, bool isReflective, bool isSpecular,
		float specularFactor, float specularIntensity, float lightness, vec3 color, float uvRepeat, string lodEntityID, bool isInstanced,
		vector<string> aabbNames, vector<vec3> aabbPositions, vector<vec3> aabbSizes);
	void _loadObjFileNames();
	void _loadOBJ();
	void _loadDiffuseMap();
	void _loadLightMap();
	void _loadReflectionMap();
	void _loadNormalMap();
	void _updateManagementScreen();
	void _updateModelCreation();
	void _updateModelChoosing();
	void _updateEditingScreen();
	void _updateModelEditingMesh();
	void _updateModelEditingOptions();
	void _updateModelEditingLighting();
	void _updateModelEditingSize();
	void _updateModelEditingAabb();
	void _updateModelRemoval();
	void _updateCamera();
	void _updateMiscellaneous();

	// Core
	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui = nullptr;

	// Strings
	string _currentModelID = "";
	string _currentAabbID = "";
	string _currentProjectName = "";
	string _hoveredModelID = "";
	vector<string> _modelNames;
	vector<string> _objFileNamesList;

	// Vectors
	const vec3 _defaultCameraPosition = vec3(0.0f, 5.0f, 5.0f);
	vec2 _totalCursorDifference = vec2(0.0f);
	vec2 _cameraAcceleration = vec2(0.0f);
	vec2 _lastCursorPos = vec2(0.0f);

	// Floats
	float _cameraDistance = 5.0f;
	float _cameraScrollingAcceleration = 0.0f;
	float _aabbTransformationSpeed = 1.0f;
	const float _minCameraDistance = 1.0f;
	const float _minCameraHeight = 1.0f;
	const float _cameraSpeed = 0.15f;
	const float _scrollWheelDivider = 15.0f;

	// Booleans
	bool _modelCreationEnabled = false;
	bool _modelChoosingEnabled = false;
	bool _modelEditingEnabled = false;
	bool _movingToggled = false;
	bool _resizingToggled = false;
	bool _modelRemovalEnabled = false;
	bool _isLoaded = false;

	// Miscellaneous
	TransformationDirection _direction = TransformationDirection::X;
};