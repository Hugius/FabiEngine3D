#include "world_editor.hpp"
#include "left_viewport_controller.hpp"

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

#define TW(text) VPC::calculateTextWidth(text, CW)

void WorldEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	// Left-viewport: worldEditorMenuMain
	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("worldEditorMenuMain");
	leftWindow->getScreen("worldEditorMenuMain")->createButton("create", Vec2(0.0f, positions[0]), Vec2(TW("Create World"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create World", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuMain")->createButton("edit", Vec2(0.0f, positions[1]), Vec2(TW("Edit World"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit World", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuMain")->createButton("delete", Vec2(0.0f, positions[2]), Vec2(TW("Delete World"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete World", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuMain")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuChoice
	positions = VPC::calculateButtonPositions(11, CH);
	leftWindow->createScreen("worldEditorMenuChoice");
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("sky", Vec2(0.0f, positions[0]), Vec2(TW("Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("terrain", Vec2(0.0f, positions[1]), Vec2(TW("Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("water", Vec2(0.0f, positions[2]), Vec2(TW("Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("models", Vec2(0.0f, positions[3]), Vec2(TW("Models"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Models", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("billboards", Vec2(0.0f, positions[4]), Vec2(TW("Billboards"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Billboards", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("sounds", Vec2(0.0f, positions[5]), Vec2(TW("Sounds"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sounds", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("pointlights", Vec2(0.0f, positions[6]), Vec2(TW("Pointlights"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Pointlights", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("spotlights", Vec2(0.0f, positions[7]), Vec2(TW("Spotlights"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spotlights", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("reflections", Vec2(0.0f, positions[8]), Vec2(TW("Reflections"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflections", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("settings", Vec2(0.0f, positions[9]), Vec2(TW("Settings"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Settings", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("back", Vec2(0.0f, positions[10]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuSky
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuSky");
	leftWindow->getScreen("worldEditorMenuSky")->createButton("choose", Vec2(0.0f, positions[0]), Vec2(TW("Choose Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSky")->createButton("delete", Vec2(0.0f, positions[1]), Vec2(TW("Delete Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSky")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuTerrain
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuTerrain");
	leftWindow->getScreen("worldEditorMenuTerrain")->createButton("choose", Vec2(0.0f, positions[0]), Vec2(TW("Choose Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuTerrain")->createButton("delete", Vec2(0.0f, positions[1]), Vec2(TW("Delete Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuTerrain")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuWater
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("worldEditorMenuWater");
	leftWindow->getScreen("worldEditorMenuWater")->createButton("choose", Vec2(0.0f, positions[0]), Vec2(TW("Choose Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuWater")->createButton("delete", Vec2(0.0f, positions[1]), Vec2(TW("Delete Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuWater")->createButton("up", Vec2(0.0f, positions[2]), Vec2(TW("Move Up"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Move Up", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuWater")->createButton("down", Vec2(0.0f, positions[3]), Vec2(TW("Move Down"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Move Down", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuWater")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuModel
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuModel");
	leftWindow->getScreen("worldEditorMenuModel")->createButton("place", Vec2(0.0f, positions[0]), Vec2(TW("Place Model"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Place Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuModel")->createButton("choice", Vec2(0.0f, positions[1]), Vec2(TW("Choose Model"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuModel")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuModelPlace
	leftWindow->createScreen("worldEditorMenuModelPlace");
	leftWindow->getScreen("worldEditorMenuModelPlace")->createScrollingList("modelList", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuModelPlace")->createButton("back", Vec2(0.0f, -0.9f), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuModelChoice
	leftWindow->createScreen("worldEditorMenuModelChoice");
	leftWindow->getScreen("worldEditorMenuModelChoice")->createScrollingList("modelList", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuModelChoice")->createButton("back", Vec2(0.0f, -0.9f), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuBillboard
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuBillboard");
	leftWindow->getScreen("worldEditorMenuBillboard")->createButton("place", Vec2(0.0f, positions[0]), Vec2(TW("Place Billboard"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Place Billboard", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuBillboard")->createButton("choice", Vec2(0.0f, positions[1]), Vec2(TW("Choose Billboard"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Billboard", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuBillboard")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuBillboardPlace
	leftWindow->createScreen("worldEditorMenuBillboardPlace");
	leftWindow->getScreen("worldEditorMenuBillboardPlace")->createScrollingList("billboardList", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuBillboardPlace")->createButton("back", Vec2(0.0f, -0.9f), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuBillboardChoice
	leftWindow->createScreen("worldEditorMenuBillboardChoice");
	leftWindow->getScreen("worldEditorMenuBillboardChoice")->createScrollingList("billboardList", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuBillboardChoice")->createButton("back", Vec2(0.0f, -0.9f), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuSound
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuSound");
	leftWindow->getScreen("worldEditorMenuSound")->createButton("place", Vec2(0.0f, positions[0]), Vec2(TW("Place Sound"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Place Sound", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSound")->createButton("choice", Vec2(0.0f, positions[1]), Vec2(TW("Choose Sound"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Sound", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSound")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuSoundPlace
	leftWindow->createScreen("worldEditorMenuSoundPlace");
	leftWindow->getScreen("worldEditorMenuSoundPlace")->createScrollingList("sounds", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuSoundPlace")->createButton("back", Vec2(0.0f, -0.9f), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuSoundChoice
	leftWindow->createScreen("worldEditorMenuSoundChoice");
	leftWindow->getScreen("worldEditorMenuSoundChoice")->createScrollingList("sounds", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuSoundChoice")->createButton("back", Vec2(0.0f, -0.9f), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuPointlight
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuPointlight");
	leftWindow->getScreen("worldEditorMenuPointlight")->createButton("place", Vec2(0.0f, positions[0]), Vec2(TW("Place Pointlight"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Place Pointlight", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuPointlight")->createButton("choice", Vec2(0.0f, positions[1]), Vec2(TW("Choose Pointlight"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Pointlight", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuPointlight")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuPointlightChoice
	leftWindow->createScreen("worldEditorMenuPointlightChoice");
	leftWindow->getScreen("worldEditorMenuPointlightChoice")->createScrollingList("pointlights", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuPointlightChoice")->createButton("back", Vec2(0.0f, -0.9f), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuSpotlight
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuSpotlight");
	leftWindow->getScreen("worldEditorMenuSpotlight")->createButton("place", Vec2(0.0f, positions[0]), Vec2(TW("Place Spotlight"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Place Spotlight", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSpotlight")->createButton("choice", Vec2(0.0f, positions[1]), Vec2(TW("Choose Spotlight"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Spotlight", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSpotlight")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuSpotlightChoice
	leftWindow->createScreen("worldEditorMenuSpotlightChoice");
	leftWindow->getScreen("worldEditorMenuSpotlightChoice")->createScrollingList("spotlights", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuSpotlightChoice")->createButton("back", Vec2(0.0f, -0.9f), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuReflection
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuReflection");
	leftWindow->getScreen("worldEditorMenuReflection")->createButton("place", Vec2(0.0f, positions[0]), Vec2(TW("Place Reflection"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Place Reflection", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuReflection")->createButton("choice", Vec2(0.0f, positions[1]), Vec2(TW("Choose Reflection"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Reflection", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuReflection")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuReflectionChoice
	leftWindow->createScreen("worldEditorMenuReflectionChoice");
	leftWindow->getScreen("worldEditorMenuReflectionChoice")->createScrollingList("reflections", Vec2(0.0f, 0.1f), Vec2(1.8f, 1.75f), LVPC::SCROLLING_LIST_COLOR, LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, Vec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuReflectionChoice")->createButton("back", Vec2(0.0f, -0.9f), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuSettings
	positions = VPC::calculateButtonPositions(6, CH);
	leftWindow->createScreen("worldEditorMenuSettings");
	leftWindow->getScreen("worldEditorMenuSettings")->createButton("lighting", Vec2(0.0f, positions[0]), Vec2(TW("Lighting"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lighting", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettings")->createButton("graphics", Vec2(0.0f, positions[1]), Vec2(TW("Graphics"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Graphics", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettings")->createButton("editorSpeed", Vec2(0.0f, positions[2]), Vec2(TW("Editor Speed"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Editor Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettings")->createButton("lodDistance", Vec2(0.0f, positions[3]), Vec2(TW("LOD Distance"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "LOD Distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettings")->createButton("planarHeight", Vec2(0.0f, positions[4]), Vec2(TW("Planar Height"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Planar Height", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettings")->createButton("back", Vec2(0.0f, positions[5]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuSettingsLighting
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuSettingsLighting");
	leftWindow->getScreen("worldEditorMenuSettingsLighting")->createButton("ambient", Vec2(0.0f, positions[0]), Vec2(TW("Ambient"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Ambient", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsLighting")->createButton("directional", Vec2(0.0f, positions[1]), Vec2(TW("Directional"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Directional", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsLighting")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuSettingsLightingAmbient
	positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("worldEditorMenuSettingsLightingAmbient");
	leftWindow->getScreen("worldEditorMenuSettingsLightingAmbient")->createButton("isEnabled", Vec2(0.0f, positions[0]), Vec2(TW("Enabled: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsLightingAmbient")->createButton("color", Vec2(0.0f, positions[1]), Vec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsLightingAmbient")->createButton("intensity", Vec2(0.0f, positions[2]), Vec2(TW("Intensity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsLightingAmbient")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuSettingsLightingDirectional
	positions = VPC::calculateButtonPositions(6, CH);
	leftWindow->createScreen("worldEditorMenuSettingsLightingDirectional");
	leftWindow->getScreen("worldEditorMenuSettingsLightingDirectional")->createButton("isEnabled", Vec2(0.0f, positions[0]), Vec2(TW("Enabled: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsLightingDirectional")->createButton("position", Vec2(0.0f, positions[2]), Vec2(TW("Position"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Position", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsLightingDirectional")->createButton("color", Vec2(0.0f, positions[1]), Vec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsLightingDirectional")->createButton("intensity", Vec2(0.0f, positions[2]), Vec2(TW("Intensity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsLightingDirectional")->createButton("billboardSize", Vec2(0.0f, positions[3]), Vec2(TW("Billboard Size"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Billboard Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsLightingDirectional")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuSettingsGraphics
	positions = VPC::calculateButtonPositions(8, CH);
	leftWindow->createScreen("worldEditorMenuSettingsGraphics");
	leftWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("shadows", Vec2(0.0f, positions[0]), Vec2(TW("Shadows"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Shadows", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("motionBlur", Vec2(0.0f, positions[1]), Vec2(TW("Motion Blur"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Motion Blur", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("dof", Vec2(0.0f, positions[2]), Vec2(TW("Depth Of Field"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Depth Of Field", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("fog", Vec2(0.0f, positions[3]), Vec2(TW("Fog"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Fog", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("lensFlare", Vec2(0.0f, positions[4]), Vec2(TW("Lens Flare"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lens Flare", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("skyExposure", Vec2(0.0f, positions[5]), Vec2(TW("Sky Exposure"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sky Exposure", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("bloom", Vec2(0.0f, positions[6]), Vec2(TW("Bloom"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Bloom", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("back", Vec2(0.0f, positions[7]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuSettingsGraphicsShadows
	positions = VPC::calculateButtonPositions(8, CH);
	leftWindow->createScreen("worldEditorMenuSettingsGraphicsShadows");
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("isEnabled", Vec2(0.0f, positions[0]), Vec2(TW("Enabled: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("position", Vec2(0.0f, positions[1]), Vec2(TW("Position"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Position", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("center", Vec2(0.0f, positions[2]), Vec2(TW("Center"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Center", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("size", Vec2(0.0f, positions[3]), Vec2(TW("Size"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("lightness", Vec2(0.0f, positions[4]), Vec2(TW("Lightness"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("follow", Vec2(0.0f, positions[5]), Vec2(TW("Follow Cam: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Follow Cam: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("interval", Vec2(0.0f, positions[6]), Vec2(TW("Interval"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Interval", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("back", Vec2(0.0f, positions[7]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuSettingsGraphicsMotionBlur
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuSettingsGraphicsMotionBlur");
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsMotionBlur")->createButton("isEnabled", Vec2(0.0f, positions[0]), Vec2(TW("Enabled: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsMotionBlur")->createButton("sensitivity", Vec2(0.0f, positions[1]), Vec2(TW("Sensitivity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sensitivity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsMotionBlur")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuSettingsGraphicsDof
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("worldEditorMenuSettingsGraphicsDof");
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsDof")->createButton("isEnabled", Vec2(0.0f, positions[0]), Vec2(TW("Enabled: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsDof")->createButton("isDynamic", Vec2(0.0f, positions[1]), Vec2(TW("Dynamic: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Dynamic: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsDof")->createButton("blurDistance", Vec2(0.0f, positions[2]), Vec2(TW("Blur Distance"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blur Distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsDof")->createButton("dynamicDistance", Vec2(0.0f, positions[3]), Vec2(TW("Dynamic Distance"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Dynamic Distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsDof")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuSettingsGraphicsFog
	positions = VPC::calculateButtonPositions(6, CH);
	leftWindow->createScreen("worldEditorMenuSettingsGraphicsFog");
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsFog")->createButton("isEnabled", Vec2(0.0f, positions[0]), Vec2(TW("Enabled: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsFog")->createButton("minDistance", Vec2(0.0f, positions[1]), Vec2(TW("Min Distance"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Min Distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsFog")->createButton("maxDistance", Vec2(0.0f, positions[2]), Vec2(TW("Max Distance"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Max Distance", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsFog")->createButton("thickness", Vec2(0.0f, positions[3]), Vec2(TW("Thickness"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Thickness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsFog")->createButton("color", Vec2(0.0f, positions[4]), Vec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsFog")->createButton("back", Vec2(0.0f, positions[5]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuSettingsGraphicsLensFlare
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("worldEditorMenuSettingsGraphicsLensFlare");
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsLensFlare")->createButton("isEnabled", Vec2(0.0f, positions[0]), Vec2(TW("Enabled: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsLensFlare")->createButton("flareMap", Vec2(0.0f, positions[1]), Vec2(TW("Flare Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Flare Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsLensFlare")->createButton("intensity", Vec2(0.0f, positions[2]), Vec2(TW("Intensity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsLensFlare")->createButton("sensitivity", Vec2(0.0f, positions[3]), Vec2(TW("Sensitivity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sensitivity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsLensFlare")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuSettingsGraphicsSkyExposure
	positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("worldEditorMenuSettingsGraphicsSkyExposure");
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsSkyExposure")->createButton("isEnabled", Vec2(0.0f, positions[0]), Vec2(TW("Enabled: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsSkyExposure")->createButton("intensity", Vec2(0.0f, positions[1]), Vec2(TW("Intensity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsSkyExposure")->createButton("speed", Vec2(0.0f, positions[2]), Vec2(TW("Speed"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsSkyExposure")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: worldEditorMenuSettingsGraphicsBloom
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("worldEditorMenuSettingsGraphicsBloom");
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsBloom")->createButton("isEnabled", Vec2(0.0f, positions[0]), Vec2(TW("Enabled: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Enabled: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsBloom")->createButton("type", Vec2(0.0f, positions[1]), Vec2(TW("Type: EVERYTHING"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Type: EVERYTHING", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsBloom")->createButton("intensity", Vec2(0.0f, positions[2]), Vec2(TW("Intensity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsBloom")->createButton("blurs", Vec2(0.0f, positions[3]), Vec2(TW("Blurs"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blurs", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsBloom")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Right-viewport: modelPropertiesMenu
	rightWindow->createScreen("modelPropertiesMenu");
	rightWindow->getScreen("modelPropertiesMenu")->createTextField("title", Vec2(0.0f, 0.95f), Vec2(1.25f, 0.1f), "Model Menu", Vec3(0.0f, 1.0f, 0.0f), true, false);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("position", Vec2(0.0f, 0.8f), Vec2(0.75f, 0.2f), "position.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("rotation", Vec2(0.0f, 0.55f), Vec2(0.75f, 0.2f), "rotation.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("size", Vec2(0.0f, 0.3f), Vec2(0.75f, 0.2f), "size.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("modelPropertiesMenu")->createTextField("x", Vec2(0.0f, 0.135f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f), true, false);
	rightWindow->getScreen("modelPropertiesMenu")->createTextField("y", Vec2(0.0f, -0.115f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f), true, false);
	rightWindow->getScreen("modelPropertiesMenu")->createTextField("z", Vec2(0.0f, -0.365f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f), true, false);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("xPlus", Vec2(0.75f, 0.025f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("yPlus", Vec2(0.75f, -0.225f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("zPlus", Vec2(0.75f, -0.475f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("xMinus", Vec2(-0.75f, 0.025f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("yMinus", Vec2(-0.75f, -0.225f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("zMinus", Vec2(-0.75f, -0.475f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("modelPropertiesMenu")->createWriteField("x", Vec2(0.0f, 0.025f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("modelPropertiesMenu")->createWriteField("y", Vec2(0.0f, -0.225f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("modelPropertiesMenu")->createWriteField("z", Vec2(0.0f, -0.475f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("animation", Vec2(0.0f, -0.625f), Vec2(1.5f, 0.1f), Vec3(0.0f, 0.0f, 0.75f), Vec3(0.25f, 0.25f, 1.0f), "Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("freeze", Vec2(0.0f, -0.775f), Vec2(1.0f, 0.1f), Vec3(0.0f, 0.0f, 0.75f), Vec3(0.25f, 0.25f, 1.0f), "Freeze", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("delete", Vec2(0.0f, -0.925f), Vec2(1.0f, 0.1f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Right-viewport: billboardPropertiesMenu
	rightWindow->createScreen("billboardPropertiesMenu");
	rightWindow->getScreen("billboardPropertiesMenu")->createTextField("title", Vec2(0.0f, 0.95f), Vec2(1.75f, 0.1f), "Billboard Menu", Vec3(0.0f, 1.0f, 0.0f), true, false);
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("position", Vec2(0.0f, 0.8f), Vec2(0.75f, 0.2f), "position.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("rotation", Vec2(0.0f, 0.55f), Vec2(0.75f, 0.2f), "rotation.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("size", Vec2(0.0f, 0.3f), Vec2(0.75f, 0.2f), "size.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("billboardPropertiesMenu")->createTextField("x", Vec2(0.0f, 0.135f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f), true, false);
	rightWindow->getScreen("billboardPropertiesMenu")->createTextField("y", Vec2(0.0f, -0.115f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f), true, false);
	rightWindow->getScreen("billboardPropertiesMenu")->createTextField("z", Vec2(0.0f, -0.365f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f), true, false);
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("xPlus", Vec2(0.75f, 0.025f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("yPlus", Vec2(0.75f, -0.225f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("zPlus", Vec2(0.75f, -0.475f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("xMinus", Vec2(-0.75f, 0.025f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("yMinus", Vec2(-0.75f, -0.225f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("zMinus", Vec2(-0.75f, -0.475f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("billboardPropertiesMenu")->createWriteField("x", Vec2(0.0f, 0.025f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("billboardPropertiesMenu")->createWriteField("y", Vec2(0.0f, -0.225f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("billboardPropertiesMenu")->createWriteField("z", Vec2(0.0f, -0.475f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("billboardPropertiesMenu")->createButton("delete", Vec2(0.0f, -0.625f), Vec2(1.0f, 0.1f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Right-viewport: soundPropertiesMenu
	rightWindow->createScreen("soundPropertiesMenu");
	rightWindow->getScreen("soundPropertiesMenu")->createTextField("title", Vec2(0.0f, 0.95f), Vec2(1.25f, 0.1f), "Sound Menu", Vec3(0.0f, 1.0f, 0.0f), true, false);
	rightWindow->getScreen("soundPropertiesMenu")->createTextField("x", Vec2(0.0f, 0.81f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f), true, false);
	rightWindow->getScreen("soundPropertiesMenu")->createTextField("y", Vec2(0.0f, 0.56f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f), true, false);
	rightWindow->getScreen("soundPropertiesMenu")->createTextField("z", Vec2(0.0f, 0.31f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f), true, false);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("xPlus", Vec2(0.75f, 0.7f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("yPlus", Vec2(0.75f, 0.45f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("zPlus", Vec2(0.75f, 0.2f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("xMinus", Vec2(-0.75f, 0.7f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("yMinus", Vec2(-0.75f, 0.45f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("zMinus", Vec2(-0.75f, 0.2f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("soundPropertiesMenu")->createWriteField("x", Vec2(0.0f, 0.7f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("soundPropertiesMenu")->createWriteField("y", Vec2(0.0f, 0.45f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("soundPropertiesMenu")->createWriteField("z", Vec2(0.0f, 0.2f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("soundPropertiesMenu")->createTextField("distance", Vec2(0.0f, 0.06f), Vec2(1.5f, 0.1f), "Max distance", Vec3(1.0f), true, false);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("distancePlus", Vec2(0.75f, -0.05f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("distanceMinus", Vec2(-0.75f, -0.05f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("soundPropertiesMenu")->createWriteField("distance", Vec2(0.0f, -0.05f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("soundPropertiesMenu")->createTextField("volume", Vec2(0.0f, -0.19f), Vec2(1.25f, 0.1f), "Max volume", Vec3(1.0f), true, false);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("volumePlus", Vec2(0.75f, -0.3f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("volumeMinus", Vec2(-0.75f, -0.3f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("soundPropertiesMenu")->createWriteField("volume", Vec2(0.0f, -0.3f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("delete", Vec2(0.0f, -0.45f), Vec2(1.0f, 0.1f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Right-viewport: pointlightPropertiesMenu
	rightWindow->createScreen("pointlightPropertiesMenu");
	rightWindow->getScreen("pointlightPropertiesMenu")->createTextField("title", Vec2(0.0f, 0.95f), Vec2(1.875f, 0.1f), "Pointlight Menu", Vec3(0.0f, 1.0f, 0.0f), true, false);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("position", Vec2(0.0f, 0.8f), Vec2(0.75f, 0.2f), "position.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("radius", Vec2(0.0f, 0.6f), Vec2(0.75f, 0.2f), "radius.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("color", Vec2(0.0f, 0.4f), Vec2(0.75f, 0.2f), "color.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createTextField("x", Vec2(0.0f, 0.235f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f), true, false);
	rightWindow->getScreen("pointlightPropertiesMenu")->createTextField("y", Vec2(0.0f, 0.01f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f), true, false);
	rightWindow->getScreen("pointlightPropertiesMenu")->createTextField("z", Vec2(0.0f, -0.215f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f), true, false);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("xPlus", Vec2(0.75f, 0.125f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("yPlus", Vec2(0.75f, -0.1f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("zPlus", Vec2(0.75f, -0.325f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("xMinus", Vec2(-0.75f, 0.125f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("yMinus", Vec2(-0.75f, -0.1f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("zMinus", Vec2(-0.75f, -0.325f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createWriteField("x", Vec2(0.0f, 0.125f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createWriteField("y", Vec2(0.0f, -0.1f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createWriteField("z", Vec2(0.0f, -0.325f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createTextField("intensity", Vec2(0.0f, -0.44f), Vec2(1.125f, 0.1f), "Intensity", Vec3(1.0f), true, false);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("intensityPlus", Vec2(0.75f, -0.55f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("intensityMinus", Vec2(-0.75f, -0.55f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createWriteField("intensity", Vec2(0.0f, -0.55f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("shape", Vec2(0.0f, -0.725f), Vec2(0.75f, 0.2f), "shape_circle.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("delete", Vec2(0.0f, -0.91f), Vec2(1.0f, 0.1f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Right-viewport: spotlightPropertiesMenu
	rightWindow->createScreen("spotlightPropertiesMenu");
	rightWindow->getScreen("spotlightPropertiesMenu")->createTextField("title", Vec2(0.0f, 0.95f), Vec2(1.75f, 0.1f), "Spotlight Menu", Vec3(0.0f, 1.0f, 0.0f), true, false);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("position", Vec2(-0.5f, 0.8f), Vec2(0.75f, 0.2f), "position.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("color", Vec2(0.5f, 0.8f), Vec2(0.75f, 0.2f), "color.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createTextField("x", Vec2(0.0f, 0.725f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f), true, false);
	rightWindow->getScreen("spotlightPropertiesMenu")->createTextField("y", Vec2(0.0f, 0.525f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f), true, false);
	rightWindow->getScreen("spotlightPropertiesMenu")->createTextField("z", Vec2(0.0f, 0.325f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f), true, false);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("xPlus", Vec2(0.75f, 0.625f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("yPlus", Vec2(0.75f, 0.425f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("zPlus", Vec2(0.75f, 0.225f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("xMinus", Vec2(-0.75f, 0.625f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("yMinus", Vec2(-0.75f, 0.425f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("zMinus", Vec2(-0.75f, 0.225f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createWriteField("x", Vec2(0.0f, 0.625f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createWriteField("y", Vec2(0.0f, 0.425f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createWriteField("z", Vec2(0.0f, 0.225f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createTextField("yaw", Vec2(0.0f, 0.125f), Vec2(0.375f, 0.1f), "Yaw", Vec3(1.0f), true, false);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("yawPlus", Vec2(0.75f, 0.025f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("yawMinus", Vec2(-0.75f, 0.025f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createWriteField("yaw", Vec2(0.0f, 0.025f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createTextField("pitch", Vec2(0.0f, -0.075f), Vec2(0.625f, 0.1f), "Pitch", Vec3(1.0f), true, false);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("pitchPlus", Vec2(0.75f, -0.175f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("pitchMinus", Vec2(-0.75f, -0.175f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createWriteField("pitch", Vec2(0.0f, -0.175f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createTextField("intensity", Vec2(0.0f, -0.275f), Vec2(1.125f, 0.1f), "Intensity", Vec3(1.0f), true, false);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("intensityPlus", Vec2(0.75f, -0.375f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("intensityMinus", Vec2(-0.75f, -0.375f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createWriteField("intensity", Vec2(0.0f, -0.375f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createTextField("angle", Vec2(0.0f, -0.475f), Vec2(0.625f, 0.1f), "Angle", Vec3(1.0f), true, false);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("anglePlus", Vec2(0.75f, -0.575f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("angleMinus", Vec2(-0.75f, -0.575f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createWriteField("angle", Vec2(0.0f, -0.575f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createTextField("distance", Vec2(0.0f, -0.675f), Vec2(1.0f, 0.1f), "Distance", Vec3(1.0f), true, false);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("distancePlus", Vec2(0.75f, -0.775f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("distanceMinus", Vec2(-0.75f, -0.775f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createWriteField("distance", Vec2(0.0f, -0.775f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("delete", Vec2(0.0f, -0.915f), Vec2(1.0f, 0.1f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Right-viewport: reflectionPropertiesMenu
	rightWindow->createScreen("reflectionPropertiesMenu");
	rightWindow->getScreen("reflectionPropertiesMenu")->createTextField("title", Vec2(0.0f, 0.95f), Vec2(1.875f, 0.1f), "Reflection Menu", Vec3(0.0f, 1.0f, 0.0f), true, false);
	rightWindow->getScreen("reflectionPropertiesMenu")->createTextField("x", Vec2(0.0f, 0.81f), Vec2(0.25f, 0.1f), "X", Vec3(1.0f), true, false);
	rightWindow->getScreen("reflectionPropertiesMenu")->createTextField("y", Vec2(0.0f, 0.56f), Vec2(0.25f, 0.1f), "Y", Vec3(1.0f), true, false);
	rightWindow->getScreen("reflectionPropertiesMenu")->createTextField("z", Vec2(0.0f, 0.31f), Vec2(0.25f, 0.1f), "Z", Vec3(1.0f), true, false);
	rightWindow->getScreen("reflectionPropertiesMenu")->createButton("xPlus", Vec2(0.75f, 0.7f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createButton("yPlus", Vec2(0.75f, 0.45f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createButton("zPlus", Vec2(0.75f, 0.2f), Vec2(0.5f, 0.15f), "plus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createButton("xMinus", Vec2(-0.75f, 0.7f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createButton("yMinus", Vec2(-0.75f, 0.45f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createButton("zMinus", Vec2(-0.75f, 0.2f), Vec2(0.5f, 0.15f), "minus.png", Vec3(1.0f), true, true, true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createWriteField("x", Vec2(0.0f, 0.7f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createWriteField("y", Vec2(0.0f, 0.45f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createWriteField("z", Vec2(0.0f, 0.2f), Vec2(1.0f, 0.1f), Vec3(0.25f), Vec3(0.75f), Vec3(1.0f), Vec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createButton("capture", Vec2(0.0f, 0.05f), Vec2(1.0f, 0.1f), Vec3(0.0f, 0.0f, 0.75f), Vec3(0.25f, 0.25f, 1.0f), "Capture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createButton("delete", Vec2(0.0f, -0.1f), Vec2(1.0f, 0.1f), Vec3(0.75f, 0.0f, 0.0f), Vec3(1.0f, 0.25f, 0.25f), "Delete", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
}

void WorldEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuSky");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuTerrain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuWater");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuModel");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuModelPlace");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuModelChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuBillboard");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuBillboardPlace");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuBillboardChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuSound");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuSoundPlace");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuSoundChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuPointlight");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuPointlightChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuSpotlight");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuSpotlightChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuReflection");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuReflectionChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuSettings");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuSettingsLighting");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuSettingsLightingAmbient");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuSettingsLightingDirectional");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuSettingsGraphics");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuSettingsGraphicsShadows");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuSettingsGraphicsMotionBlur");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuSettingsGraphicsDof");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuSettingsGraphicsFog");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuSettingsGraphicsLensFlare");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuSettingsGraphicsSkyExposure");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("worldEditorMenuSettingsGraphicsBloom");
	_gui.getViewport("right")->getWindow("main")->deleteScreen("modelPropertiesMenu");
	_gui.getViewport("right")->getWindow("main")->deleteScreen("billboardPropertiesMenu");
	_gui.getViewport("right")->getWindow("main")->deleteScreen("soundPropertiesMenu");
	_gui.getViewport("right")->getWindow("main")->deleteScreen("pointlightPropertiesMenu");
	_gui.getViewport("right")->getWindow("main")->deleteScreen("spotlightPropertiesMenu");
	_gui.getViewport("right")->getWindow("main")->deleteScreen("reflectionPropertiesMenu");
}