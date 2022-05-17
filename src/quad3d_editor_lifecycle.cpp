#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)
#define POSITIONS(count) Mathematics::calculateDistributedPositions(count, CH, false)

#include "quad3d_editor.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void Quad3dEditor::_load()
{
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
	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d->camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonEnabled(true);
	_fe3d->camera_setThirdPersonYaw(INITIAL_CAMERA_YAW);
	_fe3d->camera_setThirdPersonPitch(INITIAL_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);

	_gui->getOverlay()->createTextField(QUAD3D_TITLE_ID, QUAD3D_TITLE_POSITION, QUAD3D_TITLE_SIZE, "", fvec3(1.0f), true);
}

void Quad3dEditor::_unload()
{
	for(const auto & quad3dId : _loadedQuad3dIds)
	{
		_fe3d->quad3d_delete(quad3dId);
	}

	_fe3d->model_delete(GRID_ID);
	_fe3d->model_delete(BOX_ID);
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
	_fe3d->camera_reset();

	_gui->getOverlay()->deleteTextField(QUAD3D_TITLE_ID);

	_loadedQuad3dIds.clear();
}

void Quad3dEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	leftWindow->createScreen("quad3dEditorMenuMain");
	leftWindow->getScreen("quad3dEditorMenuMain")->createButton("create", fvec2(0.0f, POSITIONS(4)[0]), TEXT_SIZE("Create Quad3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Quad3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuMain")->createButton("edit", fvec2(0.0f, POSITIONS(4)[1]), TEXT_SIZE("Edit Quad3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Quad3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuMain")->createButton("delete", fvec2(0.0f, POSITIONS(4)[2]), TEXT_SIZE("Delete Quad3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Quad3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuMain")->createButton("back", fvec2(0.0f, POSITIONS(4)[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("quad3dEditorMenuChoice");
	leftWindow->getScreen("quad3dEditorMenuChoice")->createButton("texturing", fvec2(0.0f, POSITIONS(5)[0]), TEXT_SIZE("Texturing"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Texturing", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuChoice")->createButton("lighting", fvec2(0.0f, POSITIONS(5)[1]), TEXT_SIZE("Lighting"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lighting", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuChoice")->createButton("miscellaneous", fvec2(0.0f, POSITIONS(5)[2]), TEXT_SIZE("Miscellaneous"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Miscellaneous", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuChoice")->createButton("aabb", fvec2(0.0f, POSITIONS(5)[3]), TEXT_SIZE("AABB"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "AABB", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuChoice")->createButton("back", fvec2(0.0f, POSITIONS(5)[4]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("quad3dEditorMenuTexturing");
	leftWindow->getScreen("quad3dEditorMenuTexturing")->createButton("diffuseMap", fvec2(0.0f, POSITIONS(5)[0]), TEXT_SIZE("Diffuse Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Diffuse Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuTexturing")->createButton("emissionMap", fvec2(0.0f, POSITIONS(5)[1]), TEXT_SIZE("Emission Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Emission Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuTexturing")->createButton("clearMaps", fvec2(0.0f, POSITIONS(5)[2]), TEXT_SIZE("Clear Maps"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear Maps", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuTexturing")->createButton("textureRepeat", fvec2(0.0f, POSITIONS(5)[3]), TEXT_SIZE("Texture Repeat"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Texture Repeat", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuTexturing")->createButton("back", fvec2(0.0f, POSITIONS(5)[4]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("quad3dEditorMenuLighting");
	leftWindow->getScreen("quad3dEditorMenuLighting")->createButton("color", fvec2(0.0f, POSITIONS(8)[0]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuLighting")->createButton("lightness", fvec2(0.0f, POSITIONS(8)[1]), TEXT_SIZE("Lightness"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lightness", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuLighting")->createButton("emissionIntensity", fvec2(0.0f, POSITIONS(8)[2]), TEXT_SIZE("Emission Intensity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Emission Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuLighting")->createButton("isBright", fvec2(0.0f, POSITIONS(8)[3]), TEXT_SIZE("Bright: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Bright: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuLighting")->createButton("isShadowed", fvec2(0.0f, POSITIONS(8)[4]), TEXT_SIZE("Shadowed: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Shadowed: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuLighting")->createButton("isReflected", fvec2(0.0f, POSITIONS(8)[5]), TEXT_SIZE("Reflected: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Reflected: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuLighting")->createButton("isRefracted", fvec2(0.0f, POSITIONS(8)[6]), TEXT_SIZE("Refracted: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Refracted: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuLighting")->createButton("back", fvec2(0.0f, POSITIONS(8)[7]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("quad3dEditorMenuMiscellaneous");
	leftWindow->getScreen("quad3dEditorMenuMiscellaneous")->createButton("size", fvec2(0.0f, POSITIONS(9)[0]), TEXT_SIZE("Size"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Size", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuMiscellaneous")->createButton("isFacingCameraHorizontally", fvec2(0.0f, POSITIONS(9)[1]), TEXT_SIZE("Facing X: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Facing X: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuMiscellaneous")->createButton("isFacingCameraVertically", fvec2(0.0f, POSITIONS(9)[2]), TEXT_SIZE("Facing Y: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Facing Y: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuMiscellaneous")->createButton("isHorizontallyFlipped", fvec2(0.0f, POSITIONS(9)[3]), TEXT_SIZE("Flipped X: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Flipped X: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuMiscellaneous")->createButton("isVerticallyFlipped", fvec2(0.0f, POSITIONS(9)[4]), TEXT_SIZE("Flipped Y: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Flipped Y: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuMiscellaneous")->createButton("opacity", fvec2(0.0f, POSITIONS(9)[5]), TEXT_SIZE("Opacity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Opacity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuMiscellaneous")->createButton("minTextureAlpha", fvec2(0.0f, POSITIONS(9)[6]), TEXT_SIZE("Min Alpha"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Min Alpha", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuMiscellaneous")->createButton("rotationOrder", fvec2(0.0f, POSITIONS(9)[7]), TEXT_SIZE("Rotation: Y X Z"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Rotation : Y X Z", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuMiscellaneous")->createButton("back", fvec2(0.0f, POSITIONS(9)[8]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("quad3dEditorMenuAabb");
	leftWindow->getScreen("quad3dEditorMenuAabb")->createButton("create", fvec2(0.0f, POSITIONS(3)[0]), TEXT_SIZE("Create AABB"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create AABB", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuAabb")->createButton("delete", fvec2(0.0f, POSITIONS(3)[1]), TEXT_SIZE("Delete AABB"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete AABB", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dEditorMenuAabb")->createButton("back", fvec2(0.0f, POSITIONS(3)[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("quad3dEditorMenuMain");

	rightWindow->setActiveScreen("empty");
}

void Quad3dEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	leftWindow->deleteScreen("quad3dEditorMenuMain");
	leftWindow->deleteScreen("quad3dEditorMenuChoice");
	leftWindow->deleteScreen("quad3dEditorMenuTexturing");
	leftWindow->deleteScreen("quad3dEditorMenuLighting");
	leftWindow->deleteScreen("quad3dEditorMenuMiscellaneous");
	leftWindow->deleteScreen("quad3dEditorMenuAabb");

	leftWindow->setActiveScreen("main");

	rightWindow->setActiveScreen("main");
}

void Quad3dEditor::update()
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
		_updateAabbMenu();
	}

	if(isLoaded())
	{
		_updateQuad3dCreating();
	}

	if(isLoaded())
	{
		_updateQuad3dChoosing();
	}

	if(isLoaded())
	{
		_updateQuad3dDeleting();
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