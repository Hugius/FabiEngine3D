#include "scene_editor.hpp"

void SceneEditor::_updateModelScreen()
{
	if (_isLoaded)
	{
		if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuModel")
		{
			auto screen = _leftWindow->getScreen("sceneEditorMenuModel");
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("sceneEditorMenuModelPlace")->isHovered()) // Place model button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuModelPlace");
				}
				else if (screen->getButton("sceneEditorMenuModelChoice")->isHovered()) // Choose model button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuModelChoice");

					// Clear all buttons from scrolling list
					_leftWindow->getScreen("sceneEditorMenuModelChoice")->getScrollingList("modelList")->deleteButtons();

					// Add every placed model name
					for (auto& modelName : _fe3d.gameEntity_getAllIDs())
					{
						// Check if model is not a preview model
						if (modelName[0] != '@')
						{
							_leftWindow->getScreen("sceneEditorMenuModelChoice")->getScrollingList("modelList")->addButton(modelName, modelName);
						}
					}
				}
				else if (screen->getButton("back")->isHovered()) // Back button
				{
					_leftWindow->setActiveScreen("sceneEditorMenu");
				}
			}
		}
	}
}

void SceneEditor::_updateModelPlacingScreen()
{
	if (_isLoaded)
	{
		// Placing screen
		if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuModelPlace")
		{
			auto screen = _leftWindow->getScreen("sceneEditorMenuModelPlace");
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				// Loop over every created model
				for (auto& modelName : _modelEditor.getModelNames())
				{
					// Check if model has a game entity
					if (_fe3d.gameEntity_isExisting(modelName))
					{
						// Check if button is hovered
						if (screen->getScrollingList("modelList")->getButton(modelName)->isHovered())
						{
							// Hide old preview model
							if (_currentPreviewModelName != "")
							{
								_fe3d.gameEntity_hide(_currentPreviewModelName);
							}

							// Set new preview model
							_currentPreviewModelName = modelName;
							_fe3d.gameEntity_show(_currentPreviewModelName);
							string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
							_fe3d.textEntity_show(textEntityID);
							_fe3d.textEntity_setTextContent(textEntityID, "Model: " + _currentPreviewModelName.substr(1, _currentPreviewModelName.size() - 1), 0.025f);
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

void SceneEditor::_updateModelChoosingScreen()
{
	if (_isLoaded)
	{
		// Choosing screen
		if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuModelChoice")
		{
			auto screen = _leftWindow->getScreen("sceneEditorMenuModelChoice");

			// Update scrollinglist content every 1/10 second
			static int lastMS = 0;
			if (abs(_fe3d.misc_getMsTimeSinceEpoch() - lastMS) > 100)
			{
				// Remove deleted models from the scrolLinglist buttons
				for (auto& button : _leftWindow->getScreen("sceneEditorMenuModelChoice")->getScrollingList("modelList")->getButtons())
				{
					// Check if model is still existing
					if (!_fe3d.gameEntity_isExisting(button->getID()))
					{
						// Delete button
						_leftWindow->getScreen("sceneEditorMenuModelChoice")->getScrollingList("modelList")->deleteButton(button->getID());
					}
				}

				// Set last time
				lastMS = _fe3d.misc_getMsTimeSinceEpoch();
			}

			// Loop over every placed model
			for (auto& modelName : _fe3d.gameEntity_getAllIDs())
			{
				// Check if model is not a preview model
				if (modelName[0] != '@')
				{
					// Check if button is hovered
					if (screen->getScrollingList("modelList")->getButton(modelName)->isHovered())
					{
						// Check if LMB pressed (activation)
						if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
						{
							_activateModel(modelName);
						}
						else // Hovering (selection)
						{
							_selectModel(modelName);
						}

						break;
					}
				}
			}

			// Back button
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
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