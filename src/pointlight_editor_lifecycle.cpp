#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)
#define POSITIONS(count) Mathematics::calculateDistributedPositions(count, CH, false)

#include "pointlight_editor.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void PointlightEditor::_load()
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
	_fe3d->model_create(LAMP_ID, LAMP_MESH_PATH);
	_fe3d->model_setBasePosition(LAMP_ID, LAMP_POSITION);
	_fe3d->model_setBaseSize(LAMP_ID, LAMP_SIZE);
	_fe3d->model_setShadowed(LAMP_ID, false);
	_fe3d->model_setBright(LAMP_ID, "", true);
	_fe3d->model_setVisible(LAMP_ID, false);
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
	_fe3d->graphics_setShadowPositionOffset(fvec3(GRID_SIZE * 0.5f));
	_fe3d->graphics_setShadowSize(Mathematics::calculateMagnitude(fvec3(GRID_SIZE * 0.5f)));
	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d->camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonEnabled(true);
	_fe3d->camera_setThirdPersonYaw(INITIAL_CAMERA_YAW);
	_fe3d->camera_setThirdPersonPitch(INITIAL_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);

	_gui->getOverlay()->createTextField(POINTLIGHT_TITLE_ID, POINTLIGHT_TITLE_POSITION, POINTLIGHT_TITLE_SIZE, "", fvec3(1.0f), true);
}

void PointlightEditor::_unload()
{
	for(const auto & pointlightId : _loadedPointlightIds)
	{
		_fe3d->pointlight_delete(pointlightId);
	}

	_fe3d->model_delete(GRID_ID);
	_fe3d->model_delete(BOX_ID);
	_fe3d->model_delete(LAMP_ID);
	_fe3d->graphics_setAntiAliasingEnabled(false);
	_fe3d->graphics_setAnisotropicFilteringQuality(0);
	_fe3d->graphics_setAmbientLightingEnabled(false);
	_fe3d->graphics_setAmbientLightingIntensity(0.0f);
	_fe3d->graphics_setDirectionalLightingEnabled(false);
	_fe3d->graphics_setDirectionalLightingPosition(fvec3(0.0f));
	_fe3d->graphics_setDirectionalLightingIntensity(0.0f);
	_fe3d->graphics_setShadowsEnabled(false);
	_fe3d->graphics_setShadowLightness(0.0f);
	_fe3d->graphics_setShadowQuality(0);
	_fe3d->graphics_setShadowPositionOffset(fvec3(0.0f));
	_fe3d->graphics_setShadowSize(0.0f);
	_fe3d->camera_reset();

	_gui->getOverlay()->deleteTextField(POINTLIGHT_TITLE_ID);

	_loadedPointlightIds.clear();
}

void PointlightEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	rightWindow->createScreen("pointlightEditorMenuMain");
	rightWindow->getScreen("pointlightEditorMenuMain")->createButton("create", fvec2(0.0f, POSITIONS(4)[0]), TEXT_SIZE("Create Pointlight"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Pointlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("pointlightEditorMenuMain")->createButton("edit", fvec2(0.0f, POSITIONS(4)[1]), TEXT_SIZE("Edit Pointlight"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Pointlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("pointlightEditorMenuMain")->createButton("delete", fvec2(0.0f, POSITIONS(4)[2]), TEXT_SIZE("Delete Pointlight"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Pointlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("pointlightEditorMenuMain")->createButton("back", fvec2(0.0f, POSITIONS(4)[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("pointlightEditorMenuChoice");
	rightWindow->getScreen("pointlightEditorMenuChoice")->createButton("radius", fvec2(0.0f, POSITIONS(5)[0]), TEXT_SIZE("Radius"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Radius", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("pointlightEditorMenuChoice")->createButton("color", fvec2(0.0f, POSITIONS(5)[1]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("pointlightEditorMenuChoice")->createButton("intensity", fvec2(0.0f, POSITIONS(5)[2]), TEXT_SIZE("Intensity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("pointlightEditorMenuChoice")->createButton("shape", fvec2(0.0f, POSITIONS(5)[3]), TEXT_SIZE("Shape: CIRCLE"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Shape: CIRCLE", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("pointlightEditorMenuChoice")->createButton("back", fvec2(0.0f, POSITIONS(5)[4]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("empty");

	rightWindow->setActiveScreen("pointlightEditorMenuMain");
}

void PointlightEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	rightWindow->deleteScreen("pointlightEditorMenuMain");
	rightWindow->deleteScreen("pointlightEditorMenuChoice");

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