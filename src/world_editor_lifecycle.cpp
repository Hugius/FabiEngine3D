#include "world_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

void WorldEditor::_load()
{
	_fe3d->camera_reset();

	_fe3d->graphics_setAntiAliasingEnabled(true);
	_fe3d->graphics_setAnisotropicFilteringQuality(16);

	_skyEditor->loadEntitiesFromFile();

	_terrainEditor->loadEntitiesFromFile();

	_waterEditor->loadEntitiesFromFile();

	_modelEditor->loadEntitiesFromFile();
	for(const auto & id : _modelEditor->getLoadedEntityIds())
	{
		auto screen = _gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuModelPlace");
		screen->getScrollingList("modelList")->createOption(id, id.substr(1));
	}

	_quad3dEditor->loadEntitiesFromFile();
	for(const auto & id : _quad3dEditor->getLoadedEntityIds())
	{
		auto screen = _gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuQuad3dPlace");
		screen->getScrollingList("quadList")->createOption(id, id.substr(1));
	}

	_text3dEditor->loadEntitiesFromFile();
	for(const auto & id : _text3dEditor->getLoadedEntityIds())
	{
		auto screen = _gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuText3dPlace");
		screen->getScrollingList("textList")->createOption(id, id.substr(1));
	}

	_animation2dEditor->loadAnimationsFromFile();
	_animation3dEditor->loadAnimationsFromFile();

	_fe3d->model_create(TEMPLATE_LAMP_ID, LAMP_MODEL_PATH);
	_fe3d->model_setBaseSize(TEMPLATE_LAMP_ID, DEFAULT_LAMP_SIZE);
	_fe3d->model_setShadowed(TEMPLATE_LAMP_ID, false);
	_fe3d->model_setReflected(TEMPLATE_LAMP_ID, false);
	_fe3d->model_setVisible(TEMPLATE_LAMP_ID, false);
	_fe3d->pointlight_create(TEMPLATE_POINTLIGHT_ID);
	_fe3d->pointlight_setRadius(TEMPLATE_POINTLIGHT_ID, fvec3(DEFAULT_POINTLIGHT_RADIUS));
	_fe3d->pointlight_setIntensity(TEMPLATE_POINTLIGHT_ID, DEFAULT_POINTLIGHT_INTENSITY);
	_fe3d->pointlight_setVisible(TEMPLATE_POINTLIGHT_ID, false);

	_fe3d->model_create(TEMPLATE_TORCH_ID, TORCH_MODEL_PATH);
	_fe3d->model_setBaseRotation(TEMPLATE_TORCH_ID, DEFAULT_TORCH_ROTATION);
	_fe3d->model_setBaseSize(TEMPLATE_TORCH_ID, DEFAULT_TORCH_SIZE);
	_fe3d->model_setShadowed(TEMPLATE_TORCH_ID, false);
	_fe3d->model_setReflected(TEMPLATE_TORCH_ID, false);
	_fe3d->model_setVisible(TEMPLATE_TORCH_ID, false);
	_fe3d->spotlight_create(TEMPLATE_SPOTLIGHT_ID);
	_fe3d->spotlight_setPitch(TEMPLATE_SPOTLIGHT_ID, DEFAULT_SPOTLIGHT_PITCH);
	_fe3d->spotlight_setIntensity(TEMPLATE_SPOTLIGHT_ID, DEFAULT_SPOTLIGHT_INTENSITY);
	_fe3d->spotlight_setAngle(TEMPLATE_SPOTLIGHT_ID, DEFAULT_SPOTLIGHT_ANGLE);
	_fe3d->spotlight_setDistance(TEMPLATE_SPOTLIGHT_ID, DEFAULT_SPOTLIGHT_DISTANCE);
	_fe3d->spotlight_setVisible(TEMPLATE_SPOTLIGHT_ID, false);

	_fe3d->model_create(TEMPLATE_CAMERA_ID, CAMERA_MODEL_PATH);
	_fe3d->model_setBaseSize(TEMPLATE_CAMERA_ID, DEFAULT_CAMERA_SIZE);
	_fe3d->model_setShadowed(TEMPLATE_CAMERA_ID, false);
	_fe3d->model_setReflected(TEMPLATE_CAMERA_ID, false);
	_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);
	_fe3d->captor_create(TEMPLATE_CAPTOR_ID);
	_fe3d->captor_setVisible(TEMPLATE_CAPTOR_ID, false);

	_soundEditor->loadSoundsFromFile();
	_fe3d->model_create(TEMPLATE_SPEAKER_ID, SPEAKER_MODEL_PATH);
	_fe3d->model_setBaseSize(TEMPLATE_SPEAKER_ID, DEFAULT_SPEAKER_SIZE);
	_fe3d->model_setShadowed(TEMPLATE_SPEAKER_ID, false);
	_fe3d->model_setReflected(TEMPLATE_SPEAKER_ID, false);
	_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);
	for(const auto & id : _soundEditor->getLoadedSoundIds())
	{
		_fe3d->sound3d_create(id, _fe3d->sound2d_getAudioPath(id));
		_fe3d->sound3d_setMaxVolume(id, DEFAULT_SOUND_MAX_VOLUME);
		_fe3d->sound3d_setMaxDistance(id, DEFAULT_SOUND_MAX_DISTANCE);

		auto screen = _gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuSoundPlace");
		screen->getScrollingList("soundList")->createOption(id, id.substr(1));
	}

	_gui->getOverlay()->createTextField("selectedId", fvec2(0.0f, 0.0f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
	_gui->getOverlay()->createTextField("activeId", fvec2(0.0f, 0.0f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);

	_fe3d->collision_setCameraAabbResponseEnabled(true, true, true);

	_fe3d->raycast_setAabbIntersectionEnabled(true);

	_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");
}

void WorldEditor::_unload()
{
	_fe3d->graphics_setAntiAliasingEnabled(false);
	_fe3d->graphics_setAnisotropicFilteringQuality(0);

	_fe3d->model_delete(TEMPLATE_LAMP_ID);
	_fe3d->model_delete(TEMPLATE_TORCH_ID);
	_fe3d->model_delete(TEMPLATE_CAMERA_ID);
	_fe3d->model_delete(TEMPLATE_SPEAKER_ID);

	_fe3d->pointlight_delete(TEMPLATE_POINTLIGHT_ID);
	_fe3d->spotlight_delete(TEMPLATE_SPOTLIGHT_ID);
	_fe3d->captor_delete(TEMPLATE_CAPTOR_ID);

	for(const auto & id : _soundEditor->getLoadedSoundIds())
	{
		_fe3d->sound3d_delete(id);
	}

	_skyEditor->deleteLoadedEntities();
	_terrainEditor->deleteLoadedEntities();
	_waterEditor->deleteLoadedEntities();
	_modelEditor->deleteLoadedEntities();
	_quad3dEditor->deleteLoadedEntities();
	_text3dEditor->deleteLoadedEntities();
	_animation3dEditor->deleteLoadedAnimations();
	_animation2dEditor->deleteLoadedAnimations();
	_soundEditor->deleteLoadedSounds();

	_gui->getOverlay()->deleteTextField("selectedId");
	_gui->getOverlay()->deleteTextField("activeId");

	_fe3d->collision_setCameraAabbResponseEnabled(false, false, false);

	_fe3d->raycast_setAabbIntersectionEnabled(false);

	_loadedModelIds.clear();
	_loadedQuadIds.clear();
	_loadedTextIds.clear();
	_loadedSoundIds.clear();
	_loadedAabbIds.clear();
	_loadedPointlightIds.clear();
	_loadedSpotlightIds.clear();
	_loadedCaptorIds.clear();
	_currentTemplateModelId = "";
	_selectedModelId = "";
	_activeModelId = "";
	_currentTemplateQuadId = "";
	_selectedQuadId = "";
	_activeQuadId = "";
	_currentTemplateTextId = "";
	_selectedTextId = "";
	_activeTextId = "";
	_selectedPointlightId = "";
	_activePointlightId = "";
	_selectedSpotlightId = "";
	_activeSpotlightId = "";
	_selectedCaptorId = "";
	_activeCaptorId = "";
	_currentTemplateSoundId = "";
	_selectedSoundId = "";
	_activeSoundId = "";
	_loadedWorldId = "";
	_currentWorldId = "";
	_editorSpeed = 1.0f;
	_selectedModelHighlightDirection = 1;
	_activeModelHighlightDirection = 1;
	_selectedQuad3dHighlightDirection = 1;
	_activeQuad3dHighlightDirection = 1;
	_selectedText3dHighlightDirection = 1;
	_activeText3dHighlightDirection = 1;
	_selectedPointlightHighlightDirection = 1;
	_activePointlightHighlightDirection = 1;
	_selectedSpotlightHighlightDirection = 1;
	_activeSpotlightHighlightDirection = 1;
	_selectedCaptorHighlightDirection = 1;
	_activeCaptorHighlightDirection = 1;
	_selectedSoundHighlightDirection = 1;
	_activeSoundHighlightDirection = 1;
	_dontResetSelectedModel = false;
	_dontResetSelectedQuad3d = false;
	_dontResetSelectedText3d = false;
	_dontResetSelectedPointlight = false;
	_dontResetSelectedSpotlight = false;
	_dontResetSelectedCaptor = false;
	_dontResetSelectedSound = false;
	_isPlacingPointlight = false;
	_isPlacingSpotlight = false;
	_isPlacingCaptor = false;
	_isWireframeModeEnabled = false;
	_isAabbModeEnabled = false;
}

void WorldEditor::update()
{
	if(isLoaded())
	{
		_updateMainMenu();
	}
	if(isLoaded())
	{
		_updateWorldCreating();
	}
	if(isLoaded())
	{
		_updateWorldChoosing();
	}
	if(isLoaded())
	{
		_updateWorldDeleting();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateChoiceMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateModelPlacing();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateQuad3dPlacing();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateText3dPlacing();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updatePointlightPlacing();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSpotlightPlacing();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateCaptorPlacing();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSoundPlacing();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSkyMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateTerrainMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateWaterMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateModelMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateQuad3dMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateText3dMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updatePointlightMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSpotlightMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateCaptorMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSoundMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateModelPlacingMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateQuad3dPlacingMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateText3dPlacingMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSoundPlacingMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateModelChoosingMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateQuad3dChoosingMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateText3dChoosingMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updatePointlightChoosingMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSpotlightChoosingMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateCaptorChoosingMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSoundChoosingMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateModelEditing();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateQuad3dEditing();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateText3dEditing();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updatePointlightEditing();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSpotlightEditing();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateCaptorEditing();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSoundEditing();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateLightingSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateAmbientLightingSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateDirectionalLightingSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateGraphicsSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateShadowsGraphicsSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateReflectionsGraphicsSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateRefractionsGraphicsSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateDofGraphicsSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateFogGraphicsSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateLensFlareGraphicsSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSkyExposureGraphicsSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateBloomGraphicsSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateCamera();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateMiscellaneous();
	}
}