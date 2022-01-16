#define TW(text) VPC::calculateTextWidth(text, CW)

#include "text_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

void TextEditor::load()
{
	_loadGUI();

	_fe3d->camera_reset();
	_fe3d->camera_setYaw(270.0f);

	_fe3d->billboard_create(PREVIEW_BILLBOARD_ID, true);
	_fe3d->billboard_setPosition(PREVIEW_BILLBOARD_ID, PREVIEW_BILLBOARD_POSITION);
	_fe3d->billboard_setVisible(PREVIEW_BILLBOARD_ID, false);

	_gui->getOverlay()->createTextField("textID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(0.0f), true);

	_isEditorLoaded = true;
}

void TextEditor::unload()
{
	for(const auto& ID : _loadedTextIDs)
	{
		_fe3d->text_delete(ID);
	}

	_unloadGUI();

	_fe3d->billboard_delete(PREVIEW_BILLBOARD_ID);

	_gui->getOverlay()->deleteTextField("textID");

	_loadedTextIDs.clear();
	_currentTextID = "";
	_hoveredTextID = "";
	_isEditorLoaded = false;
	_isCreatingText = false;
	_isChoosingText = false;
	_isDeletingText = false;
}

void TextEditor::_loadGUI()
{
	auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("textEditorMenuMain");
	leftWindow->getScreen("textEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create Text"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Text", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("textEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit Text"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Text", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("textEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete Text"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Text", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("textEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("textEditorMenuChoice");
	leftWindow->getScreen("textEditorMenuChoice")->createButton("fontMap", fvec2(0.0f, positions[0]), fvec2(TW("Font Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Font Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quadEditorMenuChoice")->createButton("color", fvec2(0.0f, positions[1]), fvec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("textEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
}

void TextEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("textEditorMenuMain");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("textEditorMenuChoice");
}

void TextEditor::update()
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