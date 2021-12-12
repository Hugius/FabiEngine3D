#include "water_editor.hpp"
#include "logger.hpp"

void WaterEditor::_updateCamera()
{
	// Check if third person view is enabled
	if(_fe3d.camera_isThirdPersonViewEnabled())
	{
		// Update distance scrolling
		auto scrollOffset = _fe3d.input_getMouseWheelY();
		auto cameraDistance = _fe3d.camera_getThirdPersonDistance();
		cameraDistance = max(MIN_CAMERA_DISTANCE, cameraDistance - (static_cast<float>(scrollOffset) * CAMERA_DISTANCE_SPEED));
		_fe3d.camera_setThirdPersonDistance(cameraDistance);

		// Hide cursor
		_fe3d.image_setVisible("@@cursor", false);
	}

	// Check if allowed by GUI
	if(!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Check if RMB pressed
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
		{
			// Check third person view status
			if(_fe3d.camera_isThirdPersonViewEnabled())
			{
				_fe3d.camera_disableThirdPersonView();
			}
			else
			{
				_fe3d.camera_enableThirdPersonView(_fe3d.camera_getThirdPersonYaw(), _fe3d.camera_getThirdPersonPitch());
			}
		}
	}

	// Disable third person view if necessary
	if(_fe3d.camera_isThirdPersonViewEnabled())
	{
		if(_gui.getGlobalScreen()->isFocused())
		{
			_fe3d.camera_disableThirdPersonView();
		}
	}
}

void WaterEditor::_updateMiscellaneous()
{
	// Check if allowed by GUI
	if(!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Update reference model visibility
		if(_fe3d.input_isKeyPressed(InputType::KEY_R))
		{
			if(_fe3d.model_isVisible("@@box"))
			{
				_fe3d.model_setVisible("@@box", false);
			}
			else
			{
				_fe3d.model_setVisible("@@box", true);
			}
		}

		// Update wireframe rendering
		if(_fe3d.water_isExisting(_currentWaterID))
		{
			if(_fe3d.input_isKeyPressed(InputType::KEY_F))
			{
				if(_fe3d.water_isWireframed(_currentWaterID))
				{
					_fe3d.water_setWireframed(_currentWaterID, false);
				}
				else
				{
					_fe3d.water_setWireframed(_currentWaterID, true);
				}
			}
		}

		// Update debug rendering
		if(_fe3d.input_isKeyPressed(InputType::KEY_H))
		{
			if(_fe3d.misc_isDebugRenderingEnabled())
			{
				_fe3d.misc_disableDebugRendering();
			}
			else
			{
				_fe3d.misc_enableDebugRendering();
			}
		}
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