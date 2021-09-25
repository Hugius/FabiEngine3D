#include "model_editor.hpp"
#include "logger.hpp"

void ModelEditor::update()
{
	if (_isEditorLoaded)
	{
		_updateMainMenu();
	}
	if (_isEditorLoaded)
	{
		_updateChoiceMenu();
	}
	if (_isEditorLoaded)
	{
		_updateMeshMenu();
	}
	if (_isEditorLoaded)
	{
		_updateLightingMenu();
	}
	if (_isEditorLoaded)
	{
		_updateOptionsMenu();
	}
	if (_isEditorLoaded)
	{
		_updateMainAabbMenu();
	}
	if (_isEditorLoaded)
	{
		_updateChoiceAabbMenu();
	}
	if (_isEditorLoaded)
	{
		_updateModelCreating();
	}
	if (_isEditorLoaded)
	{
		_updateModelChoosing();
	}
	if (_isEditorLoaded)
	{
		_updateModelDeleting();
	}
	if (_isEditorLoaded)
	{
		_updatePartChoosing();
	}
	if (_isEditorLoaded)
	{
		_updateAabbCreating();
	}
	if (_isEditorLoaded)
	{
		_updateAabbChoosing();
	}
	if (_isEditorLoaded)
	{
		_updateAabbDeleting();
	}
	if (_isEditorLoaded)
	{
		_updateCamera();
	}
	if (_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}

void ModelEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "modelEditorMenuMain")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
		{
			_gui.getGlobalScreen()->createAnswerForm("back", "Save Changes?", Vec2(0.0f, 0.25f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("modelCreate", "Create Model", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
			_isCreatingModel = true;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto IDs = getLoadedModelIDs();
			for (auto& ID : IDs) { ID = ID.substr(1); }
			_gui.getGlobalScreen()->createChoiceForm("modelList", "Edit Model", Vec2(-0.5f, 0.1f), IDs);
			_isChoosingModel = true;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto IDs = getLoadedModelIDs();
			for (auto& ID : IDs) { ID = ID.substr(1); }
			_gui.getGlobalScreen()->createChoiceForm("modelList", "Delete Model", Vec2(-0.5f, 0.1f), IDs);
			_isChoosingModel = true;
			_isDeletingModel = true;
		}

		// Update answer forms
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveModelEntitiesToFile();
			unload();
			return;
		}
		if (_gui.getGlobalScreen()->isAnswerFormDenied("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
	}
}

void ModelEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "modelEditorMenuChoice")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			// Hide model
			_fe3d.modelEntity_setWireFramed(_currentModelID, false);
			_fe3d.modelEntity_setVisible(_currentModelID, false);

			// Go back to main screen
			_currentModelID = "";
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuMain");
			_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), false);
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("mesh")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuMesh");
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lighting")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuLighting");
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("options")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuOptions");
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("aabb")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuAabbMain");
			_fe3d.misc_enableAabbFrameRendering();
		}

		// Update buttons hoverability
		screen->getButton("aabb")->setHoverable(!_fe3d.modelEntity_isInstanced(_currentModelID));
	}
}

void ModelEditor::_updateModelCreating()
{
	if (_isCreatingModel)
	{
		// Temporary values
		string newModelID;

		// Check if user filled in a new ID
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

					// If model not existing yet
					if (find(_loadedModelIDs.begin(), _loadedModelIDs.end(), newModelID) == _loadedModelIDs.end())
					{
						// Get the chosen filename
						const auto rootDirectory = _fe3d.misc_getRootDirectory();
						const string targetDirectory = string("game_assets\\meshes\\");

						// Validate target directory
						if (!_fe3d.misc_isDirectoryExisting(rootDirectory + targetDirectory))
						{
							Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
							_isCreatingModel = false;
							return;
						}

						// Validate chosen file
						const string filePath = _fe3d.misc_getWinExplorerFilename(string(rootDirectory + targetDirectory), "OBJ");
						if (filePath.empty())
						{
							_isCreatingModel = false;
							return;
						}

						// Validate directory of file
						if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
							filePath.substr(rootDirectory.size(), targetDirectory.size()) != targetDirectory)
						{
							Logger::throwWarning("File cannot be outside of `" + targetDirectory + "`!");
							_isCreatingModel = false;
							return;
						}

						// Create model
						const string finalFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearMeshCache(finalFilePath);
						_fe3d.modelEntity_create(newModelID, finalFilePath);
	
						// Check if model creation went well
						if (_fe3d.modelEntity_isExisting(newModelID))
						{
							// Go to editor
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");

							// Select model
							_currentModelID = newModelID;
							_loadedModelIDs.push_back(newModelID);

							// Miscellaneous
							_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), "Model: " + newModelID.substr(1), 0.025f);
							_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), true);
							_isCreatingModel = false;
						}
					}
					else
					{
						Logger::throwWarning("Model with ID \"" + newModelID.substr(1) + "\" already exists!");
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
		if (!selectedButtonID.empty())
		{
			// Set new hovered model
			_hoveredModelID = ("@" + selectedButtonID);

			// Check if LMB is pressed
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select model
				_currentModelID = ("@" + selectedButtonID);
				_hoveredModelID = "";

				// Go to editor
				if (!_isDeletingModel)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
					_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), "Model: " + _currentModelID.substr(1), 0.025f);
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), true);
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

		// Update answer form
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			_fe3d.modelEntity_delete(_currentModelID);
			_loadedModelIDs.erase(remove(_loadedModelIDs.begin(), _loadedModelIDs.end(), _currentModelID), _loadedModelIDs.end());
			_isDeletingModel = false;
			_currentModelID = "";
		}
		if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_fe3d.modelEntity_setVisible(_currentModelID, false);
			_isDeletingModel = false;
			_currentModelID = "";
		}
	}
}

void ModelEditor::_updatePartChoosing()
{
	if (_isChoosingPart)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("partList");

		// Check if a part ID is hovered
		if (!selectedButtonID.empty())
		{
			// Check if LMB is pressed
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select part
				_currentPartID = selectedButtonID;

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("partList");
				_isChoosingPart = false;
				_partExecutionFunction();
			}
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("partList")) // Cancelled choosing
		{
			_isChoosingPart = false;
			_gui.getGlobalScreen()->deleteChoiceForm("partList");
		}
	}
}