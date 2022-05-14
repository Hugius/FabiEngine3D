#include "world_editor.hpp"
#include "configuration.hpp"

void WorldEditor::_load()
{
	_skyEditor->loadSkiesFromFile();
	_terrainEditor->loadTerrainsFromFile();
	_waterEditor->loadWatersFromFile();
	_modelEditor->loadModelsFromFile();
	_quad3dEditor->loadQuad3dsFromFile();
	_text3dEditor->loadText3dsFromFile();
	_animation3dEditor->loadAnimation3dsFromFile();
	_animation2dEditor->loadAnimation2dsFromFile();
	_aabbEditor->loadAabbsFromFile();
	_pointlightEditor->loadPointlightsFromFile();
	_spotlightEditor->loadSpotlightsFromFile();
	_sound3dEditor->loadSound3dsFromFile();

	_fe3d->model_create(POINTLIGHT_MODEL_ID, POINTLIGHT_MODEL_PATH);
	_fe3d->model_create(SPOTLIGHT_MODEL_ID, SPOTLIGHT_MODEL_PATH);
	_fe3d->model_create(CAPTOR_MODEL_ID, CAPTOR_MODEL_PATH);
	_fe3d->model_create(SOUND3D_MODEL_ID, SOUND3D_MODEL_PATH);
	_fe3d->model_setBaseSize(POINTLIGHT_MODEL_ID, POINTLIGHT_MODEL_SIZE);
	_fe3d->model_setBaseSize(SPOTLIGHT_MODEL_ID, SPOTLIGHT_MODEL_SIZE);
	_fe3d->model_setBaseSize(CAPTOR_MODEL_ID, CAPTOR_MODEL_SIZE);
	_fe3d->model_setBaseSize(SOUND3D_MODEL_ID, SOUND3D_MODEL_SIZE);
	_fe3d->model_setBaseRotation(SPOTLIGHT_MODEL_ID, SPOTLIGHT_MODEL_ROTATION);
	_fe3d->model_setShadowed(POINTLIGHT_MODEL_ID, false);
	_fe3d->model_setShadowed(SPOTLIGHT_MODEL_ID, false);
	_fe3d->model_setShadowed(CAPTOR_MODEL_ID, false);
	_fe3d->model_setShadowed(SOUND3D_MODEL_ID, false);
	_fe3d->model_setReflected(POINTLIGHT_MODEL_ID, false);
	_fe3d->model_setReflected(SPOTLIGHT_MODEL_ID, false);
	_fe3d->model_setReflected(CAPTOR_MODEL_ID, false);
	_fe3d->model_setReflected(SOUND3D_MODEL_ID, false);
	_fe3d->model_setRefracted(POINTLIGHT_MODEL_ID, false);
	_fe3d->model_setRefracted(SPOTLIGHT_MODEL_ID, false);
	_fe3d->model_setRefracted(CAPTOR_MODEL_ID, false);
	_fe3d->model_setRefracted(SOUND3D_MODEL_ID, false);
	_fe3d->model_setVisible(POINTLIGHT_MODEL_ID, false);
	_fe3d->model_setVisible(SPOTLIGHT_MODEL_ID, false);
	_fe3d->model_setVisible(CAPTOR_MODEL_ID, false);
	_fe3d->model_setVisible(SOUND3D_MODEL_ID, false);

	_fe3d->pointlight_create(POINTLIGHT_MODEL_ID);
	_fe3d->pointlight_setRadius(POINTLIGHT_MODEL_ID, fvec3(POINTLIGHT_RADIUS));
	_fe3d->pointlight_setIntensity(POINTLIGHT_MODEL_ID, POINTLIGHT_INTENSITY);
	_fe3d->pointlight_setVisible(POINTLIGHT_MODEL_ID, false);

	_fe3d->spotlight_create(SPOTLIGHT_MODEL_ID);
	_fe3d->spotlight_setPitch(SPOTLIGHT_MODEL_ID, SPOTLIGHT_PITCH);
	_fe3d->spotlight_setIntensity(SPOTLIGHT_MODEL_ID, SPOTLIGHT_INTENSITY);
	_fe3d->spotlight_setAngle(SPOTLIGHT_MODEL_ID, SPOTLIGHT_ANGLE);
	_fe3d->spotlight_setDistance(SPOTLIGHT_MODEL_ID, SPOTLIGHT_DISTANCE);
	_fe3d->spotlight_setVisible(SPOTLIGHT_MODEL_ID, false);

	_fe3d->captor_create(CAPTOR_MODEL_ID);

	for(const auto & sound3dId : _sound3dEditor->getLoadedSound3dIds())
	{
		_fe3d->sound3d_create(sound3dId, _fe3d->sound3d_getAudioPath(sound3dId));
		_fe3d->sound3d_setMaxVolume(sound3dId, SOUND3D_MAX_VOLUME);
		_fe3d->sound3d_setMaxDistance(sound3dId, SOUND3D_MAX_DISTANCE);
	}

	_fe3d->model_create(GRID_ID, GRID_MESH_PATH);
	_fe3d->model_setBaseSize(GRID_ID, fvec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d->model_setDiffuseMap(GRID_ID, "", GRID_TEXTURE_PATH);
	_fe3d->model_setTextureRepeat(GRID_ID, "", GRID_REPEAT);
	_fe3d->model_setMinTextureAlpha(GRID_ID, "", GRID_MIN_TEXTURE_ALPHA);
	_fe3d->model_setLightness(GRID_ID, "", GRID_LIGHTNESS);
	_fe3d->model_setShadowed(GRID_ID, false);

	_fe3d->graphics_setAntiAliasingEnabled(true);
	_fe3d->graphics_setAnisotropicFilteringQuality(16);
	_fe3d->collision_setCameraAabbResponseEnabled(true, true, true);
	_fe3d->raycast_setAabbIntersectionEnabled(true);

	for(const auto & skyId : _skyEditor->getLoadedSkyIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuSkyPlace")->getScrollingList("templateSkies")->createOption(skyId, skyId.substr(1));
	}

	for(const auto & terrainId : _terrainEditor->getLoadedTerrainIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuTerrainPlace")->getScrollingList("templateTerrains")->createOption(terrainId, terrainId.substr(1));
	}

	for(const auto & waterId : _waterEditor->getLoadedWaterIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuWaterPlace")->getScrollingList("templateWaters")->createOption(waterId, waterId.substr(1));
	}

	for(const auto & modelId : _modelEditor->getLoadedModelIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuModelPlace")->getScrollingList("templateModels")->createOption(modelId, modelId.substr(1));
	}

	for(const auto & quad3dId : _quad3dEditor->getLoadedQuad3dIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuQuad3dPlace")->getScrollingList("templateQuad3ds")->createOption(quad3dId, quad3dId.substr(1));
	}

	for(const auto & text3dId : _text3dEditor->getLoadedText3dIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuText3dPlace")->getScrollingList("templateText3ds")->createOption(text3dId, text3dId.substr(1));
	}

	for(const auto & aabbId : _aabbEditor->getLoadedAabbIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuAabbPlace")->getScrollingList("templateAabbs")->createOption(aabbId, aabbId.substr(1));
	}

	for(const auto & pointlightId : _pointlightEditor->getLoadedPointlightIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuPointlightPlace")->getScrollingList("templatePointlights")->createOption(pointlightId, pointlightId.substr(1));
	}

	for(const auto & sound3dId : _sound3dEditor->getLoadedSound3dIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuSound3dPlace")->getScrollingList("templateSound3ds")->createOption(sound3dId, sound3dId.substr(1));
	}

	_gui->getOverlay()->createTextField("selectedId", fvec2(0.0f, 0.0f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
	_gui->getOverlay()->createTextField("activeId", fvec2(0.0f, 0.0f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
}

void WorldEditor::_unload()
{
	const auto sound3dIds = _sound3dEditor->getLoadedSound3dIds();

	_skyEditor->deleteLoadedSkies();
	_terrainEditor->deleteLoadedTerrains();
	_waterEditor->deleteLoadedWaters();
	_modelEditor->deleteLoadedModels();
	_quad3dEditor->deleteLoadedQuad3ds();
	_text3dEditor->deleteLoadedText3ds();
	_animation3dEditor->deleteLoadedAnimation3ds();
	_animation2dEditor->deleteLoadedAnimation2ds();
	_aabbEditor->deleteLoadedAabbs();
	_pointlightEditor->deleteLoadedPointlights();
	_spotlightEditor->deleteLoadedSpotlights();
	_sound3dEditor->deleteLoadedSound3ds();

	_fe3d->model_delete(POINTLIGHT_MODEL_ID);
	_fe3d->model_delete(SPOTLIGHT_MODEL_ID);
	_fe3d->model_delete(CAPTOR_MODEL_ID);
	_fe3d->model_delete(SOUND3D_MODEL_ID);

	_fe3d->pointlight_delete(POINTLIGHT_MODEL_ID);

	_fe3d->spotlight_delete(SPOTLIGHT_MODEL_ID);

	_fe3d->captor_delete(CAPTOR_MODEL_ID);

	for(const auto & sound3dId : sound3dIds)
	{
		_fe3d->sound3d_delete(sound3dId);
	}

	_fe3d->model_delete(GRID_ID);

	_fe3d->graphics_setAntiAliasingEnabled(false);
	_fe3d->graphics_setAnisotropicFilteringQuality(0);

	_fe3d->collision_setCameraAabbResponseEnabled(false, false, false);

	_fe3d->raycast_setAabbIntersectionEnabled(false);

	_gui->getOverlay()->deleteTextField("selectedId");
	_gui->getOverlay()->deleteTextField("activeId");
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
		_updateAabbPlacing();
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
		_updateSound3dPlacing();
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
		_updateAabbMenu();
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
		_updateSound3dMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSkyPlacingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateTerrainPlacingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateWaterPlacingMenu();
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
		_updateAabbPlacingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updatePointlightPlacingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSound3dPlacingMenu();
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
		_updateAabbChoosingMenu();
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
		_updateSound3dChoosingMenu();
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
		_updateAabbEditing();
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
		_updateSound3dEditing();
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