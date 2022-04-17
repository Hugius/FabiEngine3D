#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKey::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			unload();
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createWorld", "Create World", "", fvec2(0.0f, 0.1f), 10, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto ids = _getWorldIds();
			sort(ids.begin(), ids.end());
			_gui->getOverlay()->openChoiceForm("editWorld", "Edit World", fvec2(0.0f, 0.1f), ids);
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto ids = _getWorldIds();
			sort(ids.begin(), ids.end());
			_gui->getOverlay()->openChoiceForm("deleteWorld", "Delete World", fvec2(0.0f, 0.1f), ids);
		}
	}
}

void WorldEditor::_updateChoiceMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKey::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("back", "Save Changes?", "Yes", "No", fvec2(0.0f, 0.25f));
			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("sky")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSky");
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("terrain")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuTerrain");
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("water")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuWater");
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("model")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuModel");
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("quad3d")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuQuad3d");
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("text3d")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuText3d");
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("sound")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSound");
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("pointlight")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuPointlight");
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("spotlight")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSpotlight");
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("reflection")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuReflection");
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("settings")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettings");
		}

		if((_gui->getOverlay()->getAnswerFormId() == "back") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveWorldToFile();
				clearLoadedWorld();

				_currentWorldId = "";
				_currentTemplateModelId = "";
				_currentTemplateQuadId = "";
				_currentTemplateTextId = "";
				_currentTemplateSoundId = "";
				_isPlacingPointlight = false;
				_isPlacingSpotlight = false;
				_isPlacingReflection = false;

				_fe3d->misc_setVsyncEnabled(true);

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuMain");
				_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");
			}
			if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				clearLoadedWorld();

				_currentWorldId = "";
				_currentTemplateModelId = "";
				_currentTemplateQuadId = "";
				_currentTemplateTextId = "";
				_currentTemplateSoundId = "";
				_isPlacingPointlight = false;
				_isPlacingSpotlight = false;
				_isPlacingReflection = false;

				_fe3d->misc_setVsyncEnabled(true);

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuMain");
				_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");
			}
		}
	}
}