#include "scene_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

SceneEditor::SceneEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, EnvironmentEditor& environmentEditor, 
	ModelEditor& modelEditor, AnimationEditor& animationEditor, BillboardEditor& billboardEditor, AudioEditor& audioEditor) :
	_fe3d(fe3d),
	_gui(gui),
	_environmentEditor(environmentEditor),
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
	_fe3d.billboardEntity_create("@@lightSource", texturePath, Vec3(0.0f), Vec3(0.0f), Vec2(0.0f), true, true, true, true);
	_fe3d.billboardEntity_setDepthMapIncluded("@@lightSource", false);
	_fe3d.billboardEntity_setShadowed("@@lightSource", false);
	_fe3d.billboardEntity_setReflected("@@lightSource", true);
	_fe3d.billboardEntity_setBright("@@lightSource", true);

	// Preview environment loading
	_environmentEditor.loadSkyEntitiesFromFile();
	_environmentEditor.loadTerrainEntitiesFromFile();
	_environmentEditor.loadWaterEntitiesFromFile();

	// Preview models loading
	_modelEditor.loadModelEntitiesFromFile();
	for (const auto& modelID : _modelEditor.getLoadedModelIDs())
	{
		// Check if there is a model entity present
		if (_fe3d.modelEntity_isExisting(modelID))
		{
			_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelPlace")->getScrollingList("modelList")->
				addButton(modelID, modelID.substr(1));
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
				addButton(billboardID, billboardID.substr(1));
		}
	}

	// Preview audio loading
	_audioEditor.loadAudioEntitiesFromFile();
	_fe3d.modelEntity_create(PREVIEW_SPEAKER_ID, SPEAKER_MODEL_PATH, Vec3(0.0f), Vec3(0.0f), DEFAULT_SPEAKER_SIZE, false);
	_fe3d.modelEntity_setShadowed(PREVIEW_SPEAKER_ID, false);
	_fe3d.modelEntity_setReflected(PREVIEW_SPEAKER_ID, false);
	_fe3d.modelEntity_setBright(PREVIEW_SPEAKER_ID, true);
	for (const auto& audioID : _audioEditor.getLoadedAudioIDs())
	{
		_fe3d.soundEntity_make3D(audioID, Vec3(0.0f), DEFAULT_SOUND_MAX_VOLUME, DEFAULT_SOUND_MAX_DISTANCE);
		_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuSoundPlace")->getScrollingList("soundcasters")->
			addButton(audioID, audioID.substr(1));
	}

	// Preview point light loading
	_fe3d.lightEntity_create(PREVIEW_LIGHT_BULB_ID, Vec3(0.0f), Vec3(1.0f), 1.0f, 10.0f);
	_fe3d.lightEntity_setVisible(PREVIEW_LIGHT_BULB_ID, false);
	_fe3d.modelEntity_create(PREVIEW_LIGHT_BULB_ID, LIGHT_BULB_MODEL_PATH, Vec3(0.0f), Vec3(0.0f), DEFAULT_LIGHT_BULB_SIZE, false);
	_fe3d.modelEntity_setShadowed(PREVIEW_LIGHT_BULB_ID, false);
	_fe3d.modelEntity_setReflected(PREVIEW_LIGHT_BULB_ID, false);
	_fe3d.modelEntity_setBright(PREVIEW_LIGHT_BULB_ID, true);

	// Create name textfields
	_gui.getGlobalScreen()->addTextfield("selectedModelName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedBillboardName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedSoundName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));

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
	_environmentEditor.unloadSkyEntities();
	_environmentEditor.unloadTerrainEntities();
	_environmentEditor.unloadWaterEntities();

	// Delete other preview entities
	_fe3d.soundEntity_deleteAll();
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
	_selectedLightBulbID = "";
	_activeLightBulbID = "";
	_currentSceneID = "";
	_selectedModelInversionDirection = 1;
	_activeModelInversionDirection = 1;
	_selectedBillboardInversionDirection = 1;
	_activeBillboardInversionDirection = 1;
	_selectedLightBulbSizeDirection = 1;
	_activeLightBulbSizeDirection = 1;
	_dontResetSelectedModel = false;
	_dontResetSelectedBillboard = false;
	_isPlacingPointLight = false;
	_isChoosingScene = false;
	_isDeletingScene = false;
	_editorSpeed = 1.0f;

	// Delete name textfields
	_gui.getGlobalScreen()->deleteTextfield("selectedModelName");
	_gui.getGlobalScreen()->deleteTextfield("selectedBillboardName");
	_gui.getGlobalScreen()->deleteTextfield("selectedSoundName");

	// Miscellaneous
	_fe3d.collision_disableCameraResponse();
	if (_fe3d.misc_isAabbFrameRenderingEnabled())
	{
		_fe3d.misc_disableAabbFrameRendering();
	}
	if (_fe3d.misc_isWireframeRenderingEnabled())
	{
		_fe3d.misc_disableWireframeRendering();
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