#include "entity_placer.hpp"

void EntityPlacer::_updateModelPlacing()
{
	if (_isLoaded)
	{
		// Update model placing
		if (_currentModelName != "")
		{
			if (_fe3d.misc_isMouseInsideViewport() && !_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_RIGHT) && !_gui->getGlobalScreen()->isFocused())
			{
				// Show preview model
				_fe3d.gameEntity_show(_currentModelName);

				// Update preview model position
				_fe3d.gameEntity_setPosition(_currentModelName, _fe3d.terrainEntity_getMousePoint());

				// Placing model
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
				{
					// Create new ID: (no @) + modelName + count
					string newID = _currentModelName.substr(1, _currentModelName.size()) + std::to_string(_counterMap[_currentModelName]);
					_fe3d.gameEntity_add(newID, _fe3d.gameEntity_getObjPath(_currentModelName),
						_fe3d.terrainEntity_getMousePoint(), vec3(0.0f), _fe3d.gameEntity_getSize(_currentModelName));

					// Model properties
					_fe3d.gameEntity_setFaceCulled(newID, _fe3d.gameEntity_isFaceCulled(_currentModelName));
					_fe3d.gameEntity_setShadowed(newID, _fe3d.gameEntity_isShadowed(_currentModelName));
					_fe3d.gameEntity_setTransparent(newID, _fe3d.gameEntity_isTransparent(_currentModelName));
					_fe3d.gameEntity_setSpecularLighted(newID, _fe3d.gameEntity_isSpecularLighted(_currentModelName));
					_fe3d.gameEntity_setLightness(newID, _fe3d.gameEntity_getLightness(_currentModelName));
					_fe3d.gameEntity_setUvRepeat(newID, _fe3d.gameEntity_getUvRepeat(_currentModelName));
					_fe3d.gameEntity_setColor(newID, _fe3d.gameEntity_getColor(_currentModelName));
					_fe3d.aabbEntity_bindToGameEntity(newID, _fe3d.aabbEntity_getSize(_currentModelName), true);

					// Diffuse map
					if (_fe3d.gameEntity_getDiffuseMapPath(_currentModelName) != "")
					{
						_fe3d.gameEntity_setDiffuseMap(newID, _fe3d.gameEntity_getDiffuseMapPath(_currentModelName));
					}

					// Light map
					if (_fe3d.gameEntity_getLightMapPath(_currentModelName) != "")
					{
						_fe3d.gameEntity_setLightMap(newID, _fe3d.gameEntity_getLightMapPath(_currentModelName));
						_fe3d.gameEntity_setLightmapped(newID, true);
					}

					// Reflection map
					if (_fe3d.gameEntity_getReflectionMapPath(_currentModelName) != "")
					{
						_fe3d.gameEntity_setReflectionMap(newID, _fe3d.gameEntity_getReflectionMapPath(_currentModelName));
						_fe3d.gameEntity_setSkyReflective(newID, true);
					}

					// Increase 
					_counterMap[_currentModelName]++;
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

	}
}

void EntityPlacer::_updateLightPlacing()
{
	if (_isLoaded)
	{

	}
}