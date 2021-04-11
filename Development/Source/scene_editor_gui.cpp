#include "scene_editor.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVPC::calcTextWidth(text, 0.15f, 1.8f)

void SceneEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	string screenID;

	// Left-viewport: mainWindow - sceneEditorMenuMain
	screenID = "sceneEditorMenuMain";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("create", Vec2(0.0f, 0.63f), Vec2(GW("Create"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("edit", Vec2(0.0f, 0.21f), Vec2(GW("Edit"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, -0.21f), Vec2(GW("Remove"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Remove", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuChoice
	screenID = "sceneEditorMenuChoice";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("environment", Vec2(0.0f, 0.7875f), Vec2(GW("Environment"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Environment", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("model", Vec2(0.0f, 0.525f), Vec2(GW("Models"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Models", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("billboard", Vec2(0.0f, 0.2625f), Vec2(GW("Billboards"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Billboards", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("sound", Vec2(0.0f, 0.0f), Vec2(GW("Sound"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sound", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("lighting", Vec2(0.0f, -0.2625f), Vec2(GW("Lighting"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lighting", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("settings", Vec2(0.0f, -0.525f), Vec2(GW("Settings"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Settings", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.7875f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuEnvironment
	screenID = "sceneEditorMenuEnvironment";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("sky", Vec2(0.0f, 0.63f), Vec2(GW("Sky"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("terrain", Vec2(0.0f, 0.21f), Vec2(GW("Terrain"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("water", Vec2(0.0f, -0.21f), Vec2(GW("Water"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuEnvironmentSky
	screenID = "sceneEditorMenuEnvironmentSky";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("choose", Vec2(0.0f, 0.475f), Vec2(GW("Choose sky"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, 0.0f), Vec2(GW("Remove sky"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Remove sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuEnvironmentTerrain
	screenID = "sceneEditorMenuEnvironmentTerrain";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("choose", Vec2(0.0f, 0.475f), Vec2(GW("Choose terrain"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, 0.0f), Vec2(GW("Remove terrain"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Remove terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuEnvironmentWater
	screenID = "sceneEditorMenuEnvironmentWater";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("choose", Vec2(0.0f, 0.475f), Vec2(GW("Choose water"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, 0.0f), Vec2(GW("Remove water"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Remove water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuModel
	screenID = "sceneEditorMenuModel";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("place", Vec2(0.0f, 0.475f), Vec2(GW("Place model"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Place model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("choice", Vec2(0.0f, 0.0f), Vec2(GW("Choose model"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuModelPlace
	screenID = "sceneEditorMenuModelPlace";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("models", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), Vec3(0.3f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.9f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuModelChoice
	screenID = "sceneEditorMenuModelChoice";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("models", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), Vec3(0.3f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.9f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuBillboard
	screenID = "sceneEditorMenuBillboard";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("place", Vec2(0.0f, 0.475f), Vec2(GW("Place billboard"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Place billboard", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("choice", Vec2(0.0f, 0.0f), Vec2(GW("Choose billboard"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose billboard", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuBillboardPlace
	screenID = "sceneEditorMenuBillboardPlace";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("billboards", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), Vec3(0.3f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.9f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuBillboardChoice
	screenID = "sceneEditorMenuBillboardChoice";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("billboards", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), Vec3(0.3f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.9f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSound
	screenID = "sceneEditorMenuSound";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("place", Vec2(0.0f, 0.475f), Vec2(GW("Place sound"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Place sound", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("choice", Vec2(0.0f, 0.0f), Vec2(GW("Choose sound"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose sound", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSoundPlace
	screenID = "sceneEditorMenuSoundPlace";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("soundcasters", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), Vec3(0.3f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.9f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSoundChoice
	screenID = "sceneEditorMenuSoundChoice";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addScrollingList("soundcasters", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), Vec3(0.3f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f));
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.9f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuLighting
	screenID = "sceneEditorMenuLighting";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("ambient", Vec2(0.0f, 0.63f), Vec2(GW("Ambient"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Ambient", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("directional", Vec2(0.0f, 0.21f), Vec2(GW("Directional"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Directional", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("point", Vec2(0.0f, -0.21f), Vec2(GW("Point"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Point", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuLightingAmbient
	screenID = "sceneEditorMenuLightingAmbient";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.63f), Vec2(GW("Enabled: NO"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("color", Vec2(0.0f, 0.21f), Vec2(GW("Color"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("intensity", Vec2(0.0f, -0.21f), Vec2(GW("Intensity"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuLightingDirectional
	screenID = "sceneEditorMenuLightingDirectional";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.75f), Vec2(GW("Enabled: NO"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("color", Vec2(0.0f, 0.45f), Vec2(GW("Color"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("position", Vec2(0.0f, 0.15f), Vec2(GW("Position"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Position", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("intensity", Vec2(0.0f, -0.15f), Vec2(GW("Intensity"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("billboardSize", Vec2(0.0f, -0.45f), Vec2(GW("Billboard size"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Billboard size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.75f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuLightingPoint
	screenID = "sceneEditorMenuLightingPoint";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("add", Vec2(0.0f, 0.45f), Vec2(GW("Place light"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Place light", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.45f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSettings
	screenID = "sceneEditorMenuSettings";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("graphics", Vec2(0.0f, 0.63f), Vec2(GW("Graphics"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Graphics", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("setSpeed", Vec2(0.0f, 0.21f), Vec2(GW("Editor speed"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Editor speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("lodDistance", Vec2(0.0f, -0.21f), Vec2(GW("LOD distance"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "LOD distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphics
	screenID = "sceneEditorMenuSettingsGraphics";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("shadows", Vec2(0.0f, 0.7875f), Vec2(GW("Shadows"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Shadows", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("motionblur", Vec2(0.0f, 0.525f), Vec2(GW("Motion blur"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Motion blur", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("dof", Vec2(0.0f, 0.2625f), Vec2(GW("Depth Of Field"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Depth Of Field", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("fog", Vec2(0.0f, 0.0f), Vec2(GW("Fog"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Fog", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("lensflare", Vec2(0.0f, -0.2625f), Vec2(GW("Lens flare"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lens flare", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("skyHdr", Vec2(0.0f, -0.525f), Vec2(GW("Sky HDR"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sky HDR", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.7875f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsShadows
	screenID = "sceneEditorMenuSettingsGraphicsShadows";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.8f), Vec2(GW("Enabled: NO"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("size", Vec2(0.0f, 0.6f), Vec2(GW("Size"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("position", Vec2(0.0f, 0.4f), Vec2(GW("Position"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Position", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("center", Vec2(0.0f, 0.2f), Vec2(GW("Center"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Center", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("follow", Vec2(0.0f, 0.0f), Vec2(GW("Follow cam: OFF"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Follow cam: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("soft", Vec2(0.0f, -0.2f), Vec2(GW("Soft: OFF"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Soft: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("lightness", Vec2(0.0f, -0.4f), Vec2(GW("Lightness"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("interval", Vec2(0.0f, -0.6f), Vec2(GW("Interval"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Interval", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.8f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsMotionblur
	screenID = "sceneEditorMenuSettingsGraphicsMotionblur";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.475f), Vec2(GW("Enabled: NO"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("strength", Vec2(0.0f, 0.0f), Vec2(GW("Strength"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Strength", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsDof
	screenID = "sceneEditorMenuSettingsGraphicsDof";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.7f), Vec2(GW("Enabled: NO"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("dynamic", Vec2(0.0f, 0.35f), Vec2(GW("Dynamic: NO"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Dynamic: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("blurDistance", Vec2(0.0f, 0.0f), Vec2(GW("Blur distance"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blur distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("maxDistance", Vec2(0.0f, -0.35f), Vec2(GW("DOF distance"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "DOF distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.7f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsFog
	screenID = "sceneEditorMenuSettingsGraphicsFog";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.75f), Vec2(GW("Enabled: NO"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("minDistance", Vec2(0.0f, 0.45f), Vec2(GW("Min distance"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Min distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("maxDistance", Vec2(0.0f, 0.15f), Vec2(GW("Max distance"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Max distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("thickness", Vec2(0.0f, -0.15f), Vec2(GW("Thickness"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Thickness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("color", Vec2(0.0f, -0.45f), Vec2(GW("Color"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.75f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsLensFlare
	screenID = "sceneEditorMenuSettingsGraphicsLensFlare";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.7f), Vec2(GW("Enabled: NO"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("loadFlareMap", Vec2(0.0f, 0.35f), Vec2(GW("FlareMap"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "FlareMap", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("intensity", Vec2(0.0f, 0.0f), Vec2(GW("Intensity"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("multiplier", Vec2(0.0f, -0.35f), Vec2(GW("Multiplier"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Multiplier", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.7f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - sceneEditorMenuSettingsGraphicsSkyHDR
	screenID = "sceneEditorMenuSettingsGraphicsSkyHDR";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("enabled", Vec2(0.0f, 0.475f), Vec2(GW("Enabled: NO"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("intensity", Vec2(0.0f, 0.0f), Vec2(GW("Intensity"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.475f), Vec2(GW("Go back"), 0.1f), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Right-viewport: mainWindow - modelPropertiesMenu
	screenID = "modelPropertiesMenu";
	rightWindow->addScreen(screenID);
	rightWindow->getScreen(screenID)->addTextfield("transformation", Vec2(0.0f, 0.95f), Vec2(1.75f, 0.1f), "Transformation", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("translation", Vec2(0.0f, 0.8f), Vec2(0.75f, 0.2f), "translation.png", Vec3(0.0f));
	rightWindow->getScreen(screenID)->addButton("rotation", Vec2(0.0f, 0.55f), Vec2(0.75f, 0.2f), "rotation.png", Vec3(0.0f));
	rightWindow->getScreen(screenID)->addButton("scaling", Vec2(0.0f, 0.3f), Vec2(0.75f, 0.2f), "scaling.png", Vec3(0.0f));
	rightWindow->getScreen(screenID)->addButton("freeze", Vec2(0.0f, 0.13f), Vec2(1.15f, 0.075f), Vec3(0.0f, 0.0f, 0.75f), Vec3(0.25f, 0.25f, 1.0f), "Freeze", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	rightWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, -0.03f), Vec2(1.25f, 0.075f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	rightWindow->getScreen(screenID)->addTextfield("x", Vec2(0.0f, -0.15f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("y", Vec2(0.0f, -0.4f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("z", Vec2(0.0f, -0.65f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xPlus", Vec2(0.75f, -0.25f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yPlus", Vec2(0.75f, -0.5f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zPlus", Vec2(0.75f, -0.75f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xMinus", Vec2(-0.75f, -0.25f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yMinus", Vec2(-0.75f, -0.5f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zMinus", Vec2(-0.75f, -0.75f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("x", Vec2(0.0f, -0.25f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWritefield("y", Vec2(0.0f, -0.5f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWritefield("z", Vec2(0.0f, -0.75f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addButton("animation", Vec2(0.0f, -0.9f), Vec2(1.5f, 0.08f), Vec3(0.0f, 0.0f, 0.75f), Vec3(0.25f, 0.25f, 1.0f), "Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Right-viewport: mainWindow - billboardPropertiesMenu
	screenID = "billboardPropertiesMenu";
	rightWindow->addScreen(screenID);
	rightWindow->getScreen(screenID)->addTextfield("transformation", Vec2(0.0f, 0.95f), Vec2(1.75f, 0.1f), "Transformation", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("translation", Vec2(0.0f, 0.8f), Vec2(0.75f, 0.2f), "translation.png", Vec3(0.0f));
	rightWindow->getScreen(screenID)->addButton("rotation", Vec2(0.0f, 0.55f), Vec2(0.75f, 0.2f), "rotation.png", Vec3(0.0f));
	rightWindow->getScreen(screenID)->addButton("scaling", Vec2(0.0f, 0.3f), Vec2(0.75f, 0.2f), "scaling.png", Vec3(0.0f));
	rightWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, 0.05f), Vec2(1.25f, 0.075f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	rightWindow->getScreen(screenID)->addTextfield("x", Vec2(0.0f, -0.15f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("y", Vec2(0.0f, -0.4f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addTextfield("z", Vec2(0.0f, -0.65f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xPlus", Vec2(0.75f, -0.25f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yPlus", Vec2(0.75f, -0.5f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zPlus", Vec2(0.75f, -0.75f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xMinus", Vec2(-0.75f, -0.25f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yMinus", Vec2(-0.75f, -0.5f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zMinus", Vec2(-0.75f, -0.75f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("x", Vec2(0.0f, -0.25f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWritefield("y", Vec2(0.0f, -0.5f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addWritefield("z", Vec2(0.0f, -0.75f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);

	// Right-viewport: mainWindow - pointlightPropertiesMenu
	screenID = "pointlightPropertiesMenu";
	rightWindow->addScreen(screenID);
	rightWindow->getScreen(screenID)->addTextfield("intensity", Vec2(0.0f, 0.95f), Vec2(1.5f, 0.1f), "Intensity", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("intensityPlus", Vec2(0.75f, 0.85f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("intensityMinus", Vec2(-0.75f, 0.85f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("intensity", Vec2(0.0f, 0.85f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("distance", Vec2(0.0f, 0.725f), Vec2(1.5f, 0.1f), "Distance", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("distancePlus", Vec2(0.75f, 0.625f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("distanceMinus", Vec2(-0.75f, 0.625f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("distance", Vec2(0.0f, 0.625f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("x", Vec2(0.0f, 0.5f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xPlus", Vec2(0.75f, 0.4f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xMinus", Vec2(-0.75f, 0.4f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("x", Vec2(0.0f, 0.4f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("y", Vec2(0.0f, 0.275f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yPlus", Vec2(0.75f, 0.175f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yMinus", Vec2(-0.75f, 0.175f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("y", Vec2(0.0f, 0.175f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("z", Vec2(0.0f, 0.05f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zPlus", Vec2(0.75f, -0.05f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zMinus", Vec2(-0.75f, -0.05f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("z", Vec2(0.0f, -0.05f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("r", Vec2(0.0f, -0.175f), Vec2(0.25f, 0.1f), "R", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("rPlus", Vec2(0.75f, -0.275f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("rMinus", Vec2(-0.75f, -0.275f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("r", Vec2(0.0f, -0.275f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("g", Vec2(0.0f, -0.4f), Vec2(0.25f, 0.1f), "G", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("gPlus", Vec2(0.75f, -0.5f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("gMinus", Vec2(-0.75f, -0.5f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("g", Vec2(0.0f, -0.5f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("b", Vec2(0.0f, -0.625f), Vec2(0.25f, 0.1f), "B", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("bPlus", Vec2(0.75f, -0.725f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("bMinus", Vec2(-0.75f, -0.725f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("b", Vec2(0.0f, -0.725f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, -0.9f), Vec2(1.5f, 0.1f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Right-viewport: mainWindow - soundPropertiesMenu
	screenID = "soundPropertiesMenu";
	rightWindow->addScreen(screenID);
	rightWindow->getScreen(screenID)->addTextfield("volume", Vec2(0.0f, 0.95f), Vec2(1.5f, 0.1f), "Max volume", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("volumePlus", Vec2(0.75f, 0.85f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("volumeMinus", Vec2(-0.75f, 0.85f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("volume", Vec2(0.0f, 0.85f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("distance", Vec2(0.0f, 0.725f), Vec2(1.5f, 0.1f), "Max distance", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("distancePlus", Vec2(0.75f, 0.625f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("distanceMinus", Vec2(-0.75f, 0.625f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("distance", Vec2(0.0f, 0.625f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("x", Vec2(0.0f, 0.5f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xPlus", Vec2(0.75f, 0.4f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("xMinus", Vec2(-0.75f, 0.4f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("x", Vec2(0.0f, 0.4f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("y", Vec2(0.0f, 0.275f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yPlus", Vec2(0.75f, 0.175f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("yMinus", Vec2(-0.75f, 0.175f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("y", Vec2(0.0f, 0.175f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addTextfield("z", Vec2(0.0f, 0.05f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zPlus", Vec2(0.75f, -0.05f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addButton("zMinus", Vec2(-0.75f, -0.05f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen(screenID)->addWritefield("z", Vec2(0.0f, -0.05f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, -0.175f), Vec2(1.5f, 0.1f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
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
	leftWindow->deleteScreen("sceneEditorMenuSettingsGraphicsMotionblur");
	leftWindow->deleteScreen("sceneEditorMenuSettingsGraphicsDof");
	leftWindow->deleteScreen("sceneEditorMenuSettingsGraphicsFog");
	leftWindow->deleteScreen("sceneEditorMenuSettingsGraphicsLensFlare");
	leftWindow->deleteScreen("sceneEditorMenuSettingsGraphicsSkyHDR");
	rightWindow->deleteScreen("modelPropertiesMenu");
	rightWindow->deleteScreen("billboardPropertiesMenu");
	rightWindow->deleteScreen("pointlightPropertiesMenu");
	rightWindow->deleteScreen("soundPropertiesMenu");
}