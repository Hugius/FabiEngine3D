#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)
#define POSITIONS(count) Mathematics::calculateDistributedPositions(count, CH, false)

#include "sky_editor.hpp"
#include "tools.hpp"

void SkyEditor::_load()
{
	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);

	_gui->getOverlay()->createTextField(SKY_TITLE_ID, SKY_TITLE_POSITION, SKY_TITLE_SIZE, "", fvec3(1.0f), true);
}

void SkyEditor::_unload()
{
	for(const auto & skyId : _loadedSkyIds)
	{
		_fe3d->sky_delete(skyId);
	}

	_fe3d->camera_reset();

	_gui->getOverlay()->deleteTextField(SKY_TITLE_ID);

	_loadedSkyIds.clear();
}

void SkyEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	leftWindow->createScreen("skyEditorMenuMain");
	leftWindow->getScreen("skyEditorMenuMain")->createButton("create", fvec2(0.0f, POSITIONS(4)[0]), TEXT_SIZE("Create Sky"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuMain")->createButton("edit", fvec2(0.0f, POSITIONS(4)[1]), TEXT_SIZE("Edit Sky"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuMain")->createButton("delete", fvec2(0.0f, POSITIONS(4)[2]), TEXT_SIZE("Delete Sky"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuMain")->createButton("back", fvec2(0.0f, POSITIONS(4)[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("skyEditorMenuChoice");
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("texturing", fvec2(0.0f, POSITIONS(4)[0]), TEXT_SIZE("Texturing"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Texturing", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("graphics", fvec2(0.0f, POSITIONS(4)[1]), TEXT_SIZE("Graphics"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Graphics", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("miscellaneous", fvec2(0.0f, POSITIONS(4)[2]), TEXT_SIZE("Miscellaneous"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Miscellaneous", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("back", fvec2(0.0f, POSITIONS(4)[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("skyEditorMenuTexturing");
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("leftMap", fvec2(0.0f, POSITIONS(13)[0]), TEXT_SIZE("Left Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Left Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("clearLeftMap", fvec2(0.0f, POSITIONS(13)[1]), TEXT_SIZE("Clear"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("rightMap", fvec2(0.0f, POSITIONS(13)[2]), TEXT_SIZE("Right Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Right Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("clearRightMap", fvec2(0.0f, POSITIONS(13)[3]), TEXT_SIZE("Clear"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("bottomMap", fvec2(0.0f, POSITIONS(13)[4]), TEXT_SIZE("Bottom Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Bottom Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("clearBottomMap", fvec2(0.0f, POSITIONS(13)[5]), TEXT_SIZE("Clear"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("topMap", fvec2(0.0f, POSITIONS(13)[6]), TEXT_SIZE("Top Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Top Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("clearTopMap", fvec2(0.0f, POSITIONS(13)[7]), TEXT_SIZE("Clear"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("backMap", fvec2(0.0f, POSITIONS(13)[8]), TEXT_SIZE("Back Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Back Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("clearBackMap", fvec2(0.0f, POSITIONS(13)[9]), TEXT_SIZE("Clear"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("frontMap", fvec2(0.0f, POSITIONS(13)[10]), TEXT_SIZE("Front Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Front Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("clearFrontMap", fvec2(0.0f, POSITIONS(13)[11]), TEXT_SIZE("Clear"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("back", fvec2(0.0f, POSITIONS(13)[12]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("skyEditorMenuGraphics");
	leftWindow->getScreen("skyEditorMenuGraphics")->createButton("color", fvec2(0.0f, POSITIONS(3)[0]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuGraphics")->createButton("lightness", fvec2(0.0f, POSITIONS(3)[1]), TEXT_SIZE("Lightness"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lightness", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuGraphics")->createButton("back", fvec2(0.0f, POSITIONS(3)[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("skyEditorMenuMiscellaneous");
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("rotation", fvec2(0.0f, POSITIONS(3)[0]), TEXT_SIZE("Rotation"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Rotation", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("rotationOrder", fvec2(0.0f, POSITIONS(3)[1]), TEXT_SIZE("Rotation: Y X Z"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Rotation : Y X Z", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("back", fvec2(0.0f, POSITIONS(3)[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("skyEditorMenuMain");

	rightWindow->setActiveScreen("empty");
}

void SkyEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	leftWindow->deleteScreen("skyEditorMenuMain");
	leftWindow->deleteScreen("skyEditorMenuChoice");
	leftWindow->deleteScreen("skyEditorMenuTexturing");
	leftWindow->deleteScreen("skyEditorMenuGraphics");
	leftWindow->deleteScreen("skyEditorMenuMiscellaneous");

	leftWindow->setActiveScreen("main");

	rightWindow->setActiveScreen("main");
}

void SkyEditor::_update()
{
	if(isLoaded())
	{
		_updateMainMenu();
	}

	if(isLoaded())
	{
		_updateChoiceMenu();
	}

	if(isLoaded())
	{
		_updateTexturingMenu();
	}

	if(isLoaded())
	{
		_updateGraphicsMenu();
	}

	if(isLoaded())
	{
		_updateMiscellaneousMenu();
	}

	if(isLoaded())
	{
		_updateSkyCreating();
	}

	if(isLoaded())
	{
		_updateSkyChoosing();
	}

	if(isLoaded())
	{
		_updateSkyDeleting();
	}

	if(isLoaded())
	{
		_updateCamera();
	}

	if(isLoaded())
	{
		_updateMiscellaneous();
	}
}