#include "world_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void WorldEditor::_updateMainMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuMain")
	{
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			unload();
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui.getOverlay()->createValueForm("worldCreate", "Create World", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			_isChoosingWorld = true;
			auto IDs = _getWorldIDs();
			sort(IDs.begin(), IDs.end());
			_gui.getOverlay()->createChoiceForm("worldList", "Edit World", fvec2(0.0f, 0.1f), IDs);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_isDeletingWorld = true;
			auto IDs = _getWorldIDs();
			sort(IDs.begin(), IDs.end());
			_gui.getOverlay()->createChoiceForm("worldList", "Delete World", fvec2(0.0f, 0.1f), IDs);
		}

		string newWorldName;
		if(_gui.getOverlay()->checkValueForm("worldCreate", newWorldName, {}))
		{
			auto worldNames = _getWorldIDs();

			if(find(worldNames.begin(), worldNames.end(), newWorldName) == worldNames.end())
			{
				_fe3d.sky_selectMainSky("");

				_currentWorldID = newWorldName;
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			}
			else
			{
				Logger::throwWarning("World with ID \"" + newWorldName + "\" already exists!");
			}
		}

		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			string selectedButtonID = _gui.getOverlay()->checkChoiceForm("worldList");
			if(!selectedButtonID.empty())
			{
				_currentWorldID = selectedButtonID;

				if(_isChoosingWorld)
				{
					_fe3d.sky_selectMainSky("");

					if(loadEditorWorldFromFile(_currentWorldID))
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
					}
					else
					{
						_fe3d.sky_selectMainSky("@@background");
					}
				}
				else if(_isDeletingWorld)
				{
					_gui.getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
				}

				_gui.getOverlay()->deleteChoiceForm("worldList");
				_isChoosingWorld = false;
			}
			else if(_gui.getOverlay()->isChoiceFormCancelled("worldList"))
			{
				_gui.getOverlay()->deleteChoiceForm("worldList");
			}
		}

		if(_gui.getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_deleteWorldFile(_currentWorldID);
			_isDeletingWorld = false;
			_currentWorldID = "";
		}
		if(_gui.getOverlay()->isAnswerFormDenied("delete"))
		{
			_isDeletingWorld = false;
			_currentWorldID = "";
		}
	}
}

void WorldEditor::_updateChoiceMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuChoice")
	{
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getOverlay()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("sky")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSky");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("terrain")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuTerrain");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("water")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuWater");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("models")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuModel");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("billboards")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuBillboard");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("sounds")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSound");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("pointlights")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuPointlight");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("spotlights")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSpotlight");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("reflections")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuReflection");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("settings")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSettings");
		}

		if(_gui.getOverlay()->isAnswerFormConfirmed("back"))
		{
			_currentTemplateModelID = "";
			_currentTemplateBillboardID = "";
			_currentTemplateSoundID = "";
			_isPlacingPointlight = false;
			_isPlacingSpotlight = false;
			_isPlacingReflection = false;

			saveEditorWorldToFile();

			clearEditorWorld();

			_fe3d.sky_selectMainSky("@@background");

			_currentWorldID = "";
			_currentSkyID = "";
			_currentTerrainID = "";
			_currentWaterID = "";

			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuMain");
			return;
		}
		if(_gui.getOverlay()->isAnswerFormDenied("back"))
		{
			_currentTemplateModelID = "";
			_currentTemplateBillboardID = "";
			_currentTemplateSoundID = "";
			_isPlacingPointlight = false;
			_isPlacingSpotlight = false;
			_isPlacingReflection = false;

			clearEditorWorld();

			_fe3d.sky_selectMainSky("@@background");

			_currentWorldID = "";
			_currentSkyID = "";
			_currentTerrainID = "";
			_currentWaterID = "";

			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuMain");
			return;
		}
	}
}