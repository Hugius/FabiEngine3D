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

			_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuModelChoice")->getScrollingList("modelList")->deleteOptions();

			for(auto & [key, templateId] : _loadedModelIds)
			{
				_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuModelChoice")->getScrollingList("modelList")->createOption(key, key);
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
			const auto hoveredOptionId = screen->getScrollingList("modelList")->getHoveredOptionId();

			if(!hoveredOptionId.empty())
			{
				_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");

				_deactivateModel();
				_deactivateQuad3d();
				_deactivateSound();
				_deactivatePointlight();
				_deactivateSpotlight();
				_deactivateReflection();

				_currentTemplateModelId = hoveredOptionId;
				_fe3d->model_setVisible(_currentTemplateModelId, true);
				_fe3d->misc_centerCursor();

				if(_fe3d->terrain_getSelectedId().empty())
				{
					_fe3d->model_setBasePosition(_currentTemplateModelId, fvec3(0.0f));
					//_gui->getOverlay()->openValueForm("positionX", "X", 0.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
					//_gui->getOverlay()->openValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
					//_gui->getOverlay()->openValueForm("positionZ", "Z", 0.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
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
		for(const auto & optionId : screen->getScrollingList("modelList")->getOptionIds())
		{
			if(!_fe3d->model_isExisting(optionId))
			{
				screen->getScrollingList("modelList")->deleteOption(optionId);
				break;
			}
		}

		const auto hoveredOptionId = screen->getScrollingList("modelList")->getHoveredOptionId();

		if(!hoveredOptionId.empty())
		{
			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_deactivateModel();
				_deactivateQuad3d();
				_deactivateSound();
				_deactivatePointlight();
				_deactivateSpotlight();
				_deactivateReflection();

				_activateModel(hoveredOptionId);
			}
			else
			{
				_selectModel(hoveredOptionId);

				_dontResetSelectedModel = true;
			}
		}

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuModel");
			return;
		}
	}
}