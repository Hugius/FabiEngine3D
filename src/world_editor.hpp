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
#include "world_helper.hpp"

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
	void inject(shared_ptr<WorldHelper> worldHelper);
	void update();
	void clearLoadedWorld();

	const string & getLoadedWorldId() const;

	const bool loadWorldFromFile(const string & fileName);
	const bool saveWorldToFile() const;

private:
	void _load();
	void _unload();
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
	void _updateCaptorMenu();
	void _updateCaptorChoosingMenu();
	void _updateCaptorPlacing();
	void _updateCaptorEditing();
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
	void _updateModelHighlighting(const string & id, int & direction);
	void _updateQuad3dHighlighting(const string & id, int & direction);
	void _updateText3dHighlighting(const string & id, int & direction);
	void _updatePointlightHighlighting(const string & id, int & direction);
	void _updateSpotlightHighlighting(const string & id, int & direction);
	void _updateCaptorHighlighting(const string & id, int & direction);
	void _updateSoundHighlighting(const string & id, int & direction);
	void _deleteWorldFile(const string & id);
	void _selectModel(const string & id);
	void _selectQuad(const string & id);
	void _selectText(const string & id);
	void _selectPointlight(const string & id);
	void _selectSpotlight(const string & id);
	void _selectCaptor(const string & id);
	void _selectSound(const string & id);
	void _deselectModel(const string & id);
	void _deselectQuad(const string & id);
	void _deselectText(const string & id);
	void _deselectPointlight(const string & id);
	void _deselectSpotlight(const string & id);
	void _deselectCaptor(const string & id);
	void _deselectSound(const string & id);
	void _activateModel(const string & id);
	void _activateQuad(const string & id);
	void _activateText(const string & id);
	void _activatePointlight(const string & id);
	void _activateSpotlight(const string & id);
	void _activateCaptor(const string & id);
	void _activateSound(const string & id);
	void _deactivateModel();
	void _deactivateQuad();
	void _deactivateText();
	void _deactivatePointlight();
	void _deactivateSpotlight();
	void _deactivateCaptor();
	void _deactivateSound();
	void _handleInputBox(const string & screenId, const string & leftButtonId, const string & inputBoxId, const string & rightButtonId, float & value, float delta = 0.0f, float multiplier = 1.0f, float minimum = -FLT_MAX, float maximum = FLT_MAX);

	const vector<string> _getWorldIds() const;

	static inline const string TEMPLATE_POINTLIGHT_ID = "@@template_pointlight";
	static inline const string TEMPLATE_SPOTLIGHT_ID = "@@template_spotlight";
	static inline const string TEMPLATE_CAPTOR_ID = "@@template_captor";
	static inline const string TEMPLATE_SOUND_ID = "@@template_sound";
	static inline const string TEMPLATE_LAMP_ID = "@@template_lamp";
	static inline const string TEMPLATE_TORCH_ID = "@@template_torch";
	static inline const string TEMPLATE_CAMERA_ID = "@@template_camera";
	static inline const string TEMPLATE_SPEAKER_ID = "@@template_speaker";
	static inline const string LAMP_MODEL_PATH = "engine\\assets\\mesh\\lamp.obj";
	static inline const string TORCH_MODEL_PATH = "engine\\assets\\mesh\\torch.obj";
	static inline const string CAMERA_MODEL_PATH = "engine\\assets\\mesh\\camera.obj";
	static inline const string SPEAKER_MODEL_PATH = "engine\\assets\\mesh\\speaker.obj";

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
	static inline const fvec3 CAPTOR_TERRAIN_OFFSET = fvec3(0.0f, 0.5f, 0.0f);
	static inline const fvec3 SOUND_TERRAIN_OFFSET = fvec3(0.0f, 0.5f, 0.0f);

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
	static inline constexpr float SPOTLIGHT_INTENSITY_MULTIPLIER = 10.0f;
	static inline constexpr float CAPTOR_POSITION_DIVIDER = 100.0f;
	static inline constexpr float SOUND_POSITION_DIVIDER = 100.0f;
	static inline constexpr float SOUND_DISTANCE_DIVIDER = 100.0f;
	static inline constexpr float SOUND_VOLUME_MULTIPLIER = 100.0f;
	static inline constexpr float SOUND_VOLUME_SPEED = 0.01f;
	static inline constexpr float LAMP_HIGHLIGHT_SPEED = 0.025f;
	static inline constexpr float LAMP_SIZE_INCREASE = 1.25f;
	static inline constexpr float SPOTLIGHT_HIGHLIGHT_SPEED = 0.025f;
	static inline constexpr float SPOTLIGHT_SIZE_INCREASE = 1.25f;
	static inline constexpr float CAPTOR_HIGHLIGHT_SPEED = 0.025f;
	static inline constexpr float CAPTOR_SIZE_INCREASE = 1.25f;
	static inline constexpr float SOUND_HIGHLIGHT_SPEED = 0.025f;
	static inline constexpr float SOUND_SIZE_INCREASE = 1.25f;
	static inline constexpr float DEFAULT_POINTLIGHT_RADIUS = 5.0f;
	static inline constexpr float DEFAULT_POINTLIGHT_INTENSITY = 10.0f;
	static inline constexpr float DEFAULT_SPOTLIGHT_PITCH = -90.0f;
	static inline constexpr float DEFAULT_SPOTLIGHT_INTENSITY = 10.0f;
	static inline constexpr float DEFAULT_SPOTLIGHT_ANGLE = 25.0f;
	static inline constexpr float DEFAULT_SPOTLIGHT_DISTANCE = 10.0f;
	static inline constexpr float DEFAULT_SOUND_MAX_VOLUME = 1.0f;
	static inline constexpr float DEFAULT_SOUND_MAX_DISTANCE = 25.0f;

	unordered_map<string, string> _loadedModelIds = {};
	unordered_map<string, string> _loadedQuadIds = {};
	unordered_map<string, string> _loadedTextIds = {};
	unordered_map<string, string> _loadedSoundIds = {};

	vector<string> _loadedAabbIds = {};
	vector<string> _loadedPointlightIds = {};
	vector<string> _loadedSpotlightIds = {};
	vector<string> _loadedCaptorIds = {};

	shared_ptr<SkyEditor> _skyEditor = nullptr;
	shared_ptr<TerrainEditor> _terrainEditor = nullptr;
	shared_ptr<WaterEditor> _waterEditor = nullptr;
	shared_ptr<ModelEditor> _modelEditor = nullptr;
	shared_ptr<Quad3dEditor> _quad3dEditor = nullptr;
	shared_ptr<Text3dEditor> _text3dEditor = nullptr;
	shared_ptr<Animation2dEditor> _animation2dEditor = nullptr;
	shared_ptr<Animation3dEditor> _animation3dEditor = nullptr;
	shared_ptr<SoundEditor> _soundEditor = nullptr;
	shared_ptr<WorldHelper> _worldHelper = nullptr;

	string _loadedWorldId = "";
	string _currentWorldId = "";
	string _currentTemplateModelId = "";
	string _currentTemplateQuadId = "";
	string _currentTemplateTextId = "";
	string _currentTemplateSoundId = "";
	string _selectedModelId = "";
	string _selectedQuadId = "";
	string _selectedTextId = "";
	string _selectedPointlightId = "";
	string _selectedSpotlightId = "";
	string _selectedCaptorId = "";
	string _selectedSoundId = "";
	string _activeModelId = "";
	string _activeQuadId = "";
	string _activeTextId = "";
	string _activePointlightId = "";
	string _activeSpotlightId = "";
	string _activeCaptorId = "";
	string _activeSoundId = "";

	float _editorSpeed = 1.0f;

	int _idCounter = 0;
	int _selectedModelHighlightDirection = 1;
	int _activeModelHighlightDirection = 1;
	int _selectedQuad3dHighlightDirection = 1;
	int _activeQuad3dHighlightDirection = 1;
	int _selectedText3dHighlightDirection = 1;
	int _activeText3dHighlightDirection = 1;
	int _selectedPointlightHighlightDirection = 1;
	int _activePointlightHighlightDirection = 1;
	int _selectedSpotlightHighlightDirection = 1;
	int _activeSpotlightHighlightDirection = 1;
	int _selectedCaptorHighlightDirection = 1;
	int _activeCaptorHighlightDirection = 1;
	int _selectedSoundHighlightDirection = 1;
	int _activeSoundHighlightDirection = 1;

	bool _dontResetSelectedModel = false;
	bool _dontResetSelectedQuad3d = false;
	bool _dontResetSelectedText3d = false;
	bool _dontResetSelectedPointlight = false;
	bool _dontResetSelectedSpotlight = false;
	bool _dontResetSelectedCaptor = false;
	bool _dontResetSelectedSound = false;
	bool _isPlacingPointlight = false;
	bool _isPlacingSpotlight = false;
	bool _isPlacingCaptor = false;
	bool _isWireframeModeEnabled = false;
	bool _isAabbModeEnabled = false;
};