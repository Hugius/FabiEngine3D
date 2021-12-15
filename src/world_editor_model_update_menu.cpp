#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateModelMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuModel")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuModelPlace");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuModelChoice");

			// Clear all buttons from scrolling list
			_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuModelChoice")->getScrollingList("modelList")->deleteButtons();

			// Add the ID of every placed model
			auto IDs = _fe3d.model_getIDs();
			sort(IDs.begin(), IDs.end());
			for(auto& modelID : IDs)
			{
				// Must not be template entity
				if(modelID[0] != '@')
				{
					// Removing the unique number from the ID
					reverse(modelID.begin(), modelID.end());
					string rawID = modelID.substr(modelID.find('_') + 1);
					reverse(rawID.begin(), rawID.end());
					reverse(modelID.begin(), modelID.end());

					// Add new button
					_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuModelChoice")->getScrollingList("modelList")->createButton(modelID, rawID);
				}
			}
		}
	}
}

void WorldEditor::_updateModelPlacingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuModelPlace")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			// Reset placing
			if(!_currentTemplateModelID.empty())
			{
				_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), false);
				_fe3d.model_setVisible(_currentTemplateModelID, false);
				_currentTemplateModelID = "";
			}

			// Miscellaneous
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuModel");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			// Iterate through every created model
			for(const auto& modelID : _modelEditor.getLoadedIDs())
			{
				// Check if model has mesh
				if(_fe3d.model_isExisting(modelID))
				{
					// Check if button is hovered
					if(screen->getScrollingList("modelList")->getButton(modelID)->isHovered())
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

						// Set new template model
						_currentTemplateModelID = modelID;
						_fe3d.model_setBasePosition(_currentTemplateModelID, fvec3(0.0f));
						_fe3d.model_setVisible(_currentTemplateModelID, true);
						_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), true);
						_fe3d.text_setContent(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), "Model: " + _currentTemplateModelID.substr(1), 0.025f);
						_fe3d.misc_centerCursor();

						// Add position value forms for placing without terrain
						if(_fe3d.terrain_getSelectedID().empty())
						{
							_gui.getGlobalScreen()->createValueForm("positionX", "X", 0.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
							_gui.getGlobalScreen()->createValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
							_gui.getGlobalScreen()->createValueForm("positionZ", "Z", 0.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
						}

						// Disable model choosing
						break;
					}
				}
			}
		}
	}
}

void WorldEditor::_updateModelChoosingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuModelChoice")
	{
		// Remove deleted models from the scrollingList buttons
		for(const auto& button : _gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuModelChoice")->getScrollingList("modelList")->getButtons())
		{
			// Check if model is still existing
			if(!_fe3d.model_isExisting(button->getID()))
			{
				// Delete button
				_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuModelChoice")->getScrollingList("modelList")->deleteButton(button->getID());
				break;
			}
		}

		// Iterate through every placed model
		for(const auto& modelID : _fe3d.model_getIDs())
		{
			// Must not be template entity
			if(modelID[0] != '@')
			{
				// Check if button is hovered
				if(screen->getScrollingList("modelList")->getButton(modelID)->isHovered())
				{
					// Check if LMB pressed (activation)
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						_activateModel(modelID);
					}
					else // Hovering (selection)
					{
						_dontResetSelectedModel = true;
						_selectModel(modelID);
					}

					break;
				}
			}
		}

		// Back button
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuModel");
			return;
		}
	}
}