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
		bool faceCulled, bool shadowed, bool transparent, bool specular, float specularIntensity, vec3 color, float uvRepeat, vec3 aabbSize);
	void _updateCamera();
	void _updateModelBlinking(string modelID, int& multiplier);
	void _updateLightbulbAnimation(string modelID, int& multiplier);
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
	string _currentPreviewModelName = "";

	// Billboard placement
	string _currentBillboardName = "";

	// Ambient lighting
	vec3 _ambientLightColor = vec3(1.0f);
	float _ambientLightIntensity = 1.0f;

	// Directional lighting
	vec3 _directionalLightColor = vec3(1.0f);
	vec3 _directionalLightPosition = vec3(0.0f);
	float _directionalLightIntensity = 0.0f;

	// Point lighting
	bool _isPlacingPointlight = false;
	const string _previewPointlightID = "@previewPointlight";
	const vec3 _defaultPointlightColor = vec3(1.0f);
	const vec3 _defaultLightbulbSize = vec3(1.0f);
	const vec3 _defaultLightbulbAabbSize = vec3(1.0f, 1.25f, 1.0f);
	const float _defaultPointlightIntensity = 1.0f;

	// Miscellaneous
	bool _isLoaded = false;
	Transformation _transformation = Transformation::TRANSLATION;
	string _currentProjectName = "";
	float _customCameraSpeed = 10.0f;
	const float _modelBlinkingSpeed = 0.025f;
	const float _lightbulbAnimationSpeed = 0.01f;
	const float _transformationSpeed = 0.05f;
};