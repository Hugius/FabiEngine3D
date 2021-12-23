#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateBillboardPlacing()
{
	// Only if user is in placement mode
	if(!_currentTemplateBillboardID.empty())
	{
		if(_fe3d.terrain_getSelectedID().empty()) // Placing without terrain
		{
			// Retrieve current position
			auto newPosition = _fe3d.billboard_getPosition(_currentTemplateBillboardID);

			// Update value forms
			_gui.getOverlay()->checkValueForm("positionX", newPosition.x, {});
			_gui.getOverlay()->checkValueForm("positionY", newPosition.y, {});
			_gui.getOverlay()->checkValueForm("positionZ", newPosition.z, {});

			// Update position
			_fe3d.billboard_setPosition(_currentTemplateBillboardID, newPosition);

			// Check if billboard must be placed
			if(_gui.getOverlay()->isValueFormConfirmed())
			{
				// Adding a number to make it unique
				BEGIN1:
				int randomSerial = Math::getRandomNumber(0, INT_MAX);
				const string newID = (_currentTemplateBillboardID.substr(1) + "_" + to_string(randomSerial));

				// Check if billboard already exists
				if(_fe3d.billboard_isExisting(newID))
				{
					goto BEGIN1;
				}

				// Create billboard
				_copyTemplateBillboard(newID, _currentTemplateBillboardID, newPosition, false);
			}

			// Check if placement mode must be disabled
			if(_gui.getOverlay()->isValueFormConfirmed() || _gui.getOverlay()->isValueFormCancelled())
			{
				_fe3d.billboard_setVisible(_currentTemplateBillboardID, false);
				_fe3d.text_setVisible(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), false);
				_currentTemplateBillboardID = "";
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
						// Show template billboard
						_fe3d.billboard_setVisible(_currentTemplateBillboardID, true);

						// Update position
						_fe3d.billboard_setPosition(_currentTemplateBillboardID, (_fe3d.raycast_getPointOnTerrain() + BILLBOARD_TERRAIN_OFFSET));
					}
					else
					{
						// Hide template billboard
						_fe3d.billboard_setVisible(_currentTemplateBillboardID, false);
					}

					// Check if billboard must be placed
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.raycast_isPointOnTerrainValid())
					{
						// Temporary values
						const auto newPosition = _fe3d.billboard_getPosition(_currentTemplateBillboardID);

						BEGIN2:
						// Adding a number to make it unique
						const string newID = (_currentTemplateBillboardID.substr(1) + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));

						// Check if billboard already exists
						if(_fe3d.billboard_isExisting(newID))
						{
							goto BEGIN2;
						}

						// Create billboard
						_copyTemplateBillboard(newID, _currentTemplateBillboardID, newPosition, false);
					}
					else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Disable placement mode
					{
						_fe3d.billboard_setVisible(_currentTemplateBillboardID, false);
						_fe3d.text_setVisible(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), false);
						_currentTemplateBillboardID = "";
					}
				}
				else
				{
					_fe3d.billboard_setVisible(_currentTemplateBillboardID, false);
				}
			}
			else
			{
				_fe3d.billboard_setVisible(_currentTemplateBillboardID, false);
			}
		}
	}
}