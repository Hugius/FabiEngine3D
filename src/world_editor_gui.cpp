#define TW(text) (static_cast<float>(string(text).size()) * CW)

#include "world_editor.hpp"
#include "left_viewport_controller.hpp"
#include "tools.hpp"

void WorldEditor::_loadGUI()
{
	auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	auto rightWindow = _gui->getRightViewport()->getWindow("main");

	auto positions = Math::calculateDistributedPositions(4, CH);
	leftWindow->createScreen("worldEditorMenuMain");
	leftWindow->getScreen("worldEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create World"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create World", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit World"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit World", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete World"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete World", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(12, CH);
	leftWindow->createScreen("worldEditorMenuChoice");
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("sky", fvec2(0.0f, positions[0]), fvec2(TW("Sky"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("terrain", fvec2(0.0f, positions[1]), fvec2(TW("Terrain"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Terrain", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("water", fvec2(0.0f, positions[2]), fvec2(TW("Water"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Water", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("model", fvec2(0.0f, positions[3]), fvec2(TW("Model"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("quad3d", fvec2(0.0f, positions[4]), fvec2(TW("Quad3d"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Quad3d", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("text3d", fvec2(0.0f, positions[5]), fvec2(TW("Text3d"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Text3d", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("pointlight", fvec2(0.0f, positions[6]), fvec2(TW("Pointlight"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Pointlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("spotlight", fvec2(0.0f, positions[7]), fvec2(TW("Spotlight"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Spotlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("reflection", fvec2(0.0f, positions[8]), fvec2(TW("Reflection"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Reflection", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("sound", fvec2(0.0f, positions[9]), fvec2(TW("Sound"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Sound", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("settings", fvec2(0.0f, positions[10]), fvec2(TW("Settings"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Settings", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[11]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuSky");
	leftWindow->getScreen("worldEditorMenuSky")->createButton("choose", fvec2(0.0f, positions[0]), fvec2(TW("Choose Sky"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Choose Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSky")->createButton("delete", fvec2(0.0f, positions[1]), fvec2(TW("Delete Sky"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSky")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuTerrain");
	leftWindow->getScreen("worldEditorMenuTerrain")->createButton("choose", fvec2(0.0f, positions[0]), fvec2(TW("Choose Terrain"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Choose Terrain", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuTerrain")->createButton("delete", fvec2(0.0f, positions[1]), fvec2(TW("Delete Terrain"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Terrain", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuTerrain")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(5, CH);
	leftWindow->createScreen("worldEditorMenuWater");
	leftWindow->getScreen("worldEditorMenuWater")->createButton("choose", fvec2(0.0f, positions[0]), fvec2(TW("Choose Water"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Choose Water", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuWater")->createButton("delete", fvec2(0.0f, positions[1]), fvec2(TW("Delete Water"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Water", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuWater")->createButton("up", fvec2(0.0f, positions[2]), fvec2(TW("Move Up"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Move Up", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuWater")->createButton("down", fvec2(0.0f, positions[3]), fvec2(TW("Move Down"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Move Down", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuWater")->createButton("back", fvec2(0.0f, positions[4]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuModel");
	leftWindow->getScreen("worldEditorMenuModel")->createButton("place", fvec2(0.0f, positions[0]), fvec2(TW("Place Model"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Place Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuModel")->createButton("choice", fvec2(0.0f, positions[1]), fvec2(TW("Choose Model"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Choose Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuModel")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("worldEditorMenuModelPlace");
	leftWindow->getScreen("worldEditorMenuModelPlace")->createScrollingList("modelList", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuModelPlace")->createButton("back", fvec2(0.0f, -0.9f), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("worldEditorMenuModelChoice");
	leftWindow->getScreen("worldEditorMenuModelChoice")->createScrollingList("modelList", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuModelChoice")->createButton("back", fvec2(0.0f, -0.9f), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuQuad3d");
	leftWindow->getScreen("worldEditorMenuQuad3d")->createButton("place", fvec2(0.0f, positions[0]), fvec2(TW("Place Quad3D"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Place Quad3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuQuad3d")->createButton("choice", fvec2(0.0f, positions[1]), fvec2(TW("Choose Quad3D"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Choose Quad3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuQuad3d")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("worldEditorMenuQuad3dPlace");
	leftWindow->getScreen("worldEditorMenuQuad3dPlace")->createScrollingList("quad3dList", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuQuad3dPlace")->createButton("back", fvec2(0.0f, -0.9f), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("worldEditorMenuQuad3dChoice");
	leftWindow->getScreen("worldEditorMenuQuad3dChoice")->createScrollingList("quad3dList", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuQuad3dChoice")->createButton("back", fvec2(0.0f, -0.9f), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuText3d");
	leftWindow->getScreen("worldEditorMenuText3d")->createButton("place", fvec2(0.0f, positions[0]), fvec2(TW("Place Text3D"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Place Text3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuText3d")->createButton("choice", fvec2(0.0f, positions[1]), fvec2(TW("Choose Text3D"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Choose Text3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuText3d")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("worldEditorMenuText3dPlace");
	leftWindow->getScreen("worldEditorMenuText3dPlace")->createScrollingList("text3dList", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuText3dPlace")->createButton("back", fvec2(0.0f, -0.9f), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("worldEditorMenuText3dChoice");
	leftWindow->getScreen("worldEditorMenuText3dChoice")->createScrollingList("text3dList", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuText3dChoice")->createButton("back", fvec2(0.0f, -0.9f), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuPointlight");
	leftWindow->getScreen("worldEditorMenuPointlight")->createButton("place", fvec2(0.0f, positions[0]), fvec2(TW("Place Pointlight"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Place Pointlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuPointlight")->createButton("choice", fvec2(0.0f, positions[1]), fvec2(TW("Choose Pointlight"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Choose Pointlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuPointlight")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("worldEditorMenuPointlightChoice");
	leftWindow->getScreen("worldEditorMenuPointlightChoice")->createScrollingList("pointlightList", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuPointlightChoice")->createButton("back", fvec2(0.0f, -0.9f), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuSpotlight");
	leftWindow->getScreen("worldEditorMenuSpotlight")->createButton("place", fvec2(0.0f, positions[0]), fvec2(TW("Place Spotlight"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Place Spotlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSpotlight")->createButton("choice", fvec2(0.0f, positions[1]), fvec2(TW("Choose Spotlight"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Choose Spotlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSpotlight")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("worldEditorMenuSpotlightChoice");
	leftWindow->getScreen("worldEditorMenuSpotlightChoice")->createScrollingList("spotlightList", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuSpotlightChoice")->createButton("back", fvec2(0.0f, -0.9f), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuReflection");
	leftWindow->getScreen("worldEditorMenuReflection")->createButton("place", fvec2(0.0f, positions[0]), fvec2(TW("Place Reflection"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Place Reflection", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuReflection")->createButton("choice", fvec2(0.0f, positions[1]), fvec2(TW("Choose Reflection"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Choose Reflection", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuReflection")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("worldEditorMenuReflectionChoice");
	leftWindow->getScreen("worldEditorMenuReflectionChoice")->createScrollingList("reflectionList", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuReflectionChoice")->createButton("back", fvec2(0.0f, -0.9f), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuSound");
	leftWindow->getScreen("worldEditorMenuSound")->createButton("place", fvec2(0.0f, positions[0]), fvec2(TW("Place Sound"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Place Sound", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSound")->createButton("choice", fvec2(0.0f, positions[1]), fvec2(TW("Choose Sound"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Choose Sound", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSound")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("worldEditorMenuSoundPlace");
	leftWindow->getScreen("worldEditorMenuSoundPlace")->createScrollingList("soundList", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuSoundPlace")->createButton("back", fvec2(0.0f, -0.9f), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("worldEditorMenuSoundChoice");
	leftWindow->getScreen("worldEditorMenuSoundChoice")->createScrollingList("soundList", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.15f, 0.1f), true);
	leftWindow->getScreen("worldEditorMenuSoundChoice")->createButton("back", fvec2(0.0f, -0.9f), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(4, CH);
	leftWindow->createScreen("worldEditorMenuSettings");
	leftWindow->getScreen("worldEditorMenuSettings")->createButton("lighting", fvec2(0.0f, positions[0]), fvec2(TW("Lighting"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lighting", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettings")->createButton("graphics", fvec2(0.0f, positions[1]), fvec2(TW("Graphics"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Graphics", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettings")->createButton("editorSpeed", fvec2(0.0f, positions[2]), fvec2(TW("Editor Speed"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Editor Speed", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettings")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(3, CH);
	leftWindow->createScreen("worldEditorMenuSettingsLighting");
	leftWindow->getScreen("worldEditorMenuSettingsLighting")->createButton("ambient", fvec2(0.0f, positions[0]), fvec2(TW("Ambient"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Ambient", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsLighting")->createButton("directional", fvec2(0.0f, positions[1]), fvec2(TW("Directional"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Directional", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsLighting")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(4, CH);
	leftWindow->createScreen("worldEditorMenuSettingsLightingAmbient");
	leftWindow->getScreen("worldEditorMenuSettingsLightingAmbient")->createButton("isEnabled", fvec2(0.0f, positions[0]), fvec2(TW("Enabled: OFF"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Enabled: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsLightingAmbient")->createButton("color", fvec2(0.0f, positions[1]), fvec2(TW("Color"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsLightingAmbient")->createButton("intensity", fvec2(0.0f, positions[2]), fvec2(TW("Intensity"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsLightingAmbient")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(5, CH);
	leftWindow->createScreen("worldEditorMenuSettingsLightingDirectional");
	leftWindow->getScreen("worldEditorMenuSettingsLightingDirectional")->createButton("isEnabled", fvec2(0.0f, positions[0]), fvec2(TW("Enabled: OFF"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Enabled: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsLightingDirectional")->createButton("position", fvec2(0.0f, positions[1]), fvec2(TW("Position"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Position", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsLightingDirectional")->createButton("color", fvec2(0.0f, positions[2]), fvec2(TW("Color"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsLightingDirectional")->createButton("intensity", fvec2(0.0f, positions[3]), fvec2(TW("Intensity"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsLightingDirectional")->createButton("back", fvec2(0.0f, positions[4]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(9, CH);
	leftWindow->createScreen("worldEditorMenuSettingsGraphics");
	leftWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("shadows", fvec2(0.0f, positions[0]), fvec2(TW("Shadows"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Shadows", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("reflections", fvec2(0.0f, positions[1]), fvec2(TW("Reflections"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Reflections", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("refractions", fvec2(0.0f, positions[2]), fvec2(TW("Refractions"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Refractions", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("dof", fvec2(0.0f, positions[3]), fvec2(TW("DOF"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "DOF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("fog", fvec2(0.0f, positions[4]), fvec2(TW("Fog"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Fog", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("lensFlare", fvec2(0.0f, positions[5]), fvec2(TW("Lens Flare"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lens Flare", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("skyExposure", fvec2(0.0f, positions[6]), fvec2(TW("Sky Exposure"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Sky Exposure", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("bloom", fvec2(0.0f, positions[7]), fvec2(TW("Bloom"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Bloom", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("back", fvec2(0.0f, positions[8]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(9, CH);
	leftWindow->createScreen("worldEditorMenuSettingsGraphicsShadows");
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("isEnabled", fvec2(0.0f, positions[0]), fvec2(TW("Enabled: OFF"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Enabled: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("eye", fvec2(0.0f, positions[1]), fvec2(TW("Eye"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Eye", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("center", fvec2(0.0f, positions[2]), fvec2(TW("Center"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Center", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("size", fvec2(0.0f, positions[3]), fvec2(TW("Size"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Size", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("lightness", fvec2(0.0f, positions[4]), fvec2(TW("Lightness"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lightness", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("isFollowingCamera", fvec2(0.0f, positions[5]), fvec2(TW("Follow Cam: OFF"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Follow Cam: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("interval", fvec2(0.0f, positions[6]), fvec2(TW("Interval"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Interval", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("quality", fvec2(0.0f, positions[7]), fvec2(TW("Quality"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Quality", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("back", fvec2(0.0f, positions[8]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(4, CH);
	leftWindow->createScreen("worldEditorMenuSettingsGraphicsReflections");
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsReflections")->createButton("planarHeight", fvec2(0.0f, positions[0]), fvec2(TW("Planar Height"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Planar Height", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsReflections")->createButton("cubeQuality", fvec2(0.0f, positions[1]), fvec2(TW("Cube Quality"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Cube Quality", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsReflections")->createButton("planarQuality", fvec2(0.0f, positions[2]), fvec2(TW("Planar Quality"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Planar Quality", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsReflections")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(2, CH);
	leftWindow->createScreen("worldEditorMenuSettingsGraphicsRefractions");
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsRefractions")->createButton("planarQuality", fvec2(0.0f, positions[0]), fvec2(TW("Planar Quality"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Planar Quality", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsRefractions")->createButton("back", fvec2(0.0f, positions[1]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(6, CH);
	leftWindow->createScreen("worldEditorMenuSettingsGraphicsDof");
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsDof")->createButton("isEnabled", fvec2(0.0f, positions[0]), fvec2(TW("Enabled: OFF"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Enabled: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsDof")->createButton("isDynamic", fvec2(0.0f, positions[1]), fvec2(TW("Dynamic: OFF"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Dynamic: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsDof")->createButton("blurDistance", fvec2(0.0f, positions[2]), fvec2(TW("Blur Distance"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Blur Distance", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsDof")->createButton("dynamicDistance", fvec2(0.0f, positions[3]), fvec2(TW("Dynamic Distance"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Dynamic Distance", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsDof")->createButton("quality", fvec2(0.0f, positions[4]), fvec2(TW("Quality"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Quality", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsDof")->createButton("back", fvec2(0.0f, positions[5]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(6, CH);
	leftWindow->createScreen("worldEditorMenuSettingsGraphicsFog");
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsFog")->createButton("isEnabled", fvec2(0.0f, positions[0]), fvec2(TW("Enabled: OFF"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Enabled: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsFog")->createButton("minDistance", fvec2(0.0f, positions[1]), fvec2(TW("Min Distance"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Min Distance", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsFog")->createButton("maxDistance", fvec2(0.0f, positions[2]), fvec2(TW("Max Distance"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Max Distance", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsFog")->createButton("thickness", fvec2(0.0f, positions[3]), fvec2(TW("Thickness"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Thickness", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsFog")->createButton("color", fvec2(0.0f, positions[4]), fvec2(TW("Color"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsFog")->createButton("back", fvec2(0.0f, positions[5]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(5, CH);
	leftWindow->createScreen("worldEditorMenuSettingsGraphicsLensFlare");
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsLensFlare")->createButton("isEnabled", fvec2(0.0f, positions[0]), fvec2(TW("Enabled: OFF"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Enabled: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsLensFlare")->createButton("flareMap", fvec2(0.0f, positions[1]), fvec2(TW("Flare Map"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Flare Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsLensFlare")->createButton("intensity", fvec2(0.0f, positions[2]), fvec2(TW("Intensity"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsLensFlare")->createButton("sensitivity", fvec2(0.0f, positions[3]), fvec2(TW("Sensitivity"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Sensitivity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsLensFlare")->createButton("back", fvec2(0.0f, positions[4]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(4, CH);
	leftWindow->createScreen("worldEditorMenuSettingsGraphicsSkyExposure");
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsSkyExposure")->createButton("isEnabled", fvec2(0.0f, positions[0]), fvec2(TW("Enabled: OFF"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Enabled: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsSkyExposure")->createButton("intensity", fvec2(0.0f, positions[1]), fvec2(TW("Intensity"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsSkyExposure")->createButton("speed", fvec2(0.0f, positions[2]), fvec2(TW("Speed"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Speed", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsSkyExposure")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(6, CH);
	leftWindow->createScreen("worldEditorMenuSettingsGraphicsBloom");
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsBloom")->createButton("isEnabled", fvec2(0.0f, positions[0]), fvec2(TW("Enabled: OFF"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Enabled: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsBloom")->createButton("type", fvec2(0.0f, positions[1]), fvec2(TW("Type: EVERYTHING"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Type: EVERYTHING", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsBloom")->createButton("intensity", fvec2(0.0f, positions[2]), fvec2(TW("Intensity"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsBloom")->createButton("blurCount", fvec2(0.0f, positions[3]), fvec2(TW("Blur Count"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Blur Count", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsBloom")->createButton("quality", fvec2(0.0f, positions[4]), fvec2(TW("Quality"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Quality", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("worldEditorMenuSettingsGraphicsBloom")->createButton("back", fvec2(0.0f, positions[5]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("modelPropertiesMenu");
	rightWindow->getScreen("modelPropertiesMenu")->createTextField("title", fvec2(0.0f, 0.95f), fvec2(1.25f, 0.1f), "Model Menu", fvec3(0.0f, 1.0f, 0.0f), true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("position", fvec2(0.0f, 0.8f), fvec2(0.75f, 0.2f), "position.tga", fvec3(1.0f), true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("rotation", fvec2(0.0f, 0.55f), fvec2(0.75f, 0.2f), "rotation.tga", fvec3(1.0f), true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("size", fvec2(0.0f, 0.3f), fvec2(0.75f, 0.2f), "size.tga", fvec3(1.0f), true);
	rightWindow->getScreen("modelPropertiesMenu")->createTextField("x", fvec2(0.0f, 0.135f), fvec2(0.25f, 0.1f), "X", fvec3(1.0f), true);
	rightWindow->getScreen("modelPropertiesMenu")->createTextField("y", fvec2(0.0f, -0.115f), fvec2(0.25f, 0.1f), "Y", fvec3(1.0f), true);
	rightWindow->getScreen("modelPropertiesMenu")->createTextField("z", fvec2(0.0f, -0.365f), fvec2(0.25f, 0.1f), "Z", fvec3(1.0f), true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("xPlus", fvec2(0.75f, 0.025f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("yPlus", fvec2(0.75f, -0.225f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("zPlus", fvec2(0.75f, -0.475f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("xMinus", fvec2(-0.75f, 0.025f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("yMinus", fvec2(-0.75f, -0.225f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("zMinus", fvec2(-0.75f, -0.475f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("modelPropertiesMenu")->createWriteField("x", fvec2(0.0f, 0.025f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("modelPropertiesMenu")->createWriteField("y", fvec2(0.0f, -0.225f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("modelPropertiesMenu")->createWriteField("z", fvec2(0.0f, -0.475f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("animation", fvec2(0.0f, -0.625f), fvec2(1.5f, 0.1f), fvec3(0.0f, 0.0f, 0.75f), fvec3(0.25f, 0.25f, 1.0f), "Animation", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("freeze", fvec2(0.0f, -0.775f), fvec2(1.0f, 0.1f), fvec3(0.0f, 0.0f, 0.75f), fvec3(0.25f, 0.25f, 1.0f), "Freeze", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("modelPropertiesMenu")->createButton("delete", fvec2(0.0f, -0.925f), fvec2(1.0f, 0.1f), fvec3(0.75f, 0.0f, 0.0f), fvec3(1.0f, 0.25f, 0.25f), "Delete", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("quad3dPropertiesMenu");
	rightWindow->getScreen("quad3dPropertiesMenu")->createTextField("title", fvec2(0.0f, 0.95f), fvec2(1.75f, 0.1f), "Quad3d Menu", fvec3(0.0f, 1.0f, 0.0f), true);
	rightWindow->getScreen("quad3dPropertiesMenu")->createButton("position", fvec2(0.0f, 0.8f), fvec2(0.75f, 0.2f), "position.tga", fvec3(1.0f), true);
	rightWindow->getScreen("quad3dPropertiesMenu")->createButton("rotation", fvec2(0.0f, 0.55f), fvec2(0.75f, 0.2f), "rotation.tga", fvec3(1.0f), true);
	rightWindow->getScreen("quad3dPropertiesMenu")->createButton("size", fvec2(0.0f, 0.3f), fvec2(0.75f, 0.2f), "size.tga", fvec3(1.0f), true);
	rightWindow->getScreen("quad3dPropertiesMenu")->createTextField("x", fvec2(0.0f, 0.135f), fvec2(0.25f, 0.1f), "X", fvec3(1.0f), true);
	rightWindow->getScreen("quad3dPropertiesMenu")->createTextField("y", fvec2(0.0f, -0.115f), fvec2(0.25f, 0.1f), "Y", fvec3(1.0f), true);
	rightWindow->getScreen("quad3dPropertiesMenu")->createTextField("z", fvec2(0.0f, -0.365f), fvec2(0.25f, 0.1f), "Z", fvec3(1.0f), true);
	rightWindow->getScreen("quad3dPropertiesMenu")->createButton("xPlus", fvec2(0.75f, 0.025f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("quad3dPropertiesMenu")->createButton("yPlus", fvec2(0.75f, -0.225f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("quad3dPropertiesMenu")->createButton("zPlus", fvec2(0.75f, -0.475f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("quad3dPropertiesMenu")->createButton("xMinus", fvec2(-0.75f, 0.025f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("quad3dPropertiesMenu")->createButton("yMinus", fvec2(-0.75f, -0.225f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("quad3dPropertiesMenu")->createButton("zMinus", fvec2(-0.75f, -0.475f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("quad3dPropertiesMenu")->createWriteField("x", fvec2(0.0f, 0.025f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("quad3dPropertiesMenu")->createWriteField("y", fvec2(0.0f, -0.225f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("quad3dPropertiesMenu")->createWriteField("z", fvec2(0.0f, -0.475f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("quad3dPropertiesMenu")->createButton("animation", fvec2(0.0f, -0.625f), fvec2(1.5f, 0.1f), fvec3(0.0f, 0.0f, 0.75f), fvec3(0.25f, 0.25f, 1.0f), "Animation", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("quad3dPropertiesMenu")->createButton("freeze", fvec2(0.0f, -0.775f), fvec2(1.0f, 0.1f), fvec3(0.0f, 0.0f, 0.75f), fvec3(0.25f, 0.25f, 1.0f), "Freeze", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("quad3dPropertiesMenu")->createButton("delete", fvec2(0.0f, -0.925f), fvec2(1.0f, 0.1f), fvec3(0.75f, 0.0f, 0.0f), fvec3(1.0f, 0.25f, 0.25f), "Delete", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("text3dPropertiesMenu");
	rightWindow->getScreen("text3dPropertiesMenu")->createTextField("title", fvec2(0.0f, 0.95f), fvec2(1.75f, 0.1f), "Text3d Menu", fvec3(0.0f, 1.0f, 0.0f), true);
	rightWindow->getScreen("text3dPropertiesMenu")->createButton("position", fvec2(0.0f, 0.8f), fvec2(0.75f, 0.2f), "position.tga", fvec3(1.0f), true);
	rightWindow->getScreen("text3dPropertiesMenu")->createButton("rotation", fvec2(0.0f, 0.55f), fvec2(0.75f, 0.2f), "rotation.tga", fvec3(1.0f), true);
	rightWindow->getScreen("text3dPropertiesMenu")->createButton("size", fvec2(0.0f, 0.3f), fvec2(0.75f, 0.2f), "size.tga", fvec3(1.0f), true);
	rightWindow->getScreen("text3dPropertiesMenu")->createTextField("x", fvec2(0.0f, 0.135f), fvec2(0.25f, 0.1f), "X", fvec3(1.0f), true);
	rightWindow->getScreen("text3dPropertiesMenu")->createTextField("y", fvec2(0.0f, -0.115f), fvec2(0.25f, 0.1f), "Y", fvec3(1.0f), true);
	rightWindow->getScreen("text3dPropertiesMenu")->createTextField("z", fvec2(0.0f, -0.365f), fvec2(0.25f, 0.1f), "Z", fvec3(1.0f), true);
	rightWindow->getScreen("text3dPropertiesMenu")->createButton("xPlus", fvec2(0.75f, 0.025f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("text3dPropertiesMenu")->createButton("yPlus", fvec2(0.75f, -0.225f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("text3dPropertiesMenu")->createButton("zPlus", fvec2(0.75f, -0.475f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("text3dPropertiesMenu")->createButton("xMinus", fvec2(-0.75f, 0.025f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("text3dPropertiesMenu")->createButton("yMinus", fvec2(-0.75f, -0.225f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("text3dPropertiesMenu")->createButton("zMinus", fvec2(-0.75f, -0.475f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("text3dPropertiesMenu")->createWriteField("x", fvec2(0.0f, 0.025f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("text3dPropertiesMenu")->createWriteField("y", fvec2(0.0f, -0.225f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("text3dPropertiesMenu")->createWriteField("z", fvec2(0.0f, -0.475f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("text3dPropertiesMenu")->createButton("animation", fvec2(0.0f, -0.625f), fvec2(1.5f, 0.1f), fvec3(0.0f, 0.0f, 0.75f), fvec3(0.25f, 0.25f, 1.0f), "Animation", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("text3dPropertiesMenu")->createButton("freeze", fvec2(0.0f, -0.775f), fvec2(1.0f, 0.1f), fvec3(0.0f, 0.0f, 0.75f), fvec3(0.25f, 0.25f, 1.0f), "Freeze", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("text3dPropertiesMenu")->createButton("delete", fvec2(0.0f, -0.925f), fvec2(1.0f, 0.1f), fvec3(0.75f, 0.0f, 0.0f), fvec3(1.0f, 0.25f, 0.25f), "Delete", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("pointlightPropertiesMenu");
	rightWindow->getScreen("pointlightPropertiesMenu")->createTextField("title", fvec2(0.0f, 0.95f), fvec2(1.875f, 0.1f), "Pointlight Menu", fvec3(0.0f, 1.0f, 0.0f), true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("position", fvec2(0.0f, 0.8f), fvec2(0.75f, 0.2f), "position.tga", fvec3(1.0f), true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("radius", fvec2(0.0f, 0.6f), fvec2(0.75f, 0.2f), "radius.tga", fvec3(1.0f), true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("color", fvec2(0.0f, 0.4f), fvec2(0.75f, 0.2f), "color.tga", fvec3(1.0f), true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createTextField("x", fvec2(0.0f, 0.235f), fvec2(0.25f, 0.1f), "X", fvec3(1.0f), true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createTextField("y", fvec2(0.0f, 0.01f), fvec2(0.25f, 0.1f), "Y", fvec3(1.0f), true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createTextField("z", fvec2(0.0f, -0.215f), fvec2(0.25f, 0.1f), "Z", fvec3(1.0f), true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("xPlus", fvec2(0.75f, 0.125f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("yPlus", fvec2(0.75f, -0.1f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("zPlus", fvec2(0.75f, -0.325f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("xMinus", fvec2(-0.75f, 0.125f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("yMinus", fvec2(-0.75f, -0.1f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("zMinus", fvec2(-0.75f, -0.325f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createWriteField("x", fvec2(0.0f, 0.125f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createWriteField("y", fvec2(0.0f, -0.1f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createWriteField("z", fvec2(0.0f, -0.325f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createTextField("intensity", fvec2(0.0f, -0.44f), fvec2(1.125f, 0.1f), "Intensity", fvec3(1.0f), true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("intensityPlus", fvec2(0.75f, -0.55f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("intensityMinus", fvec2(-0.75f, -0.55f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createWriteField("intensity", fvec2(0.0f, -0.55f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("shape", fvec2(0.0f, -0.725f), fvec2(0.75f, 0.2f), "shape_circle.tga", fvec3(1.0f), true);
	rightWindow->getScreen("pointlightPropertiesMenu")->createButton("delete", fvec2(0.0f, -0.91f), fvec2(1.0f, 0.1f), fvec3(0.75f, 0.0f, 0.0f), fvec3(1.0f, 0.25f, 0.25f), "Delete", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("spotlightPropertiesMenu");
	rightWindow->getScreen("spotlightPropertiesMenu")->createTextField("title", fvec2(0.0f, 0.95f), fvec2(1.75f, 0.1f), "Spotlight Menu", fvec3(0.0f, 1.0f, 0.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("position", fvec2(-0.5f, 0.8f), fvec2(0.75f, 0.2f), "position.tga", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("color", fvec2(0.5f, 0.8f), fvec2(0.75f, 0.2f), "color.tga", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createTextField("x", fvec2(0.0f, 0.725f), fvec2(0.25f, 0.1f), "X", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createTextField("y", fvec2(0.0f, 0.525f), fvec2(0.25f, 0.1f), "Y", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createTextField("z", fvec2(0.0f, 0.325f), fvec2(0.25f, 0.1f), "Z", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("xPlus", fvec2(0.75f, 0.625f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("yPlus", fvec2(0.75f, 0.425f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("zPlus", fvec2(0.75f, 0.225f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("xMinus", fvec2(-0.75f, 0.625f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("yMinus", fvec2(-0.75f, 0.425f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("zMinus", fvec2(-0.75f, 0.225f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createWriteField("x", fvec2(0.0f, 0.625f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createWriteField("y", fvec2(0.0f, 0.425f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createWriteField("z", fvec2(0.0f, 0.225f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createTextField("yaw", fvec2(0.0f, 0.125f), fvec2(0.375f, 0.1f), "Yaw", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("yawPlus", fvec2(0.75f, 0.025f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("yawMinus", fvec2(-0.75f, 0.025f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createWriteField("yaw", fvec2(0.0f, 0.025f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createTextField("pitch", fvec2(0.0f, -0.075f), fvec2(0.625f, 0.1f), "Pitch", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("pitchPlus", fvec2(0.75f, -0.175f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("pitchMinus", fvec2(-0.75f, -0.175f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createWriteField("pitch", fvec2(0.0f, -0.175f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createTextField("intensity", fvec2(0.0f, -0.275f), fvec2(1.125f, 0.1f), "Intensity", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("intensityPlus", fvec2(0.75f, -0.375f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("intensityMinus", fvec2(-0.75f, -0.375f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createWriteField("intensity", fvec2(0.0f, -0.375f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createTextField("angle", fvec2(0.0f, -0.475f), fvec2(0.625f, 0.1f), "Angle", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("anglePlus", fvec2(0.75f, -0.575f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("angleMinus", fvec2(-0.75f, -0.575f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createWriteField("angle", fvec2(0.0f, -0.575f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createTextField("distance", fvec2(0.0f, -0.675f), fvec2(1.0f, 0.1f), "Distance", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("distancePlus", fvec2(0.75f, -0.775f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("distanceMinus", fvec2(-0.75f, -0.775f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createWriteField("distance", fvec2(0.0f, -0.775f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("spotlightPropertiesMenu")->createButton("delete", fvec2(0.0f, -0.915f), fvec2(1.0f, 0.1f), fvec3(0.75f, 0.0f, 0.0f), fvec3(1.0f, 0.25f, 0.25f), "Delete", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("reflectionPropertiesMenu");
	rightWindow->getScreen("reflectionPropertiesMenu")->createTextField("title", fvec2(0.0f, 0.95f), fvec2(1.875f, 0.1f), "Reflection Menu", fvec3(0.0f, 1.0f, 0.0f), true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createTextField("x", fvec2(0.0f, 0.81f), fvec2(0.25f, 0.1f), "X", fvec3(1.0f), true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createTextField("y", fvec2(0.0f, 0.56f), fvec2(0.25f, 0.1f), "Y", fvec3(1.0f), true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createTextField("z", fvec2(0.0f, 0.31f), fvec2(0.25f, 0.1f), "Z", fvec3(1.0f), true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createButton("xPlus", fvec2(0.75f, 0.7f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createButton("yPlus", fvec2(0.75f, 0.45f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createButton("zPlus", fvec2(0.75f, 0.2f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createButton("xMinus", fvec2(-0.75f, 0.7f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createButton("yMinus", fvec2(-0.75f, 0.45f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createButton("zMinus", fvec2(-0.75f, 0.2f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createWriteField("x", fvec2(0.0f, 0.7f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createWriteField("y", fvec2(0.0f, 0.45f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createWriteField("z", fvec2(0.0f, 0.2f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createButton("capture", fvec2(0.0f, 0.05f), fvec2(1.0f, 0.1f), fvec3(0.0f, 0.0f, 0.75f), fvec3(0.25f, 0.25f, 1.0f), "Capture", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("reflectionPropertiesMenu")->createButton("delete", fvec2(0.0f, -0.1f), fvec2(1.0f, 0.1f), fvec3(0.75f, 0.0f, 0.0f), fvec3(1.0f, 0.25f, 0.25f), "Delete", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("soundPropertiesMenu");
	rightWindow->getScreen("soundPropertiesMenu")->createTextField("title", fvec2(0.0f, 0.95f), fvec2(1.25f, 0.1f), "Sound Menu", fvec3(0.0f, 1.0f, 0.0f), true);
	rightWindow->getScreen("soundPropertiesMenu")->createTextField("x", fvec2(0.0f, 0.81f), fvec2(0.25f, 0.1f), "X", fvec3(1.0f), true);
	rightWindow->getScreen("soundPropertiesMenu")->createTextField("y", fvec2(0.0f, 0.56f), fvec2(0.25f, 0.1f), "Y", fvec3(1.0f), true);
	rightWindow->getScreen("soundPropertiesMenu")->createTextField("z", fvec2(0.0f, 0.31f), fvec2(0.25f, 0.1f), "Z", fvec3(1.0f), true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("xPlus", fvec2(0.75f, 0.7f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("yPlus", fvec2(0.75f, 0.45f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("zPlus", fvec2(0.75f, 0.2f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("xMinus", fvec2(-0.75f, 0.7f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("yMinus", fvec2(-0.75f, 0.45f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("zMinus", fvec2(-0.75f, 0.2f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("soundPropertiesMenu")->createWriteField("x", fvec2(0.0f, 0.7f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("soundPropertiesMenu")->createWriteField("y", fvec2(0.0f, 0.45f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("soundPropertiesMenu")->createWriteField("z", fvec2(0.0f, 0.2f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("soundPropertiesMenu")->createTextField("distance", fvec2(0.0f, 0.06f), fvec2(1.5f, 0.1f), "Max distance", fvec3(1.0f), true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("distancePlus", fvec2(0.75f, -0.05f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("distanceMinus", fvec2(-0.75f, -0.05f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("soundPropertiesMenu")->createWriteField("distance", fvec2(0.0f, -0.05f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("soundPropertiesMenu")->createTextField("volume", fvec2(0.0f, -0.19f), fvec2(1.25f, 0.1f), "Max volume", fvec3(1.0f), true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("volumePlus", fvec2(0.75f, -0.3f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("volumeMinus", fvec2(-0.75f, -0.3f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), true);
	rightWindow->getScreen("soundPropertiesMenu")->createWriteField("volume", fvec2(0.0f, -0.3f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 0, 1, 1, 1, 1, true);
	rightWindow->getScreen("soundPropertiesMenu")->createButton("delete", fvec2(0.0f, -0.45f), fvec2(1.0f, 0.1f), fvec3(0.75f, 0.0f, 0.0f), fvec3(1.0f, 0.25f, 0.25f), "Delete", TEXT_COLOR, TEXT_HOVER_COLOR, true);
}

void WorldEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuMain");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuChoice");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSky");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuTerrain");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuWater");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuModel");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuModelPlace");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuModelChoice");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuQuad3d");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuQuad3dPlace");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuQuad3dChoice");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuText3d");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuText3dPlace");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuText3dChoice");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSound");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSoundPlace");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSoundChoice");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuPointlight");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuPointlightChoice");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSpotlight");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSpotlightChoice");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuReflection");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuReflectionChoice");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSettings");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSettingsLighting");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSettingsLightingAmbient");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSettingsLightingDirectional");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSettingsGraphics");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSettingsGraphicsShadows");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSettingsGraphicsReflections");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSettingsGraphicsRefractions");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSettingsGraphicsDof");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSettingsGraphicsFog");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSettingsGraphicsLensFlare");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSettingsGraphicsSkyExposure");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("worldEditorMenuSettingsGraphicsBloom");
	_gui->getRightViewport()->getWindow("main")->deleteScreen("modelPropertiesMenu");
	_gui->getRightViewport()->getWindow("main")->deleteScreen("quad3dPropertiesMenu");
	_gui->getRightViewport()->getWindow("main")->deleteScreen("text3dPropertiesMenu");
	_gui->getRightViewport()->getWindow("main")->deleteScreen("soundPropertiesMenu");
	_gui->getRightViewport()->getWindow("main")->deleteScreen("pointlightPropertiesMenu");
	_gui->getRightViewport()->getWindow("main")->deleteScreen("spotlightPropertiesMenu");
	_gui->getRightViewport()->getWindow("main")->deleteScreen("reflectionPropertiesMenu");
}