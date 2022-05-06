#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	auto positions = Mathematics::calculateDistributedPositions(4, CH, false);
	rightWindow->createScreen("worldEditorMenuMain");
	rightWindow->getScreen("worldEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create World"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create World", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit World"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit World", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), TEXT_SIZE("Delete World"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete World", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(13, CH, false);
	rightWindow->createScreen("worldEditorMenuChoice");
	rightWindow->getScreen("worldEditorMenuChoice")->createButton("sky", fvec2(0.0f, positions[0]), TEXT_SIZE("Sky"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuChoice")->createButton("terrain", fvec2(0.0f, positions[1]), TEXT_SIZE("Terrain"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Terrain", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuChoice")->createButton("water", fvec2(0.0f, positions[2]), TEXT_SIZE("Water"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Water", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuChoice")->createButton("model", fvec2(0.0f, positions[3]), TEXT_SIZE("Model"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuChoice")->createButton("quad3d", fvec2(0.0f, positions[4]), TEXT_SIZE("Quad3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Quad3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuChoice")->createButton("text3d", fvec2(0.0f, positions[5]), TEXT_SIZE("Text3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Text3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuChoice")->createButton("aabb", fvec2(0.0f, positions[6]), TEXT_SIZE("AABB"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "AABB", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuChoice")->createButton("pointlight", fvec2(0.0f, positions[7]), TEXT_SIZE("Pointlight"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Pointlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuChoice")->createButton("spotlight", fvec2(0.0f, positions[8]), TEXT_SIZE("Spotlight"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Spotlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuChoice")->createButton("captor", fvec2(0.0f, positions[9]), TEXT_SIZE("Captor"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Captor", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuChoice")->createButton("sound3d", fvec2(0.0f, positions[10]), TEXT_SIZE("Sound3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Sound3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuChoice")->createButton("settings", fvec2(0.0f, positions[11]), TEXT_SIZE("Settings"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Settings", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[12]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(3, CH, false);
	rightWindow->createScreen("worldEditorMenuSky");
	rightWindow->getScreen("worldEditorMenuSky")->createButton("place", fvec2(0.0f, positions[0]), TEXT_SIZE("Place Sky"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Place Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSky")->createButton("delete", fvec2(0.0f, positions[1]), TEXT_SIZE("Delete Sky"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSky")->createButton("back", fvec2(0.0f, positions[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("worldEditorMenuSkyPlace");
	rightWindow->getScreen("worldEditorMenuSkyPlace")->createScrollingList("templateSkies", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.125f, 0.075f), 0.25f, true);
	rightWindow->getScreen("worldEditorMenuSkyPlace")->createButton("back", fvec2(0.0f, -0.9f), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(3, CH, false);
	rightWindow->createScreen("worldEditorMenuTerrain");
	rightWindow->getScreen("worldEditorMenuTerrain")->createButton("place", fvec2(0.0f, positions[0]), TEXT_SIZE("Place Terrain"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Place Terrain", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuTerrain")->createButton("delete", fvec2(0.0f, positions[1]), TEXT_SIZE("Delete Terrain"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Terrain", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuTerrain")->createButton("back", fvec2(0.0f, positions[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("worldEditorMenuTerrainPlace");
	rightWindow->getScreen("worldEditorMenuTerrainPlace")->createScrollingList("templateTerrains", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.125f, 0.075f), 0.25f, true);
	rightWindow->getScreen("worldEditorMenuTerrainPlace")->createButton("back", fvec2(0.0f, -0.9f), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(5, CH, false);
	rightWindow->createScreen("worldEditorMenuWater");
	rightWindow->getScreen("worldEditorMenuWater")->createButton("place", fvec2(0.0f, positions[0]), TEXT_SIZE("Place Water"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Place Water", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuWater")->createButton("up", fvec2(0.0f, positions[1]), TEXT_SIZE("Move Up"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Move Up", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuWater")->createButton("down", fvec2(0.0f, positions[2]), TEXT_SIZE("Move Down"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Move Down", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuWater")->createButton("delete", fvec2(0.0f, positions[3]), TEXT_SIZE("Delete Water"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Water", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuWater")->createButton("back", fvec2(0.0f, positions[4]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("worldEditorMenuWaterPlace");
	rightWindow->getScreen("worldEditorMenuWaterPlace")->createScrollingList("templateWaters", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.125f, 0.075f), 0.25f, true);
	rightWindow->getScreen("worldEditorMenuWaterPlace")->createButton("back", fvec2(0.0f, -0.9f), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(3, CH, false);
	rightWindow->createScreen("worldEditorMenuModel");
	rightWindow->getScreen("worldEditorMenuModel")->createButton("place", fvec2(0.0f, positions[0]), TEXT_SIZE("Place Model"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Place Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuModel")->createButton("choice", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Model"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuModel")->createButton("back", fvec2(0.0f, positions[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("worldEditorMenuModelPlace");
	rightWindow->getScreen("worldEditorMenuModelPlace")->createScrollingList("templateModels", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.125f, 0.075f), 0.25f, true);
	rightWindow->getScreen("worldEditorMenuModelPlace")->createButton("back", fvec2(0.0f, -0.9f), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("worldEditorMenuModelChoice");
	rightWindow->getScreen("worldEditorMenuModelChoice")->createScrollingList("placedModels", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.125f, 0.075f), 0.25f, true);
	rightWindow->getScreen("worldEditorMenuModelChoice")->createButton("back", fvec2(0.0f, -0.9f), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(3, CH, false);
	rightWindow->createScreen("worldEditorMenuQuad3d");
	rightWindow->getScreen("worldEditorMenuQuad3d")->createButton("place", fvec2(0.0f, positions[0]), TEXT_SIZE("Place Quad3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Place Quad3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuQuad3d")->createButton("choice", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Quad3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Quad3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuQuad3d")->createButton("back", fvec2(0.0f, positions[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("worldEditorMenuQuad3dPlace");
	rightWindow->getScreen("worldEditorMenuQuad3dPlace")->createScrollingList("templateQuad3ds", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.125f, 0.075f), 0.25f, true);
	rightWindow->getScreen("worldEditorMenuQuad3dPlace")->createButton("back", fvec2(0.0f, -0.9f), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("worldEditorMenuQuad3dChoice");
	rightWindow->getScreen("worldEditorMenuQuad3dChoice")->createScrollingList("placedQuad3ds", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.125f, 0.075f), 0.25f, true);
	rightWindow->getScreen("worldEditorMenuQuad3dChoice")->createButton("back", fvec2(0.0f, -0.9f), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(3, CH, false);
	rightWindow->createScreen("worldEditorMenuText3d");
	rightWindow->getScreen("worldEditorMenuText3d")->createButton("place", fvec2(0.0f, positions[0]), TEXT_SIZE("Place Text3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Place Text3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuText3d")->createButton("choice", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Text3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Text3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuText3d")->createButton("back", fvec2(0.0f, positions[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("worldEditorMenuText3dPlace");
	rightWindow->getScreen("worldEditorMenuText3dPlace")->createScrollingList("templateText3ds", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.125f, 0.075f), 0.25f, true);
	rightWindow->getScreen("worldEditorMenuText3dPlace")->createButton("back", fvec2(0.0f, -0.9f), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("worldEditorMenuText3dChoice");
	rightWindow->getScreen("worldEditorMenuText3dChoice")->createScrollingList("placedText3ds", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.125f, 0.075f), 0.25f, true);
	rightWindow->getScreen("worldEditorMenuText3dChoice")->createButton("back", fvec2(0.0f, -0.9f), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(3, CH, false);
	rightWindow->createScreen("worldEditorMenuAabb");
	rightWindow->getScreen("worldEditorMenuAabb")->createButton("place", fvec2(0.0f, positions[0]), TEXT_SIZE("Place AABB"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Place AABB", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuAabb")->createButton("choice", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit AABB"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit AABB", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuAabb")->createButton("back", fvec2(0.0f, positions[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("worldEditorMenuAabbPlace");
	rightWindow->getScreen("worldEditorMenuAabbPlace")->createScrollingList("templateAabbs", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.125f, 0.075f), 0.25f, true);
	rightWindow->getScreen("worldEditorMenuAabbPlace")->createButton("back", fvec2(0.0f, -0.9f), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("worldEditorMenuAabbChoice");
	rightWindow->getScreen("worldEditorMenuAabbChoice")->createScrollingList("placedAabbs", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.125f, 0.075f), 0.25f, true);
	rightWindow->getScreen("worldEditorMenuAabbChoice")->createButton("back", fvec2(0.0f, -0.9f), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(3, CH, false);
	rightWindow->createScreen("worldEditorMenuPointlight");
	rightWindow->getScreen("worldEditorMenuPointlight")->createButton("place", fvec2(0.0f, positions[0]), TEXT_SIZE("Place Pointlight"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Place Pointlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuPointlight")->createButton("choice", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Pointlight"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Pointlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuPointlight")->createButton("back", fvec2(0.0f, positions[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("worldEditorMenuPointlightChoice");
	rightWindow->getScreen("worldEditorMenuPointlightChoice")->createScrollingList("placedPointlights", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.125f, 0.075f), 0.25f, true);
	rightWindow->getScreen("worldEditorMenuPointlightChoice")->createButton("back", fvec2(0.0f, -0.9f), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(3, CH, false);
	rightWindow->createScreen("worldEditorMenuSpotlight");
	rightWindow->getScreen("worldEditorMenuSpotlight")->createButton("place", fvec2(0.0f, positions[0]), TEXT_SIZE("Place Spotlight"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Place Spotlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSpotlight")->createButton("choice", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Spotlight"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Spotlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSpotlight")->createButton("back", fvec2(0.0f, positions[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("worldEditorMenuSpotlightChoice");
	rightWindow->getScreen("worldEditorMenuSpotlightChoice")->createScrollingList("placedSpotlights", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.125f, 0.075f), 0.25f, true);
	rightWindow->getScreen("worldEditorMenuSpotlightChoice")->createButton("back", fvec2(0.0f, -0.9f), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(3, CH, false);
	rightWindow->createScreen("worldEditorMenuCaptor");
	rightWindow->getScreen("worldEditorMenuCaptor")->createButton("place", fvec2(0.0f, positions[0]), TEXT_SIZE("Place Captor"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Place Captor", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuCaptor")->createButton("choice", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Captor"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Captor", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuCaptor")->createButton("back", fvec2(0.0f, positions[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("worldEditorMenuCaptorChoice");
	rightWindow->getScreen("worldEditorMenuCaptorChoice")->createScrollingList("placedCaptors", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.125f, 0.075f), 0.25f, true);
	rightWindow->getScreen("worldEditorMenuCaptorChoice")->createButton("back", fvec2(0.0f, -0.9f), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(3, CH, false);
	rightWindow->createScreen("worldEditorMenuSound3d");
	rightWindow->getScreen("worldEditorMenuSound3d")->createButton("place", fvec2(0.0f, positions[0]), TEXT_SIZE("Place Sound3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Place Sound3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSound3d")->createButton("choice", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Sound3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Sound3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSound3d")->createButton("back", fvec2(0.0f, positions[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("worldEditorMenuSound3dPlace");
	rightWindow->getScreen("worldEditorMenuSound3dPlace")->createScrollingList("templateSound3ds", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.125f, 0.075f), 0.25f, true);
	rightWindow->getScreen("worldEditorMenuSound3dPlace")->createButton("back", fvec2(0.0f, -0.9f), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("worldEditorMenuSound3dChoice");
	rightWindow->getScreen("worldEditorMenuSound3dChoice")->createScrollingList("placedSound3ds", fvec2(0.0f, 0.1f), fvec2(1.8f, 1.75f), SCROLLING_LIST_COLOR, BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, fvec2(0.125f, 0.075f), 0.25f, true);
	rightWindow->getScreen("worldEditorMenuSound3dChoice")->createButton("back", fvec2(0.0f, -0.9f), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(4, CH, false);
	rightWindow->createScreen("worldEditorMenuSettings");
	rightWindow->getScreen("worldEditorMenuSettings")->createButton("lighting", fvec2(0.0f, positions[0]), TEXT_SIZE("Lighting"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lighting", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettings")->createButton("graphics", fvec2(0.0f, positions[1]), TEXT_SIZE("Graphics"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Graphics", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettings")->createButton("editorSpeed", fvec2(0.0f, positions[2]), TEXT_SIZE("Editor Speed"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Editor Speed", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettings")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(3, CH, false);
	rightWindow->createScreen("worldEditorMenuSettingsLighting");
	rightWindow->getScreen("worldEditorMenuSettingsLighting")->createButton("ambient", fvec2(0.0f, positions[0]), TEXT_SIZE("Ambient"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Ambient", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsLighting")->createButton("directional", fvec2(0.0f, positions[1]), TEXT_SIZE("Directional"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Directional", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsLighting")->createButton("back", fvec2(0.0f, positions[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(4, CH, false);
	rightWindow->createScreen("worldEditorMenuSettingsLightingAmbient");
	rightWindow->getScreen("worldEditorMenuSettingsLightingAmbient")->createButton("isEnabled", fvec2(0.0f, positions[0]), TEXT_SIZE("Enabled: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Enabled: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsLightingAmbient")->createButton("color", fvec2(0.0f, positions[1]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsLightingAmbient")->createButton("intensity", fvec2(0.0f, positions[2]), TEXT_SIZE("Intensity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsLightingAmbient")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(5, CH, false);
	rightWindow->createScreen("worldEditorMenuSettingsLightingDirectional");
	rightWindow->getScreen("worldEditorMenuSettingsLightingDirectional")->createButton("isEnabled", fvec2(0.0f, positions[0]), TEXT_SIZE("Enabled: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Enabled: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsLightingDirectional")->createButton("position", fvec2(0.0f, positions[1]), TEXT_SIZE("Position"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Position", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsLightingDirectional")->createButton("color", fvec2(0.0f, positions[2]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsLightingDirectional")->createButton("intensity", fvec2(0.0f, positions[3]), TEXT_SIZE("Intensity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsLightingDirectional")->createButton("back", fvec2(0.0f, positions[4]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(9, CH, false);
	rightWindow->createScreen("worldEditorMenuSettingsGraphics");
	rightWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("shadows", fvec2(0.0f, positions[0]), TEXT_SIZE("Shadows"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Shadows", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("reflections", fvec2(0.0f, positions[1]), TEXT_SIZE("Reflections"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Reflections", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("refractions", fvec2(0.0f, positions[2]), TEXT_SIZE("Refractions"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Refractions", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("dof", fvec2(0.0f, positions[3]), TEXT_SIZE("DOF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "DOF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("fog", fvec2(0.0f, positions[4]), TEXT_SIZE("Fog"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Fog", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("lensFlare", fvec2(0.0f, positions[5]), TEXT_SIZE("Lens Flare"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lens Flare", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("skyExposure", fvec2(0.0f, positions[6]), TEXT_SIZE("Sky Exposure"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Sky Exposure", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("bloom", fvec2(0.0f, positions[7]), TEXT_SIZE("Bloom"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Bloom", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphics")->createButton("back", fvec2(0.0f, positions[8]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(11, CH, false);
	rightWindow->createScreen("worldEditorMenuSettingsGraphicsShadows");
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("isEnabled", fvec2(0.0f, positions[0]), TEXT_SIZE("Enabled: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Enabled: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("position", fvec2(0.0f, positions[1]), TEXT_SIZE("Position"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Position", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("lookat", fvec2(0.0f, positions[2]), TEXT_SIZE("Lookat"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lookat", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("size", fvec2(0.0f, positions[3]), TEXT_SIZE("Size"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Size", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("lightness", fvec2(0.0f, positions[4]), TEXT_SIZE("Lightness"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lightness", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("isFollowingCameraX", fvec2(0.0f, positions[5]), TEXT_SIZE("Follow Cam X: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Follow Cam X: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("isFollowingCameraY", fvec2(0.0f, positions[6]), TEXT_SIZE("Follow Cam Y: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Follow Cam Y: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("isFollowingCameraZ", fvec2(0.0f, positions[7]), TEXT_SIZE("Follow Cam Z: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Follow Cam Z: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("interval", fvec2(0.0f, positions[8]), TEXT_SIZE("Interval"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Interval", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("quality", fvec2(0.0f, positions[9]), TEXT_SIZE("Quality"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Quality", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsShadows")->createButton("back", fvec2(0.0f, positions[10]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(5, CH, false);
	rightWindow->createScreen("worldEditorMenuSettingsGraphicsReflections");
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsReflections")->createButton("cubeInterval", fvec2(0.0f, positions[0]), TEXT_SIZE("Cube Interval"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Cube Interval", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsReflections")->createButton("cubeQuality", fvec2(0.0f, positions[1]), TEXT_SIZE("Cube Quality"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Cube Quality", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsReflections")->createButton("planarHeight", fvec2(0.0f, positions[2]), TEXT_SIZE("Planar Height"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Planar Height", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsReflections")->createButton("planarQuality", fvec2(0.0f, positions[3]), TEXT_SIZE("Planar Quality"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Planar Quality", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsReflections")->createButton("back", fvec2(0.0f, positions[4]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(5, CH, false);
	rightWindow->createScreen("worldEditorMenuSettingsGraphicsRefractions");
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsRefractions")->createButton("cubeInterval", fvec2(0.0f, positions[0]), TEXT_SIZE("Cube Interval"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Planar Interval", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsRefractions")->createButton("cubeQuality", fvec2(0.0f, positions[1]), TEXT_SIZE("Cube Quality"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Planar Quality", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsRefractions")->createButton("planarHeight", fvec2(0.0f, positions[2]), TEXT_SIZE("Planar Height"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Planar Height", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsRefractions")->createButton("planarQuality", fvec2(0.0f, positions[3]), TEXT_SIZE("Planar Quality"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Planar Quality", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsRefractions")->createButton("back", fvec2(0.0f, positions[4]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(6, CH, false);
	rightWindow->createScreen("worldEditorMenuSettingsGraphicsDof");
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsDof")->createButton("isEnabled", fvec2(0.0f, positions[0]), TEXT_SIZE("Enabled: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Enabled: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsDof")->createButton("isDynamic", fvec2(0.0f, positions[1]), TEXT_SIZE("Dynamic: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Dynamic: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsDof")->createButton("blurDistance", fvec2(0.0f, positions[2]), TEXT_SIZE("Blur Distance"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Blur Distance", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsDof")->createButton("dynamicDistance", fvec2(0.0f, positions[3]), TEXT_SIZE("Dynamic Distance"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Dynamic Distance", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsDof")->createButton("quality", fvec2(0.0f, positions[4]), TEXT_SIZE("Quality"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Quality", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsDof")->createButton("back", fvec2(0.0f, positions[5]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(6, CH, false);
	rightWindow->createScreen("worldEditorMenuSettingsGraphicsFog");
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsFog")->createButton("isEnabled", fvec2(0.0f, positions[0]), TEXT_SIZE("Enabled: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Enabled: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsFog")->createButton("minDistance", fvec2(0.0f, positions[1]), TEXT_SIZE("Min Distance"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Min Distance", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsFog")->createButton("maxDistance", fvec2(0.0f, positions[2]), TEXT_SIZE("Max Distance"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Max Distance", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsFog")->createButton("thickness", fvec2(0.0f, positions[3]), TEXT_SIZE("Thickness"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Thickness", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsFog")->createButton("color", fvec2(0.0f, positions[4]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsFog")->createButton("back", fvec2(0.0f, positions[5]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(5, CH, false);
	rightWindow->createScreen("worldEditorMenuSettingsGraphicsLensFlare");
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsLensFlare")->createButton("isEnabled", fvec2(0.0f, positions[0]), TEXT_SIZE("Enabled: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Enabled: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsLensFlare")->createButton("flareMap", fvec2(0.0f, positions[1]), TEXT_SIZE("Flare Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Flare Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsLensFlare")->createButton("intensity", fvec2(0.0f, positions[2]), TEXT_SIZE("Intensity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsLensFlare")->createButton("sensitivity", fvec2(0.0f, positions[3]), TEXT_SIZE("Sensitivity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Sensitivity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsLensFlare")->createButton("back", fvec2(0.0f, positions[4]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(4, CH, false);
	rightWindow->createScreen("worldEditorMenuSettingsGraphicsSkyExposure");
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsSkyExposure")->createButton("isEnabled", fvec2(0.0f, positions[0]), TEXT_SIZE("Enabled: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Enabled: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsSkyExposure")->createButton("intensity", fvec2(0.0f, positions[1]), TEXT_SIZE("Intensity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsSkyExposure")->createButton("speed", fvec2(0.0f, positions[2]), TEXT_SIZE("Speed"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Speed", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsSkyExposure")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(6, CH, false);
	rightWindow->createScreen("worldEditorMenuSettingsGraphicsBloom");
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsBloom")->createButton("isEnabled", fvec2(0.0f, positions[0]), TEXT_SIZE("Enabled: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Enabled: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsBloom")->createButton("type", fvec2(0.0f, positions[1]), TEXT_SIZE("Type: EVERYTHING"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Type: EVERYTHING", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsBloom")->createButton("intensity", fvec2(0.0f, positions[2]), TEXT_SIZE("Intensity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsBloom")->createButton("blurCount", fvec2(0.0f, positions[3]), TEXT_SIZE("Blur Count"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Blur Count", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsBloom")->createButton("quality", fvec2(0.0f, positions[4]), TEXT_SIZE("Quality"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Quality", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("worldEditorMenuSettingsGraphicsBloom")->createButton("back", fvec2(0.0f, positions[5]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("modelPropertiesMenu");
	leftWindow->getScreen("modelPropertiesMenu")->createTextField("title", fvec2(0.0f, 0.95f), fvec2(1.25f, 0.1f), "Model Menu", fvec3(0.0f, 1.0f, 0.0f), true);
	leftWindow->getScreen("modelPropertiesMenu")->createButton("position", fvec2(0.0f, 0.8f), fvec2(0.75f, 0.2f), "position.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("modelPropertiesMenu")->createButton("rotation", fvec2(0.0f, 0.55f), fvec2(0.75f, 0.2f), "rotation.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("modelPropertiesMenu")->createButton("size", fvec2(0.0f, 0.3f), fvec2(0.75f, 0.2f), "size.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("modelPropertiesMenu")->createTextField("x", fvec2(0.0f, 0.135f), fvec2(0.25f, 0.1f), "X", fvec3(1.0f), true);
	leftWindow->getScreen("modelPropertiesMenu")->createTextField("y", fvec2(0.0f, -0.115f), fvec2(0.25f, 0.1f), "Y", fvec3(1.0f), true);
	leftWindow->getScreen("modelPropertiesMenu")->createTextField("z", fvec2(0.0f, -0.365f), fvec2(0.25f, 0.1f), "Z", fvec3(1.0f), true);
	leftWindow->getScreen("modelPropertiesMenu")->createButton("xPlus", fvec2(0.75f, 0.025f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("modelPropertiesMenu")->createButton("yPlus", fvec2(0.75f, -0.225f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("modelPropertiesMenu")->createButton("zPlus", fvec2(0.75f, -0.475f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("modelPropertiesMenu")->createButton("xMinus", fvec2(-0.75f, 0.025f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("modelPropertiesMenu")->createButton("yMinus", fvec2(-0.75f, -0.225f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("modelPropertiesMenu")->createButton("zMinus", fvec2(-0.75f, -0.475f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("modelPropertiesMenu")->createInputBox("x", fvec2(0.0f, 0.025f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("modelPropertiesMenu")->createInputBox("y", fvec2(0.0f, -0.225f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("modelPropertiesMenu")->createInputBox("z", fvec2(0.0f, -0.475f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("modelPropertiesMenu")->createButton("animation3d", fvec2(0.0f, -0.625f), fvec2(1.875f, 0.1f), "", fvec3(0.0f, 0.0f, 0.75f), fvec3(0.25f, 0.25f, 1.0f), "Start Animation3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelPropertiesMenu")->createButton("freeze", fvec2(0.0f, -0.775f), fvec2(0.75f, 0.1f), "", fvec3(0.0f, 0.0f, 0.75f), fvec3(0.25f, 0.25f, 1.0f), "Freeze", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("modelPropertiesMenu")->createButton("delete", fvec2(0.0f, -0.925f), fvec2(0.75f, 0.1f), "", fvec3(0.75f, 0.0f, 0.0f), fvec3(1.0f, 0.25f, 0.25f), "Delete", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("quad3dPropertiesMenu");
	leftWindow->getScreen("quad3dPropertiesMenu")->createTextField("title", fvec2(0.0f, 0.95f), fvec2(1.375f, 0.1f), "Quad3D Menu", fvec3(0.0f, 1.0f, 0.0f), true);
	leftWindow->getScreen("quad3dPropertiesMenu")->createButton("position", fvec2(0.0f, 0.8f), fvec2(0.75f, 0.2f), "position.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("quad3dPropertiesMenu")->createButton("rotation", fvec2(0.0f, 0.55f), fvec2(0.75f, 0.2f), "rotation.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("quad3dPropertiesMenu")->createButton("size", fvec2(0.0f, 0.3f), fvec2(0.75f, 0.2f), "size.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("quad3dPropertiesMenu")->createTextField("x", fvec2(0.0f, 0.135f), fvec2(0.25f, 0.1f), "X", fvec3(1.0f), true);
	leftWindow->getScreen("quad3dPropertiesMenu")->createTextField("y", fvec2(0.0f, -0.115f), fvec2(0.25f, 0.1f), "Y", fvec3(1.0f), true);
	leftWindow->getScreen("quad3dPropertiesMenu")->createTextField("z", fvec2(0.0f, -0.365f), fvec2(0.25f, 0.1f), "Z", fvec3(1.0f), true);
	leftWindow->getScreen("quad3dPropertiesMenu")->createButton("xPlus", fvec2(0.75f, 0.025f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("quad3dPropertiesMenu")->createButton("yPlus", fvec2(0.75f, -0.225f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("quad3dPropertiesMenu")->createButton("zPlus", fvec2(0.75f, -0.475f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("quad3dPropertiesMenu")->createButton("xMinus", fvec2(-0.75f, 0.025f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("quad3dPropertiesMenu")->createButton("yMinus", fvec2(-0.75f, -0.225f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("quad3dPropertiesMenu")->createButton("zMinus", fvec2(-0.75f, -0.475f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("quad3dPropertiesMenu")->createInputBox("x", fvec2(0.0f, 0.025f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("quad3dPropertiesMenu")->createInputBox("y", fvec2(0.0f, -0.225f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("quad3dPropertiesMenu")->createInputBox("z", fvec2(0.0f, -0.475f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("quad3dPropertiesMenu")->createButton("animation2d", fvec2(0.0f, -0.625f), fvec2(1.875f, 0.1f), "", fvec3(0.0f, 0.0f, 0.75f), fvec3(0.25f, 0.25f, 1.0f), "Start Animation2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dPropertiesMenu")->createButton("freeze", fvec2(0.0f, -0.775f), fvec2(0.75f, 0.1f), "", fvec3(0.0f, 0.0f, 0.75f), fvec3(0.25f, 0.25f, 1.0f), "Freeze", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad3dPropertiesMenu")->createButton("delete", fvec2(0.0f, -0.925f), fvec2(0.75f, 0.1f), "", fvec3(0.75f, 0.0f, 0.0f), fvec3(1.0f, 0.25f, 0.25f), "Delete", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("text3dPropertiesMenu");
	leftWindow->getScreen("text3dPropertiesMenu")->createTextField("title", fvec2(0.0f, 0.95f), fvec2(1.375f, 0.1f), "Text3D Menu", fvec3(0.0f, 1.0f, 0.0f), true);
	leftWindow->getScreen("text3dPropertiesMenu")->createButton("position", fvec2(0.0f, 0.8f), fvec2(0.75f, 0.2f), "position.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("text3dPropertiesMenu")->createButton("rotation", fvec2(0.0f, 0.55f), fvec2(0.75f, 0.2f), "rotation.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("text3dPropertiesMenu")->createButton("size", fvec2(0.0f, 0.3f), fvec2(0.75f, 0.2f), "size.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("text3dPropertiesMenu")->createTextField("x", fvec2(0.0f, 0.135f), fvec2(0.25f, 0.1f), "X", fvec3(1.0f), true);
	leftWindow->getScreen("text3dPropertiesMenu")->createTextField("y", fvec2(0.0f, -0.115f), fvec2(0.25f, 0.1f), "Y", fvec3(1.0f), true);
	leftWindow->getScreen("text3dPropertiesMenu")->createTextField("z", fvec2(0.0f, -0.365f), fvec2(0.25f, 0.1f), "Z", fvec3(1.0f), true);
	leftWindow->getScreen("text3dPropertiesMenu")->createButton("xPlus", fvec2(0.75f, 0.025f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("text3dPropertiesMenu")->createButton("yPlus", fvec2(0.75f, -0.225f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("text3dPropertiesMenu")->createButton("zPlus", fvec2(0.75f, -0.475f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("text3dPropertiesMenu")->createButton("xMinus", fvec2(-0.75f, 0.025f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("text3dPropertiesMenu")->createButton("yMinus", fvec2(-0.75f, -0.225f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("text3dPropertiesMenu")->createButton("zMinus", fvec2(-0.75f, -0.475f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("text3dPropertiesMenu")->createInputBox("x", fvec2(0.0f, 0.025f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("text3dPropertiesMenu")->createInputBox("y", fvec2(0.0f, -0.225f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("text3dPropertiesMenu")->createInputBox("z", fvec2(0.0f, -0.475f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("text3dPropertiesMenu")->createButton("content", fvec2(0.0f, -0.625f), fvec2(0.875f, 0.1f), "", fvec3(0.0f, 0.0f, 0.75f), fvec3(0.25f, 0.25f, 1.0f), "Content", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dPropertiesMenu")->createButton("freeze", fvec2(0.0f, -0.775f), fvec2(0.75f, 0.1f), "", fvec3(0.0f, 0.0f, 0.75f), fvec3(0.25f, 0.25f, 1.0f), "Freeze", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text3dPropertiesMenu")->createButton("delete", fvec2(0.0f, -0.925f), fvec2(0.75f, 0.1f), "", fvec3(0.75f, 0.0f, 0.0f), fvec3(1.0f, 0.25f, 0.25f), "Delete", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("aabbPropertiesMenu");
	leftWindow->getScreen("aabbPropertiesMenu")->createTextField("title", fvec2(0.0f, 0.95f), fvec2(1.125f, 0.1f), "AABB Menu", fvec3(0.0f, 1.0f, 0.0f), true);
	leftWindow->getScreen("aabbPropertiesMenu")->createButton("position", fvec2(0.0f, 0.8f), fvec2(0.75f, 0.2f), "position.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("aabbPropertiesMenu")->createButton("size", fvec2(0.0f, 0.55f), fvec2(0.75f, 0.2f), "size.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("aabbPropertiesMenu")->createTextField("x", fvec2(0.0f, 0.385f), fvec2(0.25f, 0.1f), "X", fvec3(1.0f), true);
	leftWindow->getScreen("aabbPropertiesMenu")->createTextField("y", fvec2(0.0f, 0.135f), fvec2(0.25f, 0.1f), "Y", fvec3(1.0f), true);
	leftWindow->getScreen("aabbPropertiesMenu")->createTextField("z", fvec2(0.0f, -0.115f), fvec2(0.25f, 0.1f), "Z", fvec3(1.0f), true);
	leftWindow->getScreen("aabbPropertiesMenu")->createButton("xPlus", fvec2(0.75f, 0.275f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("aabbPropertiesMenu")->createButton("yPlus", fvec2(0.75f, 0.025f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("aabbPropertiesMenu")->createButton("zPlus", fvec2(0.75f, -0.225f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("aabbPropertiesMenu")->createButton("xMinus", fvec2(-0.75f, 0.275f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("aabbPropertiesMenu")->createButton("yMinus", fvec2(-0.75f, 0.025f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("aabbPropertiesMenu")->createButton("zMinus", fvec2(-0.75f, -0.225f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("aabbPropertiesMenu")->createInputBox("x", fvec2(0.0f, 0.275f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("aabbPropertiesMenu")->createInputBox("y", fvec2(0.0f, 0.025f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("aabbPropertiesMenu")->createInputBox("z", fvec2(0.0f, -0.225f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("aabbPropertiesMenu")->createButton("delete", fvec2(0.0f, -0.375f), fvec2(0.75f, 0.1f), "", fvec3(0.75f, 0.0f, 0.0f), fvec3(1.0f, 0.25f, 0.25f), "Delete", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("pointlightPropertiesMenu");
	leftWindow->getScreen("pointlightPropertiesMenu")->createTextField("title", fvec2(0.0f, 0.95f), fvec2(1.875f, 0.1f), "Pointlight Menu", fvec3(0.0f, 1.0f, 0.0f), true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createButton("position", fvec2(0.0f, 0.8f), fvec2(0.75f, 0.2f), "position.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createButton("radius", fvec2(0.0f, 0.6f), fvec2(0.75f, 0.2f), "radius.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createButton("color", fvec2(0.0f, 0.4f), fvec2(0.75f, 0.2f), "color.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createTextField("x", fvec2(0.0f, 0.235f), fvec2(0.25f, 0.1f), "X", fvec3(1.0f), true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createTextField("y", fvec2(0.0f, 0.01f), fvec2(0.25f, 0.1f), "Y", fvec3(1.0f), true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createTextField("z", fvec2(0.0f, -0.215f), fvec2(0.25f, 0.1f), "Z", fvec3(1.0f), true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createButton("xPlus", fvec2(0.75f, 0.125f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createButton("yPlus", fvec2(0.75f, -0.1f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createButton("zPlus", fvec2(0.75f, -0.325f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createButton("xMinus", fvec2(-0.75f, 0.125f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createButton("yMinus", fvec2(-0.75f, -0.1f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createButton("zMinus", fvec2(-0.75f, -0.325f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createInputBox("x", fvec2(0.0f, 0.125f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createInputBox("y", fvec2(0.0f, -0.1f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createInputBox("z", fvec2(0.0f, -0.325f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createTextField("intensity", fvec2(0.0f, -0.44f), fvec2(1.125f, 0.1f), "Intensity", fvec3(1.0f), true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createButton("intensityPlus", fvec2(0.75f, -0.55f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createButton("intensityMinus", fvec2(-0.75f, -0.55f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createInputBox("intensity", fvec2(0.0f, -0.55f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createButton("shape", fvec2(0.0f, -0.725f), fvec2(0.75f, 0.2f), "shape_circle.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("pointlightPropertiesMenu")->createButton("delete", fvec2(0.0f, -0.91f), fvec2(0.75f, 0.1f), "", fvec3(0.75f, 0.0f, 0.0f), fvec3(1.0f, 0.25f, 0.25f), "Delete", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("spotlightPropertiesMenu");
	leftWindow->getScreen("spotlightPropertiesMenu")->createTextField("title", fvec2(0.0f, 0.95f), fvec2(1.75f, 0.1f), "Spotlight Menu", fvec3(0.0f, 1.0f, 0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("position", fvec2(-0.5f, 0.8f), fvec2(0.75f, 0.2f), "position.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("color", fvec2(0.5f, 0.8f), fvec2(0.75f, 0.2f), "color.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createTextField("x", fvec2(0.0f, 0.725f), fvec2(0.25f, 0.1f), "X", fvec3(1.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createTextField("y", fvec2(0.0f, 0.525f), fvec2(0.25f, 0.1f), "Y", fvec3(1.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createTextField("z", fvec2(0.0f, 0.325f), fvec2(0.25f, 0.1f), "Z", fvec3(1.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("xPlus", fvec2(0.75f, 0.625f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("yPlus", fvec2(0.75f, 0.425f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("zPlus", fvec2(0.75f, 0.225f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("xMinus", fvec2(-0.75f, 0.625f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("yMinus", fvec2(-0.75f, 0.425f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("zMinus", fvec2(-0.75f, 0.225f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createInputBox("x", fvec2(0.0f, 0.625f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createInputBox("y", fvec2(0.0f, 0.425f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createInputBox("z", fvec2(0.0f, 0.225f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createTextField("yaw", fvec2(0.0f, 0.125f), fvec2(0.375f, 0.1f), "Yaw", fvec3(1.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("yawPlus", fvec2(0.75f, 0.025f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("yawMinus", fvec2(-0.75f, 0.025f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createInputBox("yaw", fvec2(0.0f, 0.025f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createTextField("pitch", fvec2(0.0f, -0.075f), fvec2(0.625f, 0.1f), "Pitch", fvec3(1.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("pitchPlus", fvec2(0.75f, -0.175f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("pitchMinus", fvec2(-0.75f, -0.175f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createInputBox("pitch", fvec2(0.0f, -0.175f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createTextField("intensity", fvec2(0.0f, -0.275f), fvec2(1.125f, 0.1f), "Intensity", fvec3(1.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("intensityPlus", fvec2(0.75f, -0.375f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("intensityMinus", fvec2(-0.75f, -0.375f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createInputBox("intensity", fvec2(0.0f, -0.375f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createTextField("angle", fvec2(0.0f, -0.475f), fvec2(0.625f, 0.1f), "Angle", fvec3(1.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("anglePlus", fvec2(0.75f, -0.575f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("angleMinus", fvec2(-0.75f, -0.575f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createInputBox("angle", fvec2(0.0f, -0.575f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createTextField("distance", fvec2(0.0f, -0.675f), fvec2(1.0f, 0.1f), "Distance", fvec3(1.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("distancePlus", fvec2(0.75f, -0.775f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("distanceMinus", fvec2(-0.75f, -0.775f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createInputBox("distance", fvec2(0.0f, -0.775f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("spotlightPropertiesMenu")->createButton("delete", fvec2(0.0f, -0.915f), fvec2(0.75f, 0.1f), "", fvec3(0.75f, 0.0f, 0.0f), fvec3(1.0f, 0.25f, 0.25f), "Delete", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("captorPropertiesMenu");
	leftWindow->getScreen("captorPropertiesMenu")->createTextField("title", fvec2(0.0f, 0.95f), fvec2(1.375f, 0.1f), "Captor Menu", fvec3(0.0f, 1.0f, 0.0f), true);
	leftWindow->getScreen("captorPropertiesMenu")->createTextField("x", fvec2(0.0f, 0.81f), fvec2(0.25f, 0.1f), "X", fvec3(1.0f), true);
	leftWindow->getScreen("captorPropertiesMenu")->createTextField("y", fvec2(0.0f, 0.56f), fvec2(0.25f, 0.1f), "Y", fvec3(1.0f), true);
	leftWindow->getScreen("captorPropertiesMenu")->createTextField("z", fvec2(0.0f, 0.31f), fvec2(0.25f, 0.1f), "Z", fvec3(1.0f), true);
	leftWindow->getScreen("captorPropertiesMenu")->createButton("xPlus", fvec2(0.75f, 0.7f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("captorPropertiesMenu")->createButton("yPlus", fvec2(0.75f, 0.45f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("captorPropertiesMenu")->createButton("zPlus", fvec2(0.75f, 0.2f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("captorPropertiesMenu")->createButton("xMinus", fvec2(-0.75f, 0.7f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("captorPropertiesMenu")->createButton("yMinus", fvec2(-0.75f, 0.45f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("captorPropertiesMenu")->createButton("zMinus", fvec2(-0.75f, 0.2f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("captorPropertiesMenu")->createInputBox("x", fvec2(0.0f, 0.7f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("captorPropertiesMenu")->createInputBox("y", fvec2(0.0f, 0.45f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("captorPropertiesMenu")->createInputBox("z", fvec2(0.0f, 0.2f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("captorPropertiesMenu")->createButton("exception", fvec2(0.0f, 0.05f), fvec2(1.5f, 0.1f), "", fvec3(0.0f, 0.0f, 0.75f), fvec3(0.25f, 0.25f, 1.0f), "Exception", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("captorPropertiesMenu")->createButton("capture", fvec2(0.0f, -0.1f), fvec2(0.875f, 0.1f), "", fvec3(0.0f, 0.0f, 0.75f), fvec3(0.25f, 0.25f, 1.0f), "Capture", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("captorPropertiesMenu")->createButton("delete", fvec2(0.0f, -0.25f), fvec2(0.75f, 0.1f), "", fvec3(0.75f, 0.0f, 0.0f), fvec3(1.0f, 0.25f, 0.25f), "Delete", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("sound3dPropertiesMenu");
	leftWindow->getScreen("sound3dPropertiesMenu")->createTextField("title", fvec2(0.0f, 0.95f), fvec2(1.5f, 0.1f), "Sound3D Menu", fvec3(0.0f, 1.0f, 0.0f), true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createTextField("x", fvec2(0.0f, 0.81f), fvec2(0.25f, 0.1f), "X", fvec3(1.0f), true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createTextField("y", fvec2(0.0f, 0.56f), fvec2(0.25f, 0.1f), "Y", fvec3(1.0f), true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createTextField("z", fvec2(0.0f, 0.31f), fvec2(0.25f, 0.1f), "Z", fvec3(1.0f), true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createButton("xPlus", fvec2(0.75f, 0.7f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createButton("yPlus", fvec2(0.75f, 0.45f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createButton("zPlus", fvec2(0.75f, 0.2f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createButton("xMinus", fvec2(-0.75f, 0.7f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createButton("yMinus", fvec2(-0.75f, 0.45f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createButton("zMinus", fvec2(-0.75f, 0.2f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createInputBox("x", fvec2(0.0f, 0.7f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createInputBox("y", fvec2(0.0f, 0.45f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createInputBox("z", fvec2(0.0f, 0.2f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createTextField("distance", fvec2(0.0f, 0.06f), fvec2(1.5f, 0.1f), "Max distance", fvec3(1.0f), true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createButton("distancePlus", fvec2(0.75f, -0.05f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createButton("distanceMinus", fvec2(-0.75f, -0.05f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createInputBox("distance", fvec2(0.0f, -0.05f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createTextField("volume", fvec2(0.0f, -0.19f), fvec2(1.25f, 0.1f), "Max volume", fvec3(1.0f), true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createButton("volumePlus", fvec2(0.75f, -0.3f), fvec2(0.5f, 0.15f), "plus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createButton("volumeMinus", fvec2(-0.75f, -0.3f), fvec2(0.5f, 0.15f), "minus.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createInputBox("volume", fvec2(0.0f, -0.3f), fvec2(1.0f, 0.1f), fvec3(0.25f), fvec3(0.75f), fvec3(1.0f), fvec3(0.0f), 7, false, true, false, true);
	leftWindow->getScreen("sound3dPropertiesMenu")->createButton("delete", fvec2(0.0f, -0.45f), fvec2(0.75f, 0.1f), "", fvec3(0.75f, 0.0f, 0.0f), fvec3(1.0f, 0.25f, 0.25f), "Delete", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("empty");
	rightWindow->setActiveScreen("worldEditorMenuMain");
}

void WorldEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	leftWindow->deleteScreen("modelPropertiesMenu");
	leftWindow->deleteScreen("quad3dPropertiesMenu");
	leftWindow->deleteScreen("text3dPropertiesMenu");
	leftWindow->deleteScreen("aabbPropertiesMenu");
	leftWindow->deleteScreen("pointlightPropertiesMenu");
	leftWindow->deleteScreen("spotlightPropertiesMenu");
	leftWindow->deleteScreen("captorPropertiesMenu");
	leftWindow->deleteScreen("sound3dPropertiesMenu");

	rightWindow->deleteScreen("worldEditorMenuMain");
	rightWindow->deleteScreen("worldEditorMenuChoice");
	rightWindow->deleteScreen("worldEditorMenuSky");
	rightWindow->deleteScreen("worldEditorMenuSkyPlace");
	rightWindow->deleteScreen("worldEditorMenuTerrain");
	rightWindow->deleteScreen("worldEditorMenuTerrainPlace");
	rightWindow->deleteScreen("worldEditorMenuWater");
	rightWindow->deleteScreen("worldEditorMenuWaterPlace");
	rightWindow->deleteScreen("worldEditorMenuModel");
	rightWindow->deleteScreen("worldEditorMenuModelPlace");
	rightWindow->deleteScreen("worldEditorMenuModelChoice");
	rightWindow->deleteScreen("worldEditorMenuQuad3d");
	rightWindow->deleteScreen("worldEditorMenuQuad3dPlace");
	rightWindow->deleteScreen("worldEditorMenuQuad3dChoice");
	rightWindow->deleteScreen("worldEditorMenuText3d");
	rightWindow->deleteScreen("worldEditorMenuText3dPlace");
	rightWindow->deleteScreen("worldEditorMenuText3dChoice");
	rightWindow->deleteScreen("worldEditorMenuAabb");
	rightWindow->deleteScreen("worldEditorMenuAabbPlace");
	rightWindow->deleteScreen("worldEditorMenuAabbChoice");
	rightWindow->deleteScreen("worldEditorMenuPointlight");
	rightWindow->deleteScreen("worldEditorMenuPointlightChoice");
	rightWindow->deleteScreen("worldEditorMenuSpotlight");
	rightWindow->deleteScreen("worldEditorMenuSpotlightChoice");
	rightWindow->deleteScreen("worldEditorMenuCaptor");
	rightWindow->deleteScreen("worldEditorMenuCaptorChoice");
	rightWindow->deleteScreen("worldEditorMenuSound3d");
	rightWindow->deleteScreen("worldEditorMenuSound3dPlace");
	rightWindow->deleteScreen("worldEditorMenuSound3dChoice");
	rightWindow->deleteScreen("worldEditorMenuSettings");
	rightWindow->deleteScreen("worldEditorMenuSettingsLighting");
	rightWindow->deleteScreen("worldEditorMenuSettingsLightingAmbient");
	rightWindow->deleteScreen("worldEditorMenuSettingsLightingDirectional");
	rightWindow->deleteScreen("worldEditorMenuSettingsGraphics");
	rightWindow->deleteScreen("worldEditorMenuSettingsGraphicsShadows");
	rightWindow->deleteScreen("worldEditorMenuSettingsGraphicsReflections");
	rightWindow->deleteScreen("worldEditorMenuSettingsGraphicsRefractions");
	rightWindow->deleteScreen("worldEditorMenuSettingsGraphicsDof");
	rightWindow->deleteScreen("worldEditorMenuSettingsGraphicsFog");
	rightWindow->deleteScreen("worldEditorMenuSettingsGraphicsLensFlare");
	rightWindow->deleteScreen("worldEditorMenuSettingsGraphicsSkyExposure");
	rightWindow->deleteScreen("worldEditorMenuSettingsGraphicsBloom");

	leftWindow->setActiveScreen("main");
	rightWindow->setActiveScreen("main");
}