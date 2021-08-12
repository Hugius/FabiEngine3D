#include "water_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void WaterEditor::update()
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
		_updateEffectsMenu();
	}
	if (_isEditorLoaded)
	{
		_updateOptionsMenu();
	}
	if (_isEditorLoaded)
	{
		_updateWaterCreating();
	}
	if (_isEditorLoaded)
	{
		_updateWaterChoosing();
	}
	if (_isEditorLoaded)
	{
		_updateWaterDeleting();
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

void WaterEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "waterEditorMenuMain")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getGlobalScreen()->createAnswerForm("exit", "Save Changes?", Vec2(0.0f, 0.25f));
			}
			else if (screen->getButton("create")->isHovered())
			{
				_isCreatingWater = true;
				_gui.getGlobalScreen()->createValueForm("waterCreate", "Create Water", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("edit")->isHovered())
			{
				_isChoosingWater = true;
				_isEditingWater = true;
				auto IDs = getLoadedWaterIDs();
				for (auto& ID : IDs)
				{
					ID = ID.substr(1);
				}
				_gui.getGlobalScreen()->createChoiceForm("waterList", "Edit Water", Vec2(0.0f, 0.1f), IDs);
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_isChoosingWater = true;
				_isDeletingWater = true;
				auto IDs = getLoadedWaterIDs();
				for (auto& ID : IDs)
				{
					ID = ID.substr(1);
				}
				_gui.getGlobalScreen()->createChoiceForm("waterList", "Delete Water", Vec2(0.0f, 0.1f), IDs);
			}
		}

		// Check if user wants to save changes
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exit"))
		{
			saveWaterEntitiesToFile();
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

void WaterEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "waterEditorMenuChoice")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuMain");
				_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("waterID")->getEntityID(), false);
				_fe3d.waterEntity_setWireFramed(_currentWaterID, false);
				_fe3d.waterEntity_select("");
				_currentWaterID = "";
				_isEditingWater = false;
				return;
			}
			else if (screen->getButton("mesh")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuMesh");
			}
			else if (screen->getButton("effects")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuEffects");
			}
			else if (screen->getButton("options")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuOptions");
			}
		}

		// Screen hoverabilities
		screen->getButton("effects")->setHoverable(_fe3d.waterEntity_isExisting(_currentWaterID));
		screen->getButton("options")->setHoverable(_fe3d.waterEntity_isExisting(_currentWaterID));
	}
}

void WaterEditor::_updateWaterCreating()
{
	if (_isCreatingWater)
	{
		string newWaterID;

		// Create new water
		if (_gui.getGlobalScreen()->checkValueForm("waterCreate", newWaterID, {}))
		{
			// @ sign not allowed
			if (newWaterID.find('@') == string::npos)
			{
				// Spaces not allowed
				if (newWaterID.find(' ') == string::npos)
				{
					// Add @ sign to new ID
					newWaterID = ("@" + newWaterID);

					// If water not existing yet
					if (find(_loadedWaterIDs.begin(), _loadedWaterIDs.end(), newWaterID) == _loadedWaterIDs.end())
					{
						// Create water
						_fe3d.waterEntity_create(newWaterID);

						// Check if water creation went well
						if (_fe3d.waterEntity_isExisting(newWaterID))
						{
							// Go to editor
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");

							// Select water
							_currentWaterID = newWaterID;
							_loadedWaterIDs.push_back(newWaterID);
							_fe3d.waterEntity_select(newWaterID);

							// Miscellaneous
							auto textEntityID = _gui.getGlobalScreen()->getTextfield("waterID")->getEntityID();
							_fe3d.textEntity_setTextContent(textEntityID, "Water: " + newWaterID.substr(1), 0.025f);
							_fe3d.textEntity_setVisible(textEntityID, true);
							_isCreatingWater = false;
							_isEditingWater = true;
						}
					}
					else
					{
						Logger::throwWarning("Water with ID \"" + newWaterID.substr(1) + "\" already exists!");
					}
				}
				else
				{
					Logger::throwWarning("Water ID cannot contain any spaces!");
				}
			}
			else
			{
				Logger::throwWarning("Water ID cannot contain '@'!");
			}
		}
	}
}

void WaterEditor::_updateWaterChoosing()
{
	if (_isChoosingWater)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("waterList");

		// Check if a water ID is hovered
		if (selectedButtonID != "")
		{
			// Check if LMB is pressed
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select water
				_currentWaterID = "@" + selectedButtonID;

				// Go to editor
				if (_isEditingWater)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
					auto textEntityID = _gui.getGlobalScreen()->getTextfield("terrainID")->getEntityID();
					_fe3d.textEntity_setTextContent(textEntityID, "Water: " + _currentWaterID.substr(1), 0.025f);
					_fe3d.textEntity_setVisible(textEntityID, true);
				}

				// Show entity
				_fe3d.waterEntity_select(_currentWaterID);

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("waterList");
				_isChoosingWater = false;
			}
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("waterList")) // Cancelled choosing
		{
			_isChoosingWater = false;
			_isEditingWater = false;
			_isDeletingWater = false;
			_gui.getGlobalScreen()->deleteChoiceForm("waterList");
		}
	}
}

void WaterEditor::_updateWaterDeleting()
{
	if (_isDeletingWater && _currentWaterID != "")
	{
		// Add answer form
		if (!_gui.getGlobalScreen()->isAnswerFormExisting("delete"))
		{
			_gui.getGlobalScreen()->createAnswerForm("delete", "Are You Sure?", Vec2(0.0f, 0.25f));
		}

		// Check if form is answered
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			// Delete entity
			_fe3d.waterEntity_delete(_currentWaterID);

			// Delete from ID record
			_loadedWaterIDs.erase(remove(_loadedWaterIDs.begin(), _loadedWaterIDs.end(), _currentWaterID), _loadedWaterIDs.end());
			_isDeletingWater = false;
			_currentWaterID = "";
		}
		else if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_fe3d.waterEntity_select("");
			_isDeletingWater = false;
			_currentWaterID = "";
		}
	}
}