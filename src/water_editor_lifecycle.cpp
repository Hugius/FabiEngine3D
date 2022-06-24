#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)
#define POSITIONS(count) Mathematics::calculateDistributedPositions(count, CH, false)

#include "water_editor.hpp"
#include "tools.hpp"

void WaterEditor::_load()
{
	_skyEditor->loadSkiesFromFile();

	_fe3d->model_create(GRID_ID, GRID_MESH_PATH);
	_fe3d->model_setBaseSize(GRID_ID, fvec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d->model_setDiffuseMap(GRID_ID, "", GRID_TEXTURE_PATH);
	_fe3d->model_setTextureRepeat(GRID_ID, "", GRID_REPEAT);
	_fe3d->model_setMinAlpha(GRID_ID, "", GRID_MIN_ALPHA);
	_fe3d->model_setLightness(GRID_ID, "", GRID_LIGHTNESS);
	_fe3d->model_setShadowed(GRID_ID, false);
	_fe3d->model_create(BOX_ID, BOX_MESH_PATH);
	_fe3d->model_setDiffuseMap(BOX_ID, "", BOX_TEXTURE_PATH);
	_fe3d->model_setLightness(BOX_ID, "", BOX_LIGHTNESS);
	_fe3d->model_setFaceCulled(BOX_ID, "", true);
	_fe3d->graphics_setAntiAliasingEnabled(true);
	_fe3d->graphics_setAnisotropicFilteringQuality(ANISOTROPIC_FILTERING_QUALITY);
	_fe3d->graphics_setAmbientLightingEnabled(true);
	_fe3d->graphics_setAmbientLightingIntensity(AMBIENT_LIGHTING_INTENSITY);
	_fe3d->graphics_setDirectionalLightingEnabled(true);
	_fe3d->graphics_setDirectionalLightingPosition(DIRECTIONAL_LIGHTING_POSITION);
	_fe3d->graphics_setDirectionalLightingIntensity(DIRECTIONAL_LIGHTING_INTENSITY);
	_fe3d->graphics_setShadowsEnabled(true);
	_fe3d->graphics_setShadowLightness(SHADOW_LIGHTNESS);
	_fe3d->graphics_setShadowQuality(SHADOW_QUALITY);
	_fe3d->graphics_setShadowPcfCount(SHADOW_PCF_COUNT);
	_fe3d->graphics_setShadowBias(SHADOW_BIAS);
	_fe3d->graphics_setShadowPositionOffset(fvec3(GRID_SIZE * 0.5f));
	_fe3d->graphics_setShadowSize(Mathematics::calculateMagnitude(fvec3(GRID_SIZE * 0.5f)));
	_fe3d->graphics_setPlanarReflectionQuality(PLANAR_REFLECTION_QUALITY);
	_fe3d->graphics_setPlanarRefractionQuality(PLANAR_REFRACTION_QUALITY);
	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d->camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonEnabled(true);
	_fe3d->camera_setThirdPersonYaw(INITIAL_CAMERA_YAW);
	_fe3d->camera_setThirdPersonPitch(INITIAL_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);

	_gui->getOverlay()->createTextField(WATER_TITLE_ID, WATER_TITLE_POSITION, WATER_TITLE_SIZE, "", fvec3(1.0f), true);
}

void WaterEditor::_unload()
{
	for(const auto & waterId : _loadedWaterIds)
	{
		_fe3d->water_delete(waterId);
	}

	_skyEditor->deleteLoadedSkies();

	_fe3d->model_delete(GRID_ID);
	_fe3d->model_delete(BOX_ID);
	_fe3d->graphics_setAntiAliasingEnabled(false);
	_fe3d->graphics_setAnisotropicFilteringQuality(0);
	_fe3d->graphics_setAmbientLightingEnabled(false);
	_fe3d->graphics_setAmbientLightingIntensity(0.0f);
	_fe3d->graphics_setDirectionalLightingEnabled(false);
	_fe3d->graphics_setDirectionalLightingPosition(fvec3(0.0f));
	_fe3d->graphics_setDirectionalLightingIntensity(0.0f);
	_fe3d->graphics_setPlanarReflectionQuality(0);
	_fe3d->graphics_setPlanarRefractionQuality(0);
	_fe3d->graphics_setShadowsEnabled(false);
	_fe3d->graphics_setShadowLightness(0.0f);
	_fe3d->graphics_setShadowQuality(0);
	_fe3d->graphics_setShadowPositionOffset(fvec3(0.0f));
	_fe3d->graphics_setShadowSize(0.0f);
	_fe3d->graphics_setShadowPcfCount(0);
	_fe3d->graphics_setShadowBias(0.0f);
	_fe3d->camera_reset();

	_gui->getOverlay()->deleteTextField(WATER_TITLE_ID);

	_loadedWaterIds.clear();
}

void WaterEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	leftWindow->createScreen("waterEditorMenuMain");
	leftWindow->getScreen("waterEditorMenuMain")->createButton("sky", fvec2(0.0f, POSITIONS(5)[0]), TEXT_SIZE("Select Sky"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Select Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMain")->createButton("create", fvec2(0.0f, POSITIONS(5)[1]), TEXT_SIZE("Create Water"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Water", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMain")->createButton("edit", fvec2(0.0f, POSITIONS(5)[2]), TEXT_SIZE("Edit Water"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Water", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMain")->createButton("delete", fvec2(0.0f, POSITIONS(5)[3]), TEXT_SIZE("Delete Water"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Water", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMain")->createButton("back", fvec2(0.0f, POSITIONS(5)[4]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("waterEditorMenuChoice");
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("texturing", fvec2(0.0f, POSITIONS(4)[0]), TEXT_SIZE("Texturing"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Texturing", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("lighting", fvec2(0.0f, POSITIONS(4)[1]), TEXT_SIZE("Lighting"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lighting", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("miscellaneous", fvec2(0.0f, POSITIONS(4)[2]), TEXT_SIZE("Miscellaneous"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Miscellaneous", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("back", fvec2(0.0f, POSITIONS(4)[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("waterEditorMenuTexturing");
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("dudvMap", fvec2(0.0f, POSITIONS(6)[0]), TEXT_SIZE("DUDV Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "DUDV Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("normalMap", fvec2(0.0f, POSITIONS(6)[1]), TEXT_SIZE("Normal Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Normal Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("heightMap", fvec2(0.0f, POSITIONS(6)[2]), TEXT_SIZE("Height Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Height Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("clearMaps", fvec2(0.0f, POSITIONS(6)[3]), TEXT_SIZE("Clear Maps"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear Maps", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("textureRepeat", fvec2(0.0f, POSITIONS(6)[4]), TEXT_SIZE("Texture Repeat"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Texture Repeat", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("back", fvec2(0.0f, POSITIONS(6)[5]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("waterEditorMenuLighting");
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("color", fvec2(0.0f, POSITIONS(11)[0]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("lightness", fvec2(0.0f, POSITIONS(11)[1]), TEXT_SIZE("Lightness"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lightness", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("specularShininess", fvec2(0.0f, POSITIONS(11)[2]), TEXT_SIZE("Specular Shininess"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular Shininess", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("specularIntensity", fvec2(0.0f, POSITIONS(11)[3]), TEXT_SIZE("Specular Intensity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("distortionSize", fvec2(0.0f, POSITIONS(11)[4]), TEXT_SIZE("Distortion size"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Distortion size", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("distortionFactor", fvec2(0.0f, POSITIONS(11)[5]), TEXT_SIZE("Distortion Factor"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Distortion Factor", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("isReflective", fvec2(0.0f, POSITIONS(11)[6]), TEXT_SIZE("Reflective: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Reflective: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("isRefractive", fvec2(0.0f, POSITIONS(11)[7]), TEXT_SIZE("Refractive: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Refractive: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("isSpecular", fvec2(0.0f, POSITIONS(11)[8]), TEXT_SIZE("Specular: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("isEdged", fvec2(0.0f, POSITIONS(11)[9]), TEXT_SIZE("Edged: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edged: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("back", fvec2(0.0f, POSITIONS(11)[10]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("waterEditorMenuMiscellaneous");
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("size", fvec2(0.0f, POSITIONS(13)[0]), TEXT_SIZE("Size"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Size", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("waveHeight", fvec2(0.0f, POSITIONS(13)[1]), TEXT_SIZE("Wave Height"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Wave Height", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("maxDepth", fvec2(0.0f, POSITIONS(13)[2]), TEXT_SIZE("Max Depth"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Max Depth", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("rippleSpeed", fvec2(0.0f, POSITIONS(13)[3]), TEXT_SIZE("Ripple Speed"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Ripple Speed", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("waveSpeed", fvec2(0.0f, POSITIONS(13)[4]), TEXT_SIZE("Wave Speed"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Wave Speed", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("captureOffset", fvec2(0.0f, POSITIONS(13)[5]), TEXT_SIZE("Capture Offset"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Capture Offset", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("isCapturingSky", fvec2(0.0f, POSITIONS(13)[6]), TEXT_SIZE("Sky: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Sky: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("isCapturingTerrain", fvec2(0.0f, POSITIONS(13)[7]), TEXT_SIZE("Terrain: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Terrain: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("isCapturingModels", fvec2(0.0f, POSITIONS(13)[8]), TEXT_SIZE("Models: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Models: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("isCapturingQuad3ds", fvec2(0.0f, POSITIONS(13)[9]), TEXT_SIZE("Quad3Ds: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Quad3Ds: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("isCapturingText3ds", fvec2(0.0f, POSITIONS(13)[10]), TEXT_SIZE("Text3Ds: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Text3Ds: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("isCapturingAabbs", fvec2(0.0f, POSITIONS(13)[11]), TEXT_SIZE("AABBs: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "AABBs: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("back", fvec2(0.0f, POSITIONS(13)[12]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("waterEditorMenuMain");

	rightWindow->setActiveScreen("empty");
}

void WaterEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	leftWindow->deleteScreen("waterEditorMenuMain");
	leftWindow->deleteScreen("waterEditorMenuChoice");
	leftWindow->deleteScreen("waterEditorMenuTexturing");
	leftWindow->deleteScreen("waterEditorMenuLighting");
	leftWindow->deleteScreen("waterEditorMenuMiscellaneous");

	leftWindow->setActiveScreen("main");

	rightWindow->setActiveScreen("main");
}

void WaterEditor::_update()
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
		_updateWaterCreating();
	}

	if(isLoaded())
	{
		_updateWaterChoosing();
	}

	if(isLoaded())
	{
		_updateWaterDeleting();
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