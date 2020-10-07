#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "world_editor.hpp"
#include "model_editor.hpp"
#include "billboard_editor.hpp"

#include <map>
#include <limits>

enum class TransformationType
{
	TRANSLATION,
	ROTATION,
	SCALING,
};

class SceneEditor final
{
public:
	SceneEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui, WorldEditor& worldEditor, ModelEditor& modelEditor, BillboardEditor& billboardEditor);
	~SceneEditor() = default;

	void initializeGUI();
	void load();
	void save();
	void unload();
	void update();
	void setCurrentProjectName(const string&projectName);
	void loadScene(bool overwriteCamera);
	void unloadScene();

	bool isLoaded();

private:
	// Model updates
	void _updateMainModelMenu();
	void _updateModelPlacingMenu();
	void _updateModelChoosingMenu();
	void _updateModelPlacing();
	void _updateModelEditing();

	// Billboard updates
	void _updateMainBillboardMenu();
	void _updateBilboardPlacingMenu();
	void _updateBillboardChoosingMenu();
	void _updateBillboardPlacing();
	void _updateBillboardEditing();

	// Light updates
	void _updateMainLightingMenu();
	void _updateAmbientLightingMenu();
	void _updateDirectionalLightingMenu();
	void _updatePointLightingMenu();
	void _updateLightPlacing();
	void _updateLightEditing();

	// Settings updates
	void _updateMainSettingsMenu();
	void _updateGraphicsSettingsMenu();
	void _updateShadowGraphicsSettingsMenu();
	void _updateMotionblurGraphicsSettingsMenu();
	void _updateDofGraphicsSettingsMenu();
	void _updateFogGraphicsSettingsMenu();
	void _updateLensFlareGraphicsSettingsMenu();
	void _updateskyHdrGraphicsSettingsMenu();

	// Miscellaneous updates
	void _updateMainMenu();
	void _updateCamera();
	void _updateMiscellaneous();

	// Miscellaneous
	bool _loadSceneFile(bool overwriteCamera);
	void _placeModel(const string& newID, const string& previewID, vec3 position);
	void _placeModel(const string& newID, vec3 position, vec3 rotation, vec3 size, const string& objPath, const string& diffuseMapPath,
		const string& lightMapPath, const string& reflectionMapPath, const string& normalMapPath, bool isFrozen,
		bool isFaceCulled, bool isShadowed, bool isTransparent, bool isReflective, bool isSpecular, 
		float specularFactor, float specularIntensity, float lightness, vec3 color, float uvRepeat, const string& lodEntityID, bool isInstanced,
		vector<vec3> instancedOffsets, vector<string> aabbNames, vector<vec3> aabbPositions, vector<vec3> aabbSizes);
	void _placeBillboard(const string& newID, const string& previewID, vec3 position);
	void _updateModelBlinking(const string& modelID, int& multiplier);
	void _updateBillboardBlinking(const string& billboardID, int& multiplier);
	void _updateLightbulbAnimation(const string& modelID, int& multiplier);
	void _selectModel(const string& modelID);
	void _activateModel(const string& modelID);
	void _selectBillboard(const string& modelID);
	void _activateBillboard(const string& modelID);
	void _handleValueChanging(const string& screenID, string buttonID, string wfID, float& value, float adder, float multiplier = 1.0f,
		float minimum = (std::numeric_limits<float>::lowest)(), float maximum = (std::numeric_limits<float>::max)());

	// Instances
	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui = nullptr;
	WorldEditor& _worldEditor;
	ModelEditor& _modelEditor;
	BillboardEditor& _billboardEditor;
	shared_ptr<EngineGuiWindow> _leftWindow = nullptr;
	shared_ptr<EngineGuiWindow> _rightWindow = nullptr;

	// Model variables
	string _currentPreviewModelName = "";
	string _selectedModelID = "";
	string _activeModelID = "";
	int _selectedModelLightnessMultiplier = 1;
	int _activeModelLightnessMultiplier = 1;
	bool _dontResetSelectedModel = false;
	const float _modelBlinkingSpeed = 0.025f;

	// Billboard variables
	string _currentPreviewBillboardName = "";
	string _selectedBillboardID = "";
	string _activeBillboardID = "";
	int _selectedBillboardLightnessMultiplier = 1;
	int _activeBillboardLightnessMultiplier = 1;
	bool _dontResetSelectedBillboard = false;
	const float _billboardBlinkingSpeed = 0.025f;

	// Lighting variables
	bool _isPlacingPointlight = false;
	const string _previewPointlightID = "@previewPointlight";
	const vec3 _defaultLightbulbSize = vec3(1.0f);
	const vec3 _defaultLightbulbAabbSize = vec3(1.0f, 1.25f, 1.0f);
	const float _lightbulbAnimationSpeed = 0.01f;
	const float _lightingChangingSpeed = 0.01f;
	const float _colorChangingSpeed = 0.005f;
	int _selectedLightSizeMultiplier = 1;
	int _activeLightSizeMultiplier = 1;
	string _selectedLightBulbID = "";
	string _activeLightBulbID = "";

	// Miscellaneous
	bool _isLoaded = false;
	bool _isLoadingSceneEditor = false;
	TransformationType _transformation = TransformationType::TRANSLATION;
	string _currentProjectName = "";
	float _customCameraSpeed = 1.0f;
	const float _movementChangingSpeed = 0.1f;
};