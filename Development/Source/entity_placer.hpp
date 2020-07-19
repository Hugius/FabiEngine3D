#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "world_editor.hpp"
#include "model_editor.hpp"
#include "billboard_editor.hpp"

#include <map>
#include <limits>

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
	// Model updates
	void _updateModelScreen();
	void _updateModelPlacingScreen();
	void _updateModelChoosingScreen();
	void _updateModelPlacing();
	void _updateModelEditing();

	// Billboard updates
	void _updateBillboardScreen();
	void _updateBilboardPlacing();
	void _updateBillboardEditing();

	// Light updates
	void _updateLightScreen();
	void _updateAmbientLightScreen();
	void _updateDirectionalLightScreen();
	void _updatePointLightScreen();
	void _updateLightPlacing();
	void _updateLightEditing();

	// Miscellaneous updates
	void _updateManagementScreen();
	void _updateCamera();
	void _updateMiscellaneous();

	// Miscellaneous
	void _placeModel(string modelID, string modelName, vec3 position, vec3 rotation, vec3 size);
	void _placeModel(string modelID, vec3 position, vec3 rotation, vec3 size, string objPath, string diffuseMapPath, string lightMapPath, string reflectionMapPath,
		bool faceCulled, bool shadowed, bool transparent, bool specular, float specularIntensity, vec3 color, float uvRepeat, vec3 aabbSize);
	void _updateModelBlinking(string modelID, int& multiplier);
	void _updateLightbulbAnimation(string modelID, int& multiplier);
	void _handleValueChanging(string screenID, string buttonID, string wfID, float& value, float adder, float multiplier = 1.0f,
		float minimum = (std::numeric_limits<float>::lowest)(), float maximum = (std::numeric_limits<float>::max)());
	void _selectModel(string modelID);
	void _activateModel(string modelID);

	// Instances
	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui;
	WorldEditor& _worldEditor;
	ModelEditor& _modelEditor;
	BillboardEditor& _billboardEditor;
	shared_ptr<EngineGuiWindow> _leftWindow;
	shared_ptr<EngineGuiWindow> _rightWindow;

	// Model variables
	string _currentPreviewModelName = "";
	string _selectedModelID = "";
	string _activeModelID = "";
	int _selectedLightnessMultiplier = 1;
	int _activeLightnessMultiplier = 1;

	// Billboard variables
	string _currentBillboardName = "";

	// Lighting variables
	vec3 _ambientLightColor = vec3(1.0f);
	float _ambientLightIntensity = 1.0f;
	vec3 _directionalLightColor = vec3(1.0f);
	vec3 _directionalLightPosition = vec3(0.0f);
	float _directionalLightIntensity = 0.0f;
	bool _isPlacingPointlight = false;
	const string _previewPointlightID = "@previewPointlight";
	const vec3 _defaultPointlightColor = vec3(1.0f);
	const vec3 _defaultLightbulbSize = vec3(1.0f);
	const vec3 _defaultLightbulbAabbSize = vec3(1.0f, 1.25f, 1.0f);
	const float _defaultPointlightIntensity = 1.0f;
	const float _defaultPointlightDistance = 1.0f;

	// Miscellaneous
	bool _isLoaded = false;
	Transformation _transformation = Transformation::TRANSLATION;
	string _currentProjectName = "";
	float _customCameraSpeed = 10.0f;
	const float _modelBlinkingSpeed = 0.025f;
	const float _lightbulbAnimationSpeed = 0.01f;
	const float _movementChangingSpeed = 0.05f;
	const float _colorChangingSpeed = 0.005f;
};