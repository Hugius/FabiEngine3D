#include "text3d_editor.hpp"

void Text3dEditor::_updateMainMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "text3dEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("save", "Save Changes?", "Yes", "No", ANSWER_FORM_POSITION);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createText3d", "Create Text3D", "", VALUE_FORM_POSITION, VALUE_FORM_SIZE, true, true, true);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto text3dIds = _loadedText3dIds;

			for(auto & text3dId : text3dIds)
			{
				text3dId = text3dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editText3d", "Edit Text3D", LEFT_CHOICE_FORM_POSITION, text3dIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto text3dIds = _loadedText3dIds;

			for(auto & text3dId : text3dIds)
			{
				text3dId = text3dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteText3d", "Delete Text3D", LEFT_CHOICE_FORM_POSITION, text3dIds);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "save") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveText3dsToFile();

				unload();

				return;
			}
			else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				unload();

				return;
			}
		}
	}
}

void Text3dEditor::_updateChoiceMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "text3dEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->text3d_setWireframed(_currentText3dId, false);
			_fe3d->text3d_setVisible(_currentText3dId, false);

			_gui->getOverlay()->getTextField(TEXT3D_TITLE_ID)->setVisible(false);

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuMain");

			_currentText3dId = "";

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("graphics")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuGraphics");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("miscellaneous")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuMiscellaneous");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("aabb")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuAabb");
		}
	}
}