#pragma once

#include "FabiEngine3D.hpp"
#include "EngineGuiManager.hpp"

enum class RotationType
{
	X,
	Y,
	Z
};

class ModelEditorr final
{
public:
	ModelEditorr(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui);
	~ModelEditorr() = default;

	vector<string>& getTotalObjFileNames();

	void update(float delta);

private:
	// Functions
	void _loadObjFileNames();
	void _updateModelCreation();
	void _updateModelEditing();
	void _updateModelRemoval();
	void _loadOBJ();
	void _loadDiffuseMap();
	void _loadLightMap();
	void _loadReflectionMap();

	bool _modelCreationEnabled = false;
	bool _modelEditingEnabled = false;
	bool _modelRemovalEnabled = false;

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