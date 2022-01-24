#pragma once

#include "base_editor.hpp"
#include "sky_editor.hpp"
#include "terrain_editor.hpp"
#include "water_editor.hpp"
#include "model_editor.hpp"
#include "quad3d_editor.hpp"
#include "text3d_editor.hpp"
#include "animation3d_editor.hpp"
#include "animation2d_editor.hpp"
#include "sound_editor.hpp"
#include "transformation_type.hpp"

#include <map>
#include <limits>

using std::numeric_limits;

class WorldEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void inject(shared_ptr<SkyEditor> skyEditor);
	void inject(shared_ptr<TerrainEditor> terrainEditor);
	void inject(shared_ptr<WaterEditor> waterEditor);
	void inject(shared_ptr<ModelEditor> modelEditor);
	void inject(shared_ptr<Quad3dEditor> quad3dEditor);
	void inject(shared_ptr<Text3dEditor> text3dEditor);
	void inject(shared_ptr<Animation2dEditor> animation2dEditor);
	void inject(shared_ptr<Animation3dEditor> animation3dEditor);
	void inject(shared_ptr<SoundEditor> soundEditor);

	void setCurrentProjectID(const string& id);
	void load();
	void unload();
	void update();
	void createCustomWorld(const string& id);
	void addLightingToCustomWorld();
	void addGraphicsToCustomWorld();
	void addSkyToCustomWorld();
	void addTerrainToCustomWorld();
	void addWaterToCustomWorld();
	void addModelToCustomWorld(const string& id);
	void addQuad3dToCustomWorld(const string& id);
	void addText3dToCustomWorld(const string& id);
	void addAabbToCustomWorld(const string& id);
	void addSoundToCustomWorld(const string& id);
	void addPointlightToCustomWorld(const string& id);
	void addSpotlightToCustomWorld(const string& id);
	void addReflectionToCustomWorld(const string& id);
	void copyTemplateModel(const string& newID, const string& templateID, const fvec3& position);
	void copyTemplateQuad3d(const string& newID, const string& templateID, const fvec3& position);
	void copyTemplateText3d(const string& newID, const string& templateID, const fvec3& position);
	void copyTemplateSound(const string& newID, const string& templateID, const fvec3& position);
	void unloadEditorWorld();
	void unloadCustomWorld();

	const string& getLoadedWorldID() const;

	const bool isLoaded() const;
	const bool loadEditorWorldFromFile(const string& fileName);
	const bool saveEditorWorldToFile();
	const bool loadCustomWorldFromFile(const string& fileName);
	const bool saveCustomWorldToFile();

private:
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateSkyMenu();
	void _updateTerrainMenu();
	void _updateWaterMenu();
	void _updateModelMenu();
	void _updateModelPlacingMenu();
	void _updateModelChoosingMenu();
	void _updateModelPlacing();
	void _updateModelEditing();
	void _updateQuad3dMenu();
	void _updateQuad3dPlacingMenu();
	void _updateQuad3dChoosingMenu();
	void _updateQuad3dPlacing();
	void _updateQuad3dEditing();
	void _updateText3dMenu();
	void _updateText3dPlacingMenu();
	void _updateText3dChoosingMenu();
	void _updateText3dPlacing();
	void _updateText3dEditing();
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
	void _updateSoundMenu();
	void _updateSoundPlacingMenu();
	void _updateSoundChoosingMenu();
	void _updateSoundPlacing();
	void _updateSoundEditing();
	void _updateSettingsMenu();
	void _updateLightingSettingsMenu();
	void _updateAmbientLightingSettingsMenu();
	void _updateDirectionalLightingSettingsMenu();
	void _updateGraphicsSettingsMenu();
	void _updateShadowsGraphicsSettingsMenu();
	void _updateReflectionsGraphicsSettingsMenu();
	void _updateRefractionsGraphicsSettingsMenu();
	void _updateDofGraphicsSettingsMenu();
	void _updateFogGraphicsSettingsMenu();
	void _updateLensFlareGraphicsSettingsMenu();
	void _updateSkyExposureGraphicsSettingsMenu();
	void _updateBloomGraphicsSettingsMenu();
	void _updateWorldCreating();
	void _updateWorldChoosing();
	void _updateWorldDeleting();
	void _updateCamera();
	void _updateMiscellaneous();
	void _updateModelHighlighting(const string& id, int& direction);
	void _updateQuad3dHighlighting(const string& id, int& direction);
	void _updateText3dHighlighting(const string& id, int& direction);
	void _updateLampHighlighting(const string& id, int& direction);
	void _updateTorchHighlighting(const string& id, int& direction);
	void _updateCameraHighlighting(const string& id, int& direction);
	void _updateSpeakerHighlighting(const string& id, int& direction);
	void _deleteWorldFile(const string& id);
	void _selectModel(const string& id);
	void _selectQuad3d(const string& id);
	void _selectText3d(const string& id);
	void _selectPointlight(const string& id);
	void _selectSpotlight(const string& id);
	void _selectReflection(const string& id);
	void _selectSound(const string& id);
	void _unselectModel(const string& id);
	void _unselectQuad3d(const string& id);
	void _unselectText3d(const string& id);
	void _unselectPointlight(const string& id);
	void _unselectSpotlight(const string& id);
	void _unselectReflection(const string& id);
	void _unselectSound(const string& id);
	void _activateModel(const string& id);
	void _activateQuad3d(const string& id);
	void _activateText3d(const string& id);
	void _activatePointlight(const string& id);
	void _activateSpotlight(const string& id);
	void _activateReflection(const string& id);
	void _activateSound(const string& id);
	void _deactivateModel();
	void _deactivateQuad3d();
	void _deactivateText3d();
	void _deactivatePointlight();
	void _deactivateSpotlight();
	void _deactivateReflection();
	void _deactivateSound();
	void _handleValueChanging(const string& screenID, const string& buttonID, const string& writeFieldID, float& value, float adder, float multiplier = 1.0f, float minimum = numeric_limits<float>::lowest(), float maximum = numeric_limits<float>::max());

	const vector<string> _getWorldIDs() const;

	const bool _copyTemplateSky(const string& newID, const string& templateID);
	const bool _copyTemplateTerrain(const string& newID, const string& templateID);
	const bool _copyTemplateWater(const string& newID, const string& templateID);
	const bool _copyTemplateModel(const string& newID, const string& templateID, const fvec3& position, bool isFromOutside);
	const bool _copyTemplateQuad3d(const string& newID, const string& templateID, const fvec3& position, bool isFromOutside);
	const bool _copyTemplateText3d(const string& newID, const string& templateID, const fvec3& position, bool isFromOutside);
	const bool _copyTemplateSound(const string& newID, const string& templateID, const fvec3& position, bool isFromOutside);

	static inline const string TEMPLATE_LAMP_ID = "@@template_lamp";
	static inline const string TEMPLATE_TORCH_ID = "@@template_torch";
	static inline const string TEMPLATE_CAMERA_ID = "@@template_camera";
	static inline const string TEMPLATE_SPEAKER_ID = "@@template_speaker";
	static inline const string LAMP_MODEL_PATH = "engine\\assets\\mesh\\lamp.obj";
	static inline const string TORCH_MODEL_PATH = "engine\\assets\\mesh\\torch.obj";
	static inline const string CAMERA_MODEL_PATH = "engine\\assets\\mesh\\camera.obj";
	static inline const string SPEAKER_MODEL_PATH = "engine\\assets\\mesh\\speaker.obj";
	map<string, string> _loadedModelIDs;
	map<string, string> _outsideLoadedModelIDs;
	map<string, string> _loadedQuadIDs;
	map<string, string> _outsideLoadedQuadIDs;
	map<string, string> _loadedTextIDs;
	map<string, string> _outsideLoadedTextIDs;
	map<string, string> _loadedSoundIDs;
	map<string, string> _outsideLoadedSoundIDs;
	map<string, fvec3> _initialModelPosition;
	map<string, fvec3> _initialModelRotation;
	map<string, fvec3> _initialModelSize;
	vector<string> _customWorldModelIDs;
	vector<string> _customWorldQuadIDs;
	vector<string> _customWorldTextIDs;
	vector<string> _customWorldAabbIDs;
	vector<string> _customWorldPointlightIDs;
	vector<string> _customWorldSpotlightIDs;
	vector<string> _customWorldReflectionIDs;
	vector<string> _customWorldSoundIDs;
	vector<string> _loadedAabbIDs;
	vector<string> _loadedPointlightIDs;
	vector<string> _loadedSpotlightIDs;
	vector<string> _loadedReflectionIDs;
	string _customWorldID = "";
	string _loadedSkyID = "";
	string _loadedTerrainID = "";
	string _loadedWaterID = "";
	string _currentSkyID = "";
	string _currentTerrainID = "";
	string _currentWaterID = "";
	string _currentTemplateModelID = "";
	string _selectedModelID = "";
	string _activeModelID = "";
	string _currentTemplateQuadID = "";
	string _selectedQuadID = "";
	string _activeQuadID = "";
	string _currentTemplateTextID = "";
	string _selectedTextID = "";
	string _activeTextID = "";
	string _selectedLampID = "";
	string _activeLampID = "";
	string _selectedTorchID = "";
	string _activeTorchID = "";
	string _selectedCameraID = "";
	string _activeCameraID = "";
	string _currentTemplateSoundID = "";
	string _selectedSpeakerID = "";
	string _activeSpeakerID = "";
	string _loadedWorldID = "";
	string _currentProjectID = "";
	string _currentWorldID = "";

	static inline const fvec3 DEFAULT_LAMP_SIZE = fvec3(1.0f, 1.0f, 1.0f);
	static inline const fvec3 DEFAULT_LAMP_AABB_SIZE = fvec3(0.6f, 1.0f, 0.6f);
	static inline const fvec3 DEFAULT_TORCH_ROTATION = fvec3(0.0f, 0.0f, -90.0f);
	static inline const fvec3 DEFAULT_TORCH_SIZE = fvec3(1.0f, 1.0f, 1.0f);
	static inline const fvec3 DEFAULT_TORCH_AABB_SIZE = fvec3(1.0f, 0.25f, 0.3f);
	static inline const fvec3 DEFAULT_CAMERA_SIZE = fvec3(1.0f, 1.0f, 1.0f);
	static inline const fvec3 DEFAULT_CAMERA_AABB_SIZE = fvec3(1.0f, 1.0f, 1.0f);
	static inline const fvec3 DEFAULT_SPEAKER_SIZE = fvec3(1.0f, 1.0f, 1.0f);
	static inline const fvec3 DEFAULT_SPEAKER_AABB_SIZE = fvec3(1.05f, 1.05f, 0.9f);
	static inline const fvec3 MODEL_TERRAIN_OFFSET = fvec3(0.0f, 0.0f, 0.0f);
	static inline const fvec3 QUAD3D_TERRAIN_OFFSET = fvec3(0.0f, 0.0f, 0.0f);
	static inline const fvec3 TEXT3D_TERRAIN_OFFSET = fvec3(0.0f, 0.0f, 0.0f);
	static inline const fvec3 POINTLIGHT_TERRAIN_OFFSET = fvec3(0.0f, 1.5f, 0.0f);
	static inline const fvec3 SPOTLIGHT_TERRAIN_OFFSET = fvec3(0.0f, 1.5f, 0.0f);
	static inline const fvec3 REFLECTION_TERRAIN_OFFSET = fvec3(0.0f, 0.5f, 0.0f);
	static inline const fvec3 SOUND_TERRAIN_OFFSET = fvec3(0.0f, 0.5f, 0.0f);
	static inline const fvec3 LAMP_OFFSET = fvec3(0.0f, 0.5f, 0.0f);
	static inline const fvec3 CAMERA_OFFSET = fvec3(0.0f, 0.5f, 0.0f);
	static inline const fvec3 SPEAKER_OFFSET = fvec3(0.0f, 0.5f, 0.0f);

	static inline constexpr float MODEL_POSITION_DIVIDER = 100.0f;
	static inline constexpr float MODEL_ROTATION_SPEED = 0.5f;
	static inline constexpr float MODEL_SIZE_DIVIDER = 100.0f;
	static inline constexpr float MODEL_SIZE_MULTIPLIER = 100.0f;
	static inline constexpr float MODEL_HIGHLIGHT_SPEED = 0.025f;
	static inline constexpr float QUAD3D_POSITION_DIVIDER = 100.0f;
	static inline constexpr float QUAD3D_ROTATION_SPEED = 0.5f;
	static inline constexpr float QUAD3D_SIZE_DIVIDER = 100.0f;
	static inline constexpr float QUAD3D_SIZE_MULTIPLIER = 100.0f;
	static inline constexpr float QUAD3D_HIGHLIGHT_SPEED = 0.025f;
	static inline constexpr float TEXT3D_POSITION_DIVIDER = 100.0f;
	static inline constexpr float TEXT3D_ROTATION_SPEED = 0.5f;
	static inline constexpr float TEXT3D_SIZE_DIVIDER = 100.0f;
	static inline constexpr float TEXT3D_SIZE_MULTIPLIER = 100.0f;
	static inline constexpr float TEXT3D_HIGHLIGHT_SPEED = 0.025f;
	static inline constexpr float POINTLIGHT_POSITION_DIVIDER = 100.0f;
	static inline constexpr float POINTLIGHT_RADIUS_DIVIDER = 100.0f;
	static inline constexpr float POINTLIGHT_COLOR_SPEED = 0.005f;
	static inline constexpr float POINTLIGHT_INTENSITY_SPEED = 0.1f;
	static inline constexpr float SPOTLIGHT_POSITION_DIVIDER = 100.0f;
	static inline constexpr float SPOTLIGHT_COLOR_SPEED = 0.005f;
	static inline constexpr float SPOTLIGHT_YAW_SPEED = 0.5f;
	static inline constexpr float SPOTLIGHT_PITCH_SPEED = 0.5f;
	static inline constexpr float SPOTLIGHT_INTENSITY_SPEED = 0.1f;
	static inline constexpr float SPOTLIGHT_ANGLE_SPEED = 0.1f;
	static inline constexpr float SPOTLIGHT_DISTANCE_DIVIDER = 100.0f;
	static inline constexpr float REFLECTION_POSITION_DIVIDER = 100.0f;
	static inline constexpr float SOUND_POSITION_DIVIDER = 100.0f;
	static inline constexpr float SOUND_DISTANCE_DIVIDER = 100.0f;
	static inline constexpr float SOUND_VOLUME_MULTIPLIER = 100.0f;
	static inline constexpr float SOUND_VOLUME_SPEED = 0.01f;
	static inline constexpr float LAMP_HIGHLIGHT_SPEED = 0.025f;
	static inline constexpr float LAMP_SIZE_INCREASE = 1.25f;
	static inline constexpr float TORCH_HIGHLIGHT_SPEED = 0.025f;
	static inline constexpr float TORCH_SIZE_INCREASE = 1.25f;
	static inline constexpr float CAMERA_HIGHLIGHT_SPEED = 0.025f;
	static inline constexpr float CAMERA_SIZE_INCREASE = 1.25f;
	static inline constexpr float SPEAKER_HIGHLIGHT_SPEED = 0.025f;
	static inline constexpr float SPEAKER_SIZE_INCREASE = 1.25f;
	static inline constexpr float DEFAULT_POINTLIGHT_RADIUS = 5.0f;
	static inline constexpr float DEFAULT_POINTLIGHT_INTENSITY = 10.0f;
	static inline constexpr float DEFAULT_SPOTLIGHT_PITCH = -90.0f;
	static inline constexpr float DEFAULT_SPOTLIGHT_INTENSITY = 10.0f;
	static inline constexpr float DEFAULT_SPOTLIGHT_ANGLE = 25.0f;
	static inline constexpr float DEFAULT_SPOTLIGHT_DISTANCE = 10.0f;
	static inline constexpr float DEFAULT_SOUND_MAX_VOLUME = 1.0f;
	static inline constexpr float DEFAULT_SOUND_MAX_DISTANCE = 25.0f;
	static inline constexpr float CW = 0.115f;
	static inline constexpr float CH = 0.0875f;
	float _editorSpeed = 1.0f;

	int _selectedModelHighlightDirection = 1;
	int _activeModelHighlightDirection = 1;
	int _selectedQuad3dHighlightDirection = 1;
	int _activeQuad3dHighlightDirection = 1;
	int _selectedText3dHighlightDirection = 1;
	int _activeText3dHighlightDirection = 1;
	int _selectedLampHighlightDirection = 1;
	int _activeLampHighlightDirection = 1;
	int _selectedTorchHighlightDirection = 1;
	int _activeTorchHighlightDirection = 1;
	int _selectedCameraHighlightDirection = 1;
	int _activeCameraHighlightDirection = 1;
	int _selectedSpeakerHighlightDirection = 1;
	int _activeSpeakerHighlightDirection = 1;

	bool _hasCustomWorldLighting = false;
	bool _hasCustomWorldGraphics = false;
	bool _hasCustomWorldSky = false;
	bool _hasCustomWorldTerrain = false;
	bool _hasCustomWorldWater = false;
	bool _dontResetSelectedModel = false;
	bool _dontResetSelectedQuad3d = false;
	bool _dontResetSelectedText3d = false;
	bool _dontResetSelectedLamp = false;
	bool _dontResetSelectedTorch = false;
	bool _dontResetSelectedCamera = false;
	bool _dontResetSelectedSpeaker = false;
	bool _isPlacingPointlight = false;
	bool _isPlacingSpotlight = false;
	bool _isPlacingReflection = false;
	bool _isCreatingWorld = false;
	bool _isChoosingWorld = false;
	bool _isDeletingWorld = false;
	bool _isEditorLoaded = false;

	shared_ptr<SkyEditor> _skyEditor = nullptr;
	shared_ptr<TerrainEditor> _terrainEditor = nullptr;
	shared_ptr<WaterEditor> _waterEditor = nullptr;
	shared_ptr<ModelEditor> _modelEditor = nullptr;
	shared_ptr<Quad3dEditor> _quad3dEditor = nullptr;
	shared_ptr<Text3dEditor> _text3dEditor = nullptr;
	shared_ptr<Animation2dEditor> _animation2dEditor = nullptr;
	shared_ptr<Animation3dEditor> _animation3dEditor = nullptr;
	shared_ptr<SoundEditor> _soundEditor = nullptr;
};