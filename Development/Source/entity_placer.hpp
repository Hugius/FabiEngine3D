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
	void loadWorld();

	bool isLoaded();

private:
	// Menus
	void _updateManagementScreen();
	void _updateModelScreen();
	void _updateBillboardScreen();
	void _updateLightScreen();
	void _updateAmbientLightScreen();
	void _updateDirectionalLightScreen();
	void _updatePointLightScreen();

	// Placement
	void _updateModelPlacing();
	void _updateBilboardPlacing();
	void _updateLightPlacing();

	// Editing
	void _updateModelEditing();
	void _updateBillboardEditing();
	void _updateLightEditing();

	// Miscellaneous
	void _placeModel(string modelID, string modelName, vec3 position, vec3 rotation, vec3 size);
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

	vec3 _directionalPos = vec3(0.0f);

	float _ambientStrength = 0.5f;
	float _directionalStrength = 0.0f;
	float _cameraMovementSpeed = 25.0f;
	const float _blinkingSpeed = 0.025f;
	const float _transformationSpeed = 0.05f;
};