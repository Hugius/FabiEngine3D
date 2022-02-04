#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "text3d_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void Text3dEditor::_load()
{
	_fe3d->camera_reset();
	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d->camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonEnabled(true);
	_fe3d->camera_setThirdPersonYaw(INITIAL_CAMERA_YAW);
	_fe3d->camera_setThirdPersonPitch(INITIAL_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);
	_fe3d->camera_setThirdPersonLookat(fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));

	_fe3d->gfx_setAntiAliasingEnabled(true);
	_fe3d->gfx_setAnisotropicFilteringQuality(16);
	_fe3d->gfx_setAmbientLightingEnabled(true);
	_fe3d->gfx_setAmbientLightingColor(fvec3(1.0f));
	_fe3d->gfx_setAmbientLightingIntensity(1.0f);
	_fe3d->gfx_setDirectionalLightingEnabled(true);
	_fe3d->gfx_setDirectionalLightingColor(fvec3(1.0f));
	_fe3d->gfx_setDirectionalLightingPosition(fvec3(10000.0f));
	_fe3d->gfx_setDirectionalLightingIntensity(3.0f);
	_fe3d->gfx_setBloomEnabled(true);
	_fe3d->gfx_setBloomType(BloomType::PARTS);
	_fe3d->gfx_setBloomIntensity(1.0f);
	_fe3d->gfx_setBloomBlurCount(5);
	_fe3d->gfx_setBloomQuality(5);
	_fe3d->gfx_setShadowsEnabled(true);
	_fe3d->gfx_setShadowLightness(0.25f);
	_fe3d->gfx_setShadowQuality(16384);

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

	_gui->getOverlay()->createTextField("textId", fvec2(0.0f, 0.85f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
}

void Text3dEditor::_unload()
{
	for(const auto& id : _loadedTextIds)
	{
		_fe3d->text3d_delete(id);
	}

	_fe3d->camera_setThirdPersonEnabled(false);

	_fe3d->gfx_setAntiAliasingEnabled(false);
	_fe3d->gfx_setAnisotropicFilteringQuality(0);
	_fe3d->gfx_setAmbientLightingEnabled(false);
	_fe3d->gfx_setAmbientLightingColor(fvec3(0.0f));
	_fe3d->gfx_setAmbientLightingIntensity(0.0f);
	_fe3d->gfx_setDirectionalLightingEnabled(false);
	_fe3d->gfx_setDirectionalLightingColor(fvec3(0.0f));
	_fe3d->gfx_setDirectionalLightingPosition(fvec3(0.0f));
	_fe3d->gfx_setDirectionalLightingIntensity(0.0f);
	_fe3d->gfx_setBloomEnabled(false);
	_fe3d->gfx_setBloomType(BloomType::EVERYTHING);
	_fe3d->gfx_setBloomIntensity(0.0f);
	_fe3d->gfx_setBloomBlurCount(0);
	_fe3d->gfx_setBloomQuality(0);
	_fe3d->gfx_setShadowsEnabled(false);
	_fe3d->gfx_setShadowLightness(0.0f);
	_fe3d->gfx_setShadowQuality(0);

	_fe3d->model_delete("@@box");
	_fe3d->model_delete("@@grid");

	_gui->getOverlay()->deleteTextField("textId");

	_loadedTextIds.clear();
	_hoveredTextId = "";
	_currentTextId = "";
	_isCreatingText3d = false;
	_isChoosingText3d = false;
	_isDeletingText3d = false;
}

void Text3dEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = Math::calculateDistributedPositions(4, CH);
	leftWindow->createScreen("text3dEditorMenuMain");
	leftWindow->getScreen("text3dEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create Text3D"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Text3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Text3D"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Text3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), TEXT_SIZE("Delete Text3D"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Text3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(3, CH);
	leftWindow->createScreen("text3dEditorMenuChoice");
	leftWindow->getScreen("text3dEditorMenuChoice")->createButton("lighting", fvec2(0.0f, positions[0]), TEXT_SIZE("Lighting"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lighting", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuChoice")->createButton("miscellaneous", fvec2(0.0f, positions[1]), TEXT_SIZE("Miscellaneous"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Miscellaneous", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[2]), TEXT_SIZE("Go Back"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(6, CH);
	leftWindow->createScreen("text3dEditorMenuLighting");
	leftWindow->getScreen("text3dEditorMenuLighting")->createButton("color", fvec2(0.0f, positions[0]), TEXT_SIZE("Color"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuLighting")->createButton("lightness", fvec2(0.0f, positions[1]), TEXT_SIZE("Lightness"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lightness", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuLighting")->createButton("isBright", fvec2(0.0f, positions[2]), TEXT_SIZE("Bright: OFF"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Bright: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuLighting")->createButton("isShadowed", fvec2(0.0f, positions[3]), TEXT_SIZE("Shadowed: OFF"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Shadowed: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuLighting")->createButton("isReflected", fvec2(0.0f, positions[4]), TEXT_SIZE("Reflected: OFF"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Reflected: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuLighting")->createButton("back", fvec2(0.0f, positions[5]), TEXT_SIZE("Go Back"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(6, CH);
	leftWindow->createScreen("text3dEditorMenuMiscellaneous");
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("size", fvec2(0.0f, positions[0]), TEXT_SIZE("Size"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Size", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("isFacingCameraHorizontally", fvec2(0.0f, positions[1]), TEXT_SIZE("Facing X: OFF"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Facing X: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("isFacingCameraVertically", fvec2(0.0f, positions[2]), TEXT_SIZE("Facing Y: OFF"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Facing Y: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("opacity", fvec2(0.0f, positions[3]), TEXT_SIZE("Opacity"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Opacity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("minTextureAlpha", fvec2(0.0f, positions[4]), TEXT_SIZE("Min Alpha"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Min Alpha", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("back", fvec2(0.0f, positions[5]), TEXT_SIZE("Go Back"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);
}

void Text3dEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("text3dEditorMenuMain");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("text3dEditorMenuChoice");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("text3dEditorMenuLighting");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("text3dEditorMenuMiscellaneous");
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