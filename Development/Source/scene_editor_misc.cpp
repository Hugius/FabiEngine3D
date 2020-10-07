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
		_fe3d.textEntity_setTextContent(textEntityID, "Selected model : " + modelName, 0.025f);
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
	_fe3d.textEntity_setTextContent(textEntityID, "Active model: " + modelName, 0.025f);
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
		_fe3d.textEntity_setTextContent(textEntityID, "Selected billboard: " + billboardName, 0.025f);
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
	_fe3d.textEntity_setTextContent(textEntityID, "Active billboard: " + billboardName, 0.025f);
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