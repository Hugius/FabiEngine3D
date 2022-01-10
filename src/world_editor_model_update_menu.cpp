#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateModelMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuModel")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuModelPlace");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuModelChoice");

			_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuModelChoice")->getScrollingList("modelList")->deleteButtons();

			auto IDs = _fe3d->model_getIDs();
			sort(IDs.begin(), IDs.end());
			for(auto& modelID : IDs)
			{
				if(modelID[0] != '@')
				{
					reverse(modelID.begin(), modelID.end());
					string rawID = modelID.substr(modelID.find('_') + 1);
					reverse(rawID.begin(), rawID.end());
					reverse(modelID.begin(), modelID.end());

					_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuModelChoice")->getScrollingList("modelList")->createButton(modelID, rawID);
				}
			}
		}
	}
}

void WorldEditor::_updateModelPlacingMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuModelPlace")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			if(!_currentTemplateModelID.empty())
			{
				_fe3d->text_setVisible(_gui.getOverlay()->getTextField("modelID")->getEntityID(), false);
				_fe3d->model_setVisible(_currentTemplateModelID, false);
				_currentTemplateModelID = "";
			}

			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuModel");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			for(const auto& modelID : _modelEditor.getLoadedIDs())
			{
				if(_fe3d->model_isExisting(modelID))
				{
					if(screen->getScrollingList("modelList")->getButton(modelID)->isHovered())
					{
						_gui.getViewport("right")->getWindow("main")->setActiveScreen("main");

						_deactivateModel();
						_deactivateBillboard();
						_deactivateSound();
						_deactivatePointlight();
						_deactivateSpotlight();
						_deactivateReflection();

						_currentTemplateModelID = modelID;
						_fe3d->model_setBasePosition(_currentTemplateModelID, fvec3(0.0f));
						_fe3d->model_setVisible(_currentTemplateModelID, true);
						_fe3d->text_setVisible(_gui.getOverlay()->getTextField("modelID")->getEntityID(), true);
						_fe3d->text_setContent(_gui.getOverlay()->getTextField("modelID")->getEntityID(), "Model: " + _currentTemplateModelID.substr(1), 0.025f);
						_fe3d->misc_centerCursor();

						if(_fe3d->terrain_getSelectedID().empty())
						{
							_gui.getOverlay()->createValueForm("positionX", "X", 0.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
							_gui.getOverlay()->createValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
							_gui.getOverlay()->createValueForm("positionZ", "Z", 0.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
						}

						break;
					}
				}
			}
		}
	}
}

void WorldEditor::_updateModelChoosingMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuModelChoice")
	{
		for(const auto& button : _gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuModelChoice")->getScrollingList("modelList")->getButtons())
		{
			if(!_fe3d->model_isExisting(button->getID()))
			{
				_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuModelChoice")->getScrollingList("modelList")->deleteButton(button->getID());
				break;
			}
		}

		for(const auto& modelID : _fe3d->model_getIDs())
		{
			if(modelID[0] != '@')
			{
				if(screen->getScrollingList("modelList")->getButton(modelID)->isHovered())
				{
					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						_activateModel(modelID);
					}
					else
					{
						_dontResetSelectedModel = true;
						_selectModel(modelID);
					}

					break;
				}
			}
		}

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuModel");
			return;
		}
	}
}