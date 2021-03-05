#include "model_editor.hpp"
#include "left_viewport_controller.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

#define GW(text) LVPC::calcTextWidth(text, 0.15f, 1.8f)

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
	leftWindow->getScreen("modelEditorMenuMain")->addButton("addModel", Vec2(0.0f, 0.63f), Vec2(GW("Add model"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Add model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMain")->addButton("editModel", Vec2(0.0f, 0.21f), Vec2(GW("Edit model"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMain")->addButton("deleteModel", Vec2(0.0f, -0.21f), Vec2(GW("Delete model"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMain")->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - modelEditorMenuChoice
	leftWindow->addScreen("modelEditorMenuChoice");
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("mesh", Vec2(0.0f, 0.75f), Vec2(GW("3D mesh"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "3D mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("options", Vec2(0.0f, 0.45f), Vec2(GW("Options"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Options", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("lighting", Vec2(0.0f, 0.15f), Vec2(GW("Lighting"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lighting", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("size", Vec2(0.0f, -0.15f), Vec2(GW("Size"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("aabb", Vec2(0.0f, -0.45f), Vec2(GW("AABB"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "AABB", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("back", Vec2(0.0f, -0.75f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - modelEditorMenuMesh
	leftWindow->addScreen("modelEditorMenuMesh");
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadMesh", Vec2(0.0f, 0.75f), Vec2(GW("Load mesh"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Load mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadDiffuseMap", Vec2(0.0f, 0.45f), Vec2(GW("DiffuseMap"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "DiffuseMap", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadLightMap", Vec2(0.0f, 0.15f), Vec2(GW("LightMap"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "LightMap", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadReflectionMap", Vec2(0.0f, -0.15f), Vec2(GW("ReflectMap"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "ReflectMap", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadNormalMap", Vec2(0.0f, -0.45f), Vec2(GW("NormalMap"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "NormalMap", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("back", Vec2(0.0f, -0.75f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	
	// Left-viewport: mainWindow - modelEditorMenuOptions
	leftWindow->addScreen("modelEditorMenuOptions");
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("isFaceculled", Vec2(0.0f, 0.7875f), Vec2(GW("Culling: OFF"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Culling: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("isTransparent", Vec2(0.0f, 0.525f), Vec2(GW("Alpha: OFF"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Alpha: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("isInstanced", Vec2(0.0f, 0.2625f), Vec2(GW("Instanced: OFF"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Instanced: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("setColor", Vec2(0.0f, 0.0f), Vec2(GW("Set color"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Set color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("uvRepeat", Vec2(0.0f, -0.2625f), Vec2(GW("Set UV-repeat"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Set UV-repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("lodID", Vec2(0.0f, -0.525f), Vec2(GW("Level of detail"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Level of detail", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("back", Vec2(0.0f, -0.7875f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - modelEditorMenuLighting
	leftWindow->addScreen("modelEditorMenuLighting");
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("isSpecular", Vec2(0.0f, 0.7875f), Vec2(GW("Specular: OFF"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("specularFactor", Vec2(0.0f, 0.525f), Vec2(GW("Spec factor"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec factor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("specularIntensity", Vec2(0.0f, 0.2625f), Vec2(GW("Spec intensity"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("lightness", Vec2(0.0f, 0.0f), Vec2(GW("Lightness"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("isShadowed", Vec2(0.0f, -0.2625f), Vec2(GW("Shadowed : ON"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Shadowed : ON", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("reflectionType", Vec2(0.0f, -0.525f), Vec2(GW("Reflection: OFF"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflection: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("back", Vec2(0.0f, -0.7875f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - modelEditorMenuSize
	leftWindow->addScreen("modelEditorMenuSize");
	leftWindow->getScreen("modelEditorMenuSize")->addButton("setSize", Vec2(0.0f, 0.63f), Vec2(GW("Set mesh size"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Set mesh size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuSize")->addButton("toggleResize", Vec2(0.0f, 0.21f), Vec2(GW("Mesh resize: OFF"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Mesh resize: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuSize")->addButton("direction", Vec2(0.0f, -0.21f), Vec2(GW("Direction: X"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Direction: X", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuSize")->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - modelEditorMenuAabb
	leftWindow->addScreen("modelEditorMenuAabb");
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("add", Vec2(0.0f, 0.83f), Vec2(GW("Create AABB"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create AABB", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("edit", Vec2(0.0f, 0.59f), Vec2(GW("Edit AABB"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit AABB", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("delete", Vec2(0.0f, 0.36f), Vec2(GW("Delete"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("speed", Vec2(0.0f, 0.13f), Vec2(GW("Set speed"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Set speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("toggleMove", Vec2(0.0f, -0.13f), Vec2(GW("Box move: OFF"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Box move: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("toggleResize", Vec2(0.0f, -0.36f), Vec2(GW("Box resize: OFF"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Box resize: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("direction", Vec2(0.0f, -0.59f), Vec2(GW("Direction: X"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Direction: X", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("back", Vec2(0.0f, -0.83f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
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
	// GUI
	_loadGUI();

	// Load all mesh filenames from assets folder
	_loadMeshFileNames();

	// Camera
	_fe3d.camera_load(90.0f, 0.1f, 10000.0f, DEFAULT_CAMERA_POSITION);
	_fe3d.camera_enableLookatView();

	// Enable graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 0.75f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(1000.0f), Vec3(1.0f), 0.5f);
	_fe3d.gfx_enableSceneReflections(0.5f);
	_fe3d.gfx_enableSkyReflections(0.5f);
	_fe3d.gfx_enableLightMapping();
	_fe3d.gfx_enableNormalMapping();
	_fe3d.gfx_enableSpecularLighting();
	
	// 3D Environment
	_fe3d.gameEntity_add("@@cube", "engine_assets\\meshes\\cube.obj", Vec3(0.0f), Vec3(0.0f), Vec3(1.0f));
	_fe3d.gameEntity_setDiffuseMap("@@cube", "engine_assets\\textures\\cube.png");
	_fe3d.gameEntity_setFaceCulled("@@cube", true);
	_fe3d.gameEntity_add("@@grid", "engine_assets\\meshes\\plane.obj", Vec3(0.0f), Vec3(0.0f), Vec3(50.0f, 1.0f, 50.0f));
	_fe3d.gameEntity_setDiffuseMap("@@grid", "engine_assets\\textures\\grid.png");
	_fe3d.gameEntity_setUvRepeat("@@grid", 5.0f);
	_fe3d.gameEntity_setTransparent("@@grid", true);

	// Miscellaneous
	loadGameEntitiesFromFile();
	_gui.getGlobalScreen()->addTextfield("selectedModelName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedAabbName", Vec2(0.0f, 0.75f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_fe3d.gameEntity_setLevelOfDetailDistance(10000.0f);
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("modelEditorControls");
	_isEditorLoaded = true;
}

void ModelEditor::unload()
{
	// GUI
	_unloadGUI();

	// Disable graphics
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableShadows(true);
	_fe3d.gfx_disableSceneReflections(true);
	_fe3d.gfx_disableSkyReflections(true);
	_fe3d.gfx_disableLightMapping(true);
	_fe3d.gfx_disableNormalMapping(true);
	_fe3d.gfx_disableSpecularLighting(true);

	// Delete models
	_fe3d.gameEntity_deleteAll();

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
	_cameraSpeed = 0.1f;
	_cameraScrollingAcceleration = 0.0f;
	_aabbTransformationSpeed = 0.1f;
	_isCreatingModel = false;
	_isChoosingModel = false;
	_isEditingModel = false;
	_movingToggled = false;
	_resizingToggled = false;
	_isDeletingModel = false;
	_isEditorLoaded = false;
	_transformationDirection = Direction::X;

	// Miscellaneous
	_gui.getGlobalScreen()->deleteTextfield("selectedModelName");
	_gui.getGlobalScreen()->deleteTextfield("selectedAabbName");
	_fe3d.misc_disableAabbFrameRendering();
	_fe3d.misc_disableDebugRendering();
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_fe3d.input_setKeyTogglingLocked(false);
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
}