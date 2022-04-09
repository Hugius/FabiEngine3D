#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "text2d_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void Text2dEditor::_load()
{
	_fe3d->camera_reset();
	_fe3d->camera_setYaw(270.0f);

	_gui->getOverlay()->createTextField("textId", fvec2(0.0f, 0.85f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
}

void Text2dEditor::_unload()
{
	for(const auto & id : _loadedEntityIds)
	{
		_fe3d->text2d_delete(id);
	}

	_gui->getOverlay()->deleteTextField("textId");

	_loadedEntityIds.clear();
	_currentTextId = "";
	_hoveredTextId = "";
}

void Text2dEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = Mathematics::calculateDistributedPositions(4, CH, false);
	leftWindow->createScreen("text2dEditorMenuMain");
	leftWindow->getScreen("text2dEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create Text"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Text", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Text"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Text", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), TEXT_SIZE("Delete Text"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Text", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(3, CH, false);
	leftWindow->createScreen("text2dEditorMenuChoice");
	leftWindow->getScreen("text2dEditorMenuChoice")->createButton("color", fvec2(0.0f, positions[0]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuChoice")->createButton("opacity", fvec2(0.0f, positions[1]), TEXT_SIZE("Opacity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Opacity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);
}

void Text2dEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("text2dEditorMenuMain");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("text2dEditorMenuChoice");
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
		_updateTextCreating();
	}
	if(isLoaded())
	{
		_updateTextChoosing();
	}
	if(isLoaded())
	{
		_updateTextDeleting();
	}
}