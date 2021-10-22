#include "scene_editor.hpp"

#include <algorithm>

void SceneEditor::_updateBillboardMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "sceneEditorMenuBillboard")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuBillboardPlace");
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuBillboardChoice");

			// Clear all buttons from scrolling list
			_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardChoice")->getScrollingList("billboardList")->deleteButtons();

			// Add the ID of every placed billboard
			auto IDs = _fe3d.billboardEntity_getAllIDs();
			sort(IDs.begin(), IDs.end());
			for (auto& billboardID : IDs)
			{
				// Check if billboard is not a preview
				if (billboardID[0] != '@')
				{
					// Removing the unique number from the billboardID
					reverse(billboardID.begin(), billboardID.end());
					string rawID = billboardID.substr(billboardID.find('_') + 1);
					reverse(rawID.begin(), rawID.end());
					reverse(billboardID.begin(), billboardID.end());

					// Add new button
					_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardChoice")->getScrollingList("billboardList")->createButton(billboardID, rawID);
				}
			}
		}
	}
}

void SceneEditor::_updateBillboardPlacingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "sceneEditorMenuBillboardPlace")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			// Reset placing
			if (!_currentPreviewBillboardID.empty())
			{
				_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), false);
				_fe3d.billboardEntity_setVisible(_currentPreviewBillboardID, false);
				_currentPreviewBillboardID = "";
			}

			// Miscellaneous
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuBillboard");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			// Iterate through every created billboard
			for (const auto& billboardID : _billboardEditor.getLoadedBillboardIDs())
			{
				// Check if billboard has a billboard entity
				if (_fe3d.billboardEntity_isExisting(billboardID))
				{
					// Check if button is hovered
					if (screen->getScrollingList("billboardList")->getButton(billboardID)->isHovered())
					{
						// Deactivate everything
						_deactivateModel();
						_deactivateBillboard();
						_deactivateSound();
						_deactivatePoinlight();
						_deactivateReflection();

						// Set new preview billboard
						_currentPreviewBillboardID = billboardID;
						_fe3d.billboardEntity_setPosition(_currentPreviewBillboardID, Vec3(0.0f));
						_fe3d.billboardEntity_setVisible(_currentPreviewBillboardID, true);
						_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), true);
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), "Billboard: " + _currentPreviewBillboardID.substr(1), 0.025f);
						_fe3d.misc_centerCursor();

						// Add position value forms for placing without terrain
						if (_fe3d.terrainEntity_getSelectedID().empty())
						{
							_gui.getGlobalScreen()->createValueForm("positionX", "X", 0.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
							_gui.getGlobalScreen()->createValueForm("positionY", "Y", 0.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
							_gui.getGlobalScreen()->createValueForm("positionZ", "Z", 0.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
						}

						// Disable billboard choosing
						break;
					}
				}
			}
		}
	}
}

void SceneEditor::_updateBillboardChoosingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "sceneEditorMenuBillboardChoice")
	{
		// Remove deleted billboards from the scrollingList buttons
		for (const auto& button : _gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardChoice")->getScrollingList("billboardList")->getButtons())
		{
			// Check if billboard is still existing
			if (!_fe3d.billboardEntity_isExisting(button->getID()))
			{
				// Delete button
				_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardChoice")->getScrollingList("billboardList")->deleteButton(button->getID());
				break;
			}
		}

		// Iterate through every placed billboard
		for (const auto& billboardID : _fe3d.billboardEntity_getAllIDs())
		{
			// Check if billboard is not a preview billboard
			if (billboardID[0] != '@')
			{
				// Check if button is hovered
				if (screen->getScrollingList("billboardList")->getButton(billboardID)->isHovered())
				{
					// Check if LMB pressed (activation)
					if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						_activateBillboard(billboardID);
					}
					else // Hovering (selection)
					{
						_dontResetSelectedBillboard = true;
						_selectBillboard(billboardID);
					}

					break;
				}
			}
		}

		// Back button
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuBillboard");
			return;
		}
	}
}