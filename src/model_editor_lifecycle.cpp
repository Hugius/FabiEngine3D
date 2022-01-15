#define TW(text) VPC::calculateTextWidth(text, CW)

#include "model_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

using std::numeric_limits;

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

void ModelEditor::load()
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
	_fe3d->model_setTextureRepeat("@@grid", "", GRID_UV);
	_fe3d->model_setShadowed("@@grid", false);

	_fe3d->reflection_create("@@reflection");
	_fe3d->reflection_capture("@@reflection");

	_gui->getOverlay()->createTextField("modelID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(0.0f), true);
	_gui->getOverlay()->createTextField("partID", fvec2(0.0f, 0.75f), fvec2(0.5f, 0.1f), "", fvec3(0.0f), true);
	_gui->getOverlay()->createTextField("aabbID", fvec2(0.0f, 0.75f), fvec2(0.5f, 0.1f), "", fvec3(0.0f), true);

	_isEditorLoaded = true;
}

void ModelEditor::unload()
{
	for(const auto& ID : _loadedModelIDs)
	{
		_fe3d->model_delete(ID);
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

	_fe3d->reflection_delete("@@reflection");

	_gui->getOverlay()->deleteTextField("modelID");
	_gui->getOverlay()->deleteTextField("partID");
	_gui->getOverlay()->deleteTextField("aabbID");

	_loadedModelIDs.clear();
	_currentModelID = "";
	_currentPartID = "";
	_currentAabbID = "";
	_hoveredModelID = "";
	_hoveredPartID = "";
	_selectedPartHighlightDirection = 1;
	_isCreatingModel = false;
	_isChoosingModel = false;
	_isDeletingModel = false;
	_isCreatingAabb = false;
	_isChoosingAabb = false;
	_isDeletingAabb = false;
	_isEditorLoaded = false;

	if(_fe3d->misc_isAabbFrameRenderingEnabled())
	{
		_fe3d->misc_disableAabbFrameRendering();
	}
}

void ModelEditor::_loadGUI()
{
	auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("modelEditorMenuMain");
	leftWindow->getScreen("modelEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create Model"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit Model"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete Model"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	positions = VPC::calculateButtonPositions(6, CH);
	leftWindow->createScreen("modelEditorMenuChoice");
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("part", fvec2(0.0f, positions[0]), fvec2(TW("Select Part"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Select Part", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("texturing", fvec2(0.0f, positions[1]), fvec2(TW("Texturing"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Texturing", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("lighting", fvec2(0.0f, positions[2]), fvec2(TW("Lighting"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lighting", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("miscellaneous", fvec2(0.0f, positions[3]), fvec2(TW("Miscellaneous"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Miscellaneous", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("aabb", fvec2(0.0f, positions[4]), fvec2(TW("AABB"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "AABB", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[5]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	positions = VPC::calculateButtonPositions(8, CH);
	leftWindow->createScreen("modelEditorMenuTexturing");
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("diffuseMap", fvec2(0.0f, positions[0]), fvec2(TW("Diffuse Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Diffuse Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("emissionMap", fvec2(0.0f, positions[1]), fvec2(TW("Emission Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Emission Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("specularMap", fvec2(0.0f, positions[2]), fvec2(TW("Specular Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("reflectionMap", fvec2(0.0f, positions[3]), fvec2(TW("Reflect Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflect Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("normalMap", fvec2(0.0f, positions[4]), fvec2(TW("Normal Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("clearMaps", fvec2(0.0f, positions[5]), fvec2(TW("Clear Maps"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Clear Maps", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("textureRepeat", fvec2(0.0f, positions[6]), fvec2(TW("Texture Repeat"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Texture Repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuTexturing")->createButton("back", fvec2(0.0f, positions[7]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	positions = VPC::calculateButtonPositions(9, CH);
	leftWindow->createScreen("modelEditorMenuLighting");
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("color", fvec2(0.0f, positions[0]), fvec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("lightness", fvec2(0.0f, positions[1]), fvec2(TW("Lightness"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("isSpecular", fvec2(0.0f, positions[2]), fvec2(TW("Specular: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("specularShininess", fvec2(0.0f, positions[3]), fvec2(TW("Specular Shininess"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular Shininess", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("specularIntensity", fvec2(0.0f, positions[4]), fvec2(TW("Specular Intensity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("isReflective", fvec2(0.0f, positions[5]), fvec2(TW("Reflective: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflective: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("reflectionType", fvec2(0.0f, positions[6]), fvec2(TW("Type: NONE"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Type: NONE", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("reflectivity", fvec2(0.0f, positions[7]), fvec2(TW("Reflectivity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflectivity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("back", fvec2(0.0f, positions[8]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	positions = VPC::calculateButtonPositions(6, CH);
	leftWindow->createScreen("modelEditorMenuMiscellaneous");
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("size", fvec2(0.0f, positions[0]), fvec2(TW("Size"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("isFaceCulled", fvec2(0.0f, positions[1]), fvec2(TW("Culling: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Culling: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("levelOfDetailEntityID", fvec2(0.0f, positions[2]), fvec2(TW("LOD Entity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "LOD Entity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("levelOfDetailDistance", fvec2(0.0f, positions[3]), fvec2(TW("LOD Distance"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "LOD Distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("rotationOrder", fvec2(0.0f, positions[4]), fvec2(TW("Rotation: Y X Z"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rotation : Y X Z", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuMiscellaneous")->createButton("back", fvec2(0.0f, positions[5]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("modelEditorMenuAabbMain");
	leftWindow->getScreen("modelEditorMenuAabbMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create AABB"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create AABB", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuAabbMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit AABB"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit AABB", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuAabbMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuAabbMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("modelEditorMenuAabbChoice");
	leftWindow->getScreen("modelEditorMenuAabbChoice")->createButton("position", fvec2(0.0f, positions[0]), fvec2(TW("Position"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Position", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuAabbChoice")->createButton("size", fvec2(0.0f, positions[1]), fvec2(TW("Size"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelEditorMenuAabbChoice")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
}

void ModelEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("modelEditorMenuMain");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("modelEditorMenuChoice");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("modelEditorMenuTexturing");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("modelEditorMenuLighting");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("modelEditorMenuMiscellaneous");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("modelEditorMenuAabbMain");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("modelEditorMenuAabbChoice");
}

void ModelEditor::update()
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
		_updateTexturingMenu();
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
		_updateMainAabbMenu();
	}
	if(_isEditorLoaded)
	{
		_updateChoiceAabbMenu();
	}
	if(_isEditorLoaded)
	{
		_updateModelCreating();
	}
	if(_isEditorLoaded)
	{
		_updateModelChoosing();
	}
	if(_isEditorLoaded)
	{
		_updateModelDeleting();
	}
	if(_isEditorLoaded)
	{
		_updatePartChoosing();
	}
	if(_isEditorLoaded)
	{
		_updateAabbCreating();
	}
	if(_isEditorLoaded)
	{
		_updateAabbChoosing();
	}
	if(_isEditorLoaded)
	{
		_updateAabbDeleting();
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