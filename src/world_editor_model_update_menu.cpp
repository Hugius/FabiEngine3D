#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateModelMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuModel")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentTemplateModelId.empty())
			{
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("modelId")->getEntityId(), false);
				_fe3d->model_setVisible(_currentTemplateModelId, false);
				_currentTemplateModelId = "";
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuModelPlace");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuModelChoice");

			_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuModelChoice")->getScrollingList("modelList")->deleteButtons();

			auto Ids = _fe3d->model_getIds();
			sort(Ids.begin(), Ids.end());
			for(auto& modelId : Ids)
			{
				if(modelId[0] != '@')
				{
					reverse(modelId.begin(), modelId.end());
					string rawId = modelId.substr(modelId.find('_') + 1);
					reverse(rawId.begin(), rawId.end());
					reverse(modelId.begin(), modelId.end());

					_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuModelChoice")->getScrollingList("modelList")->createButton(modelId, rawId);
				}
			}
		}

		screen->getButton("choice")->setHoverable(_currentTemplateModelId.empty());
	}
}

void WorldEditor::_updateModelPlacingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuModelPlace")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuModel");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			for(const auto& modelId : _modelEditor->getLoadedIds())
			{
				if(_fe3d->model_isExisting(modelId))
				{
					if(screen->getScrollingList("modelList")->getButton(modelId)->isHovered())
					{
						_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");

						_deactivateModel();
						_deactivateQuad3d();
						_deactivateSound();
						_deactivatePointlight();
						_deactivateSpotlight();
						_deactivateReflection();

						_currentTemplateModelId = modelId;
						_fe3d->model_setVisible(_currentTemplateModelId, true);
						_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("modelId")->getEntityId(), true);
						_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("modelId")->getEntityId(), "Model: " + _currentTemplateModelId.substr(1), 0.025f);
						_fe3d->misc_centerCursor();

						if(_fe3d->terrain_getSelectedId().empty())
						{
							_fe3d->model_setBasePosition(_currentTemplateModelId, fvec3(0.0f));
							_gui->getOverlay()->createValueForm("positionX", "X", 0.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
							_gui->getOverlay()->createValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
							_gui->getOverlay()->createValueForm("positionZ", "Z", 0.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
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
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuModelChoice")
	{
		for(const auto& button : _gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuModelChoice")->getScrollingList("modelList")->getButtons())
		{
			if(!_fe3d->model_isExisting(button->getId()))
			{
				_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuModelChoice")->getScrollingList("modelList")->deleteButton(button->getId());
				break;
			}
		}

		for(const auto& modelId : _fe3d->model_getIds())
		{
			if(modelId[0] != '@')
			{
				if(screen->getScrollingList("modelList")->getButton(modelId)->isHovered())
				{
					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						_activateModel(modelId);
					}
					else
					{
						_dontResetSelectedModel = true;
						_selectModel(modelId);
					}

					break;
				}
			}
		}

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuModel");
			return;
		}
	}
}