#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateBillboardMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuBillboard")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused())) // Back button
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuBillboardPlace");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuBillboardChoice");

			// Clear all buttons from scrolling list
			_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuBillboardChoice")->getScrollingList("billboardList")->deleteButtons();

			// Add the ID of every placed billboard
			auto IDs = _fe3d.billboard_getIDs();
			sort(IDs.begin(), IDs.end());
			for(auto& billboardID : IDs)
			{
				// Cannot be template
				if(billboardID[0] != '@')
				{
					// Removing the unique number from the ID
					reverse(billboardID.begin(), billboardID.end());
					string rawID = billboardID.substr(billboardID.find('_') + 1);
					reverse(rawID.begin(), rawID.end());
					reverse(billboardID.begin(), billboardID.end());

					// Add new button
					_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuBillboardChoice")->getScrollingList("billboardList")->createButton(billboardID, rawID);
				}
			}
		}
	}
}

void WorldEditor::_updateBillboardPlacingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuBillboardPlace")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			// Reset placing
			if(!_currentTemplateBillboardID.empty())
			{
				_fe3d.text_setVisible(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), false);
				_fe3d.billboard_setVisible(_currentTemplateBillboardID, false);
				_currentTemplateBillboardID = "";
			}

			// Miscellaneous
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuBillboard");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			// Iterate through every created billboard
			for(const auto& billboardID : _billboardEditor.getLoadedIDs())
			{
				// Check if billboard has a billboard entity
				if(_fe3d.billboard_isExisting(billboardID))
				{
					// Check if button is hovered
					if(screen->getScrollingList("billboardList")->getButton(billboardID)->isHovered())
					{
						// Reset right window
						_gui.getViewport("right")->getWindow("main")->setActiveScreen("main");

						// Deactivate everything
						_deactivateModel();
						_deactivateBillboard();
						_deactivateSound();
						_deactivatePointlight();
						_deactivateReflection();

						// Set new template billboard
						_currentTemplateBillboardID = billboardID;
						_fe3d.billboard_setPosition(_currentTemplateBillboardID, fvec3(0.0f));
						_fe3d.billboard_setVisible(_currentTemplateBillboardID, true);
						_fe3d.text_setVisible(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), true);
						_fe3d.text_setContent(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), "Billboard: " + _currentTemplateBillboardID.substr(1), 0.025f);
						_fe3d.misc_centerCursor();

						// Add position value forms for placing without terrain
						if(_fe3d.terrain_getSelectedID().empty())
						{
							_gui.getOverlay()->createValueForm("positionX", "X", 0.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
							_gui.getOverlay()->createValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
							_gui.getOverlay()->createValueForm("positionZ", "Z", 0.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
						}

						// Disable billboard choosing
						break;
					}
				}
			}
		}
	}
}

void WorldEditor::_updateBillboardChoosingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuBillboardChoice")
	{
		// Remove deleted billboards from the scrollingList buttons
		for(const auto& button : _gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuBillboardChoice")->getScrollingList("billboardList")->getButtons())
		{
			// Check if billboard is still existing
			if(!_fe3d.billboard_isExisting(button->getID()))
			{
				// Delete button
				_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuBillboardChoice")->getScrollingList("billboardList")->deleteButton(button->getID());
				break;
			}
		}

		// Iterate through every placed billboard
		for(const auto& billboardID : _fe3d.billboard_getIDs())
		{
			// Cannot be template
			if(billboardID[0] != '@')
			{
				// Check if button is hovered
				if(screen->getScrollingList("billboardList")->getButton(billboardID)->isHovered())
				{
					// Check if LMB pressed (activation)
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
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
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuBillboard");
			return;
		}
	}
}