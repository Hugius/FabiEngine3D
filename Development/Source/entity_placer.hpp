#pragma once

#include <map>

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "world_editor.hpp"
#include "model_editor.hpp"
#include "billboard_editor.hpp"

enum class Transformation
{
	TRANSLATION,
	ROTATION,
	SCALING,
};

class EntityPlacer final
{
public:
	EntityPlacer(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui, WorldEditor& worldEditor, ModelEditor& modelEditor, BillboardEditor& billboardEditor);
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
	void _placeModel(string modelID, vec3 position, vec3 rotation, vec3 size, string objPath, string diffuseMapPath, string lightMapPath, string reflectionMapPath,
		bool faceCulled, bool shadowed, bool transparent, bool specular, float specularStrength, vec3 color, float uvRepeat, vec3 aabbSize);
	void _updateCamera();
	void _updateMiscellaneous();

	// Instances
	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui;
	WorldEditor& _worldEditor;
	ModelEditor& _modelEditor;
	BillboardEditor& _billboardEditor;
	shared_ptr<EngineGuiWindow> _leftWindow;
	shared_ptr<EngineGuiWindow> _rightWindow;

	// Model placement
	string _currentModelName = "";

	// Billboard placement
	string _currentBillboardName = "";

	// Ambient lighting
	vec3 _ambientLightColor = vec3(1.0f);
	float _ambientLightStrength = 1.0f;

	// Directional lighting
	vec3 _directionalLightColor = vec3(1.0f);
	vec3 _directionalLightPosition = vec3(0.0f);
	float _directionalLightStrength = 0.0f;

	// Point lighting
	bool _isPlacingPointlight = false;
	const string _previewPointlightID = "@previewPointlight";

	// Miscellaneous
	bool _isLoaded = false;
	Transformation _transformation = Transformation::TRANSLATION;
	string _currentProjectName = "";
	float _customCameraSpeed = 25.0f;
	const float _blinkingSpeed = 0.025f;
	const float _transformationSpeed = 0.05f;
};