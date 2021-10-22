#include "scene_editor.hpp"

#include <algorithm>

void SceneEditor::_updateSpotlightMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "sceneEditorMenuSpotlight")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			// Reset placing
			if (_isPlacingSpotlight)
			{
				_fe3d.modelEntity_setVisible(PREVIEW_TORCH_ID, false);
				_fe3d.spotlightEntity_setVisible(PREVIEW_TORCH_ID, false);
				_isPlacingSpotlight = false;
			}

			// Miscellaneous
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			// Deactivate everything
			_deactivateModel();
			_deactivateBillboard();
			_deactivateSound();
			_deactivateSpotlight();
			_deactivateReflection();

			// Set new preview spotlight
			_isPlacingSpotlight = true;
			_fe3d.modelEntity_setVisible(PREVIEW_TORCH_ID, true);
			_fe3d.spotlightEntity_setVisible(PREVIEW_TORCH_ID, true);
			_fe3d.spotlightEntity_setPosition(PREVIEW_TORCH_ID, Vec3(0.0f));
			_fe3d.misc_centerCursor();

			// Add position value forms for placing without terrain
			if (_fe3d.terrainEntity_getSelectedID().empty())
			{
				_gui.getGlobalScreen()->createValueForm("positionX", "X", 0.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("positionY", "Y", 0.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("positionZ", "Z", 0.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSpotlightChoice");

			// Clear all buttons from scrolling list
			_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuSpotlightChoice")->getScrollingList("spotlights")->deleteButtons();

			// Add the ID of every placed spotlight
			auto IDs = _fe3d.spotlightEntity_getAllIDs();
			sort(IDs.begin(), IDs.end());
			for (auto& spotlightID : IDs)
			{
				// Check if spotlight is not a preview
				if (spotlightID[0] != '@')
				{
					// Removing the unique number from the ID
					reverse(spotlightID.begin(), spotlightID.end());
					string rawID = spotlightID.substr(spotlightID.find('_') + 1);
					reverse(rawID.begin(), rawID.end());
					reverse(spotlightID.begin(), spotlightID.end());

					// Add new button
					_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuSpotlightChoice")->getScrollingList("spotlights")->createButton(spotlightID, rawID);
				}
			}
		}
	}
}

void SceneEditor::_updateSpotlightChoosingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "sceneEditorMenuSpotlightChoice")
	{
		// Remove deleted spotlights from the scrollingList buttons
		for (const auto& button : screen->getScrollingList("spotlights")->getButtons())
		{
			// Check if spotlight is still existing
			if (!_fe3d.spotlightEntity_isExisting(button->getID()))
			{
				// Delete button
				screen->getScrollingList("spotlights")->deleteButton(button->getID());
				break;
			}
		}

		// Iterate through every placed spotlight
		for (const auto& spotlightID : _fe3d.spotlightEntity_getAllIDs())
		{
			// Check if spotlight is not a preview
			if (spotlightID[0] != '@')
			{
				// Check if button is hovered
				if (screen->getScrollingList("spotlights")->getButton(spotlightID)->isHovered())
				{
					// Check if LMB pressed (activation)
					if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
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
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSpotlight");
				return;
			}
		}
	}
}