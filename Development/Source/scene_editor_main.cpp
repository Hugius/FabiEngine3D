#include "scene_editor.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVPC::calcTextWidth(text, 0.15f, 1.8f)

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

	// Default camera
	_fe3d.camera_load(90.0f, 0.1f, 10000.0f, Vec3(0.0f));

	// Default graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 0.5f);
	_fe3d.gfx_enableSpecularLighting();
	_fe3d.gfx_enablePointLighting();
	_fe3d.gfx_enableSkyReflections(0.5f);
	_fe3d.gfx_enableSceneReflections(0.5f);
	_fe3d.gfx_enableLightMapping();
	_fe3d.gfx_enableNormalMapping();
	_fe3d.gfx_enableWaterEffects();

	// Preview environment loading
	_environmentEditor.loadSkyEntitiesFromFile();
	_environmentEditor.loadTerrainEntitiesFromFile();
	_environmentEditor.loadWaterEntitiesFromFile();

	// Preview models loading
	_modelEditor.loadGameEntitiesFromFile();
	for (auto& modelName : _modelEditor.getLoadedModelIDs())
	{
		// Check if there is a GAME entity present
		if (_fe3d.gameEntity_isExisting(modelName))
		{
			_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelPlace")->getScrollingList("models")->
				addButton(modelName, modelName.substr(1));
		}
	}

	// Preview animations loading
	_animationEditor.loadAnimationsFromFile();

	// Preview billboards loading
	_billboardEditor.loadBillboardEntitiesFromFile();
	for (auto& billboardName : _billboardEditor.getLoadedBillboardIDs())
	{
		// Check if there is a BILLBOARD entity present
		if (_fe3d.billboardEntity_isExisting(billboardName))
		{
			_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardPlace")->getScrollingList("billboards")->
				addButton(billboardName, billboardName.substr(1));
		}
	}

	// Load lightsource billboard
	const string texturePath = "engine_assets\\textures\\light_source.png";
	_fe3d.billboardEntity_add("@@lightSource", texturePath, Vec3(0.0f), Vec3(0.0f), Vec2(0.0f), true, true, true, true);
	_fe3d.billboardEntity_setDepthMapIncluded("@@lightSource", false);
	_fe3d.billboardEntity_setLightness("@@lightSource", 10000.0f);

	// Preview pointlight loading
	_fe3d.lightEntity_add(PREVIEW_POINTLIGHT_ID);
	_fe3d.lightEntity_hide(PREVIEW_POINTLIGHT_ID);
	_fe3d.gameEntity_add(PREVIEW_POINTLIGHT_ID, LIGHTBULB_MODEL_PATH, Vec3(0.0f), Vec3(0.0f), DEFAULT_LIGHTBULB_SIZE, false);
	_fe3d.gameEntity_setShadowed(PREVIEW_POINTLIGHT_ID, false);

	// Preview audio loading
	_audioEditor.loadAudioEntitiesFromFile();
	_fe3d.gameEntity_add(PREVIEW_SPEAKER_ID, SPEAKER_MODEL_PATH, Vec3(0.0f), Vec3(0.0f), DEFAULT_SPEAKER_SIZE, false);
	_fe3d.gameEntity_setShadowed(PREVIEW_SPEAKER_ID, false);
	for (auto& audioName : _audioEditor.getLoadedAudioIDs())
	{
		_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuAudioPlace")->getScrollingList("audiocasters")->
			addButton(audioName, audioName.substr(1));
	}

	// Create name textfields
	_gui.getGlobalScreen()->addTextfield("selectedModelName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedBillboardName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedAudioName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));

	// Miscellaneous
	_fe3d.collision_setCameraBoxSize(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	_fe3d.collision_enableCameraResponse(true, true, true);
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
	clearScene();

	// Unload environment preview entities
	_environmentEditor.unloadSkyEntities();
	_environmentEditor.unloadTerrainEntities();
	_environmentEditor.unloadWaterEntities();

	// Delete other preview entities
	_fe3d.audioEntity_deleteAll();
	_fe3d.gameEntity_deleteAll();
	_fe3d.billboardEntity_deleteAll();
	_fe3d.lightEntity_deleteAll();

	// Reset variables
	_loadedSceneID = "";
	_loadedSkyID = "";
	_loadedTerrainID = "";
	_loadedWaterID = "";
	_loadedModelIDs.clear();
	_loadedBillboardIDs.clear();
	_loadedLightIDs.clear();
	_loadedAudioIDs.clear();
	_currentSkyID = "";
	_currentTerrainID = "";
	_currentWaterID = "";
	_initialModelLightness.clear();
	_initialModelPosition.clear();
	_initialModelRotation.clear();
	_initialModelSize.clear();
	_currentPreviewModelName = "";
	_selectedModelID = "";
	_activeModelID = "";
	_selectedModelLightnessMultiplier = 1;
	_activeModelLightnessMultiplier = 1;
	_dontResetSelectedModel = false;
	_initialBillboardLightness.clear();
	_currentPreviewBillboardName = "";
	_selectedBillboardID = "";
	_activeBillboardID = "";
	_selectedBillboardLightnessMultiplier = 1;
	_activeBillboardLightnessMultiplier = 1;
	_dontResetSelectedBillboard = false;
	_isPlacingPointlight = false;
	_selectedLightSizeMultiplier = 1;
	_activeLightSizeMultiplier = 1;
	_selectedLightBulbID = "";
	_activeLightBulbID = "";
	_currentSceneID = "";
	_isChoosingScene = false;
	_isDeletingScene = false;
	_transformation = TransformationType::TRANSLATION;
	_customEditorSpeed = 1.0f;

	// Delete name textfields
	_gui.getGlobalScreen()->deleteTextfield("selectedModelName");
	_gui.getGlobalScreen()->deleteTextfield("selectedBillboardName");
	_gui.getGlobalScreen()->deleteTextfield("selectedAudioName");

	// Miscellaneous
	_fe3d.collision_disableCameraResponse();
	_fe3d.misc_disableAabbFrameRendering();
	_fe3d.misc_disableWireframeRendering();
	_fe3d.misc_disableDebugRendering();
	_fe3d.misc_disableTerrainRaycasting();
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_fe3d.input_setKeyTogglingLocked(false);
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	_isEditorLoaded = false;
}