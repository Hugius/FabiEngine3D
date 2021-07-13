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
	_fe3d.gfx_enableSkyReflections(0.5f);
	_fe3d.gfx_enableSceneReflections(0.5f, 0.0f);
	_fe3d.gfx_enableLightMapping();
	_fe3d.gfx_enableNormalMapping();

	// Directional light source
	const string texturePath = "engine_assets\\textures\\light_source.png";
	_fe3d.billboardEntity_add("@@lightSource", texturePath, Vec3(0.0f), Vec3(0.0f), Vec2(0.0f), true, true, true, true);
	_fe3d.billboardEntity_setDepthMapIncluded("@@lightSource", false);
	_fe3d.billboardEntity_setShadowed("@@lightSource", false);
	_fe3d.billboardEntity_setReflected("@@lightSource", true);
	_fe3d.billboardEntity_setBloomed("@@lightSource", true);

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
	_animationEditor.loadAnimationsFromFile();

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
	_fe3d.modelEntity_add(PREVIEW_SPEAKER_ID, SPEAKER_MODEL_PATH, Vec3(0.0f), Vec3(0.0f), DEFAULT_SPEAKER_SIZE, false);
	_fe3d.modelEntity_setShadowed(PREVIEW_SPEAKER_ID, false);
	_fe3d.modelEntity_setReflected(PREVIEW_SPEAKER_ID, false);
	_fe3d.modelEntity_setColor(PREVIEW_SPEAKER_ID, Vec3(1.0f));
	for (const auto& audioID : _audioEditor.getLoadedAudioIDs())
	{
		_fe3d.soundEntity_make3D(audioID, Vec3(0.0f), DEFAULT_SOUND_MAX_VOLUME, DEFAULT_SOUND_MAX_DISTANCE);
		_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuSoundPlace")->getScrollingList("soundcasters")->
			addButton(audioID, audioID.substr(1));
	}

	// Preview pointlight loading
	_fe3d.lightEntity_add(PREVIEW_POINTLIGHT_ID);
	_fe3d.lightEntity_setVisible(PREVIEW_POINTLIGHT_ID, false);
	_fe3d.modelEntity_add(PREVIEW_POINTLIGHT_ID, LIGHTBULB_MODEL_PATH, Vec3(0.0f), Vec3(0.0f), DEFAULT_LIGHTBULB_SIZE, false);
	_fe3d.modelEntity_setShadowed(PREVIEW_POINTLIGHT_ID, false);
	_fe3d.modelEntity_setReflected(PREVIEW_POINTLIGHT_ID, false);
	_fe3d.modelEntity_setBloomed(PREVIEW_POINTLIGHT_ID, true);
	_fe3d.modelEntity_setColor(PREVIEW_POINTLIGHT_ID, Vec3(1.0f));

	// Create name textfields
	_gui.getGlobalScreen()->addTextfield("selectedModelName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedBillboardName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedSoundName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));

	// Miscellaneous
	_fe3d.collision_enableCameraResponse(true, true, true);
	_fe3d.collision_setCameraBoxSize(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
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
	_fe3d.gfx_disableSkyReflections(true);
	_fe3d.gfx_disableSceneReflections(true);
	_fe3d.gfx_disableLightMapping(true);
	_fe3d.gfx_disableNormalMapping(true);

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
	_initialModelLightness.clear();
	_initialModelPosition.clear();
	_initialModelRotation.clear();
	_initialModelSize.clear();
	_initialBillboardLightness.clear();
	_currentPreviewModelID = "";
	_selectedModelID = "";
	_activeModelID = "";
	_currentPreviewBillboardID = "";
	_selectedBillboardID = "";
	_activeBillboardID = "";
	_selectedLightBulbID = "";
	_activeLightBulbID = "";
	_currentSceneID = "";
	_selectedModelLightnessMultiplier = 1;
	_activeModelLightnessMultiplier = 1;
	_selectedBillboardLightnessMultiplier = 1;
	_activeBillboardLightnessMultiplier = 1;
	_selectedLightSizeMultiplier = 1;
	_activeLightSizeMultiplier = 1;
	_dontResetSelectedModel = false;
	_dontResetSelectedBillboard = false;
	_isPlacingPointlight = false;
	_isChoosingScene = false;
	_isDeletingScene = false;
	_transformation = TransformationType::TRANSLATION;
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
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_fe3d.input_setKeyTogglingLocked(false);
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	_isEditorLoaded = false;
}