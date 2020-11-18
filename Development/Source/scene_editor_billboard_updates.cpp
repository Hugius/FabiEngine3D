#include "scene_editor.hpp"

void SceneEditor::_updateMainBillboardMenu()
{
	if (_isLoaded)
	{
		if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "sceneEditorMenuBillboard")
		{
			auto screen = _gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboard");
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("place")->isHovered()) // Place billboard button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("place");
				}
				else if (screen->getButton("choice")->isHovered()) // Choose billboard button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("choice");

					// Clear all buttons from scrolling list
					_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardChoice")->getScrollingList("billboards")->deleteButtons();

					// Add every placed billboard name
					for (auto& billboardID : _fe3d.billboardEntity_getAllIDs())
					{
						// Check if billboard is not a preview billboard
						if (billboardID[0] != '@')
						{
							// Removing the unique number from the billboardID
							string billboardName = billboardID.substr(billboardID.find('@') + 1);

							// Add new button
							_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardChoice")->getScrollingList("billboards")->addButton(billboardID, billboardName);
						}
					}
				}
				else if (screen->getButton("back")->isHovered()) // Back button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
				}
			}
		}
	}
}

void SceneEditor::_updateBilboardPlacingMenu()
{
	if (_isLoaded)
	{
		// Placing screen
		if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "sceneEditorMenuBillboardPlace")
		{
			auto screen = _gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardPlace");
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Loop over every created billboard
				for (auto& billboardName : _billboardEditor.getBillboardNames())
				{
					// Check if billboard has a billboard entity
					if (_fe3d.billboardEntity_isExisting(billboardName))
					{
						// Check if button is hovered
						if (screen->getScrollingList("billboards")->getButton(billboardName)->isHovered())
						{
							// Hide old preview billboard
							if (_currentPreviewBillboardName != "")
							{
								_fe3d.billboardEntity_hide(_currentPreviewBillboardName);
							}

							// Set new preview billboard
							_currentPreviewBillboardName = billboardName;
							_fe3d.billboardEntity_show(_currentPreviewBillboardName);
							string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID();
							_fe3d.textEntity_show(textEntityID);
							_fe3d.textEntity_setTextContent(textEntityID, "Billboard: " + _currentPreviewBillboardName.substr(1), 0.025f);
							break;
						}
					}
				}

				// Back button
				if (screen->getButton("back")->isHovered())
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuBillboard");
				}
			}
		}
	}
}

void SceneEditor::_updateBillboardChoosingMenu()
{
	if (_isLoaded)
	{
		// Choosing screen
		if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "choice")
		{
			auto screen = _gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardChoice");

			// Remove deleted billboards from the scrollingList buttons
			for (auto& button : _gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardChoice")->getScrollingList("billboards")->getButtons())
			{
				// Check if billboard is still existing
				if (!_fe3d.billboardEntity_isExisting(button->getID()))
				{
					// Delete button
					_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardChoice")->getScrollingList("billboards")->deleteButton(button->getID());
					break;
				}
			}

			// Loop over every placed billboard
			for (auto& billboardName : _fe3d.billboardEntity_getAllIDs())
			{
				// Check if billboard is not a preview billboard
				if (billboardName[0] != '@')
				{
					// Check if button is hovered
					if (screen->getScrollingList("billboards")->getButton(billboardName)->isHovered())
					{
						// Check if LMB pressed (activation)
						if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
						{
							_activateBillboard(billboardName);
						}
						else // Hovering (selection)
						{
							_dontResetSelectedBillboard = true;
							_selectBillboard(billboardName);
						}

						break;
					}
				}
			}

			// Back button
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("back")->isHovered())
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuBillboard");
					_currentPreviewBillboardName = "";
				}
			}
		}
	}
}