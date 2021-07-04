#include "model_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

#define CW(text) VPC::calculateTextWidth(text, 0.115f)

constexpr auto TH = 0.0875f;

ModelEditor::ModelEditor(FabiEngine3D& fe3d, EngineGuiManager& gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void ModelEditor::_loadGUI()
{
	// Private window instance of left viewport
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - modelEditorMenuMain
	leftWindow->addScreen("modelEditorMenuMain");
	leftWindow->getScreen("modelEditorMenuMain")->addButton("addModel", Vec2(0.0f, 0.63f), Vec2(CW("Add Model"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Add Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMain")->addButton("editModel", Vec2(0.0f, 0.21f), Vec2(CW("Edit Model"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMain")->addButton("deleteModel", Vec2(0.0f, -0.21f), Vec2(CW("Delete Model"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMain")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - modelEditorMenuChoice
	leftWindow->addScreen("modelEditorMenuChoice");
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("mesh", Vec2(0.0f, 0.75f), Vec2(CW("3D mesh"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "3D mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("options", Vec2(0.0f, 0.45f), Vec2(CW("Options"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Options", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("lighting", Vec2(0.0f, 0.15f), Vec2(CW("Lighting"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lighting", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("size", Vec2(0.0f, -0.15f), Vec2(CW("Size"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("aabb", Vec2(0.0f, -0.45f), Vec2(CW("AABB"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "AABB", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("back", Vec2(0.0f, -0.75f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - modelEditorMenuMesh
	leftWindow->addScreen("modelEditorMenuMesh");
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadMesh", Vec2(0.0f, 0.75f), Vec2(CW("Load Mesh"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Load Mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadDiffuseMap", Vec2(0.0f, 0.45f), Vec2(CW("Diffuse Map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Diffuse Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadLightMap", Vec2(0.0f, 0.15f), Vec2(CW("Light Map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Light Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadReflectionMap", Vec2(0.0f, -0.15f), Vec2(CW("Reflect Map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflect Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadNormalMap", Vec2(0.0f, -0.45f), Vec2(CW("Normal Map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("back", Vec2(0.0f, -0.75f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	
	// Left-viewport: mainWindow - modelEditorMenuOptions
	leftWindow->addScreen("modelEditorMenuOptions");
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("isFaceculled", Vec2(0.0f, 0.7875f), Vec2(CW("Culling: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Culling: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("isTransparent", Vec2(0.0f, 0.525f), Vec2(CW("Alpha: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Alpha: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("isInstanced", Vec2(0.0f, 0.2625f), Vec2(CW("Instanced: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Instanced: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("color", Vec2(0.0f, 0.0f), Vec2(CW("Color"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("uvRepeat", Vec2(0.0f, -0.2625f), Vec2(CW("UV Repeat"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "UV Repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("lodID", Vec2(0.0f, -0.525f), Vec2(CW("Level Of Detail"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Level Of Detail", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("back", Vec2(0.0f, -0.7875f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - modelEditorMenuLighting
	leftWindow->addScreen("modelEditorMenuLighting");
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("isSpecular", Vec2(0.0f, 0.75f), Vec2(CW("Specular: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("specularFactor", Vec2(0.0f, 0.45f), Vec2(CW("Spec factor"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec factor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("specularIntensity", Vec2(0.0f, 0.15f), Vec2(CW("Spec Intensity"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("lightness", Vec2(0.0f, -0.15f), Vec2(CW("Lightness"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("reflectionType", Vec2(0.0f, -0.45f), Vec2(CW("Reflect: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflect: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("back", Vec2(0.0f, -0.75f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - modelEditorMenuSize
	leftWindow->addScreen("modelEditorMenuSize");
	leftWindow->getScreen("modelEditorMenuSize")->addButton("size", Vec2(0.0f, 0.63f), Vec2(CW("Size"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuSize")->addButton("toggleResize", Vec2(0.0f, 0.21f), Vec2(CW("Resize: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Resize: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuSize")->addButton("direction", Vec2(0.0f, -0.21f), Vec2(CW("Direction: X"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Direction: X", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuSize")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - modelEditorMenuAabb
	leftWindow->addScreen("modelEditorMenuAabb");
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("add", Vec2(0.0f, 0.83f), Vec2(CW("Create AABB"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create AABB", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("edit", Vec2(0.0f, 0.59f), Vec2(CW("Edit AABB"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit AABB", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("delete", Vec2(0.0f, 0.36f), Vec2(CW("Delete"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("speed", Vec2(0.0f, 0.13f), Vec2(CW("Speed"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("toggleMove", Vec2(0.0f, -0.13f), Vec2(CW("Move: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Move: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("toggleResize", Vec2(0.0f, -0.36f), Vec2(CW("Resize: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Resize: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("direction", Vec2(0.0f, -0.59f), Vec2(CW("Direction: X"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Direction: X", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("back", Vec2(0.0f, -0.83f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void ModelEditor::_unloadGUI()
{
	auto leftWindow = _gui.getViewport("left")->getWindow("main");
	leftWindow->deleteScreen("modelEditorMenuMain");
	leftWindow->deleteScreen("modelEditorMenuChoice");
	leftWindow->deleteScreen("modelEditorMenuMesh");
	leftWindow->deleteScreen("modelEditorMenuOptions");
	leftWindow->deleteScreen("modelEditorMenuLighting");
	leftWindow->deleteScreen("modelEditorMenuSize");
	leftWindow->deleteScreen("modelEditorMenuAabb");
}

void ModelEditor::load()
{
	// Load all mesh filenames from assets folder
	_loadMeshFileNames();

	// GUI
	_loadGUI();

	// Camera
	_fe3d.camera_load(Config::DEFAULT_CAMERA_FOV, Config::DEFAULT_CAMERA_NEAR, Config::DEFAULT_CAMERA_FAR, CAMERA_POSITION, 0.0f, 0.0f);
	_fe3d.camera_enableLookatView();

	// Enable default graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 0.75f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(1000.0f), Vec3(1.0f), 0.5f);
	_fe3d.gfx_enableSceneReflections(0.5f);
	_fe3d.gfx_enableSkyReflections(0.5f);
	_fe3d.gfx_enableLightMapping();
	_fe3d.gfx_enableNormalMapping();
	_fe3d.gfx_enableSpecularLighting();
	
	// 3D Environment
	_fe3d.modelEntity_add("@@cube", "engine_assets\\meshes\\cube.obj", Vec3(0.0f), Vec3(0.0f), Vec3(1.0f));
	_fe3d.modelEntity_setDiffuseMap("@@cube", "engine_assets\\textures\\cube.png");
	_fe3d.modelEntity_setFaceCulled("@@cube", true);
	_fe3d.modelEntity_add("@@grid", "engine_assets\\meshes\\plane.obj", Vec3(0.0f), Vec3(0.0f), Vec3(50.0f, 1.0f, 50.0f));
	_fe3d.modelEntity_setDiffuseMap("@@grid", "engine_assets\\textures\\grid.png");
	_fe3d.modelEntity_setUvRepeat("@@grid", 5.0f);
	_fe3d.modelEntity_setTransparent("@@grid", true);

	// Miscellaneous
	loadModelEntitiesFromFile();
	_gui.getGlobalScreen()->addTextfield("selectedModelName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedAabbName", Vec2(0.0f, 0.75f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_fe3d.misc_setLevelOfDetailDistance(Config::DEFAULT_CAMERA_FAR);
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("modelEditorControls");
	_isEditorLoaded = true;
}

void ModelEditor::unload()
{
	// GUI
	_unloadGUI();

	// Camera
	_fe3d.camera_disableLookatView();

	// Disable default graphics
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableShadows(true);
	_fe3d.gfx_disableSceneReflections(true);
	_fe3d.gfx_disableSkyReflections(true);
	_fe3d.gfx_disableLightMapping(true);
	_fe3d.gfx_disableNormalMapping(true);
	_fe3d.gfx_disableSpecularLighting(true);

	// Delete models
	_fe3d.modelEntity_deleteAll();

	// Properties
	_currentModelID = "";
	_currentAabbID = "";
	_hoveredModelID = "";
	_loadedModelIDs.clear();
	_meshFileNames.clear();
	_cameraLookatPosition = Vec3(0.0f);
	_totalCursorDifference = Vec2(0.0f, 0.5f);
	_cameraAcceleration = Vec2(0.0f);
	_lastCursorPos = Vec2(0.0f);
	_cameraDistance = 5.0f;
	_cameraScrollingAcceleration = 0.0f;
	_aabbTransformationSpeed = 0.1f;
	_cameraSpeed = 0.1f;
	_isCreatingModel = false;
	_isChoosingModel = false;
	_isEditingModel = false;
	_isDeletingModel = false;
	_isMovingToggled = false;
	_isResizingToggled = false;
	_isEditorLoaded = false;
	_transformationDirection = Direction::X;

	// Miscellaneous
	_gui.getGlobalScreen()->deleteTextfield("selectedModelName");
	_gui.getGlobalScreen()->deleteTextfield("selectedAabbName");
	if (_fe3d.misc_isAabbFrameRenderingEnabled())
	{
		_fe3d.misc_disableAabbFrameRendering();
	}
	if (_fe3d.misc_isDebugRenderingEnabled())
	{
		_fe3d.misc_disableDebugRendering();
	}
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_fe3d.input_setKeyTogglingLocked(false);
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
}