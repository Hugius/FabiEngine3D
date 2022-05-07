#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "model_editor.hpp"
#include "configuration.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

void ModelEditor::_load()
{
	_skyEditor->loadSkiesFromFile();

	_fe3d->model_create("@@box", "engine\\assets\\mesh\\box.obj");
	_fe3d->model_setDiffuseMap("@@box", "", "engine\\assets\\image\\diffuse_map\\box.tga");
	_fe3d->model_setFaceCulled("@@box", "", true);
	_fe3d->model_create("@@grid", "engine\\assets\\mesh\\plane.obj");
	_fe3d->model_setBaseSize("@@grid", fvec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d->model_setDiffuseMap("@@grid", "", "engine\\assets\\image\\diffuse_map\\grid.tga");
	_fe3d->model_setTextureRepeat("@@grid", "", GRID_REPEAT);
	_fe3d->model_setMinTextureAlpha("@@grid", "", 0.1f);
	_fe3d->model_setShadowed("@@grid", false);

	_fe3d->captor_create("@@captor");
	_fe3d->captor_capture("@@captor");

	_fe3d->graphics_setAntiAliasingEnabled(true);
	_fe3d->graphics_setAnisotropicFilteringQuality(16);
	_fe3d->graphics_setAmbientLightingEnabled(true);
	_fe3d->graphics_setAmbientLightingColor(fvec3(1.0f));
	_fe3d->graphics_setAmbientLightingIntensity(1.0f);
	_fe3d->graphics_setDirectionalLightingEnabled(true);
	_fe3d->graphics_setDirectionalLightingColor(fvec3(1.0f));
	_fe3d->graphics_setDirectionalLightingPosition(fvec3(10000.0f));
	_fe3d->graphics_setDirectionalLightingIntensity(3.0f);
	_fe3d->graphics_setBloomEnabled(true);
	_fe3d->graphics_setBloomType(BloomType::PARTS);
	_fe3d->graphics_setBloomIntensity(1.0f);
	_fe3d->graphics_setBloomBlurCount(5);
	_fe3d->graphics_setBloomQuality(5);
	_fe3d->graphics_setShadowsEnabled(true);
	_fe3d->graphics_setShadowLightness(0.25f);
	_fe3d->graphics_setShadowQuality(16384);
	_fe3d->graphics_setShadowPositionOffset(fvec3(GRID_SIZE / 2.0f));
	_fe3d->graphics_setShadowSize(Mathematics::calculateMagnitude(fvec3(GRID_SIZE / 2.0f)));
	_fe3d->graphics_setCubeReflectionQuality(1024);
	_fe3d->graphics_setCubeRefractionQuality(1024);
	_fe3d->graphics_setPlanarReflectionQuality(1024);
	_fe3d->graphics_setPlanarRefractionQuality(1024);

	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d->camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonEnabled(true);
	_fe3d->camera_setThirdPersonYaw(INITIAL_CAMERA_YAW);
	_fe3d->camera_setThirdPersonPitch(INITIAL_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);

	_gui->getOverlay()->createTextField("modelId", fvec2(0.0f, 0.85f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
	_gui->getOverlay()->createTextField("aabbId", fvec2(0.0f, 0.75f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
}

void ModelEditor::_unload()
{
	_skyEditor->deleteLoadedSkies();

	for(const auto & modelId : _loadedModelIds)
	{
		_fe3d->model_delete(modelId);
	}

	_fe3d->graphics_setAntiAliasingEnabled(false);
	_fe3d->graphics_setAnisotropicFilteringQuality(0);
	_fe3d->graphics_setAmbientLightingEnabled(false);
	_fe3d->graphics_setAmbientLightingColor(fvec3(0.0f));
	_fe3d->graphics_setAmbientLightingIntensity(0.0f);
	_fe3d->graphics_setDirectionalLightingEnabled(false);
	_fe3d->graphics_setDirectionalLightingColor(fvec3(0.0f));
	_fe3d->graphics_setDirectionalLightingPosition(fvec3(0.0f));
	_fe3d->graphics_setDirectionalLightingIntensity(0.0f);
	_fe3d->graphics_setBloomEnabled(false);
	_fe3d->graphics_setBloomType(BloomType::EVERYTHING);
	_fe3d->graphics_setBloomIntensity(0.0f);
	_fe3d->graphics_setBloomBlurCount(0);
	_fe3d->graphics_setBloomQuality(0);
	_fe3d->graphics_setShadowsEnabled(false);
	_fe3d->graphics_setShadowLightness(0.0f);
	_fe3d->graphics_setShadowQuality(0);
	_fe3d->graphics_setCubeReflectionQuality(0);
	_fe3d->graphics_setCubeRefractionQuality(0);
	_fe3d->graphics_setPlanarReflectionQuality(0);
	_fe3d->graphics_setPlanarRefractionQuality(0);

	_fe3d->camera_reset();

	_fe3d->model_delete("@@box");
	_fe3d->model_delete("@@grid");

	_fe3d->captor_delete("@@captor");

	_gui->getOverlay()->deleteTextField("modelId");
	_gui->getOverlay()->deleteTextField("aabbId");

	_loadedModelIds.clear();
}

void ModelEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	auto positions = Mathematics::calculateDistributedPositions(5, CH, false);
	leftWindow->createScreen("modelEditorMenuMain");
	leftWindow->getScreen("modelEditorMenuMain")->createButton("sky", fvec2(0.0f, positions[0]), TEXT_SIZE("Select Sky"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Select Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMain")->createButton("create", fvec2(0.0f, positions[1]), TEXT_SIZE("Create Model"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[2]), TEXT_SIZE("Edit Model"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[3]), TEXT_SIZE("Delete Model"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMain")->createButton("back", fvec2(0.0f, positions[4]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(6, CH, false);
	leftWindow->createScreen("modelEditorMenuChoice");
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("part", fvec2(0.0f, positions[0]), TEXT_SIZE("Select Part"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Select Part", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("texturing", fvec2(0.0f, positions[1]), TEXT_SIZE("Texturing"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Texturing", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("lighting", fvec2(0.0f, positions[2]), TEXT_SIZE("Lighting"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lighting", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("miscellaneous", fvec2(0.0f, positions[3]), TEXT_SIZE("Miscellaneous"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Miscellaneous", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("aabb", fvec2(0.0f, positions[4]), TEXT_SIZE("AABB"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "AABB", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[5]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(9, CH, false);
	leftWindow->createScreen("modelEditorMenuTexturing");
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("diffuseMap", fvec2(0.0f, positions[0]), TEXT_SIZE("Diffuse Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Diffuse Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("emissionMap", fvec2(0.0f, positions[1]), TEXT_SIZE("Emission Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Emission Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("specularMap", fvec2(0.0f, positions[2]), TEXT_SIZE("Specular Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("reflectionMap", fvec2(0.0f, positions[3]), TEXT_SIZE("Reflection Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Reflection Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("refractionMap", fvec2(0.0f, positions[4]), TEXT_SIZE("Refraction Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Refraction Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("normalMap", fvec2(0.0f, positions[5]), TEXT_SIZE("Normal Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Normal Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("clearMaps", fvec2(0.0f, positions[6]), TEXT_SIZE("Clear Maps"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear Maps", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("textureRepeat", fvec2(0.0f, positions[7]), TEXT_SIZE("Texture Repeat"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Texture Repeat", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("back", fvec2(0.0f, positions[8]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(17, CH, false);
	leftWindow->createScreen("modelEditorMenuLighting");
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("color", fvec2(0.0f, positions[0]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("lightness", fvec2(0.0f, positions[1]), TEXT_SIZE("Lightness"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lightness", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("isSpecular", fvec2(0.0f, positions[2]), TEXT_SIZE("Specular: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("specularShininess", fvec2(0.0f, positions[3]), TEXT_SIZE("Specular Shininess"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular Shininess", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("specularIntensity", fvec2(0.0f, positions[4]), TEXT_SIZE("Specular Intensity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("isReflective", fvec2(0.0f, positions[5]), TEXT_SIZE("Reflective: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Reflective: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("isRefractive", fvec2(0.0f, positions[6]), TEXT_SIZE("Refractive: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Refractive: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("reflectionType", fvec2(0.0f, positions[7]), TEXT_SIZE("Type: NONE"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Type: NONE", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("refractionType", fvec2(0.0f, positions[8]), TEXT_SIZE("Type: NONE"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Type: NONE", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("reflectivity", fvec2(0.0f, positions[9]), TEXT_SIZE("Reflectivity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Reflectivity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("refractivity", fvec2(0.0f, positions[10]), TEXT_SIZE("Refractivity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Refractivity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("isBright", fvec2(0.0f, positions[11]), TEXT_SIZE("Bright: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Bright: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("isShadowed", fvec2(0.0f, positions[12]), TEXT_SIZE("Shadowed: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Shadowed: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("isReflected", fvec2(0.0f, positions[13]), TEXT_SIZE("Reflected: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Reflected: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("isRefracted", fvec2(0.0f, positions[14]), TEXT_SIZE("Refracted: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Refracted: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("emissionIntensity", fvec2(0.0f, positions[15]), TEXT_SIZE("Emission Intensity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Emission Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("back", fvec2(0.0f, positions[16]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(8, CH, false);
	leftWindow->createScreen("modelEditorMenuMiscellaneous");
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("size", fvec2(0.0f, positions[0]), TEXT_SIZE("Size"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Size", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("opacity", fvec2(0.0f, positions[1]), TEXT_SIZE("Opacity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Opacity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("minTextureAlpha", fvec2(0.0f, positions[2]), TEXT_SIZE("Min Alpha"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Min Alpha", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("isFaceCulled", fvec2(0.0f, positions[3]), TEXT_SIZE("Culling: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Culling: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("levelOfDetailId", fvec2(0.0f, positions[4]), TEXT_SIZE("LOD Model"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "LOD Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("levelOfDetailDistance", fvec2(0.0f, positions[5]), TEXT_SIZE("LOD Distance"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "LOD Distance", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("rotationOrder", fvec2(0.0f, positions[6]), TEXT_SIZE("Rotation: Y X Z"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Rotation : Y X Z", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("back", fvec2(0.0f, positions[7]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(4, CH, false);
	leftWindow->createScreen("modelEditorMenuAabbMain");
	leftWindow->getScreen("modelEditorMenuAabbMain")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create AABB"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create AABB", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuAabbMain")->createButton("edit", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit AABB"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit AABB", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuAabbMain")->createButton("delete", fvec2(0.0f, positions[2]), TEXT_SIZE("Delete AABB"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete AABB", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuAabbMain")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(3, CH, false);
	leftWindow->createScreen("modelEditorMenuAabbChoice");
	leftWindow->getScreen("modelEditorMenuAabbChoice")->createButton("position", fvec2(0.0f, positions[0]), TEXT_SIZE("Position"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Position", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuAabbChoice")->createButton("size", fvec2(0.0f, positions[1]), TEXT_SIZE("Size"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Size", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuAabbChoice")->createButton("back", fvec2(0.0f, positions[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("modelEditorMenuMain");
	rightWindow->setActiveScreen("empty");
}

void ModelEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	leftWindow->deleteScreen("modelEditorMenuMain");
	leftWindow->deleteScreen("modelEditorMenuChoice");
	leftWindow->deleteScreen("modelEditorMenuTexturing");
	leftWindow->deleteScreen("modelEditorMenuLighting");
	leftWindow->deleteScreen("modelEditorMenuMiscellaneous");
	leftWindow->deleteScreen("modelEditorMenuAabbMain");
	leftWindow->deleteScreen("modelEditorMenuAabbChoice");

	leftWindow->setActiveScreen("main");
	rightWindow->setActiveScreen("main");
}

void ModelEditor::update()
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
		_updateTexturingMenu();
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
		_updateMainAabbMenu();
	}
	if(isLoaded())
	{
		_updateChoiceAabbMenu();
	}
	if(isLoaded())
	{
		_updateModelCreating();
	}
	if(isLoaded())
	{
		_updateModelChoosing();
	}
	if(isLoaded())
	{
		_updateModelDeleting();
	}
	if(isLoaded())
	{
		_updatePartChoosing();
	}
	if(isLoaded())
	{
		_updateAabbCreating();
	}
	if(isLoaded())
	{
		_updateAabbChoosing();
	}
	if(isLoaded())
	{
		_updateAabbDeleting();
	}
	if(isLoaded())
	{
		_updateSkyChoosing();
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