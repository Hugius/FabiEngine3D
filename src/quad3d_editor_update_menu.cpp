#include "quad3d_editor.hpp"

void Quad3dEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad3dEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("back", "Save Changes?", "Yes", "No", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createQuad3d", "Create Quad3D", "", fvec2(0.0f, 0.1f), 10, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto quad3dIds = _loadedQuad3dIds;

			for(auto & quad3dId : quad3dIds)
			{
				quad3dId = quad3dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editQuad3d", "Edit Quad3D", fvec2(-0.5f, 0.1f), quad3dIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto quad3dIds = _loadedQuad3dIds;

			for(auto & quad3dId : quad3dIds)
			{
				quad3dId = quad3dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteQuad3d", "Delete Quad3D", fvec2(-0.5f, 0.1f), quad3dIds);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "back") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveQuad3dsToFile();
				unload();

				return;
			}
			if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				unload();

				return;
			}
		}
	}
}

void Quad3dEditor::_updateChoiceMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad3dEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->quad3d_setWireframed(_currentQuad3dId, false);
			_fe3d->quad3d_setVisible(_currentQuad3dId, false);
			_gui->getOverlay()->getTextField("quad3dId")->setVisible(false);
			_currentQuad3dId = "";
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuMain");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("texturing")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuTexturing");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("lighting")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuLighting");
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