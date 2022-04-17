#include "world_editor.hpp"
#include "tools.hpp"

#include <algorithm>

void WorldEditor::_updateModelMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuModel")
	{
		if((_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKey::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentTemplateModelId.empty())
			{
				_fe3d->model_setVisible(_currentTemplateModelId, false);
				_currentTemplateModelId = "";
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuModelPlace");
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuModelChoice");

			_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuModelChoice")->getScrollingList("modelList")->deleteOptions();

			for(auto & [placedId, templateId] : _loadedModelIds)
			{
				_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuModelChoice")->getScrollingList("modelList")->createOption(placedId, placedId);
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
		if((_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKey::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuModel");
			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT))
		{
			const auto hoveredOptionId = screen->getScrollingList("modelList")->getHoveredOptionId();

			if(!hoveredOptionId.empty())
			{
				_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");

				_deactivateModel();
				_deactivateQuad();
				_deactivateSound();
				_deactivatePointlight();
				_deactivateSpotlight();
				_deactivateReflection();

				_currentTemplateModelId = hoveredOptionId;
				_fe3d->model_setVisible(_currentTemplateModelId, true);
				Tools::setCursorPosition(Tools::convertFromNdc(Tools::convertPositionRelativeToDisplay(fvec2(0.0f))));

				if(_fe3d->terrain_getSelectedId().empty())
				{
					_fe3d->model_setBasePosition(_currentTemplateModelId, fvec3(0.0f));
					_gui->getOverlay()->openValueForm("positionX", "X", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
					_gui->getOverlay()->openValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
					_gui->getOverlay()->openValueForm("positionZ", "Z", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
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
			if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT))
			{
				_deactivateModel();
				_deactivateQuad();
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

		if((_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKey::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuModel");
			return;
		}
	}
}