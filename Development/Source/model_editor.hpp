#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "direction.hpp"

class ModelEditor final
{
public:
	ModelEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);
	~ModelEditor() = default;

	void initializeGUI();
	void load();
	void unload();
	void update();
	void setCurrentProjectName(const string& projectName);
	void loadGameEntitiesFromFile();
	void saveGameEntitiesToFile();

	bool isLoaded();

	vector<string>& getTotalObjFileNames();
	vector<string>& getModelNames();

private:
	bool _addModel(const string& modelName, string objName, string diffuseMapName, string lightMapName, string reflectionMapName, string normalMapName,
		Vec3 size, bool isFaceCulled, bool isShadowed, bool isTransparent, bool isReflective, bool isSpecular,
		float specularFactor, float specularIntensity, float lightness, Vec3 color, float uvRepeat, string lodEntityID, bool isInstanced,
		vector<string> aabbNames, vector<Vec3> aabbPositions, vector<Vec3> aabbSizes);
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
	EngineGuiManager& _gui;

	// Strings
	string _currentModelID = "";
	string _currentAabbID = "";
	string _currentProjectName = "";
	string _hoveredModelID = "";
	vector<string> _modelIDs;
	vector<string> _objFileNamesList;

	// Vectors
	const Vec3 _defaultCameraPosition = Vec3(0.0f, 5.0f, 5.0f);
	Vec2 _totalCursorDifference = Vec2(0.0f);
	Vec2 _cameraAcceleration = Vec2(0.0f);
	Vec2 _lastCursorPos = Vec2(0.0f);

	// Floats
	float _cameraDistance = 5.0f;
	float _cameraScrollingAcceleration = 0.0f;
	float _aabbTransformationSpeed = 1.0f;
	const float _minCameraDistance = 1.0f;
	const float _minCameraHeight = 1.0f;
	const float _cameraSpeed = 0.15f;
	const float _scrollWheelDivider = 15.0f;

	// Booleans
	bool _isCreatingModel = false;
	bool _isChoosingModel = false;
	bool _isEditingModel = false;
	bool _isDeletingModel = false;
	bool _movingToggled = false;
	bool _resizingToggled = false;
	bool _isEditorLoaded = false;

	// Miscellaneous
	Direction _transformationDirection = Direction::X;
};