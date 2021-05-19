#include "scene_editor.hpp"

#include <algorithm>

void SceneEditor::_updateMainModelMenu()
{
	if (_isEditorLoaded)
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

					// Add the name of every placed model
					auto IDs = _fe3d.modelEntity_getAllIDs();
					std::sort(IDs.begin(), IDs.end());
					for (auto& modelID : IDs)
					{
						// Check if model is not a preview model
						if (modelID[0] != '@')
						{
							// Removing the unique number from the modelID
							std::reverse(modelID.begin(), modelID.end());
							string modelName = modelID.substr(modelID.find('_') + 1);
							std::reverse(modelName.begin(), modelName.end());
							std::reverse(modelID.begin(), modelID.end());

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
	if (_isEditorLoaded)
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
					for (const auto& modelID : _modelEditor.getLoadedModelIDs())
					{
						// Check if model has mesh
						if (_fe3d.modelEntity_isExisting(modelID))
						{
							// Check if button is hovered
							if (screen->getScrollingList("models")->getButton(modelID)->isHovered())
							{
								// Hide old preview model
								if (_currentPreviewModelID != "")
								{
									_fe3d.modelEntity_hide(_currentPreviewModelID);
								}

								// Set new preview model
								_currentPreviewModelID = modelID;
								_fe3d.modelEntity_show(_currentPreviewModelID);
								string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
								_fe3d.textEntity_show(textEntityID);
								_fe3d.textEntity_setTextContent(textEntityID, "Model: " + _currentPreviewModelID.substr(1), 0.025f);
								_fe3d.misc_setCursorPosition(_fe3d.misc_convertToScreenCoords(Vec2(0.5f)));
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
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuModelChoice")
		{
			// Remove deleted models from the scrollingList buttons
			for (const auto& button : _gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelChoice")->getScrollingList("models")->getButtons())
			{
				// Check if model is still existing
				if (!_fe3d.modelEntity_isExisting(button->getID()))
				{
					// Delete button
					_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelChoice")->getScrollingList("models")->deleteButton(button->getID());
					break;
				}
			}

			// Loop over every placed model
			for (const auto& modelID : _fe3d.modelEntity_getAllIDs())
			{
				// Check if model is not a preview model
				if (modelID[0] != '@')
				{
					// Check if button is hovered
					if (screen->getScrollingList("models")->getButton(modelID)->isHovered())
					{
						// Check if LMB pressed (activation)
						if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
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
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuModel");
					_currentPreviewModelID = "";
				}
			}
		}
	}
}