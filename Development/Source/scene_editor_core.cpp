#include "scene_editor.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVPC::calcTextWidth(text, 0.15f, 1.8f)

SceneEditor::SceneEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, EnvironmentEditor& environmentEditor, 
	ModelEditor& modelEditor, BillboardEditor& billboardEditor, AudioEditor& audioEditor) :
	_fe3d(fe3d),
	_gui(gui),
	_environmentEditor(environmentEditor),
	_modelEditor(modelEditor),
	_billboardEditor(billboardEditor),
	_audioEditor(audioEditor)
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
	leftWindow->getScreen(screenID)->addButton("create", Vec2(0.0f, 0.63f), Vec2(GW("Create"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Create", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("edit", Vec2(0.0f, 0.21f), Vec2(GW("Edit"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, -0.21f), Vec2(GW("Remove"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Remove", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuChoice
	screenID = "sceneEditorMenuChoice";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("environment", Vec2(0.0f, 0.7875f), Vec2(GW("Environment"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Environment", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("model", Vec2(0.0f, 0.525f), Vec2(GW("Models"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Models", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("billboard", Vec2(0.0f, 0.2625f), Vec2(GW("Billboards"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Billboards", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("lighting", Vec2(0.0f, 0.0f), Vec2(GW("Lighting"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Lighting", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("audio", Vec2(0.0f, -0.2625f), Vec2(GW("Audio"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Audio", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("settings", Vec2(0.0f, -0.525f), Vec2(GW("Settings"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Settings", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.7875f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - sceneEditorMenuEnvironment
	screenID = "sceneEditorMenuEnvironment";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("sky", Vec2(0.0f, 0.63f), Vec2(GW("Sky"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Sky", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("terrain", Vec2(0.0f, 0.21f), Vec2(GW("Terrain"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Terrain", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("water", Vec2(0.0f, -0.21f), Vec2(GW("Water"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Water", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuEnvironmentSky
	screenID = "sceneEditorMenuEnvironmentSky";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("choose", Vec2(0.0f, 0.475f), Vec2(GW("Choose sky"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Choose sky", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, 0.0f), Vec2(GW("Remove sky"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Remove sky", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuEnvironmentTerrain
	screenID = "sceneEditorMenuEnvironmentTerrain";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("choose", Vec2(0.0f, 0.475f), Vec2(GW("Choose terrain"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Choose terrain", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, 0.0f), Vec2(GW("Remove terrain"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Remove terrain", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuEnvironmentWater
	screenID = "sceneEditorMenuEnvironmentWater";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("choose", Vec2(0.0f, 0.475f), Vec2(GW("Choose water"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Choose water", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, 0.0f), Vec2(GW("Remove water"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Remove water", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuModel
	screenID = "sceneEditorMenuModel";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("place", Vec2(0.0f, 0.475f), Vec2(GW("Place model"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Place model", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("choice", Vec2(0.0f, 0.0f), Vec2(GW("Choose model"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Choose model", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuModelPlace
	screenID = "sceneEditorMenuModelPlace";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("models", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), Vec3(0.3f), LVPC::buttonColor, LVPC::buttonHoverColor, LVPC::textColor, LVPC::textHoverColor, Vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.9f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - sceneEditorMenuModelChoice
	screenID = "sceneEditorMenuModelChoice";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("models", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), Vec3(0.3f), LVPC::buttonColor, LVPC::buttonHoverColor, LVPC::textColor, LVPC::textHoverColor, Vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.9f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuBillboard
	screenID = "sceneEditorMenuBillboard";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("place", Vec2(0.0f, 0.475f), Vec2(GW("Place billboard"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Place billboard", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("choice", Vec2(0.0f, 0.0f), Vec2(GW("Choose billboard"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Choose billboard", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuBillboardPlace
	screenID = "sceneEditorMenuBillboardPlace";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("billboards", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), Vec3(0.3f), LVPC::buttonColor, LVPC::buttonHoverColor, LVPC::textColor, LVPC::textHoverColor, Vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.9f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuBillboardChoice
	screenID = "sceneEditorMenuBillboardChoice";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("billboards", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), Vec3(0.3f), LVPC::buttonColor, LVPC::buttonHoverColor, LVPC::textColor, LVPC::textHoverColor, Vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.9f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuLighting
	screenID = "sceneEditorMenuLighting";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("ambient", Vec2(0.0f, 0.63f), Vec2(GW("Ambient"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Ambient", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("directional", Vec2(0.0f, 0.21f), Vec2(GW("Directional"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Directional", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("point", Vec2(0.0f, -0.21f), Vec2(GW("Point"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Point", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuLightingAmbient
	screenID = "sceneEditorMenuLightingAmbient";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("color", Vec2(0.0f, 0.475f), Vec2(GW("Color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Color", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("intensity", Vec2(0.0f, 0.0f), Vec2(GW("Intensity"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Intensity", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuLightingDirectional
	screenID = "sceneEditorMenuLightingDirectional";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("color", Vec2(0.0f, 0.7f), Vec2(GW("Color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Color", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("position", Vec2(0.0f, 0.35f), Vec2(GW("Position"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Position", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("intensity", Vec2(0.0f, 0.0f), Vec2(GW("Intensity"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Intensity", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("billboardSize", Vec2(0.0f, -0.35f), Vec2(GW("Billboard size"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Billboard size", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.7f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - sceneEditorMenuLightingPoint
	screenID = "sceneEditorMenuLightingPoint";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("add", Vec2(0.0f, 0.45f), Vec2(GW("Place light"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Place light", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.45f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuAudio
	screenID = "sceneEditorMenuAudio";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("place", Vec2(0.0f, 0.475f), Vec2(GW("Place audio"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Place audio", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("choice", Vec2(0.0f, 0.0f), Vec2(GW("Choose audio"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Choose audio", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuAudioPlace
	screenID = "sceneEditorMenuAudioPlace";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("audiocasters", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), Vec3(0.3f), LVPC::buttonColor, LVPC::buttonHoverColor, LVPC::textColor, LVPC::textHoverColor, Vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.9f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuAudioChoice
	screenID = "sceneEditorMenuAudioChoice";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("audiocasters", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), Vec3(0.3f), LVPC::buttonColor, LVPC::buttonHoverColor, LVPC::textColor, LVPC::textHoverColor, Vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.9f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettings
	screenID = "sceneEditorMenuSettings";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("graphics", Vec2(0.0f, 0.63f), Vec2(GW("Graphics"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Graphics", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("setSpeed", Vec2(0.0f, 0.21f), Vec2(GW("Editor speed"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Editor speed", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("lodDistance", Vec2(0.0f, -0.21f), Vec2(GW("LOD distance"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "LOD distance", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphics
	screenID = "sceneEditorMenuSettingsGraphics";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("shadows", Vec2(0.0f, 0.7875f), Vec2(GW("Shadows"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Shadows", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("motionblur", Vec2(0.0f, 0.525f), Vec2(GW("Motion blur"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Motion blur", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("dof", Vec2(0.0f, 0.2625f), Vec2(GW("Depth Of Field"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Depth Of Field", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("fog", Vec2(0.0f, 0.0f), Vec2(GW("Fog"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Fog", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("lensflare", Vec2(0.0f, -0.2625f), Vec2(GW("Lens flare"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Lens flare", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("skyHdr", Vec2(0.0f, -0.525f), Vec2(GW("Sky HDR"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Sky HDR", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.7875f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsShadows
	screenID = "sceneEditorMenuSettingsGraphicsShadows";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.7875f), Vec2(GW("Enabled: NO"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Enabled: NO", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("size", Vec2(0.0f, 0.525f), Vec2(GW("Size"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Size", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("position", Vec2(0.0f, 0.2625f), Vec2(GW("Position"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Position", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("center", Vec2(0.0f, 0.0f), Vec2(GW("Center"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Center", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("follow", Vec2(0.0f, -0.2625f), Vec2(GW("Follow cam: OFF"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Follow cam: OFF", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("interval", Vec2(0.0f, -0.525f), Vec2(GW("Interval"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Interval", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.7875f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsMotionblur
	screenID = "sceneEditorMenuSettingsGraphicsMotionblur";
	leftWindow->addScreen(screenID); 
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.475f), Vec2(GW("Enabled: NO"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Enabled: NO", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("strength", Vec2(0.0f, 0.0f), Vec2(GW("Strength"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Strength", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsDof
	screenID = "sceneEditorMenuSettingsGraphicsDof";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.7f), Vec2(GW("Enabled: NO"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Enabled: NO", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("dynamic", Vec2(0.0f, 0.35f), Vec2(GW("Dynamic: NO"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Dynamic: NO", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("blurDistance", Vec2(0.0f, 0.0f), Vec2(GW("Blur distance"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Blur distance", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("maxDistance", Vec2(0.0f, -0.35f), Vec2(GW("DOF distance"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "DOF distance", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.7f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsFog
	screenID = "sceneEditorMenuSettingsGraphicsFog";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.75f), Vec2(GW("Enabled: NO"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Enabled: NO", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("minDistance", Vec2(0.0f, 0.45f), Vec2(GW("Min distance"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Min distance", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("maxDistance", Vec2(0.0f, 0.15f), Vec2(GW("Max distance"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Max distance", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("defaultFactor", Vec2(0.0f, -0.15f), Vec2(GW("Default factor"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Default factor", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("color", Vec2(0.0f, -0.45f), Vec2(GW("Color"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Color", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.75f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsLensFlare
	screenID = "sceneEditorMenuSettingsGraphicsLensFlare";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.7f), Vec2(GW("Enabled: NO"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Enabled: NO", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("loadFlareMap", Vec2(0.0f, 0.35f), Vec2(GW("FlareMap"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "FlareMap", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("intensity", Vec2(0.0f, 0.0f), Vec2(GW("Intensity"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Intensity", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("multiplier", Vec2(0.0f, -0.35f), Vec2(GW("Multiplier"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Multiplier", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.7f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsSkyHDR
	screenID = "sceneEditorMenuSettingsGraphicsSkyHDR";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.475f), Vec2(GW("Enabled: NO"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Enabled: NO", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("intensity", Vec2(0.0f, 0.0f), Vec2(GW("Intensity"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Intensity", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Right-viewport: mainWindow - modelPropertiesMenu
	screenID = "modelPropertiesMenu";
	rightWindow->addScreen(screenID);
	rightWindow->getScreen(screenID)->addTextfield("transformation", Vec2(0.0f, 0.95f), Vec2(1.75f, 0.1f), "Transformation", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("translation", Vec2(0.0f, 0.8f), Vec2(0.75f, 0.2f), "translation.png", Vec3(0.0f));
	rightWindow->getScreen(screenID)->addButton("rotation", Vec2(0.0f, 0.55f), Vec2(0.75f, 0.2f), "rotation.png", Vec3(0.0f));
	rightWindow->getScreen(screenID)->addButton("scaling", Vec2(0.0f, 0.3f), Vec2(0.75f, 0.2f), "scaling.png", Vec3(0.0f));
	rightWindow->getScreen(screenID)->addButton("freeze", Vec2(0.0f, 0.13f), Vec2(1.25f, 0.075f), Vec3(0.0f, 0.0f, 0.75f), Vec3(0.25f, 0.25f, 1.0f), "Freeze", LVPC::textColor, LVPC::textHoverColor);
	rightWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, -0.03f), Vec2(1.25f, 0.075f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::textColor, LVPC::textHoverColor);
	rightWindow->getScreen(screenID)->addTextfield("x", Vec2(0.0f, -0.15f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("y", Vec2(0.0f, -0.4f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("z", Vec2(0.0f, -0.65f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xPlus", Vec2(0.75f, -0.25f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yPlus", Vec2(0.75f, -0.5f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zPlus", Vec2(0.75f, -0.75f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xMinus", Vec2(-0.75f, -0.25f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yMinus", Vec2(-0.75f, -0.5f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zMinus", Vec2(-0.75f, -0.75f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("x", Vec2(0.0f, -0.25f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWriteField("y", Vec2(0.0f, -0.5f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWriteField("z", Vec2(0.0f, -0.75f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);

	// Right-viewport: mainWindow - billboardPropertiesMenu
	screenID = "billboardPropertiesMenu";
	rightWindow->addScreen(screenID);
	rightWindow->getScreen(screenID)->addTextfield("transformation", Vec2(0.0f, 0.95f), Vec2(1.75f, 0.1f), "Transformation", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("translation", Vec2(0.0f, 0.8f), Vec2(0.75f, 0.2f), "translation.png", Vec3(0.0f));
	rightWindow->getScreen(screenID)->addButton("rotation", Vec2(0.0f, 0.55f), Vec2(0.75f, 0.2f), "rotation.png", Vec3(0.0f));
	rightWindow->getScreen(screenID)->addButton("scaling", Vec2(0.0f, 0.3f), Vec2(0.75f, 0.2f), "scaling.png", Vec3(0.0f));
	rightWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, 0.05f), Vec2(1.25f, 0.075f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::textColor, LVPC::textHoverColor);
	rightWindow->getScreen(screenID)->addTextfield("x", Vec2(0.0f, -0.15f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("y", Vec2(0.0f, -0.4f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("z", Vec2(0.0f, -0.65f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xPlus", Vec2(0.75f, -0.25f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yPlus", Vec2(0.75f, -0.5f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zPlus", Vec2(0.75f, -0.75f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xMinus", Vec2(-0.75f, -0.25f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yMinus", Vec2(-0.75f, -0.5f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zMinus", Vec2(-0.75f, -0.75f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("x", Vec2(0.0f, -0.25f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWriteField("y", Vec2(0.0f, -0.5f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWriteField("z", Vec2(0.0f, -0.75f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);

	// Right-viewport: mainWindow - pointlightPropertiesMenu
	screenID = "pointlightPropertiesMenu";
	rightWindow->addScreen(screenID);
	rightWindow->getScreen(screenID)->addTextfield("intensity", Vec2(0.0f, 0.95f), Vec2(1.5f, 0.1f), "Intensity", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("intensityPlus", Vec2(0.75f, 0.85f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("intensityMinus", Vec2(-0.75f, 0.85f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("intensity", Vec2(0.0f, 0.85f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("distance", Vec2(0.0f, 0.725f), Vec2(1.5f, 0.1f), "Distance", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("distancePlus", Vec2(0.75f, 0.625f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("distanceMinus", Vec2(-0.75f, 0.625f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("distance", Vec2(0.0f, 0.625f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("x", Vec2(0.0f, 0.5f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xPlus", Vec2(0.75f, 0.4f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xMinus", Vec2(-0.75f, 0.4f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("x", Vec2(0.0f, 0.4f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("y", Vec2(0.0f, 0.275f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yPlus", Vec2(0.75f, 0.175f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yMinus", Vec2(-0.75f, 0.175f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("y", Vec2(0.0f, 0.175f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("z", Vec2(0.0f, 0.05f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zPlus", Vec2(0.75f, -0.05f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zMinus", Vec2(-0.75f, -0.05f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("z", Vec2(0.0f, -0.05f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("r", Vec2(0.0f, -0.175f), Vec2(0.25f, 0.1f), "R", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("rPlus", Vec2(0.75f, -0.275f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("rMinus", Vec2(-0.75f, -0.275f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("r", Vec2(0.0f, -0.275f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("g", Vec2(0.0f, -0.4f), Vec2(0.25f, 0.1f), "G", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("gPlus", Vec2(0.75f, -0.5f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("gMinus", Vec2(-0.75f, -0.5f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("g", Vec2(0.0f, -0.5f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("b", Vec2(0.0f, -0.625f), Vec2(0.25f, 0.1f), "B", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("bPlus", Vec2(0.75f, -0.725f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("bMinus", Vec2(-0.75f, -0.725f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("b", Vec2(0.0f, -0.725f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, -0.9f), Vec2(1.5f, 0.1f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::textColor, LVPC::textHoverColor);

	// Right-viewport: mainWindow - audiocasterPropertiesMenu
	screenID = "audioPropertiesMenu";
	rightWindow->addScreen(screenID);
	rightWindow->getScreen(screenID)->addTextfield("volume", Vec2(0.0f, 0.95f), Vec2(1.5f, 0.1f), "Max volume", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("volumePlus", Vec2(0.75f, 0.85f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("volumeMinus", Vec2(-0.75f, 0.85f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("volume", Vec2(0.0f, 0.85f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("distance", Vec2(0.0f, 0.725f), Vec2(1.5f, 0.1f), "Max distance", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("distancePlus", Vec2(0.75f, 0.625f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("distanceMinus", Vec2(-0.75f, 0.625f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("distance", Vec2(0.0f, 0.625f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("x", Vec2(0.0f, 0.5f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xPlus", Vec2(0.75f, 0.4f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xMinus", Vec2(-0.75f, 0.4f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("x", Vec2(0.0f, 0.4f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("y", Vec2(0.0f, 0.275f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yPlus", Vec2(0.75f, 0.175f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yMinus", Vec2(-0.75f, 0.175f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("y", Vec2(0.0f, 0.175f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("z", Vec2(0.0f, 0.05f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zPlus", Vec2(0.75f, -0.05f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zMinus", Vec2(-0.75f, -0.05f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWriteField("z", Vec2(0.0f, -0.05f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, -0.175f), Vec2(1.5f, 0.1f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::textColor, LVPC::textHoverColor);
}

void SceneEditor::load()
{
	// Load environment preview entities
	_environmentEditor.loadSkyEntitiesFromFile();
	_environmentEditor.loadTerrainEntitiesFromFile();
	_environmentEditor.loadWaterEntitiesFromFile();

	// Load lightsource billboard
	_fe3d.billBoardEntity_add("@@lightSource", "engine\\textures\\light_source.png", _fe3d.gfx_getDirectionalLightingPosition(),
		Vec3(0.0f), Vec2(0.0f), true, true, true, true);
	_fe3d.billboardEntity_setDepthMapIncluded("@@lightSource", false);

	// Preview model loading
	_modelEditor.loadGameEntitiesFromFile();
	for (auto& modelName : _modelEditor.getModelNames())
	{
		// Check if there is a GAME entity present
		if (_fe3d.gameEntity_isExisting(modelName))
		{
			_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelPlace")->getScrollingList("models")->
				addButton(modelName, modelName.substr(1));
		}
	}

	// Preview billboard loading
	_billboardEditor.loadBillboardEntitiesFromFile();
	for (auto& billboardName : _billboardEditor.getBillboardNames())
	{
		// Check if there is a BILLBOARD entity present
		if (_fe3d.billboardEntity_isExisting(billboardName))
		{
			_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardPlace")->getScrollingList("billboards")->
				addButton(billboardName, billboardName.substr(1));
		}
	}

	// Preview pointlight loading
	_fe3d.lightEntity_add(_previewPointlightID);
	_fe3d.lightEntity_hide(_previewPointlightID);
	_fe3d.gameEntity_add(_previewPointlightID, _lightBulbModelPath, Vec3(0.0f), Vec3(0.0f), _defaultLightbulbSize, false);
	_fe3d.gameEntity_setShadowed(_previewPointlightID, false);

	// Preview audio loading
	_audioEditor.loadAudioEntitiesFromFile();
	_fe3d.gameEntity_add(_previewSpeakerID, _speakerModelPath, Vec3(0.0f), Vec3(0.0f), _defaultSpeakerSize, false);
	_fe3d.gameEntity_setShadowed(_previewSpeakerID, false);
	for (auto& audioName : _audioEditor.getAudioNames())
	{
		_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuAudioPlace")->getScrollingList("audiocasters")->
			addButton(audioName, audioName.substr(1));
	}

	// Create name textfields
	_gui.getGlobalScreen()->addTextfield("selectedModelName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedBillboardName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedAudioName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));

	// Miscellaneous
	_fe3d.input_clearKeyToggles();
	_fe3d.collision_enableCameraResponse();
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("sceneEditorControls");
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
	_gui.getGlobalScreen()->deleteTextfield("selectedAudioName");

	// Miscellaneous
	_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelPlace")->getScrollingList("models")->deleteButtons();
	_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelChoice")->getScrollingList("models")->deleteButtons();
	_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardPlace")->getScrollingList("billboards")->deleteButtons();
	_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardChoice")->getScrollingList("billboards")->deleteButtons();
	_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuAudioPlace")->getScrollingList("audiocasters")->deleteButtons();
	_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuAudioChoice")->getScrollingList("audiocasters")->deleteButtons();
	_fe3d.misc_disableAabbFrameRendering();
	_fe3d.misc_disableWireframeRendering();
	_fe3d.misc_disableDebugRendering();
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	_isLoaded = false;
}