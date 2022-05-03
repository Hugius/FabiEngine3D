#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "terrain_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void TerrainEditor::_load()
{
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

	_fe3d->graphics_setAntiAliasingEnabled(true);
	_fe3d->graphics_setAnisotropicFilteringQuality(16);
	_fe3d->graphics_setAmbientLightingEnabled(true);
	_fe3d->graphics_setAmbientLightingColor(fvec3(1.0f));
	_fe3d->graphics_setAmbientLightingIntensity(1.0f);
	_fe3d->graphics_setDirectionalLightingEnabled(true);
	_fe3d->graphics_setDirectionalLightingColor(fvec3(1.0f));
	_fe3d->graphics_setDirectionalLightingPosition(fvec3(10000.0f));
	_fe3d->graphics_setDirectionalLightingIntensity(3.0f);

	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d->camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonEnabled(true);
	_fe3d->camera_setThirdPersonYaw(INITIAL_CAMERA_YAW);
	_fe3d->camera_setThirdPersonPitch(INITIAL_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);
	_fe3d->camera_setThirdPersonLookat(fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));

	_gui->getOverlay()->createTextField("terrainId", fvec2(0.0f, 0.85f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
}

void TerrainEditor::_unload()
{
	for(const auto & terrainId : _loadedTerrainIds)
	{
		_fe3d->terrain_delete(terrainId);
	}

	_fe3d->model_delete("@@box");
	_fe3d->model_delete("@@grid");

	_fe3d->graphics_setAntiAliasingEnabled(false);
	_fe3d->graphics_setAnisotropicFilteringQuality(0);
	_fe3d->graphics_setAmbientLightingEnabled(false);
	_fe3d->graphics_setAmbientLightingColor(fvec3(0.0f));
	_fe3d->graphics_setAmbientLightingIntensity(0.0f);
	_fe3d->graphics_setDirectionalLightingEnabled(false);
	_fe3d->graphics_setDirectionalLightingColor(fvec3(0.0f));
	_fe3d->graphics_setDirectionalLightingPosition(fvec3(0.0f));
	_fe3d->graphics_setDirectionalLightingIntensity(0.0f);

	_fe3d->camera_reset();

	_gui->getOverlay()->deleteTextField("terrainId");

	_loadedTerrainIds.clear();
}

void TerrainEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	auto positions = Mathematics::calculateDistributedPositions(4, CH, false);
	leftWindow->createScreen("terrainEditorMenuMain");
	leftWindow->getScreen("terrainEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create Terrain"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Terrain", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Terrain"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Terrain", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), TEXT_SIZE("Delete Terrain"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Terrain", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(6, CH, false);
	leftWindow->createScreen("terrainEditorMenuChoice");
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("diffuseTexturing", fvec2(0.0f, positions[0]), TEXT_SIZE("Diffuse Texturing"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Diffuse Texturing", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("normalTexturing", fvec2(0.0f, positions[1]), TEXT_SIZE("Normal Texturing"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Normal Texturing", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("blendTexturing", fvec2(0.0f, positions[2]), TEXT_SIZE("Blend Texturing"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Blend Texturing", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("lighting", fvec2(0.0f, positions[3]), TEXT_SIZE("Lighting"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lighting", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("miscellaneous", fvec2(0.0f, positions[4]), TEXT_SIZE("Miscellaneous"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Miscellaneous", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[5]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(6, CH, false);
	leftWindow->createScreen("terrainEditorMenuDiffuseTexturing");
	leftWindow->getScreen("terrainEditorMenuDiffuseTexturing")->createButton("diffuseMap", fvec2(0.0f, positions[0]), TEXT_SIZE("Diffuse Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Diffuse Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuDiffuseTexturing")->createButton("redDiffuseMap", fvec2(0.0f, positions[1]), TEXT_SIZE("Red Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Red Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuDiffuseTexturing")->createButton("greenDiffuseMap", fvec2(0.0f, positions[2]), TEXT_SIZE("Green Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Green Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuDiffuseTexturing")->createButton("blueDiffuseMap", fvec2(0.0f, positions[3]), TEXT_SIZE("Blue Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Blue Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuDiffuseTexturing")->createButton("clearMaps", fvec2(0.0f, positions[4]), TEXT_SIZE("Clear Maps"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear Maps", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuDiffuseTexturing")->createButton("back", fvec2(0.0f, positions[5]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(6, CH, false);
	leftWindow->createScreen("terrainEditorMenuNormalTexturing");
	leftWindow->getScreen("terrainEditorMenuNormalTexturing")->createButton("normalMap", fvec2(0.0f, positions[0]), TEXT_SIZE("Normal Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Normal Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuNormalTexturing")->createButton("redNormalMap", fvec2(0.0f, positions[1]), TEXT_SIZE("Red Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Red Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuNormalTexturing")->createButton("greenNormalMap", fvec2(0.0f, positions[2]), TEXT_SIZE("Green Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Green Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuNormalTexturing")->createButton("blueNormalMap", fvec2(0.0f, positions[3]), TEXT_SIZE("Blue Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Blue Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuNormalTexturing")->createButton("clearMaps", fvec2(0.0f, positions[4]), TEXT_SIZE("Clear Maps"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear Maps", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuNormalTexturing")->createButton("back", fvec2(0.0f, positions[5]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(3, CH, false);
	leftWindow->createScreen("terrainEditorMenuBlendTexturing");
	leftWindow->getScreen("terrainEditorMenuBlendTexturing")->createButton("blendMap", fvec2(0.0f, positions[0]), TEXT_SIZE("Blend Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Blend Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuBlendTexturing")->createButton("clearMaps", fvec2(0.0f, positions[1]), TEXT_SIZE("Clear Maps"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear Maps", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuBlendTexturing")->createButton("back", fvec2(0.0f, positions[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(6, CH, false);
	leftWindow->createScreen("terrainEditorMenuLighting");
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("color", fvec2(0.0f, positions[0]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("lightness", fvec2(0.0f, positions[1]), TEXT_SIZE("Lightness"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lightness", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("isSpecular", fvec2(0.0f, positions[2]), TEXT_SIZE("Specular: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("specularShininess", fvec2(0.0f, positions[3]), TEXT_SIZE("Specular Shininess"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular Shininess", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("specularIntensity", fvec2(0.0f, positions[4]), TEXT_SIZE("Specular Intensity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("back", fvec2(0.0f, positions[5]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(6, CH, false);
	leftWindow->createScreen("terrainEditorMenuMiscellaneous");
	leftWindow->getScreen("terrainEditorMenuMiscellaneous")->createButton("maxHeight", fvec2(0.0f, positions[0]), TEXT_SIZE("Max Height"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Max Height", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMiscellaneous")->createButton("textureRepeat", fvec2(0.0f, positions[1]), TEXT_SIZE("Texture Repeat"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Texture Repeat", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMiscellaneous")->createButton("redTextureRepeat", fvec2(0.0f, positions[2]), TEXT_SIZE("Red Repeat"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Red Repeat", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMiscellaneous")->createButton("greenTextureRepeat", fvec2(0.0f, positions[3]), TEXT_SIZE("Green Repeat"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Green Repeat", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMiscellaneous")->createButton("blueTextureRepeat", fvec2(0.0f, positions[4]), TEXT_SIZE("Blue Repeat"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Blue Repeat", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMiscellaneous")->createButton("back", fvec2(0.0f, positions[5]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("terrainEditorMenuMain");
	rightWindow->setActiveScreen("empty");
}

void TerrainEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	leftWindow->deleteScreen("terrainEditorMenuMain");
	leftWindow->deleteScreen("terrainEditorMenuChoice");
	leftWindow->deleteScreen("terrainEditorMenuDiffuseTexturing");
	leftWindow->deleteScreen("terrainEditorMenuBlendTexturing");
	leftWindow->deleteScreen("terrainEditorMenuNormalTexturing");
	leftWindow->deleteScreen("terrainEditorMenuLighting");
	leftWindow->deleteScreen("terrainEditorMenuMiscellaneous");

	leftWindow->setActiveScreen("main");
	rightWindow->setActiveScreen("main");
}

void TerrainEditor::update()
{
	if(isLoaded())
	{
		_updateMainMenu();
	}
	if(isLoaded())
	{
		_updateChoiceMenu();
	}
	if(isLoaded())
	{
		_updateDiffuseMapMenu();
	}
	if(isLoaded())
	{
		_updateNormalMapMenu();
	}
	if(isLoaded())
	{
		_updateBlendMapMenu();
	}
	if(isLoaded())
	{
		_updateLightingMenu();
	}
	if(isLoaded())
	{
		_updateMiscellaneousMenu();
	}
	if(isLoaded())
	{
		_updateTerrainCreating();
	}
	if(isLoaded())
	{
		_updateTerrainChoosing();
	}
	if(isLoaded())
	{
		_updateTerrainDeleting();
	}
	if(isLoaded())
	{
		_updateCamera();
	}
	if(isLoaded())
	{
		_updateMiscellaneous();
	}
}