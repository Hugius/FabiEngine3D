#include "scene_editor.hpp"

#include <algorithm>
#include <filesystem>

bool SceneEditor::isLoaded()
{
	return _isEditorLoaded;
}

bool SceneEditor::isSceneExisting(const string& fileName)
{
	// Error checking
	if (_currentProjectID == "")
	{
		_fe3d.logger_throwError("No current project loaded --> SceneEditor::isSceneExisting()");
	}

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
		("projects\\" + _currentProjectID)) + "\\scenes\\editor\\" + fileName + ".fe3d";

	// Check if scene file exists
	return (_fe3d.misc_isFileExisting(filePath));
}

const string& SceneEditor::getLoadedSceneID()
{
	return _loadedSceneID;
}

void SceneEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

void SceneEditor::_selectModel(const string& modelID)
{
	_selectedModelID = modelID;

	// Change cursor
	_fe3d.imageEntity_changeTexture("@@cursor", "engine_assets\\textures\\cursor_pointing.png");

	// Check if nothing is active
	if (_activeModelID == "" && _activeBillboardID == "" && _activeLightBulbID == "" && _activeSpeakerID == "")
	{
		// Removing the unique number from the modelID and updating the text content
		string tempID = modelID;
		std::reverse(tempID.begin(), tempID.end());
		string modelName = tempID.substr(tempID.find('_') + 1);
		std::reverse(modelName.begin(), modelName.end());
		string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
		_fe3d.textEntity_setVisible(textEntityID, true);
		_fe3d.textEntity_setTextContent(textEntityID, "Selected model: " + modelName, 0.025f);
	}
}

void SceneEditor::_activateModel(const string& modelID)
{
	_activeModelID = modelID;
	_transformation = TransformationType::TRANSLATION;

	// Activate properties screen
	_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("translation")->setHoverable(false);
	_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("rotation")->setHoverable(true);
	_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("scaling")->setHoverable(true);

	// Filling writefields
	Vec3 position = _fe3d.modelEntity_getPosition(_activeModelID);
	_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getWritefield("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getWritefield("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getWritefield("z")->changeTextContent(to_string(static_cast<int>(position.z)));

	// Removing the unique number from the modelID and updating the text content
	string tempID = modelID;
	std::reverse(tempID.begin(), tempID.end());
	string modelName = tempID.substr(tempID.find('_') + 1);
	std::reverse(modelName.begin(), modelName.end());
	string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
	_fe3d.textEntity_setVisible(textEntityID, true);
	_fe3d.textEntity_setTextContent(textEntityID, "Active model: " + modelName, 0.025f);
}

void SceneEditor::_selectBillboard(const string& billboardID)
{
	_selectedBillboardID = billboardID;

	// Change cursor
	_fe3d.imageEntity_changeTexture("@@cursor", "engine_assets\\textures\\cursor_pointing.png");

	// Check if nothing is active
	if (_activeBillboardID == "" && _activeModelID == "" && _activeLightBulbID == "" && _activeSpeakerID == "")
	{
		// Removing the unique number from the billboardID and updating the text content
		string tempID = billboardID;
		std::reverse(tempID.begin(), tempID.end());
		string billboardName = tempID.substr(tempID.find('_') + 1);
		std::reverse(billboardName.begin(), billboardName.end());
		string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID();
		_fe3d.textEntity_setVisible(textEntityID, true);
		_fe3d.textEntity_setTextContent(textEntityID, "Selected billboard: " + billboardName, 0.025f);
	}
}

void SceneEditor::_activateBillboard(const string& billboardID)
{
	_activeBillboardID = billboardID;
	_transformation = TransformationType::TRANSLATION;

	// Activate properties screen
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("translation")->setHoverable(false);
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("rotation")->setHoverable(true);
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("scaling")->setHoverable(true);

	// Filling writefields
	Vec3 position = _fe3d.billboardEntity_getPosition(_activeBillboardID);
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWritefield("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWritefield("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWritefield("z")->changeTextContent(to_string(static_cast<int>(position.z)));

	// Removing the unique number from the billboardID and updating the text content
	string tempID = billboardID;
	std::reverse(tempID.begin(), tempID.end());
	string billboardName = tempID.substr(tempID.find('_') + 1);
	std::reverse(billboardName.begin(), billboardName.end());
	string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID();
	_fe3d.textEntity_setVisible(textEntityID, true);
	_fe3d.textEntity_setTextContent(textEntityID, "Active billboard: " + billboardName, 0.025f);
}

void SceneEditor::_selectSound(const string& soundID)
{
	_selectedSpeakerID = "@speaker_" + soundID;

	// Change cursor
	_fe3d.imageEntity_changeTexture("@@cursor", "engine_assets\\textures\\cursor_pointing.png");

	// Check if nothing is active
	if (_activeBillboardID == "" && _activeModelID == "" && _activeLightBulbID == "" && _activeSpeakerID == "")
	{
		// Removing the unique number from the soundID and updating the text content
		string tempID = soundID;
		std::reverse(tempID.begin(), tempID.end());
		string soundName = tempID.substr(tempID.find('_') + 1);
		std::reverse(soundName.begin(), soundName.end());
		string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedSoundName")->getEntityID();
		_fe3d.textEntity_setVisible(textEntityID, true);
		_fe3d.textEntity_setTextContent(textEntityID, "Selected sound: " + soundName, 0.025f);
	}
}

void SceneEditor::_activateSound(const string& soundID)
{
	_activeSpeakerID = "@speaker_" + soundID;
	_transformation = TransformationType::TRANSLATION;

	// Filling writefields
	Vec3 position = _fe3d.soundEntity_getPosition(_activeSpeakerID.substr(string("@speaker_").size()));
	float maxVolume = _fe3d.soundEntity_getMaxVolume(_activeSpeakerID.substr(string("@speaker_").size()));
	float maxDistance = _fe3d.soundEntity_getMaxDistance(_activeSpeakerID.substr(string("@speaker_").size()));
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWritefield("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWritefield("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWritefield("z")->changeTextContent(to_string(static_cast<int>(position.z)));
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWritefield("volume")->changeTextContent(to_string(static_cast<int>(maxVolume * 100.0f)));
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWritefield("distance")->changeTextContent(to_string(static_cast<int>(maxDistance)));

	// Removing the unique number from the soundID and updating the text content
	string tempID = soundID;
	std::reverse(tempID.begin(), tempID.end());
	string soundName = tempID.substr(tempID.find('_') + 1);
	std::reverse(soundName.begin(), soundName.end());
	string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedSoundName")->getEntityID();
	_fe3d.textEntity_setVisible(textEntityID, true);
	_fe3d.textEntity_setTextContent(textEntityID, "Active sound: " + soundName, 0.025f);
}

vector<string> SceneEditor::_loadSceneIDs()
{
	// Temporary values
	vector<string> sceneIDs;
	string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
		("projects\\" + _currentProjectID)) + "\\scenes\\editor\\");

	// Check if scenes directory exists
	if (_fe3d.misc_isDirectoryExisting(directoryPath))
	{
		// Get all project IDs
		for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
		{
			string sceneID = string(entry.path().u8string());
			sceneID.erase(0, directoryPath.size());
			sceneIDs.push_back(sceneID.substr(0, sceneID.size() - 5));
		}
	}
	else
	{
		_fe3d.logger_throwError("Project \"" + _currentProjectID + "\" corrupted: \"scenes\\editor\\\" folder missing!");
	}

	return sceneIDs;
}

void SceneEditor::_deleteSceneFile(const string& sceneID)
{
	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
		("projects\\" + _currentProjectID)) + "\\scenes\\editor\\" + sceneID + ".fe3d";

	// Check if scene file is still existing
	if (_fe3d.misc_isFileExisting(filePath))
	{
		std::filesystem::remove_all(filePath);
	}
	else
	{
		_fe3d.logger_throwError("Project \"" + _currentProjectID + "\" corrupted: \"scenes\\editor\\" + sceneID + ".fe3d\" missing!");
	}
}

void SceneEditor::_handleValueChanging(const string& screenID, string buttonID, string writefieldID, float& value, float adder, 
	float multiplier, float minimum, float maximum)
{
	// Temporary values
	auto writefield = _gui.getViewport("right")->getWindow("main")->getScreen(screenID)->getWritefield(writefieldID);

	// Plus & minus button handling
	if (_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_LEFT))
	{
		if (_gui.getViewport("right")->getWindow("main")->getScreen(screenID)->getButton(buttonID)->isHovered())
		{
			value += adder;
		}
	}

	// Writefield pre-update
	if (!writefield->isActive())
	{
		writefield->changeTextContent(to_string(static_cast<int>(value * multiplier)));
	}

	// Writefield handling
	if (writefield->getTextContent().empty())
	{
		value = 0.0f; // Reset value to default
	}
	else
	{
		// Check if something is filled in
		if (writefield->isActive())
		{
			value = (static_cast<float>(stoi(writefield->getTextContent())) / multiplier); // Update value in realtime
		}
	}

	// Clamp value range
	value = std::clamp(value, minimum, maximum);

	// Writefield post-update
	if (!writefield->isActive())
	{
		writefield->changeTextContent(to_string(static_cast<int>(value * multiplier)));
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
		if ((_fe3d.modelEntity_getLightness(modelID) > _initialModelLightness[modelID]) ||
			_fe3d.modelEntity_getLightness(modelID) <= 0.0f)
		{
			multiplier *= -1;
		}

		// Set model lightness
		float range = _initialModelLightness[modelID];
		float speed = (MODEL_BLINKING_SPEED * static_cast<float>(multiplier) * range);
		_fe3d.modelEntity_setLightness(modelID, _fe3d.modelEntity_getLightness(modelID) + speed);
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
		if (_fe3d.billboardEntity_getLightness(billboardID) > _initialBillboardLightness[billboardID] ||
			_fe3d.billboardEntity_getLightness(billboardID) <= 0.0f)
		{
			multiplier *= -1;
		}

		// Set billboard lightness
		float range = _initialBillboardLightness[billboardID];
		float speed = (BILLBOARD_BLINKING_SPEED * static_cast<float>(multiplier) * range);
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
		if (_fe3d.modelEntity_getSize(modelID).x > DEFAULT_LIGHTBULB_SIZE.x * 1.5f ||
			_fe3d.modelEntity_getSize(modelID).x < DEFAULT_LIGHTBULB_SIZE.x)
		{
			multiplier *= -1;
		}

		// Set model size
		float speed = (LIGHTBULB_ANIMATION_SPEED * static_cast<float>(multiplier));
		_fe3d.modelEntity_setSize(modelID, _fe3d.modelEntity_getSize(modelID) + Vec3(speed));
		_fe3d.aabbEntity_setSize(modelID, _fe3d.aabbEntity_getSize(modelID) + Vec3(speed));
	}
}

void SceneEditor::_updateSpeakerAnimation(const string& modelID, int& multiplier)
{
	// Reset multiplier if nothing active / selected
	if (modelID == "")
	{
		multiplier = 1;
	}

	// Update speaker animation
	if (modelID != "")
	{
		// Check if model size reached bounds
		if (_fe3d.modelEntity_getSize(modelID).x > DEFAULT_SPEAKER_SIZE.x * 1.5f ||
			_fe3d.modelEntity_getSize(modelID).x < DEFAULT_SPEAKER_SIZE.x)
		{
			multiplier *= -1;
		}

		// Set model size
		float speed = (SPEAKER_ANIMATION_SPEED * static_cast<float>(multiplier));
		_fe3d.modelEntity_setSize(modelID, _fe3d.modelEntity_getSize(modelID) + Vec3(speed));
		_fe3d.aabbEntity_setSize(modelID, _fe3d.aabbEntity_getSize(modelID) + Vec3(speed));
	}
}