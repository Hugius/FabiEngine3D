#include "world_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

WorldEditor::WorldEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, SkyEditor& skyEditor, TerrainEditor& terrainEditor, WaterEditor& waterEditor, ModelEditor& modelEditor, AnimationEditor& animationEditor, BillboardEditor& billboardEditor, AudioEditor& audioEditor)
	:
	_fe3d(fe3d),
	_gui(gui),
	_skyEditor(skyEditor),
	_terrainEditor(terrainEditor),
	_waterEditor(waterEditor),
	_modelEditor(modelEditor),
	_animationEditor(animationEditor),
	_billboardEditor(billboardEditor),
	_audioEditor(audioEditor)
{

}

void WorldEditor::load()
{
	// GUI
	_loadGUI();

	// Camera
	_fe3d.camera_reset();

	// Default graphics
	_fe3d.gfx_setPlanarReflectionHeight(0.0f);

	// Directional light source
	const string texturePath = "engine\\assets\\textures\\light_source.png";
	_fe3d.billboard_create("@@directionalLightSource");
	_fe3d.billboard_setSize("@@directionalLightSource", fvec2(0.0f));
	_fe3d.billboard_setDiffuseMap("@@directionalLightSource", texturePath);
	_fe3d.billboard_setDepthMapIncluded("@@directionalLightSource", false);
	_fe3d.billboard_setShadowed("@@directionalLightSource", false);
	_fe3d.billboard_setReflected("@@directionalLightSource", true);
	_fe3d.billboard_setBright("@@directionalLightSource", true);
	_fe3d.billboard_setCameraFacingX("@@directionalLightSource", true);
	_fe3d.billboard_setCameraFacingY("@@directionalLightSource", true);
	_fe3d.billboard_setVisible("@@directionalLightSource", false);

	// Load preview skies
	_skyEditor.loadSkyEntitiesFromFile();

	// Load preview terrains
	_terrainEditor.loadTerrainEntitiesFromFile();

	// Load preview waters
	_waterEditor.loadWaterEntitiesFromFile();

	// Load preview models
	_modelEditor.loadModelEntitiesFromFile();
	for(const auto& modelID : _modelEditor.getLoadedModelIDs())
	{
		// Check if there is a model entity present
		if(_fe3d.model_isExisting(modelID))
		{
			_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuModelPlace")->getScrollingList("modelList")->
				createButton(modelID, modelID.substr(1));
		}
	}

	// Load preview animations
	_animationEditor.loadAnimationsFromFile(false);

	// Load preview billboards
	_billboardEditor.loadBillboardEntitiesFromFile();
	for(const auto& billboardID : _billboardEditor.getLoadedBillboardIDs())
	{
		// Check if there is a billboard entity present
		if(_fe3d.billboard_isExisting(billboardID))
		{
			_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuBillboardPlace")->getScrollingList("billboardList")->
				createButton(billboardID, billboardID.substr(1));
		}
	}

	// Load preview sounds
	_audioEditor.loadAudioEntitiesFromFile();
	_fe3d.model_create(PREVIEW_SPEAKER_ID, SPEAKER_MODEL_PATH);
	_fe3d.model_setBaseSize(PREVIEW_SPEAKER_ID, DEFAULT_SPEAKER_SIZE);
	_fe3d.model_setShadowed(PREVIEW_SPEAKER_ID, false);
	_fe3d.model_setReflected(PREVIEW_SPEAKER_ID, false);
	_fe3d.model_setBright(PREVIEW_SPEAKER_ID, true);
	_fe3d.model_setVisible(PREVIEW_SPEAKER_ID, false);
	for(const auto& audioID : _audioEditor.getLoadedAudioIDs())
	{
		_fe3d.sound_make3D(audioID, fvec3(0.0f), DEFAULT_SOUND_MAX_VOLUME, DEFAULT_SOUND_MAX_DISTANCE);
		_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuSoundPlace")->getScrollingList("sounds")->
			createButton(audioID, audioID.substr(1));
	}

	// Load preview pointlight
	_fe3d.model_create(PREVIEW_LAMP_ID, LAMP_MODEL_PATH);
	_fe3d.model_setBaseSize(PREVIEW_LAMP_ID, DEFAULT_LAMP_SIZE);
	_fe3d.model_setShadowed(PREVIEW_LAMP_ID, false);
	_fe3d.model_setReflected(PREVIEW_LAMP_ID, false);
	_fe3d.model_setBright(PREVIEW_LAMP_ID, true);
	_fe3d.model_setVisible(PREVIEW_LAMP_ID, false);
	_fe3d.pointlight_create(PREVIEW_LAMP_ID);
	_fe3d.pointlight_setRadius(PREVIEW_LAMP_ID, fvec3(DEFAULT_POINTLIGHT_RADIUS));
	_fe3d.pointlight_setIntensity(PREVIEW_LAMP_ID, DEFAULT_POINTLIGHT_INTENSITY);
	_fe3d.pointlight_setVisible(PREVIEW_LAMP_ID, false);

	// Load preview spotlight
	_fe3d.model_create(PREVIEW_TORCH_ID, TORCH_MODEL_PATH);
	_fe3d.model_setBaseSize(PREVIEW_TORCH_ID, DEFAULT_TORCH_SIZE);
	_fe3d.model_setShadowed(PREVIEW_TORCH_ID, false);
	_fe3d.model_setReflected(PREVIEW_TORCH_ID, false);
	_fe3d.model_setBright(PREVIEW_TORCH_ID, true);
	_fe3d.model_setVisible(PREVIEW_TORCH_ID, false);
	_fe3d.spotlight_create(PREVIEW_TORCH_ID);
	_fe3d.spotlight_setPitch(PREVIEW_TORCH_ID, DEFAULT_SPOTLIGHT_PITCH);
	_fe3d.spotlight_setIntensity(PREVIEW_TORCH_ID, DEFAULT_SPOTLIGHT_INTENSITY);
	_fe3d.spotlight_setAngle(PREVIEW_TORCH_ID, DEFAULT_SPOTLIGHT_ANGLE);
	_fe3d.spotlight_setDistance(PREVIEW_TORCH_ID, DEFAULT_SPOTLIGHT_DISTANCE);
	_fe3d.spotlight_setVisible(PREVIEW_TORCH_ID, false);

	// Load preview reflection
	_fe3d.model_create(PREVIEW_CAMERA_ID, CAMERA_MODEL_PATH);
	_fe3d.model_setBaseSize(PREVIEW_CAMERA_ID, DEFAULT_CAMERA_SIZE);
	_fe3d.model_setShadowed(PREVIEW_CAMERA_ID, false);
	_fe3d.model_setReflected(PREVIEW_CAMERA_ID, false);
	_fe3d.model_setBright(PREVIEW_CAMERA_ID, true);
	_fe3d.model_setVisible(PREVIEW_CAMERA_ID, false);
	_fe3d.reflection_create(PREVIEW_CAMERA_ID);
	_fe3d.reflection_setVisible(PREVIEW_CAMERA_ID, false);

	// Create ID textFields
	_gui.getGlobalScreen()->createTextField("modelID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true, false);
	_gui.getGlobalScreen()->createTextField("billboardID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true, false);
	_gui.getGlobalScreen()->createTextField("soundID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true, false);

	// Miscellaneous
	_fe3d.collision_enableCameraResponse(true, true, true);
	_fe3d.collision_setCameraBox(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("worldEditorControls");
	_isEditorLoaded = true;
}

void WorldEditor::unload()
{
	// GUI
	_unloadGUI();

	// Clear world
	clearCurrentWorld();

	// Unload preview entities
	_skyEditor.unloadSkyEntities();
	_terrainEditor.unloadTerrainEntities();
	_waterEditor.unloadWaterEntities();
	_fe3d.model_deleteAll();
	_fe3d.billboard_deleteAll();
	_fe3d.sound_deleteAll();
	_fe3d.pointlight_deleteAll();
	_fe3d.spotlight_deleteAll();
	_fe3d.reflection_deleteAll();

	// Reset editor properties
	_loadedModelIDs.clear();
	_outsideLoadedModelIDs.clear();
	_loadedBillboardIDs.clear();
	_outsideLoadedBillboardIDs.clear();
	_loadedSoundIDs.clear();
	_outsideLoadedSoundIDs.clear();
	_initialModelPosition.clear();
	_initialModelRotation.clear();
	_initialModelSize.clear();
	_customWorldModelIDs.clear();
	_customWorldBillboardIDs.clear();
	_customWorldAabbIDs.clear();
	_customWorldSoundIDs.clear();
	_customWorldPointlightIDs.clear();
	_customWorldSpotlightIDs.clear();
	_customWorldReflectionIDs.clear();
	_loadedAabbIDs.clear();
	_loadedPointlightIDs.clear();
	_loadedSpotlightIDs.clear();
	_loadedReflectionIDs.clear();
	_customWorldID = "";
	_loadedSkyID = "";
	_loadedTerrainID = "";
	_loadedWaterID = "";
	_currentSkyID = "";
	_currentTerrainID = "";
	_currentWaterID = "";
	_currentPreviewModelID = "";
	_selectedModelID = "";
	_activeModelID = "";
	_currentPreviewBillboardID = "";
	_selectedBillboardID = "";
	_activeBillboardID = "";
	_currentPreviewSoundID = "";
	_selectedSpeakerID = "";
	_activeSpeakerID = "";
	_selectedLampID = "";
	_activeLampID = "";
	_selectedTorchID = "";
	_activeTorchID = "";
	_selectedCameraID = "";
	_activeCameraID = "";
	_loadedWorldID = "";
	_currentWorldID = "";
	_editorSpeed = 1.0f;
	_selectedModelHighlightDirection = 1;
	_activeModelHighlightDirection = 1;
	_selectedBillboardHighlightDirection = 1;
	_activeBillboardHighlightDirection = 1;
	_selectedSpeakerHighlightDirection = 1;
	_activeSpeakerHighlightDirection = 1;
	_selectedLampHighlightDirection = 1;
	_activeLampHighlightDirection = 1;
	_selectedTorchHighlightDirection = 1;
	_activeTorchHighlightDirection = 1;
	_selectedCameraHighlightDirection = 1;
	_activeCameraHighlightDirection = 1;
	_hasCustomWorldLighting = false;
	_hasCustomWorldGraphics = false;
	_hasCustomWorldSky = false;
	_hasCustomWorldTerrain = false;
	_hasCustomWorldWater = false;
	_dontResetSelectedModel = false;
	_dontResetSelectedBillboard = false;
	_dontResetSelectedSpeaker = false;
	_dontResetSelectedLamp = false;
	_dontResetSelectedTorch = false;
	_dontResetSelectedCamera = false;
	_isPlacingPointlight = false;
	_isPlacingSpotlight = false;
	_isPlacingReflection = false;
	_isEditorLoaded = false;
	_isChoosingWorld = false;
	_isDeletingWorld = false;

	// Delete ID textFields
	_gui.getGlobalScreen()->deleteTextField("modelID");
	_gui.getGlobalScreen()->deleteTextField("billboardID");
	_gui.getGlobalScreen()->deleteTextField("soundID");

	// Miscellaneous
	_fe3d.collision_disableCameraResponse();
	if(_fe3d.misc_isAabbFrameRenderingEnabled())
	{
		_fe3d.misc_disableAabbFrameRendering();
	}
	if(_fe3d.misc_isWireframeRenderingEnabled())
	{
		_fe3d.misc_disableWireframeRendering();
	}
	if(_fe3d.misc_isDebugRenderingEnabled())
	{
		_fe3d.misc_disableDebugRendering();
	}
	if(_fe3d.raycast_isTerrainPointingEnabled())
	{
		_fe3d.raycast_disableTerrainPointing();
	}
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
}