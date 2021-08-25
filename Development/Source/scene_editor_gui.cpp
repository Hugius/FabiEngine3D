#include "scene_editor.hpp"
#include "left_viewport_controller.hpp"

#define TW(text) VPC::calculateTextWidth(text, CW)

void SceneEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	// Left-viewport: sceneEditorMenuMain
	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("sceneEditorMenuMain");
	leftWindow->getScreen("sceneEditorMenuMain")->createButton("create", Vec2(0.0f, positions[0]), Vec2(TW("Create Scene"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Scene", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuMain")->createButton("edit", Vec2(0.0f, positions[1]), Vec2(TW("Edit Scene"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Scene", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuMain")->createButton("delete", Vec2(0.0f, positions[2]), Vec2(TW("Delete Scene"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Scene", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuMain")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuChoice
	positions = VPC::calculateButtonPositions(9, CH);
	leftWindow->createScreen("sceneEditorMenuChoice");
	leftWindow->getScreen("sceneEditorMenuChoice")->createButton("sky", Vec2(0.0f, positions[0]), Vec2(TW("Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuChoice")->createButton("terrain", Vec2(0.0f, positions[1]), Vec2(TW("Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuChoice")->createButton("water", Vec2(0.0f, positions[2]), Vec2(TW("Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuChoice")->createButton("models", Vec2(0.0f, positions[3]), Vec2(TW("Models"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Models", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuChoice")->createButton("billboards", Vec2(0.0f, positions[4]), Vec2(TW("Billboards"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Billboards", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuChoice")->createButton("sounds", Vec2(0.0f, positions[5]), Vec2(TW("Sounds"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sounds", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuChoice")->createButton("lights", Vec2(0.0f, positions[6]), Vec2(TW("Lights"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lights", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuChoice")->createButton("settings", Vec2(0.0f, positions[7]), Vec2(TW("Settings"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Settings", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuChoice")->createButton("back", Vec2(0.0f, positions[8]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuSky
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("sceneEditorMenuSky");
	leftWindow->getScreen("sceneEditorMenuSky")->createButton("choose", Vec2(0.0f, positions[0]), Vec2(TW("Choose Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSky")->createButton("delete", Vec2(0.0f, positions[1]), Vec2(TW("Delete Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSky")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuTerrain
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("sceneEditorMenuTerrain");
	leftWindow->getScreen("sceneEditorMenuTerrain")->createButton("choose", Vec2(0.0f, positions[0]), Vec2(TW("Choose Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuTerrain")->createButton("delete", Vec2(0.0f, positions[1]), Vec2(TW("Delete Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuTerrain")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuWater
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("sceneEditorMenuWater");
	leftWindow->getScreen("sceneEditorMenuWater")->createButton("choose", Vec2(0.0f, positions[0]), Vec2(TW("Choose Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuWater")->createButton("delete", Vec2(0.0f, positions[1]), Vec2(TW("Delete Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuWater")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuModel
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("sceneEditorMenuModel");
	leftWindow->getScreen("sceneEditorMenuModel")->createButton("place", Vec2(0.0f, positions[0]), Vec2(TW("Place Model"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Place Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuModel")->createButton("choice", Vec2(0.0f, positions[1]), Vec2(TW("Choose Model"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuModel")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuModelPlace
	leftWindow->createScreen("sceneEditorMenuModelPlace");
	leftWindow->getScreen("sceneEditorMenuModelPlace")->createScrollingList("modelList", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f));
	leftWindow->getScreen("sceneEditorMenuModelPlace")->createButton("back", Vec2(0.0f, -0.9f), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuModelChoice
	leftWindow->createScreen("sceneEditorMenuModelChoice");
	leftWindow->getScreen("sceneEditorMenuModelChoice")->createScrollingList("modelList", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f));
	leftWindow->getScreen("sceneEditorMenuModelChoice")->createButton("back", Vec2(0.0f, -0.9f), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuBillboard
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("sceneEditorMenuBillboard");
	leftWindow->getScreen("sceneEditorMenuBillboard")->createButton("place", Vec2(0.0f, positions[0]), Vec2(TW("Place Billboard"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Place Billboard", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuBillboard")->createButton("choice", Vec2(0.0f, positions[1]), Vec2(TW("Choose Billboard"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Billboard", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuBillboard")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuBillboardPlace
	leftWindow->createScreen("sceneEditorMenuBillboardPlace");
	leftWindow->getScreen("sceneEditorMenuBillboardPlace")->createScrollingList("billboardList", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f));
	leftWindow->getScreen("sceneEditorMenuBillboardPlace")->createButton("back", Vec2(0.0f, -0.9f), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuBillboardChoice
	leftWindow->createScreen("sceneEditorMenuBillboardChoice");
	leftWindow->getScreen("sceneEditorMenuBillboardChoice")->createScrollingList("billboardList", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f));
	leftWindow->getScreen("sceneEditorMenuBillboardChoice")->createButton("back", Vec2(0.0f, -0.9f), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuSound
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("sceneEditorMenuSound");
	leftWindow->getScreen("sceneEditorMenuSound")->createButton("place", Vec2(0.0f, positions[0]), Vec2(TW("Place Sound"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Place Sound", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSound")->createButton("choice", Vec2(0.0f, positions[1]), Vec2(TW("Choose Sound"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Sound", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSound")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuSoundPlace
	leftWindow->createScreen("sceneEditorMenuSoundPlace");
	leftWindow->getScreen("sceneEditorMenuSoundPlace")->createScrollingList("sounds", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f));
	leftWindow->getScreen("sceneEditorMenuSoundPlace")->createButton("back", Vec2(0.0f, -0.9f), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuSoundChoice
	leftWindow->createScreen("sceneEditorMenuSoundChoice");
	leftWindow->getScreen("sceneEditorMenuSoundChoice")->createScrollingList("sounds", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f));
	leftWindow->getScreen("sceneEditorMenuSoundChoice")->createButton("back", Vec2(0.0f, -0.9f), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	
	// Left-viewport: sceneEditorMenuLight
	positions = VPC::calculateButtonPositions(2, CH);
	leftWindow->createScreen("sceneEditorMenuLight");
	leftWindow->getScreen("sceneEditorMenuLight")->createButton("place", Vec2(0.0f, positions[0]), Vec2(TW("Place Light"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Place Light", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuLight")->createButton("back", Vec2(0.0f, positions[1]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuSettings
	positions = VPC::calculateButtonPositions(6, CH);
	leftWindow->createScreen("sceneEditorMenuSettings");
	leftWindow->getScreen("sceneEditorMenuSettings")->createButton("lighting", Vec2(0.0f, positions[0]), Vec2(TW("Lighting"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lighting", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettings")->createButton("graphics", Vec2(0.0f, positions[1]), Vec2(TW("Graphics"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Graphics", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettings")->createButton("setSpeed", Vec2(0.0f, positions[2]), Vec2(TW("Editor Speed"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Editor Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettings")->createButton("lodDistance", Vec2(0.0f, positions[3]), Vec2(TW("LOD Distance"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "LOD Distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettings")->createButton("planarHeight", Vec2(0.0f, positions[4]), Vec2(TW("Planar Height"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Planar Height", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettings")->createButton("back", Vec2(0.0f, positions[5]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuSettingsLighting
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("sceneEditorMenuSettingsLighting");
	leftWindow->getScreen("sceneEditorMenuSettingsLighting")->createButton("ambient", Vec2(0.0f, positions[0]), Vec2(TW("Ambient"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Ambient", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsLighting")->createButton("directional", Vec2(0.0f, positions[1]), Vec2(TW("Directional"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Directional", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsLighting")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuSettingsLightingAmbient
	positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("sceneEditorMenuSettingsLightingAmbient");
	leftWindow->getScreen("sceneEditorMenuSettingsLightingAmbient")->createButton("enabled", Vec2(0.0f, positions[0]), Vec2(TW("Enabled: NO"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsLightingAmbient")->createButton("color", Vec2(0.0f, positions[1]), Vec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsLightingAmbient")->createButton("intensity", Vec2(0.0f, positions[2]), Vec2(TW("Intensity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsLightingAmbient")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuSettingsLightingDirectional
	positions = VPC::calculateButtonPositions(6, CH);
	leftWindow->createScreen("sceneEditorMenuSettingsLightingDirectional");
	leftWindow->getScreen("sceneEditorMenuSettingsLightingDirectional")->createButton("enabled", Vec2(0.0f, positions[0]), Vec2(TW("Enabled: NO"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsLightingDirectional")->createButton("color", Vec2(0.0f, positions[1]), Vec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsLightingDirectional")->createButton("position", Vec2(0.0f, positions[2]), Vec2(TW("Position"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Position", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsLightingDirectional")->createButton("intensity", Vec2(0.0f, positions[3]), Vec2(TW("Intensity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsLightingDirectional")->createButton("billboardSize", Vec2(0.0f, positions[4]), Vec2(TW("Billboard Size"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Billboard Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsLightingDirectional")->createButton("back", Vec2(0.0f, positions[5]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuSettingsGraphics
	positions = VPC::calculateButtonPositions(8, CH);
	leftWindow->createScreen("sceneEditorMenuSettingsGraphics");
	leftWindow->getScreen("sceneEditorMenuSettingsGraphics")->createButton("shadows", Vec2(0.0f, positions[0]), Vec2(TW("Shadows"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Shadows", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphics")->createButton("motionBlur", Vec2(0.0f, positions[1]), Vec2(TW("Motion Blur"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Motion Blur", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphics")->createButton("dof", Vec2(0.0f, positions[2]), Vec2(TW("Depth Of Field"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Depth Of Field", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphics")->createButton("fog", Vec2(0.0f, positions[3]), Vec2(TW("Fog"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Fog", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphics")->createButton("lensFlare", Vec2(0.0f, positions[4]), Vec2(TW("Lens Flare"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lens Flare", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphics")->createButton("skyExposure", Vec2(0.0f, positions[5]), Vec2(TW("Sky Exposure"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sky Exposure", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphics")->createButton("bloom", Vec2(0.0f, positions[6]), Vec2(TW("Bloom"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Bloom", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphics")->createButton("back", Vec2(0.0f, positions[7]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuSettingsGraphicsShadows
	positions = VPC::calculateButtonPositions(8, CH);
	leftWindow->createScreen("sceneEditorMenuSettingsGraphicsShadows");
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsShadows")->createButton("enabled", Vec2(0.0f, positions[0]), Vec2(TW("Enabled: NO"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsShadows")->createButton("size", Vec2(0.0f, positions[1]), Vec2(TW("Size"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsShadows")->createButton("position", Vec2(0.0f, positions[2]), Vec2(TW("Position"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Position", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsShadows")->createButton("center", Vec2(0.0f, positions[3]), Vec2(TW("Center"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Center", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsShadows")->createButton("follow", Vec2(0.0f, positions[4]), Vec2(TW("Follow Cam: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Follow Cam: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsShadows")->createButton("lightness", Vec2(0.0f, positions[5]), Vec2(TW("Lightness"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsShadows")->createButton("interval", Vec2(0.0f, positions[6]), Vec2(TW("Interval"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Interval", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsShadows")->createButton("back", Vec2(0.0f, positions[7]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuSettingsGraphicsMotionBlur
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("sceneEditorMenuSettingsGraphicsMotionBlur");
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsMotionBlur")->createButton("enabled", Vec2(0.0f, positions[0]), Vec2(TW("Enabled: NO"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsMotionBlur")->createButton("strength", Vec2(0.0f, positions[1]), Vec2(TW("Strength"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Strength", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsMotionBlur")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuSettingsGraphicsDof
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("sceneEditorMenuSettingsGraphicsDof");
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsDof")->createButton("enabled", Vec2(0.0f, positions[0]), Vec2(TW("Enabled: NO"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsDof")->createButton("dynamic", Vec2(0.0f, positions[1]), Vec2(TW("Dynamic: NO"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Dynamic: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsDof")->createButton("blurDistance", Vec2(0.0f, positions[2]), Vec2(TW("Blur Distance"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blur Distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsDof")->createButton("maxDistance", Vec2(0.0f, positions[3]), Vec2(TW("DOF Distance"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "DOF Distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsDof")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuSettingsGraphicsFog
	positions = VPC::calculateButtonPositions(6, CH);
	leftWindow->createScreen("sceneEditorMenuSettingsGraphicsFog");
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsFog")->createButton("enabled", Vec2(0.0f, positions[0]), Vec2(TW("Enabled: NO"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsFog")->createButton("minDistance", Vec2(0.0f, positions[1]), Vec2(TW("Min Distance"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Min Distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsFog")->createButton("maxDistance", Vec2(0.0f, positions[2]), Vec2(TW("Max Distance"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Max Distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsFog")->createButton("thickness", Vec2(0.0f, positions[3]), Vec2(TW("Thickness"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Thickness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsFog")->createButton("color", Vec2(0.0f, positions[4]), Vec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsFog")->createButton("back", Vec2(0.0f, positions[5]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuSettingsGraphicsLensFlare
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("sceneEditorMenuSettingsGraphicsLensFlare");
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsLensFlare")->createButton("enabled", Vec2(0.0f, positions[0]), Vec2(TW("Enabled: NO"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsLensFlare")->createButton("loadFlareMap", Vec2(0.0f, positions[1]), Vec2(TW("Flare Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Flare Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsLensFlare")->createButton("intensity", Vec2(0.0f, positions[2]), Vec2(TW("Intensity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsLensFlare")->createButton("multiplier", Vec2(0.0f, positions[3]), Vec2(TW("Multiplier"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Multiplier", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsLensFlare")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: sceneEditorMenuSettingsGraphicsSkyExposure
	positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("sceneEditorMenuSettingsGraphicsSkyExposure");
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsSkyExposure")->createButton("enabled", Vec2(0.0f, positions[0]), Vec2(TW("Enabled: NO"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsSkyExposure")->createButton("factor", Vec2(0.0f, positions[1]), Vec2(TW("Factor"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Factor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsSkyExposure")->createButton("speed", Vec2(0.0f, positions[2]), Vec2(TW("Speed"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsSkyExposure")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	
	// Left-viewport: sceneEditorMenuSettingsGraphicsBloom
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("sceneEditorMenuSettingsGraphicsBloom");
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsBloom")->createButton("enabled", Vec2(0.0f, positions[0]), Vec2(TW("Enabled: NO"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: NO", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsBloom")->createButton("type", Vec2(0.0f, positions[1]), Vec2(TW("Type: EVERYTHING"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Type: EVERYTHING", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsBloom")->createButton("intensity", Vec2(0.0f, positions[2]), Vec2(TW("Intensity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsBloom")->createButton("blurs", Vec2(0.0f, positions[3]), Vec2(TW("Blurs"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blurs", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("sceneEditorMenuSettingsGraphicsBloom")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Right-viewport: modelPropertiesMenu
	rightWindow->createScreen("modelPropertiesMenu");
	rightWindow->getScreen("modelPropertiesMenu")->createTextField("title", Vec2(0.0f, 0.95f), Vec2(1.25f, 0.1f), "Model Menu", Vec3(0.0f, 1.0f, 0.0f));
	rightWindow->getScreen("modelPropertiesMenu")->createButton("position", Vec2(0.0f, 0.8f), Vec2(0.75f, 0.2f), "position.png", Vec3(1.0f));
	rightWindow->getScreen("modelPropertiesMenu")->createButton("rotation", Vec2(0.0f, 0.55f), Vec2(0.75f, 0.2f), "rotation.png", Vec3(1.0f));
	rightWindow->getScreen("modelPropertiesMenu")->createButton("size", Vec2(0.0f, 0.3f), Vec2(0.75f, 0.2f), "size.png", Vec3(1.0f));
	rightWindow->getScreen("modelPropertiesMenu")->createTextField("x", Vec2(0.0f, 0.135f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f));
	rightWindow->getScreen("modelPropertiesMenu")->createTextField("y", Vec2(0.0f, -0.115f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f));
	rightWindow->getScreen("modelPropertiesMenu")->createTextField("z", Vec2(0.0f, -0.365f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f));
	rightWindow->getScreen("modelPropertiesMenu")->createButton("xPlus", Vec2(0.75f, 0.025f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen("modelPropertiesMenu")->createButton("yPlus", Vec2(0.75f, -0.225f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen("modelPropertiesMenu")->createButton("zPlus", Vec2(0.75f, -0.475f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen("modelPropertiesMenu")->createButton("xMinus", Vec2(-0.75f, 0.025f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen("modelPropertiesMenu")->createButton("yMinus", Vec2(-0.75f, -0.225f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen("modelPropertiesMenu")->createButton("zMinus", Vec2(-0.75f, -0.475f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen("modelPropertiesMenu")->createWriteField("x", Vec2(0.0f, 0.025f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen("modelPropertiesMenu")->createWriteField("y", Vec2(0.0f, -0.225f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen("modelPropertiesMenu")->createWriteField("z", Vec2(0.0f, -0.475f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("animation", Vec2(0.0f, -0.625f), Vec2(1.5f, 0.1f), Vec3(0.0f, 0.0f, 0.75f), Vec3(0.25f, 0.25f, 1.0f), "Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("freeze", Vec2(0.0f, -0.775f), Vec2(1.0f, 0.1f), Vec3(0.0f, 0.0f, 0.75f), Vec3(0.25f, 0.25f, 1.0f), "Freeze", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("delete", Vec2(0.0f, -0.925f), Vec2(1.0f, 0.1f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Right-viewport: billboardPropertiesMenu
	rightWindow->createScreen("billboardPropertiesMenu");
	rightWindow->getScreen("billboardPropertiesMenu")->createTextField("title", Vec2(0.0f, 0.95f), Vec2(1.75f, 0.1f), "Billboard Menu", Vec3(0.0f, 1.0f, 0.0f));
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("position", Vec2(0.0f, 0.8f), Vec2(0.75f, 0.2f), "position.png", Vec3(1.0f));
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("rotation", Vec2(0.0f, 0.55f), Vec2(0.75f, 0.2f), "rotation.png", Vec3(1.0f));
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("size", Vec2(0.0f, 0.3f), Vec2(0.75f, 0.2f), "size.png", Vec3(1.0f));
	rightWindow->getScreen("billboardPropertiesMenu")->createTextField("x", Vec2(0.0f, 0.135f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f));
	rightWindow->getScreen("billboardPropertiesMenu")->createTextField("y", Vec2(0.0f, -0.115f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f));
	rightWindow->getScreen("billboardPropertiesMenu")->createTextField("z", Vec2(0.0f, -0.365f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f));
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("xPlus", Vec2(0.75f, 0.025f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("yPlus", Vec2(0.75f, -0.225f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("zPlus", Vec2(0.75f, -0.475f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("xMinus", Vec2(-0.75f, 0.025f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("yMinus", Vec2(-0.75f, -0.225f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("zMinus", Vec2(-0.75f, -0.475f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen("billboardPropertiesMenu")->createWriteField("x", Vec2(0.0f, 0.025f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen("billboardPropertiesMenu")->createWriteField("y", Vec2(0.0f, -0.225f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen("billboardPropertiesMenu")->createWriteField("z", Vec2(0.0f, -0.475f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("delete", Vec2(0.0f, -0.625f), Vec2(1.0f, 0.1f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Right-viewport: soundPropertiesMenu
	rightWindow->createScreen("soundPropertiesMenu");
	rightWindow->getScreen("soundPropertiesMenu")->createTextField("title", Vec2(0.0f, 0.95f), Vec2(1.25f, 0.1f), "Sound Menu", Vec3(0.0f, 1.0f, 0.0f));
	rightWindow->getScreen("soundPropertiesMenu")->createTextField("x", Vec2(0.0f, 0.81f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f));
	rightWindow->getScreen("soundPropertiesMenu")->createTextField("y", Vec2(0.0f, 0.56f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f));
	rightWindow->getScreen("soundPropertiesMenu")->createTextField("z", Vec2(0.0f, 0.31f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f));
	rightWindow->getScreen("soundPropertiesMenu")->createButton("xPlus", Vec2(0.75f, 0.7f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen("soundPropertiesMenu")->createButton("yPlus", Vec2(0.75f, 0.45f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen("soundPropertiesMenu")->createButton("zPlus", Vec2(0.75f, 0.2f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen("soundPropertiesMenu")->createButton("xMinus", Vec2(-0.75f, 0.7f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen("soundPropertiesMenu")->createButton("yMinus", Vec2(-0.75f, 0.45f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen("soundPropertiesMenu")->createButton("zMinus", Vec2(-0.75f, 0.2f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen("soundPropertiesMenu")->createWriteField("x", Vec2(0.0f, 0.7f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen("soundPropertiesMenu")->createWriteField("y", Vec2(0.0f, 0.45f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen("soundPropertiesMenu")->createWriteField("z", Vec2(0.0f, 0.2f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen("soundPropertiesMenu")->createTextField("distance", Vec2(0.0f, 0.06f), Vec2(1.5f, 0.1f), "Max distance", Vec3(1.0f));
	rightWindow->getScreen("soundPropertiesMenu")->createButton("distancePlus", Vec2(0.75f, -0.05f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen("soundPropertiesMenu")->createButton("distanceMinus", Vec2(-0.75f, -0.05f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen("soundPropertiesMenu")->createWriteField("distance", Vec2(0.0f, -0.05f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen("soundPropertiesMenu")->createTextField("volume", Vec2(0.0f, -0.19f), Vec2(1.25f, 0.1f), "Max volume", Vec3(1.0f));
	rightWindow->getScreen("soundPropertiesMenu")->createButton("volumePlus", Vec2(0.75f, -0.3f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen("soundPropertiesMenu")->createButton("volumeMinus", Vec2(-0.75f, -0.3f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen("soundPropertiesMenu")->createWriteField("volume", Vec2(0.0f, -0.3f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("delete", Vec2(0.0f, -0.45f), Vec2(1.0f, 0.1f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	
	// Right-viewport: lightPropertiesMenu
	rightWindow->createScreen("lightPropertiesMenu");
	rightWindow->getScreen("lightPropertiesMenu")->createTextField("title", Vec2(0.0f, 0.95f), Vec2(1.25f, 0.1f), "Light Menu", Vec3(0.0f, 1.0f, 0.0f));
	rightWindow->getScreen("lightPropertiesMenu")->createButton("position", Vec2(0.0f, 0.8f), Vec2(0.75f, 0.2f), "position.png", Vec3(1.0f));
	rightWindow->getScreen("lightPropertiesMenu")->createButton("radius", Vec2(0.0f, 0.6f), Vec2(0.75f, 0.2f), "radius.png", Vec3(1.0f));
	rightWindow->getScreen("lightPropertiesMenu")->createButton("color", Vec2(0.0f, 0.4f), Vec2(0.75f, 0.2f), "color.png", Vec3(1.0f));
	rightWindow->getScreen("lightPropertiesMenu")->createTextField("x", Vec2(0.0f, 0.235f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f));
	rightWindow->getScreen("lightPropertiesMenu")->createTextField("y", Vec2(0.0f, 0.01f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f));
	rightWindow->getScreen("lightPropertiesMenu")->createTextField("z", Vec2(0.0f, -0.215f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f));
	rightWindow->getScreen("lightPropertiesMenu")->createButton("xPlus", Vec2(0.75f, 0.125f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen("lightPropertiesMenu")->createButton("yPlus", Vec2(0.75f, -0.1f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen("lightPropertiesMenu")->createButton("zPlus", Vec2(0.75f, -0.325f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen("lightPropertiesMenu")->createButton("xMinus", Vec2(-0.75f, 0.125f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen("lightPropertiesMenu")->createButton("yMinus", Vec2(-0.75f, -0.1f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen("lightPropertiesMenu")->createButton("zMinus", Vec2(-0.75f, -0.325f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen("lightPropertiesMenu")->createWriteField("x", Vec2(0.0f, 0.125f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen("lightPropertiesMenu")->createWriteField("y", Vec2(0.0f, -0.1f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen("lightPropertiesMenu")->createWriteField("z", Vec2(0.0f, -0.325f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen("lightPropertiesMenu")->createTextField("intensity", Vec2(0.0f, -0.44f), Vec2(1.125f, 0.1f), "Intensity", Vec3(1.0f));
	rightWindow->getScreen("lightPropertiesMenu")->createButton("intensityPlus", Vec2(0.75f, -0.55f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f));
	rightWindow->getScreen("lightPropertiesMenu")->createButton("intensityMinus", Vec2(-0.75f, -0.55f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f));
	rightWindow->getScreen("lightPropertiesMenu")->createWriteField("intensity", Vec2(0.0f, -0.55f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1);
	rightWindow->getScreen("lightPropertiesMenu")->createButton("shape", Vec2(0.0f, -0.725f), Vec2(0.75f, 0.2f), "shape_circle.png", Vec3(1.0f));
	rightWindow->getScreen("lightPropertiesMenu")->createButton("delete", Vec2(0.0f, -0.9f), Vec2(1.0f, 0.1f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void SceneEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuSky");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuTerrain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuWater");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuModel");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuModelPlace");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuModelChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuBillboard");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuBillboardPlace");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuBillboardChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuLight");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuSound");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuSoundPlace");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuSoundChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuSettings");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuSettingsLighting");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuSettingsLightingAmbient");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuSettingsLightingDirectional");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuSettingsGraphics");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuSettingsGraphicsShadows");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuSettingsGraphicsMotionBlur");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuSettingsGraphicsDof");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuSettingsGraphicsFog");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuSettingsGraphicsLensFlare");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuSettingsGraphicsSkyExposure");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("sceneEditorMenuSettingsGraphicsBloom");
	_gui.getViewport("right")->getWindow("main")->deleteScreen("modelPropertiesMenu");
	_gui.getViewport("right")->getWindow("main")->deleteScreen("billboardPropertiesMenu");
	_gui.getViewport("right")->getWindow("main")->deleteScreen("lightPropertiesMenu");
	_gui.getViewport("right")->getWindow("main")->deleteScreen("soundPropertiesMenu");
}