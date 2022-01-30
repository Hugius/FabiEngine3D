#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "text3d_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void Text3dEditor::load()
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
	_fe3d->gfx_enableBloom();
	_fe3d->gfx_setBloomType(BloomType::PARTS);
	_fe3d->gfx_setBloomIntensity(1.0f);
	_fe3d->gfx_setBloomBlurCount(5);
	_fe3d->gfx_setBloomQuality(Config::MAX_BLOOM_QUALITY);
	_fe3d->gfx_enableShadows();
	_fe3d->gfx_setShadowLightness(0.25f);
	_fe3d->gfx_setShadowQuality(Config::MAX_SHADOW_QUALITY);

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

	_gui->getOverlay()->createTextField("textId", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true);

	_isEditorLoaded = true;
}

void Text3dEditor::unload()
{
	for(const auto& id : _loadedTextIds)
	{
		_fe3d->text3d_delete(id);
	}

	_unloadGUI();

	if(_fe3d->camera_isThirdPersonViewEnabled())
	{
		_fe3d->camera_disableThirdPersonView();
	}

	_fe3d->gfx_disableAntiAliasing(true);
	_fe3d->gfx_setAnisotropicFilteringQuality(Config::MIN_ANISOTROPIC_FILTERING_QUALITY);
	_fe3d->gfx_disableAmbientLighting(true);
	_fe3d->gfx_disableDirectionalLighting(true);
	_fe3d->gfx_disableBloom(true);
	_fe3d->gfx_disableShadows(true);

	_fe3d->model_delete("@@box");
	_fe3d->model_delete("@@grid");

	_gui->getOverlay()->deleteTextField("textId");

	_loadedTextIds.clear();
	_hoveredTextId = "";
	_currentTextId = "";
	_isCreatingText3d = false;
	_isChoosingText3d = false;
	_isDeletingText3d = false;
	_isEditorLoaded = false;
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

	positions = Math::calculateDistributedPositions(5, CH);
	leftWindow->createScreen("text3dEditorMenuMiscellaneous");
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("size", fvec2(0.0f, positions[0]), TEXT_SIZE("Size"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Size", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("isFacingCameraHorizontally", fvec2(0.0f, positions[1]), TEXT_SIZE("Facing X: OFF"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Facing X: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("isFacingCameraVertically", fvec2(0.0f, positions[2]), TEXT_SIZE("Facing Y: OFF"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Facing Y: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("opacity", fvec2(0.0f, positions[3]), TEXT_SIZE("Opacity"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Opacity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dEditorMenuMiscellaneous")->createButton("back", fvec2(0.0f, positions[4]), TEXT_SIZE("Go Back"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);
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
		_updateLightingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneousMenu();
	}
	if(_isEditorLoaded)
	{
		_updateText3dCreating();
	}
	if(_isEditorLoaded)
	{
		_updateText3dChoosing();
	}
	if(_isEditorLoaded)
	{
		_updateText3dDeleting();
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