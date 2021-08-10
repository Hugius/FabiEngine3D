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
	_fe3d.gfx_enableSpecularLighting();
	_fe3d.gfx_enablePointLighting();
	_fe3d.gfx_setSceneReflectionHeight(0.0f);

	// Directional light source
	const string texturePath = "engine_assets\\textures\\light_source.png";
	_fe3d.billboardEntity_create("@@lightSource");
	_fe3d.billboardEntity_setSize("@@lightSource", Vec2(0.0f));
	_fe3d.billboardEntity_setDiffuseMap("@@lightSource", texturePath);
	_fe3d.billboardEntity_setTransparent("@@lightSource", true);
	_fe3d.billboardEntity_setDepthMapIncluded("@@lightSource", false);
	_fe3d.billboardEntity_setShadowed("@@lightSource", false);
	_fe3d.billboardEntity_setReflected("@@lightSource", true);
	_fe3d.billboardEntity_setBright("@@lightSource", true);
	_fe3d.billboardEntity_setCameraFacingX("@@lightSource", true);
	_fe3d.billboardEntity_setCameraFacingY("@@lightSource", true);

	// Preview environment loading
	_skyEditor.loadSkyEntitiesFromFile();
	_terrainEditor.loadTerrainEntitiesFromFile();
	_waterEditor.loadWaterEntitiesFromFile();

	// Preview models loading
	_modelEditor.loadModelEntitiesFromFile();
	for (const auto& modelID : _modelEditor.getLoadedModelIDs())
	{
		// Check if there is a model entity present
		if (_fe3d.modelEntity_isExisting(modelID))
		{
			_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelPlace")->getScrollingList("modelList")->
				createButton(modelID, modelID.substr(1));
		}
	}

	// Preview animations loading
	_animationEditor.loadAnimationsFromFile(false);

	// Preview billboards loading
	_billboardEditor.loadBillboardEntitiesFromFile();
	for (const auto& billboardID : _billboardEditor.getLoadedBillboardIDs())
	{
		// Check if there is a billboard entity present
		if (_fe3d.billboardEntity_isExisting(billboardID))
		{
			_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardPlace")->getScrollingList("billboardList")->
				createButton(billboardID, billboardID.substr(1));
		}
	}

	// Preview audio loading
	_audioEditor.loadAudioEntitiesFromFile();
	_fe3d.modelEntity_create(PREVIEW_SPEAKER_ID, SPEAKER_MODEL_PATH);
	_fe3d.modelEntity_setSize(PREVIEW_SPEAKER_ID, DEFAULT_SPEAKER_SIZE);
	_fe3d.modelEntity_setShadowed(PREVIEW_SPEAKER_ID, false);
	_fe3d.modelEntity_setReflected(PREVIEW_SPEAKER_ID, false);
	_fe3d.modelEntity_setBright(PREVIEW_SPEAKER_ID, true);
	_fe3d.modelEntity_setVisible(PREVIEW_SPEAKER_ID, false);
	for (const auto& audioID : _audioEditor.getLoadedAudioIDs())
	{
		_fe3d.sound_make3D(audioID, Vec3(0.0f), DEFAULT_SOUND_MAX_VOLUME, DEFAULT_SOUND_MAX_DISTANCE);
		_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuSoundPlace")->getScrollingList("soundcasters")->
			createButton(audioID, audioID.substr(1));
	}

	// Preview point light loading
	_fe3d.modelEntity_create(PREVIEW_LAMP_ID, LAMP_MODEL_PATH);
	_fe3d.modelEntity_setSize(PREVIEW_LAMP_ID, DEFAULT_LAMP_SIZE);
	_fe3d.modelEntity_setShadowed(PREVIEW_LAMP_ID, false);
	_fe3d.modelEntity_setReflected(PREVIEW_LAMP_ID, false);
	_fe3d.modelEntity_setBright(PREVIEW_LAMP_ID, true);
	_fe3d.modelEntity_setVisible(PREVIEW_LAMP_ID, false);
	_fe3d.lightEntity_create(PREVIEW_LAMP_ID);
	_fe3d.lightEntity_setRadius(PREVIEW_LAMP_ID, Vec3(DEFAULT_LIGHT_RADIUS));
	_fe3d.lightEntity_setIntensity(PREVIEW_LAMP_ID, DEFAULT_LIGHT_INTENSITY);
	_fe3d.lightEntity_setVisible(PREVIEW_LAMP_ID, false);

	// Create ID textfields
	_gui.getGlobalScreen()->createTextfield("selectedModelID", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->createTextfield("selectedBillboardID", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->createTextfield("selectedSoundID", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));

	// Miscellaneous
	_fe3d.collision_enableCameraResponse(true, true, true);
	_fe3d.collision_setCameraBoxSize(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("sceneEditorControls");
	_isEditorLoaded = true;
}

void SceneEditor::unload()
{	
	// GUI
	_unloadGUI();

	// Clear scene
	clearCurrentScene();

	// Default graphics
	_fe3d.gfx_disableSpecularLighting(true);
	_fe3d.gfx_disablePointLighting(true);

	// Unload environment preview entities
	_skyEditor.unloadSkyEntities();
	_terrainEditor.unloadTerrainEntities();
	_waterEditor.unloadWaterEntities();

	// Delete other preview entities
	_fe3d.sound_deleteAll();
	_fe3d.modelEntity_deleteAll();
	_fe3d.billboardEntity_deleteAll();
	_fe3d.lightEntity_deleteAll();

	// Reset editor properties
	_hasCustomSceneLighting = false;
	_hasCustomSceneGraphics = false;
	_hasCustomSceneSky = false;
	_hasCustomSceneTerrain = false;
	_hasCustomSceneWater = false;
	_customSceneModelIDs.clear();
	_customSceneBillboardIDs.clear();
	_customSceneAabbIDs.clear();
	_customSceneSoundIDs.clear();
	_customSceneLightIDs.clear();
	_currentSkyID = "";
	_currentTerrainID = "";
	_currentWaterID = "";
	_loadedSceneID = "";
	_loadedSkyID = "";
	_loadedTerrainID = "";
	_loadedWaterID = "";
	_loadedModelIDs.clear();
	_loadedBillboardIDs.clear();
	_loadedSoundIDs.clear();
	_loadedLightIDs.clear();
	_loadedAabbIDs.clear();
	_outsideLoadedModelIDs.clear();
	_outsideLoadedBillboardIDs.clear();
	_outsideLoadedSoundIDs.clear();
	_initialModelPosition.clear();
	_initialModelRotation.clear();
	_initialModelSize.clear();
	_currentPreviewModelID = "";
	_selectedModelID = "";
	_activeModelID = "";
	_currentPreviewBillboardID = "";
	_selectedBillboardID = "";
	_activeBillboardID = "";
	_selectedLampID = "";
	_activeLampID = "";
	_currentSceneID = "";
	_selectedModelInversionDirection = 1;
	_activeModelInversionDirection = 1;
	_selectedBillboardInversionDirection = 1;
	_activeBillboardInversionDirection = 1;
	_selectedLampSizeDirection = 1;
	_activeLampSizeDirection = 1;
	_dontResetSelectedModel = false;
	_dontResetSelectedBillboard = false;
	_isPlacingPointLight = false;
	_isChoosingScene = false;
	_isDeletingScene = false;
	_editorSpeed = 1.0f;

	// Delete ID textfields
	_gui.getGlobalScreen()->deleteTextfield("selectedModelID");
	_gui.getGlobalScreen()->deleteTextfield("selectedBillboardID");
	_gui.getGlobalScreen()->deleteTextfield("selectedSoundID");

	// Miscellaneous
	_fe3d.collision_disableCameraResponse();
	if (_fe3d.misc_isAabbFrameRenderingEnabled())
	{
		_fe3d.misc_disableAabbFrameRendering();
	}
	if (_fe3d.misc_isWireFrameRenderingEnabled())
	{
		_fe3d.misc_disableWireFrameRendering();
	}
	if (_fe3d.misc_isDebugRenderingEnabled())
	{
		_fe3d.misc_disableDebugRendering();
	}
	if (_fe3d.misc_isTerrainRaycastPointingEnabled())
	{
		_fe3d.misc_disableTerrainRaycastPointing();
	}
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	_isEditorLoaded = false;
}