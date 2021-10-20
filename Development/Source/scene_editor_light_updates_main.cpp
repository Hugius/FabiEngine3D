#include "scene_editor.hpp"

#include <algorithm>

void SceneEditor::_updateLightMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "sceneEditorMenuLight")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			// Reset placing
			if (_isPlacingLight)
			{
				_fe3d.modelEntity_setVisible(PREVIEW_LAMP_ID, false);
				_fe3d.pointlightEntity_setVisible(PREVIEW_LAMP_ID, false);
				_isPlacingLight = false;
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
			_deactivateLight();
			_deactivateReflection();

			// Set new preview light
			_isPlacingLight = true;
			_fe3d.modelEntity_setVisible(PREVIEW_LAMP_ID, true);
			_fe3d.pointlightEntity_setVisible(PREVIEW_LAMP_ID, true);
			_fe3d.pointlightEntity_setPosition(PREVIEW_LAMP_ID, Vec3(0.0f));
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
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuLightChoice");

			// Clear all buttons from scrolling list
			_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuLightChoice")->getScrollingList("lights")->deleteButtons();

			// Add the ID of every placed light
			auto IDs = _fe3d.pointlightEntity_getAllIDs();
			sort(IDs.begin(), IDs.end());
			for (auto& lightID : IDs)
			{
				// Check if light is not a preview
				if (lightID[0] != '@')
				{
					// Removing the unique number from the ID
					reverse(lightID.begin(), lightID.end());
					string rawID = lightID.substr(lightID.find('_') + 1);
					reverse(rawID.begin(), rawID.end());
					reverse(lightID.begin(), lightID.end());

					// Add new button
					_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuLightChoice")->getScrollingList("lights")->createButton(lightID, rawID);
				}
			}
		}
	}
}

void SceneEditor::_updateLightChoosingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "sceneEditorMenuLightChoice")
	{
		// Remove deleted lights from the scrollingList buttons
		for (const auto& button : screen->getScrollingList("lights")->getButtons())
		{
			// Check if light is still existing
			if (!_fe3d.pointlightEntity_isExisting(button->getID()))
			{
				// Delete button
				screen->getScrollingList("lights")->deleteButton(button->getID());
				break;
			}
		}

		// Iterate through every placed light
		for (const auto& lightID : _fe3d.pointlightEntity_getAllIDs())
		{
			// Check if light is not a preview
			if (lightID[0] != '@')
			{
				// Check if button is hovered
				if (screen->getScrollingList("lights")->getButton(lightID)->isHovered())
				{
					// Check if LMB pressed (activation)
					if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						_activateLight(lightID);
					}
					else // Hovering (selection)
					{
						_dontResetSelectedLamp = true;
						_selectLight(lightID);
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
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuLight");
				return;
			}
		}
	}
}