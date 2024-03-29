#include "quad3d_editor.hpp"

void Quad3dEditor::_updateMainMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad3dEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("save", "Save Changes?", "Yes", "No", ANSWER_FORM_POSITION);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createQuad3d", "Create Quad3D", "", VALUE_FORM_POSITION, VALUE_FORM_SIZE, true, true, true);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto quad3dIds = _loadedQuad3dIds;

			for(auto & quad3dId : quad3dIds)
			{
				quad3dId = quad3dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editQuad3d", "Edit Quad3D", LEFT_CHOICE_FORM_POSITION, quad3dIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto quad3dIds = _loadedQuad3dIds;

			for(auto & quad3dId : quad3dIds)
			{
				quad3dId = quad3dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteQuad3d", "Delete Quad3D", LEFT_CHOICE_FORM_POSITION, quad3dIds);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "save") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveQuad3dsToFile();

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

void Quad3dEditor::_updateChoiceMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad3dEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->quad3d_setWireframed(_currentQuad3dId, false);
			_fe3d->quad3d_setVisible(_currentQuad3dId, false);

			_gui->getOverlay()->getTextField(QUAD3D_TITLE_ID)->setVisible(false);

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuMain");

			_currentQuad3dId = "";

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("texturing")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuTexturing");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("graphics")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuGraphics");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("miscellaneous")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuMiscellaneous");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("aabb")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuAabb");
		}
	}
}