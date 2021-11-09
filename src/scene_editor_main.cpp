#include "scene_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

SceneEditor::SceneEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, SkyEditor& skyEditor, TerrainEditor& terrainEditor, WaterEditor& waterEditor, ModelEditor& modelEditor, AnimationEditor& animationEditor, BillboardEditor& billboardEditor, AudioEditor& audioEditor)
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

void SceneEditor::load()
{
	// GUI
	_loadGUI();

	// Camera
	_fe3d.camera_reset();

	// Default graphics
	_fe3d.gfx_setPlanarReflectionHeight(0.0f);

	// Directional light source
	const string texturePath = "engine\\textures\\light_source.png";
	_fe3d.billboardEntity_create("@@lightSource");
	_fe3d.billboardEntity_setSize("@@lightSource", Vec2(0.0f));
	_fe3d.billboardEntity_setDiffuseMap("@@lightSource", texturePath);
	_fe3d.billboardEntity_setDepthMapIncluded("@@lightSource", false);
	_fe3d.billboardEntity_setShadowed("@@lightSource", false);
	_fe3d.billboardEntity_setReflected("@@lightSource", true);
	_fe3d.billboardEntity_setBright("@@lightSource", true);
	_fe3d.billboardEntity_setCameraFacingX("@@lightSource", true);
	_fe3d.billboardEntity_setCameraFacingY("@@lightSource", true);

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
		if(_fe3d.modelEntity_isExisting(modelID))
		{
			_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelPlace")->getScrollingList("modelList")->
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
		if(_fe3d.billboardEntity_isExisting(billboardID))
		{
			_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardPlace")->getScrollingList("billboardList")->
				createButton(billboardID, billboardID.substr(1));
		}
	}

	// Load preview sounds
	_audioEditor.loadAudioEntitiesFromFile();
	_fe3d.modelEntity_create(PREVIEW_SPEAKER_ID, SPEAKER_MODEL_PATH);
	_fe3d.modelEntity_setBaseSize(PREVIEW_SPEAKER_ID, DEFAULT_SPEAKER_SIZE);
	_fe3d.modelEntity_setShadowed(PREVIEW_SPEAKER_ID, false);
	_fe3d.modelEntity_setReflected(PREVIEW_SPEAKER_ID, false);
	_fe3d.modelEntity_setBright(PREVIEW_SPEAKER_ID, true);
	_fe3d.modelEntity_setVisible(PREVIEW_SPEAKER_ID, false);
	for(const auto& audioID : _audioEditor.getLoadedAudioIDs())
	{
		_fe3d.sound_make3D(audioID, Vec3(0.0f), DEFAULT_SOUND_MAX_VOLUME, DEFAULT_SOUND_MAX_DISTANCE);
		_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuSoundPlace")->getScrollingList("sounds")->
			createButton(audioID, audioID.substr(1));
	}

	// Load preview pointlight
	_fe3d.modelEntity_create(PREVIEW_LAMP_ID, LAMP_MODEL_PATH);
	_fe3d.modelEntity_setBaseSize(PREVIEW_LAMP_ID, DEFAULT_LAMP_SIZE);
	_fe3d.modelEntity_setShadowed(PREVIEW_LAMP_ID, false);
	_fe3d.modelEntity_setReflected(PREVIEW_LAMP_ID, false);
	_fe3d.modelEntity_setBright(PREVIEW_LAMP_ID, true);
	_fe3d.modelEntity_setVisible(PREVIEW_LAMP_ID, false);
	_fe3d.pointlightEntity_create(PREVIEW_LAMP_ID);
	_fe3d.pointlightEntity_setRadius(PREVIEW_LAMP_ID, Vec3(DEFAULT_POINTLIGHT_RADIUS));
	_fe3d.pointlightEntity_setIntensity(PREVIEW_LAMP_ID, DEFAULT_POINTLIGHT_INTENSITY);
	_fe3d.pointlightEntity_setVisible(PREVIEW_LAMP_ID, false);

	// Load preview spotlight
	_fe3d.modelEntity_create(PREVIEW_TORCH_ID, TORCH_MODEL_PATH);
	_fe3d.modelEntity_setBaseSize(PREVIEW_TORCH_ID, DEFAULT_TORCH_SIZE);
	_fe3d.modelEntity_setShadowed(PREVIEW_TORCH_ID, false);
	_fe3d.modelEntity_setReflected(PREVIEW_TORCH_ID, false);
	_fe3d.modelEntity_setBright(PREVIEW_TORCH_ID, true);
	_fe3d.modelEntity_setVisible(PREVIEW_TORCH_ID, false);
	_fe3d.spotlightEntity_create(PREVIEW_TORCH_ID);
	_fe3d.spotlightEntity_setPitch(PREVIEW_TORCH_ID, DEFAULT_SPOTLIGHT_PITCH);
	_fe3d.spotlightEntity_setIntensity(PREVIEW_TORCH_ID, DEFAULT_SPOTLIGHT_INTENSITY);
	_fe3d.spotlightEntity_setAngle(PREVIEW_TORCH_ID, DEFAULT_SPOTLIGHT_ANGLE);
	_fe3d.spotlightEntity_setDistance(PREVIEW_TORCH_ID, DEFAULT_SPOTLIGHT_DISTANCE);
	_fe3d.spotlightEntity_setVisible(PREVIEW_TORCH_ID, false);

	// Load preview reflection
	_fe3d.modelEntity_create(PREVIEW_CAMERA_ID, CAMERA_MODEL_PATH);
	_fe3d.modelEntity_setBaseSize(PREVIEW_CAMERA_ID, DEFAULT_CAMERA_SIZE);
	_fe3d.modelEntity_setShadowed(PREVIEW_CAMERA_ID, false);
	_fe3d.modelEntity_setReflected(PREVIEW_CAMERA_ID, false);
	_fe3d.modelEntity_setBright(PREVIEW_CAMERA_ID, true);
	_fe3d.modelEntity_setVisible(PREVIEW_CAMERA_ID, false);
	_fe3d.reflectionEntity_create(PREVIEW_CAMERA_ID);
	_fe3d.reflectionEntity_setVisible(PREVIEW_CAMERA_ID, false);

	// Create ID textFields
	_gui.getGlobalScreen()->createTextField("modelID", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f), true, false);
	_gui.getGlobalScreen()->createTextField("billboardID", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f), true, false);
	_gui.getGlobalScreen()->createTextField("soundID", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f), true, false);

	// Miscellaneous
	_fe3d.collision_enableCameraResponse(true, true, true);
	_fe3d.collision_setCameraBox(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("sceneEditorControls");
	_isEditorLoaded = true;
}

void SceneEditor::unload()
{
	// GUI
	_unloadGUI();

	// Clear scene
	clearCurrentScene();

	// Unload preview entities
	_skyEditor.unloadSkyEntities();
	_terrainEditor.unloadTerrainEntities();
	_waterEditor.unloadWaterEntities();
	_fe3d.modelEntity_deleteAll();
	_fe3d.billboardEntity_deleteAll();
	_fe3d.sound_deleteAll();
	_fe3d.pointlightEntity_deleteAll();
	_fe3d.spotlightEntity_deleteAll();
	_fe3d.reflectionEntity_deleteAll();

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
	_customSceneModelIDs.clear();
	_customSceneBillboardIDs.clear();
	_customSceneAabbIDs.clear();
	_customSceneSoundIDs.clear();
	_customScenePointlightIDs.clear();
	_customSceneSpotlightIDs.clear();
	_customSceneReflectionIDs.clear();
	_loadedAabbIDs.clear();
	_loadedPointlightIDs.clear();
	_loadedSpotlightIDs.clear();
	_loadedReflectionIDs.clear();
	_customSceneID = "";
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
	_loadedSceneID = "";
	_currentSceneID = "";
	_editorSpeed = 1.0f;
	_selectedModelInversionDirection = 1;
	_activeModelInversionDirection = 1;
	_selectedBillboardInversionDirection = 1;
	_activeBillboardInversionDirection = 1;
	_selectedSpeakerSizeDirection = 1;
	_activeSpeakerSizeDirection = 1;
	_selectedLampSizeDirection = 1;
	_activeLampSizeDirection = 1;
	_selectedTorchSizeDirection = 1;
	_activeTorchSizeDirection = 1;
	_selectedCameraSizeDirection = 1;
	_activeCameraSizeDirection = 1;
	_hasCustomSceneLighting = false;
	_hasCustomSceneGraphics = false;
	_hasCustomSceneSky = false;
	_hasCustomSceneTerrain = false;
	_hasCustomSceneWater = false;
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
	_isChoosingScene = false;
	_isDeletingScene = false;

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
	if(_fe3d.misc_isWireFrameRenderingEnabled())
	{
		_fe3d.misc_disableWireFrameRendering();
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