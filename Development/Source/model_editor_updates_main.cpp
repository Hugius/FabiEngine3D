#include "model_editor.hpp"

void ModelEditor::update()
{
	_updateManagementScreen();
	_updateModelCreation();
	_updateModelChoosing();
	_updateEditingScreen();
	_updateModelRemoval();
	_updateCamera();
	_updateMiscellaneous();
}

void ModelEditor::_updateManagementScreen()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "modelEditorMenuMain")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
				{
					_gui.getGlobalScreen()->addAnswerForm("exitModelEditor", "Save changes?", Vec2(0.0f, 0.25f));
				}
				else if (screen->getButton("addModel")->isHovered()) // Add model button
				{
					_gui.getGlobalScreen()->addValueForm("newModelName", "New model name", "", Vec2(0.0f), Vec2(0.5f, 0.1f));
					_isCreatingModel = true;
				}
				else if (screen->getButton("editModel")->isHovered()) // Edit model button
				{
					_isChoosingModel = true;
					_isEditingModel = true;
					auto IDs = getLoadedModelIDs();
					for (auto& name : IDs) { name = name.substr(1); }
					_gui.getGlobalScreen()->addChoiceForm("models", "Select model", Vec2(-0.4f, 0.1f), IDs);
				}
				else if (screen->getButton("deleteModel")->isHovered()) // Delete model button
				{
					_isChoosingModel = true;
					_isDeletingModel = true;
					auto IDs = getLoadedModelIDs();
					for (auto& name : IDs) { name = name.substr(1); }
					_gui.getGlobalScreen()->addChoiceForm("models", "Select model", Vec2(-0.4f, 0.1f), IDs);
				}
			}

			// Check if user wants to save changes
			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exitModelEditor"))
			{
				saveGameEntitiesToFile();
				unload();
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("exitModelEditor"))
			{
				unload();
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			}
		}
	}
}

void ModelEditor::_updateEditingScreen()
{
	if (_isEditingModel && _currentModelID != "")
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();
		
		// GUI management
		if (screen->getID() == "modelEditorMenuChoice")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					// Hide game entity
					if (_fe3d.gameEntity_isExisting(_currentModelID))
					{
						_fe3d.gameEntity_hide(_currentModelID);
					}

					// Reset variables and go back to main screen
					_isEditingModel = false;
					_currentModelID = "";
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuMain");
					_fe3d.textEntity_hide(_gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID());
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
					if (_fe3d.gameEntity_isExisting(_currentModelID))
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuSize");
					}
				}
				else if (screen->getButton("aabb")->isHovered())
				{
					if (_fe3d.gameEntity_isExisting(_currentModelID))
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuAabb");
						_fe3d.misc_enableAabbFrameRendering();
					}
				}
			}

			// Check if mesh exists
			bool existing = _fe3d.gameEntity_isExisting(_currentModelID);
			bool hoverable = false;
			if (existing)
			{
				hoverable = true;

				// Show mesh
				_fe3d.gameEntity_show(_currentModelID);
			}

			// Editing buttons hoverability
			screen->getButton("options")->setHoverable(hoverable);
			screen->getButton("lighting")->setHoverable(hoverable);
			screen->getButton("size")->setHoverable(hoverable);
			screen->getButton("aabb")->setHoverable(hoverable && !_fe3d.gameEntity_isInstanced(_currentModelID));
		}
		else if (screen->getID() == "modelEditorMenuMesh")
		{
			_updateModelEditingMesh();
		}
		else if (screen->getID() == "modelEditorMenuOptions")
		{
			_updateModelEditingOptions();
		}
		else if (screen->getID() == "modelEditorMenuLighting")
		{
			_updateModelEditingLighting();
		}
		else if (screen->getID() == "modelEditorMenuSize")
		{
			_updateModelEditingSize();
		}
		else if (screen->getID() == "modelEditorMenuAabb")
		{
			_updateModelEditingAabb();
		}
	}
}

void ModelEditor::_updateModelCreation()
{
	if (_isEditorLoaded)
	{
		if (_isCreatingModel)
		{
			string newModelName;

			// Create new model
			if (_gui.getGlobalScreen()->checkValueForm("newModelName", newModelName, {}))
			{
				// Starting with at-sign not allowed
				if (newModelName[0] != '@')
				{
					// Check if name contains spaces
					if (newModelName.find(' ') == string::npos)
					{
						// Add model and check if not already existing
						if (_addModel("@" + newModelName, "", "", "", "", "", Vec3(0.0f), 0, 1, 0, 0, 0, 1.0f, 1.0f, 1.0f, Vec3(1.0f), 1.0f, "", false, {}, {}, {}))
						{
							// Go to editor screen
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");

							// Select model
							_currentModelID = "@" + newModelName;

							// Miscellaneous
							_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID(),
								"Model: " + _currentModelID.substr(1), 0.025f);
							_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID());
							_isCreatingModel = false;
							_isEditingModel = true;
						}
					}
					else
					{
						_fe3d.logger_throwWarning("New model name cannot contain any spaces!");
					}
				}
				else
				{
					_fe3d.logger_throwWarning("New model name cannot begin with '@'!");
				}
			}
		}
	}
}

void ModelEditor::_updateModelChoosing()
{
	if (_isEditorLoaded)
	{
		if (_isChoosingModel)
		{
			// Get selected button ID
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("models");

			// Hide last model
			if (_hoveredModelID != "")
			{
				// Check if model has game entity
				if (_fe3d.gameEntity_isExisting(_hoveredModelID))
				{
					_fe3d.gameEntity_hide(_hoveredModelID);
				}
			}

			// Check if a model name is hovered
			if (selectedButtonID != "")
			{
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT)) // LMB pressed
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
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID());
					}

					// Check if model has game entity
					if (_fe3d.gameEntity_isExisting(_currentModelID))
					{
						_fe3d.gameEntity_show(_currentModelID);
					}

					// Miscellaneous
					_gui.getGlobalScreen()->removeChoiceForm("models");
					_isChoosingModel = false;
				}
				else
				{
					// Set new hovered model
					_hoveredModelID = "@" + selectedButtonID;
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("models")) // Cancelled choosing
			{
				_isChoosingModel = false;
				_isEditingModel = false;
				_isDeletingModel = false;
				_gui.getGlobalScreen()->removeChoiceForm("models");
			}
			else // Nothing hovered
			{
				_hoveredModelID = "";
			}

			// Show hovered model
			if (_hoveredModelID != "")
			{
				// Check if model has game entity
				if (_fe3d.gameEntity_isExisting(_hoveredModelID))
				{
					_fe3d.gameEntity_show(_hoveredModelID);
				}
			}
		}
	}
}

void ModelEditor::_updateModelRemoval()
{
	if (_isEditorLoaded)
	{
		if (_isDeletingModel && _currentModelID != "")
		{
			_gui.getGlobalScreen()->addAnswerForm("deleteModel", "Are you sure?", Vec2(0.0f, 0.25f));

			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("deleteModel"))
			{
				// Delete entity
				if (_fe3d.gameEntity_isExisting(_currentModelID))
				{
					_fe3d.gameEntity_delete(_currentModelID);
				}

				// Delete from name record
				_loadedModelIDs.erase(std::remove(_loadedModelIDs.begin(), _loadedModelIDs.end(), _currentModelID), _loadedModelIDs.end());
				_isDeletingModel = false;
				_currentModelID = "";
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("deleteModel"))
			{
				// Check if model has game entity
				if (_fe3d.gameEntity_isExisting(_currentModelID))
				{
					_fe3d.gameEntity_hide(_currentModelID);
				}

				_isDeletingModel = false;
				_currentModelID = "";
			}
		}
	}
}