#pragma once

#include "fe3d.hpp"
#include "engine_gui_manager.hpp"
#include "sky_editor.hpp"
#include "terrain_editor.hpp"
#include "water_editor.hpp"
#include "model_editor.hpp"
#include "animation_editor.hpp"
#include "billboard_editor.hpp"
#include "audio_editor.hpp"
#include "transformation_type.hpp"

#include <map>
#include <limits>

using std::numeric_limits;

class SceneEditor final
{
public:
	SceneEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, SkyEditor& skyEditor, TerrainEditor& terrainEditor, WaterEditor& waterEditor, ModelEditor& modelEditor, AnimationEditor& animationEditor, BillboardEditor& billboardEditor, AudioEditor& audioEditor);

	// Voids
	void setCurrentProjectID(const string& ID);
	void load();
	void unload();
	void update();
	void createCustomScene(const string& ID);
	void addLightingToCustomScene();
	void addGraphicsToCustomScene();
	void addSkyToCustomScene();
	void addTerrainToCustomScene();
	void addWaterToCustomScene();
	void addModelToCustomScene(const string& ID);
	void addBillboardToCustomScene(const string& ID);
	void addAabbToCustomScene(const string& ID);
	void addSoundToCustomScene(const string& ID);
	void addPointlightToCustomScene(const string& ID);
	void addSpotlightToCustomScene(const string& ID);
	void addReflectionToCustomScene(const string& ID);
	void copyPreviewModel(const string& newID, const string& previewID, Vec3 position);
	void copyPreviewBillboard(const string& newID, const string& previewID, Vec3 position);
	void copyPreviewSound(const string& newID, const string& previewID, Vec3 position);
	void clearCurrentScene();

	// Strings
	const string& getLoadedSceneID();

	// Booleans
	bool isLoaded();
	bool isSceneExisting(const string& filename);
	bool loadEditorSceneFromFile(const string& filename);
	bool saveEditorSceneToFile();
	bool loadCustomSceneFromFile(const string& filename);
	bool saveCustomSceneToFile();

private:
	// Voids
	void _loadGUI();
	void _unloadGUI();
	void _updateSkyMenu();
	void _updateTerrainMenu();
	void _updateWaterMenu();
	void _updateModelMenu();
	void _updateModelPlacingMenu();
	void _updateModelChoosingMenu();
	void _updateModelPlacing();
	void _updateModelEditing();
	void _updateBillboardMenu();
	void _updateBillboardPlacingMenu();
	void _updateBillboardChoosingMenu();
	void _updateBillboardPlacing();
	void _updateBillboardEditing();
	void _updateSoundMenu();
	void _updateSoundPlacingMenu();
	void _updateSoundChoosingMenu();
	void _updateSoundPlacing();
	void _updateSoundEditing();
	void _updatePointlightMenu();
	void _updatePointlightChoosingMenu();
	void _updatePointlightPlacing();
	void _updatePointlightEditing();
	void _updateSpotlightMenu();
	void _updateSpotlightChoosingMenu();
	void _updateSpotlightPlacing();
	void _updateSpotlightEditing();
	void _updateReflectionMenu();
	void _updateReflectionChoosingMenu();
	void _updateReflectionPlacing();
	void _updateReflectionEditing();
	void _updateSettingsMenu();
	void _updateLightingSettingsMenu();
	void _updateAmbientLightingSettingsMenu();
	void _updateDirectionalLightingSettingsMenu();
	void _updateGraphicsSettingsMenu();
	void _updateShadowGraphicsSettingsMenu();
	void _updateMotionBlurGraphicsSettingsMenu();
	void _updateDofGraphicsSettingsMenu();
	void _updateFogGraphicsSettingsMenu();
	void _updateLensFlareGraphicsSettingsMenu();
	void _updateSkyExposureGraphicsSettingsMenu();
	void _updateBloomGraphicsSettingsMenu();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateCamera();
	void _updateMiscellaneous();
	void _deleteSceneFile(const string& ID);
	void _updateModelBlinking(const string& ID, int& direction);
	void _updateBillboardBlinking(const string& ID, int& direction);
	void _updateSpeakerAnimation(const string& ID, int& direction);
	void _updateLampAnimation(const string& ID, int& direction);
	void _updateCameraAnimation(const string& ID, int& direction);
	void _selectModel(const string& ID);
	void _selectBillboard(const string& ID);
	void _selectSound(const string& ID);
	void _selectPointlight(const string& ID);
	void _selectSpotlight(const string& ID);
	void _selectReflection(const string& ID);
	void _activateModel(const string& ID);
	void _activateBillboard(const string& ID);
	void _activateSound(const string& ID);
	void _activatePointlight(const string& ID);
	void _activateSpotlight(const string& ID);
	void _activateReflection(const string& ID);
	void _deactivateModel();
	void _deactivateBillboard();
	void _deactivateSound();
	void _deactivatePoinlight();
	void _deactivateReflection();
	void _handleValueChanging(const string& screenID, string buttonID, string writeFieldID, float& value, float adder, float multiplier = 1.0f, float minimum = numeric_limits<float>::lowest(), float maximum = numeric_limits<float>::max());

	// Strings
	vector<string> _loadSceneIDs();

	// Booleans
	bool _copyPreviewSky(const string& newID, const string& previewID);
	bool _copyPreviewTerrain(const string& newID, const string& previewID);
	bool _copyPreviewWater(const string& newID, const string& previewID);
	bool _copyPreviewModel(const string& newID, const string& previewID, Vec3 position, bool fromOutside = false);
	bool _copyPreviewBillboard(const string& newID, const string& previewID, Vec3 position, bool fromOutside = false);
	bool _copyPreviewSound(const string& newID, const string& previewID, Vec3 position, bool fromOutside = false);
	
	// Instances
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
	SkyEditor& _skyEditor;
	TerrainEditor& _terrainEditor;
	WaterEditor& _waterEditor;
	ModelEditor& _modelEditor;
	AnimationEditor& _animationEditor;
	BillboardEditor& _billboardEditor;
	AudioEditor& _audioEditor;

	// Strings
	static inline const string PREVIEW_SPEAKER_ID = "@@previewSpeaker";
	static inline const string PREVIEW_LAMP_ID = "@@previewLamp";
	static inline const string PREVIEW_CAMERA_ID = "@@previewCamera";
	static inline const string SPEAKER_MODEL_PATH = "engine_assets\\meshes\\speaker.obj";
	static inline const string LAMP_MODEL_PATH = "engine_assets\\meshes\\lamp.obj";
	static inline const string CAMERA_MODEL_PATH = "engine_assets\\meshes\\camera.obj";
	map<string, string> _loadedModelIDs;
	map<string, string> _outsideLoadedModelIDs;
	map<string, string> _loadedBillboardIDs;
	map<string, string> _outsideLoadedBillboardIDs;
	map<string, string> _loadedSoundIDs;
	map<string, string> _outsideLoadedSoundIDs;
	map<string, Vec3> _initialModelPosition;
	map<string, Vec3> _initialModelRotation;
	map<string, Vec3> _initialModelSize;
	vector<string> _customSceneModelIDs;
	vector<string> _customSceneBillboardIDs;
	vector<string> _customSceneAabbIDs;
	vector<string> _customSceneSoundIDs;
	vector<string> _customScenePointlightIDs;
	vector<string> _customSceneReflectionIDs;
	vector<string> _loadedAabbIDs;
	vector<string> _loadedPointlightIDs;
	vector<string> _loadedReflectionIDs;
	string _customSceneID = "";
	string _loadedSkyID = "";
	string _loadedTerrainID = "";
	string _loadedWaterID = "";
	string _currentSkyID = "";
	string _currentTerrainID = "";
	string _currentWaterID = "";
	string _currentPreviewModelID = "";
	string _selectedModelID = "";
	string _activeModelID = "";
	string _currentPreviewBillboardID = "";
	string _selectedBillboardID = "";
	string _activeBillboardID = "";
	string _currentPreviewSoundID = "";
	string _selectedSpeakerID = "";
	string _activeSpeakerID = "";
	string _selectedLampID = "";
	string _activeLampID = "";
	string _selectedTorchID = "";
	string _activeTorchID = "";
	string _selectedCameraID = "";
	string _activeCameraID = "";
	string _loadedSceneID = "";
	string _currentProjectID = "";
	string _currentSceneID = "";

	// Vectors
	static inline const Vec3 DEFAULT_SPEAKER_SIZE = Vec3(1.0f, 1.0f, 1.0f);
	static inline const Vec3 DEFAULT_SPEAKER_AABB_SIZE = Vec3(1.05f, 1.05f, 0.9f);
	static inline const Vec3 DEFAULT_LAMP_SIZE = Vec3(1.0f, 1.0f, 1.0f);
	static inline const Vec3 DEFAULT_LAMP_AABB_SIZE = Vec3(0.6f, 1.0f, 0.6f);
	static inline const Vec3 DEFAULT_CAMERA_SIZE = Vec3(1.0f, 1.0f, 1.0f);
	static inline const Vec3 DEFAULT_CAMERA_AABB_SIZE = Vec3(1.0f, 1.0f, 1.0f);
	static inline const Vec3 MODEL_TERRAIN_OFFSET = Vec3(0.0f, 0.0f, 0.0f);
	static inline const Vec3 BILLBOARD_TERRAIN_OFFSET = Vec3(0.0f, 0.0f, 0.0f);
	static inline const Vec3 SOUND_TERRAIN_OFFSET = Vec3(0.0f, 0.5f, 0.0f);
	static inline const Vec3 POINTLIGHT_TERRAIN_OFFSET = Vec3(0.0f, 1.5f, 0.0f);
	static inline const Vec3 REFLECTION_TERRAIN_OFFSET = Vec3(0.0f, 0.5f, 0.0f);
	static inline const Vec3 SPEAKER_OFFSET = Vec3(0.0f, 0.5f, 0.0f);
	static inline const Vec3 LAMP_OFFSET = Vec3(0.0f, 0.5f, 0.0f);
	static inline const Vec3 CAMERA_OFFSET = Vec3(0.0f, 0.5f, 0.0f);

	// Floats
	static inline const float MODEL_BLINKING_SPEED = 0.025f;
	static inline const float MODEL_SIZE_MULTIPLIER = 100.0f;
	static inline const float BILLBOARD_BLINKING_SPEED = 0.025f;
	static inline const float BILLBOARD_SIZE_MULTIPLIER = 100.0f;
	static inline const float SPEAKER_SIZE_INCREASE = 1.25f;
	static inline const float DEFAULT_SOUND_MAX_VOLUME = 1.0f;
	static inline const float DEFAULT_SOUND_MAX_DISTANCE = 25.0f;
	static inline const float SPEAKER_ANIMATION_SPEED = 0.025f;
	static inline const float SOUND_VOLUME_CHANGING_SPEED = 0.01f;
	static inline const float DEFAULT_POINTLIGHT_RADIUS = 5.0f;
	static inline const float DEFAULT_POINTLIGHT_INTENSITY = 10.0f;
	static inline const float LAMP_SIZE_INCREASE = 1.25f;
	static inline const float LAMP_ANIMATION_SPEED = 0.025f;
	static inline const float POINTLIGHT_INTENSITY_CHANGING_SPEED = 0.01f;
	static inline const float POINTLIGHT_COLOR_CHANGING_SPEED = 0.005f;
	static inline const float CAMERA_SIZE_INCREASE = 1.25f;
	static inline const float CAMERA_ANIMATION_SPEED = 0.025f;
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
	float _editorSpeed = 1.0f;

	// Integers
	int _selectedModelInversionDirection = 1;
	int _activeModelInversionDirection = 1;
	int _selectedBillboardInversionDirection = 1;
	int _activeBillboardInversionDirection = 1;
	int _selectedSpeakerSizeDirection = 1;
	int _activeSpeakerSizeDirection = 1;
	int _selectedLampSizeDirection = 1;
	int _activeLampSizeDirection = 1;
	int _selectedCameraSizeDirection = 1;
	int _activeCameraSizeDirection = 1;

	// Booleans
	bool _hasCustomSceneLighting = false;
	bool _hasCustomSceneGraphics = false;
	bool _hasCustomSceneSky = false;
	bool _hasCustomSceneTerrain = false;
	bool _hasCustomSceneWater = false;
	bool _dontResetSelectedModel = false;
	bool _dontResetSelectedBillboard = false;
	bool _dontResetSelectedSpeaker = false;
	bool _dontResetSelectedLamp = false;
	bool _dontResetSelectedCamera = false;
	bool _isPlacingPointlight = false;
	bool _isPlacingReflection = false;
	bool _isChoosingScene = false;
	bool _isDeletingScene = false;
	bool _isEditorLoaded = false;
};