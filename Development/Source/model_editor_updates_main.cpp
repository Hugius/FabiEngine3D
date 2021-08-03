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
				_gui.getGlobalScreen()->createValueForm("modelCreate", "New model name", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
				_isCreatingModel = true;
			}
			else if (screen->getButton("edit")->isHovered()) // Edit model button
			{
				_isChoosingModel = true;
				_isEditingModel = true;
				auto IDs = getLoadedModelIDs();
				for (auto& name : IDs) { name = name.substr(1); }
				_gui.getGlobalScreen()->createChoiceForm("modelList", "Select Model", Vec2(-0.5f, 0.1f), IDs);
			}
			else if (screen->getButton("delete")->isHovered()) // Delete model button
			{
				_isChoosingModel = true;
				_isDeletingModel = true;
				auto IDs = getLoadedModelIDs();
				for (auto& name : IDs) { name = name.substr(1); }
				_gui.getGlobalScreen()->createChoiceForm("modelList", "Select Model", Vec2(-0.5f, 0.1f), IDs);
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
				if (_fe3d.modelEntity_isExisting(_currentModelID))
				{
					_fe3d.modelEntity_setWireFramed(_currentModelID, false);
					_fe3d.modelEntity_setVisible(_currentModelID, false);
				}

				// Go back to main screen
				_isEditingModel = false;
				_currentModelID = "";
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuMain");
				_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID(), false);
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
				if (_fe3d.modelEntity_isExisting(_currentModelID))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuSize");
				}
			}
			else if (screen->getButton("aabb")->isHovered())
			{
				if (_fe3d.modelEntity_isExisting(_currentModelID))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuAabb");
					_fe3d.misc_enableAabbFrameRendering();
				}
			}
		}

		// Check if mesh exists
		bool isExisting = _fe3d.modelEntity_isExisting(_currentModelID);
		bool isHoverable = false;
		if (isExisting)
		{
			isHoverable = true;

			// Show mesh
			_fe3d.modelEntity_setVisible(_currentModelID, true);
		}

		// Editing buttons hoverability
		screen->getButton("options")->setHoverable(isHoverable);
		screen->getButton("lighting")->setHoverable(isHoverable);
		screen->getButton("size")->setHoverable(isHoverable);
		screen->getButton("aabb")->setHoverable(isHoverable && !_fe3d.modelEntity_isInstanced(_currentModelID));
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
		string newModelName;

		// Create new model
		if (_gui.getGlobalScreen()->checkValueForm("modelCreate", newModelName, {}))
		{
			// @ sign not allowed
			if (newModelName.find('@') == string::npos)
			{
				// Spaces not allowed
				if (newModelName.find(' ') == string::npos)
				{
					// Add model and check if not already existing
					if (_createModel("@" + newModelName, "", "", "", "", "", Vec3(0.0f), 0, 0, 0, ReflectionType(), 1.0f, 1.0f, 1.0f, Vec3(1.0f), 1.0f, "", 0, 0, {}, {}, {}))
					{
						// Go to editor screen
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");

						// Select model
						_currentModelID = "@" + newModelName;

						// Miscellaneous
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID(),
							"Model: " + _currentModelID.substr(1), 0.025f);
						_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID(), true);
						_isCreatingModel = false;
						_isEditingModel = true;
					}
				}
				else
				{
					Logger::throwWarning("Model name cannot contain any spaces!");
				}
			}
			else
			{
				Logger::throwWarning("Model name cannot contain '@'!");
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
			// Check if model has mesh
			if (_fe3d.modelEntity_isExisting(_hoveredModelID))
			{
				_fe3d.modelEntity_setVisible(_hoveredModelID, false);
			}
		}

		// Check if a model name is hovered
		if (selectedButtonID != "")
		{
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT)) // LMB pressed
			{
				// Select model
				_currentModelID = "@" + selectedButtonID;
				_hoveredModelID = "";

				// Go to editor screen & show model name
				if (_isEditingModel)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
					_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID(),
						"Model: " + _currentModelID.substr(1), 0.025f);
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID(), true);
				}

				// Check if model has mesh
				if (_fe3d.modelEntity_isExisting(_currentModelID))
				{
					_fe3d.modelEntity_setVisible(_currentModelID, true);
				}

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("modelList");
				_isChoosingModel = false;
			}
			else
			{
				// Set new hovered model
				_hoveredModelID = "@" + selectedButtonID;
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
			// Check if model has mesh
			if (_fe3d.modelEntity_isExisting(_hoveredModelID))
			{
				_fe3d.modelEntity_setVisible(_hoveredModelID, true);
			}
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
			// Delete entity
			if (_fe3d.modelEntity_isExisting(_currentModelID))
			{
				_fe3d.modelEntity_delete(_currentModelID);
			}

			// Delete from name record
			_loadedModelIDs.erase(std::remove(_loadedModelIDs.begin(), _loadedModelIDs.end(), _currentModelID), _loadedModelIDs.end());
			_isDeletingModel = false;
			_currentModelID = "";
		}
		else if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			// Check if model has mesh
			if (_fe3d.modelEntity_isExisting(_currentModelID))
			{
				_fe3d.modelEntity_setVisible(_currentModelID, false);
			}

			_isDeletingModel = false;
			_currentModelID = "";
		}
	}
}