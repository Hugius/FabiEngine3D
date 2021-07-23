#include "scene_editor.hpp"
#include "left_viewport_controller.hpp"

#define CW(text) VPC::calculateTextWidth(text, 0.115f)

constexpr auto TH = 0.0875f;

void SceneEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	string screenID = "";

	// Left-viewport: mainWindow - sceneEditorMenuMain
	screenID = "sceneEditorMenuMain";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("add", Vec2(0.0f, 0.63f), Vec2(CW("Add Scene"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Add Scene", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("edit", Vec2(0.0f, 0.21f), Vec2(CW("Edit Scene"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Scene", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, -0.21f), Vec2(CW("Delete Scene"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Scene", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuChoice
	screenID = "sceneEditorMenuChoice";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("environment", Vec2(0.0f, 0.7875f), Vec2(CW("Environment"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Environment", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("model", Vec2(0.0f, 0.525f), Vec2(CW("Models"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Models", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("billboard", Vec2(0.0f, 0.2625f), Vec2(CW("Billboards"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Billboards", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("sound", Vec2(0.0f, 0.0f), Vec2(CW("Sounds"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sounds", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("lighting", Vec2(0.0f, -0.2625f), Vec2(CW("Lighting"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lighting", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("settings", Vec2(0.0f, -0.525f), Vec2(CW("Settings"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Settings", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.7875f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuEnvironment
	screenID = "sceneEditorMenuEnvironment";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("sky", Vec2(0.0f, 0.63f), Vec2(CW("Sky"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("terrain", Vec2(0.0f, 0.21f), Vec2(CW("Terrain"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("water", Vec2(0.0f, -0.21f), Vec2(CW("Water"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuEnvironmentSky
	screenID = "sceneEditorMenuEnvironmentSky";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("choose", Vec2(0.0f, 0.475f), Vec2(CW("Choose Sky"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, 0.0f), Vec2(CW("Delete Sky"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuEnvironmentTerrain
	screenID = "sceneEditorMenuEnvironmentTerrain";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("choose", Vec2(0.0f, 0.475f), Vec2(CW("Choose Terrain"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, 0.0f), Vec2(CW("Delete Terrain"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuEnvironmentWater
	screenID = "sceneEditorMenuEnvironmentWater";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("choose", Vec2(0.0f, 0.475f), Vec2(CW("Choose Water"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, 0.0f), Vec2(CW("Delete Water"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuModel
	screenID = "sceneEditorMenuModel";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("place", Vec2(0.0f, 0.475f), Vec2(CW("Place Model"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Place Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("choice", Vec2(0.0f, 0.0f), Vec2(CW("Choose Model"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuModelPlace
	screenID = "sceneEditorMenuModelPlace";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("modelList", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.9f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuModelChoice
	screenID = "sceneEditorMenuModelChoice";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("modelList", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.9f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuBillboard
	screenID = "sceneEditorMenuBillboard";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("place", Vec2(0.0f, 0.475f), Vec2(CW("Place Billboard"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Place Billboard", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("choice", Vec2(0.0f, 0.0f), Vec2(CW("Choose Billboard"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Billboard", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuBillboardPlace
	screenID = "sceneEditorMenuBillboardPlace";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("billboardList", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.9f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuBillboardChoice
	screenID = "sceneEditorMenuBillboardChoice";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("billboardList", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.9f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSound
	screenID = "sceneEditorMenuSound";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("place", Vec2(0.0f, 0.475f), Vec2(CW("Place Sound"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Place Sound", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("choice", Vec2(0.0f, 0.0f), Vec2(CW("Choose Sound"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Sound", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSoundPlace
	screenID = "sceneEditorMenuSoundPlace";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("soundcasters", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.9f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSoundChoice
	screenID = "sceneEditorMenuSoundChoice";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("soundcasters", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.9f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuLighting
	screenID = "sceneEditorMenuLighting";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("ambient", Vec2(0.0f, 0.63f), Vec2(CW("Ambient"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Ambient", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("directional", Vec2(0.0f, 0.21f), Vec2(CW("Directional"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Directional", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("point", Vec2(0.0f, -0.21f), Vec2(CW("Point"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Point", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuLightingAmbient
	screenID = "sceneEditorMenuLightingAmbient";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.63f), Vec2(CW("Enabled: NO"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("color", Vec2(0.0f, 0.21f), Vec2(CW("Color"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("intensity", Vec2(0.0f, -0.21f), Vec2(CW("Intensity"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuLightingDirectional
	screenID = "sceneEditorMenuLightingDirectional";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.75f), Vec2(CW("Enabled: NO"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("color", Vec2(0.0f, 0.45f), Vec2(CW("Color"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("position", Vec2(0.0f, 0.15f), Vec2(CW("Position"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Position", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("intensity", Vec2(0.0f, -0.15f), Vec2(CW("Intensity"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("billboardSize", Vec2(0.0f, -0.45f), Vec2(CW("Billboard Size"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Billboard Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.75f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuLightingPoint
	screenID = "sceneEditorMenuLightingPoint";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("add", Vec2(0.0f, 0.45f), Vec2(CW("Place Light"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Place Light", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.45f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSettings
	screenID = "sceneEditorMenuSettings";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("graphics", Vec2(0.0f, 0.7f), Vec2(CW("Graphics"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Graphics", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("setSpeed", Vec2(0.0f, 0.35f), Vec2(CW("Editor Speed"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Editor Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("lodDistance", Vec2(0.0f, 0.0f), Vec2(CW("LOD Distance"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "LOD Distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("reflectionHeight", Vec2(0.0f, -0.35f), Vec2(CW("Reflect height"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflect height", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.7f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphics
	screenID = "sceneEditorMenuSettingsGraphics";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("shadows", Vec2(0.0f, 0.83f), Vec2(CW("Shadows"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Shadows", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("motionBlur", Vec2(0.0f, 0.59f), Vec2(CW("Motion Blur"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Motion Blur", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("dof", Vec2(0.0f, 0.36f), Vec2(CW("Depth Of Field"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Depth Of Field", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("fog", Vec2(0.0f, 0.13f), Vec2(CW("Fog"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Fog", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("lensFlare", Vec2(0.0f, -0.13f), Vec2(CW("Lens Flare"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lens Flare", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("skyExposure", Vec2(0.0f, -0.36f), Vec2(CW("Sky Exposure"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sky Exposure", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("bloom", Vec2(0.0f, -0.59f), Vec2(CW("Bloom"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Bloom", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.83f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsShadows
	screenID = "sceneEditorMenuSettingsGraphicsShadows";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.8f), Vec2(CW("Enabled: NO"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("size", Vec2(0.0f, 0.6f), Vec2(CW("Size"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("position", Vec2(0.0f, 0.4f), Vec2(CW("Position"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Position", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("center", Vec2(0.0f, 0.2f), Vec2(CW("Center"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Center", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("follow", Vec2(0.0f, 0.0f), Vec2(CW("Follow Cam: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Follow Cam: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("lighted", Vec2(0.0f, -0.2f), Vec2(CW("Lighted: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lighted: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("lightness", Vec2(0.0f, -0.4f), Vec2(CW("Lightness"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("interval", Vec2(0.0f, -0.6f), Vec2(CW("Interval"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Interval", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.8f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsMotionBlur
	screenID = "sceneEditorMenuSettingsGraphicsMotionBlur";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.475f), Vec2(CW("Enabled: NO"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("strength", Vec2(0.0f, 0.0f), Vec2(CW("Strength"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Strength", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsDof
	screenID = "sceneEditorMenuSettingsGraphicsDof";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.7f), Vec2(CW("Enabled: NO"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("dynamic", Vec2(0.0f, 0.35f), Vec2(CW("Dynamic: NO"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Dynamic: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("blurDistance", Vec2(0.0f, 0.0f), Vec2(CW("Blur Distance"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blur Distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("maxDistance", Vec2(0.0f, -0.35f), Vec2(CW("DOF Distance"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "DOF Distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.7f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsFog
	screenID = "sceneEditorMenuSettingsGraphicsFog";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.75f), Vec2(CW("Enabled: NO"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("minDistance", Vec2(0.0f, 0.45f), Vec2(CW("Min Distance"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Min Distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("maxDistance", Vec2(0.0f, 0.15f), Vec2(CW("Max Distance"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Max Distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("thickness", Vec2(0.0f, -0.15f), Vec2(CW("Thickness"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Thickness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("color", Vec2(0.0f, -0.45f), Vec2(CW("Color"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.75f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsLensFlare
	screenID = "sceneEditorMenuSettingsGraphicsLensFlare";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.7f), Vec2(CW("Enabled: NO"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("loadFlareMap", Vec2(0.0f, 0.35f), Vec2(CW("Flare Map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Flare Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("intensity", Vec2(0.0f, 0.0f), Vec2(CW("Intensity"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("multiplier", Vec2(0.0f, -0.35f), Vec2(CW("Multiplier"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Multiplier", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.7f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsSkyExposure
	screenID = "sceneEditorMenuSettingsGraphicsSkyExposure";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.63f), Vec2(CW("Enabled: NO"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("factor", Vec2(0.0f, 0.21f), Vec2(CW("Factor"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Factor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("speed", Vec2(0.0f, -0.21f), Vec2(CW("Speed"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	
	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsBloom
	screenID = "sceneEditorMenuSettingsGraphicsBloom";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.7f), Vec2(CW("Enabled: NO"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("type", Vec2(0.0f, 0.35f), Vec2(CW("Type: EVERYTHING"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Type: EVERYTHING", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("intensity", Vec2(0.0f, 0.0f), Vec2(CW("Intensity"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("blurs", Vec2(0.0f, -0.35f), Vec2(CW("Blurs"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blurs", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.7f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Right-viewport: mainWindow - modelPropertiesMenu
	screenID = "modelPropertiesMenu";
	rightWindow->addScreen(screenID);
	rightWindow->getScreen(screenID)->addTextfield("title", Vec2(0.0f, 0.95f), Vec2(1.25f, 0.1f), "Model Menu", Vec3(0.0f, 1.0f, 0.0f));
	rightWindow->getScreen(screenID)->addButton("position", Vec2(0.0f, 0.8f), Vec2(0.75f, 0.2f), "position.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("rotation", Vec2(0.0f, 0.55f), Vec2(0.75f, 0.2f), "rotation.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("size", Vec2(0.0f, 0.3f), Vec2(0.75f, 0.2f), "size.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("x", Vec2(0.0f, 0.135f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("y", Vec2(0.0f, -0.115f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("z", Vec2(0.0f, -0.365f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xPlus", Vec2(0.75f, 0.025f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yPlus", Vec2(0.75f, -0.225f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zPlus", Vec2(0.75f, -0.475f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xMinus", Vec2(-0.75f, 0.025f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yMinus", Vec2(-0.75f, -0.225f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zMinus", Vec2(-0.75f, -0.475f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("x", Vec2(0.0f, 0.025f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWritefield("y", Vec2(0.0f, -0.225f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWritefield("z", Vec2(0.0f, -0.475f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addButton("animation", Vec2(0.0f, -0.625f), Vec2(1.5f, 0.08f), Vec3(0.0f, 0.0f, 0.75f), Vec3(0.25f, 0.25f, 1.0f), "Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	rightWindow->getScreen(screenID)->addButton("freeze", Vec2(0.0f, -0.775f), Vec2(1.0f, 0.08f), Vec3(0.0f, 0.0f, 0.75f), Vec3(0.25f, 0.25f, 1.0f), "Freeze", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	rightWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, -0.925f), Vec2(1.0f, 0.08f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Right-viewport: mainWindow - billboardPropertiesMenu
	screenID = "billboardPropertiesMenu";
	rightWindow->addScreen(screenID);
	rightWindow->getScreen(screenID)->addTextfield("title", Vec2(0.0f, 0.95f), Vec2(1.75f, 0.1f), "Billboard Menu", Vec3(0.0f, 1.0f, 0.0f));
	rightWindow->getScreen(screenID)->addButton("position", Vec2(0.0f, 0.8f), Vec2(0.75f, 0.2f), "position.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("rotation", Vec2(0.0f, 0.55f), Vec2(0.75f, 0.2f), "rotation.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("size", Vec2(0.0f, 0.3f), Vec2(0.75f, 0.2f), "size.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("x", Vec2(0.0f, 0.135f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("y", Vec2(0.0f, -0.115f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("z", Vec2(0.0f, -0.365f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xPlus", Vec2(0.75f, 0.025f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yPlus", Vec2(0.75f, -0.225f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zPlus", Vec2(0.75f, -0.475f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xMinus", Vec2(-0.75f, 0.025f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yMinus", Vec2(-0.75f, -0.225f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zMinus", Vec2(-0.75f, -0.475f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("x", Vec2(0.0f, 0.025f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWritefield("y", Vec2(0.0f, -0.225f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWritefield("z", Vec2(0.0f, -0.475f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, -0.775f), Vec2(1.0f, 0.08f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Right-viewport: mainWindow - pointLightPropertiesMenu
	screenID = "pointLightPropertiesMenu";
	rightWindow->addScreen(screenID);
	rightWindow->getScreen(screenID)->addTextfield("title", Vec2(0.0f, 0.95f), Vec2(1.25f, 0.1f), "Light Menu", Vec3(0.0f, 1.0f, 0.0f));
	rightWindow->getScreen(screenID)->addButton("position", Vec2(0.0f, 0.8f), Vec2(0.75f, 0.2f), "position.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("radius", Vec2(0.0f, 0.55f), Vec2(0.75f, 0.2f), "radius.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("color", Vec2(0.0f, 0.3f), Vec2(0.75f, 0.2f), "color.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("x", Vec2(0.0f, 0.135f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("y", Vec2(0.0f, -0.115f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("z", Vec2(0.0f, -0.365f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xPlus", Vec2(0.75f, 0.025f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yPlus", Vec2(0.75f, -0.225f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zPlus", Vec2(0.75f, -0.475f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xMinus", Vec2(-0.75f, 0.025f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yMinus", Vec2(-0.75f, -0.225f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zMinus", Vec2(-0.75f, -0.475f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("x", Vec2(0.0f, 0.025f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWritefield("y", Vec2(0.0f, -0.225f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWritefield("z", Vec2(0.0f, -0.475f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("intensity", Vec2(0.0f, -0.64f), Vec2(1.5f, 0.1f), "Intensity", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("intensityPlus", Vec2(0.75f, -0.75f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("intensityMinus", Vec2(-0.75f, -0.75f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("intensity", Vec2(0.0f, -0.75f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, -0.9f), Vec2(1.0f, 0.08f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Right-viewport: mainWindow - soundPropertiesMenu
	screenID = "soundPropertiesMenu";
	rightWindow->addScreen(screenID);
	rightWindow->getScreen(screenID)->addTextfield("title", Vec2(0.0f, 0.95f), Vec2(1.25f, 0.1f), "Sound Menu", Vec3(0.0f, 1.0f, 0.0f));
	rightWindow->getScreen(screenID)->addTextfield("x", Vec2(0.0f, 0.8f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("y", Vec2(0.0f, 0.55f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("z", Vec2(0.0f, 0.3f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xPlus", Vec2(0.75f, 0.7f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yPlus", Vec2(0.75f, 0.45f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zPlus", Vec2(0.75f, 0.2f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xMinus", Vec2(-0.75f, 0.7f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yMinus", Vec2(-0.75f, 0.45f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zMinus", Vec2(-0.75f, 0.2f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("x", Vec2(0.0f, 0.7f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWritefield("y", Vec2(0.0f, 0.45f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWritefield("z", Vec2(0.0f, 0.2f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("distance", Vec2(0.0f, -0.325f), Vec2(1.5f, 0.1f), "Max distance", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("distancePlus", Vec2(0.75f, -0.425f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("distanceMinus", Vec2(-0.75f, -0.425f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("distance", Vec2(0.0f, -0.425f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("volume", Vec2(0.0f, -0.55f), Vec2(1.25f, 0.1f), "Max volume", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("volumePlus", Vec2(0.75f, -0.65f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("volumeMinus", Vec2(-0.75f, -0.65f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("volume", Vec2(0.0f, -0.65f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, -0.9f), Vec2(1.5f, 0.1f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void SceneEditor::_unloadGUI()
{
	auto leftWindow = _gui.getViewport("left")->getWindow("main");
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	leftWindow->deleteScreen("sceneEditorMenuMain");
	leftWindow->deleteScreen("sceneEditorMenuChoice");
	leftWindow->deleteScreen("sceneEditorMenuEnvironment");
	leftWindow->deleteScreen("sceneEditorMenuEnvironmentSky");
	leftWindow->deleteScreen("sceneEditorMenuEnvironmentTerrain");
	leftWindow->deleteScreen("sceneEditorMenuEnvironmentWater");
	leftWindow->deleteScreen("sceneEditorMenuModel");
	leftWindow->deleteScreen("sceneEditorMenuModelPlace");
	leftWindow->deleteScreen("sceneEditorMenuModelChoice");
	leftWindow->deleteScreen("sceneEditorMenuBillboard");
	leftWindow->deleteScreen("sceneEditorMenuBillboardPlace");
	leftWindow->deleteScreen("sceneEditorMenuBillboardChoice");
	leftWindow->deleteScreen("sceneEditorMenuLighting");
	leftWindow->deleteScreen("sceneEditorMenuLightingAmbient");
	leftWindow->deleteScreen("sceneEditorMenuLightingDirectional");
	leftWindow->deleteScreen("sceneEditorMenuLightingPoint");
	leftWindow->deleteScreen("sceneEditorMenuSound");
	leftWindow->deleteScreen("sceneEditorMenuSoundPlace");
	leftWindow->deleteScreen("sceneEditorMenuSoundChoice");
	leftWindow->deleteScreen("sceneEditorMenuSettings");
	leftWindow->deleteScreen("sceneEditorMenuSettingsGraphics");
	leftWindow->deleteScreen("sceneEditorMenuSettingsGraphicsShadows");
	leftWindow->deleteScreen("sceneEditorMenuSettingsGraphicsMotionBlur");
	leftWindow->deleteScreen("sceneEditorMenuSettingsGraphicsDof");
	leftWindow->deleteScreen("sceneEditorMenuSettingsGraphicsFog");
	leftWindow->deleteScreen("sceneEditorMenuSettingsGraphicsLensFlare");
	leftWindow->deleteScreen("sceneEditorMenuSettingsGraphicsSkyExposure");
	leftWindow->deleteScreen("sceneEditorMenuSettingsGraphicsBloom");
	rightWindow->deleteScreen("modelPropertiesMenu");
	rightWindow->deleteScreen("billboardPropertiesMenu");
	rightWindow->deleteScreen("pointLightPropertiesMenu");
	rightWindow->deleteScreen("soundPropertiesMenu");
}