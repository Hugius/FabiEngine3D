#include "water_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void WaterEditor::update()
{
	if(_isEditorLoaded)
	{
		_updateMainMenu();
	}
	if(_isEditorLoaded)
	{
		_updateChoiceMenu();
	}
	if(_isEditorLoaded)
	{
		_updateTexturingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateLightingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneousMenu();
	}
	if(_isEditorLoaded)
	{
		_updateWaterCreating();
	}
	if(_isEditorLoaded)
	{
		_updateWaterChoosing();
	}
	if(_isEditorLoaded)
	{
		_updateWaterDeleting();
	}
	if(_isEditorLoaded)
	{
		_updateCamera();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}

void WaterEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "waterEditorMenuMain")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getGlobalScreen()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("waterCreate", "Create Water", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingWater = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto IDs = getLoadedWaterIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getGlobalScreen()->createChoiceForm("waterList", "Edit Water", fvec2(0.0f, 0.1f), IDs);
			_isChoosingWater = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto IDs = getLoadedWaterIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getGlobalScreen()->createChoiceForm("waterList", "Delete Water", fvec2(0.0f, 0.1f), IDs);
			_isChoosingWater = true;
			_isDeletingWater = true;
		}

		// Update answer forms
		if(_gui.getGlobalScreen()->isAnswerFormConfirmed("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveWaterEntitiesToFile();
			unload();
			return;
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
	}
}

void WaterEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "waterEditorMenuChoice")
	{
		// Temporary values
		float size = _fe3d.water_getSize(_currentWaterID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuMain");
			_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("waterID")->getEntityID(), false);
			_fe3d.water_setWireframed(_currentWaterID, false);
			_fe3d.water_select("");
			_currentWaterID = "";
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("size", "Size", size, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("texturing")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuTexturing");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lighting")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuLighting");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("miscellaneous")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuMiscellaneous");
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("size", size, {0.0f}))
		{
			_fe3d.water_setSize(_currentWaterID, size);
		}

		// Update buttons hoverability
		screen->getButton("lighting")->setHoverable(_fe3d.water_isExisting(_currentWaterID));
		screen->getButton("miscellaneous")->setHoverable(_fe3d.water_isExisting(_currentWaterID));
	}
}

void WaterEditor::_updateWaterCreating()
{
	if(_isCreatingWater)
	{
		string newWaterID;

		// Create if user filled in a new ID
		if(_gui.getGlobalScreen()->checkValueForm("waterCreate", newWaterID, {}))
		{
			// @ sign not allowed
			if(newWaterID.find('@') == string::npos)
			{
				// Spaces not allowed
				if(newWaterID.find(' ') == string::npos)
				{
					// Add @ sign to new ID
					newWaterID = ("@" + newWaterID);

					// If water not existing yet
					if(find(_loadedWaterIDs.begin(), _loadedWaterIDs.end(), newWaterID) == _loadedWaterIDs.end())
					{
						// Create water
						_fe3d.water_create(newWaterID);

						// Check if water creation went well
						if(_fe3d.water_isExisting(newWaterID))
						{
							// Go to next screen
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");

							// Select water
							_currentWaterID = newWaterID;
							_loadedWaterIDs.push_back(newWaterID);
							_fe3d.water_select(newWaterID);

							// Miscellaneous
							_fe3d.text_setContent(_gui.getGlobalScreen()->getTextField("waterID")->getEntityID(), "Water: " + newWaterID.substr(1), 0.025f);
							_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("waterID")->getEntityID(), true);
							_isCreatingWater = false;
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
	if(_isChoosingWater)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("waterList");

		// Hide last water
		_fe3d.water_select("");

		// Check if a water ID is hovered
		if(!selectedButtonID.empty())
		{
			// Show water
			_fe3d.water_select("@" + selectedButtonID);

			// Check if LMB is pressed
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select water
				_currentWaterID = ("@" + selectedButtonID);

				// Go to next screen
				if(!_isDeletingWater)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
					_fe3d.text_setContent(_gui.getGlobalScreen()->getTextField("waterID")->getEntityID(), "Water: " + _currentWaterID.substr(1), 0.025f);
					_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("waterID")->getEntityID(), true);
				}

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("waterList");
				_isChoosingWater = false;
			}
		}
		else if(_gui.getGlobalScreen()->isChoiceFormCancelled("waterList")) // Cancelled choosing
		{
			_isChoosingWater = false;
			_isDeletingWater = false;
			_gui.getGlobalScreen()->deleteChoiceForm("waterList");
		}
	}
}

void WaterEditor::_updateWaterDeleting()
{
	if(_isDeletingWater && _currentWaterID != "")
	{
		// Add answer form
		if(!_gui.getGlobalScreen()->isAnswerFormExisting("delete"))
		{
			_gui.getGlobalScreen()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		// Update answer form
		if(_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			// Delete entity
			_fe3d.water_delete(_currentWaterID);

			// Delete from ID record
			_loadedWaterIDs.erase(remove(_loadedWaterIDs.begin(), _loadedWaterIDs.end(), _currentWaterID), _loadedWaterIDs.end());
			_isDeletingWater = false;
			_currentWaterID = "";
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_fe3d.water_select("");
			_isDeletingWater = false;
			_currentWaterID = "";
		}
	}
}