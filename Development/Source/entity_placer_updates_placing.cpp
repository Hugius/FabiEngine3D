#include "entity_placer.hpp"

void EntityPlacer::_updateModelPlacing()
{
	if (_isLoaded)
	{
		// Only if user is in placement mode
		if (_currentModelName != "")
		{
			// Check if mouse behavior isn't being invalid
			if (_fe3d.misc_isMouseInsideViewport() && !_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_RIGHT) && !_gui->getGlobalScreen()->isFocused())
			{
				// Default placement position
				vec3 newPosition = vec3(0.0f);

				// Check if a terrain is loaded
				if(_fe3d.terrainEntity_getSelectedID() != "")
				{
					// Show preview model
					_fe3d.gameEntity_show(_currentModelName);

					// Update preview model position
					newPosition = _fe3d.terrainEntity_getMousePoint();
					_fe3d.gameEntity_setPosition(_currentModelName, newPosition);
				}

				// Placing model
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) || _fe3d.terrainEntity_getSelectedID() == "")  // Can be bypassed if terrain does not exist
				{
					// Add new model
					begin: int randomSerial = _fe3d.misc_getUniqueInt(0, INT_MAX);
					string newID = _currentModelName.substr(1, _currentModelName.size()) + std::to_string(randomSerial); // Remove the '@'

					// Check if ID not already exists
					if (_fe3d.gameEntity_isExisting(newID))
					{
						goto begin;
					}

					// Add model
					_placeModel(newID, _currentModelName, newPosition, vec3(0.0f), _fe3d.gameEntity_getSize(_currentModelName));

					// Disable placement mode if no terrain availible to choose position from
					if (_fe3d.terrainEntity_getSelectedID() == "")
					{
						_currentModelName = "";
					}
				}
				else if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_MIDDLE)) // Cancelling model placement
				{
					// Hide preview model
					_fe3d.gameEntity_hide(_currentModelName);
					_currentModelName = "";
					string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
					_fe3d.textEntity_hide(textEntityID);
				}
			}
			else
			{
				// Hide preview model
				_fe3d.gameEntity_hide(_currentModelName);
			}
		}
	}
}

void EntityPlacer::_updateBilboardPlacing()
{
	if (_isLoaded)
	{
		// Only if user is in placement mode
		if (_currentBillboardName != "")
		{

		}
	}
}

void EntityPlacer::_updateLightPlacing()
{
	if (_isLoaded)
	{
		// Only if user is in placement mode
		if (_isPlacingPointlight)
		{
			// Check if mouse behavior isn't being invalid
			if (_fe3d.misc_isMouseInsideViewport() && !_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_RIGHT) && !_gui->getGlobalScreen()->isFocused())
			{
				// Default placement position
				vec3 newPosition = vec3(0.0f);

				// Check if a terrain is loaded
				if (_fe3d.terrainEntity_getSelectedID() != "")
				{
					// Update preview pointlight position
					newPosition = _fe3d.terrainEntity_getMousePoint();
					_fe3d.lightEntity_setPosition(_previewPointlightID, newPosition + vec3(0.0f, 25.0f, 0.0f));
				}

				// Placing pointlight
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) || _fe3d.terrainEntity_getSelectedID() == "") // Can be bypassed if terrain does not exist
				{
					// Add new pointlight
					begin: int randomSerial = _fe3d.misc_getUniqueInt(0, INT_MAX);
					string newID = "pointlight" + std::to_string(randomSerial); // Remove the '@'

					// Check if ID not already exists
					if (_fe3d.lightEntity_isExisting(newID))
					{
						goto begin;
					}

					// Disable placement mode if no terrain availible to choose position from
					if (_fe3d.terrainEntity_getSelectedID() == "")
					{
						_isPlacingPointlight = false;
					}
				}
				else if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_MIDDLE)) // Cancelling pointlight placement
				{
					// Hide preview pointlight
					_fe3d.lightEntity_hide(_previewPointlightID);
					_isPlacingPointlight = false;
				}
			}
			else
			{
				// Hide preview pointlight
				_fe3d.lightEntity_hide(_previewPointlightID);
			}
		}
	}
}