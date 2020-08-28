#include "scene_editor.hpp"
#include "left_viewport_controller.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

#define GW(text) LVC::calcTextWidth(text, 0.15f, 1.8f)

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
	string screenID;

	// Left-viewport: mainWindow - sceneEditorMenuMain
	screenID = "sceneEditorMenuMain";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("sceneEditorMenuModel", vec2(0.0f, 0.75f), vec2(GW("Models"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Models", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("sceneEditorMenuBillboard", vec2(0.0f, 0.45f), vec2(GW("Billboards"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Billboards", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("sceneEditorMenuLighting", vec2(0.0f, 0.15f), vec2(GW("Lighting"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Lighting", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("sceneEditorMenuAudio", vec2(0.0f, -0.15f), vec2(GW("Audio"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Audio", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("sceneEditorMenuSettings", vec2(0.0f, -0.45f), vec2(GW("Settings"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Settings", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.75f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);
	
	// Left-viewport: mainWindow - sceneEditorMenuModel
	screenID = "sceneEditorMenuModel";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("sceneEditorMenuModelPlace", vec2(0.0f, 0.475f), vec2(GW("Place model"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Place model", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("sceneEditorMenuModelChoice", vec2(0.0f, 0.0f), vec2(GW("Choose model"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Choose model", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.475f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuModelPlace
	screenID = "sceneEditorMenuModelPlace";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addScrollingList("modelList", vec2(0.0f, 0.1f), vec2(1.8f, 1.75f), vec3(0.3f), LVC::buttonColor, LVC::buttonHoverColor, LVC::textColor, LVC::textHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.9f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);
	
	// Left-viewport: mainWindow - sceneEditorMenuModelChoice
	screenID = "sceneEditorMenuModelChoice";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addScrollingList("modelList", vec2(0.0f, 0.1f), vec2(1.8f, 1.75f), vec3(0.3f), LVC::buttonColor, LVC::buttonHoverColor, LVC::textColor, LVC::textHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.9f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuBillboard
	screenID = "sceneEditorMenuBillboard";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuLighting
	screenID = "sceneEditorMenuLighting";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("ambient", vec2(0.0f, 0.63f), vec2(GW("Ambient"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Ambient", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("directional", vec2(0.0f, 0.21f), vec2(GW("Directional"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Directional", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("point", vec2(0.0f, -0.21f), vec2(GW("Point"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Point", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuLightingAmbient
	screenID = "sceneEditorMenuLightingAmbient";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("color", vec2(0.0f, 0.475f), vec2(GW("Color"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Color", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("intensity", vec2(0.0f, 0.0f), vec2(GW("Intensity"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Intensity", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.475f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuLightingDirectional
	screenID = "sceneEditorMenuLightingDirectional";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("color", vec2(0.0f, 0.7f), vec2(GW("Color"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Color", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("position", vec2(0.0f, 0.35f), vec2(GW("Position"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Position", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("intensity", vec2(0.0f, 0.0f), vec2(GW("Intensity"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Intensity", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("billboardSize", vec2(0.0f, -0.35f), vec2(GW("Billboard size"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Billboard size", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.7f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);
	
	// Left-viewport: mainWindow - sceneEditorMenuLightingPoint
	screenID = "sceneEditorMenuLightingPoint";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("add", vec2(0.0f, 0.45f), vec2(GW("Add light"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Add light", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.45f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettings
	screenID = "sceneEditorMenuSettings";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("graphics", vec2(0.0f, 0.475f), vec2(GW("Graphics"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Graphics", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("setSpeed", vec2(0.0f, 0.0f), vec2(GW("Editor speed"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Editor speed", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.475f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);
	
	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphics
	screenID = "sceneEditorMenuSettingsGraphics";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("shadows", vec2(0.0f, 0.7875f), vec2(GW("Shadows"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Shadows", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("motionblur", vec2(0.0f, 0.525f), vec2(GW("Motion blur"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Motion blur", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("dof", vec2(0.0f, 0.2625f), vec2(GW("Depth Of Field"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Depth Of Field", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("fog", vec2(0.0f, 0.0f), vec2(GW("Fog"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Fog", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("lensflare", vec2(0.0f, -0.2625f), vec2(GW("Lens flare"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Lens flare", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("skyHdr", vec2(0.0f, -0.525f), vec2(GW("Sky HDR"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Sky HDR", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.7875f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsShadows
	screenID = "sceneEditorMenuSettingsGraphicsShadows";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("size", vec2(0.0f, 0.7f), vec2(GW("Size"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Size", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("position", vec2(0.0f, 0.35f), vec2(GW("Position"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Position", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("center", vec2(0.0f, 0.0f), vec2(GW("Center"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Center", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("follow", vec2(0.0f, -0.35f), vec2(GW("Follow cam: OFF"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Follow cam: OFF", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.7f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Right-viewport: mainWindow - modelPropertiesMenu
	screenID = "modelPropertiesMenu";
	_rightWindow->addScreen(screenID);
	_rightWindow->getScreen(screenID)->addTextfield("transformation", vec2(0.0f, 0.95f), vec2(1.75f, 0.1f), "Transformation", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("translation", vec2(0.0f, 0.8f), vec2(0.75f, 0.2f), "translation.png", vec3(0.0f));
	_rightWindow->getScreen(screenID)->addButton("rotation", vec2(0.0f, 0.55f), vec2(0.75f, 0.2f), "rotation.png", vec3(0.0f));
	_rightWindow->getScreen(screenID)->addButton("scaling", vec2(0.0f, 0.3f), vec2(0.75f, 0.2f), "scaling.png", vec3(0.0f));
	_rightWindow->getScreen(screenID)->addButton("freeze", vec2(0.0f, 0.13f), vec2(1.25f, 0.075f), vec3(0.0f, 0.0f, 0.75f), vec3(0.25f, 0.25f, 1.0f), "Freeze", LVC::textColor, LVC::textHoverColor);
	_rightWindow->getScreen(screenID)->addButton("delete", vec2(0.0f, -0.03f), vec2(1.25f, 0.075f), vec3(0.75f, 0.0f, 0.0f), vec3(1.0f, 0.25f, 0.25f), "Delete", LVC::textColor, LVC::textHoverColor);
	_rightWindow->getScreen(screenID)->addTextfield("x", vec2(0.0f, -0.15f), vec2(0.25f, 0.1f), "X", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addTextfield("y", vec2(0.0f, -0.4f), vec2(0.25f, 0.1f), "Y", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addTextfield("z", vec2(0.0f, -0.65f), vec2(0.25f, 0.1f), "Z", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("xPlus", vec2(0.75f, -0.25f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("yPlus", vec2(0.75f, -0.5f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("zPlus", vec2(0.75f, -0.75f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("xMinus", vec2(-0.75f, -0.25f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("yMinus", vec2(-0.75f, -0.5f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("zMinus", vec2(-0.75f, -0.75f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addWriteField("x", vec2(0.0f, -0.25f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen(screenID)->addWriteField("y", vec2(0.0f, -0.5f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen(screenID)->addWriteField("z", vec2(0.0f, -0.75f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);

	// Right-viewport: mainWindow - pointLightPropertiesMenu
	screenID = "pointLightPropertiesMenu";
	_rightWindow->addScreen(screenID);
	_rightWindow->getScreen(screenID)->addTextfield("intensity", vec2(0.0f, 0.95f), vec2(1.5f, 0.1f), "Intensity", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("intensityPlus", vec2(0.75f, 0.85f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("intensityMinus", vec2(-0.75f, 0.85f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addWriteField("intensity", vec2(0.0f, 0.85f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen(screenID)->addTextfield("distance", vec2(0.0f, 0.725f), vec2(1.5f, 0.1f), "Distance", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("distancePlus", vec2(0.75f, 0.625f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("distanceMinus", vec2(-0.75f, 0.625f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addWriteField("distance", vec2(0.0f, 0.625f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen(screenID)->addTextfield("x", vec2(0.0f, 0.5f), vec2(0.25f, 0.1f), "X", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("xPlus", vec2(0.75f, 0.4f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("xMinus", vec2(-0.75f, 0.4f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addWriteField("x", vec2(0.0f, 0.4f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen(screenID)->addTextfield("y", vec2(0.0f, 0.275f), vec2(0.25f, 0.1f), "Y", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("yPlus", vec2(0.75f, 0.175f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("yMinus", vec2(-0.75f, 0.175f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addWriteField("y", vec2(0.0f, 0.175f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen(screenID)->addTextfield("z", vec2(0.0f, 0.05f), vec2(0.25f, 0.1f), "Z", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("zPlus", vec2(0.75f, -0.05f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("zMinus", vec2(-0.75f, -0.05f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addWriteField("z", vec2(0.0f, -0.05f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen(screenID)->addTextfield("r", vec2(0.0f, -0.175f), vec2(0.25f, 0.1f), "R", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("rPlus", vec2(0.75f, -0.275f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("rMinus", vec2(-0.75f, -0.275f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addWriteField("r", vec2(0.0f, -0.275f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen(screenID)->addTextfield("g", vec2(0.0f, -0.4f), vec2(0.25f, 0.1f), "G", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("gPlus", vec2(0.75f, -0.5f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("gMinus", vec2(-0.75f, -0.5f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addWriteField("g", vec2(0.0f, -0.5f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen(screenID)->addTextfield("b", vec2(0.0f, -0.625f), vec2(0.25f, 0.1f), "B", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("bPlus", vec2(0.75f, -0.725f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addButton("bMinus", vec2(-0.75f, -0.725f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen(screenID)->addWriteField("b", vec2(0.0f, -0.725f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen(screenID)->addButton("delete", vec2(0.0f, -0.9f), vec2(1.5f, 0.1f), vec3(0.75f, 0.0f, 0.0f), vec3(1.0f, 0.25f, 0.25f), "Delete", LVC::textColor, LVC::textHoverColor);
}

void SceneEditor::load()
{
	// Enable default graphics
	_fe3d.gfx_enableAmbientLighting(vec3(1.0f), 1.0f);
	_fe3d.gfx_enableSpecularLighting();
	_fe3d.gfx_enablePointLighting();
	//_fe3d.gfx_enableFog(150.0f, vec3(0.75f));
	_fe3d.gfx_enableSkyReflections(0.5f);
	_fe3d.gfx_enableSceneReflections(0.25f);
	_fe3d.gfx_enableLightMapping();
	_fe3d.gfx_enableWaterEffects();
	_fe3d.gfx_enableSkyHDR(0.4f);
	_fe3d.gfx_enableDOF(75.0f);
	_fe3d.gfx_enableMotionBlur();
	_fe3d.gfx_enableLensFlare("User\\Assets\\Textures\\FlareMaps\\flare.png", 1.0f, 1.0f);
	
	// Disable default skybox
	_fe3d.skyEntity_select("");

	// Load world entities
	_worldEditor.loadSkyEntity();
	_worldEditor.loadTerrainEntity();
	_worldEditor.loadWaterEntity();

	// Load scene
	bool loadedFile = _loadScene();

	// Load lightsource billboard
	if (!_fe3d.billboardEntity_isExisting("@@lightSource"))
	{
		_fe3d.billBoardEntity_add("@@lightSource", "Engine\\Textures\\light_source.png", _fe3d.gfx_getDirectionalLightingPosition(),
			vec3(0.0f), vec2(0.0f), true, true, true, true);
	}
	
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

	// Default camera height
	if (!loadedFile)
	{
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
	}

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
	_fe3d.gameEntity_setDepthMapIncluded(_previewPointlightID, false);

	// Create name textfields
	_gui->getGlobalScreen()->addTextfield("selectedModelName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_gui->getGlobalScreen()->addTextfield("selectedBillboardName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_gui->getGlobalScreen()->addTextfield("selectedPointlightName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));

	// Miscellaneous
	_gui->getViewport("bottom")->getWindow("controls")->setActiveScreen("sceneEditor");
	_isLoaded = true;
}

bool SceneEditor::_loadScene()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	string filePath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\Scenes\\scene.fe3d";

	// Check if scene file existing
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Load scene file
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
				float uvRepeat, specularFactor, specularIntensity, lightness;
				bool isFaceculled, isShadowed, isTransparent, isSpecular, isReflective, isFrozen;

				// Load model data
				iss >>
					modelID >>
					position.x >>
					position.y >>
					position.z >>
					rotation.x >>
					rotation.y >>
					rotation.z >>
					size.x >>
					size.y >>
					size.z >>
					objPath >>
					diffuseMapPath >>
					lightMapPath >>
					reflectionMapPath >>
					isFrozen >>
					isFaceculled >>
					isShadowed >>
					isTransparent >>
					isReflective >>
					isSpecular >>
					specularFactor >>
					specularIntensity >>
					lightness >>
					color.r >>
					color.g >>
					color.b >>
					uvRepeat >>
					aabbSize.x >>
					aabbSize.y >>
					aabbSize.z;

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
				_placeModel(modelID, position, rotation, size, objPath, diffuseMapPath, lightMapPath, reflectionMapPath, isFrozen,
					isFaceculled, isShadowed, isTransparent, isReflective, isSpecular, specularFactor, specularIntensity, lightness,
					color, uvRepeat, aabbSize);
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
				float directionalLightingIntensity, billboardSize;

				// Extract
				iss >> directionalLightingPosition.x >> directionalLightingPosition.y >> directionalLightingPosition.z >>
					directionalLightingColor.r >> directionalLightingColor.g >> directionalLightingColor.b >>
					directionalLightingIntensity >> billboardSize;

				// Apply
				_fe3d.gfx_enableDirectionalLighting(directionalLightingPosition, directionalLightingColor, directionalLightingIntensity);
				_fe3d.billBoardEntity_add("@@lightSource", "Engine\\Textures\\light_source.png", directionalLightingPosition, vec3(0.0f), vec2(billboardSize), true, true, true, true);
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
				_fe3d.gameEntity_setDepthMapIncluded("@" + ID, false);
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

		return true;
	}
	else
	{
		return false;
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
				auto isFrozen = _fe3d.gameEntity_isStaticToCamera(entityID);
				auto isFaceCulled = _fe3d.gameEntity_isFaceCulled(entityID);
				auto isShadowed = _fe3d.gameEntity_isShadowed(entityID);
				auto isTransparent = _fe3d.gameEntity_isTransparent(entityID);
				auto isReflective = _fe3d.gameEntity_isSceneReflective(entityID);
				auto isSpecular = _fe3d.gameEntity_isSpecularLighted(entityID);
				auto specularFactor = _fe3d.gameEntity_getSpecularFactor(entityID);
				auto specularIntensity = _fe3d.gameEntity_getSpecularIntensity(entityID);
				auto lightness = _fe3d.gameEntity_getLightness(entityID);
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
					isFrozen << " " <<
					isFaceCulled << " " <<
					isShadowed << " " <<
					isTransparent << " " <<
					isReflective << " " <<
					isSpecular << " " <<
					specularFactor << " " <<
					specularIntensity << " " <<
					lightness << " " <<
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
		float billboardSize = _fe3d.billboardEntity_getSize("@@lightSource").x;

		file << 
			"DIRECTIONAL " <<
			directionalLightingPosition.x << " " <<
			directionalLightingPosition.y << " " <<
			directionalLightingPosition.z << " " <<
			directionalLightingColor.r << " " <<
			directionalLightingColor.g << " " <<
			directionalLightingColor.b << " " <<
			directionalLightingIntensity << " " <<
			billboardSize << std::endl;

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
	_fe3d.gfx_disableFog();
	_fe3d.gfx_disableDOF();
	_fe3d.gfx_disableSkyHDR();
	_fe3d.gfx_disableShadows();
	_fe3d.gfx_disableLensFlare();
	_fe3d.gfx_disableSkyReflections();
	_fe3d.gfx_disableLightMapping();
	_fe3d.gfx_disableSpecularLighting();
	_fe3d.gfx_disableSceneReflections();
	_fe3d.gfx_disableWaterEffects();

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
	_dontResetSelectedModel = false;
	_isPlacingPointlight = false;
	_isLoaded = false;
	_transformation = Transformation::TRANSLATION;
	_selectedLightSizeMultiplier = 1;
	_activeLightSizeMultiplier = 1;
	_activeLightBulbID = "";
	_customCameraSpeed = 1.0f;

	// Delete name textfields
	_gui->getGlobalScreen()->deleteTextfield("selectedModelName");
	_gui->getGlobalScreen()->deleteTextfield("selectedBillboardName");
	_gui->getGlobalScreen()->deleteTextfield("selectedPointlightName");

	// Enable default skybox
	_fe3d.skyEntity_select("@@defaultSky");

	// Camera
	_fe3d.camera_setPosition(vec3(0.0f));
	_fe3d.camera_setYaw(0.0f);
	_fe3d.camera_setPitch(0.0f);
	_fe3d.camera_disableFirstPersonView();

	// Other
	_leftWindow->getScreen("sceneEditorMenuModelPlace")->getScrollingList("modelList")->deleteButtons();
	_gui->getViewport("bottom")->getWindow("controls")->setActiveScreen("mainMenu");
	_fe3d.misc_disableAabbFrameRendering();
}