#include "entity_placer.hpp"

bool EntityPlacer::isLoaded()
{
	return _isLoaded;
}

void EntityPlacer::setCurrentProjectName(string projectName)
{
	_currentProjectName = projectName;
}

void EntityPlacer::_updateMiscellaneous()
{
	if (_isLoaded)
	{
		_fe3d.input_setKeyTogglingLocked(_gui->getGlobalScreen()->isFocused() || !_fe3d.misc_isMouseInsideViewport());

		// Update bounding box visibility
		if (_fe3d.input_getKeyToggled(Input::KEY_B))
		{
			_fe3d.collision_enableFrameRendering();
		}
		else
		{
			_fe3d.collision_disableFrameRendering();
		}
	}
}

void EntityPlacer::_placeModel(string modelID, string modelName, vec3 position, vec3 rotation, vec3 size)
{
	// Add game entity
	_fe3d.gameEntity_add(modelID, _fe3d.gameEntity_getObjPath(modelName), position, rotation, size);
	_fe3d.aabbEntity_bindToGameEntity(modelID, _fe3d.aabbEntity_getSize(modelName), true);

	// Model properties
	_fe3d.gameEntity_setFaceCulled(modelID, _fe3d.gameEntity_isFaceCulled(modelName));
	_fe3d.gameEntity_setShadowed(modelID, _fe3d.gameEntity_isShadowed(modelName));
	_fe3d.gameEntity_setTransparent(modelID, _fe3d.gameEntity_isTransparent(modelName));
	_fe3d.gameEntity_setSpecularLighted(modelID, _fe3d.gameEntity_isSpecularLighted(modelName));
	_fe3d.gameEntity_setUvRepeat(modelID, _fe3d.gameEntity_getUvRepeat(modelName));
	_fe3d.gameEntity_setColor(modelID, _fe3d.gameEntity_getColor(modelName));

	// Diffuse map
	if (_fe3d.gameEntity_getDiffuseMapPath(modelName) != "")
	{
		_fe3d.gameEntity_setDiffuseMap(modelID, _fe3d.gameEntity_getDiffuseMapPath(modelName));
	}

	// Light map
	if (_fe3d.gameEntity_getLightMapPath(modelName) != "")
	{
		_fe3d.gameEntity_setLightMap(modelID, _fe3d.gameEntity_getLightMapPath(modelName));
		_fe3d.gameEntity_setLightmapped(modelID, true);
	}

	// Reflection map
	if (_fe3d.gameEntity_getReflectionMapPath(modelName) != "")
	{
		_fe3d.gameEntity_setReflectionMap(modelID, _fe3d.gameEntity_getReflectionMapPath(modelName));
		_fe3d.gameEntity_setSkyReflective(modelID, true);
	}
}

void EntityPlacer::_placeModel(string modelID, vec3 position, vec3 rotation, vec3 size,
	string objPath, string diffuseMapPath, string lightMapPath, string reflectionMapPath,
	bool faceCulled, bool shadowed, bool transparent, bool specular, float specularIntensity, vec3 color, float uvRepeat, vec3 aabbSize)
{
	// Add game entity
	_fe3d.gameEntity_add(modelID, objPath, position, rotation, size);
	_fe3d.aabbEntity_bindToGameEntity(modelID, aabbSize, true);

	// Model properties
	_fe3d.gameEntity_setFaceCulled(modelID, faceCulled);
	_fe3d.gameEntity_setShadowed(modelID, shadowed);
	_fe3d.gameEntity_setTransparent(modelID, transparent);
	_fe3d.gameEntity_setSpecularLighted(modelID, specular);
	_fe3d.gameEntity_setSpecularIntensity(modelID, specularIntensity);
	_fe3d.gameEntity_setColor(modelID, color);
	_fe3d.gameEntity_setUvRepeat(modelID, uvRepeat);

	// Diffuse map
	if (diffuseMapPath != "")
	{
		_fe3d.gameEntity_setDiffuseMap(modelID, diffuseMapPath);
	}

	// Light map
	if (lightMapPath != "")
	{
		_fe3d.gameEntity_setLightMap(modelID, lightMapPath);
		_fe3d.gameEntity_setLightmapped(modelID, true);
	}

	// Reflection map
	if (reflectionMapPath != "")
	{
		_fe3d.gameEntity_setReflectionMap(modelID, reflectionMapPath);
		_fe3d.gameEntity_setSkyReflective(modelID, true);
	}
}

void EntityPlacer::_updateModelBlinking(string modelID, int& multiplier)
{
	// Reset multiplier if nothing active / selected
	if (modelID == "")
	{
		multiplier = 1;
	}

	// Update model lightness
	if (modelID != "")
	{
		// Check if lightness reached bounds
		if (_fe3d.gameEntity_getLightness(modelID) > 1.0f || _fe3d.gameEntity_getLightness(modelID) < 0.0f)
		{
			multiplier *= -1;
		}

		// Set model lightness
		float speed = (_modelBlinkingSpeed * static_cast<float>(multiplier));
		_fe3d.gameEntity_setLightness(modelID, _fe3d.gameEntity_getLightness(modelID) + speed);
	}
}

void EntityPlacer::_updateLightbulbAnimation(string modelID, int& multiplier)
{
	// Reset multiplier if nothing active / selected
	if (modelID == "")
	{
		multiplier = 1;
	}
	
	// Update lightbulb animation
	if (modelID != "")
	{
		// Check if model size reached bounds
		if (_fe3d.gameEntity_getSize(modelID).x > _defaultLightbulbSize.x * 1.5f || 
			_fe3d.gameEntity_getSize(modelID).x < _defaultLightbulbSize.x)
		{
			multiplier *= -1;
		}

		// Set model size
		float speed = (_lightbulbAnimationSpeed * static_cast<float>(multiplier));
		_fe3d.gameEntity_setSize(modelID, _fe3d.gameEntity_getSize(modelID) + vec3(speed));
		_fe3d.aabbEntity_setSize(modelID, _fe3d.aabbEntity_getSize(modelID) + vec3(speed));
	}
}