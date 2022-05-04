#include "world_editor.hpp"

void WorldEditor::_updateSkyMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSky")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSkyPlace");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d->sky_delete(_fe3d->sky_getSelectedId());
		}

		screen->getButton("place")->setHoverable(_fe3d->sky_getSelectedId().empty());
		screen->getButton("delete")->setHoverable(!_fe3d->sky_getSelectedId().empty());
	}
}

void WorldEditor::_updateSkyPlacingMenu()
{
	auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSkyPlace")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSky");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
		{
			const auto hoveredOptionId = screen->getScrollingList("templateSkies")->getHoveredOptionId();

			if(!hoveredOptionId.empty())
			{
				_worldHelper->copyTemplateSky(hoveredOptionId.substr(1), hoveredOptionId);

				_fe3d->sky_select(hoveredOptionId.substr(1));
			}
		}
	}
}