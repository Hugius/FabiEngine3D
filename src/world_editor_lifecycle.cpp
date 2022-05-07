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
	_aabbEditor->loadAabbsFromFile();
	_animation3dEditor->loadAnimation3dsFromFile();
	_animation2dEditor->loadAnimation2dsFromFile();
	_sound2dEditor->loadSound2dsFromFile();

	_fe3d->model_create(TEMPLATE_POINTLIGHT_ID, TEMPLATE_POINTLIGHT_MODEL_PATH);
	_fe3d->model_create(TEMPLATE_SPOTLIGHT_ID, TEMPLATE_SPOTLIGHT_MODEL_PATH);
	_fe3d->model_create(TEMPLATE_CAPTOR_ID, TEMPLATE_CAPTOR_MODEL_PATH);
	_fe3d->model_create(TEMPLATE_SOUND3D_ID, TEMPLATE_SOUND3D_MODEL_PATH);
	_fe3d->model_setBaseSize(TEMPLATE_POINTLIGHT_ID, DEFAULT_POINTLIGHT_SIZE);
	_fe3d->model_setBaseSize(TEMPLATE_SPOTLIGHT_ID, DEFAULT_SPOTLIGHT_SIZE);
	_fe3d->model_setBaseSize(TEMPLATE_CAPTOR_ID, DEFAULT_CAPTOR_SIZE);
	_fe3d->model_setBaseSize(TEMPLATE_SOUND3D_ID, DEFAULT_SOUND3D_SIZE);
	_fe3d->model_setBaseRotation(TEMPLATE_SPOTLIGHT_ID, DEFAULT_SPOTLIGHT_ROTATION);
	_fe3d->model_setShadowed(TEMPLATE_POINTLIGHT_ID, false);
	_fe3d->model_setShadowed(TEMPLATE_SPOTLIGHT_ID, false);
	_fe3d->model_setShadowed(TEMPLATE_CAPTOR_ID, false);
	_fe3d->model_setShadowed(TEMPLATE_SOUND3D_ID, false);
	_fe3d->model_setReflected(TEMPLATE_POINTLIGHT_ID, false);
	_fe3d->model_setReflected(TEMPLATE_SPOTLIGHT_ID, false);
	_fe3d->model_setReflected(TEMPLATE_CAPTOR_ID, false);
	_fe3d->model_setReflected(TEMPLATE_SOUND3D_ID, false);
	_fe3d->model_setRefracted(TEMPLATE_POINTLIGHT_ID, false);
	_fe3d->model_setRefracted(TEMPLATE_SPOTLIGHT_ID, false);
	_fe3d->model_setRefracted(TEMPLATE_CAPTOR_ID, false);
	_fe3d->model_setRefracted(TEMPLATE_SOUND3D_ID, false);
	_fe3d->model_setVisible(TEMPLATE_POINTLIGHT_ID, false);
	_fe3d->model_setVisible(TEMPLATE_SPOTLIGHT_ID, false);
	_fe3d->model_setVisible(TEMPLATE_CAPTOR_ID, false);
	_fe3d->model_setVisible(TEMPLATE_SOUND3D_ID, false);

	_fe3d->pointlight_create(TEMPLATE_POINTLIGHT_ID);
	_fe3d->pointlight_setRadius(TEMPLATE_POINTLIGHT_ID, fvec3(DEFAULT_POINTLIGHT_RADIUS));
	_fe3d->pointlight_setIntensity(TEMPLATE_POINTLIGHT_ID, DEFAULT_POINTLIGHT_INTENSITY);
	_fe3d->pointlight_setVisible(TEMPLATE_POINTLIGHT_ID, false);

	_fe3d->spotlight_create(TEMPLATE_SPOTLIGHT_ID);
	_fe3d->spotlight_setPitch(TEMPLATE_SPOTLIGHT_ID, DEFAULT_SPOTLIGHT_PITCH);
	_fe3d->spotlight_setIntensity(TEMPLATE_SPOTLIGHT_ID, DEFAULT_SPOTLIGHT_INTENSITY);
	_fe3d->spotlight_setAngle(TEMPLATE_SPOTLIGHT_ID, DEFAULT_SPOTLIGHT_ANGLE);
	_fe3d->spotlight_setDistance(TEMPLATE_SPOTLIGHT_ID, DEFAULT_SPOTLIGHT_DISTANCE);
	_fe3d->spotlight_setVisible(TEMPLATE_SPOTLIGHT_ID, false);

	_fe3d->captor_create(TEMPLATE_CAPTOR_ID);

	for(const auto & sound2dId : _sound2dEditor->getLoadedSound2dIds())
	{
		_fe3d->sound3d_create(sound2dId, _fe3d->sound2d_getAudioPath(sound2dId));
		_fe3d->sound3d_setMaxVolume(sound2dId, DEFAULT_SOUND3D_MAX_VOLUME);
		_fe3d->sound3d_setMaxDistance(sound2dId, DEFAULT_SOUND3D_MAX_DISTANCE);
	}

	_fe3d->model_create("@@grid", "engine\\assets\\mesh\\plane.obj");
	_fe3d->model_setBaseSize("@@grid", fvec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d->model_setDiffuseMap("@@grid", "", "engine\\assets\\image\\diffuse_map\\grid.tga");
	_fe3d->model_setTextureRepeat("@@grid", "", GRID_REPEAT);
	_fe3d->model_setMinTextureAlpha("@@grid", "", 0.1f);
	_fe3d->model_setShadowed("@@grid", false);

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

	for(const auto & sound2dId : _sound2dEditor->getLoadedSound2dIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuSound3dPlace")->getScrollingList("templateSound3ds")->createOption(sound2dId, sound2dId.substr(1));
	}

	_gui->getOverlay()->createTextField("selectedId", fvec2(0.0f, 0.0f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
	_gui->getOverlay()->createTextField("activeId", fvec2(0.0f, 0.0f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
}

void WorldEditor::_unload()
{
	const auto sound2dIds = _sound2dEditor->getLoadedSound2dIds();

	_skyEditor->deleteLoadedSkies();
	_terrainEditor->deleteLoadedTerrains();
	_waterEditor->deleteLoadedWaters();
	_modelEditor->deleteLoadedModels();
	_quad3dEditor->deleteLoadedQuad3ds();
	_text3dEditor->deleteLoadedText3ds();
	_aabbEditor->deleteLoadedAabbs();
	_animation3dEditor->deleteLoadedAnimation3ds();
	_animation2dEditor->deleteLoadedAnimation2ds();
	_sound2dEditor->deleteLoadedSound2ds();

	_fe3d->model_delete(TEMPLATE_POINTLIGHT_ID);
	_fe3d->model_delete(TEMPLATE_SPOTLIGHT_ID);
	_fe3d->model_delete(TEMPLATE_CAPTOR_ID);
	_fe3d->model_delete(TEMPLATE_SOUND3D_ID);

	_fe3d->pointlight_delete(TEMPLATE_POINTLIGHT_ID);

	_fe3d->spotlight_delete(TEMPLATE_SPOTLIGHT_ID);

	_fe3d->captor_delete(TEMPLATE_CAPTOR_ID);

	for(const auto & sound2dId : sound2dIds)
	{
		_fe3d->sound3d_delete(sound2dId);
	}

	_fe3d->model_delete("@@grid");

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