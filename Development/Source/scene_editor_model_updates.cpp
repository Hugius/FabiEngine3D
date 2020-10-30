#include "scene_editor.hpp"

void SceneEditor::_updateMainModelMenu()
{
	if (_isLoaded)
	{
		if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuModel")
		{
			auto screen = _leftWindow->getScreen("sceneEditorMenuModel");
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("place")->isHovered()) // Place model button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuModelPlace");
				}
				else if (screen->getButton("choice")->isHovered()) // Choose model button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuModelChoice");

					// Clear all buttons from scrolling list
					_leftWindow->getScreen("sceneEditorMenuModelChoice")->getScrollingList("models")->deleteButtons();

					// Add every placed model name
					for (auto& modelID : _fe3d.gameEntity_getAllIDs())
					{
						// Check if model is not a preview model
						if (modelID[0] != '@')
						{
							// Removing the unique number from the modelID
							string modelName = modelID.substr(modelID.find('@') + 1);

							// Add new button
							_leftWindow->getScreen("sceneEditorMenuModelChoice")->getScrollingList("models")->addButton(modelID, modelName);
						}
					}
				}
				else if (screen->getButton("back")->isHovered()) // Back button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuChoice");
				}
			}
		}
	}
}

void SceneEditor::_updateModelPlacingMenu()
{
	if (_isLoaded)
	{
		// Placing screen
		if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuModelPlace")
		{
			auto screen = _leftWindow->getScreen("sceneEditorMenuModelPlace");
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
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

				// Back button
				if (screen->getButton("back")->isHovered())
				{
					_leftWindow->setActiveScreen("sceneEditorMenuModel");
				}
			}
		}
	}
}

void SceneEditor::_updateModelChoosingMenu()
{
	if (_isLoaded)
	{
		// Choosing screen
		if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuModelChoice")
		{
			auto screen = _leftWindow->getScreen("sceneEditorMenuModelChoice");

			// Remove deleted models from the scrollingList buttons
			for (auto& button : _leftWindow->getScreen("sceneEditorMenuModelChoice")->getScrollingList("models")->getButtons())
			{
				// Check if model is still existing
				if (!_fe3d.gameEntity_isExisting(button->getID()))
				{
					// Delete button
					_leftWindow->getScreen("sceneEditorMenuModelChoice")->getScrollingList("models")->deleteButton(button->getID());
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
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("back")->isHovered())
				{
					_leftWindow->setActiveScreen("sceneEditorMenuModel");
					_currentPreviewModelName = "";
				}
			}
		}
	}
}