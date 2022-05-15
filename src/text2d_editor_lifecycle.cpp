#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)
#define POSITIONS(count) Mathematics::calculateDistributedPositions(count, CH, false)

#include "text2d_editor.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void Text2dEditor::_load()
{
	_fe3d->camera_setYaw(270.0f);

	_gui->getOverlay()->createTextField("text2dId", fvec2(0.0f, 0.85f), fvec2(0.025f, 0.1f), "", fvec3(1.0f), true);
}

void Text2dEditor::_unload()
{
	for(const auto & text2dId : _loadedText2dIds)
	{
		_fe3d->text2d_delete(text2dId);
	}

	_fe3d->camera_reset();

	_gui->getOverlay()->deleteTextField("text2dId");

	_loadedText2dIds.clear();
}

void Text2dEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	leftWindow->createScreen("text2dEditorMenuMain");
	leftWindow->getScreen("text2dEditorMenuMain")->createButton("create", fvec2(0.0f, POSITIONS(4)[0]), TEXT_SIZE("Create Text2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Text2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuMain")->createButton("edit", fvec2(0.0f, POSITIONS(4)[1]), TEXT_SIZE("Edit Text2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Text2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuMain")->createButton("delete", fvec2(0.0f, POSITIONS(4)[2]), TEXT_SIZE("Delete Text2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Text2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuMain")->createButton("back", fvec2(0.0f, POSITIONS(4)[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("text2dEditorMenuChoice");
	leftWindow->getScreen("text2dEditorMenuChoice")->createButton("color", fvec2(0.0f, POSITIONS(5)[0]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuChoice")->createButton("opacity", fvec2(0.0f, POSITIONS(5)[1]), TEXT_SIZE("Opacity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Opacity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuChoice")->createButton("isHorizontallyFlipped", fvec2(0.0f, POSITIONS(5)[2]), TEXT_SIZE("Flipped X: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Flipped X: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuChoice")->createButton("isVerticallyFlipped", fvec2(0.0f, POSITIONS(5)[3]), TEXT_SIZE("Flipped Y: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Flipped Y: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuChoice")->createButton("back", fvec2(0.0f, POSITIONS(5)[4]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("text2dEditorMenuMain");
	rightWindow->setActiveScreen("empty");
}

void Text2dEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	leftWindow->deleteScreen("text2dEditorMenuMain");
	leftWindow->deleteScreen("text2dEditorMenuChoice");

	leftWindow->setActiveScreen("main");
	rightWindow->setActiveScreen("main");
}

void Text2dEditor::update()
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
		_updateText2dCreating();
	}

	if(isLoaded())
	{
		_updateText2dChoosing();
	}

	if(isLoaded())
	{
		_updateText2dDeleting();
	}
}