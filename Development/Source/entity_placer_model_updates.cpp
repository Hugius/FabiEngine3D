#include "entity_placer.hpp"

void EntityPlacer::_updateModelScreen()
{
	if (_isLoaded)
	{
		if (_leftWindow->getActiveScreen()->getID() == "modelPlaceManagement")
		{
			auto screen = _leftWindow->getScreen("modelPlaceManagement");
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("placeModel")->isHovered()) // Place model button
				{
					_leftWindow->setActiveScreen("placeModel");
				}
				else if (screen->getButton("chooseModel")->isHovered()) // Choose model button
				{
					_leftWindow->setActiveScreen("chooseModel");

					// Prepare scrolling list
					_leftWindow->getScreen("chooseModel")->getScrollingList("modelList")->deleteButtons();
					for (auto& modelName : _fe3d.gameEntity_getAllIDs())
					{
						// Check if model is not a preview model
						if (modelName[0] != '@')
						{
							_leftWindow->getScreen("chooseModel")->getScrollingList("modelList")->addButton(modelName, modelName);
						}
					}
				}
				else if (screen->getButton("back")->isHovered()) // Back button
				{
					_leftWindow->setActiveScreen("placeManagement");
				}
			}
		}
	}
}

void EntityPlacer::_updateModelPlacingScreen()
{
	if (_isLoaded)
	{
		// Placing screen
		if (_leftWindow->getActiveScreen()->getID() == "placeModel")
		{
			auto screen = _leftWindow->getScreen("placeModel");
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
					_leftWindow->setActiveScreen("modelPlaceManagement");
				}
			}
		}
	}
}

void EntityPlacer::_updateModelChoosingScreen()
{
	if (_isLoaded)
	{
		// Choosing screen
		if (_leftWindow->getActiveScreen()->getID() == "chooseModel")
		{
			auto screen = _leftWindow->getScreen("chooseModel");

			// Loop over every created model
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
					_leftWindow->setActiveScreen("modelPlaceManagement");
					_currentPreviewModelName = "";
				}
			}
		}
	}
}