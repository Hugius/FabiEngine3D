#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "water_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void WaterEditor::_load()
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

	_gui->getOverlay()->createTextField("waterId", fvec2(0.0f, 0.85f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
}

void WaterEditor::_unload()
{
	for(const auto & id : _loadedWaterIds)
	{
		_fe3d->water_delete(id);
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

	_gui->getOverlay()->deleteTextField("waterId");

	_loadedWaterIds.clear();
}

void WaterEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = Mathematics::calculateDistributedPositions(4, CH, false);
	leftWindow->createScreen("waterEditorMenuMain");
	leftWindow->getScreen("waterEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create Water"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Water", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Water"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Water", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), TEXT_SIZE("Delete Water"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Water", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(4, CH, false);
	leftWindow->createScreen("waterEditorMenuChoice");
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("texturing", fvec2(0.0f, positions[0]), TEXT_SIZE("Texturing"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Texturing", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("lighting", fvec2(0.0f, positions[1]), TEXT_SIZE("Lighting"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lighting", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("miscellaneous", fvec2(0.0f, positions[2]), TEXT_SIZE("Miscellaneous"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Miscellaneous", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(6, CH, false);
	leftWindow->createScreen("waterEditorMenuTexturing");
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("dudvMap", fvec2(0.0f, positions[0]), TEXT_SIZE("DUDV Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "DUDV Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("normalMap", fvec2(0.0f, positions[1]), TEXT_SIZE("Normal Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Normal Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("displaceMap", fvec2(0.0f, positions[2]), TEXT_SIZE("Displace Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Displace Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("clearMaps", fvec2(0.0f, positions[3]), TEXT_SIZE("Clear Maps"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear Maps", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("textureRepeat", fvec2(0.0f, positions[4]), TEXT_SIZE("Texture Repeat"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Texture Repeat", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("back", fvec2(0.0f, positions[5]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(8, CH, false);
	leftWindow->createScreen("waterEditorMenuLighting");
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("color", fvec2(0.0f, positions[0]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("isReflective", fvec2(0.0f, positions[1]), TEXT_SIZE("Reflective: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Reflective: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("isRefractive", fvec2(0.0f, positions[2]), TEXT_SIZE("Refractive: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Refractive: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("isSpecular", fvec2(0.0f, positions[3]), TEXT_SIZE("Specular: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("isEdged", fvec2(0.0f, positions[4]), TEXT_SIZE("Edged: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edged: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("specularShininess", fvec2(0.0f, positions[5]), TEXT_SIZE("Specular Shininess"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular Shininess", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("specularIntensity", fvec2(0.0f, positions[6]), TEXT_SIZE("Specular Intensity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Specular Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("back", fvec2(0.0f, positions[7]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(6, CH, false);
	leftWindow->createScreen("waterEditorMenuMiscellaneous");
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("size", fvec2(0.0f, positions[0]), TEXT_SIZE("Size"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Size", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("waveHeight", fvec2(0.0f, positions[1]), TEXT_SIZE("Wave Height"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Wave Height", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("maxDepth", fvec2(0.0f, positions[2]), TEXT_SIZE("Max Depth"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Max Depth", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("rippleSpeed", fvec2(0.0f, positions[3]), TEXT_SIZE("Ripple Speed"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Ripple Speed", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("waveSpeed", fvec2(0.0f, positions[4]), TEXT_SIZE("Wave Speed"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Wave Speed", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("back", fvec2(0.0f, positions[5]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);
}

void WaterEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("waterEditorMenuMain");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("waterEditorMenuChoice");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("waterEditorMenuTexturing");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("waterEditorMenuLighting");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("waterEditorMenuMiscellaneous");
}

void WaterEditor::update()
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
		_updateCamera();
	}
	if(isLoaded())
	{
		_updateMiscellaneous();
	}
}