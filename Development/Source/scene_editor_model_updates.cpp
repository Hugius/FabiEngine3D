#include "scene_editor.hpp"

void SceneEditor::_updateMainModelMenu()
{
	if (_isLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuModel")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
				}
				else if (screen->getButton("place")->isHovered()) // Place model button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuModelPlace");
				}
				else if (screen->getButton("choice")->isHovered()) // Choose model button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuModelChoice");

					// Clear all buttons from scrolling list
					_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelChoice")->getScrollingList("models")->deleteButtons();

					// Add every placed model name
					for (auto& modelID : _fe3d.gameEntity_getAllIDs())
					{
						// Check if model is not a preview model
						if (modelID[0] != '@')
						{
							// Removing the unique number from the modelID
							string modelName = modelID.substr(modelID.find('@') + 1);

							// Add new button
							_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelChoice")->getScrollingList("models")->addButton(modelID, modelName);
						}
					}
				}
			}
		}
	}
}

void SceneEditor::_updateModelPlacingMenu()
{
	if (_isLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuModelPlace")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuModel");
				}
				else
				{
					// Loop over every created model
					for (auto& modelName : _modelEditor.getModelNames())
					{
						// Check if model has a game entity
						if (_fe3d.gameEntity_isExisting(modelName))
						{
							// Check if button is hovered
							if (screen->getScrollingList("models")->getButton(modelName)->isHovered())
							{
								// Hide old preview model
								if (_currentPreviewModelName != "")
								{
									_fe3d.gameEntity_hide(_currentPreviewModelName);
								}

								// Set new preview model
								_currentPreviewModelName = modelName;
								_fe3d.gameEntity_show(_currentPreviewModelName);
								string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
								_fe3d.textEntity_show(textEntityID);
								_fe3d.textEntity_setTextContent(textEntityID, "Model: " + _currentPreviewModelName.substr(1), 0.025f);
								break;
							}
						}
					}
				}
			}
		}
	}
}

void SceneEditor::_updateModelChoosingMenu()
{
	if (_isLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuModelChoice")
		{
			// Remove deleted models from the scrollingList buttons
			for (auto& button : _gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelChoice")->getScrollingList("models")->getButtons())
			{
				// Check if model is still existing
				if (!_fe3d.gameEntity_isExisting(button->getID()))
				{
					// Delete button
					_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelChoice")->getScrollingList("models")->deleteButton(button->getID());
					break;
				}
			}

			// Loop over every placed model
			for (auto& modelName : _fe3d.gameEntity_getAllIDs())
			{
				// Check if model is not a preview model
				if (modelName[0] != '@')
				{
					// Check if button is hovered
					if (screen->getScrollingList("models")->getButton(modelName)->isHovered())
					{
						// Check if LMB pressed (activation)
						if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
						{
							_activateModel(modelName);
						}
						else // Hovering (selection)
						{
							_dontResetSelectedModel = true;
							_selectModel(modelName);
						}

						break;
					}
				}
			}

			// Back button
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuModel");
					_currentPreviewModelName = "";
				}
			}
		}
	}
}