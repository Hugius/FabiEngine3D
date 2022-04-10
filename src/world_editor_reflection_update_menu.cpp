#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateReflectionMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuReflection")
	{
		if((_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(_isPlacingReflection)
			{
				_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);
				_fe3d->reflection_setVisible(TEMPLATE_REFLECTION_ID, false);
				_isPlacingReflection = false;
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");

			_deactivateModel();
			_deactivateQuad();
			_deactivateSound();
			_deactivatePointlight();
			_deactivateSpotlight();
			_deactivateReflection();

			_isPlacingReflection = true;
			_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, true);
			_fe3d->reflection_setVisible(TEMPLATE_REFLECTION_ID, true);
			_fe3d->misc_centerCursor();

			if(_fe3d->terrain_getSelectedId().empty())
			{
				_fe3d->reflection_setPosition(TEMPLATE_REFLECTION_ID, fvec3(0.0f));
				_gui->getOverlay()->openValueForm("positionX", "X", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
				_gui->getOverlay()->openValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
				_gui->getOverlay()->openValueForm("positionZ", "Z", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
			}
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuReflectionChoice");

			_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuReflectionChoice")->getScrollingList("reflectionList")->deleteOptions();

			for(auto & id : _loadedReflectionIds)
			{
				_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuReflectionChoice")->getScrollingList("reflectionList")->createOption(id, id);
			}
		}

		screen->getButton("choice")->setHoverable(!_isPlacingReflection);
	}
}

void WorldEditor::_updateReflectionChoosingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuReflectionChoice")
	{
		for(const auto & optionId : screen->getScrollingList("reflectionList")->getOptionIds())
		{
			if(!_fe3d->reflection_isExisting(optionId))
			{
				screen->getScrollingList("reflectionList")->deleteOption(optionId);
				break;
			}
		}

		const auto hoveredOptionId = screen->getScrollingList("reflectionList")->getHoveredOptionId();

		if(!hoveredOptionId.empty())
		{
			if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT))
			{
				_deactivateModel();
				_deactivateQuad();
				_deactivateSound();
				_deactivatePointlight();
				_deactivateSpotlight();
				_deactivateReflection();

				_activateReflection(hoveredOptionId);
			}
			else
			{
				_selectReflection(hoveredOptionId);

				_dontResetSelectedReflection = true;
			}
		}

		if((_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuReflection");
			return;
		}
	}
}