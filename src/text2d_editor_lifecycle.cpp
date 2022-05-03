#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "text2d_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void Text2dEditor::_load()
{
	_fe3d->camera_setYaw(270.0f);

	_gui->getOverlay()->createTextField("text2dId", fvec2(0.0f, 0.85f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
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
	const auto window = _gui->getLeftViewport()->getWindow("main");

	auto positions = Mathematics::calculateDistributedPositions(4, CH, false);
	window->createScreen("text2dEditorMenuMain");
	window->getScreen("text2dEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create Text2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Text2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("text2dEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Text2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Text2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("text2dEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), TEXT_SIZE("Delete Text2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Text2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("text2dEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(5, CH, false);
	window->createScreen("text2dEditorMenuChoice");
	window->getScreen("text2dEditorMenuChoice")->createButton("color", fvec2(0.0f, positions[0]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("text2dEditorMenuChoice")->createButton("opacity", fvec2(0.0f, positions[1]), TEXT_SIZE("Opacity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Opacity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("text2dEditorMenuChoice")->createButton("isHorizontallyFlipped", fvec2(0.0f, positions[2]), TEXT_SIZE("Flipped X: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Flipped X: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("text2dEditorMenuChoice")->createButton("isVerticallyFlipped", fvec2(0.0f, positions[3]), TEXT_SIZE("Flipped Y: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Flipped Y: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("text2dEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[4]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);
}

void Text2dEditor::_unloadGUI()
{
	const auto window = _gui->getLeftViewport()->getWindow("main");

	window->deleteScreen("text2dEditorMenuMain");
	window->deleteScreen("text2dEditorMenuChoice");
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