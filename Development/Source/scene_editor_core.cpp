#include "scene_editor.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVPC::calcTextWidth(text, 0.15f, 1.8f)

SceneEditor::SceneEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, EnvironmentEditor& environmentEditor, ModelEditor& modelEditor, BillboardEditor& billboardEditor) :
	_fe3d(fe3d),
	_gui(gui),
	_environmentEditor(environmentEditor),
	_modelEditor(modelEditor),
	_billboardEditor(billboardEditor)
{

}

void SceneEditor::initializeGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	string screenID;

	// Left-viewport: mainWindow - sceneEditorMenuMain
	screenID = "sceneEditorMenuMain";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("create", vec2(0.0f, 0.63f), vec2(GW("Create"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Create", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("edit", vec2(0.0f, 0.21f), vec2(GW("Edit"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("delete", vec2(0.0f, -0.21f), vec2(GW("Remove"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Remove", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuChoice
	screenID = "sceneEditorMenuChoice";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("environment", vec2(0.0f, 0.7875f), vec2(GW("Environment"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Environment", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("model", vec2(0.0f, 0.525f), vec2(GW("Models"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Models", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("billboard", vec2(0.0f, 0.2625f), vec2(GW("Billboards"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Billboards", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("lighting", vec2(0.0f, 0.0f), vec2(GW("Lighting"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Lighting", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("audio", vec2(0.0f, -0.2625f), vec2(GW("Audio"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Audio", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("settings", vec2(0.0f, -0.525f), vec2(GW("Settings"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Settings", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.7875f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - sceneEditorMenuEnvironment
	screenID = "sceneEditorMenuEnvironment";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("sky", vec2(0.0f, 0.63f), vec2(GW("Sky"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Sky", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("terrain", vec2(0.0f, 0.21f), vec2(GW("Terrain"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Terrain", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("water", vec2(0.0f, -0.21f), vec2(GW("Water"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Water", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuEnvironmentSky
	screenID = "sceneEditorMenuEnvironmentSky";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("choose", vec2(0.0f, 0.475f), vec2(GW("Choose sky"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Choose sky", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("delete", vec2(0.0f, 0.0f), vec2(GW("Remove sky"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Remove sky", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.475f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuEnvironmentTerrain
	screenID = "sceneEditorMenuEnvironmentTerrain";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("choose", vec2(0.0f, 0.475f), vec2(GW("Choose terrain"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Choose terrain", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("delete", vec2(0.0f, 0.0f), vec2(GW("Remove terrain"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Remove terrain", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.475f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuEnvironmentWater
	screenID = "sceneEditorMenuEnvironmentWater";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("choose", vec2(0.0f, 0.475f), vec2(GW("Choose water"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Choose water", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("delete", vec2(0.0f, 0.0f), vec2(GW("Remove water"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Remove water", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.475f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuModel
	screenID = "sceneEditorMenuModel";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("place", vec2(0.0f, 0.475f), vec2(GW("Place model"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Place model", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("choice", vec2(0.0f, 0.0f), vec2(GW("Choose model"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Choose model", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.475f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuModelPlace
	screenID = "sceneEditorMenuModelPlace";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("models", vec2(0.0f, 0.1f), vec2(1.8f, 1.75f), vec3(0.3f), LVPC::buttonColor, LVPC::buttonHoverColor, LVPC::textColor, LVPC::textHoverColor, vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.9f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - sceneEditorMenuModelChoice
	screenID = "sceneEditorMenuModelChoice";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("models", vec2(0.0f, 0.1f), vec2(1.8f, 1.75f), vec3(0.3f), LVPC::buttonColor, LVPC::buttonHoverColor, LVPC::textColor, LVPC::textHoverColor, vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.9f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuBillboard
	screenID = "sceneEditorMenuBillboard";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("place", vec2(0.0f, 0.475f), vec2(GW("Place billboard"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Place billboard", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("choice", vec2(0.0f, 0.0f), vec2(GW("Choose billboard"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Choose billboard", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.475f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuBillboardPlace
	screenID = "sceneEditorMenuBillboardPlace";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("billboards", vec2(0.0f, 0.1f), vec2(1.8f, 1.75f), vec3(0.3f), LVPC::buttonColor, LVPC::buttonHoverColor, LVPC::textColor, LVPC::textHoverColor, vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.9f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuBillboardChoice
	screenID = "sceneEditorMenuBillboardChoice";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("billboards", vec2(0.0f, 0.1f), vec2(1.8f, 1.75f), vec3(0.3f), LVPC::buttonColor, LVPC::buttonHoverColor, LVPC::textColor, LVPC::textHoverColor, vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.9f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuLighting
	screenID = "sceneEditorMenuLighting";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("ambient", vec2(0.0f, 0.63f), vec2(GW("Ambient"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Ambient", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("directional", vec2(0.0f, 0.21f), vec2(GW("Directional"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Directional", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("point", vec2(0.0f, -0.21f), vec2(GW("Point"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Point", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuLightingAmbient
	screenID = "sceneEditorMenuLightingAmbient";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("color", vec2(0.0f, 0.475f), vec2(GW("Color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Color", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("intensity", vec2(0.0f, 0.0f), vec2(GW("Intensity"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Intensity", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.475f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuLightingDirectional
	screenID = "sceneEditorMenuLightingDirectional";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("color", vec2(0.0f, 0.7f), vec2(GW("Color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Color", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("position", vec2(0.0f, 0.35f), vec2(GW("Position"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Position", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("intensity", vec2(0.0f, 0.0f), vec2(GW("Intensity"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Intensity", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("billboardSize", vec2(0.0f, -0.35f), vec2(GW("Billboard size"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Billboard size", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.7f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - sceneEditorMenuLightingPoint
	screenID = "sceneEditorMenuLightingPoint";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("add", vec2(0.0f, 0.45f), vec2(GW("Add light"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Add light", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.45f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettings
	screenID = "sceneEditorMenuSettings";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("graphics", vec2(0.0f, 0.63f), vec2(GW("Graphics"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Graphics", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("setSpeed", vec2(0.0f, 0.21f), vec2(GW("Editor speed"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Editor speed", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("lodDistance", vec2(0.0f, -0.21f), vec2(GW("LOD distance"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "LOD distance", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphics
	screenID = "sceneEditorMenuSettingsGraphics";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("shadows", vec2(0.0f, 0.7875f), vec2(GW("Shadows"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Shadows", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("motionblur", vec2(0.0f, 0.525f), vec2(GW("Motion blur"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Motion blur", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("dof", vec2(0.0f, 0.2625f), vec2(GW("Depth Of Field"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Depth Of Field", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("fog", vec2(0.0f, 0.0f), vec2(GW("Fog"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Fog", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("lensflare", vec2(0.0f, -0.2625f), vec2(GW("Lens flare"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Lens flare", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("skyHdr", vec2(0.0f, -0.525f), vec2(GW("Sky HDR"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Sky HDR", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.7875f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsShadows
	screenID = "sceneEditorMenuSettingsGraphicsShadows";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", vec2(0.0f, 0.7875f), vec2(GW("Enabled: NO"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Enabled: NO", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("size", vec2(0.0f, 0.525f), vec2(GW("Size"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Size", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("position", vec2(0.0f, 0.2625f), vec2(GW("Position"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Position", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("center", vec2(0.0f, 0.0f), vec2(GW("Center"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Center", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("follow", vec2(0.0f, -0.2625f), vec2(GW("Follow cam: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Follow cam: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("interval", vec2(0.0f, -0.525f), vec2(GW("Interval"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Interval", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.7875f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsMotionblur
	screenID = "sceneEditorMenuSettingsGraphicsMotionblur";
	leftWindow->addScreen(screenID); 
	leftWindow->getScreen(screenID)->addButton("enabled", vec2(0.0f, 0.475f), vec2(GW("Enabled: NO"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Enabled: NO", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("strength", vec2(0.0f, 0.0f), vec2(GW("Strength"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Strength", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.475f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsDof
	screenID = "sceneEditorMenuSettingsGraphicsDof";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", vec2(0.0f, 0.7f), vec2(GW("Enabled: NO"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Enabled: NO", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("dynamic", vec2(0.0f, 0.35f), vec2(GW("Dynamic: NO"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Dynamic: NO", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("blurDistance", vec2(0.0f, 0.0f), vec2(GW("Blur distance"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Blur distance", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("maxDistance", vec2(0.0f, -0.35f), vec2(GW("DOF distance"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "DOF distance", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.7f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsFog
	screenID = "sceneEditorMenuSettingsGraphicsFog";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", vec2(0.0f, 0.75f), vec2(GW("Enabled: NO"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Enabled: NO", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("minDistance", vec2(0.0f, 0.45f), vec2(GW("Min distance"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Min distance", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("maxDistance", vec2(0.0f, 0.15f), vec2(GW("Max distance"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Max distance", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("defaultFactor", vec2(0.0f, -0.15f), vec2(GW("Default factor"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Default factor", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("color", vec2(0.0f, -0.45f), vec2(GW("Color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Color", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.75f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsLensFlare
	screenID = "sceneEditorMenuSettingsGraphicsLensFlare";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", vec2(0.0f, 0.7f), vec2(GW("Enabled: NO"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Enabled: NO", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("loadFlareMap", vec2(0.0f, 0.35f), vec2(GW("FlareMap"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "FlareMap", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("intensity", vec2(0.0f, 0.0f), vec2(GW("Intensity"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Intensity", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("multiplier", vec2(0.0f, -0.35f), vec2(GW("Multiplier"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Multiplier", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.7f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsSkyHDR
	screenID = "sceneEditorMenuSettingsGraphicsSkyHDR";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", vec2(0.0f, 0.475f), vec2(GW("Enabled: NO"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Enabled: NO", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("intensity", vec2(0.0f, 0.0f), vec2(GW("Intensity"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Intensity", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.475f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Right-viewport: mainWindow - modelPropertiesMenu
	screenID = "modelPropertiesMenu";
	rightWindow->addScreen(screenID);
	rightWindow->getScreen(screenID)->addTextfield("transformation", vec2(0.0f, 0.95f), vec2(1.75f, 0.1f), "Transformation", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("translation", vec2(0.0f, 0.8f), vec2(0.75f, 0.2f), "translation.png", vec3(0.0f));
	rightWindow->getScreen(screenID)->addButton("rotation", vec2(0.0f, 0.55f), vec2(0.75f, 0.2f), "rotation.png", vec3(0.0f));
	rightWindow->getScreen(screenID)->addButton("scaling", vec2(0.0f, 0.3f), vec2(0.75f, 0.2f), "scaling.png", vec3(0.0f));
	rightWindow->getScreen(screenID)->addButton("freeze", vec2(0.0f, 0.13f), vec2(1.25f, 0.075f), vec3(0.0f, 0.0f, 0.75f), vec3(0.25f, 0.25f, 1.0f), "Freeze", LVPC::textColor, LVPC::textHoverColor);
	rightWindow->getScreen(screenID)->addButton("delete", vec2(0.0f, -0.03f), vec2(1.25f, 0.075f), vec3(0.75f, 0.0f, 0.0f), vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::textColor, LVPC::textHoverColor);
	rightWindow->getScreen(screenID)->addTextfield("x", vec2(0.0f, -0.15f), vec2(0.25f, 0.1f), "X", vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("y", vec2(0.0f, -0.4f), vec2(0.25f, 0.1f), "Y", vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("z", vec2(0.0f, -0.65f), vec2(0.25f, 0.1f), "Z", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xPlus", vec2(0.75f, -0.25f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yPlus", vec2(0.75f, -0.5f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zPlus", vec2(0.75f, -0.75f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xMinus", vec2(-0.75f, -0.25f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yMinus", vec2(-0.75f, -0.5f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zMinus", vec2(-0.75f, -0.75f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("x", vec2(0.0f, -0.25f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWriteField("y", vec2(0.0f, -0.5f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWriteField("z", vec2(0.0f, -0.75f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);

	// Right-viewport: mainWindow - billboardPropertiesMenu
	screenID = "billboardPropertiesMenu";
	rightWindow->addScreen(screenID);
	rightWindow->getScreen(screenID)->addTextfield("transformation", vec2(0.0f, 0.95f), vec2(1.75f, 0.1f), "Transformation", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("translation", vec2(0.0f, 0.8f), vec2(0.75f, 0.2f), "translation.png", vec3(0.0f));
	rightWindow->getScreen(screenID)->addButton("rotation", vec2(0.0f, 0.55f), vec2(0.75f, 0.2f), "rotation.png", vec3(0.0f));
	rightWindow->getScreen(screenID)->addButton("scaling", vec2(0.0f, 0.3f), vec2(0.75f, 0.2f), "scaling.png", vec3(0.0f));
	rightWindow->getScreen(screenID)->addButton("delete", vec2(0.0f, 0.05f), vec2(1.25f, 0.075f), vec3(0.75f, 0.0f, 0.0f), vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::textColor, LVPC::textHoverColor);
	rightWindow->getScreen(screenID)->addTextfield("x", vec2(0.0f, -0.15f), vec2(0.25f, 0.1f), "X", vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("y", vec2(0.0f, -0.4f), vec2(0.25f, 0.1f), "Y", vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("z", vec2(0.0f, -0.65f), vec2(0.25f, 0.1f), "Z", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xPlus", vec2(0.75f, -0.25f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yPlus", vec2(0.75f, -0.5f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zPlus", vec2(0.75f, -0.75f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xMinus", vec2(-0.75f, -0.25f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yMinus", vec2(-0.75f, -0.5f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zMinus", vec2(-0.75f, -0.75f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("x", vec2(0.0f, -0.25f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWriteField("y", vec2(0.0f, -0.5f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWriteField("z", vec2(0.0f, -0.75f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);

	// Right-viewport: mainWindow - pointLightPropertiesMenu
	screenID = "pointLightPropertiesMenu";
	rightWindow->addScreen(screenID);
	rightWindow->getScreen(screenID)->addTextfield("intensity", vec2(0.0f, 0.95f), vec2(1.5f, 0.1f), "Intensity", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("intensityPlus", vec2(0.75f, 0.85f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("intensityMinus", vec2(-0.75f, 0.85f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("intensity", vec2(0.0f, 0.85f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("distance", vec2(0.0f, 0.725f), vec2(1.5f, 0.1f), "Distance", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("distancePlus", vec2(0.75f, 0.625f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("distanceMinus", vec2(-0.75f, 0.625f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("distance", vec2(0.0f, 0.625f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("x", vec2(0.0f, 0.5f), vec2(0.25f, 0.1f), "X", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xPlus", vec2(0.75f, 0.4f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xMinus", vec2(-0.75f, 0.4f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("x", vec2(0.0f, 0.4f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("y", vec2(0.0f, 0.275f), vec2(0.25f, 0.1f), "Y", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yPlus", vec2(0.75f, 0.175f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yMinus", vec2(-0.75f, 0.175f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("y", vec2(0.0f, 0.175f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("z", vec2(0.0f, 0.05f), vec2(0.25f, 0.1f), "Z", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zPlus", vec2(0.75f, -0.05f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zMinus", vec2(-0.75f, -0.05f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("z", vec2(0.0f, -0.05f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("r", vec2(0.0f, -0.175f), vec2(0.25f, 0.1f), "R", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("rPlus", vec2(0.75f, -0.275f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("rMinus", vec2(-0.75f, -0.275f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("r", vec2(0.0f, -0.275f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("g", vec2(0.0f, -0.4f), vec2(0.25f, 0.1f), "G", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("gPlus", vec2(0.75f, -0.5f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("gMinus", vec2(-0.75f, -0.5f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("g", vec2(0.0f, -0.5f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("b", vec2(0.0f, -0.625f), vec2(0.25f, 0.1f), "B", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("bPlus", vec2(0.75f, -0.725f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("bMinus", vec2(-0.75f, -0.725f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("b", vec2(0.0f, -0.725f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addButton("delete", vec2(0.0f, -0.9f), vec2(1.5f, 0.1f), vec3(0.75f, 0.0f, 0.0f), vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::textColor, LVPC::textHoverColor);
}

void SceneEditor::load()
{
	// Load environment preview entities
	_environmentEditor.loadSkyEntitiesFromFile();
	_environmentEditor.loadTerrainEntitiesFromFile();
	_environmentEditor.loadWaterEntitiesFromFile();

	// Load lightsource billboard
	_fe3d.billBoardEntity_add("@@lightSource", "engine\\textures\\light_source.png", _fe3d.gfx_getDirectionalLightingPosition(),
		vec3(0.0f), vec2(0.0f), true, true, true, true);
	_fe3d.billboardEntity_setDepthMapIncluded("@@lightSource", false);

	// Preview model loading
	_modelEditor.loadGameEntitiesFromFile();
	for (auto& modelName : _modelEditor.getModelNames())
	{
		// Check if there is a GAME entity present
		if (_fe3d.gameEntity_isExisting(modelName))
		{
			_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelPlace")->getScrollingList("models")->addButton(modelName, modelName.substr(1));
		}
	}

	// Preview billboard loading
	_billboardEditor.loadBillboardEntitiesFromFile();
	for (auto& billboardName : _billboardEditor.getBillboardNames())
	{
		// Check if there is a BILLBOARD entity present
		if (_fe3d.billboardEntity_isExisting(billboardName))
		{
			_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardPlace")->getScrollingList("billboards")->addButton(billboardName, billboardName.substr(1));
		}
	}

	// Preview pointlight loading
	_fe3d.lightEntity_add(_previewPointlightID);
	_fe3d.lightEntity_hide(_previewPointlightID);
	_fe3d.gameEntity_add(_previewPointlightID, "engine\\models\\lamp.obj", vec3(0.0f), vec3(0.0f), _defaultLightbulbSize, false);
	_fe3d.gameEntity_setShadowed(_previewPointlightID, false);
	_fe3d.gameEntity_setDepthMapIncluded(_previewPointlightID, false);

	// Create name textfields
	_gui.getGlobalScreen()->addTextfield("selectedModelName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedBillboardName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedPointlightName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));

	// Miscellaneous
	_fe3d.input_clearKeyToggles();
	_fe3d.collision_enableCameraResponse();
	_isLoaded = true;
}

void SceneEditor::unload()
{	
	// Clear scene
	clearScene();

	// Unload environment preview entities
	_environmentEditor.unloadSkyEntities();
	_environmentEditor.unloadTerrainEntities();
	_environmentEditor.unloadWaterEntities();

	// Delete other preview entities
	_fe3d.audioEntity_deleteAll();
	_fe3d.gameEntity_deleteAll();
	_fe3d.billboardEntity_deleteAll();
	_fe3d.lightEntity_deleteAll();

	// Reset variables
	_currentSkyID = "";
	_currentTerrainID = "";
	_currentWaterID = "";
	_currentPreviewModelName = "";
	_selectedModelID = "";
	_activeModelID = "";
	_selectedModelLightnessMultiplier = 1;
	_activeModelLightnessMultiplier = 1;
	_dontResetSelectedModel = false;
	_currentPreviewBillboardName = "";
	_selectedBillboardID = "";
	_activeBillboardID = "";
	_selectedBillboardLightnessMultiplier = 1;
	_activeBillboardLightnessMultiplier = 1;
	_dontResetSelectedBillboard = false;
	_isPlacingPointlight = false;
	_selectedLightSizeMultiplier = 1;
	_activeLightSizeMultiplier = 1;
	_selectedLightBulbID = "";
	_activeLightBulbID = "";
	_currentSceneName = "";
	_isChoosingScene = false;
	_isDeletingScene = false;
	_transformation = TransformationType::TRANSLATION;
	_customCameraSpeed = 1.0f;

	// Delete name textfields
	_gui.getGlobalScreen()->deleteTextfield("selectedModelName");
	_gui.getGlobalScreen()->deleteTextfield("selectedBillboardName");
	_gui.getGlobalScreen()->deleteTextfield("selectedPointlightName");

	// Miscellaneous
	_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelPlace")->getScrollingList("models")->deleteButtons();
	_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelChoice")->getScrollingList("models")->deleteButtons();
	_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardPlace")->getScrollingList("billboards")->deleteButtons();
	_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardChoice")->getScrollingList("billboards")->deleteButtons();
	_fe3d.misc_disableAabbFrameRendering();
	_fe3d.misc_disableWireframeRendering();
	_fe3d.misc_disableDebugRendering();
	_isLoaded = false;
}