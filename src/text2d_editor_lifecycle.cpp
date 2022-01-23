#define TW(text) VPC::calculateTextWidth(text, CW)

#include "text2d_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

void Text2dEditor::load()
{
	_loadGUI();

	_fe3d->camera_reset();
	_fe3d->camera_setYaw(270.0f);

	_gui->getOverlay()->createTextField("textID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true);

	_isEditorLoaded = true;
}

void Text2dEditor::unload()
{
	for(const auto& ID : _loadedTextIDs)
	{
		_fe3d->text2d_delete(ID);
	}

	_unloadGUI();

	_gui->getOverlay()->deleteTextField("textID");

	_loadedTextIDs.clear();
	_currentTextID = "";
	_hoveredTextID = "";
	_isEditorLoaded = false;
	_isCreatingText = false;
	_isChoosingText = false;
	_isDeletingText = false;
}

void Text2dEditor::_loadGUI()
{
	auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("text2dEditorMenuMain");
	leftWindow->getScreen("text2dEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create Text"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Text", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit Text"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Text", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete Text"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Text", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("text2dEditorMenuChoice");
	leftWindow->getScreen("text2dEditorMenuChoice")->createButton("color", fvec2(0.0f, positions[0]), fvec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuChoice")->createButton("opacity", fvec2(0.0f, positions[1]), fvec2(TW("Opacity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Opacity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("text2dEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
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