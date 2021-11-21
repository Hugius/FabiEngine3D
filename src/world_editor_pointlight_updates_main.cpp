#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updatePointlightMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuPointlight")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			// Reset placing
			if(_isPlacingPointlight)
			{
				_fe3d.model_setVisible(PREVIEW_LAMP_ID, false);
				_fe3d.pointlight_setVisible(PREVIEW_LAMP_ID, false);
				_isPlacingPointlight = false;
			}

			// Miscellaneous
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			// Reset right window
			_gui.getViewport("right")->getWindow("main")->setActiveScreen("worldEditorControls");

			// Deactivate everything
			_deactivateModel();
			_deactivateBillboard();
			_deactivateSound();
			_deactivatePointlight();
			_deactivateSpotlight();
			_deactivateReflection();

			// Set new preview pointlight
			_isPlacingPointlight = true;
			_fe3d.model_setVisible(PREVIEW_LAMP_ID, true);
			_fe3d.pointlight_setVisible(PREVIEW_LAMP_ID, true);
			_fe3d.pointlight_setPosition(PREVIEW_LAMP_ID, Vec3(0.0f));
			_fe3d.misc_centerCursor();

			// Add position value forms for placing without terrain
			if(_fe3d.terrain_getSelectedID().empty())
			{
				_gui.getGlobalScreen()->createValueForm("positionX", "X", 0.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("positionY", "Y", 0.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("positionZ", "Z", 0.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuPointlightChoice");

			// Clear all buttons from scrolling list
			_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuPointlightChoice")->getScrollingList("pointlights")->deleteButtons();

			// Add the ID of every placed pointlight
			auto IDs = _fe3d.pointlight_getAllIDs();
			sort(IDs.begin(), IDs.end());
			for(auto& pointlightID : IDs)
			{
				// Check if pointlight is not a preview
				if(pointlightID[0] != '@')
				{
					// Removing the unique number from the ID
					reverse(pointlightID.begin(), pointlightID.end());
					string rawID = pointlightID.substr(pointlightID.find('_') + 1);
					reverse(rawID.begin(), rawID.end());
					reverse(pointlightID.begin(), pointlightID.end());

					// Add new button
					_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuPointlightChoice")->getScrollingList("pointlights")->createButton(pointlightID, rawID);
				}
			}
		}
	}
}

void WorldEditor::_updatePointlightChoosingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuPointlightChoice")
	{
		// Remove deleted pointlights from the scrollingList buttons
		for(const auto& button : screen->getScrollingList("pointlights")->getButtons())
		{
			// Check if pointlight is still existing
			if(!_fe3d.pointlight_isExisting(button->getID()))
			{
				// Delete button
				screen->getScrollingList("pointlights")->deleteButton(button->getID());
				break;
			}
		}

		// Iterate through every placed pointlight
		for(const auto& pointlightID : _fe3d.pointlight_getAllIDs())
		{
			// Check if pointlight is not a preview
			if(pointlightID[0] != '@')
			{
				// Check if button is hovered
				if(screen->getScrollingList("pointlights")->getButton(pointlightID)->isHovered())
				{
					// Check if LMB pressed (activation)
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						_activatePointlight(pointlightID);
					}
					else // Hovering (selection)
					{
						_dontResetSelectedLamp = true;
						_selectPointlight(pointlightID);
					}

					break;
				}
			}
		}

		// Back button
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuPointlight");
				return;
			}
		}
	}
}