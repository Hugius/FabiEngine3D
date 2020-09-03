#include "scene_editor.hpp"
#include "left_viewport_controller.hpp"

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
	_leftWindow->getScreen(screenID)->addButton("enabled", vec2(0.0f, 0.75f), vec2(GW("Enabled: NO"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Enabled: NO", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("size", vec2(0.0f, 0.45f), vec2(GW("Size"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Size", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("position", vec2(0.0f, 0.15f), vec2(GW("Position"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Position", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("center", vec2(0.0f, -0.15f), vec2(GW("Center"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Center", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("follow", vec2(0.0f, -0.45f), vec2(GW("Follow cam: OFF"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Follow cam: OFF", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.75f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsMotionblur
	screenID = "sceneEditorMenuSettingsGraphicsMotionblur";
	_leftWindow->addScreen(screenID); 
	_leftWindow->getScreen(screenID)->addButton("enabled", vec2(0.0f, 0.475f), vec2(GW("Enabled: NO"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Enabled: NO", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("strength", vec2(0.0f, 0.0f), vec2(GW("Strength"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Strength", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.475f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsDof
	screenID = "sceneEditorMenuSettingsGraphicsDof";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("enabled", vec2(0.0f, 0.63f), vec2(GW("Enabled: NO"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Enabled: NO", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("blurDistance", vec2(0.0f, 0.21f), vec2(GW("Blur distance"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Blur distance", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("maxDistance", vec2(0.0f, -0.21f), vec2(GW("DOF distance"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "DOF distance", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsFog
	screenID = "sceneEditorMenuSettingsGraphicsFog";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("enabled", vec2(0.0f, 0.75f), vec2(GW("Enabled: NO"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Enabled: NO", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("minDistance", vec2(0.0f, 0.45f), vec2(GW("Min distance"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Min distance", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("maxDistance", vec2(0.0f, 0.15f), vec2(GW("Max distance"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Max distance", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("defaultFactor", vec2(0.0f, -0.15f), vec2(GW("Default factor"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Default factor", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("color", vec2(0.0f, -0.45f), vec2(GW("Color"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Color", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.75f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsLensFlare
	screenID = "sceneEditorMenuSettingsGraphicsLensFlare";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("enabled", vec2(0.0f, 0.7f), vec2(GW("Enabled: NO"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Enabled: NO", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("loadFlareMap", vec2(0.0f, 0.35f), vec2(GW("FlareMap"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "FlareMap", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("intensity", vec2(0.0f, 0.0f), vec2(GW("Intensity"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Intensity", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("multiplier", vec2(0.0f, -0.35f), vec2(GW("Multiplier"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Multiplier", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.7f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsSkyHDR
	screenID = "sceneEditorMenuSettingsGraphicsSkyHDR";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("enabled", vec2(0.0f, 0.475f), vec2(GW("Enabled: NO"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Enabled: NO", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("intensity", vec2(0.0f, 0.0f), vec2(GW("Intensity"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Intensity", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.475f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);

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
	// Default camera
	float mouseSpeed = _fe3d.camera_getMouseSensitivity();
	_fe3d.camera_load(_fe3d.camera_getFOV(), 0.1f, 10000.0f, vec3(0.0f));
	_fe3d.camera_setMouseSensitivity(mouseSpeed);

	// Default graphics
	_fe3d.gfx_enableAmbientLighting(vec3(1.0f), 1.0f);
	_fe3d.gfx_enableSpecularLighting();
	_fe3d.gfx_enablePointLighting();
	_fe3d.gfx_enableSkyReflections(0.5f);
	_fe3d.gfx_enableSceneReflections(0.5f);
	_fe3d.gfx_enableLightMapping();
	_fe3d.gfx_enableWaterEffects();
	
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
			_leftWindow->getScreen("sceneEditorMenuModelPlace")->getScrollingList("modelList")->addButton(modelName, modelName.substr(1));
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
	_fe3d.gfx_disableMotionBlur();

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

	// Other
	_leftWindow->getScreen("sceneEditorMenuModelPlace")->getScrollingList("modelList")->deleteButtons();
	_gui->getViewport("bottom")->getWindow("controls")->setActiveScreen("mainMenu");
	_fe3d.misc_disableAabbFrameRendering();
}