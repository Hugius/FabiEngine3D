#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)
#define POSITIONS(count) Mathematics::calculateDistributedPositions(count, CH, false)

#include "model_editor.hpp"
#include "configuration.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

void ModelEditor::_load()
{
	_skyEditor->loadSkiesFromFile();

	_fe3d->model_create(GRID_ID, GRID_MESH_PATH);
	_fe3d->model_setBaseSize(GRID_ID, fvec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d->model_setDiffuseMap(GRID_ID, "", GRID_TEXTURE_PATH);
	_fe3d->model_setTextureRepeat(GRID_ID, "", GRID_REPEAT);
	_fe3d->model_setMinTextureAlpha(GRID_ID, "", GRID_MIN_TEXTURE_ALPHA);
	_fe3d->model_setLightness(GRID_ID, "", GRID_LIGHTNESS);
	_fe3d->model_setShadowed(GRID_ID, false);
	_fe3d->model_create(BOX_ID, BOX_MESH_PATH);
	_fe3d->model_setDiffuseMap(BOX_ID, "", BOX_TEXTURE_PATH);
	_fe3d->model_setFaceCulled(BOX_ID, "", true);
	_fe3d->model_setVisible(BOX_ID, false);
	_fe3d->captor_create(CAPTOR_ID);
	_fe3d->captor_setPosition(CAPTOR_ID, CAPTOR_POSITION);
	_fe3d->captor_capture(CAPTOR_ID);
	_fe3d->model_setVisible(BOX_ID, true);
	_fe3d->graphics_setAntiAliasingEnabled(true);
	_fe3d->graphics_setAnisotropicFilteringQuality(ANISOTROPIC_FILTERING_QUALITY);
	_fe3d->graphics_setAmbientLightingEnabled(true);
	_fe3d->graphics_setAmbientLightingIntensity(AMBIENT_LIGHTING_INTENSITY);
	_fe3d->graphics_setDirectionalLightingEnabled(true);
	_fe3d->graphics_setDirectionalLightingPosition(DIRECTIONAL_LIGHTING_POSITION);
	_fe3d->graphics_setDirectionalLightingIntensity(DIRECTIONAL_LIGHTING_INTENSITY);
	_fe3d->graphics_setBloomEnabled(true);
	_fe3d->graphics_setBloomType(BLOOM_TYPE);
	_fe3d->graphics_setBloomIntensity(BLOOM_INTENSITY);
	_fe3d->graphics_setBloomBlurCount(BLOOM_BLUR_COUNT);
	_fe3d->graphics_setBloomQuality(BLOOM_QUALITY);
	_fe3d->graphics_setShadowsEnabled(true);
	_fe3d->graphics_setShadowLightness(SHADOW_LIGHTNESS);
	_fe3d->graphics_setShadowQuality(SHADOW_QUALITY);
	_fe3d->graphics_setShadowPositionOffset(fvec3(GRID_SIZE * 0.5f));
	_fe3d->graphics_setShadowSize(Mathematics::calculateMagnitude(fvec3(GRID_SIZE * 0.5f)));
	_fe3d->graphics_setCubeReflectionQuality(CUBE_REFLECTION_QUALITY);
	_fe3d->graphics_setCubeRefractionQuality(CUBE_REFRACTION_QUALITY);
	_fe3d->graphics_setPlanarReflectionQuality(PLANAR_REFLECTION_QUALITY);
	_fe3d->graphics_setPlanarRefractionQuality(PLANAR_REFRACTION_QUALITY);
	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d->camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonEnabled(true);
	_fe3d->camera_setThirdPersonYaw(INITIAL_CAMERA_YAW);
	_fe3d->camera_setThirdPersonPitch(INITIAL_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);

	_gui->getOverlay()->createTextField(MODEL_TITLE_ID, MODEL_TITLE_POSITION, MODEL_TITLE_SIZE, "", fvec3(1.0f), true);
	_gui->getOverlay()->createTextField(AABB_TITLE_ID, AABB_TITLE_POSITION, AABB_TITLE_SIZE, "", fvec3(1.0f), true);
}

void ModelEditor::_unload()
{
	for(const auto & modelId : _loadedModelIds)
	{
		_fe3d->model_delete(modelId);
	}

	_skyEditor->deleteLoadedSkies();

	_fe3d->model_delete(GRID_ID);
	_fe3d->model_delete(BOX_ID);
	_fe3d->captor_delete(CAPTOR_ID);
	_fe3d->graphics_setAntiAliasingEnabled(false);
	_fe3d->graphics_setAnisotropicFilteringQuality(0);
	_fe3d->graphics_setAmbientLightingEnabled(false);
	_fe3d->graphics_setAmbientLightingIntensity(0.0f);
	_fe3d->graphics_setDirectionalLightingEnabled(false);
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
	_fe3d->graphics_setShadowPositionOffset(fvec3(0.0f));
	_fe3d->graphics_setShadowSize(0.0f);
	_fe3d->graphics_setCubeReflectionQuality(0);
	_fe3d->graphics_setCubeRefractionQuality(0);
	_fe3d->graphics_setPlanarReflectionQuality(0);
	_fe3d->graphics_setPlanarRefractionQuality(0);
	_fe3d->camera_reset();

	_gui->getOverlay()->deleteTextField(MODEL_TITLE_ID);
	_gui->getOverlay()->deleteTextField(AABB_TITLE_ID);

	_loadedModelIds.clear();
}

void ModelEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	leftWindow->createScreen("modelEditorMenuMain");
	leftWindow->getScreen("modelEditorMenuMain")->createButton("sky", fvec2(0.0f, POSITIONS(5)[0]), TEXT_SIZE("Select Sky"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Select Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMain")->createButton("create", fvec2(0.0f, POSITIONS(5)[1]), TEXT_SIZE("Create Model"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMain")->createButton("edit", fvec2(0.0f, POSITIONS(5)[2]), TEXT_SIZE("Edit Model"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMain")->createButton("delete", fvec2(0.0f, POSITIONS(5)[3]), TEXT_SIZE("Delete Model"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMain")->createButton("back", fvec2(0.0f, POSITIONS(5)[4]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("modelEditorMenuChoice");
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("part", fvec2(0.0f, POSITIONS(6)[0]), TEXT_SIZE("Select Part"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Select Part", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("texturing", fvec2(0.0f, POSITIONS(6)[1]), TEXT_SIZE("Texturing"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Texturing", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("lighting", fvec2(0.0f, POSITIONS(6)[2]), TEXT_SIZE("Lighting"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lighting", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("miscellaneous", fvec2(0.0f, POSITIONS(6)[3]), TEXT_SIZE("Miscellaneous"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Miscellaneous", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("aabb", fvec2(0.0f, POSITIONS(6)[4]), TEXT_SIZE("AABB"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "AABB", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("back", fvec2(0.0f, POSITIONS(6)[5]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("modelEditorMenuTexturing");
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("diffuseMap", fvec2(0.0f, POSITIONS(9)[0]), TEXT_SIZE("Diffuse Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Diffuse Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("emissionMap", fvec2(0.0f, POSITIONS(9)[1]), TEXT_SIZE("Emission Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Emission Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("specularMap", fvec2(0.0f, POSITIONS(9)[2]), TEXT_SIZE("Specular Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("reflectionMap", fvec2(0.0f, POSITIONS(9)[3]), TEXT_SIZE("Reflection Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Reflection Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("refractionMap", fvec2(0.0f, POSITIONS(9)[4]), TEXT_SIZE("Refraction Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Refraction Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("normalMap", fvec2(0.0f, POSITIONS(9)[5]), TEXT_SIZE("Normal Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Normal Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("clearMaps", fvec2(0.0f, POSITIONS(9)[6]), TEXT_SIZE("Clear Maps"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear Maps", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("textureRepeat", fvec2(0.0f, POSITIONS(9)[7]), TEXT_SIZE("Texture Repeat"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Texture Repeat", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("back", fvec2(0.0f, POSITIONS(9)[8]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("modelEditorMenuLighting");
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("color", fvec2(0.0f, POSITIONS(17)[0]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("lightness", fvec2(0.0f, POSITIONS(17)[1]), TEXT_SIZE("Lightness"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lightness", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("isSpecular", fvec2(0.0f, POSITIONS(17)[2]), TEXT_SIZE("Specular: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("specularShininess", fvec2(0.0f, POSITIONS(17)[3]), TEXT_SIZE("Specular Shininess"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular Shininess", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("specularIntensity", fvec2(0.0f, POSITIONS(17)[4]), TEXT_SIZE("Specular Intensity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("isReflective", fvec2(0.0f, POSITIONS(17)[5]), TEXT_SIZE("Reflective: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Reflective: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("reflectionType", fvec2(0.0f, POSITIONS(17)[6]), TEXT_SIZE("Type: CUBE"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Type: CUBE", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("reflectivity", fvec2(0.0f, POSITIONS(17)[7]), TEXT_SIZE("Reflectivity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Reflectivity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("isRefractive", fvec2(0.0f, POSITIONS(17)[8]), TEXT_SIZE("Refractive: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Refractive: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("refractionType", fvec2(0.0f, POSITIONS(17)[9]), TEXT_SIZE("Type: CUBE"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Type: CUBE", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("refractivity", fvec2(0.0f, POSITIONS(17)[10]), TEXT_SIZE("Refractivity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Refractivity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("isBright", fvec2(0.0f, POSITIONS(17)[11]), TEXT_SIZE("Bright: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Bright: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("isShadowed", fvec2(0.0f, POSITIONS(17)[12]), TEXT_SIZE("Shadowed: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Shadowed: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("isReflected", fvec2(0.0f, POSITIONS(17)[13]), TEXT_SIZE("Reflected: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Reflected: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("isRefracted", fvec2(0.0f, POSITIONS(17)[14]), TEXT_SIZE("Refracted: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Refracted: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("emissionIntensity", fvec2(0.0f, POSITIONS(17)[15]), TEXT_SIZE("Emission Intensity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Emission Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("back", fvec2(0.0f, POSITIONS(17)[16]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("modelEditorMenuMiscellaneous");
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("size", fvec2(0.0f, POSITIONS(8)[0]), TEXT_SIZE("Size"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Size", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("opacity", fvec2(0.0f, POSITIONS(8)[1]), TEXT_SIZE("Opacity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Opacity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("minTextureAlpha", fvec2(0.0f, POSITIONS(8)[2]), TEXT_SIZE("Min Alpha"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Min Alpha", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("isFaceCulled", fvec2(0.0f, POSITIONS(8)[3]), TEXT_SIZE("Culling: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Culling: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("levelOfDetailId", fvec2(0.0f, POSITIONS(8)[4]), TEXT_SIZE("LOD Model"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "LOD Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("levelOfDetailDistance", fvec2(0.0f, POSITIONS(8)[5]), TEXT_SIZE("LOD Distance"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "LOD Distance", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("rotationOrder", fvec2(0.0f, POSITIONS(8)[6]), TEXT_SIZE("Rotation: Y X Z"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Rotation : Y X Z", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("back", fvec2(0.0f, POSITIONS(8)[7]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("modelEditorMenuAabbMain");
	leftWindow->getScreen("modelEditorMenuAabbMain")->createButton("create", fvec2(0.0f, POSITIONS(4)[0]), TEXT_SIZE("Create AABB"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create AABB", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuAabbMain")->createButton("edit", fvec2(0.0f, POSITIONS(4)[1]), TEXT_SIZE("Edit AABB"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit AABB", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuAabbMain")->createButton("delete", fvec2(0.0f, POSITIONS(4)[2]), TEXT_SIZE("Delete AABB"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete AABB", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuAabbMain")->createButton("back", fvec2(0.0f, POSITIONS(4)[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("modelEditorMenuAabbChoice");
	leftWindow->getScreen("modelEditorMenuAabbChoice")->createButton("position", fvec2(0.0f, POSITIONS(3)[0]), TEXT_SIZE("Position"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Position", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuAabbChoice")->createButton("size", fvec2(0.0f, POSITIONS(3)[1]), TEXT_SIZE("Size"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Size", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuAabbChoice")->createButton("back", fvec2(0.0f, POSITIONS(3)[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

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