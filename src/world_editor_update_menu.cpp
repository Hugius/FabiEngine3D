#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateMainMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			unload();

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createWorld", "Create World", "", VALUE_FORM_POSITION, VALUE_FORM_SIZE, true, true, true);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto worldIds = _getWorldIds();

			sort(worldIds.begin(), worldIds.end());

			_gui->getOverlay()->openChoiceForm("editWorld", "Edit World", CENTER_CHOICE_FORM_POSITION, worldIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto worldIds = _getWorldIds();

			sort(worldIds.begin(), worldIds.end());

			_gui->getOverlay()->openChoiceForm("deleteWorld", "Delete World", CENTER_CHOICE_FORM_POSITION, worldIds);
		}
	}
}

void WorldEditor::_updateChoiceMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("save", "Save Changes?", "Yes", "No", ANSWER_FORM_POSITION);

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("sky")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSky");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("terrain")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuTerrain");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("water")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuWater");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("model")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuModel");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("quad3d")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuQuad3d");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("text3d")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuText3d");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("aabb")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuAabb");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("pointlight")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuPointlight");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("spotlight")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSpotlight");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("captor")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuCaptor");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("sound3d")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSound3d");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("settings")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettings");
		}

		if((_gui->getOverlay()->getAnswerFormId() == "save") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveWorldToFile();
			}

			clearLoadedWorld();

			_fe3d->camera_reset();
			_fe3d->raycast_clearCursorRay();
			_fe3d->raycast_clearTerrainIntersection();
			_fe3d->raycast_clearAabbsIntersection();
			_fe3d->collision_clearCameraWithTerrain();
			_fe3d->collision_clearCameraWithAabbs();
			_fe3d->misc_setVsyncEnabled(true);

			_gui->getOverlay()->getTextField(SELECTED_TITLE_ID)->setVisible(false);
			_gui->getOverlay()->getTextField(ACTIVE_TITLE_ID)->setVisible(false);
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuMain");
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("empty");

			_currentWorldId = "";
			_currentTemplateModelId = "";
			_currentTemplateQuad3dId = "";
			_currentTemplateText3dId = "";
			_currentTemplateAabbId = "";
			_currentTemplatePointlightId = "";
			_currentTemplateSpotlightId = "";
			_currentTemplateCaptorId = "";
			_currentTemplateSound3dId = "";
			_selectedModelId = "";
			_selectedQuad3dId = "";
			_selectedText3dId = "";
			_selectedAabbId = "";
			_selectedPointlightId = "";
			_selectedSpotlightId = "";
			_selectedCaptorId = "";
			_selectedSound3dId = "";
			_activeModelId = "";
			_activeQuad3dId = "";
			_activeText3dId = "";
			_activeAabbId = "";
			_activePointlightId = "";
			_activeSpotlightId = "";
			_activeCaptorId = "";
			_activeSound3dId = "";
			_editorSpeed = 1.0f;
			_modelIdCounter = 0;
			_quad3dIdCounter = 0;
			_text3dIdCounter = 0;
			_aabbIdCounter = 0;
			_pointlightIdCounter = 0;
			_spotlightIdCounter = 0;
			_captorIdCounter = 0;
			_sound3dIdCounter = 0;
			_dontResetSelectedModel = false;
			_dontResetSelectedQuad3d = false;
			_dontResetSelectedText3d = false;
			_dontResetSelectedAabb = false;
			_dontResetSelectedPointlight = false;
			_dontResetSelectedSpotlight = false;
			_dontResetSelectedCaptor = false;
			_dontResetSelectedSound3d = false;
			_isGridModeEnabled = false;
			_isWireframeModeEnabled = false;
			_isAabbModeEnabled = false;
		}
	}
}