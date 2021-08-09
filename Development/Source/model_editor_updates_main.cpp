#include "model_editor.hpp"
#include "logger.hpp"

void ModelEditor::update()
{
	if (_isEditorLoaded)
	{
		_updateMainMenu();
		_updateChoiceMenu();
		_updateModelCreating();
		_updateModelChoosing();
		_updateModelDeleting();
		_updateCamera();
		_updateMiscellaneous();
	}
}

void ModelEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "modelEditorMenuMain")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
			{
				_gui.getGlobalScreen()->createAnswerForm("exit", "Save Changes?", Vec2(0.0f, 0.25f));
			}
			else if (screen->getButton("add")->isHovered()) // Add model button
			{
				_gui.getGlobalScreen()->createValueForm("modelCreate", "Create Mode", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
				_isCreatingModel = true;
			}
			else if (screen->getButton("edit")->isHovered()) // Edit model button
			{
				_isChoosingModel = true;
				_isEditingModel = true;
				auto IDs = getLoadedModelIDs();
				for (auto& ID : IDs)
				{
					ID = ID.substr(1);
				}
				_gui.getGlobalScreen()->createChoiceForm("modelList", "Edit Model", Vec2(-0.5f, 0.1f), IDs);
			}
			else if (screen->getButton("delete")->isHovered()) // Delete model button
			{
				_isChoosingModel = true;
				_isDeletingModel = true;
				auto IDs = getLoadedModelIDs();
				for (auto& ID : IDs)
				{
					ID = ID.substr(1);
				}
				_gui.getGlobalScreen()->createChoiceForm("modelList", "Delete Model", Vec2(-0.5f, 0.1f), IDs);
			}
		}

		// Check if user wants to save changes
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exit"))
		{
			saveModelEntitiesToFile();
			unload();
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
		}
		else if (_gui.getGlobalScreen()->isAnswerFormDenied("exit"))
		{
			unload();
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
		}
	}
}

void ModelEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "modelEditorMenuChoice")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				// Hide model entity
				_fe3d.modelEntity_setWireFramed(_currentModelID, false);
				_fe3d.modelEntity_setVisible(_currentModelID, false);

				// Go back to main screen
				_isEditingModel = false;
				_currentModelID = "";
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuMain");
				_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedModelID")->getEntityID(), false);
				return;
			}
			else if (screen->getButton("mesh")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuMesh");
			}
			else if (screen->getButton("options")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuOptions");
			}
			else if (screen->getButton("lighting")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuLighting");
			}
			else if (screen->getButton("size")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuSize");
			}
			else if (screen->getButton("aabb")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuAabb");
				_fe3d.misc_enableAabbFrameRendering();
			}
		}

		// Buttons hoverability
		screen->getButton("aabb")->setHoverable(!_fe3d.modelEntity_isInstanced(_currentModelID));
	}
	else if (screen->getID() == "modelEditorMenuMesh")
	{
		_updateMeshMenu();
	}
	else if (screen->getID() == "modelEditorMenuOptions")
	{
		_updateOptionsMenu();
	}
	else if (screen->getID() == "modelEditorMenuLighting")
	{
		_updateLightingMenu();
	}
	else if (screen->getID() == "modelEditorMenuSize")
	{
		_updateSizeMenu();
	}
	else if (screen->getID() == "modelEditorMenuAabb")
	{
		_updateAabbMenu();
	}
}

void ModelEditor::_updateModelCreating()
{
	if (_isCreatingModel)
	{
		string newModelID;

		// Create new model
		if (_gui.getGlobalScreen()->checkValueForm("modelCreate", newModelID, {}))
		{
			// @ sign not allowed
			if (newModelID.find('@') == string::npos)
			{
				// Spaces not allowed
				if (newModelID.find(' ') == string::npos)
				{
					// Add @ sign to new ID
					newModelID = ("@" + newModelID);

					// If model ID not existing yet
					if (find(_loadedModelIDs.begin(), _loadedModelIDs.end(), newModelID) == _loadedModelIDs.end())
					{
						// Get the chosen filename
						const string rootDirectory = _fe3d.misc_getRootDirectory();
						const string targetDirectory = string("game_assets\\meshes\\");
						const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "OBJ");

						// Check if not cancelled
						if (filePath.empty())
						{
							_isCreatingModel = false;
							return;
						}
						else
						{
							// Check if user did not switch directory
							if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
								filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
							{
								const string newFilePath = filePath.substr(rootDirectory.size());
								_fe3d.misc_clearMeshCache(newFilePath);
								_fe3d.modelEntity_create(newModelID, newFilePath);
							}
							else
							{
								Logger::throwWarning("Invalid filepath, directory switching not allowed!");
								_isCreatingModel = false;
								return;
							}
						}
	
						// Miscellaneous
						_currentModelID = newModelID;
						_loadedModelIDs.push_back(newModelID);
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedModelID")->getEntityID(),
							"Model: " + _currentModelID.substr(1), 0.025f);
						_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedModelID")->getEntityID(), true);
						_isCreatingModel = false;
						_isEditingModel = true;
					}
					else
					{
						Logger::throwWarning("Model ID \"" + newModelID.substr(1) + "\" already exists!");
					}
				}
				else
				{
					Logger::throwWarning("Model ID cannot contain any spaces!");
				}
			}
			else
			{
				Logger::throwWarning("Model ID cannot contain '@'!");
			}
		}
	}
}

void ModelEditor::_updateModelChoosing()
{
	if (_isChoosingModel)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("modelList");

		// Hide last model
		if (_hoveredModelID != "")
		{
			_fe3d.modelEntity_setVisible(_hoveredModelID, false);
		}

		// Check if a model ID is hovered
		if (selectedButtonID != "")
		{
			// Set new hovered model
			_hoveredModelID = ("@" + selectedButtonID);

			// Check if LMB is pressed
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select model
				_currentModelID = "@" + selectedButtonID;
				_hoveredModelID = "";

				// Go to editor
				if (_isEditingModel)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
					_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedModelID")->getEntityID(),
						"Model: " + _currentModelID.substr(1), 0.025f);
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedModelID")->getEntityID(), true);
				}

				// Miscellaneous
				_fe3d.modelEntity_setVisible(_currentModelID, true);
				_gui.getGlobalScreen()->deleteChoiceForm("modelList");
				_isChoosingModel = false;
			}
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("modelList")) // Cancelled choosing
		{
			_isChoosingModel = false;
			_isEditingModel = false;
			_isDeletingModel = false;
			_gui.getGlobalScreen()->deleteChoiceForm("modelList");
		}
		else // Nothing hovered
		{
			_hoveredModelID = "";
		}

		// Show hovered model
		if (_hoveredModelID != "")
		{
			_fe3d.modelEntity_setVisible(_hoveredModelID, true);
		}
	}
}

void ModelEditor::_updateModelDeleting()
{
	if (_isDeletingModel && _currentModelID != "")
	{
		// Add answer form
		if (!_gui.getGlobalScreen()->isAnswerFormExisting("delete"))
		{
			_gui.getGlobalScreen()->createAnswerForm("delete", "Are You Sure?", Vec2(0.0f, 0.25f));
		}

		// Check is form is answered
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			_fe3d.modelEntity_delete(_currentModelID);
			_loadedModelIDs.erase(remove(_loadedModelIDs.begin(), _loadedModelIDs.end(), _currentModelID), _loadedModelIDs.end());
			_isDeletingModel = false;
			_currentModelID = "";
		}
		else if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_fe3d.modelEntity_setVisible(_currentModelID, false);
			_isDeletingModel = false;
			_currentModelID = "";
		}
	}
}