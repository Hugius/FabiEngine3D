#include "scene_editor.hpp"
#include "logger.hpp"

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
		Logger::throwError("SceneEditor::isSceneExisting() ---> no current project loaded!");
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
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: \"scenes\\editor\\\" folder missing!");
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
		Logger::throwWarning("Cannot delete scene with ID \"" + sceneID + "\"!");
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
	// Reset multiplier if nothing active/selected
	if (modelID == "")
	{
		multiplier = 1;
	}

	// Update model inversion
	if (modelID != "")
	{
		// Check if inversion reached minimum
		if (_fe3d.modelEntity_getInversion(modelID) == 0.0f)
		{
			multiplier *= -1;
		}

		// Check if inversion reached maximum
		if (_fe3d.modelEntity_getInversion(modelID) == 1.0f)
		{
			multiplier *= -1;
		}

		// Set model inversion
		float speed = (MODEL_BLINKING_SPEED * static_cast<float>(multiplier));
		_fe3d.modelEntity_setInversion(modelID, _fe3d.modelEntity_getInversion(modelID) + speed);
	}
}

void SceneEditor::_updateBillboardBlinking(const string& billboardID, int& multiplier)
{
	// Reset multiplier if nothing active/selected
	if (billboardID == "")
	{
		multiplier = 1;
	}

	// Update billboard inversion
	if (billboardID != "")
	{
		// Check if inversion reached minimum
		if (_fe3d.billboardEntity_getInversion(billboardID) == 0.0f)
		{
			multiplier *= -1;
		}

		// Check if inversion reached maximum
		if (_fe3d.billboardEntity_getInversion(billboardID) == 1.0f)
		{
			multiplier *= -1;
		}

		// Set billboard inversion
		float speed = (BILLBOARD_BLINKING_SPEED * static_cast<float>(multiplier));
		_fe3d.billboardEntity_setInversion(billboardID, _fe3d.billboardEntity_getInversion(billboardID) + speed);
	}
}

void SceneEditor::_updateSpeakerAnimation(const string& modelID, int& multiplier)
{
	// Reset multiplier if nothing active/selected
	if (modelID == "")
	{
		multiplier = 1;
	}

	// Update speaker animation
	if (modelID != "")
	{
		// Check if inversion reached minimum
		if (_fe3d.modelEntity_getSize(modelID).x < DEFAULT_SPEAKER_SIZE.x)
		{
			_fe3d.modelEntity_setSize(modelID, DEFAULT_SPEAKER_SIZE);
			_fe3d.aabbEntity_setSize(modelID, DEFAULT_SPEAKER_AABB_SIZE);
			multiplier *= -1;
		}

		// Check if inversion reached maximum
		if (_fe3d.modelEntity_getSize(modelID).x > (DEFAULT_SPEAKER_SIZE.x * SPEAKER_SIZE_INCREASE))
		{
			_fe3d.modelEntity_setSize(modelID, (DEFAULT_SPEAKER_SIZE.x * SPEAKER_SIZE_INCREASE));
			_fe3d.aabbEntity_setSize(modelID, (DEFAULT_SPEAKER_AABB_SIZE.x * SPEAKER_SIZE_INCREASE));
			multiplier *= -1;
		}

		// Set new sizes
		float speed = (SPEAKER_ANIMATION_SPEED * static_cast<float>(multiplier) * (DEFAULT_SPEAKER_SIZE.x * 0.25f));
		_fe3d.modelEntity_setSize(modelID, _fe3d.modelEntity_getSize(modelID) + Vec3(speed));
		_fe3d.aabbEntity_setSize(modelID, _fe3d.aabbEntity_getSize(modelID) + Vec3(speed));
	}
}

void SceneEditor::_updateLightBulbAnimation(const string& modelID, int& multiplier)
{
	// Reset multiplier if nothing active/selected
	if (modelID == "")
	{
		multiplier = 1;
	}

	// Update light bulb animation
	if (modelID != "")
	{
		// Check if inversion reached minimum
		if (_fe3d.modelEntity_getSize(modelID).x < DEFAULT_LIGHT_BULB_SIZE.x)
		{
			_fe3d.modelEntity_setSize(modelID, DEFAULT_LIGHT_BULB_SIZE);
			_fe3d.aabbEntity_setSize(modelID, DEFAULT_LIGHT_BULB_AABB_SIZE);
			multiplier *= -1;
		}

		// Check if inversion reached maximum
		if (_fe3d.modelEntity_getSize(modelID).x > (DEFAULT_LIGHT_BULB_SIZE.x * LIGHT_BULB_SIZE_INCREASE))
		{
			_fe3d.modelEntity_setSize(modelID, (DEFAULT_LIGHT_BULB_SIZE.x * LIGHT_BULB_SIZE_INCREASE));
			_fe3d.aabbEntity_setSize(modelID, (DEFAULT_LIGHT_BULB_AABB_SIZE.x * LIGHT_BULB_SIZE_INCREASE));
			multiplier *= -1;
		}

		// Set new sizes
		float speed = (LIGHT_BULB_ANIMATION_SPEED * static_cast<float>(multiplier) * (DEFAULT_LIGHT_BULB_SIZE.x * 0.25f));
		_fe3d.modelEntity_setSize(modelID, _fe3d.modelEntity_getSize(modelID) + Vec3(speed));
		_fe3d.aabbEntity_setSize(modelID, _fe3d.aabbEntity_getSize(modelID) + Vec3(speed));
	}
}