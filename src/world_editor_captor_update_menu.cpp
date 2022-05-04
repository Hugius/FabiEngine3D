#include "world_editor.hpp"
#include "tools.hpp"

#include <algorithm>

void WorldEditor::_updateCaptorMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuCaptor")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(_isPlacingCaptor)
			{
				_fe3d->model_setVisible(TEMPLATE_CAPTOR_ID, false);
				_isPlacingCaptor = false;
			}

			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("empty");

			_deactivateModel();
			_deactivateQuad3d();
			_deactivateText3d();
			_deactivateAabb();
			_deactivatePointlight();
			_deactivateSpotlight();
			_deactivateCaptor();
			_deactivateSound3d();

			_isPlacingCaptor = true;
			_fe3d->model_setVisible(TEMPLATE_CAPTOR_ID, true);
			Tools::setCursorPosition(Tools::convertFromNdc(Tools::convertPositionRelativeToDisplay(fvec2(0.0f))));

			if(_fe3d->terrain_getSelectedId().empty())
			{
				_fe3d->captor_setPosition(TEMPLATE_CAPTOR_ID, fvec3(0.0f));
				_gui->getOverlay()->openValueForm("positionX", "X", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
				_gui->getOverlay()->openValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
				_gui->getOverlay()->openValueForm("positionZ", "Z", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuCaptorChoice");

			_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuCaptorChoice")->getScrollingList("placedCaptors")->deleteOptions();

			for(auto & captorId : _loadedCaptorIds)
			{
				_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuCaptorChoice")->getScrollingList("placedCaptors")->createOption(captorId, captorId);
			}
		}

		screen->getButton("choice")->setHoverable(!_isPlacingCaptor);
	}
}

void WorldEditor::_updateCaptorChoosingMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuCaptorChoice")
	{
		for(const auto & optionId : screen->getScrollingList("placedCaptors")->getOptionIds())
		{
			if(!_fe3d->captor_isExisting(optionId))
			{
				screen->getScrollingList("placedCaptors")->deleteOption(optionId);

				break;
			}
		}

		const auto hoveredOptionId = screen->getScrollingList("placedCaptors")->getHoveredOptionId();

		if(!hoveredOptionId.empty())
		{
			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				_deactivateModel();
				_deactivateQuad3d();
				_deactivateText3d();
				_deactivateAabb();
				_deactivatePointlight();
				_deactivateSpotlight();
				_deactivateCaptor();
				_deactivateSound3d();

				_activateCaptor(hoveredOptionId);
			}
			else
			{
				_selectCaptor(hoveredOptionId);

				_dontResetSelectedCaptor = true;
			}
		}

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuCaptor");

			return;
		}
	}
}