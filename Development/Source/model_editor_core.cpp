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
	leftWindow->getScreen("modelEditorMenuMain")->addButton("addModel", vec2(0.0f, 0.63f), vec2(GW("Add model"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Add model", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuMain")->addButton("editModel", vec2(0.0f, 0.21f), vec2(GW("Edit model"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit model", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuMain")->addButton("deleteModel", vec2(0.0f, -0.21f), vec2(GW("Delete model"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Delete model", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - modelEditorMenuChoice
	leftWindow->addScreen("modelEditorMenuChoice");
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("mesh", vec2(0.0f, 0.75f), vec2(GW("3D mesh"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "3D mesh", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("options", vec2(0.0f, 0.45f), vec2(GW("Options"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Options", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("lighting", vec2(0.0f, 0.15f), vec2(GW("Lighting"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Lighting", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("size", vec2(0.0f, -0.15f), vec2(GW("Size"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Size", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("aabb", vec2(0.0f, -0.45f), vec2(GW("AABB"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "AABB", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuChoice")->addButton("back", vec2(0.0f, -0.75f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - modelEditorMenuMesh
	leftWindow->addScreen("modelEditorMenuMesh");
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadOBJ", vec2(0.0f, 0.75f), vec2(GW("Load OBJ"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Load OBJ", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadDiffuseMap", vec2(0.0f, 0.45f), vec2(GW("DiffuseMap"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "DiffuseMap", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadLightMap", vec2(0.0f, 0.15f), vec2(GW("LightMap"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "LightMap", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadReflectionMap", vec2(0.0f, -0.15f), vec2(GW("ReflectMap"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "ReflectMap", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadNormalMap", vec2(0.0f, -0.45f), vec2(GW("NormalMap"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "NormalMap", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuMesh")->addButton("back", vec2(0.0f, -0.75f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - modelEditorMenuOptions
	leftWindow->addScreen("modelEditorMenuOptions");
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("isFaceculled", vec2(0.0f, 0.7875f), vec2(GW("Culling: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Culling: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("isTransparent", vec2(0.0f, 0.525f), vec2(GW("Alpha: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Alpha: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("isInstanced", vec2(0.0f, 0.2625f), vec2(GW("Instanced: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Instanced: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("setColor", vec2(0.0f, 0.0f), vec2(GW("Set color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Set color", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("uvRepeat", vec2(0.0f, -0.2625f), vec2(GW("Set UV-repeat"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Set UV-repeat", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("lodID", vec2(0.0f, -0.525f), vec2(GW("Level of detail"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Level of detail", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuOptions")->addButton("back", vec2(0.0f, -0.7875f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - modelEditorMenuLighting
	leftWindow->addScreen("modelEditorMenuLighting");
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("isSpecular", vec2(0.0f, 0.7875f), vec2(GW("Specular: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("specularFactor", vec2(0.0f, 0.525f), vec2(GW("Specular factor"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular factor", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("specularIntensity", vec2(0.0f, 0.2625f), vec2(GW("Specular intensity"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular intensity", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("modelLightness", vec2(0.0f, 0.0f), vec2(GW("Lightness"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Lightness", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("isShadowed", vec2(0.0f, -0.2625f), vec2(GW("Shadowed : ON"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Shadowed : ON", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("isReflectiveSurface", vec2(0.0f, -0.525f), vec2(GW("Reflective : ON"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Reflective : ON", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuLighting")->addButton("back", vec2(0.0f, -0.7875f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - modelEditorMenuSize
	leftWindow->addScreen("modelEditorMenuSize");
	leftWindow->getScreen("modelEditorMenuSize")->addButton("setSize", vec2(0.0f, 0.63f), vec2(GW("Set mesh size"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Set mesh size", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuSize")->addButton("toggleResize", vec2(0.0f, 0.21f), vec2(GW("Mesh resize: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Mesh resize: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuSize")->addButton("direction", vec2(0.0f, -0.21f), vec2(GW("Direction: X"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Direction: X", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuSize")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - modelEditorMenuAabb
	leftWindow->addScreen("modelEditorMenuAabb");
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("add", vec2(0.0f, 0.83f), vec2(GW("Create AABB"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Create AABB", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("edit", vec2(0.0f, 0.59f), vec2(GW("Edit AABB"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit AABB", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("delete", vec2(0.0f, 0.36f), vec2(GW("Delete"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Delete", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("speed", vec2(0.0f, 0.13f), vec2(GW("Set speed"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Set speed", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("toggleMove", vec2(0.0f, -0.13f), vec2(GW("Box move: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Box move: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("toggleResize", vec2(0.0f, -0.36f), vec2(GW("Box resize: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Box resize: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("direction", vec2(0.0f, -0.59f), vec2(GW("Direction: X"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Direction: X", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("modelEditorMenuAabb")->addButton("back", vec2(0.0f, -0.83f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
}

void ModelEditor::load()
{
	// Load all OBJ filenames from assets folder
	_loadObjFileNames();

	// Camera
	_fe3d.camera_load(90.0f, 0.1f, 10000.0f, _defaultCameraPosition);
	_fe3d.camera_enableLookat(vec3(0.0f));

	// Enable graphics
	_fe3d.gfx_enableAmbientLighting(vec3(1.0f), 0.75f);
	_fe3d.gfx_enableDirectionalLighting(vec3(1000.0f), vec3(1.0f), 0.5f);
	_fe3d.gfx_enableShadows(vec3(100.0f, 75.0f, 0.0f), vec3(0.0f), 200.0f, 200.0f, false);
	_fe3d.gfx_enableSceneReflections(0.25f);
	_fe3d.gfx_enableSkyReflections(0.5f);
	_fe3d.gfx_enableLightMapping();
	_fe3d.gfx_enableNormalMapping();
	_fe3d.gfx_enableSpecularLighting();
	
	// 3D Environment
	_fe3d.gameEntity_add("@@cube", "engine\\models\\cube.obj", vec3(0.0f), vec3(0.0f), vec3(1.0f));
	_fe3d.gameEntity_setDiffuseMap("@@cube", "engine\\textures\\cube.png");
	_fe3d.gameEntity_setFaceCulled("@@cube", true);
	_fe3d.gameEntity_add("@@grid", "engine\\models\\plane.obj", vec3(0.0f), vec3(0.0f), vec3(50.0f, 1.0f, 50.0f));
	_fe3d.gameEntity_setDiffuseMap("@@grid", "engine\\textures\\grid.png");
	_fe3d.gameEntity_setUvRepeat("@@grid", 5.0f);
	_fe3d.gameEntity_setTransparent("@@grid", true);

	// Other
	loadGameEntitiesFromFile();
	_gui.getGlobalScreen()->addTextfield("selectedModelName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedAabbName", vec2(0.0f, 0.75f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_fe3d.gameEntity_setLevelOfDetailDistance(10000.0f);
	_fe3d.input_clearKeyToggles();
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
	_totalCursorDifference = vec2(0.0f);
	_cameraAcceleration = vec2(0.0f);
	_lastCursorPos = vec2(0.0f);
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
}