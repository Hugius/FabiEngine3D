#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "environment_editor.hpp"
#include "model_editor.hpp"
#include "billboard_editor.hpp"
#include "audio_editor.hpp"
#include "animation_editor.hpp"
#include "transformation_type.hpp"

#include <map>
#include <limits>

class SceneEditor final
{
public:
	SceneEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, EnvironmentEditor& environmentEditor, 
		ModelEditor& modelEditor, AnimationEditor& animationEditor, BillboardEditor& billboardEditor, AudioEditor& audioEditor);
	~SceneEditor() = default;

	void initializeGUI();
	void load();
	void unload();
	void update();
	void setCurrentProjectID(const string&projectName);
	void loadSceneFromFile(const string& fileName);
	void saveSceneToFile();
	void clearScene();
	void placeModel(const string& newID, const string& previewID, Vec3 position);
	void placeBillboard(const string& newID, const string& previewID, Vec3 position);

	bool isLoaded();
	bool isSceneExisting(const string& fileName);

	const string& getLoadedSceneID();

private:
	// Environment updates
	void _updateMainEnvironmentMenu();
	void _updateSkyMenu();
	void _updateTerrainMenu();
	void _updateWaterMenu();

	// Model updates
	void _updateMainModelMenu();
	void _updateModelPlacingMenu();
	void _updateModelChoosingMenu();
	void _updateModelPlacing();
	void _updateModelEditing();

	// Billboard updates
	void _updateMainBillboardMenu();
	void _updateBillboardPlacingMenu();
	void _updateBillboardChoosingMenu();
	void _updateBillboardPlacing();
	void _updateBillboardEditing();

	// Lighting updates
	void _updateMainLightingMenu();
	void _updateAmbientLightingMenu();
	void _updateDirectionalLightingMenu();
	void _updatePointLightingMenu();
	void _updateLightPlacing();
	void _updateLightEditing();

	// Audio updates
	void _updateMainAudioMenu();
	void _updateAudioPlacingMenu();
	void _updateAudioChoosingMenu();
	void _updateAudioPlacing();
	void _updateAudioEditing();

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
	void _updateChoiceMenu();
	void _updateCamera();
	void _updateMiscellaneous();

	// Creation functions
	void _placeSky(const string& newID, const string& previewID);
	void _placeSky(const string& newID, const array<string, 6>& diffuseMapPaths, float lightness, float rotationSpeed, Vec3 color);
	void _placeTerrain(const string& newID, const string& previewID);
	void _placeTerrain(const string& newID, const string& heightMapPath, float maxHeight, float uvRepeat, bool isBlendMapped, float lightness,
		float blendRepeatR, float blendRepeatG, float blendRepeatB, bool isNormalMapped, bool isNormalMappedR, bool isNormalMappedG,
		bool isNormalMappedB, bool isSpecular, float specularFactor,
		float specularIntensity, const string& diffuseMapPath, const string& normalMapPath, const string& normalMapPathR,
		const string& normalMapPathG, const string& normalMapPathB, const string& blendMapPath,
		const string& blendMapPathR, const string& blendMapPathG, const string& blendMapPathB);
	void _placeWater(const string& newID, const string& previewID);
	void _placeWater(const string& newID, Vec3 position, float size, bool isWaving, bool isRippling, bool isSpecularLighted, bool isReflective,
		bool isRefractive, float waveHeightFactor, float specularFactor, float specularIntensity, float transparency, Vec3 color, float uvRepeat,
		Vec2 speed, const string& dudvMapPath, const string& normalMapPath, const string& displacementMapPath);
	void _placeModel(bool scriptExecution, const string& modelName, const string& modelNumber, Vec3 position, Vec3 rotation, Vec3 size, 
		const string& meshPath, const string& diffuseMapPath, const string& lightMapPath, const string& reflectionMapPath, const string& normalMapPath, 
		bool isFrozen, bool isFaceCulled, bool isShadowed, bool isTransparent, bool isSpecular, int reflectionType, float specularFactor,
		float specularIntensity, float lightness, Vec3 color, float uvRepeat, const string& lodEntityID, bool isInstanced,
		vector<Vec3> instancedOffsets, vector<string> aabbNames, vector<Vec3> aabbPositions, vector<Vec3> aabbSizes, string animationID);
	void _placeBillboard(bool scriptExecution, const string& billboardName, const string& billboardNumber,
		const string& diffusePath, const string& fontPath, const string& textContent,
		Vec3 position, Vec3 rotation, Vec2 size, Vec3 color, bool facingX, bool facingY, bool isTransparent,
		bool isAnimated, int animationRows, int animationColumns, int animationFramestep, float lightness);

	// Miscellaneous
	vector<string> _loadSceneNames();
	void _deleteSceneFile(const string& sceneName);
	void _updateModelBlinking(const string& modelID, int& multiplier);
	void _updateBillboardBlinking(const string& billboardID, int& multiplier);
	void _updateLightbulbAnimation(const string& modelID, int& multiplier);
	void _updateSpeakerAnimation(const string& modelID, int& multiplier);
	void _selectModel(const string& modelID);
	void _activateModel(const string& modelID);
	void _selectBillboard(const string& billboardID);
	void _activateBillboard(const string& billboardID);
	void _selectAudio(const string & audioID);
	void _activateAudio(const string & audioID);
	void _handleValueChanging(const string& screenID, string buttonID, string writefieldID, float& value, float adder, float multiplier = 1.0f,
		float minimum = (std::numeric_limits<float>::lowest)(), float maximum = (std::numeric_limits<float>::max)());

	// Instances
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
	EnvironmentEditor& _environmentEditor;
	ModelEditor& _modelEditor;
	AnimationEditor& _animationEditor;
	BillboardEditor& _billboardEditor;
	AudioEditor& _audioEditor;

	// Environment variables
	string _loadedSkyID = "";
	string _loadedTerrainID = "";
	string _loadedWaterID = "";
	string _currentSkyID = "";
	string _currentTerrainID = "";
	string _currentWaterID = "";

	// Model variables
	vector<string> _loadedModelIDs;
	map<string, float> _initialModelLightness;
	map<string, Vec3> _initialModelPosition;
	map<string, Vec3> _initialModelRotation;
	map<string, Vec3> _initialModelSize;
	string _currentPreviewModelName = "";
	string _selectedModelID = "";
	string _activeModelID = "";
	int _selectedModelLightnessMultiplier = 1;
	int _activeModelLightnessMultiplier = 1;
	bool _dontResetSelectedModel = false;
	const float _modelBlinkingSpeed = 0.025f;

	// Billboard variables
	vector<string> _loadedBillboardIDs;
	map<string, float> _initialBillboardLightness;
	string _currentPreviewBillboardName = "";
	string _selectedBillboardID = "";
	string _activeBillboardID = "";
	int _selectedBillboardLightnessMultiplier = 1;
	int _activeBillboardLightnessMultiplier = 1;
	bool _dontResetSelectedBillboard = false;
	const float _billboardBlinkingSpeed = 0.025f;

	// Lighting variables
	vector<string> _loadedLightIDs;
	bool _isPlacingPointlight = false;
	const string _previewPointlightID = "@@previewPointlight";
	const string _lightBulbModelPath = "engine\\meshes\\lamp.obj";
	const Vec3 _defaultLightbulbSize = Vec3(1.0f);
	const Vec3 _defaultLightbulbAabbSize = Vec3(0.7f, 1.15f, 0.7f);
	const float _lightbulbAnimationSpeed = 0.01f;
	const float _lightingChangingSpeed = 0.01f;
	const float _lightingColorChangingSpeed = 0.005f;
	int _selectedLightSizeMultiplier = 1;
	int _activeLightSizeMultiplier = 1;
	string _selectedLightBulbID = "";
	string _activeLightBulbID = "";

	// Audio variables
	vector<string> _loadedAudioIDs;
	string _currentPreviewAudioName = "";
	string _selectedSpeakerID = "";
	string _activeSpeakerID = "";
	const string _previewSpeakerID = "@previewSpeaker";
	const string _speakerModelPath = "engine\\meshes\\speaker.obj";
	const Vec3 _defaultSpeakerSize = Vec3(1.0f);
	const Vec3 _defaultSpeakerAabbSize = Vec3(1.25f, 1.3f, 1.0f);
	const float _defaultAudioMaxDistance = 25.0f;
	const float _speakerAnimationSpeed = 0.01f;
	const float _audioVolumeChangingSpeed = 0.01f;
	const float _audioDistanceChangingSpeed = 0.05f;
	int _selectedAudioSizeMultiplier = 1;
	int _activeAudioSizeMultiplier = 1;
	bool _dontResetSelectedAudio = false;

	// Miscellaneous
	string _loadedSceneID = "";
	string _currentProjectID = "";
	string _currentSceneID = "";
	bool _isEditorLoaded = false;
	bool _isChoosingScene = false;
	bool _isDeletingScene = false;
	TransformationType _transformation = TransformationType::TRANSLATION;
	float _customEditorSpeed = 1.0f;
};