#include "scene_editor.hpp"

#include <algorithm>

void SceneEditor::_updateMainBillboardMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuBillboard")
		{
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
				}
				else if (screen->getButton("place")->isHovered()) // Place billboard button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuBillboardPlace");
				}
				else if (screen->getButton("choice")->isHovered()) // Choose billboard button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuBillboardChoice");

					// Clear all buttons from scrolling list
					_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardChoice")->getScrollingList("billboards")->deleteButtons();

					// Add the name of every placed billboard
					auto IDs = _fe3d.billboardEntity_getAllIDs();
					std::sort(IDs.begin(), IDs.end());
					for (auto& billboardID : IDs)
					{
						// Check if billboard is not a preview
						if (billboardID[0] != '@')
						{
							// Removing the unique number from the billboardID
							std::reverse(billboardID.begin(), billboardID.end());
							string billboardName = billboardID.substr(billboardID.find('_') + 1);
							std::reverse(billboardName.begin(), billboardName.end());
							std::reverse(billboardID.begin(), billboardID.end());

							// Add new button
							_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardChoice")->getScrollingList("billboards")->addButton(billboardID, billboardName);
						}
					}
				}
			}
		}
	}
}

void SceneEditor::_updateBillboardPlacingMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuBillboardPlace")
		{
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				// Back button
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuBillboard");
				}
				else
				{
					// Loop over every created billboard
					for (const auto& billboardID : _billboardEditor.getLoadedBillboardIDs())
					{
						// Check if billboard has a billboard entity
						if (_fe3d.billboardEntity_isExisting(billboardID))
						{
							// Check if button is hovered
							if (screen->getScrollingList("billboards")->getButton(billboardID)->isHovered())
							{
								// Hide old preview billboard
								if (_currentPreviewBillboardID != "")
								{
									_fe3d.billboardEntity_hide(_currentPreviewBillboardID);
								}

								// Set new preview billboard
								_currentPreviewBillboardID = billboardID;
								_fe3d.billboardEntity_show(_currentPreviewBillboardID);
								string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID();
								_fe3d.textEntity_show(textEntityID);
								_fe3d.textEntity_setTextContent(textEntityID, "Billboard: " + _currentPreviewBillboardID.substr(1), 0.025f);
								_fe3d.misc_centerCursor();
								break;
							}
						}
					}
				}
			}
		}
	}
}

void SceneEditor::_updateBillboardChoosingMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuBillboardChoice")
		{
			// Remove deleted billboards from the scrollingList buttons
			for (const auto& button : _gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuBillboardChoice")->getScrollingList("billboards")->getButtons())
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
			for (const auto& billboardID : _fe3d.billboardEntity_getAllIDs())
			{
				// Check if billboard is not a preview billboard
				if (billboardID[0] != '@')
				{
					// Check if button is hovered
					if (screen->getScrollingList("billboards")->getButton(billboardID)->isHovered())
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
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuBillboard");
					_currentPreviewBillboardID = "";
				}
			}
		}
	}
}