#pragma once

#include "fe3d.hpp"
#include "gui_manager.hpp"
#include "sky_editor.hpp"
#include "terrain_editor.hpp"
#include "water_editor.hpp"
#include "model_editor.hpp"
#include "animation3d_editor.hpp"
#include "billboard_editor.hpp"
#include "sound_editor.hpp"
#include "transformation_type.hpp"

#include <map>
#include <limits>

using std::numeric_limits;

class WorldEditor final
{
public:
	WorldEditor(FabiEngine3D& fe3d,
				GuiManager& gui,
				SkyEditor& skyEditor,
				TerrainEditor& terrainEditor,
				WaterEditor& waterEditor,
				ModelEditor& modelEditor,
				BillboardEditor& billboardEditor,
				Animation3dEditor& animation3dEditor,
				SoundEditor& soundEditor);

	// VOID
	void setCurrentProjectID(const string& ID);
	void load();
	void unload();
	void update();
	void createCustomWorld(const string& ID);
	void addLightingToCustomWorld();
	void addGraphicsToCustomWorld();
	void addSkyToCustomWorld();
	void addTerrainToCustomWorld();
	void addWaterToCustomWorld();
	void addModelToCustomWorld(const string& ID);
	void addBillboardToCustomWorld(const string& ID);
	void addAabbToCustomWorld(const string& ID);
	void addSoundToCustomWorld(const string& ID);
	void addPointlightToCustomWorld(const string& ID);
	void addSpotlightToCustomWorld(const string& ID);
	void addReflectionToCustomWorld(const string& ID);
	void copyTemplateModel(const string& newID, const string& templateID, fvec3 position);
	void copyTemplateBillboard(const string& newID, const string& templateID, fvec3 position);
	void copyTemplateSound(const string& newID, const string& templateID, fvec3 position);
	void clearCurrentWorld();

	// STRING
	const string& getLoadedWorldID() const;

	// BOOL
	const bool isLoaded() const;
	const bool isWorldExisting(const string& fileName) const;
	const bool loadEditorWorldFromFile(const string& fileName);
	const bool saveEditorWorldToFile();
	const bool loadCustomWorldFromFile(const string& fileName);
	const bool saveCustomWorldToFile();

private:
	// VOID
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
	void _updateShadowsGraphicsSettingsMenu();
	void _updateReflectionsGraphicsSettingsMenu();
	void _updateRefractionsGraphicsSettingsMenu();
	void _updateDofGraphicsSettingsMenu();
	void _updateFogGraphicsSettingsMenu();
	void _updateLensFlareGraphicsSettingsMenu();
	void _updateSkyExposureGraphicsSettingsMenu();
	void _updateBloomGraphicsSettingsMenu();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateCamera();
	void _updateMiscellaneous();
	void _deleteWorldFile(const string& ID);
	void _updateModelHighlighting(const string& ID, int& direction);
	void _updateBillboardHighlighting(const string& ID, int& direction);
	void _updateSpeakerHighlighting(const string& ID, int& direction);
	void _updateLampHighlighting(const string& ID, int& direction);
	void _updateTorchHighlighting(const string& ID, int& direction);
	void _updateCameraHighlighting(const string& ID, int& direction);
	void _selectModel(const string& ID);
	void _selectBillboard(const string& ID);
	void _selectSound(const string& ID);
	void _selectPointlight(const string& ID);
	void _selectSpotlight(const string& ID);
	void _selectReflection(const string& ID);
	void _unselectModel(const string& ID);
	void _unselectBillboard(const string& ID);
	void _unselectSound(const string& ID);
	void _unselectPointlight(const string& ID);
	void _unselectSpotlight(const string& ID);
	void _unselectReflection(const string& ID);
	void _activateModel(const string& ID);
	void _activateBillboard(const string& ID);
	void _activateSound(const string& ID);
	void _activatePointlight(const string& ID);
	void _activateSpotlight(const string& ID);
	void _activateReflection(const string& ID);
	void _deactivateModel();
	void _deactivateBillboard();
	void _deactivateSound();
	void _deactivatePointlight();
	void _deactivateSpotlight();
	void _deactivateReflection();
	void _handleValueChanging(const string& screenID, string buttonID, string writeFieldID, float& value, float adder, float multiplier = 1.0f, float minimum = numeric_limits<float>::lowest(), float maximum = numeric_limits<float>::max());

	// STRING
	const vector<string> _getWorldIDs() const;

	// BOOL
	const bool _copyTemplateSky(const string& newID, const string& templateID);
	const bool _copyTemplateTerrain(const string& newID, const string& templateID);
	const bool _copyTemplateWater(const string& newID, const string& templateID);
	const bool _copyTemplateModel(const string& newID, const string& templateID, fvec3 position, bool isFromOutside);
	const bool _copyTemplateBillboard(const string& newID, const string& templateID, fvec3 position, bool isFromOutside);
	const bool _copyTemplateSound(const string& newID, const string& templateID, fvec3 position, bool isFromOutside);

	// STRING
	static inline const string TEMPLATE_SPEAKER_ID = "@@template_speaker";
	static inline const string TEMPLATE_LAMP_ID = "@@template_lamp";
	static inline const string TEMPLATE_TORCH_ID = "@@template_torch";
	static inline const string TEMPLATE_CAMERA_ID = "@@template_camera";
	static inline const string SPEAKER_MODEL_PATH = "engine\\assets\\mesh\\speaker.obj";
	static inline const string LAMP_MODEL_PATH = "engine\\assets\\mesh\\lamp.obj";
	static inline const string TORCH_MODEL_PATH = "engine\\assets\\mesh\\torch.obj";
	static inline const string CAMERA_MODEL_PATH = "engine\\assets\\mesh\\camera.obj";
	map<string, string> _loadedModelIDs;
	map<string, string> _outsideLoadedModelIDs;
	map<string, string> _loadedBillboardIDs;
	map<string, string> _outsideLoadedBillboardIDs;
	map<string, string> _loadedSoundIDs;
	map<string, string> _outsideLoadedSoundIDs;
	map<string, fvec3> _initialModelPosition;
	map<string, fvec3> _initialModelRotation;
	map<string, fvec3> _initialModelSize;
	vector<string> _customWorldModelIDs;
	vector<string> _customWorldBillboardIDs;
	vector<string> _customWorldAabbIDs;
	vector<string> _customWorldSoundIDs;
	vector<string> _customWorldPointlightIDs;
	vector<string> _customWorldSpotlightIDs;
	vector<string> _customWorldReflectionIDs;
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
	string _currentTemplateBillboardID = "";
	string _selectedBillboardID = "";
	string _activeBillboardID = "";
	string _currentTemplateSoundID = "";
	string _selectedSpeakerID = "";
	string _activeSpeakerID = "";
	string _selectedLampID = "";
	string _activeLampID = "";
	string _selectedTorchID = "";
	string _activeTorchID = "";
	string _selectedCameraID = "";
	string _activeCameraID = "";
	string _loadedWorldID = "";
	string _currentProjectID = "";
	string _currentWorldID = "";

	// FVEC3
	static inline const fvec3 DEFAULT_SPEAKER_SIZE = fvec3(1.0f, 1.0f, 1.0f);
	static inline const fvec3 DEFAULT_SPEAKER_AABB_SIZE = fvec3(1.05f, 1.05f, 0.9f);
	static inline const fvec3 DEFAULT_LAMP_SIZE = fvec3(1.0f, 1.0f, 1.0f);
	static inline const fvec3 DEFAULT_LAMP_AABB_SIZE = fvec3(0.6f, 1.0f, 0.6f);
	static inline const fvec3 DEFAULT_TORCH_SIZE = fvec3(1.0f, 1.0f, 1.0f);
	static inline const fvec3 DEFAULT_TORCH_AABB_SIZE = fvec3(1.0f, 0.25f, 0.3f);
	static inline const fvec3 DEFAULT_CAMERA_SIZE = fvec3(1.0f, 1.0f, 1.0f);
	static inline const fvec3 DEFAULT_CAMERA_AABB_SIZE = fvec3(1.0f, 1.0f, 1.0f);
	static inline const fvec3 MODEL_TERRAIN_OFFSET = fvec3(0.0f, 0.0f, 0.0f);
	static inline const fvec3 BILLBOARD_TERRAIN_OFFSET = fvec3(0.0f, 0.0f, 0.0f);
	static inline const fvec3 SOUND_TERRAIN_OFFSET = fvec3(0.0f, 0.5f, 0.0f);
	static inline const fvec3 POINTLIGHT_TERRAIN_OFFSET = fvec3(0.0f, 1.5f, 0.0f);
	static inline const fvec3 SPOTLIGHT_TERRAIN_OFFSET = fvec3(0.0f, 1.5f, 0.0f);
	static inline const fvec3 REFLECTION_TERRAIN_OFFSET = fvec3(0.0f, 0.5f, 0.0f);
	static inline const fvec3 SPEAKER_OFFSET = fvec3(0.0f, 0.5f, 0.0f);
	static inline const fvec3 LAMP_OFFSET = fvec3(0.0f, 0.5f, 0.0f);
	static inline const fvec3 TORCH_OFFSET = fvec3(0.0f, 0.5f, 0.0f);
	static inline const fvec3 CAMERA_OFFSET = fvec3(0.0f, 0.5f, 0.0f);

	// FLOAT
	static inline const float DEFAULT_SOUND_MAX_VOLUME = 1.0f;
	static inline const float DEFAULT_SOUND_MAX_DISTANCE = 25.0f;
	static inline const float DEFAULT_POINTLIGHT_RADIUS = 5.0f;
	static inline const float DEFAULT_POINTLIGHT_INTENSITY = 10.0f;
	static inline const float DEFAULT_SPOTLIGHT_PITCH = -90.0f;
	static inline const float DEFAULT_SPOTLIGHT_INTENSITY = 10.0f;
	static inline const float DEFAULT_SPOTLIGHT_ANGLE = 25.0f;
	static inline const float DEFAULT_SPOTLIGHT_DISTANCE = 10.0f;
	static inline const float MODEL_SIZE_MULTIPLIER = 100.0f;
	static inline const float MODEL_HIGHLIGHT_SPEED = 0.025f;
	static inline const float BILLBOARD_SIZE_MULTIPLIER = 100.0f;
	static inline const float BILLBOARD_HIGHLIGHT_SPEED = 0.025f;
	static inline const float SOUND_VOLUME_CHANGING_SPEED = 0.01f;
	static inline const float POINTLIGHT_COLOR_CHANGING_SPEED = 0.005f;
	static inline const float POINTLIGHT_INTENSITY_CHANGING_SPEED = 0.1f;
	static inline const float SPOTLIGHT_COLOR_CHANGING_SPEED = 0.005f;
	static inline const float SPOTLIGHT_YAW_CHANGING_SPEED = 0.5f;
	static inline const float SPOTLIGHT_PITCH_CHANGING_SPEED = 0.5f;
	static inline const float SPOTLIGHT_INTENSITY_CHANGING_SPEED = 0.1f;
	static inline const float SPOTLIGHT_ANGLE_CHANGING_SPEED = 0.1f;
	static inline const float SPEAKER_HIGHLIGHT_SPEED = 0.025f;
	static inline const float SPEAKER_SIZE_INCREASE = 1.25f;
	static inline const float LAMP_HIGHLIGHT_SPEED = 0.025f;
	static inline const float LAMP_SIZE_INCREASE = 1.25f;
	static inline const float TORCH_HIGHLIGHT_SPEED = 0.025f;
	static inline const float TORCH_SIZE_INCREASE = 1.25f;
	static inline const float CAMERA_HIGHLIGHT_SPEED = 0.025f;
	static inline const float CAMERA_SIZE_INCREASE = 1.25f;
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
	float _editorSpeed = 1.0f;

	// INT
	int _selectedModelHighlightDirection = 1;
	int _activeModelHighlightDirection = 1;
	int _selectedBillboardHighlightDirection = 1;
	int _activeBillboardHighlightDirection = 1;
	int _selectedSpeakerHighlightDirection = 1;
	int _activeSpeakerHighlightDirection = 1;
	int _selectedLampHighlightDirection = 1;
	int _activeLampHighlightDirection = 1;
	int _selectedTorchHighlightDirection = 1;
	int _activeTorchHighlightDirection = 1;
	int _selectedCameraHighlightDirection = 1;
	int _activeCameraHighlightDirection = 1;

	// BOOL
	bool _hasCustomWorldLighting = false;
	bool _hasCustomWorldGraphics = false;
	bool _hasCustomWorldSky = false;
	bool _hasCustomWorldTerrain = false;
	bool _hasCustomWorldWater = false;
	bool _dontResetSelectedModel = false;
	bool _dontResetSelectedBillboard = false;
	bool _dontResetSelectedSpeaker = false;
	bool _dontResetSelectedLamp = false;
	bool _dontResetSelectedTorch = false;
	bool _dontResetSelectedCamera = false;
	bool _isPlacingPointlight = false;
	bool _isPlacingSpotlight = false;
	bool _isPlacingReflection = false;
	bool _isChoosingWorld = false;
	bool _isDeletingWorld = false;
	bool _isEditorLoaded = false;

	// MISCELLANEOUS
	FabiEngine3D& _fe3d;
	GuiManager& _gui;
	SkyEditor& _skyEditor;
	TerrainEditor& _terrainEditor;
	WaterEditor& _waterEditor;
	ModelEditor& _modelEditor;
	BillboardEditor& _billboardEditor;
	Animation3dEditor& _animation3dEditor;
	SoundEditor& _soundEditor;
};