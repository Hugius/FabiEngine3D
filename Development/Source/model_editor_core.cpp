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

void ModelEditor::initializeGUI()
{
	// Private window instance of left viewport
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - modelEditorMenuMain
	leftWindow->addScreen("modelEditorMenuMain");
	leftWindow->getScreen("modelEditorMenuMain")->addButton("addModel", Vec2(0.0f, 0.63f), Vec2(GW("Add model"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Add model", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuMain")->addButton("editModel", Vec2(0.0f, 0.21f), Vec2(GW("Edit model"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit model", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuMain")->addButton("deleteModel", Vec2(0.0f, -0.21f), Vec2(GW("Delete model"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Delete model", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuMain")->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - modelEditorMenuChoice
	leftWindow->addScreen("modelEditorMenuChoice");
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("mesh", Vec2(0.0f, 0.75f), Vec2(GW("3D mesh"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "3D mesh", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("options", Vec2(0.0f, 0.45f), Vec2(GW("Options"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Options", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("lighting", Vec2(0.0f, 0.15f), Vec2(GW("Lighting"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Lighting", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("size", Vec2(0.0f, -0.15f), Vec2(GW("Size"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Size", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("aabb", Vec2(0.0f, -0.45f), Vec2(GW("AABB"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "AABB", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("back", Vec2(0.0f, -0.75f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - modelEditorMenuMesh
	leftWindow->addScreen("modelEditorMenuMesh");
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadOBJ", Vec2(0.0f, 0.75f), Vec2(GW("Load OBJ"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Load OBJ", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadDiffuseMap", Vec2(0.0f, 0.45f), Vec2(GW("DiffuseMap"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "DiffuseMap", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadLightMap", Vec2(0.0f, 0.15f), Vec2(GW("LightMap"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "LightMap", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadReflectionMap", Vec2(0.0f, -0.15f), Vec2(GW("ReflectMap"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "ReflectMap", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadNormalMap", Vec2(0.0f, -0.45f), Vec2(GW("NormalMap"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "NormalMap", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("back", Vec2(0.0f, -0.75f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - modelEditorMenuOptions
	leftWindow->addScreen("modelEditorMenuOptions");
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("isFaceculled", Vec2(0.0f, 0.7875f), Vec2(GW("Culling: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Culling: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("isTransparent", Vec2(0.0f, 0.525f), Vec2(GW("Alpha: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Alpha: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("isInstanced", Vec2(0.0f, 0.2625f), Vec2(GW("Instanced: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Instanced: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("setColor", Vec2(0.0f, 0.0f), Vec2(GW("Set color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Set color", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("uvRepeat", Vec2(0.0f, -0.2625f), Vec2(GW("Set UV-repeat"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Set UV-repeat", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("lodID", Vec2(0.0f, -0.525f), Vec2(GW("Level of detail"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Level of detail", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("back", Vec2(0.0f, -0.7875f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - modelEditorMenuLighting
	leftWindow->addScreen("modelEditorMenuLighting");
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("isSpecular", Vec2(0.0f, 0.7875f), Vec2(GW("Specular: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("specularFactor", Vec2(0.0f, 0.525f), Vec2(GW("Specular factor"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular factor", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("specularIntensity", Vec2(0.0f, 0.2625f), Vec2(GW("Specular intensity"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular intensity", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("modelLightness", Vec2(0.0f, 0.0f), Vec2(GW("Lightness"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Lightness", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("isShadowed", Vec2(0.0f, -0.2625f), Vec2(GW("Shadowed : ON"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Shadowed : ON", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("isReflectiveSurface", Vec2(0.0f, -0.525f), Vec2(GW("Reflective : ON"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Reflective : ON", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("back", Vec2(0.0f, -0.7875f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - modelEditorMenuSize
	leftWindow->addScreen("modelEditorMenuSize");
	leftWindow->getScreen("modelEditorMenuSize")->addButton("setSize", Vec2(0.0f, 0.63f), Vec2(GW("Set mesh size"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Set mesh size", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuSize")->addButton("toggleResize", Vec2(0.0f, 0.21f), Vec2(GW("Mesh resize: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Mesh resize: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuSize")->addButton("direction", Vec2(0.0f, -0.21f), Vec2(GW("Direction: X"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Direction: X", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuSize")->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - modelEditorMenuAabb
	leftWindow->addScreen("modelEditorMenuAabb");
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("add", Vec2(0.0f, 0.83f), Vec2(GW("Create AABB"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Create AABB", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("edit", Vec2(0.0f, 0.59f), Vec2(GW("Edit AABB"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit AABB", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("delete", Vec2(0.0f, 0.36f), Vec2(GW("Delete"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Delete", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("speed", Vec2(0.0f, 0.13f), Vec2(GW("Set speed"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Set speed", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("toggleMove", Vec2(0.0f, -0.13f), Vec2(GW("Box move: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Box move: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("toggleResize", Vec2(0.0f, -0.36f), Vec2(GW("Box resize: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Box resize: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("direction", Vec2(0.0f, -0.59f), Vec2(GW("Direction: X"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Direction: X", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("back", Vec2(0.0f, -0.83f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
}

void ModelEditor::load()
{
	// Load all OBJ filenames from assets folder
	_loadObjFileNames();

	// Camera
	_fe3d.camera_load(90.0f, 0.1f, 10000.0f, _defaultCameraPosition);
	_fe3d.camera_enableLookat(Vec3(0.0f));

	// Enable graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 0.75f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(1000.0f), Vec3(1.0f), 0.5f);
	_fe3d.gfx_enableShadows(Vec3(100.0f, 75.0f, 0.0f), Vec3(0.0f), 200.0f, 200.0f, false);
	_fe3d.gfx_enableSceneReflections(0.25f);
	_fe3d.gfx_enableSkyReflections(0.5f);
	_fe3d.gfx_enableLightMapping();
	_fe3d.gfx_enableNormalMapping();
	_fe3d.gfx_enableSpecularLighting();
	
	// 3D Environment
	_fe3d.gameEntity_add("@@cube", "engine\\models\\cube.obj", Vec3(0.0f), Vec3(0.0f), Vec3(1.0f));
	_fe3d.gameEntity_setDiffuseMap("@@cube", "engine\\textures\\cube.png");
	_fe3d.gameEntity_setFaceCulled("@@cube", true);
	_fe3d.gameEntity_add("@@grid", "engine\\models\\plane.obj", Vec3(0.0f), Vec3(0.0f), Vec3(50.0f, 1.0f, 50.0f));
	_fe3d.gameEntity_setDiffuseMap("@@grid", "engine\\textures\\grid.png");
	_fe3d.gameEntity_setUvRepeat("@@grid", 5.0f);
	_fe3d.gameEntity_setTransparent("@@grid", true);

	// Miscellaneous
	loadGameEntitiesFromFile();
	_gui.getGlobalScreen()->addTextfield("selectedModelName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedAabbName", Vec2(0.0f, 0.75f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_fe3d.gameEntity_setLevelOfDetailDistance(10000.0f);
	_fe3d.input_clearKeyToggles();
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("modelEditorControls");
	_isLoaded = true;
}

void ModelEditor::unload()
{
	// Disable graphics
	_fe3d.gfx_disableAmbientLighting();
	_fe3d.gfx_disableDirectionalLighting();
	_fe3d.gfx_disableShadows();
	_fe3d.gfx_disableSceneReflections();
	_fe3d.gfx_disableSkyReflections();
	_fe3d.gfx_disableLightMapping();
	_fe3d.gfx_disableNormalMapping();
	_fe3d.gfx_disableSpecularLighting();

	// Delete models
	_fe3d.gameEntity_deleteAll();

	// Properties
	_currentModelID = "";
	_currentAabbID = "";
	_hoveredModelID = "";
	_modelNames.clear();
	_objFileNamesList.clear();
	_totalCursorDifference = Vec2(0.0f);
	_cameraAcceleration = Vec2(0.0f);
	_lastCursorPos = Vec2(0.0f);
	_cameraDistance = 5.0f;
	_cameraScrollingAcceleration = 0.0f;
	_aabbTransformationSpeed = 1.0f;
	_isCreatingModel = false;
	_isChoosingModel = false;
	_isEditingModel = false;
	_movingToggled = false;
	_resizingToggled = false;
	_isDeletingModel = false;
	_isLoaded = false;
	_transformationDirection = Direction::X;

	// Miscellaneous
	_gui.getGlobalScreen()->deleteTextfield("selectedModelName");
	_gui.getGlobalScreen()->deleteTextfield("selectedAabbName");
	_fe3d.misc_disableAabbFrameRendering();
	_fe3d.misc_disableDebugRendering();
	_fe3d.input_clearKeyToggles();
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
}