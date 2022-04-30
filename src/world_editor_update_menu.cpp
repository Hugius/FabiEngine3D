#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			unload();

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createWorld", "Create World", "", fvec2(0.0f, 0.1f), 10, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto worldIds = _getWorldIds();
			sort(worldIds.begin(), worldIds.end());
			_gui->getOverlay()->openChoiceForm("editWorld", "Edit World", fvec2(0.0f, 0.1f), worldIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto worldIds = _getWorldIds();
			sort(worldIds.begin(), worldIds.end());
			_gui->getOverlay()->openChoiceForm("deleteWorld", "Delete World", fvec2(0.0f, 0.1f), worldIds);
		}
	}
}

void WorldEditor::_updateChoiceMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("back", "Save Changes?", "Yes", "No", fvec2(0.0f, 0.25f));

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("sky")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSky");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("terrain")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuTerrain");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("water")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuWater");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("model")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuModel");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("quad3d")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuQuad3d");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("text3d")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuText3d");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("sound3d")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSound3d");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("pointlight")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuPointlight");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("spotlight")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSpotlight");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("captor")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuCaptor");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("settings")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettings");
		}

		if((_gui->getOverlay()->getAnswerFormId() == "back") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveWorldToFile();
			}

			clearLoadedWorld();

			_fe3d->camera_reset();
			_fe3d->misc_setVsyncEnabled(true);

			_gui->getOverlay()->getTextField("selectedId")->setVisible(false);
			_gui->getOverlay()->getTextField("activeId")->setVisible(false);

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuMain");
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");

			_currentWorldId = "";
			_currentTemplateModelId = "";
			_currentTemplateQuad3dId = "";
			_currentTemplateText3dId = "";
			_currentTemplateSound3dId = "";
			_selectedModelId = "";
			_selectedQuad3dId = "";
			_selectedText3dId = "";
			_selectedPointlightId = "";
			_selectedSpotlightId = "";
			_selectedCaptorId = "";
			_selectedSound3dId = "";
			_activeModelId = "";
			_activeQuad3dId = "";
			_activeText3dId = "";
			_activePointlightId = "";
			_activeSpotlightId = "";
			_activeCaptorId = "";
			_activeSound3dId = "";
			_editorSpeed = 1.0f;
			_idCounter = 0;
			_selectedModelHighlightDirection = 1;
			_selectedQuad3dHighlightDirection = 1;
			_selectedText3dHighlightDirection = 1;
			_selectedPointlightHighlightDirection = 1;
			_selectedSpotlightHighlightDirection = 1;
			_selectedCaptorHighlightDirection = 1;
			_selectedSound3dHighlightDirection = 1;
			_activeModelHighlightDirection = 1;
			_activeQuad3dHighlightDirection = 1;
			_activeText3dHighlightDirection = 1;
			_activePointlightHighlightDirection = 1;
			_activeSpotlightHighlightDirection = 1;
			_activeCaptorHighlightDirection = 1;
			_activeSound3dHighlightDirection = 1;
			_dontResetSelectedModel = false;
			_dontResetSelectedQuad3d = false;
			_dontResetSelectedText3d = false;
			_dontResetSelectedPointlight = false;
			_dontResetSelectedSpotlight = false;
			_dontResetSelectedCaptor = false;
			_dontResetSelectedSound3d = false;
			_isPlacingPointlight = false;
			_isPlacingSpotlight = false;
			_isPlacingCaptor = false;
			_isWireframeModeEnabled = false;
			_isAabbModeEnabled = false;
			_isGridModeEnabled = false;
		}
	}
}