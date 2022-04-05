#include "sky_editor.hpp"
#include "logger.hpp"

void SkyEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "skyEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("back", "Save Changes?", "Yes", "No", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("skyCreate", "Create Sky", "", fvec2(0.0f, 0.1f), 10, true, true, false);
			_isCreatingSky = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto ids = _loadedEntityIds;
			for(auto & id : ids)
			{
				id = id.substr(1);
			}
			_gui->getOverlay()->openChoiceForm("skyList", "Edit Sky", fvec2(-0.5f, 0.1f), ids);
			_isChoosingSky = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto ids = _loadedEntityIds;
			for(auto & id : ids)
			{
				id = id.substr(1);
			}
			_gui->getOverlay()->openChoiceForm("skyList", "Delete Sky", fvec2(-0.5f, 0.1f), ids);
			_isChoosingSky = true;
			_isDeletingSky = true;
		}

		if(_gui->getOverlay()->getAnswerFormId() == "back")
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
				saveEntitiesToFile();
				unload();
				return;
			}
			if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
				unload();
				return;
			}
		}
	}
}

void SkyEditor::_updateChoiceMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "skyEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("skyEditorMenuMain");
			_gui->getOverlay()->getTextField("skyId")->setVisible(false);
			_fe3d->sky_setWireframed(_currentSkyId, false);
			_fe3d->sky_select("");
			_currentSkyId = "";
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("texturing")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("skyEditorMenuTexturing");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("miscellaneous")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("skyEditorMenuMiscellaneous");
		}
	}
}