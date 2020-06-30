#pragma once

#include <map>

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "model_editor.hpp"
#include "world_editor.hpp"

enum class Transformation
{
	TRANSLATION,
	ROTATION,
	SCALING,
};

class EntityPlacer final
{
public:
	EntityPlacer(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui, ModelEditor& modelEditor, WorldEditor& worldEditor);
	~EntityPlacer() = default;

	void initializeGUI();
	void load();
	void save();
	void unload();
	void update();
	void setCurrentProjectName(string projectName);

	bool isLoaded();

private:
	void _updateManagementScreen();
	void _updateModelScreen();
	void _updateBillboardScreen();
	void _updateLightScreen();
	void _updateModelPlacing();
	void _updateBilboardPlacing();
	void _updateLightPlacing();
	void _updateModelEditing();
	void _updateBillboardEditing();
	void _updateLightEditing();
	void _updateCamera();
	void _updateMiscellaneous();

	bool _isLoaded = false;

	Transformation _transformation = Transformation::TRANSLATION;

	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui;
	ModelEditor& _modelEditor;
	WorldEditor& _worldEditor;

	shared_ptr<EngineGuiWindow> _leftWindow;
	shared_ptr<EngineGuiWindow> _rightWindow;
	
	string _currentModelName = "";
	string _currentProjectName = "";

	std::map<string, unsigned int> _counterMap;

	float _cameraMovementSpeed = 25.0f;
	const float _blinkingSpeed = 0.025f;
	const float _transformationSpeed = 0.05f;
};