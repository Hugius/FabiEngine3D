#pragma once

#include "fabi_engine_3d.hpp"
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
	SceneEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, SkyEditor& skyEditor, TerrainEditor& terrainEditor, WaterEditor& waterEditor,
		ModelEditor& modelEditor, AnimationEditor& animationEditor, BillboardEditor& billboardEditor, AudioEditor& audioEditor);

	// Core
	void setCurrentProjectID(const string& projectID);
	void load();
	void unload();
	void update();

	// Editor scene
	bool loadEditorSceneFromFile(const string& filename);
	bool saveEditorSceneToFile();

	// Custom scene
	void createCustomScene(const string& sceneID);
	void addLightingToCustomScene();
	void addGraphicsToCustomScene();
	void addSkyToCustomScene();
	void addTerrainToCustomScene();
	void addWaterToCustomScene();
	void addModelToCustomScene(const string& modelID);
	void addBillboardToCustomScene(const string& billboardID);
	void addAabbToCustomScene(const string& aabbID);
	void addLightToCustomScene(const string& lightID);
	void addSoundToCustomScene(const string& soundID);
	bool loadCustomSceneFromFile(const string& filename);
	bool saveCustomSceneToFile();

	// Miscellaneous
	void copyPreviewModel(const string& newID, const string& previewID, Vec3 position);
	void copyPreviewBillboard(const string& newID, const string& previewID, Vec3 position);
	void copyPreviewAudio(const string& newID, const string& previewID, Vec3 position);
	void clearCurrentScene();
	bool isLoaded();
	bool isSceneExisting(const string& filename);
	const string& getLoadedSceneID();

private:
	// GUI
	void _loadGUI();
	void _unloadGUI();

	// Environment updates
	void _updateEnvironmentMenu();
	void _updateSkyMenu();
	void _updateTerrainMenu();
	void _updateWaterMenu();

	// Model updates
	void _updateModelMenu();
	void _updateModelPlacingMenu();
	void _updateModelChoosingMenu();
	void _updateModelPlacing();
	void _updateModelEditing();

	// Billboard updates
	void _updateBillboardMenu();
	void _updateBillboardPlacingMenu();
	void _updateBillboardChoosingMenu();
	void _updateBillboardPlacing();
	void _updateBillboardEditing();

	// Sound updates
	void _updateSoundMenu();
	void _updateSoundPlacingMenu();
	void _updateSoundChoosingMenu();
	void _updateSoundPlacing();
	void _updateSoundEditing();

	// Lighting updates
	void _updateLightingMenu();
	void _updateAmbientLightingMenu();
	void _updateDirectionalLightingMenu();
	void _updatePointLightingMenu();
	void _updateLightPlacing();
	void _updateLightEditing();

	// Settings updates
	void _updateSettingsMenu();
	void _updateGraphicsSettingsMenu();
	void _updateShadowGraphicsSettingsMenu();
	void _updateMotionBlurGraphicsSettingsMenu();
	void _updateDofGraphicsSettingsMenu();
	void _updateFogGraphicsSettingsMenu();
	void _updateLensFlareGraphicsSettingsMenu();
	void _updateSkyExposureGraphicsSettingsMenu();
	void _updateBloomGraphicsSettingsMenu();

	// Miscellaneous updates
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateCamera();
	void _updateMiscellaneous();

	// Creation
	bool _copyPreviewSky(const string& newID, const string& previewID);
	bool _copyPreviewTerrain(const string& newID, const string& previewID);
	bool _copyPreviewWater(const string& newID, const string& previewID);
	bool _copyPreviewModel(const string& newID, const string& previewID, Vec3 position, bool fromOutside = false);
	bool _copyPreviewBillboard(const string& newID, const string& previewID, Vec3 position, bool fromOutside = false);
	bool _copyPreviewAudio(const string& newID, const string& previewID, Vec3 position, bool fromOutside = false);

	// Miscellaneous
	vector<string> _loadSceneIDs();
	void _deleteSceneFile(const string& sceneID);
	void _updateModelBlinking(const string& modelID, int& direction);
	void _updateBillboardBlinking(const string& billboardID, int& direction);
	void _updateSpeakerAnimation(const string& modelID, int& direction);
	void _updateLampAnimation(const string& modelID, int& direction);
	void _selectModel(const string& modelID);
	void _activateModel(const string& modelID);
	void _selectBillboard(const string& billboardID);
	void _activateBillboard(const string& billboardID);
	void _selectSound(const string& soundID);
	void _activateSound(const string& soundID);
	void _handleValueChanging(const string& screenID, string buttonID, string writefieldID, float& value, float adder, float multiplier = 1.0f,
		float minimum = numeric_limits<float>::lowest(), float maximum = numeric_limits<float>::max());

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

	// Custom scene variables
	string _customSceneID = "";
	bool _hasCustomSceneLighting = false;
	bool _hasCustomSceneGraphics = false;
	bool _hasCustomSceneSky = false;
	bool _hasCustomSceneTerrain = false;
	bool _hasCustomSceneWater = false;
	vector<string> _customSceneModelIDs;
	vector<string> _customSceneBillboardIDs;
	vector<string> _customSceneAabbIDs;
	vector<string> _customSceneSoundIDs;
	vector<string> _customSceneLightIDs;

	// Environment variables
	string _loadedSkyID = "";
	string _loadedTerrainID = "";
	string _loadedWaterID = "";
	string _currentSkyID = "";
	string _currentTerrainID = "";
	string _currentWaterID = "";

	// Model variables
	map<string, string> _loadedModelIDs;
	map<string, string> _outsideLoadedModelIDs;
	map<string, Vec3> _initialModelPosition;
	map<string, Vec3> _initialModelRotation;
	map<string, Vec3> _initialModelSize;
	string _currentPreviewModelID = "";
	string _selectedModelID = "";
	string _activeModelID = "";
	int _selectedModelInversionDirection = 1;
	int _activeModelInversionDirection = 1;
	bool _dontResetSelectedModel = false;
	static inline const float MODEL_BLINKING_SPEED = 0.025f;
	static inline const float MODEL_SIZE_MULTIPLIER = 100.0f;

	// Billboard variables
	map<string, string> _loadedBillboardIDs;
	map<string, string> _outsideLoadedBillboardIDs;
	string _currentPreviewBillboardID = "";
	string _selectedBillboardID = "";
	string _activeBillboardID = "";
	int _selectedBillboardInversionDirection = 1;
	int _activeBillboardInversionDirection = 1;
	bool _dontResetSelectedBillboard = false;
	static inline const float BILLBOARD_BLINKING_SPEED = 0.025f;
	static inline const float BILLBOARD_SIZE_MULTIPLIER = 100.0f;

	// Sound variables
	map<string, string> _loadedSoundIDs;
	map<string, string> _outsideLoadedSoundIDs;
	string _currentPreviewSoundID = "";
	string _selectedSpeakerID = "";
	string _activeSpeakerID = "";
	static inline const string PREVIEW_SPEAKER_ID = "@@previewSpeaker";
	static inline const string SPEAKER_MODEL_PATH = "engine_assets\\meshes\\speaker.obj";
	static inline const Vec3 DEFAULT_SPEAKER_SIZE = Vec3(1.0f);
	static inline const Vec3 DEFAULT_SPEAKER_AABB_SIZE = Vec3(1.35f, 1.35f, 1.1f);
	static inline const float SPEAKER_SIZE_INCREASE = 1.25f;
	static inline const float DEFAULT_SOUND_MAX_VOLUME = 1.0f;
	static inline const float DEFAULT_SOUND_MAX_DISTANCE = 25.0f;
	static inline const float SPEAKER_ANIMATION_SPEED = 0.025f;
	static inline const float SOUND_VOLUME_CHANGING_SPEED = 0.01f;
	int _selectedSpeakerSizeDirection = 1;
	int _activeSpeakerSizeDirection = 1;
	bool _dontResetSelectedSpeaker = false;

	// Point light variables
	vector<string> _loadedLightIDs;
	bool _isPlacingLight = false;
	static inline const string PREVIEW_LAMP_ID = "@@previewLamp";
	static inline const string LAMP_MODEL_PATH = "engine_assets\\meshes\\lamp.obj";
	static inline const Vec3 DEFAULT_LAMP_SIZE = Vec3(1.0f);
	static inline const Vec3 DEFAULT_LAMP_AABB_SIZE = Vec3(0.7f, 1.2f, 0.7f);
	static inline const float DEFAULT_LIGHT_RADIUS = 5.0f;
	static inline const float DEFAULT_LIGHT_INTENSITY = 10.0f;
	static inline const float LAMP_SIZE_INCREASE = 1.25f;
	static inline const float LAMP_ANIMATION_SPEED = 0.025f;
	static inline const float LIGHT_INTENSITY_CHANGING_SPEED = 0.01f;
	static inline const float LIGHT_COLOR_CHANGING_SPEED = 0.005f;
	int _selectedLampSizeDirection = 1;
	int _activeLampSizeDirection = 1;
	string _selectedLampID = "";
	string _activeLampID = "";

	// Miscellaneous
	vector<string> _loadedAabbIDs;
	string _loadedSceneID = "";
	string _currentProjectID = "";
	string _currentSceneID = "";
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
	float _editorSpeed = 1.0f;
	bool _isEditorLoaded = false;
	bool _isChoosingScene = false;
	bool _isDeletingScene = false;
};