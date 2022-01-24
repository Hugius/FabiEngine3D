#include "quad3d_editor.hpp"

void Quad3dEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad3dEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->createValueForm("quad3dCreate", "Create Quad3D", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingQuad3d = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto IDs = getLoadedIDs();
			for(auto& id : IDs)
			{
				id = id.substr(1);
			}
			_gui->getOverlay()->createChoiceForm("quad3dList", "Edit Quad3D", fvec2(-0.5f, 0.1f), IDs);
			_isChoosingQuad3d = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto IDs = getLoadedIDs();
			for(auto& id : IDs)
			{
				id = id.substr(1);
			}
			_gui->getOverlay()->createChoiceForm("quad3dList", "Delete Quad3D", fvec2(-0.5f, 0.1f), IDs);
			_isChoosingQuad3d = true;
			_isDeletingQuad3d = true;
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("back"))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
			saveToFile();
			unload();
			return;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("back"))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
	}
}

void Quad3dEditor::_updateChoiceMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad3dEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->quad3d_setWireframed(_currentQuadId, false);
			_fe3d->quad3d_setVisible(_currentQuadId, false);
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadId")->getEntityId(), false);
			_currentQuadId = "";
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuMain");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("texturing")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuTexturing");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lighting")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuLighting");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("miscellaneous")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuMiscellaneous");
		}
	}
}