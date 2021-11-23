#include "world_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void WorldEditor::_updateModelPlacing()
{
	// Only if user is in placement mode
	if(!_currentPreviewModelID.empty())
	{
		if(_fe3d.terrain_getSelectedID().empty()) // Placing without terrain
		{
			// Retrieve current position
			auto newPosition = _fe3d.model_getBasePosition(_currentPreviewModelID);

			// Update value forms
			_gui.getGlobalScreen()->checkValueForm("positionX", newPosition.x, {});
			_gui.getGlobalScreen()->checkValueForm("positionY", newPosition.y, {});
			_gui.getGlobalScreen()->checkValueForm("positionZ", newPosition.z, {});

			// Update position
			_fe3d.model_setBasePosition(_currentPreviewModelID, newPosition);

			// Check if model must be placed
			if(_gui.getGlobalScreen()->isValueFormConfirmed())
			{
				// Remove the '@'
				const string rawID = _currentPreviewModelID.substr(1);

				if(_fe3d.model_isInstanced(_currentPreviewModelID)) // Instanced model
				{
					if(_fe3d.model_isExisting(rawID)) // Add to existing offsets
					{
						auto offsets = _fe3d.model_getInstancedOffsets(rawID);
						offsets.push_back(newPosition);
						_fe3d.model_disableInstancing(rawID);
						_fe3d.model_enableInstancing(rawID, offsets);
					}
					else // Create new model
					{
						_copyPreviewModel(rawID, _currentPreviewModelID, fvec3(0.0f), false);
						_fe3d.model_disableInstancing(rawID);
						_fe3d.model_enableInstancing(rawID, {newPosition });
					}
				}
				else // Non-instanced model
				{
					// Adding a number to make it unique
				BEGIN1:
					const string newID = (rawID + "_" + to_string(Math::getRandomInteger(0, INT_MAX)));

					// Check if model already exists
					if(_fe3d.model_isExisting(newID))
					{
						goto BEGIN1;
					}

					// Create model
					_copyPreviewModel(newID, _currentPreviewModelID, newPosition, false);
				}
			}

			// Check if placement mode must be disabled
			if(_gui.getGlobalScreen()->isValueFormConfirmed() || _gui.getGlobalScreen()->isValueFormCancelled())
			{
				_fe3d.model_setVisible(_currentPreviewModelID, false);
				_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), false);
				_currentPreviewModelID = "";
			}
		}
		else // Placing on terrain
		{
			// Check if allowed by GUI
			if(_fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// Check if allowed by mouse
				if(!_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Check if a terrain is loaded
					if(_fe3d.raycast_isPointOnTerrainValid())
					{
						// Show preview model
						_fe3d.model_setVisible(_currentPreviewModelID, true);

						// Update position
						_fe3d.model_setBasePosition(_currentPreviewModelID, (_fe3d.raycast_getPointOnTerrain() + MODEL_TERRAIN_OFFSET));
					}
					else
					{
						// Hide preview model
						_fe3d.model_setVisible(_currentPreviewModelID, false);
					}

					// Check if model must be placed
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.raycast_isPointOnTerrainValid())
					{
						// Temporary values
						const string rawID = _currentPreviewModelID.substr(1);
						const auto newPosition = _fe3d.model_getBasePosition(_currentPreviewModelID);

						if(_fe3d.model_isInstanced(_currentPreviewModelID)) // Instanced model
						{
							if(_fe3d.model_isExisting(rawID)) // Add to existing offsets
							{
								auto offsets = _fe3d.model_getInstancedOffsets(rawID);
								offsets.push_back(newPosition);
								_fe3d.model_disableInstancing(rawID);
								_fe3d.model_enableInstancing(rawID, offsets);
							}
							else // Create new model
							{
								_copyPreviewModel(rawID, _currentPreviewModelID, fvec3(0.0f), false);
								_fe3d.model_disableInstancing(rawID);
								_fe3d.model_enableInstancing(rawID, {newPosition });
							}
						}
						else // Non-instanced model
						{
						BEGIN2:
							// Adding a number to make it unique
							const string newID = (rawID + "_" + to_string(Math::getRandomInteger(0, INT_MAX)));

							// Check if model already exists
							if(_fe3d.model_isExisting(newID))
							{
								goto BEGIN2;
							}

							// Create model
							_copyPreviewModel(newID, _currentPreviewModelID, newPosition, false);
						}
					}
					else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Disable placement mode
					{
						_fe3d.model_setVisible(_currentPreviewModelID, false);
						_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), false);
						_currentPreviewModelID = "";
					}
				}
				else
				{
					_fe3d.model_setVisible(_currentPreviewModelID, false);
				}
			}
			else
			{
				_fe3d.model_setVisible(_currentPreviewModelID, false);
			}
		}
	}
}