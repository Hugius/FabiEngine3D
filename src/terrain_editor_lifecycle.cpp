#define TW(text) (static_cast<float>(string(text).size()) * CW)

#include "terrain_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void TerrainEditor::load()
{
	_loadGUI();

	_fe3d->camera_reset();
	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d->camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d->camera_enableThirdPersonView(INITIAL_CAMERA_YAW, INITIAL_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);
	_fe3d->camera_setThirdPersonLookat(fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));

	_fe3d->gfx_enableAntiAliasing();
	_fe3d->gfx_setAnisotropicFilteringQuality(Config::MAX_ANISOTROPIC_FILTERING_QUALITY);
	_fe3d->gfx_enableAmbientLighting();
	_fe3d->gfx_setAmbientLightingColor(fvec3(1.0f));
	_fe3d->gfx_setAmbientLightingIntensity(1.0f);
	_fe3d->gfx_enableDirectionalLighting();
	_fe3d->gfx_setDirectionalLightingColor(fvec3(1.0f));
	_fe3d->gfx_setDirectionalLightingPosition(fvec3(10000.0f));
	_fe3d->gfx_setDirectionalLightingIntensity(3.0f);

	_fe3d->model_create("@@box", "engine\\assets\\mesh\\box.obj");
	_fe3d->model_setBasePosition("@@box", fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d->model_setDiffuseMap("@@box", "", "engine\\assets\\image\\diffuse_map\\box.tga");
	_fe3d->model_setFaceCulled("@@box", "", true);
	_fe3d->model_create("@@grid", "engine\\assets\\mesh\\plane.obj");
	_fe3d->model_setBasePosition("@@grid", fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d->model_setBaseSize("@@grid", fvec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d->model_setDiffuseMap("@@grid", "", "engine\\assets\\image\\diffuse_map\\grid.tga");
	_fe3d->model_setTextureRepeat("@@grid", "", GRID_REPEAT);
	_fe3d->model_setMinTextureAlpha("@@grid", "", 0.1f);
	_fe3d->model_setShadowed("@@grid", false);

	_gui->getOverlay()->createTextField("terrainId", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true);

	_isEditorLoaded = true;
}

void TerrainEditor::unload()
{
	for(const auto& id : _loadedTerrainIds)
	{
		_fe3d->terrain_delete(id);
	}

	_unloadGUI();

	_fe3d->gfx_disableAntiAliasing(true);
	_fe3d->gfx_setAnisotropicFilteringQuality(Config::MIN_ANISOTROPIC_FILTERING_QUALITY);
	_fe3d->gfx_disableAmbientLighting(true);
	_fe3d->gfx_disableDirectionalLighting(true);

	_fe3d->model_delete("@@box");
	_fe3d->model_delete("@@grid");

	_gui->getOverlay()->deleteTextField("terrainId");

	_loadedTerrainIds.clear();
	_currentTerrainId = "";
	_isEditorLoaded = false;
	_isCreatingTerrain = false;
	_isChoosingTerrain = false;
	_isDeletingTerrain = false;

	if(_fe3d->camera_isThirdPersonViewEnabled())
	{
		_fe3d->camera_disableThirdPersonView();
	}
}

void TerrainEditor::_loadGUI()
{
	auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = Math::calculateDistributedPositions(4, CH);
	leftWindow->createScreen("terrainEditorMenuMain");
	leftWindow->getScreen("terrainEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create Terrain"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Terrain", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit Terrain"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Terrain", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete Terrain"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Terrain", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(6, CH);
	leftWindow->createScreen("terrainEditorMenuChoice");
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("diffuseTexturing", fvec2(0.0f, positions[0]), fvec2(TW("Diffuse Texturing"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Diffuse Texturing", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("normalTexturing", fvec2(0.0f, positions[1]), fvec2(TW("Normal Texturing"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Normal Texturing", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("blendTexturing", fvec2(0.0f, positions[2]), fvec2(TW("Blend Texturing"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Blend Texturing", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("lighting", fvec2(0.0f, positions[3]), fvec2(TW("Lighting"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lighting", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("miscellaneous", fvec2(0.0f, positions[4]), fvec2(TW("Miscellaneous"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Miscellaneous", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[5]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(6, CH);
	leftWindow->createScreen("terrainEditorMenuDiffuseTexturing");
	leftWindow->getScreen("terrainEditorMenuDiffuseTexturing")->createButton("diffuseMap", fvec2(0.0f, positions[0]), fvec2(TW("Diffuse Map"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Diffuse Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuDiffuseTexturing")->createButton("redDiffuseMap", fvec2(0.0f, positions[1]), fvec2(TW("Red Map"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Red Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuDiffuseTexturing")->createButton("greenDiffuseMap", fvec2(0.0f, positions[2]), fvec2(TW("Green Map"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Green Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuDiffuseTexturing")->createButton("blueDiffuseMap", fvec2(0.0f, positions[3]), fvec2(TW("Blue Map"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Blue Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuDiffuseTexturing")->createButton("clearMaps", fvec2(0.0f, positions[4]), fvec2(TW("Clear Maps"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear Maps", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuDiffuseTexturing")->createButton("back", fvec2(0.0f, positions[5]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(6, CH);
	leftWindow->createScreen("terrainEditorMenuNormalTexturing");
	leftWindow->getScreen("terrainEditorMenuNormalTexturing")->createButton("normalMap", fvec2(0.0f, positions[0]), fvec2(TW("Normal Map"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Normal Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuNormalTexturing")->createButton("redNormalMap", fvec2(0.0f, positions[1]), fvec2(TW("Red Map"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Red Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuNormalTexturing")->createButton("greenNormalMap", fvec2(0.0f, positions[2]), fvec2(TW("Green Map"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Green Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuNormalTexturing")->createButton("blueNormalMap", fvec2(0.0f, positions[3]), fvec2(TW("Blue Map"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Blue Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuNormalTexturing")->createButton("clearMaps", fvec2(0.0f, positions[4]), fvec2(TW("Clear Maps"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear Maps", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuNormalTexturing")->createButton("back", fvec2(0.0f, positions[5]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(3, CH);
	leftWindow->createScreen("terrainEditorMenuBlendTexturing");
	leftWindow->getScreen("terrainEditorMenuBlendTexturing")->createButton("blendMap", fvec2(0.0f, positions[0]), fvec2(TW("Blend Map"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Blend Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuBlendTexturing")->createButton("clearMaps", fvec2(0.0f, positions[1]), fvec2(TW("Clear Maps"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear Maps", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuBlendTexturing")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(5, CH);
	leftWindow->createScreen("terrainEditorMenuLighting");
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("lightness", fvec2(0.0f, positions[0]), fvec2(TW("Lightness"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lightness", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("isSpecular", fvec2(0.0f, positions[1]), fvec2(TW("Specular: OFF"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("specularShininess", fvec2(0.0f, positions[2]), fvec2(TW("Specular Shininess"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular Shininess", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("specularIntensity", fvec2(0.0f, positions[3]), fvec2(TW("Specular Intensity"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("back", fvec2(0.0f, positions[4]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(6, CH);
	leftWindow->createScreen("terrainEditorMenuMiscellaneous");
	leftWindow->getScreen("terrainEditorMenuMiscellaneous")->createButton("maxHeight", fvec2(0.0f, positions[0]), fvec2(TW("Max Height"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Max Height", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMiscellaneous")->createButton("textureRepeat", fvec2(0.0f, positions[1]), fvec2(TW("Texture Repeat"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Texture Repeat", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMiscellaneous")->createButton("redTextureRepeat", fvec2(0.0f, positions[2]), fvec2(TW("Red Repeat"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Red Repeat", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMiscellaneous")->createButton("greenTextureRepeat", fvec2(0.0f, positions[3]), fvec2(TW("Green Repeat"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Green Repeat", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMiscellaneous")->createButton("blueTextureRepeat", fvec2(0.0f, positions[4]), fvec2(TW("Blue Repeat"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Blue Repeat", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMiscellaneous")->createButton("back", fvec2(0.0f, positions[5]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);
}

void TerrainEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("terrainEditorMenuMain");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("terrainEditorMenuChoice");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("terrainEditorMenuDiffuseTexturing");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("terrainEditorMenuBlendTexturing");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("terrainEditorMenuNormalTexturing");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("terrainEditorMenuLighting");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("terrainEditorMenuMiscellaneous");
}

void TerrainEditor::update()
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
		_updateDiffuseMapMenu();
	}
	if(_isEditorLoaded)
	{
		_updateNormalMapMenu();
	}
	if(_isEditorLoaded)
	{
		_updateBlendMapMenu();
	}
	if(_isEditorLoaded)
	{
		_updateLightingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneousMenu();
	}
	if(_isEditorLoaded)
	{
		_updateTerrainCreating();
	}
	if(_isEditorLoaded)
	{
		_updateTerrainChoosing();
	}
	if(_isEditorLoaded)
	{
		_updateTerrainDeleting();
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