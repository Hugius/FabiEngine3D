#include "sky_editor.hpp"
#include "logger.hpp"

void SkyEditor::_updateMainMenu()
{
	auto screen = _gui->getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "skyEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->createValueForm("skyCreate", "Create Sky", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingSky = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto IDs = getLoadedIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui->getOverlay()->createChoiceForm("skyList", "Edit Sky", fvec2(-0.5f, 0.1f), IDs);
			_isChoosingSky = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto IDs = getLoadedIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui->getOverlay()->createChoiceForm("skyList", "Delete Sky", fvec2(-0.5f, 0.1f), IDs);
			_isChoosingSky = true;
			_isDeletingSky = true;
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("back"))
		{
			_gui->getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveToFile();
			unload();
			return;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("back"))
		{
			_gui->getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
	}
}

void SkyEditor::_updateChoiceMenu()
{
	auto screen = _gui->getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "skyEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuMain");
			_fe3d->text_setVisible(_gui->getOverlay()->getTextField("skyID")->getEntityID(), false);
			_fe3d->sky_setWireframed(_currentSkyID, false);
			_fe3d->sky_selectMainSky("");
			_currentSkyID = "";
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("texturing")->isHovered())
		{
			_gui->getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuTexturing");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("miscellaneous")->isHovered())
		{
			_gui->getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuMiscellaneous");
		}

		screen->getButton("miscellaneous")->setHoverable(_fe3d->sky_isExisting(_currentSkyID));
	}
}