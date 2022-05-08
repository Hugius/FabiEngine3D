#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "pointlight_editor.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void PointlightEditor::_load()
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
	_fe3d->graphics_setShadowsEnabled(true);
	_fe3d->graphics_setShadowLightness(0.25f);
	_fe3d->graphics_setShadowQuality(16384);
	_fe3d->graphics_setShadowPositionOffset(fvec3(5.0f));
	_fe3d->graphics_setShadowSize(Mathematics::calculateMagnitude(fvec3(5.0f)));

	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d->camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonEnabled(true);
	_fe3d->camera_setThirdPersonYaw(INITIAL_CAMERA_YAW);
	_fe3d->camera_setThirdPersonPitch(INITIAL_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);

	_gui->getOverlay()->createTextField("pointlightId", fvec2(0.0f, 0.85f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
}

void PointlightEditor::_unload()
{
	for(const auto & pointlightId : _loadedPointlightIds)
	{
		_fe3d->pointlight_delete(pointlightId);
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
	_fe3d->graphics_setShadowsEnabled(false);
	_fe3d->graphics_setShadowLightness(0.0f);
	_fe3d->graphics_setShadowQuality(0);
	_fe3d->graphics_setShadowPositionOffset(fvec3(0.0f));
	_fe3d->graphics_setShadowSize(0.0f);

	_fe3d->camera_reset();

	_gui->getOverlay()->deleteTextField("pointlightId");

	_loadedPointlightIds.clear();
}

void PointlightEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	auto positions = Mathematics::calculateDistributedPositions(4, CH, false);
	leftWindow->createScreen("pointlightEditorMenuMain");
	leftWindow->getScreen("pointlightEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create Pointlight"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Pointlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("pointlightEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Pointlight"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Pointlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("pointlightEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), TEXT_SIZE("Delete Pointlight"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Pointlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("pointlightEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(5, CH, false);
	leftWindow->createScreen("pointlightEditorMenuChoice");
	leftWindow->getScreen("pointlightEditorMenuChoice")->createButton("radius", fvec2(0.0f, positions[0]), TEXT_SIZE("Radius"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Radius", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("pointlightEditorMenuChoice")->createButton("color", fvec2(0.0f, positions[1]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("pointlightEditorMenuChoice")->createButton("intensity", fvec2(0.0f, positions[2]), TEXT_SIZE("Intensity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("pointlightEditorMenuChoice")->createButton("shape", fvec2(0.0f, positions[3]), TEXT_SIZE("Shape"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Shape", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("pointlightEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[4]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("pointlightEditorMenuMain");
	rightWindow->setActiveScreen("empty");
}

void PointlightEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	leftWindow->deleteScreen("pointlightEditorMenuMain");
	leftWindow->deleteScreen("pointlightEditorMenuChoice");

	leftWindow->setActiveScreen("main");
	rightWindow->setActiveScreen("main");
}

void PointlightEditor::update()
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
		_updatePointlightCreating();
	}
	if(isLoaded())
	{
		_updatePointlightChoosing();
	}
	if(isLoaded())
	{
		_updatePointlightDeleting();
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