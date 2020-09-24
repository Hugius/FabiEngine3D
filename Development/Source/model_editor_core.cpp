#include "model_editor.hpp"
#include "left_viewport_controller.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

#define GW(text) LVPC::calcTextWidth(text, 0.15f, 1.8f)

ModelEditor::ModelEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void ModelEditor::initializeGUI()
{
	// Private window instance of left viewport
	_leftWindow = _gui->getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - modelManagement
	_leftWindow->addScreen("modelEditorMenuMain");
	_leftWindow->getScreen("modelEditorMenuMain")->addButton("addModel", vec2(0.0f, 0.63f), vec2(GW("Add model"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Add model", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMain")->addButton("editModel", vec2(0.0f, 0.21), vec2(GW("Edit model"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit model", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMain")->addButton("deleteModel", vec2(0.0f, -0.21), vec2(GW("Delete model"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Delete model", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - modelEditingMain
	_leftWindow->addScreen("modelEditorMenuChoice");
	_leftWindow->getScreen("modelEditorMenuChoice")->addButton("mesh", vec2(0.0f, 0.7f), vec2(GW("3D mesh"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "3D mesh", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuChoice")->addButton("options", vec2(0.0f, 0.35f), vec2(GW("Options"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Options", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuChoice")->addButton("lighting", vec2(0.0f, 0.0f), vec2(GW("Lighting"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Lighting", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuChoice")->addButton("size", vec2(0.0f, -0.35f), vec2(GW("Size"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Size", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuChoice")->addButton("back", vec2(0.0f, -0.7f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - modelEditorMenuMesh
	_leftWindow->addScreen("modelEditorMenuMesh");
	_leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadOBJ", vec2(0.0f, 0.75f), vec2(GW("Load OBJ"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Load OBJ", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadDiffuseMap", vec2(0.0f, 0.45f), vec2(GW("DiffuseMap"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "DiffuseMap", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadLightMap", vec2(0.0f, 0.15f), vec2(GW("LightMap"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "LightMap", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadReflectionMap", vec2(0.0f, -0.15f), vec2(GW("ReflectMap"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "ReflectMap", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMesh")->addButton("loadNormalMap", vec2(0.0f, -0.45f), vec2(GW("NormalMap"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "NormalMap", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuMesh")->addButton("back", vec2(0.0f, -0.75f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - modelEditorMenuOptions
	_leftWindow->addScreen("modelEditorMenuOptions");
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("isFaceculled", vec2(0.0f, 0.75f), vec2(GW("Culling: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Culling: OFF", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("isTransparent", vec2(0.0f, 0.45f), vec2(GW("Alpha: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Alpha: OFF", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("setColor", vec2(0.0f, 0.15f), vec2(GW("Set color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Set color", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("uvRepeat", vec2(0.0f, -0.15f), vec2(GW("Set UV-repeat"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Set UV-repeat", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("lodID", vec2(0.0f, -0.45f), vec2(GW("Level of detail"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Level of detail", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuOptions")->addButton("back", vec2(0.0f, -0.75f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - modelEditorMenuLighting
	_leftWindow->addScreen("modelEditorMenuLighting");
	_leftWindow->getScreen("modelEditorMenuLighting")->addButton("isSpecular", vec2(0.0f, 0.7875f), vec2(GW("Specular: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular: OFF", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuLighting")->addButton("specularFactor", vec2(0.0f, 0.525f), vec2(GW("Specular factor"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular factor", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuLighting")->addButton("specularIntensity", vec2(0.0f, 0.2625f), vec2(GW("Specular intensity"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Specular power", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuLighting")->addButton("modelLightness", vec2(0.0f, 0.0f), vec2(GW("Lightness"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Lightness", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuLighting")->addButton("isShadowed", vec2(0.0f, -0.2625f), vec2(GW("Shadowed : ON"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Shadowed : ON", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuLighting")->addButton("isReflectiveSurface", vec2(0.0f, -0.525f), vec2(GW("Reflective : ON"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Reflective : ON", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuLighting")->addButton("back", vec2(0.0f, -0.7875f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - modelEditorMenuSize
	_leftWindow->addScreen("modelEditorMenuSize");
	_leftWindow->getScreen("modelEditorMenuSize")->addButton("setSize", vec2(0.0f, 0.75f), vec2(GW("Set mesh size"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Set mesh size", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuSize")->addButton("toggleResizeMesh", vec2(0.0f, 0.45f), vec2(GW("Mesh resize: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Mesh resize: OFF", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuSize")->addButton("toggleBoxView", vec2(0.0f, 0.15f), vec2(GW("Hitbox: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Hitbox: OFF", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuSize")->addButton("toggleResizeBox", vec2(0.0f, -0.15f), vec2(GW("Box resize: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Box resize: OFF", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuSize")->addButton("resizeBoxDir", vec2(0.0f, -0.45f), vec2(GW("Direction: X"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Direction: X", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen("modelEditorMenuSize")->addButton("back", vec2(0.0f, -0.75f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
}

void ModelEditor::load()
{
	// Load all OBJ filenames from assets folder
	_loadObjFileNames();

	// Camera
	_fe3d.camera_load(_fe3d.camera_getFOV(), 0.1f, 10000.0f, _defaultCameraPosition);
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
	_fe3d.skyEntity_select("@@editorSky");
	_fe3d.gameEntity_add("@@cube", "engine\\models\\cube.obj", vec3(0.0f), vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
	_fe3d.gameEntity_setDiffuseMap("@@cube", "engine\\textures\\cube.png");
	_fe3d.gameEntity_setFaceCulled("@@cube", true);

	// Other
	loadModels();
	_gui->getGlobalScreen()->addTextfield("selectedModelName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_gui->getViewport("bottom")->getWindow("controls")->setActiveScreen("modelEditor");
	_fe3d.gameEntity_setLevelOfDetailDistance(10000.0f);
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

	// 3D environment
	_fe3d.gameEntity_delete("@@cube");

	// Delete models
	_fe3d.gameEntity_deleteAll();

	// Delete model name textfield
	_gui->getGlobalScreen()->deleteTextfield("selectedModelName");

	// Other
	_modelCreationEnabled = false;
	_modelChoosingEnabled = false;
	_modelEditingEnabled = false;
	_meshResizingToggled = false;
	_boxResizingToggled = false;
	_modelRemovalEnabled = false;
	_aabbRenderingEnabled = false;
	_isLoaded = false;
	_totalCursorDifference = vec2(0.0f);
	_cameraAcceleration = vec2(0.0f);
	_lastCursorPos = vec2(0.0f);
	_modelResizeDirection = Direction::X;
	_cameraDistance = 5.0f;
	_currentModelName = "";
	_modelNames.clear();
	_objFileNamesList.clear();
	_gui->getViewport("bottom")->getWindow("controls")->setActiveScreen("mainMenu");
}