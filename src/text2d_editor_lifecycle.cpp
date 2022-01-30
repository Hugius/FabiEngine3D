#define TW(text) (static_cast<float>(string(text).size()) * CW)

#include "text2d_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void Text2dEditor::load()
{
	_loadGUI();

	_fe3d->camera_reset();
	_fe3d->camera_setYaw(270.0f);

	_gui->getOverlay()->createTextField("textId", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true);

	_isEditorLoaded = true;
}

void Text2dEditor::unload()
{
	for(const auto& id : _loadedTextIds)
	{
		_fe3d->text2d_delete(id);
	}

	_unloadGUI();

	_gui->getOverlay()->deleteTextField("textId");

	_loadedTextIds.clear();
	_currentTextId = "";
	_hoveredTextId = "";
	_isEditorLoaded = false;
	_isCreatingText = false;
	_isChoosingText = false;
	_isDeletingText = false;
}

void Text2dEditor::_loadGUI()
{
	auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = Math::calculateDistributedPositions(4, CH);
	leftWindow->createScreen("text2dEditorMenuMain");
	leftWindow->getScreen("text2dEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create Text"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Text", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit Text"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Text", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete Text"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Text", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(3, CH);
	leftWindow->createScreen("text2dEditorMenuChoice");
	leftWindow->getScreen("text2dEditorMenuChoice")->createButton("color", fvec2(0.0f, positions[0]), fvec2(TW("Color"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuChoice")->createButton("opacity", fvec2(0.0f, positions[1]), fvec2(TW("Opacity"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Opacity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);
}

void Text2dEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("text2dEditorMenuMain");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("text2dEditorMenuChoice");
}

void Text2dEditor::update()
{
	if(_isEditorLoaded)
	{
		_updateMainMenu();
	}
	if(_isEditorLoaded)
	{
		_updateChoiceMenu();
	}
	if(_isEditorLoaded)
	{
		_updateTextCreating();
	}
	if(_isEditorLoaded)
	{
		_updateTextChoosing();
	}
	if(_isEditorLoaded)
	{
		_updateTextDeleting();
	}
}