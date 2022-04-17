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
			_gui->getOverlay()->openValueForm("createQuad", "Create Quad3D", "", fvec2(0.0f, 0.1f), 10, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto ids = _loadedEntityIds;

			for(auto & id : ids)
			{
				id = id.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editQuad", "Edit Quad3D", fvec2(-0.5f, 0.1f), ids);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto ids = _loadedEntityIds;

			for(auto & id : ids)
			{
				id = id.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteQuad", "Delete Quad3D", fvec2(-0.5f, 0.1f), ids);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "back") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
				saveEntitiesToFile();
				unload();
			}
			if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
				unload();
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
			_fe3d->quad3d_setWireframed(_currentQuadId, false);
			_fe3d->quad3d_setVisible(_currentQuadId, false);
			_gui->getOverlay()->getTextField("quadId")->setVisible(false);
			_currentQuadId = "";
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
	}
}