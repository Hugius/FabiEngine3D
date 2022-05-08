#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "text3d_editor.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void Text3dEditor::_load()
{
	_fe3d->model_create("@@box", "engine\\assets\\mesh\\box.obj");
	_fe3d->model_setDiffuseMap("@@box", "", "engine\\assets\\image\\diffuse_map\\box.tga");
	_fe3d->model_setFaceCulled("@@box", "", true);
	_fe3d->model_create("@@grid", "engine\\assets\\mesh\\plane.obj");
	_fe3d->model_setBaseSize("@@grid", fvec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d->model_setDiffuseMap("@@grid", "", "engine\\assets\\image\\diffuse_map\\grid.tga");
	_fe3d->model_setTextureRepeat("@@grid", "", GRID_REPEAT);
	_fe3d->model_setMinTextureAlpha("@@grid", "", 0.1f);

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

	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d->camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonEnabled(true);
	_fe3d->camera_setThirdPersonYaw(INITIAL_CAMERA_YAW);
	_fe3d->camera_setThirdPersonPitch(INITIAL_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);

	_gui->getOverlay()->createTextField("text3dId", fvec2(0.0f, 0.85f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
}

void Text3dEditor::_unload()
{
	for(const auto & text3dId : _loadedText3dIds)
	{
		_fe3d->text3d_delete(text3dId);
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

	_gui->getOverlay()->deleteTextField("text3dId");

	_loadedText3dIds.clear();
}

void Text3dEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	auto positions = Mathematics::calculateDistributedPositions(4, CH, false);
	leftWindow->createScreen("text3dEditorMenuMain");
	leftWindow->getScreen("text3dEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create Text3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Text3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Text3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Text3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), TEXT_SIZE("Delete Text3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Text3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(4, CH, false);
	leftWindow->createScreen("text3dEditorMenuChoice");
	leftWindow->getScreen("text3dEditorMenuChoice")->createButton("lighting", fvec2(0.0f, positions[0]), TEXT_SIZE("Lighting"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lighting", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuChoice")->createButton("miscellaneous", fvec2(0.0f, positions[1]), TEXT_SIZE("Miscellaneous"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Miscellaneous", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuChoice")->createButton("aabb", fvec2(0.0f, positions[2]), TEXT_SIZE("AABB"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "AABB", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(7, CH, false);
	leftWindow->createScreen("text3dEditorMenuLighting");
	leftWindow->getScreen("text3dEditorMenuLighting")->createButton("color", fvec2(0.0f, positions[0]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuLighting")->createButton("lightness", fvec2(0.0f, positions[1]), TEXT_SIZE("Lightness"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lightness", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuLighting")->createButton("isBright", fvec2(0.0f, positions[2]), TEXT_SIZE("Bright: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Bright: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuLighting")->createButton("isShadowed", fvec2(0.0f, positions[3]), TEXT_SIZE("Shadowed: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Shadowed: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuLighting")->createButton("isReflected", fvec2(0.0f, positions[4]), TEXT_SIZE("Reflected: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Reflected: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuLighting")->createButton("isRefracted", fvec2(0.0f, positions[5]), TEXT_SIZE("Refracted: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Refracted: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuLighting")->createButton("back", fvec2(0.0f, positions[6]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(9, CH, false);
	leftWindow->createScreen("text3dEditorMenuMiscellaneous");
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("size", fvec2(0.0f, positions[0]), TEXT_SIZE("Size"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Size", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("isFacingCameraHorizontally", fvec2(0.0f, positions[1]), TEXT_SIZE("Facing X: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Facing X: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("isFacingCameraVertically", fvec2(0.0f, positions[2]), TEXT_SIZE("Facing Y: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Facing Y: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("isHorizontallyFlipped", fvec2(0.0f, positions[3]), TEXT_SIZE("Flipped X: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Flipped X: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("isVerticallyFlipped", fvec2(0.0f, positions[4]), TEXT_SIZE("Flipped Y: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Flipped Y: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("opacity", fvec2(0.0f, positions[5]), TEXT_SIZE("Opacity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Opacity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("minTextureAlpha", fvec2(0.0f, positions[6]), TEXT_SIZE("Min Alpha"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Min Alpha", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("rotationOrder", fvec2(0.0f, positions[7]), TEXT_SIZE("Rotation: Y X Z"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Rotation : Y X Z", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("back", fvec2(0.0f, positions[8]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(3, CH, false);
	leftWindow->createScreen("text3dEditorMenuAabb");
	leftWindow->getScreen("text3dEditorMenuAabb")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create AABB"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create AABB", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuAabb")->createButton("delete", fvec2(0.0f, positions[1]), TEXT_SIZE("Delete AABB"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete AABB", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuAabb")->createButton("back", fvec2(0.0f, positions[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("text3dEditorMenuMain");
	rightWindow->setActiveScreen("empty");
}

void Text3dEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	leftWindow->deleteScreen("text3dEditorMenuMain");
	leftWindow->deleteScreen("text3dEditorMenuChoice");
	leftWindow->deleteScreen("text3dEditorMenuLighting");
	leftWindow->deleteScreen("text3dEditorMenuMiscellaneous");
	leftWindow->deleteScreen("text3dEditorMenuAabb");

	leftWindow->setActiveScreen("main");
	rightWindow->setActiveScreen("main");
}

void Text3dEditor::update()
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
		_updateText3dCreating();
	}
	if(isLoaded())
	{
		_updateText3dChoosing();
	}
	if(isLoaded())
	{
		_updateText3dDeleting();
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