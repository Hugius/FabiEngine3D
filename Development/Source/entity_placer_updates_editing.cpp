#include "entity_placer.hpp"

void EntityPlacer::_updateModelEditing()
{
	static int lightnessMultiplier = 1;
	static string activeModelID = "";
	string selectedModelID = "";

	if (_isLoaded)
	{
		if (_currentModelName == "")
		{
			// Check if user selected model
			for (auto& entityID : _fe3d.gameEntity_getAllIDs())
			{
				if (_fe3d.collision_checkCursorInEntity(entityID))
				{
					// Select model if none active yet
					if (activeModelID == "")
					{
						selectedModelID = entityID;

						// Check if user clicked model
						if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
						{
							activeModelID = selectedModelID;
						}
					}
				}
				else
				{
					// Don't reset if model is active
					if (entityID != activeModelID)
					{
						_fe3d.gameEntity_setLightness(entityID, 1.0f);
					}
				}
			}

			// Check if user made the active model inactive
			if (selectedModelID == "")
			{
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT)) // LMB pressed
				{
					activeModelID = "";
				}
			}

			// Always set active model as selected
			if(activeModelID != "" && selectedModelID == "")
			{
				selectedModelID = activeModelID;
			}

			// Resetting lightness direciton if nothing selected
			if (selectedModelID == "")
			{
				std::cout << "hoi";
				lightnessMultiplier = 1;
			}

			// Update lightness direction
			if (selectedModelID != "")
			{
				// Check if lightness reached bounds
				if (_fe3d.gameEntity_getLightness(selectedModelID) >= 1.0f || _fe3d.gameEntity_getLightness(selectedModelID) <= 0.0f)
				{
					lightnessMultiplier *= -1;
				}

				// Change lightness
				float speed = (_blinkingSpeed * static_cast<float>(lightnessMultiplier));
				_fe3d.gameEntity_setLightness(selectedModelID, _fe3d.gameEntity_getLightness(selectedModelID) + speed);
			}
		}
		else
		{
			// Reset when user wants to place models again
			for (auto& entityID : _fe3d.gameEntity_getAllIDs())
			{
				_fe3d.gameEntity_setLightness(entityID, 1.0f);
				lightnessMultiplier = 1;
				activeModelID = "";
				selectedModelID = "";
			}
		}
	}
}

void EntityPlacer::_updateBillboardEditing()
{
	if (_isLoaded)
	{

	}
}

void EntityPlacer::_updateLightEditing()
{
	if (_isLoaded)
	{

	}
}