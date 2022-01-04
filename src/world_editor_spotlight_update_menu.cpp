#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateSpotlightMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuSpotlight")
	{
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			if(_isPlacingSpotlight)
			{
				_fe3d.model_setVisible(TEMPLATE_TORCH_ID, false);
				_fe3d.spotlight_setVisible(TEMPLATE_TORCH_ID, false);
				_isPlacingSpotlight = false;
			}

			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui.getViewport("right")->getWindow("main")->setActiveScreen("main");

			_deactivateModel();
			_deactivateBillboard();
			_deactivateSound();
			_deactivatePointlight();
			_deactivateSpotlight();
			_deactivateReflection();

			_isPlacingSpotlight = true;
			_fe3d.model_setVisible(TEMPLATE_TORCH_ID, true);
			_fe3d.spotlight_setVisible(TEMPLATE_TORCH_ID, true);
			_fe3d.misc_centerCursor();

			if(_fe3d.terrain_getSelectedID().empty())
			{
				_fe3d.spotlight_setPosition(TEMPLATE_TORCH_ID, fvec3(0.0f));
				_gui.getOverlay()->createValueForm("positionX", "X", 0.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
				_gui.getOverlay()->createValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
				_gui.getOverlay()->createValueForm("positionZ", "Z", 0.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSpotlightChoice");
			_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuSpotlightChoice")->getScrollingList("spotlights")->deleteButtons();

			auto IDs = _fe3d.spotlight_getIDs();
			sort(IDs.begin(), IDs.end());
			for(auto& spotlightID : IDs)
			{
				if(spotlightID[0] != '@')
				{
					reverse(spotlightID.begin(), spotlightID.end());
					string rawID = spotlightID.substr(spotlightID.find('_') + 1);
					reverse(rawID.begin(), rawID.end());
					reverse(spotlightID.begin(), spotlightID.end());

					_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuSpotlightChoice")->getScrollingList("spotlights")->createButton(spotlightID, rawID);
				}
			}
		}
	}
}

void WorldEditor::_updateSpotlightChoosingMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuSpotlightChoice")
	{
		for(const auto& button : screen->getScrollingList("spotlights")->getButtons())
		{
			if(!_fe3d.spotlight_isExisting(button->getID()))
			{
				screen->getScrollingList("spotlights")->deleteButton(button->getID());
				break;
			}
		}

		for(const auto& spotlightID : _fe3d.spotlight_getIDs())
		{
			if(spotlightID[0] != '@')
			{
				if(screen->getScrollingList("spotlights")->getButton(spotlightID)->isHovered())
				{
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						_activateSpotlight(spotlightID);
					}
					else
					{
						_dontResetSelectedTorch = true;
						_selectSpotlight(spotlightID);
					}

					break;
				}
			}
		}

		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSpotlight");
				return;
			}
		}
	}
}