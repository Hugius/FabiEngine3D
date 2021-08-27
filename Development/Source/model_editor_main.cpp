#include "model_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

using std::numeric_limits;

#define TW(text) VPC::calculateTextWidth(text, CW)

ModelEditor::ModelEditor(FabiEngine3D& fe3d, EngineGuiManager& gui)
	:
	_fe3d(fe3d),
	_gui(gui)
{

}

void ModelEditor::load()
{
	// GUI
	_loadGUI();

	// Camera
	_fe3d.camera_reset();
	_fe3d.camera_setMouseSensitivity(MOUSE_SENSITIVITY);
	_fe3d.camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d.camera_enableThirdPersonView(INITIAL_CAMERA_YAW, INITIAL_CAMERA_PITCH);
	_fe3d.camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);
	_fe3d.camera_setThirdPersonLookat(Vec3(0.0f, -GRID_Y_OFFSET, 0.0f));

	// Default graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 1.0f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(10000.0f), Vec3(1.0f), 3.0f);
	_fe3d.gfx_setPlanarReflectionHeight(0.0f);
	_fe3d.gfx_enableBloom(BloomType::PARTS, 1.0f, 5);
	_fe3d.gfx_enableMotionBlur(0.1f);
	
	// Editor models
	_fe3d.modelEntity_create("@@cube", "engine_assets\\meshes\\cube.obj");
	_fe3d.modelEntity_setPosition("@@cube", Vec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.modelEntity_setDiffuseMap("@@cube", "engine_assets\\textures\\cube.png");
	_fe3d.modelEntity_setFaceCulled("@@cube", true);
	_fe3d.modelEntity_create("@@grid", "engine_assets\\meshes\\plane.obj");
	_fe3d.modelEntity_setPosition("@@grid", Vec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.modelEntity_setSize("@@grid", Vec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d.modelEntity_setDiffuseMap("@@grid", "engine_assets\\textures\\grid.png");
	_fe3d.modelEntity_setUvRepeat("@@grid", GRID_UV);
	_fe3d.modelEntity_setTransparent("@@grid", true);
	_fe3d.modelEntity_setShadowed("@@grid", false);

	// Miscellaneous
	_fe3d.reflectionEntity_create("@@reflection");
	_fe3d.reflectionEntity_capture("@@reflection");
	_gui.getGlobalScreen()->createTextField("modelID", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->createTextField("aabbID", Vec2(0.0f, 0.75f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("modelEditorControls");
	_fe3d.misc_setLevelOfDetailDistance(numeric_limits<float>::max());
	_isEditorLoaded = true;
}

void ModelEditor::unload()
{
	// GUI
	_unloadGUI();

	// Camera
	if (_fe3d.camera_isThirdPersonViewEnabled())
	{
		_fe3d.camera_disableThirdPersonView();
	}

	// Shadows
	if (_fe3d.gfx_isShadowsEnabled())
	{
		_fe3d.gfx_disableShadows(true);
	}

	// Default graphics
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableBloom(true);
	_fe3d.gfx_disableMotionBlur(true);

	// Delete models
	_fe3d.modelEntity_deleteAll();

	// Properties
	_loadedModelIDs.clear();
	_currentModelID = "";
	_currentAabbID = "";
	_hoveredModelID = "";
	_aabbTransformationSpeed = 0.1f;
	_isCreatingModel = false;
	_isChoosingModel = false;
	_isEditingModel = false;
	_isDeletingModel = false;
	_isMovingToggled = false;
	_isResizingToggled = false;
	_isEditorLoaded = false;
	_transformationDirection = Direction::X;

	// Miscellaneous
	_fe3d.reflectionEntity_delete("@@reflection");
	_gui.getGlobalScreen()->deleteTextField("modelID");
	_gui.getGlobalScreen()->deleteTextField("aabbID");
	if (_fe3d.misc_isAabbFrameRenderingEnabled())
	{
		_fe3d.misc_disableAabbFrameRendering();
	}
	if (_fe3d.misc_isDebugRenderingEnabled())
	{
		_fe3d.misc_disableDebugRendering();
	}
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
}

void ModelEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: modelEditorMenuMain
	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("modelEditorMenuMain");
	leftWindow->getScreen("modelEditorMenuMain")->createButton("create", Vec2(0.0f, positions[0]), Vec2(TW("Create Model"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMain")->createButton("edit", Vec2(0.0f, positions[1]), Vec2(TW("Edit Model"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMain")->createButton("delete", Vec2(0.0f, positions[2]), Vec2(TW("Delete Model"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMain")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: modelEditorMenuChoice
	positions = VPC::calculateButtonPositions(6, CH);
	leftWindow->createScreen("modelEditorMenuChoice");
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("mesh", Vec2(0.0f, positions[0]), Vec2(TW("3D mesh"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "3D mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("options", Vec2(0.0f, positions[1]), Vec2(TW("Options"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Options", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("lighting", Vec2(0.0f, positions[2]), Vec2(TW("Lighting"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lighting", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("size", Vec2(0.0f, positions[3]), Vec2(TW("Size"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("aabb", Vec2(0.0f, positions[4]), Vec2(TW("AABB"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "AABB", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuChoice")->createButton("back", Vec2(0.0f, positions[5]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: modelEditorMenuMesh
	positions = VPC::calculateButtonPositions(7, CH);
	leftWindow->createScreen("modelEditorMenuMesh");
	leftWindow->getScreen("modelEditorMenuMesh")->createButton("loadDiffuseMap", Vec2(0.0f, positions[0]), Vec2(TW("Diffuse Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Diffuse Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMesh")->createButton("loadEmissionMap", Vec2(0.0f, positions[1]), Vec2(TW("Emission Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Emission Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMesh")->createButton("loadReflectionMap", Vec2(0.0f, positions[2]), Vec2(TW("Reflect Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflect Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMesh")->createButton("loadNormalMap", Vec2(0.0f, positions[3]), Vec2(TW("Normal Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMesh")->createButton("clearMaps", Vec2(0.0f, positions[4]), Vec2(TW("Clear Maps"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Clear Maps", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMesh")->createButton("back", Vec2(0.0f, positions[5]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: modelEditorMenuOptions
	positions = VPC::calculateButtonPositions(7, CH);
	leftWindow->createScreen("modelEditorMenuOptions");
	leftWindow->getScreen("modelEditorMenuOptions")->createButton("isFaceculled", Vec2(0.0f, positions[0]), Vec2(TW("Culling: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Culling: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuOptions")->createButton("isTransparent", Vec2(0.0f, positions[1]), Vec2(TW("Alpha: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Alpha: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuOptions")->createButton("isInstanced", Vec2(0.0f, positions[2]), Vec2(TW("Instanced: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Instanced: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuOptions")->createButton("color", Vec2(0.0f, positions[3]), Vec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuOptions")->createButton("uvRepeat", Vec2(0.0f, positions[4]), Vec2(TW("UV Repeat"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "UV Repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuOptions")->createButton("lodID", Vec2(0.0f, positions[5]), Vec2(TW("Level Of Detail"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Level Of Detail", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuOptions")->createButton("back", Vec2(0.0f, positions[6]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: modelEditorMenuLighting
	positions = VPC::calculateButtonPositions(8, CH);
	leftWindow->createScreen("modelEditorMenuLighting");
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("isSpecular", Vec2(0.0f, positions[0]), Vec2(TW("Specular: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("specularFactor", Vec2(0.0f, positions[1]), Vec2(TW("Spec Factor"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec Factor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("specularIntensity", Vec2(0.0f, positions[2]), Vec2(TW("Spec Intensity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("lightness", Vec2(0.0f, positions[3]), Vec2(TW("Lightness"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("isBright", Vec2(0.0f, positions[4]), Vec2(TW("Bright: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Bright: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("reflectionType", Vec2(0.0f, positions[5]), Vec2(TW("Reflect: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflect: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("reflectivity", Vec2(0.0f, positions[6]), Vec2(TW("Reflectivity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflectivity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuLighting")->createButton("back", Vec2(0.0f, positions[7]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: modelEditorMenuSize
	positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("modelEditorMenuSize");
	leftWindow->getScreen("modelEditorMenuSize")->createButton("size", Vec2(0.0f, positions[0]), Vec2(TW("Size"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuSize")->createButton("toggleResize", Vec2(0.0f, positions[1]), Vec2(TW("Resize: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Resize: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuSize")->createButton("direction", Vec2(0.0f, positions[2]), Vec2(TW("Direction: X"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Direction: X", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuSize")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: modelEditorMenuAabb
	positions = VPC::calculateButtonPositions(8, CH);
	leftWindow->createScreen("modelEditorMenuAabb");
	leftWindow->getScreen("modelEditorMenuAabb")->createButton("create", Vec2(0.0f, positions[0]), Vec2(TW("Create AABB"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create AABB", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->createButton("edit", Vec2(0.0f, positions[1]), Vec2(TW("Edit AABB"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit AABB", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->createButton("delete", Vec2(0.0f, positions[2]), Vec2(TW("Delete"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->createButton("speed", Vec2(0.0f, positions[3]), Vec2(TW("Speed"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->createButton("toggleMove", Vec2(0.0f, positions[4]), Vec2(TW("Move: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Move: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->createButton("toggleResize", Vec2(0.0f, positions[5]), Vec2(TW("Resize: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Resize: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->createButton("direction", Vec2(0.0f, positions[6]), Vec2(TW("Direction: X"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Direction: X", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->createButton("back", Vec2(0.0f, positions[7]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void ModelEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("modelEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("modelEditorMenuChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("modelEditorMenuMesh");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("modelEditorMenuOptions");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("modelEditorMenuLighting");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("modelEditorMenuSize");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("modelEditorMenuAabb");
}