#include "scene_editor.hpp"
#include "tools.hpp"

void SceneEditor::_updateBillboardPlacing()
{
	// Only if user is in placement mode
	if (!_currentPreviewBillboardID.empty())
	{
		if (_fe3d.terrainEntity_getSelectedID().empty()) // Placing without terrain
		{
			// Retrieve current position
			auto newPosition = _fe3d.billboardEntity_getPosition(_currentPreviewBillboardID);

			// Update value forms
			_gui.getGlobalScreen()->checkValueForm("positionX", newPosition.x, {});
			_gui.getGlobalScreen()->checkValueForm("positionY", newPosition.y, {});
			_gui.getGlobalScreen()->checkValueForm("positionZ", newPosition.z, {});

			// Update position
			_fe3d.billboardEntity_setPosition(_currentPreviewBillboardID, newPosition);

			// Check if billboard must be placed
			if (_gui.getGlobalScreen()->isValueFormConfirmed())
			{
				// Adding a number to make it unique
			BEGIN1:
				int randomSerial = Math::getRandomInteger(0, INT_MAX);
				const string newID = (_currentPreviewBillboardID.substr(1) + "_" + to_string(randomSerial));

				// Check if billboard already exists
				if (_fe3d.billboardEntity_isExisting(newID))
				{
					goto BEGIN1;
				}

				// Create billboard
				_copyPreviewBillboard(newID, _currentPreviewBillboardID, newPosition);
			}

			// Check if placement mode must be disabled
			if (_gui.getGlobalScreen()->isValueFormConfirmed() || _gui.getGlobalScreen()->isValueFormCancelled())
			{
				_fe3d.billboardEntity_setVisible(_currentPreviewBillboardID, false);
				_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), false);
				_currentPreviewBillboardID = "";
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
					if (_fe3d.raycast_isPointOnTerrainValid())
					{
						// Show preview billboard
						_fe3d.billboardEntity_setVisible(_currentPreviewBillboardID, true);

						// Update position
						_fe3d.billboardEntity_setPosition(_currentPreviewBillboardID, (_fe3d.raycast_getPointOnTerrain() + BILLBOARD_TERRAIN_OFFSET));
					}
					else
					{
						// Hide preview billboard
						_fe3d.billboardEntity_setVisible(_currentPreviewBillboardID, false);
					}

					// Check if billboard must be placed
					if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.raycast_isPointOnTerrainValid())
					{
						// Temporary values
						const auto newPosition = _fe3d.billboardEntity_getPosition(_currentPreviewBillboardID);

					BEGIN2:
						// Adding a number to make it unique
						const string newID = (_currentPreviewBillboardID.substr(1) + "_" + to_string(Math::getRandomInteger(0, INT_MAX)));

						// Check if billboard already exists
						if (_fe3d.billboardEntity_isExisting(newID))
						{
							goto BEGIN2;
						}

						// Create billboard
						_copyPreviewBillboard(newID, _currentPreviewBillboardID, newPosition);
					}
					else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Disable placement mode
					{
						_fe3d.billboardEntity_setVisible(_currentPreviewBillboardID, false);
						_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), false);
						_currentPreviewBillboardID = "";
					}
				}
				else
				{
					_fe3d.billboardEntity_setVisible(_currentPreviewBillboardID, false);
				}
			}
			else
			{
				_fe3d.billboardEntity_setVisible(_currentPreviewBillboardID, false);
			}
		}
	}
}