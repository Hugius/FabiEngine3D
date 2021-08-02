#include "scene_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void SceneEditor::_updateModelPlacing()
{
	if (_isEditorLoaded)
	{
		// Only if user is in placement mode
		if (!_currentPreviewModelID.empty())
		{
			if (_fe3d.terrainEntity_getSelectedID() == "") // Placing without terrain
			{
				// Retrieve current position
				Vec3 newPosition;
				if (_fe3d.modelEntity_isInstanced(_currentPreviewModelID))
				{
					newPosition = _fe3d.modelEntity_getInstancedOffsets(_currentPreviewModelID)[0];
				}
				else
				{
					newPosition = _fe3d.modelEntity_getPosition(_currentPreviewModelID);
				}

				// Update position change
				bool filledX = _gui.getGlobalScreen()->hasValueFormChanged("positionX", newPosition.x, { });
				bool filledY = _gui.getGlobalScreen()->hasValueFormChanged("positionY", newPosition.y, { });
				bool filledZ = _gui.getGlobalScreen()->hasValueFormChanged("positionZ", newPosition.z, { });

				// Update position
				if (_fe3d.modelEntity_isInstanced(_currentPreviewModelID))
				{
					_fe3d.modelEntity_setInstanced(_currentPreviewModelID, true, { newPosition });
				}
				else
				{
					_fe3d.modelEntity_setPosition(_currentPreviewModelID, newPosition);
				}
				
				// Check if model must be placed
				if (_gui.getGlobalScreen()->isValueFormConfirmed())
				{
					// Remove the '@'
					const string rawID = _currentPreviewModelID.substr(1);

					// Instanced model has different ID composition
					if (_fe3d.modelEntity_isInstanced(_currentPreviewModelID))
					{
						_copyPreviewModel(rawID, _currentPreviewModelID, newPosition);
					}
					else
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

						// Add model
						_copyPreviewModel(newID, _currentPreviewModelID, newPosition);
					}
				}

				// Check if placement mode must be disabled
				if (_gui.getGlobalScreen()->isValueFormConfirmed() || _gui.getGlobalScreen()->isValueFormCancelled())
				{
					_fe3d.modelEntity_setVisible(_currentPreviewModelID, false);
					string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
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

							// Retrieve new position
							auto newPosition = _fe3d.misc_getRaycastPointOnTerrain();

							// Update position
							if (_fe3d.modelEntity_isInstanced(_currentPreviewModelID))
							{
								_fe3d.modelEntity_setInstanced(_currentPreviewModelID, true, { newPosition });
							}
							else
							{
								_fe3d.modelEntity_setPosition(_currentPreviewModelID, newPosition);
							}
						}
						else
						{
							// Hide preview model
							_fe3d.modelEntity_setVisible(_currentPreviewModelID, false);
						}

						// Check if model must be placed
						if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.misc_isRaycastPointOnTerrainValid())
						{
							// Remove the '@'
							const string rawID = _currentPreviewModelID.substr(1);

							// Instanced model has different ID composition
							if (_fe3d.modelEntity_isInstanced(_currentPreviewModelID))
							{
								auto newPosition = _fe3d.modelEntity_getInstancedOffsets(_currentPreviewModelID)[0];
								_copyPreviewModel(rawID, _currentPreviewModelID, newPosition);
							}
							else
							{	
							BEGIN2:
								// Adding a number to make it unique
								int randomSerial = Tools::getRandomInteger(0, INT_MAX);
								auto newID = rawID + "_" + to_string(randomSerial);

								// Check if ID already exists
								if (_fe3d.modelEntity_isExisting(newID))
								{
									goto BEGIN2;
								}

								// Add model
								auto newPosition = _fe3d.modelEntity_getPosition(_currentPreviewModelID);
								_copyPreviewModel(newID, _currentPreviewModelID, newPosition);
							}
						}
						else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Disable placement mode
						{
							_fe3d.modelEntity_setVisible(_currentPreviewModelID, false);
							string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
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
}