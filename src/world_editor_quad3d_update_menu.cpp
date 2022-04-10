#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateQuad3dMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuQuad3d")
	{
		if((_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentTemplateQuadId.empty())
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuadId, false);
				_currentTemplateQuadId = "";
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuQuad3dPlace");
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuQuad3dChoice");

			_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuQuad3dChoice")->getScrollingList("quadList")->deleteOptions();

			for(auto & [placedId, templateId] : _loadedQuadIds)
			{
				_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuQuad3dChoice")->getScrollingList("quadList")->createOption(placedId, placedId);
			}
		}

		screen->getButton("choice")->setHoverable(_currentTemplateQuadId.empty());
	}
}

void WorldEditor::_updateQuad3dPlacingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuQuad3dPlace")
	{
		if((_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuQuad3d");
			return;
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT))
		{
			const auto hoveredOptionId = screen->getScrollingList("quadList")->getHoveredOptionId();

			if(!hoveredOptionId.empty())
			{
				_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");

				_deactivateModel();
				_deactivateQuad();
				_deactivateSound();
				_deactivatePointlight();
				_deactivateReflection();

				_currentTemplateQuadId = hoveredOptionId;
				_fe3d->quad3d_setVisible(_currentTemplateQuadId, true);
				_fe3d->misc_centerCursor();

				if(_fe3d->terrain_getSelectedId().empty())
				{
					_fe3d->quad3d_setPosition(_currentTemplateQuadId, fvec3(0.0f));
					_gui->getOverlay()->openValueForm("positionX", "X", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
					_gui->getOverlay()->openValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
					_gui->getOverlay()->openValueForm("positionZ", "Z", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
				}
			}
		}
	}
}

void WorldEditor::_updateQuad3dChoosingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuQuad3dChoice")
	{
		for(const auto & optionId : screen->getScrollingList("quadList")->getOptionIds())
		{
			if(!_fe3d->quad3d_isExisting(optionId))
			{
				screen->getScrollingList("quadList")->deleteOption(optionId);
				break;
			}
		}

		const auto hoveredOptionId = screen->getScrollingList("quadList")->getHoveredOptionId();

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

				_activateQuad(hoveredOptionId);
			}
			else
			{
				_selectQuad(hoveredOptionId);

				_dontResetSelectedQuad3d = true;
			}
		}

		if((_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuQuad3d");
			return;
		}
	}
}