#include "scene_editor.hpp"
#include "left_viewport_controller.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

SceneEditor::SceneEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui, WorldEditor& worldEditor, ModelEditor& modelEditor, BillboardEditor& billboardEditor) :
	_fe3d(fe3d),
	_gui(gui),
	_worldEditor(worldEditor),
	_modelEditor(modelEditor),
	_billboardEditor(billboardEditor)
{

}

void SceneEditor::initializeGUI()
{
	// Private window instance of GUI windows
	_leftWindow = _gui->getViewport("left")->getWindow("main");
	_rightWindow = _gui->getViewport("right")->getWindow("main");

	// Left-viewport: mainWindow - sceneEditorMenuMain
	_leftWindow->addScreen("sceneEditorMenuMain");
	_leftWindow->getScreen("sceneEditorMenuMain")->addButton("sceneEditorMenuModel", vec2(0.0f, 0.75f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Models", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("sceneEditorMenuMain")->addButton("sceneEditorMenuBillboard", vec2(0.0f, 0.45f), vec2(1.7f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Billboards", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("sceneEditorMenuMain")->addButton("sceneEditorMenuLighting", vec2(0.0f, 0.15f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Lighting", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("sceneEditorMenuMain")->addButton("sceneEditorMenuAudio", vec2(0.0f, -0.15f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Audio", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("sceneEditorMenuMain")->addButton("sceneEditorMenuSettings", vec2(0.0f, -0.45f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Settings", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("sceneEditorMenuMain")->addButton("back", vec2(0.0f, -0.75f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	
	// Left-viewport: mainWindow - sceneEditorMenuModel
	_leftWindow->addScreen("sceneEditorMenuModel");
	_leftWindow->getScreen("sceneEditorMenuModel")->addButton("sceneEditorMenuModelPlace", vec2(0.0f, 0.475f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Place model", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("sceneEditorMenuModel")->addButton("sceneEditorMenuModelChoice", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Choose model", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("sceneEditorMenuModel")->addButton("back", vec2(0.0f, -0.475f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuModelPlace
	_leftWindow->addScreen("sceneEditorMenuModelPlace");
	_leftWindow->getScreen("sceneEditorMenuModelPlace")->addScrollingList("modelList", vec2(0.0f, 0.1f), vec2(1.8, 1.75f), vec3(0.3f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, LeftViewportController::textColor, LeftViewportController::textHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen("sceneEditorMenuModelPlace")->addButton("back", vec2(0.0f, -0.9f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	
	// Left-viewport: mainWindow - sceneEditorMenuModelChoice
	_leftWindow->addScreen("sceneEditorMenuModelChoice");
	_leftWindow->getScreen("sceneEditorMenuModelChoice")->addScrollingList("modelList", vec2(0.0f, 0.1f), vec2(1.8, 1.75f), vec3(0.3f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, LeftViewportController::textColor, LeftViewportController::textHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen("sceneEditorMenuModelChoice")->addButton("back", vec2(0.0f, -0.9f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuBillboard
	_leftWindow->addScreen("sceneEditorMenuBillboard");
	_leftWindow->getScreen("sceneEditorMenuBillboard")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuLighting
	_leftWindow->addScreen("sceneEditorMenuLighting");
	_leftWindow->getScreen("sceneEditorMenuLighting")->addButton("ambient", vec2(0.0f, 0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Ambient", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("sceneEditorMenuLighting")->addButton("directional", vec2(0.0f, 0.21f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Directional", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("sceneEditorMenuLighting")->addButton("point", vec2(0.0f, -0.21f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Point", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("sceneEditorMenuLighting")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuLightingAmbient
	_leftWindow->addScreen("sceneEditorMenuLightingAmbient");
	_leftWindow->getScreen("sceneEditorMenuLightingAmbient")->addButton("color", vec2(0.0f, 0.475f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Color", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("sceneEditorMenuLightingAmbient")->addButton("intensity", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "intensity", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("sceneEditorMenuLightingAmbient")->addButton("back", vec2(0.0f, -0.475f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuLightingDirectional
	_leftWindow->addScreen("sceneEditorMenuLightingDirectional");
	_leftWindow->getScreen("sceneEditorMenuLightingDirectional")->addButton("color", vec2(0.0f, 0.63f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Color", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("sceneEditorMenuLightingDirectional")->addButton("position", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Position", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("sceneEditorMenuLightingDirectional")->addButton("intensity", vec2(0.0f, -0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "intensity", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("sceneEditorMenuLightingDirectional")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	
	// Left-viewport: mainWindow - sceneEditorMenuLightingPoint
	_leftWindow->addScreen("sceneEditorMenuLightingPoint");
	_leftWindow->getScreen("sceneEditorMenuLightingPoint")->addButton("add", vec2(0.0f, 0.45f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Add light", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("sceneEditorMenuLightingPoint")->addButton("back", vec2(0.0f, -0.45f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettings
	_leftWindow->addScreen("sceneEditorMenuSettings");
	_leftWindow->getScreen("sceneEditorMenuSettings")->addButton("graphics", vec2(0.0f, 0.475f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Graphics", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("sceneEditorMenuSettings")->addButton("setSpeed", vec2(0.0f, 0.0f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Editor speed", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("sceneEditorMenuSettings")->addButton("back", vec2(0.0f, -0.475f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Right-viewport: mainWindow - modelProperties
	_rightWindow->addScreen("modelPropertiesMenu");
	_rightWindow->getScreen("modelPropertiesMenu")->addTextfield("transformation", vec2(0.0f, 0.95f), vec2(1.75f, 0.1f), "Transformation", vec3(1.0f));
	_rightWindow->getScreen("modelPropertiesMenu")->addButton("translation", vec2(0.0f, 0.8f), vec2(0.75f, 0.2f), "translation.png", vec3(0.0f));
	_rightWindow->getScreen("modelPropertiesMenu")->addButton("rotation", vec2(0.0f, 0.55f), vec2(0.75f, 0.2f), "rotation.png", vec3(0.0f));
	_rightWindow->getScreen("modelPropertiesMenu")->addButton("scaling", vec2(0.0f, 0.3f), vec2(0.75f, 0.2f), "scaling.png", vec3(0.0f));
	_rightWindow->getScreen("modelPropertiesMenu")->addButton("freeze", vec2(0.0f, 0.13f), vec2(1.25f, 0.075f), vec3(0.0f, 0.0f, 0.75f), vec3(0.25f, 0.25f, 1.0f), "Freeze", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_rightWindow->getScreen("modelPropertiesMenu")->addButton("delete", vec2(0.0f, -0.03f), vec2(1.25f, 0.075f), vec3(0.75f, 0.0f, 0.0f), vec3(1.0f, 0.25f, 0.25f), "Delete", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_rightWindow->getScreen("modelPropertiesMenu")->addTextfield("x", vec2(0.0f, -0.15f), vec2(0.25f, 0.1f), "X", vec3(1.0f));
	_rightWindow->getScreen("modelPropertiesMenu")->addTextfield("y", vec2(0.0f, -0.4f), vec2(0.25f, 0.1f), "Y", vec3(1.0f));
	_rightWindow->getScreen("modelPropertiesMenu")->addTextfield("z", vec2(0.0f, -0.65f), vec2(0.25f, 0.1f), "Z", vec3(1.0f));
	_rightWindow->getScreen("modelPropertiesMenu")->addButton("xPlus", vec2(0.75f, -0.25f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("modelPropertiesMenu")->addButton("yPlus", vec2(0.75f, -0.5f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("modelPropertiesMenu")->addButton("zPlus", vec2(0.75f, -0.75f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("modelPropertiesMenu")->addButton("xMinus", vec2(-0.75f, -0.25f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("modelPropertiesMenu")->addButton("yMinus", vec2(-0.75f, -0.5f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("modelPropertiesMenu")->addButton("zMinus", vec2(-0.75f, -0.75f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("modelPropertiesMenu")->addWriteField("x", vec2(0.0f, -0.25f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("modelPropertiesMenu")->addWriteField("y", vec2(0.0f, -0.5f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("modelPropertiesMenu")->addWriteField("z", vec2(0.0f, -0.75f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);

	// Right-viewport: mainWindow - lightProperties
	_rightWindow->addScreen("pointLightPropertiesMenu");
	_rightWindow->getScreen("pointLightPropertiesMenu")->addTextfield("intensity", vec2(0.0f, 0.95f), vec2(1.5f, 0.1f), "Intensity", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addButton("intensityPlus", vec2(0.75f, 0.85f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addButton("intensityMinus", vec2(-0.75f, 0.85f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addWriteField("intensity", vec2(0.0f, 0.85f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("pointLightPropertiesMenu")->addTextfield("distance", vec2(0.0f, 0.725f), vec2(1.5f, 0.1f), "Distance", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addButton("distancePlus", vec2(0.75f, 0.625f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addButton("distanceMinus", vec2(-0.75f, 0.625f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addWriteField("distance", vec2(0.0f, 0.625f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("pointLightPropertiesMenu")->addTextfield("x", vec2(0.0f, 0.5f), vec2(0.25f, 0.1f), "X", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addButton("xPlus", vec2(0.75f, 0.4f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addButton("xMinus", vec2(-0.75f, 0.4f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addWriteField("x", vec2(0.0f, 0.4f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("pointLightPropertiesMenu")->addTextfield("y", vec2(0.0f, 0.275f), vec2(0.25f, 0.1f), "Y", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addButton("yPlus", vec2(0.75f, 0.175f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addButton("yMinus", vec2(-0.75f, 0.175f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addWriteField("y", vec2(0.0f, 0.175f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("pointLightPropertiesMenu")->addTextfield("z", vec2(0.0f, 0.05f), vec2(0.25f, 0.1f), "Z", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addButton("zPlus", vec2(0.75f, -0.05f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addButton("zMinus", vec2(-0.75f, -0.05f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addWriteField("z", vec2(0.0f, -0.05f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("pointLightPropertiesMenu")->addTextfield("r", vec2(0.0f, -0.175f), vec2(0.25f, 0.1f), "R", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addButton("rPlus", vec2(0.75f, -0.275f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addButton("rMinus", vec2(-0.75f, -0.275f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addWriteField("r", vec2(0.0f, -0.275f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("pointLightPropertiesMenu")->addTextfield("g", vec2(0.0f, -0.4f), vec2(0.25f, 0.1f), "G", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addButton("gPlus", vec2(0.75f, -0.5f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addButton("gMinus", vec2(-0.75f, -0.5f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addWriteField("g", vec2(0.0f, -0.5f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("pointLightPropertiesMenu")->addTextfield("b", vec2(0.0f, -0.625f), vec2(0.25f, 0.1f), "B", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addButton("bPlus", vec2(0.75f, -0.725f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addButton("bMinus", vec2(-0.75f, -0.725f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("pointLightPropertiesMenu")->addWriteField("b", vec2(0.0f, -0.725f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("pointLightPropertiesMenu")->addButton("delete", vec2(0.0f, -0.9f), vec2(1.5f, 0.1f), vec3(0.75f, 0.0f, 0.0f), vec3(1.0f, 0.25f, 0.25f), "Delete", LeftViewportController::textColor, LeftViewportController::textHoverColor);
}

void SceneEditor::load()
{
	// Enable default graphics
	_fe3d.gfx_enableAmbientLighting(vec3(1.0f), 1.0f);
	_fe3d.gfx_enableFog(150.0f, vec3(0.75f));
	_fe3d.gfx_enableDOF(50.0f);
	_fe3d.gfx_enableSkyHDR(0.35f);
	vec3 camPos = _fe3d.camera_getPosition();
	_fe3d.gfx_enableShadows(vec3(camPos.x + 100.0f, 75.0f, camPos.z), vec3(camPos.x, 0.0f, camPos.z), 200.0f, 200.0f);
	_fe3d.gfx_enableLensFlare("User\\Assets\\Textures\\FlareMaps\\flare.png");
	
	// Disable default skybox
	_fe3d.skyEntity_select("");

	// Load world entities
	_worldEditor.loadSkyEntity();
	_worldEditor.loadTerrainEntity();
	_worldEditor.loadWaterEntity();

	// Show sky entity
	if (_fe3d.skyEntity_isExisting("@sky"))
	{
		_fe3d.skyEntity_show("@sky");
	}

	// Show terrain entity
	if (_fe3d.terrainEntity_isExisting("@terrain"))
	{
		_fe3d.terrainEntity_show("@terrain");
	}

	// Show water entity
	if (_fe3d.waterEntity_isExisting("@water"))
	{
		_fe3d.waterEntity_show("@water");
	}

	// Camera properties
	float height = 0.0f;

	// Set camera height relative to water size
	if (_fe3d.waterEntity_isExisting("@water"))
	{
		float size = _fe3d.waterEntity_getSize("@water") / 2.0f;
		height = _fe3d.waterEntity_getPosition("@water").y + (size / 10.0f);
	}

	// Terrain can overwrite camera height
	if (_fe3d.terrainEntity_isExisting("@terrain"))
	{
		height = _fe3d.terrainEntity_getMaxHeight("@terrain");
	}

	// Load camera
	_fe3d.camera_setPosition(vec3(0.0f, height, 0.0f));

	// Preview model loading
	_modelEditor.loadModels();
	for (auto& modelName : _modelEditor.getModelNames())
	{
		// Check if there is a game entity present
		if (_fe3d.gameEntity_isExisting(modelName))
		{
			_leftWindow->getScreen("sceneEditorMenuModelPlace")->getScrollingList("modelList")->addButton(modelName, modelName.substr(1, modelName.size() - 1));
		}
	}

	// Preview pointlight loading
	_fe3d.lightEntity_add(_previewPointlightID);
	_fe3d.lightEntity_hide(_previewPointlightID);
	_fe3d.gameEntity_add(_previewPointlightID, "Engine\\OBJs\\lamp.obj", vec3(0.0f), vec3(0.0f), _defaultLightbulbSize, false);
	_fe3d.gameEntity_setShadowed(_previewPointlightID, false);

	// Create name textfields
	_gui->getGlobalScreen()->addTextfield("selectedModelName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_gui->getGlobalScreen()->addTextfield("selectedBillboardName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_gui->getGlobalScreen()->addTextfield("selectedPointlightName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));

	// Load world file
	loadWorld();

	float angle = atan2f(_fe3d.gfx_getDirectionalLightingPosition().z,_fe3d.gfx_getDirectionalLightingPosition().x) * 
		(180.0f / 3.14159265359f);
	_fe3d.billBoardEntity_add("sun", "Engine\\Textures\\sun.png", _fe3d.gfx_getDirectionalLightingPosition(), vec3(0.0f, angle, 0.0f), vec2(300.0f), true, false, false, true);


	// Other
	_isLoaded = true;
}

void SceneEditor::loadWorld()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	string filePath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\Scenes\\scene.fe3d";

	// Load world file
	if (_fe3d.misc_isFileExisting(filePath)) // Check if models file exists
	{
		std::ifstream file(filePath);
		string line;

		// Read model data
		while (std::getline(file, line))
		{
			// Placeholder variables
			string entityType;

			// For item extraction
			std::istringstream iss(line);

			// Extract type from file
			iss >> entityType;

			// Load entity according to type
			if (entityType == "MODEL")
			{
				// Values
				string modelID, objPath, diffuseMapPath, lightMapPath, reflectionMapPath;
				vec3 position, rotation, size, color, aabbSize;
				float uvRepeat, specularFactor;
				bool isFaceculled, isShadowed, isTransparent, isSpecular, isFrozen;

				// Load model data
				iss >> modelID >> position.x >> position.y >> position.z >> rotation.x >> rotation.y >> rotation.z >>
					size.x >> size.y >> size.z >> objPath >> diffuseMapPath >> lightMapPath >> reflectionMapPath >>
					isFaceculled >> isShadowed >> isTransparent >> isSpecular >> isFrozen >> specularFactor >>
					color.r >> color.g >> color.b >> uvRepeat >> aabbSize.x >> aabbSize.y >> aabbSize.z;

				// Perform empty string & space conversions
				objPath = (objPath == "?") ? "" : objPath;
				diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
				lightMapPath = (lightMapPath == "?") ? "" : lightMapPath;
				reflectionMapPath = (reflectionMapPath == "?") ? "" : reflectionMapPath;
				std::replace(objPath.begin(), objPath.end(), '?', ' ');
				std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
				std::replace(lightMapPath.begin(), lightMapPath.end(), '?', ' ');
				std::replace(reflectionMapPath.begin(), reflectionMapPath.end(), '?', ' ');

				// Extract the model name from the model ID
				string modelName = "";
				for (auto& name : _modelEditor.getModelNames())
				{
					if (modelID.substr(0, name.size() - 1) == name.substr(1, name.size() - 1))
					{
						modelName = name;
					}
				}

				// Add the model
				_placeModel(modelID, position, rotation, size, objPath, diffuseMapPath, lightMapPath, reflectionMapPath, isFaceculled, isShadowed, isTransparent, isSpecular,
					specularFactor, color, uvRepeat, aabbSize);
			}
			else if (entityType == "BILLBOARD")
			{

			}
			else if (entityType == "AMBIENT")
			{
				// Values
				vec3 ambientLightingColor;
				float ambientLightingIntensity;

				// Extract
				iss >> ambientLightingColor.r >> ambientLightingColor.g >> ambientLightingColor.b >> ambientLightingIntensity;

				// Apply
				_fe3d.gfx_enableAmbientLighting(ambientLightingColor, ambientLightingIntensity);
			}
			else if (entityType == "DIRECTIONAL")
			{
				// Values
				vec3 directionalLightingPosition, directionalLightingColor;
				float directionalLightingIntensity;

				// Extract
				iss >> directionalLightingPosition.x >> directionalLightingPosition.y >> directionalLightingPosition.z >>
					directionalLightingColor.r >> directionalLightingColor.g >> directionalLightingColor.b >> directionalLightingIntensity;

				// Apply
				_fe3d.gfx_enableDirectionalLighting(directionalLightingPosition, directionalLightingColor, directionalLightingIntensity);
			}
			else if (entityType == "POINT")
			{
				// Values
				string ID;
				vec3 position, color;
				float intensity, distance;

				// Extract line data
				iss >> ID >> position.x >> position.y >> position.z >> color.r >> color.g >> color.b >> intensity >> distance;

				// Add entities
				_fe3d.gameEntity_add("@" + ID, "Engine\\OBJs\\lamp.obj", position, vec3(0.0f), _defaultLightbulbSize);
				_fe3d.gameEntity_setShadowed("@" + ID, false);
				_fe3d.aabbEntity_bindToGameEntity("@" + ID, _defaultLightbulbAabbSize, true);
				_fe3d.lightEntity_add(ID, position, color, intensity, distance);
			}
			else if (entityType == "SPEED")
			{
				iss >> _customCameraSpeed;
			}
			else if (entityType == "POSITION")
			{
				vec3 position;
				iss >> position.x >> position.y >> position.z;
				_fe3d.camera_setPosition(position);
			}
			else if (entityType == "YAW")
			{
				float yaw;
				iss >> yaw;
				_fe3d.camera_setYaw(yaw);
			}
			else if (entityType == "PITCH")
			{
				float pitch;
				iss >> pitch;
				_fe3d.camera_setPitch(pitch);
			}
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Scene data from project \"" + _currentProjectName + "\" loaded!");
	}
}

void SceneEditor::save()
{
	if (_isLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		// Create or overwrite models file
		std::ofstream file;
		file.open(_fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\Scenes\\scene.fe3d");

		// Write game entities data into file
		for (auto& entityID : _fe3d.gameEntity_getAllIDs())
		{
			// Check if not preview model
			if (entityID[0] != '@')
			{
				// Retrieve all values to be saved
				auto position = _fe3d.gameEntity_getPosition(entityID);
				auto rotation = _fe3d.gameEntity_getRotation(entityID);
				auto size = _fe3d.gameEntity_getSize(entityID);
				auto objPath = _fe3d.gameEntity_getObjPath(entityID);
				auto diffuseMapPath = _fe3d.gameEntity_getDiffuseMapPath(entityID);
				auto lightMapPath = _fe3d.gameEntity_getLightMapPath(entityID);
				auto reflectionMapPath = _fe3d.gameEntity_getReflectionMapPath(entityID);
				auto isFaceCulled = _fe3d.gameEntity_isFaceCulled(entityID);
				auto isShadowed = _fe3d.gameEntity_isShadowed(entityID);
				auto isTransparent = _fe3d.gameEntity_isTransparent(entityID);
				auto isSpecular = _fe3d.gameEntity_isSpecularLighted(entityID);
				auto isFrozen = _fe3d.gameEntity_isStaticToCamera(entityID);
				auto specularFactor = _fe3d.gameEntity_getSpecularFactor(entityID);
				auto color = _fe3d.gameEntity_getColor(entityID);
				auto uvRepeat = _fe3d.gameEntity_getUvRepeat(entityID);
				auto aabbSize = _fe3d.aabbEntity_getSize(entityID);

				// Perform empty string & space conversions
				diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
				lightMapPath = (lightMapPath == "") ? "?" : lightMapPath;
				reflectionMapPath = (reflectionMapPath == "") ? "?" : reflectionMapPath;
				std::replace(objPath.begin(), objPath.end(), ' ', '?');
				std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
				std::replace(lightMapPath.begin(), lightMapPath.end(), ' ', '?');
				std::replace(reflectionMapPath.begin(), reflectionMapPath.end(), ' ', '?');

				// 1 model -> 1 line in file
				file << 
					"MODEL " <<
					entityID << " " <<
					position.x << " " <<
					position.y << " " <<
					position.z << " " <<
					rotation.x << " " <<
					rotation.y << " " <<
					rotation.z << " " <<
					size.x << " " <<
					size.y << " " <<
					size.z << " " <<
					objPath << " " <<
					diffuseMapPath << " " <<
					lightMapPath << " " <<
					reflectionMapPath << " " <<
					isFaceCulled << " " <<
					isShadowed << " " <<
					isTransparent << " " <<
					isSpecular << " " <<
					isFrozen << " " << 
					specularFactor << " " <<
					color.r << " " <<
					color.g << " " <<
					color.b << " " <<
					uvRepeat << " " <<
					aabbSize.x << " " <<
					aabbSize.y << " " <<
					aabbSize.z << std::endl;
			}
		}

		// Ambient lighting
		vec3 ambientLightingColor = _fe3d.gfx_getAmbientLightingColor();
		float ambientLightingIntensity = _fe3d.gfx_getAmbientLightingIntensity();

		file << 
			"AMBIENT " <<
			ambientLightingColor.r << " " <<
			ambientLightingColor.g << " " <<
			ambientLightingColor.b << " " <<
			ambientLightingIntensity << std::endl;

		// Directional lighting
		vec3 directionalLightingColor = _fe3d.gfx_getDirectionalLightingColor();
		vec3 directionalLightingPosition = _fe3d.gfx_getDirectionalLightingPosition();
		float directionalLightingIntensity = _fe3d.gfx_geDirectionalLightingIntensity();

		file << 
			"DIRECTIONAL " <<
			directionalLightingPosition.x << " " <<
			directionalLightingPosition.y << " " <<
			directionalLightingPosition.z << " " <<
			directionalLightingColor.r << " " <<
			directionalLightingColor.g << " " <<
			directionalLightingColor.b << " " <<
			directionalLightingIntensity << std::endl;

		// Point lights
		for (auto& entityID : _fe3d.lightEntity_getAllIDs())
		{
			// Check if not preview model
			if (entityID[0] != '@')
			{
				auto position = _fe3d.lightEntity_getPosition(entityID);
				auto color = _fe3d.lightEntity_getColor(entityID);
				auto intensity = _fe3d.lightEntity_getIntensity(entityID);
				auto distance = _fe3d.lightEntity_getDistanceFactor(entityID);

				// Write line to file
				file << 
					"POINT " <<
					entityID << " " <<
					position.x << " " <<
					position.y << " " <<
					position.z << " " <<
					color.r << " " <<
					color.g << " " <<
					color.b << " " <<
					intensity << " " <<
					distance << std::endl;
			}
		}

		// Editor camera speed
		file << "SPEED " << _customCameraSpeed << std::endl;

		// Editor camera position
		vec3 position = _fe3d.camera_getPosition();
		file << "POSITION " << position.x << " " << position.y << " " << position.z << std::endl;

		// Editor camera yaw
		file << "YAW " << _fe3d.camera_getYaw() << std::endl;

		// Editor camera pitch
		file << "PITCH " << _fe3d.camera_getPitch() << std::endl;

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Scene data from project \"" + _currentProjectName + "\" saved!");
	}
}

void SceneEditor::unload()
{
	// Disable graphics
	_fe3d.gfx_disableAmbientLighting();
	_fe3d.gfx_disableDirectionalLighting();
	_fe3d.gfx_disableSkyHDR();
	_fe3d.gfx_disableShadows();
	_fe3d.gfx_disableFog();
	_fe3d.gfx_disableDOF();

	// Delete sky entity
	if (_fe3d.skyEntity_isExisting("@sky"))
	{
		_fe3d.skyEntity_delete("@sky");
	}

	// Delete terrain entity
	if (_fe3d.terrainEntity_isExisting("@terrain"))
	{
		_fe3d.terrainEntity_delete("@terrain");
	}

	// Delete water entity
	if (_fe3d.waterEntity_isExisting("@water"))
	{
		_fe3d.waterEntity_delete("@water");
	}

	// Delete placed entities
	_fe3d.gameEntity_deleteAll();
	_fe3d.billboardEntity_deleteAll();
	_fe3d.lightEntity_deleteAll();

	// Reset variables
	_currentPreviewModelName = "";
	_currentBillboardName = "";
	_selectedModelID = "";
	_activeModelID = "";
	_selectedLightnessMultiplier = 1;
	_activeLightnessMultiplier = 1;
	_isPlacingPointlight = false;
	_isLoaded = false;
	_transformation = Transformation::TRANSLATION;
	_customCameraSpeed = 10.0f;
	_selectedLightSizeMultiplier = 1;
	_activeLightSizeMultiplier = 1;
	_activeLightBulbID = "";

	// Delete name textfields
	_gui->getGlobalScreen()->deleteTextfield("selectedModelName");
	_gui->getGlobalScreen()->deleteTextfield("selectedBillboardName");
	_gui->getGlobalScreen()->deleteTextfield("selectedPointlightName");

	// Enable default skybox
	_fe3d.skyEntity_select("@@sky");

	// Camera
	_fe3d.camera_setPosition(vec3(0.0f));
	_fe3d.camera_setYaw(0.0f);
	_fe3d.camera_setPitch(0.0f);
	_fe3d.camera_disableFirstPersonView();

	// Other
	_leftWindow->getScreen("sceneEditorMenuModelPlace")->getScrollingList("modelList")->deleteButtons();
	_fe3d.misc_disableAabbFrameRendering();
}