#include "scene_editor.hpp"

#include <algorithm>

bool SceneEditor::isLoaded()
{
	return _isLoaded;
}

void SceneEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

void SceneEditor::_selectModel(const string& modelID)
{
	_selectedModelID = modelID;

	// Removing the unique number from the modelID
	string modelName = modelID.substr(modelID.find('@') + 1);

	// Update selected model text
	string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
	_fe3d.textEntity_show(textEntityID);
	_fe3d.textEntity_setTextContent(textEntityID, "Selected: " + modelName, 0.025f);

	// Change cursor
	_fe3d.guiEntity_changeTexture("@@cursor", "Engine\\Textures\\cursor_pointing.png");
}

void SceneEditor::_activateModel(const string& modelID)
{
	_activeModelID = modelID;
	_transformation = Transformation::TRANSLATION;

	// Activate properties screen
	_rightWindow->getScreen("modelPropertiesMenu")->getButton("translation")->setHoverable(false);
	_rightWindow->getScreen("modelPropertiesMenu")->getButton("rotation")->setHoverable(true);
	_rightWindow->getScreen("modelPropertiesMenu")->getButton("scaling")->setHoverable(true);

	// Filling writefields
	vec3 position = _fe3d.gameEntity_getPosition(_activeModelID);
	_rightWindow->getScreen("modelPropertiesMenu")->getWriteField("x")->setTextContent(std::to_string(static_cast<int>(position.x)));
	_rightWindow->getScreen("modelPropertiesMenu")->getWriteField("y")->setTextContent(std::to_string(static_cast<int>(position.y)));
	_rightWindow->getScreen("modelPropertiesMenu")->getWriteField("z")->setTextContent(std::to_string(static_cast<int>(position.z)));
}

void SceneEditor::_placeModel(const string& modelID, string modelName, vec3 position, vec3 rotation, vec3 size)
{
	// Add game entity
	_fe3d.gameEntity_add(modelID, _fe3d.gameEntity_getObjPath(modelName), position, rotation, size);
	_fe3d.aabbEntity_bindToGameEntity(modelID, _fe3d.aabbEntity_getSize(modelName), true);
	
	// Model properties
	_fe3d.gameEntity_setStaticToCamera(modelID, _fe3d.gameEntity_isStaticToCamera(modelName));
	_fe3d.gameEntity_setFaceCulled(modelID, _fe3d.gameEntity_isFaceCulled(modelName));
	_fe3d.gameEntity_setShadowed(modelID, _fe3d.gameEntity_isShadowed(modelName));
	_fe3d.gameEntity_setTransparent(modelID, _fe3d.gameEntity_isTransparent(modelName));
	_fe3d.gameEntity_setSceneReflective(modelID, _fe3d.gameEntity_isSceneReflective(modelName));
	_fe3d.gameEntity_setSpecularLighted(modelID, _fe3d.gameEntity_isSpecularLighted(modelName));
	_fe3d.gameEntity_setSpecularFactor(modelID, _fe3d.gameEntity_getSpecularFactor(modelName));
	_fe3d.gameEntity_setSpecularIntensity(modelID, _fe3d.gameEntity_getSpecularIntensity(modelName));
	_fe3d.gameEntity_setLightness(modelID, _fe3d.gameEntity_getLightness(modelName));
	_fe3d.gameEntity_setOriginalLightness(modelID, _fe3d.gameEntity_getOriginalLightness(modelName));
	_fe3d.gameEntity_setColor(modelID, _fe3d.gameEntity_getColor(modelName));
	_fe3d.gameEntity_setUvRepeat(modelID, _fe3d.gameEntity_getUvRepeat(modelName));

	// Diffuse map
	if (_fe3d.gameEntity_getDiffuseMapPath(modelName) != "")
	{
		_fe3d.gameEntity_setDiffuseMap(modelID, _fe3d.gameEntity_getDiffuseMapPath(modelName));
	}

	// Light map
	if (_fe3d.gameEntity_getLightMapPath(modelName) != "")
	{
		_fe3d.gameEntity_setLightMap(modelID, _fe3d.gameEntity_getLightMapPath(modelName));
		_fe3d.gameEntity_setLightMapped(modelID, true);
	}

	// Reflection map
	if (_fe3d.gameEntity_getReflectionMapPath(modelName) != "")
	{
		_fe3d.gameEntity_setReflectionMap(modelID, _fe3d.gameEntity_getReflectionMapPath(modelName));
		_fe3d.gameEntity_setSkyReflective(modelID, true);
	}
}

void SceneEditor::_placeModel(const string& modelID, vec3 position, vec3 rotation, vec3 size, string objPath, string diffuseMapPath,
	string lightMapPath, string reflectionMapPath, bool isFrozen, bool isFaceCulled, bool isShadowed, bool isTransparent, bool isReflective,
	bool isSpecular, float specularFactor, float specularIntensity, float lightness, vec3 color, float uvRepeat, vec3 aabbSize)
{
	// Add game entity
	_fe3d.gameEntity_add(modelID, objPath, position, rotation, size);
	_fe3d.aabbEntity_bindToGameEntity(modelID, aabbSize, true);

	// Model properties
	_fe3d.gameEntity_setStaticToCamera(modelID, isFrozen);
	_fe3d.gameEntity_setFaceCulled(modelID, isFaceCulled);
	_fe3d.gameEntity_setShadowed(modelID, isShadowed);
	_fe3d.gameEntity_setTransparent(modelID, isTransparent);
	_fe3d.gameEntity_setSceneReflective(modelID, isReflective);
	_fe3d.gameEntity_setSpecularLighted(modelID, isSpecular);
	_fe3d.gameEntity_setSpecularFactor(modelID, specularFactor);
	_fe3d.gameEntity_setSpecularIntensity(modelID, specularIntensity);
	_fe3d.gameEntity_setOriginalLightness(modelID, lightness);
	_fe3d.gameEntity_setLightness(modelID, lightness);
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
		_fe3d.gameEntity_setLightMapped(modelID, true);
	}

	// Reflection map
	if (reflectionMapPath != "")
	{
		_fe3d.gameEntity_setReflectionMap(modelID, reflectionMapPath);
		_fe3d.gameEntity_setSkyReflective(modelID, true);
	}
}

void SceneEditor::_updateModelBlinking(const string& modelID, int& multiplier)
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
		if (_fe3d.gameEntity_getLightness(modelID) > _fe3d.gameEntity_getOriginalLightness(modelID) || 
			_fe3d.gameEntity_getLightness(modelID) < 0.0f)
		{
			multiplier *= -1;
		}

		// Set model lightness
		float range = _fe3d.gameEntity_getOriginalLightness(modelID);
		float speed = (_modelBlinkingSpeed * static_cast<float>(multiplier) * range);
		_fe3d.gameEntity_setLightness(modelID, _fe3d.gameEntity_getLightness(modelID) + speed);
	}
}

void SceneEditor::_updateLightbulbAnimation(const string& modelID, int& multiplier)
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

void SceneEditor::_handleValueChanging(const string& screenID, string buttonID, string wfID, float& value, float adder, 
	float multiplier, float minimum, float maximum)
{
	// Plus & minus button handling
	if (_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_LEFT))
	{
		if (_rightWindow->getScreen(screenID)->getButton(buttonID)->isHovered())
		{
			value += adder;
		}
	}

	// Writefield handling
	auto writefield = _rightWindow->getScreen(screenID)->getWriteField(wfID);
	if (writefield->confirmedInput())
	{
		if (writefield->getTextContent() != "")
		{
			// Cannot be empty
			if (writefield->getTextContent() == "?")
			{
				writefield->setTextContent(std::to_string(value));
			}

			value = float(stoi(writefield->getTextContent())) / multiplier;
		}
	}

	// Clamp value range
	value = std::clamp(value, minimum, maximum);

	// Writefield filling
	if (!_rightWindow->getScreen(screenID)->getWriteField(wfID)->isActive())
	{
		_rightWindow->getScreen(screenID)->getWriteField(wfID)->setTextContent(std::to_string(static_cast<int>(value * multiplier)));
	}
}

void SceneEditor::_updateMiscellaneous()
{
	if (_isLoaded)
	{
		// Update bounding box visibility
		if (_fe3d.input_getKeyToggled(Input::KEY_B))
		{
			_fe3d.misc_enableAabbFrameRendering();
		}
		else
		{
			_fe3d.misc_disableAabbFrameRendering();
		}
	}
}