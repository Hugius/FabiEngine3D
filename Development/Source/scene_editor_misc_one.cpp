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
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : 
		("projects\\" + _currentProjectID)) + "\\scenes\\editor\\" + fileName + ".fe3d";

	// Check if scene file exists
	return (_fe3d.misc_isFileExisting(filePath));
}

const string& SceneEditor::getLoadedSceneID()
{
	return _loadedSceneID;
}

void SceneEditor::setCurrentProjectID(const string& projectName)
{
	_currentProjectID = projectName;
}

void SceneEditor::_selectModel(const string& modelID)
{
	_selectedModelID = modelID;

	// Change cursor
	_fe3d.guiEntity_changeTexture("@@cursor", "engine_assets\\textures\\cursor_pointing.png");

	// Check if nothing is active
	if (_activeModelID == "" && _activeBillboardID == "" && _activeLightBulbID == "" && _activeSpeakerID == "")
	{
		// Removing the unique number from the modelID and updating the text content
		string tempID = modelID;
		std::reverse(tempID.begin(), tempID.end());
		string modelName = tempID.substr(tempID.find('_') + 1);
		std::reverse(modelName.begin(), modelName.end());
		string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
		_fe3d.textEntity_show(textEntityID);
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
	_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getWritefield("x")->setTextContent(to_string(static_cast<int>(position.x)));
	_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getWritefield("y")->setTextContent(to_string(static_cast<int>(position.y)));
	_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getWritefield("z")->setTextContent(to_string(static_cast<int>(position.z)));

	// Removing the unique number from the modelID and updating the text content
	string tempID = modelID;
	std::reverse(tempID.begin(), tempID.end());
	string modelName = tempID.substr(tempID.find('_') + 1);
	std::reverse(modelName.begin(), modelName.end());
	string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
	_fe3d.textEntity_show(textEntityID);
	_fe3d.textEntity_setTextContent(textEntityID, "Active model: " + modelName, 0.025f);
}

void SceneEditor::_selectBillboard(const string& billboardID)
{
	_selectedBillboardID = billboardID;

	// Change cursor
	_fe3d.guiEntity_changeTexture("@@cursor", "engine_assets\\textures\\cursor_pointing.png");

	// Check if nothing is active
	if (_activeBillboardID == "" && _activeModelID == "" && _activeLightBulbID == "" && _activeSpeakerID == "")
	{
		// Removing the unique number from the billboardID and updating the text content
		string tempID = billboardID;
		std::reverse(tempID.begin(), tempID.end());
		string billboardName = tempID.substr(tempID.find('_') + 1);
		std::reverse(billboardName.begin(), billboardName.end());
		string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID();
		_fe3d.textEntity_show(textEntityID);
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
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWritefield("x")->setTextContent(to_string(static_cast<int>(position.x)));
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWritefield("y")->setTextContent(to_string(static_cast<int>(position.y)));
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWritefield("z")->setTextContent(to_string(static_cast<int>(position.z)));

	// Removing the unique number from the billboardID and updating the text content
	string tempID = billboardID;
	std::reverse(tempID.begin(), tempID.end());
	string billboardName = tempID.substr(tempID.find('_') + 1);
	std::reverse(billboardName.begin(), billboardName.end());
	string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID();
	_fe3d.textEntity_show(textEntityID);
	_fe3d.textEntity_setTextContent(textEntityID, "Active billboard: " + billboardName, 0.025f);
}

void SceneEditor::_selectAudio(const string& audioID)
{
	_selectedSpeakerID = "@speaker_" + audioID;

	// Change cursor
	_fe3d.guiEntity_changeTexture("@@cursor", "engine_assets\\textures\\cursor_pointing.png");

	// Check if nothing is active
	if (_activeBillboardID == "" && _activeModelID == "" && _activeLightBulbID == "" && _activeSpeakerID == "")
	{
		// Removing the unique number from the audioID and updating the text content
		string tempID = audioID;
		std::reverse(tempID.begin(), tempID.end());
		string audioName = tempID.substr(tempID.find('_') + 1);
		std::reverse(audioName.begin(), audioName.end());
		string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedAudioName")->getEntityID();
		_fe3d.textEntity_show(textEntityID);
		_fe3d.textEntity_setTextContent(textEntityID, "Selected audio: " + audioName, 0.025f);
	}
}

void SceneEditor::_activateAudio(const string& audioID)
{
	_activeSpeakerID = "@speaker_" + audioID;
	_transformation = TransformationType::TRANSLATION;

	// Filling writefields
	Vec3 position = _fe3d.soundEntity_getPosition(_activeSpeakerID.substr(string("@speaker_").size()));
	float maxVolume = _fe3d.soundEntity_getMaxVolume(_activeSpeakerID.substr(string("@speaker_").size()));
	float maxDistance = _fe3d.soundEntity_getMaxDistance(_activeSpeakerID.substr(string("@speaker_").size()));
	_gui.getViewport("right")->getWindow("main")->getScreen("audioPropertiesMenu")->getWritefield("x")->setTextContent(to_string(static_cast<int>(position.x)));
	_gui.getViewport("right")->getWindow("main")->getScreen("audioPropertiesMenu")->getWritefield("y")->setTextContent(to_string(static_cast<int>(position.y)));
	_gui.getViewport("right")->getWindow("main")->getScreen("audioPropertiesMenu")->getWritefield("z")->setTextContent(to_string(static_cast<int>(position.z)));
	_gui.getViewport("right")->getWindow("main")->getScreen("audioPropertiesMenu")->getWritefield("volume")->setTextContent(to_string(static_cast<int>(maxVolume * 100.0f)));
	_gui.getViewport("right")->getWindow("main")->getScreen("audioPropertiesMenu")->getWritefield("distance")->setTextContent(to_string(static_cast<int>(maxDistance)));

	// Removing the unique number from the audioID and updating the text content
	string tempID = audioID;
	std::reverse(tempID.begin(), tempID.end());
	string audioName = tempID.substr(tempID.find('_') + 1);
	std::reverse(audioName.begin(), audioName.end());
	string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedAudioName")->getEntityID();
	_fe3d.textEntity_show(textEntityID);
	_fe3d.textEntity_setTextContent(textEntityID, "Active audio: " + audioName, 0.025f);
}

vector<string> SceneEditor::_loadSceneNames()
{
	// Temporary values
	vector<string> sceneNames;
	string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : 
		("projects\\" + _currentProjectID)) + "\\scenes\\editor\\");

	// Check if scenes directory exists
	if (_fe3d.misc_isDirectoryExisting(directoryPath))
	{
		// Get all project names
		for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
		{
			string sceneName = string(entry.path().u8string());
			sceneName.erase(0, directoryPath.size());
			sceneNames.push_back(sceneName.substr(0, sceneName.size() - 5));
		}
	}
	else
	{
		_fe3d.logger_throwWarning("Project \"" + _currentProjectID + "\" corrupted: scenes folder missing!");
	}

	return sceneNames;
}

void SceneEditor::_deleteSceneFile(const string& sceneName)
{
	// Check if scene file is still existing
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : 
		("projects\\" + _currentProjectID)) + "\\scenes\\editor\\" + sceneName + ".fe3d";
	if (_fe3d.misc_isFileExisting(filePath))
	{
		std::filesystem::remove_all(filePath);
	}
	else
	{
		_fe3d.logger_throwWarning("Project folder corrupted of project \"" + _currentProjectID + "\"!");
	}
}

void SceneEditor::_handleValueChanging(const string& screenID, string buttonID, string writefieldID, float& value, float adder, 
	float multiplier, float minimum, float maximum)
{
	// Plus & minus button handling
	if (_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_LEFT))
	{
		if (_gui.getViewport("right")->getWindow("main")->getScreen(screenID)->getButton(buttonID)->isHovered())
		{
			value += adder;
		}
	}

	// Writefield handling
	auto writefield = _gui.getViewport("right")->getWindow("main")->getScreen(screenID)->getWritefield(writefieldID);
	if (writefield->confirmedInput())
	{
		if (writefield->getTextContent() != "")
		{
			// Cannot be empty
			if (writefield->getTextContent() == "?")
			{
				writefield->setTextContent(to_string(value));
			}

			value = static_cast<float>(stoi(writefield->getTextContent())) / multiplier;
		}
	}

	// Clamp value range
	value = std::clamp(value, minimum, maximum);

	// Writefield filling
	if (!_gui.getViewport("right")->getWindow("main")->getScreen(screenID)->getWritefield(writefieldID)->isActive())
	{
		_gui.getViewport("right")->getWindow("main")->getScreen(screenID)->getWritefield(writefieldID)->
			setTextContent(to_string(static_cast<int>(value * multiplier)));
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