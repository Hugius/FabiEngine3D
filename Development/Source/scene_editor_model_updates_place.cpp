#include "scene_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void SceneEditor::_updateModelPlacing()
{
	// Only if user is in placement mode
	if (!_currentPreviewModelID.empty())
	{
		if (_fe3d.terrainEntity_getSelectedID().empty()) // Placing without terrain
		{
			// Retrieve current position
			auto newPosition = _fe3d.modelEntity_getPosition(_currentPreviewModelID);

			// Update position change
			bool filledX = _gui.getGlobalScreen()->checkValueForm("positionX", newPosition.x, { });
			bool filledY = _gui.getGlobalScreen()->checkValueForm("positionY", newPosition.y, { });
			bool filledZ = _gui.getGlobalScreen()->checkValueForm("positionZ", newPosition.z, { });

			// Update position
			_fe3d.modelEntity_setPosition(_currentPreviewModelID, newPosition);

			// Check if model must be placed
			if (_gui.getGlobalScreen()->isValueFormConfirmed())
			{
				// Remove the '@'
				const string rawID = _currentPreviewModelID.substr(1);

				if (_fe3d.modelEntity_isInstanced(_currentPreviewModelID)) // Instanced model
				{
					if (_fe3d.modelEntity_isExisting(rawID)) // Add to existing offsets
					{
						auto offsets = _fe3d.modelEntity_getInstancedOffsets(rawID);
						offsets.push_back(newPosition);
						_fe3d.modelEntity_disableInstancing(rawID);
						_fe3d.modelEntity_enableInstancing(rawID, offsets);
					}
					else // Create new model
					{
						_copyPreviewModel(rawID, _currentPreviewModelID, Vec3(0.0f));
						_fe3d.modelEntity_disableInstancing(rawID);
						_fe3d.modelEntity_enableInstancing(rawID, { newPosition });
					}
				}
				else // Non-instanced model
				{
					// Adding a number to make it unique
				BEGIN1:
					int randomSerial = Tools::getRandomInteger(0, INT_MAX);
					auto newID = rawID + "_" + to_string(randomSerial);

					// Check if ID already exists
					if (_fe3d.modelEntity_isExisting(newID))
					{
						goto BEGIN1;
					}

					// Create model
					_copyPreviewModel(newID, _currentPreviewModelID, newPosition);
				}
			}

			// Check if placement mode must be disabled
			if (_gui.getGlobalScreen()->isValueFormConfirmed() || _gui.getGlobalScreen()->isValueFormCancelled())
			{
				_fe3d.modelEntity_setVisible(_currentPreviewModelID, false);
				auto textEntityID = _gui.getGlobalScreen()->getTextfield("selectedModelID")->getEntityID();
				_fe3d.textEntity_setVisible(textEntityID, false);
				_currentPreviewModelID = "";
			}
		}
		else // Placing on terrain
		{
			// Check if allowed by GUI
			if (_fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// Check if allowed by mouse
				if (!_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Check if a terrain is loaded
					if (_fe3d.misc_isRaycastPointOnTerrainValid())
					{
						// Show preview model
						_fe3d.modelEntity_setVisible(_currentPreviewModelID, true);

						// Update position
						_fe3d.modelEntity_setPosition(_currentPreviewModelID, _fe3d.misc_getRaycastPointOnTerrain());
					}
					else
					{
						// Hide preview model
						_fe3d.modelEntity_setVisible(_currentPreviewModelID, false);
					}

					// Check if model must be placed
					if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.misc_isRaycastPointOnTerrainValid())
					{
						//Temporary values
						const string rawID = _currentPreviewModelID.substr(1);
						const auto newPosition = _fe3d.modelEntity_getPosition(_currentPreviewModelID);

						if (_fe3d.modelEntity_isInstanced(_currentPreviewModelID)) // Instanced model
						{
							if (_fe3d.modelEntity_isExisting(rawID)) // Add to existing offsets
							{
								auto offsets = _fe3d.modelEntity_getInstancedOffsets(rawID);
								offsets.push_back(newPosition);
								_fe3d.modelEntity_disableInstancing(rawID);
								_fe3d.modelEntity_enableInstancing(rawID, offsets);
							}
							else // Create new model
							{
								_copyPreviewModel(rawID, _currentPreviewModelID, Vec3(0.0f));
								_fe3d.modelEntity_disableInstancing(rawID);
								_fe3d.modelEntity_enableInstancing(rawID, { newPosition });
							}
						}
						else // Non-instanced model
						{
						BEGIN2:
							// Adding a number to make it unique
							const string newID = rawID + "_" + to_string(Tools::getRandomInteger(0, INT_MAX));

							// Check if ID already exists
							if (_fe3d.modelEntity_isExisting(newID))
							{
								goto BEGIN2;
							}

							// Create model
							_copyPreviewModel(newID, _currentPreviewModelID, newPosition);
						}
					}
					else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Disable placement mode
					{
						_fe3d.modelEntity_setVisible(_currentPreviewModelID, false);
						auto textEntityID = _gui.getGlobalScreen()->getTextfield("selectedModelID")->getEntityID();
						_fe3d.textEntity_setVisible(textEntityID, false);
						_currentPreviewModelID = "";
					}
				}
				else
				{
					_fe3d.modelEntity_setVisible(_currentPreviewModelID, false);
				}
			}
			else
			{
				_fe3d.modelEntity_setVisible(_currentPreviewModelID, false);
			}
		}
	}
}