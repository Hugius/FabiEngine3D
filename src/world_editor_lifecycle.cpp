#include "world_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

void WorldEditor::load()
{
	_loadGUI();

	_fe3d->camera_reset();

	_fe3d->gfx_enableAntiAliasing();
	_fe3d->gfx_setAnisotropicFilteringQuality(Config::MAX_ANISOTROPIC_FILTERING_QUALITY);

	_skyEditor->loadFromFile();

	_terrainEditor->loadFromFile();

	_waterEditor->loadFromFile();

	_modelEditor->loadFromFile();
	for(const auto& id : _modelEditor->getLoadedIds())
	{
		auto screen = _gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuModelPlace");
		screen->getScrollingList("modelList")->createButton(id, id.substr(1));
	}

	_quad3dEditor->loadFromFile();
	for(const auto& id : _quad3dEditor->getLoadedIds())
	{
		auto screen = _gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuQuad3dPlace");
		screen->getScrollingList("quad3dList")->createButton(id, id.substr(1));
	}

	_text3dEditor->loadFromFile();
	for(const auto& id : _text3dEditor->getLoadedIds())
	{
		auto screen = _gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuText3dPlace");
		screen->getScrollingList("text3dList")->createButton(id, id.substr(1));
	}

	_animation2dEditor->loadFromFile(false);
	_animation3dEditor->loadFromFile(false);

	_fe3d->model_create(TEMPLATE_LAMP_ID, LAMP_MODEL_PATH);
	_fe3d->model_setBaseSize(TEMPLATE_LAMP_ID, DEFAULT_LAMP_SIZE);
	_fe3d->model_setShadowed(TEMPLATE_LAMP_ID, false);
	_fe3d->model_setReflected(TEMPLATE_LAMP_ID, false);
	_fe3d->model_setBright(TEMPLATE_LAMP_ID, "", true);
	_fe3d->model_setVisible(TEMPLATE_LAMP_ID, false);
	_fe3d->pointlight_create(TEMPLATE_LAMP_ID);
	_fe3d->pointlight_setRadius(TEMPLATE_LAMP_ID, fvec3(DEFAULT_POINTLIGHT_RADIUS));
	_fe3d->pointlight_setIntensity(TEMPLATE_LAMP_ID, DEFAULT_POINTLIGHT_INTENSITY);
	_fe3d->pointlight_setVisible(TEMPLATE_LAMP_ID, false);

	_fe3d->model_create(TEMPLATE_TORCH_ID, TORCH_MODEL_PATH);
	_fe3d->model_setBaseRotation(TEMPLATE_TORCH_ID, DEFAULT_TORCH_ROTATION);
	_fe3d->model_setBaseSize(TEMPLATE_TORCH_ID, DEFAULT_TORCH_SIZE);
	_fe3d->model_setShadowed(TEMPLATE_TORCH_ID, false);
	_fe3d->model_setReflected(TEMPLATE_TORCH_ID, false);
	_fe3d->model_setBright(TEMPLATE_TORCH_ID, "", true);
	_fe3d->model_setVisible(TEMPLATE_TORCH_ID, false);
	_fe3d->spotlight_create(TEMPLATE_TORCH_ID);
	_fe3d->spotlight_setPitch(TEMPLATE_TORCH_ID, DEFAULT_SPOTLIGHT_PITCH);
	_fe3d->spotlight_setIntensity(TEMPLATE_TORCH_ID, DEFAULT_SPOTLIGHT_INTENSITY);
	_fe3d->spotlight_setAngle(TEMPLATE_TORCH_ID, DEFAULT_SPOTLIGHT_ANGLE);
	_fe3d->spotlight_setDistance(TEMPLATE_TORCH_ID, DEFAULT_SPOTLIGHT_DISTANCE);
	_fe3d->spotlight_setVisible(TEMPLATE_TORCH_ID, false);

	_fe3d->model_create(TEMPLATE_CAMERA_ID, CAMERA_MODEL_PATH);
	_fe3d->model_setBaseSize(TEMPLATE_CAMERA_ID, DEFAULT_CAMERA_SIZE);
	_fe3d->model_setShadowed(TEMPLATE_CAMERA_ID, false);
	_fe3d->model_setReflected(TEMPLATE_CAMERA_ID, false);
	_fe3d->model_setBright(TEMPLATE_CAMERA_ID, "", true);
	_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);
	_fe3d->reflection_create(TEMPLATE_CAMERA_ID);
	_fe3d->reflection_setVisible(TEMPLATE_CAMERA_ID, false);

	_soundEditor->loadFromFile();
	_fe3d->model_create(TEMPLATE_SPEAKER_ID, SPEAKER_MODEL_PATH);
	_fe3d->model_setBaseSize(TEMPLATE_SPEAKER_ID, DEFAULT_SPEAKER_SIZE);
	_fe3d->model_setShadowed(TEMPLATE_SPEAKER_ID, false);
	_fe3d->model_setReflected(TEMPLATE_SPEAKER_ID, false);
	_fe3d->model_setBright(TEMPLATE_SPEAKER_ID, "", true);
	_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);
	for(const auto& id : _soundEditor->getLoadedIds())
	{
		_fe3d->sound3d_create(id, _fe3d->sound2d_getAudioPath(id));
		_fe3d->sound3d_setMaxVolume(id, DEFAULT_SOUND_MAX_VOLUME);
		_fe3d->sound3d_setMaxDistance(id, DEFAULT_SOUND_MAX_DISTANCE);

		auto screen = _gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuSoundPlace");
		screen->getScrollingList("soundList")->createButton(id, id.substr(1));
	}

	_gui->getOverlay()->createTextField("modelId", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true);
	_gui->getOverlay()->createTextField("quadId", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true);
	_gui->getOverlay()->createTextField("textId", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true);
	_gui->getOverlay()->createTextField("soundId", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true);

	_fe3d->collision_enableCameraResponse(true, true, true);
	_fe3d->collision_setCameraBox(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");
	_isEditorLoaded = true;
}

void WorldEditor::unload()
{
	_unloadGUI();

	_fe3d->gfx_disableAntiAliasing(true);
	_fe3d->gfx_setAnisotropicFilteringQuality(Config::MIN_ANISOTROPIC_FILTERING_QUALITY);

	unloadEditorWorld();

	for(const auto& id : _skyEditor->getLoadedIds())
	{
		_fe3d->sky_delete(id);
	}

	for(const auto& id : _terrainEditor->getLoadedIds())
	{
		_fe3d->terrain_delete(id);
	}

	for(const auto& id : _waterEditor->getLoadedIds())
	{
		_fe3d->water_delete(id);
	}

	for(const auto& id : _modelEditor->getLoadedIds())
	{
		_fe3d->model_delete(id);
	}

	for(const auto& id : _quad3dEditor->getLoadedIds())
	{
		_fe3d->quad3d_delete(id);
	}

	for(const auto& id : _text3dEditor->getLoadedIds())
	{
		_fe3d->text3d_delete(id);
	}

	_fe3d->model_delete(TEMPLATE_LAMP_ID);
	_fe3d->pointlight_delete(TEMPLATE_LAMP_ID);

	_fe3d->model_delete(TEMPLATE_TORCH_ID);
	_fe3d->spotlight_delete(TEMPLATE_TORCH_ID);

	_fe3d->model_delete(TEMPLATE_CAMERA_ID);
	_fe3d->reflection_delete(TEMPLATE_CAMERA_ID);

	_fe3d->model_delete(TEMPLATE_SPEAKER_ID);
	for(const auto& id : _soundEditor->getLoadedIds())
	{
		_fe3d->sound2d_delete(id);
		_fe3d->sound3d_delete(id);
	}

	_loadedModelIds.clear();
	_outsideLoadedModelIds.clear();
	_loadedQuadIds.clear();
	_outsideLoadedQuadIds.clear();
	_loadedSoundIds.clear();
	_outsideLoadedSoundIds.clear();
	_initialModelPosition.clear();
	_initialModelRotation.clear();
	_initialModelSize.clear();
	_customWorldModelIds.clear();
	_customWorldQuadIds.clear();
	_customWorldAabbIds.clear();
	_customWorldSoundIds.clear();
	_customWorldPointlightIds.clear();
	_customWorldSpotlightIds.clear();
	_customWorldReflectionIds.clear();
	_loadedAabbIds.clear();
	_loadedPointlightIds.clear();
	_loadedSpotlightIds.clear();
	_loadedReflectionIds.clear();
	_customWorldId = "";
	_loadedSkyId = "";
	_loadedTerrainId = "";
	_loadedWaterId = "";
	_currentSkyId = "";
	_currentTerrainId = "";
	_currentWaterId = "";
	_currentTemplateModelId = "";
	_selectedModelId = "";
	_activeModelId = "";
	_currentTemplateQuadId = "";
	_selectedQuadId = "";
	_activeQuadId = "";
	_currentTemplateSoundId = "";
	_selectedSpeakerId = "";
	_activeSpeakerId = "";
	_selectedLampId = "";
	_activeLampId = "";
	_selectedTorchId = "";
	_activeTorchId = "";
	_selectedCameraId = "";
	_activeCameraId = "";
	_loadedWorldId = "";
	_currentWorldId = "";
	_editorSpeed = 1.0f;
	_selectedModelHighlightDirection = 1;
	_activeModelHighlightDirection = 1;
	_selectedQuad3dHighlightDirection = 1;
	_activeQuad3dHighlightDirection = 1;
	_selectedText3dHighlightDirection = 1;
	_activeText3dHighlightDirection = 1;
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
	_dontResetSelectedQuad3d = false;
	_dontResetSelectedText3d = false;
	_dontResetSelectedSpeaker = false;
	_dontResetSelectedLamp = false;
	_dontResetSelectedTorch = false;
	_dontResetSelectedCamera = false;
	_isPlacingPointlight = false;
	_isPlacingSpotlight = false;
	_isPlacingReflection = false;
	_isEditorLoaded = false;
	_isCreatingWorld = false;
	_isChoosingWorld = false;
	_isDeletingWorld = false;

	_gui->getOverlay()->deleteTextField("modelId");
	_gui->getOverlay()->deleteTextField("quadId");
	_gui->getOverlay()->deleteTextField("soundId");

	_fe3d->collision_disableCameraResponse();

	if(_fe3d->raycast_isTerrainPointingEnabled())
	{
		_fe3d->raycast_disableTerrainPointing();
	}
}

void WorldEditor::update()
{
	if(_isEditorLoaded)
	{
		_updateMainMenu();
	}
	if(_isEditorLoaded)
	{
		_updateChoiceMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSkyMenu();
	}
	if(_isEditorLoaded)
	{
		_updateTerrainMenu();
	}
	if(_isEditorLoaded)
	{
		_updateWaterMenu();
	}
	if(_isEditorLoaded)
	{
		_updateModelMenu();
	}
	if(_isEditorLoaded)
	{
		_updateModelPlacingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateModelChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateModelPlacing();
	}
	if(_isEditorLoaded)
	{
		_updateModelEditing();
	}
	if(_isEditorLoaded)
	{
		_updateQuad3dMenu();
	}
	if(_isEditorLoaded)
	{
		_updateQuad3dPlacingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateQuad3dChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateQuad3dPlacing();
	}
	if(_isEditorLoaded)
	{
		_updateQuad3dEditing();
	}
	if(_isEditorLoaded)
	{
		_updateText3dMenu();
	}
	if(_isEditorLoaded)
	{
		_updateText3dPlacingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateText3dChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateText3dPlacing();
	}
	if(_isEditorLoaded)
	{
		_updateText3dEditing();
	}
	if(_isEditorLoaded)
	{
		_updatePointlightMenu();
	}
	if(_isEditorLoaded)
	{
		_updatePointlightChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updatePointlightPlacing();
	}
	if(_isEditorLoaded)
	{
		_updatePointlightEditing();
	}
	if(_isEditorLoaded)
	{
		_updateSpotlightMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSpotlightChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSpotlightPlacing();
	}
	if(_isEditorLoaded)
	{
		_updateSpotlightEditing();
	}
	if(_isEditorLoaded)
	{
		_updateReflectionMenu();
	}
	if(_isEditorLoaded)
	{
		_updateReflectionChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateReflectionPlacing();
	}
	if(_isEditorLoaded)
	{
		_updateReflectionEditing();
	}
	if(_isEditorLoaded)
	{
		_updateSoundMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSoundPlacingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSoundChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSoundPlacing();
	}
	if(_isEditorLoaded)
	{
		_updateSoundEditing();
	}
	if(_isEditorLoaded)
	{
		_updateSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateLightingSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateAmbientLightingSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateDirectionalLightingSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateShadowsGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateReflectionsGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateRefractionsGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateDofGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateFogGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateLensFlareGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSkyExposureGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateBloomGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateWorldCreating();
	}
	if(_isEditorLoaded)
	{
		_updateWorldChoosing();
	}
	if(_isEditorLoaded)
	{
		_updateWorldDeleting();
	}
	if(_isEditorLoaded)
	{
		_updateCamera();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}