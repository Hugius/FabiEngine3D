#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateSpotlightMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuSpotlight")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			// Reset placing
			if(_isPlacingSpotlight)
			{
				_fe3d.model_setVisible(TEMPLATE_TORCH_ID, false);
				_fe3d.spotlight_setVisible(TEMPLATE_TORCH_ID, false);
				_isPlacingSpotlight = false;
			}

			// Miscellaneous
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			// Reset right window
			_gui.getViewport("right")->getWindow("main")->setActiveScreen("main");

			// Deactivate everything
			_deactivateModel();
			_deactivateBillboard();
			_deactivateSound();
			_deactivatePointlight();
			_deactivateSpotlight();
			_deactivateReflection();

			// Set new template spotlight
			_isPlacingSpotlight = true;
			_fe3d.model_setVisible(TEMPLATE_TORCH_ID, true);
			_fe3d.spotlight_setVisible(TEMPLATE_TORCH_ID, true);
			_fe3d.spotlight_setPosition(TEMPLATE_TORCH_ID, fvec3(0.0f));
			_fe3d.misc_centerCursor();

			// Add position value forms for placing without terrain
			if(_fe3d.terrain_getSelectedID().empty())
			{
				_gui.getOverlay()->createValueForm("positionX", "X", 0.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
				_gui.getOverlay()->createValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
				_gui.getOverlay()->createValueForm("positionZ", "Z", 0.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSpotlightChoice");

			// Clear all buttons from scrolling list
			_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuSpotlightChoice")->getScrollingList("spotlights")->deleteButtons();

			// Add the ID of every placed spotlight
			auto IDs = _fe3d.spotlight_getIDs();
			sort(IDs.begin(), IDs.end());
			for(auto& spotlightID : IDs)
			{
				// Must not be template entity
				if(spotlightID[0] != '@')
				{
					// Removing the unique number from the ID
					reverse(spotlightID.begin(), spotlightID.end());
					string rawID = spotlightID.substr(spotlightID.find('_') + 1);
					reverse(rawID.begin(), rawID.end());
					reverse(spotlightID.begin(), spotlightID.end());

					// Add new button
					_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuSpotlightChoice")->getScrollingList("spotlights")->createButton(spotlightID, rawID);
				}
			}
		}
	}
}

void WorldEditor::_updateSpotlightChoosingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuSpotlightChoice")
	{
		// Remove deleted spotlights from the scrollingList buttons
		for(const auto& button : screen->getScrollingList("spotlights")->getButtons())
		{
			// Check if spotlight is still existing
			if(!_fe3d.spotlight_isExisting(button->getID()))
			{
				// Delete button
				screen->getScrollingList("spotlights")->deleteButton(button->getID());
				break;
			}
		}

		// Iterate through every placed spotlight
		for(const auto& spotlightID : _fe3d.spotlight_getIDs())
		{
			// Must not be template entity
			if(spotlightID[0] != '@')
			{
				// Check if button is hovered
				if(screen->getScrollingList("spotlights")->getButton(spotlightID)->isHovered())
				{
					// Check if LMB pressed (activation)
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						_activateSpotlight(spotlightID);
					}
					else // Hovering (selection)
					{
						_dontResetSelectedTorch = true;
						_selectSpotlight(spotlightID);
					}

					break;
				}
			}
		}

		// Back button
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