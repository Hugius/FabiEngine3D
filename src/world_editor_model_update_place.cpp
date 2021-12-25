#include "world_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void WorldEditor::_updateModelPlacing()
{
	if(!_currentTemplateModelID.empty())
	{
		if(_fe3d.terrain_getSelectedID().empty()) // Placing without terrain
		{
			// Retrieve current position
			auto newPosition = _fe3d.model_getBasePosition(_currentTemplateModelID);

			// Update value forms
			_gui.getOverlay()->checkValueForm("positionX", newPosition.x, {});
			_gui.getOverlay()->checkValueForm("positionY", newPosition.y, {});
			_gui.getOverlay()->checkValueForm("positionZ", newPosition.z, {});

			// Update position
			_fe3d.model_setBasePosition(_currentTemplateModelID, newPosition);

			// Check if model must be placed
			if(_gui.getOverlay()->isValueFormConfirmed())
			{
				// Remove the '@'
				const string rawID = _currentTemplateModelID.substr(1);

				// Adding a number to make it unique
				BEGIN1:;
				const string newID = (rawID + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));

				// Check if model already exists
				if(_fe3d.model_isExisting(newID))
				{
					goto BEGIN1;
				}

				// Create model
				_copyTemplateModel(newID, _currentTemplateModelID, newPosition, false);
			}

			// Check if placement mode must be disabled
			if(_gui.getOverlay()->isValueFormConfirmed() || _gui.getOverlay()->isValueFormCancelled())
			{
				_fe3d.model_setVisible(_currentTemplateModelID, false);
				_fe3d.text_setVisible(_gui.getOverlay()->getTextField("modelID")->getEntityID(), false);
				_currentTemplateModelID = "";
			}
		}
		else // Placing on terrain
		{
			// Check if allowed by GUI
			if(_fe3d.misc_isCursorInsideViewport() && !_gui.getOverlay()->isFocused())
			{
				// Check if allowed by mouse
				if(!_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Check if terrain is loaded
					if(_fe3d.raycast_isPointOnTerrainValid())
					{
						// Show template model
						_fe3d.model_setVisible(_currentTemplateModelID, true);

						// Update position
						_fe3d.model_setBasePosition(_currentTemplateModelID, (_fe3d.raycast_getPointOnTerrain() + MODEL_TERRAIN_OFFSET));
					}
					else
					{
						// Hide template model
						_fe3d.model_setVisible(_currentTemplateModelID, false);
					}

					// Check if model must be placed
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.raycast_isPointOnTerrainValid())
					{
						// Temporary values
						const string rawID = _currentTemplateModelID.substr(1);
						const auto newPosition = _fe3d.model_getBasePosition(_currentTemplateModelID);

						// Adding a number to make it unique
						BEGIN2:;
						const string newID = (rawID + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));

						// Check if model already exists
						if(_fe3d.model_isExisting(newID))
						{
							goto BEGIN2;
						}

						// Create model
						_copyTemplateModel(newID, _currentTemplateModelID, newPosition, false);
					}
					else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Disable placement mode
					{
						_fe3d.model_setVisible(_currentTemplateModelID, false);
						_fe3d.text_setVisible(_gui.getOverlay()->getTextField("modelID")->getEntityID(), false);
						_currentTemplateModelID = "";
					}
				}
				else
				{
					_fe3d.model_setVisible(_currentTemplateModelID, false);
				}
			}
			else
			{
				_fe3d.model_setVisible(_currentTemplateModelID, false);
			}
		}
	}
}