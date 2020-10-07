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

	// Change cursor
	_fe3d.guiEntity_changeTexture("@@cursor", "engine\\textures\\cursor_pointing.png");

	// Check if nothing is active
	if (_activeModelID == "" && _activeBillboardID == "" && _activeLightBulbID == "")
	{
		// Removing the unique number from the modelID and updating the text content
		string modelName = modelID.substr(modelID.find('@') + 1);
		string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
		_fe3d.textEntity_show(textEntityID);
		_fe3d.textEntity_setTextContent(textEntityID, "Selected: " + modelName, 0.025f);
	}
}

void SceneEditor::_activateModel(const string& modelID)
{
	_activeModelID = modelID;
	_transformation = TransformationType::TRANSLATION;

	// Activate properties screen
	_rightWindow->getScreen("modelPropertiesMenu")->getButton("translation")->setHoverable(false);
	_rightWindow->getScreen("modelPropertiesMenu")->getButton("rotation")->setHoverable(true);
	_rightWindow->getScreen("modelPropertiesMenu")->getButton("scaling")->setHoverable(true);

	// Filling writefields
	vec3 position = _fe3d.gameEntity_getPosition(_activeModelID);
	_rightWindow->getScreen("modelPropertiesMenu")->getWriteField("x")->setTextContent(to_string(static_cast<int>(position.x)));
	_rightWindow->getScreen("modelPropertiesMenu")->getWriteField("y")->setTextContent(to_string(static_cast<int>(position.y)));
	_rightWindow->getScreen("modelPropertiesMenu")->getWriteField("z")->setTextContent(to_string(static_cast<int>(position.z)));

	// Removing the unique number from the modelID and updating the text content
	string modelName = modelID.substr(modelID.find('@') + 1);
	string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
	_fe3d.textEntity_show(textEntityID);
	_fe3d.textEntity_setTextContent(textEntityID, "Active: " + modelName, 0.025f);
}

void SceneEditor::_selectBillboard(const string& billboardID)
{
	_selectedBillboardID = billboardID;

	// Change cursor
	_fe3d.guiEntity_changeTexture("@@cursor", "engine\\textures\\cursor_pointing.png");

	// Check if nothing is active
	if (_activeBillboardID == "" && _activeModelID == "" && _activeLightBulbID == "")
	{
		// Removing the unique number from the billboardID and updating the text content
		string billboardName = billboardID.substr(billboardID.find('@') + 1);
		string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID();
		_fe3d.textEntity_show(textEntityID);
		_fe3d.textEntity_setTextContent(textEntityID, "Selected: " + billboardName, 0.025f);
	}
}

void SceneEditor::_activateBillboard(const string& billboardID)
{
	_activeBillboardID = billboardID;
	_transformation = TransformationType::TRANSLATION;

	// Activate properties screen
	_rightWindow->getScreen("billboardPropertiesMenu")->getButton("translation")->setHoverable(false);
	_rightWindow->getScreen("billboardPropertiesMenu")->getButton("rotation")->setHoverable(true);
	_rightWindow->getScreen("billboardPropertiesMenu")->getButton("scaling")->setHoverable(true);

	// Filling writefields
	vec3 position = _fe3d.billboardEntity_getPosition(_activeBillboardID);
	_rightWindow->getScreen("billboardPropertiesMenu")->getWriteField("x")->setTextContent(to_string(static_cast<int>(position.x)));
	_rightWindow->getScreen("billboardPropertiesMenu")->getWriteField("y")->setTextContent(to_string(static_cast<int>(position.y)));
	_rightWindow->getScreen("billboardPropertiesMenu")->getWriteField("z")->setTextContent(to_string(static_cast<int>(position.z)));

	// Removing the unique number from the billboardID and updating the text content
	string billboardName = billboardID.substr(billboardID.find('@') + 1);
	string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID();
	_fe3d.textEntity_show(textEntityID);
	_fe3d.textEntity_setTextContent(textEntityID, "Active: " + billboardName, 0.025f);
}

void SceneEditor::_placeModel(const string& newID, const string& previewID, vec3 position)
{
	// Check if instanced entity
	if (_fe3d.gameEntity_isInstanced(previewID))
	{
		const string instancedID = previewID.substr(1) + "_instanced";

		if (_fe3d.gameEntity_isExisting(instancedID)) // Add to offsets
		{
			auto offsets = _fe3d.gameEntity_getInstancedOffsets(instancedID);
			offsets.push_back(position);
			_fe3d.gameEntity_setInstanced(instancedID, true, offsets);
		}
		else
		{
			// Create new GAME entity
			_fe3d.gameEntity_add(instancedID, _fe3d.gameEntity_getObjPath(previewID), vec3(0.0f), vec3(0.0f), _fe3d.gameEntity_getSize(previewID));
			
			// Fill GAME entity
			_fe3d.gameEntity_setFaceCulled(instancedID, _fe3d.gameEntity_isFaceCulled(previewID));
			_fe3d.gameEntity_setShadowed(instancedID, _fe3d.gameEntity_isShadowed(previewID));
			_fe3d.gameEntity_setTransparent(instancedID, _fe3d.gameEntity_isTransparent(previewID));
			_fe3d.gameEntity_setSceneReflective(instancedID, _fe3d.gameEntity_isSceneReflective(previewID));
			_fe3d.gameEntity_setSpecularLighted(instancedID, _fe3d.gameEntity_isSpecularLighted(previewID));
			_fe3d.gameEntity_setSpecularFactor(instancedID, _fe3d.gameEntity_getSpecularFactor(previewID));
			_fe3d.gameEntity_setSpecularIntensity(instancedID, _fe3d.gameEntity_getSpecularIntensity(previewID));
			_fe3d.gameEntity_setLightness(instancedID, _fe3d.gameEntity_getLightness(previewID));
			_fe3d.gameEntity_setOriginalLightness(instancedID, _fe3d.gameEntity_getOriginalLightness(previewID));
			_fe3d.gameEntity_setColor(instancedID, _fe3d.gameEntity_getColor(previewID));
			_fe3d.gameEntity_setUvRepeat(instancedID, _fe3d.gameEntity_getUvRepeat(previewID));
			_fe3d.gameEntity_setInstanced(instancedID, true, { position });

			// Diffuse map
			if (_fe3d.gameEntity_getDiffuseMapPath(previewID) != "")
			{
				_fe3d.gameEntity_setDiffuseMap(instancedID, _fe3d.gameEntity_getDiffuseMapPath(previewID));
			}

			// Light map
			if (_fe3d.gameEntity_getLightMapPath(previewID) != "")
			{
				_fe3d.gameEntity_setLightMap(instancedID, _fe3d.gameEntity_getLightMapPath(previewID));
				_fe3d.gameEntity_setLightMapped(instancedID, true);
			}

			// Reflection map
			if (_fe3d.gameEntity_getReflectionMapPath(previewID) != "")
			{
				_fe3d.gameEntity_setReflectionMap(instancedID, _fe3d.gameEntity_getReflectionMapPath(previewID));
				_fe3d.gameEntity_setSkyReflective(instancedID, true);
			}

			// Normal map
			if (_fe3d.gameEntity_getNormalMapPath(previewID) != "")
			{
				_fe3d.gameEntity_setNormalMap(instancedID, _fe3d.gameEntity_getNormalMapPath(previewID));
				_fe3d.gameEntity_setNormalMapped(instancedID, true);
			}
		}
	}
	else // Normal entity
	{
		// Add GAME entity
		_fe3d.gameEntity_add(newID, _fe3d.gameEntity_getObjPath(previewID), position, vec3(0.0f), _fe3d.gameEntity_getSize(previewID));

		// Bind AABB entities to GAME entity
		for (auto& previewAabbID : _fe3d.aabbEntity_getBoundIDs(previewID, true, false))
		{
			string newAabbID = newID + "_" + previewAabbID.substr(string(previewID + "_").size());
			_fe3d.aabbEntity_bindToGameEntity(newID, _fe3d.aabbEntity_getPosition(previewAabbID), _fe3d.aabbEntity_getSize(previewAabbID), true, newAabbID);
		}

		// Model properties
		_fe3d.gameEntity_setStaticToCamera(newID, _fe3d.gameEntity_isStaticToCamera(previewID));
		_fe3d.gameEntity_setFaceCulled(newID, _fe3d.gameEntity_isFaceCulled(previewID));
		_fe3d.gameEntity_setShadowed(newID, _fe3d.gameEntity_isShadowed(previewID));
		_fe3d.gameEntity_setTransparent(newID, _fe3d.gameEntity_isTransparent(previewID));
		_fe3d.gameEntity_setSceneReflective(newID, _fe3d.gameEntity_isSceneReflective(previewID));
		_fe3d.gameEntity_setSpecularLighted(newID, _fe3d.gameEntity_isSpecularLighted(previewID));
		_fe3d.gameEntity_setSpecularFactor(newID, _fe3d.gameEntity_getSpecularFactor(previewID));
		_fe3d.gameEntity_setSpecularIntensity(newID, _fe3d.gameEntity_getSpecularIntensity(previewID));
		_fe3d.gameEntity_setLightness(newID, _fe3d.gameEntity_getLightness(previewID));
		_fe3d.gameEntity_setOriginalLightness(newID, _fe3d.gameEntity_getOriginalLightness(previewID));
		_fe3d.gameEntity_setColor(newID, _fe3d.gameEntity_getColor(previewID));
		_fe3d.gameEntity_setUvRepeat(newID, _fe3d.gameEntity_getUvRepeat(previewID));
		_fe3d.gameEntity_setLevelOfDetailEntity(newID, _fe3d.gameEntity_getLevelOfDetailEntityID(previewID));

		// Diffuse map
		if (_fe3d.gameEntity_getDiffuseMapPath(previewID) != "")
		{
			_fe3d.gameEntity_setDiffuseMap(newID, _fe3d.gameEntity_getDiffuseMapPath(previewID));
		}

		// Light map
		if (_fe3d.gameEntity_getLightMapPath(previewID) != "")
		{
			_fe3d.gameEntity_setLightMap(newID, _fe3d.gameEntity_getLightMapPath(previewID));
			_fe3d.gameEntity_setLightMapped(newID, true);
		}

		// Reflection map
		if (_fe3d.gameEntity_getReflectionMapPath(previewID) != "")
		{
			_fe3d.gameEntity_setReflectionMap(newID, _fe3d.gameEntity_getReflectionMapPath(previewID));
			_fe3d.gameEntity_setSkyReflective(newID, true);
		}

		// Normal map
		if (_fe3d.gameEntity_getNormalMapPath(previewID) != "")
		{
			_fe3d.gameEntity_setNormalMap(newID, _fe3d.gameEntity_getNormalMapPath(previewID));
			_fe3d.gameEntity_setNormalMapped(newID, true);
		}
	}
}

void SceneEditor::_placeModel(const string& newID, vec3 position, vec3 rotation, vec3 size, const string& objPath, const string& diffuseMapPath,
	const string& lightMapPath, const string& reflectionMapPath, const string& normalMapPath, bool isFrozen, bool isFaceCulled,
	bool isShadowed, bool isTransparent, bool isReflective, bool isSpecular, float specularFactor, 
	float specularIntensity, float lightness, vec3 color, float uvRepeat, const string& lodEntityID, bool isInstanced,
	vector<vec3> instancedOffsets, vector<string> aabbNames, vector<vec3> aabbPositions, vector<vec3> aabbSizes)
{
	// Add GAME entity
	_fe3d.gameEntity_add(newID, objPath, position, rotation, size);
	
	// Add AABBs
	for (unsigned int i = 0; i < aabbNames.size(); i++)
	{
		_fe3d.aabbEntity_bindToGameEntity(newID, aabbPositions[i], aabbSizes[i], true, newID + "_" + aabbNames[i]);
	}

	// Model properties
	_fe3d.gameEntity_setStaticToCamera(newID, isFrozen);
	_fe3d.gameEntity_setFaceCulled(newID, isFaceCulled);
	_fe3d.gameEntity_setShadowed(newID, isShadowed);
	_fe3d.gameEntity_setTransparent(newID, isTransparent);
	_fe3d.gameEntity_setSceneReflective(newID, isReflective);
	_fe3d.gameEntity_setSpecularLighted(newID, isSpecular);
	_fe3d.gameEntity_setSpecularFactor(newID, specularFactor);
	_fe3d.gameEntity_setSpecularIntensity(newID, specularIntensity);
	_fe3d.gameEntity_setOriginalLightness(newID, lightness);
	_fe3d.gameEntity_setLightness(newID, lightness);
	_fe3d.gameEntity_setColor(newID, color);
	_fe3d.gameEntity_setUvRepeat(newID, uvRepeat);
	_fe3d.gameEntity_setLevelOfDetailEntity(newID, lodEntityID);
	_fe3d.gameEntity_setInstanced(newID, isInstanced, instancedOffsets);

	// Diffuse map
	if (diffuseMapPath != "")
	{
		_fe3d.gameEntity_setDiffuseMap(newID, diffuseMapPath);
	}

	// Light map
	if (lightMapPath != "")
	{
		_fe3d.gameEntity_setLightMap(newID, lightMapPath);
		_fe3d.gameEntity_setLightMapped(newID, true);
	}

	// Reflection map
	if (reflectionMapPath != "")
	{
		_fe3d.gameEntity_setReflectionMap(newID, reflectionMapPath);
		_fe3d.gameEntity_setSkyReflective(newID, true);
	}

	// Normal map
	if (normalMapPath != "")
	{
		_fe3d.gameEntity_setNormalMap(newID, normalMapPath);
		_fe3d.gameEntity_setNormalMapped(newID, true);
	}
}

void SceneEditor::_placeBillboard(const string& newID, const string& previewID, vec3 position)
{
	auto color = _fe3d.billboardEntity_getColor(previewID);
	auto isFacingX = _fe3d.billboardEntity_isFacingCameraX(previewID);
	auto isFacingY = _fe3d.billboardEntity_isFacingCameraY(previewID);

	// Add BILLBOARD entity
	_fe3d.billBoardEntity_add(newID, color, position, vec3(0.0f), _fe3d.billboardEntity_getSize(previewID), isFacingX, isFacingY);

	// Determine BILLBOARD entity type
	if(_fe3d.billboardEntity_getDiffuseMapPath(previewID) != "")
	{
		_fe3d.billboardEntity_setDiffuseMap(newID, _fe3d.billboardEntity_getDiffuseMapPath(previewID), true);
	}
	else if (_fe3d.billboardEntity_getFontPath(previewID) != "") // Text billboard
	{
		_fe3d.billBoardEntity_setFont(newID, _fe3d.billboardEntity_getFontPath(previewID));
		_fe3d.billBoardEntity_setTextContent(newID, _fe3d.billboardEntity_getTextContent(previewID));
	}

	// Animation
	if (_fe3d.billboardEntity_isAnimationPlaying(previewID))
	{
		_fe3d.billboardEntity_setAnimationRows(newID, _fe3d.billboardEntity_getAnimationRows(previewID));
		_fe3d.billboardEntity_setAnimationColumns(newID, _fe3d.billboardEntity_getAnimationColumns(previewID));
		_fe3d.billboardEntity_setAnimationFramestep(newID, _fe3d.billboardEntity_getAnimationFramestep(previewID));
		_fe3d.billBoardEntity_playSpriteAnimation(newID, -1);
	}

	// Bind AABB entity to BILLBOARD entity
	auto billboardSize = _fe3d.billboardEntity_getSize(previewID);
	_fe3d.aabbEntity_bindToBillboardEntity(previewID, vec3(billboardSize.x, billboardSize.y, 1.0f), true, newID);

	// Miscellaneous
	_fe3d.billboardEntity_setUvRepeat(newID, _fe3d.billboardEntity_getUvRepeat(previewID));
	_fe3d.billboardEntity_setTransparent(newID, _fe3d.billboardEntity_isTransparent(previewID));
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

void SceneEditor::_updateBillboardBlinking(const string& billboardID, int& multiplier)
{
	// Reset multiplier if nothing active / selected
	if (billboardID == "")
	{
		multiplier = 1;
	}

	// Update billboard lightness
	if (billboardID != "")
	{
		// Check if lightness reached bounds
		if (_fe3d.billboardEntity_getLightness(billboardID) > _fe3d.billboardEntity_getOriginalLightness(billboardID) ||
			_fe3d.billboardEntity_getLightness(billboardID) < 0.0f)
		{
			multiplier *= -1;
		}

		// Set billboard lightness
		float range = _fe3d.billboardEntity_getOriginalLightness(billboardID);
		float speed = (_billboardBlinkingSpeed * static_cast<float>(multiplier) * range);
		_fe3d.billboardEntity_setLightness(billboardID, _fe3d.billboardEntity_getLightness(billboardID) + speed);
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
	if (_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_LEFT))
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
				writefield->setTextContent(to_string(value));
			}

			value = float(stoi(writefield->getTextContent())) / multiplier;
		}
	}

	// Clamp value range
	value = std::clamp(value, minimum, maximum);

	// Writefield filling
	if (!_rightWindow->getScreen(screenID)->getWriteField(wfID)->isActive())
	{
		_rightWindow->getScreen(screenID)->getWriteField(wfID)->setTextContent(to_string(static_cast<int>(value * multiplier)));
	}
}

void SceneEditor::_updateMiscellaneous()
{
	if (_isLoaded)
	{
		// Update bounding box visibility
		if (_fe3d.input_getKeyToggled(InputType::KEY_B))
		{
			_fe3d.misc_enableAabbFrameRendering();
		}
		else
		{
			_fe3d.misc_disableAabbFrameRendering();
		}
	}
}