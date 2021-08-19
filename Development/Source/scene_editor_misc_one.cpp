#include "scene_editor.hpp"
#include "logger.hpp"

#include <algorithm>
#include <filesystem>

using std::clamp;
using std::filesystem::directory_iterator;
using std::filesystem::remove_all;

bool SceneEditor::isLoaded()
{
	return _isEditorLoaded;
}

bool SceneEditor::isSceneExisting(const string& filename)
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("SceneEditor::isSceneExisting");
	}

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
		("projects\\" + _currentProjectID)) + "\\scenes\\editor\\" + filename + ".fe3d";

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
	// Set ID
	_selectedModelID = modelID;

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine_assets\\textures\\cursor_pointing.png");

	// Check if nothing is active
	if (_activeModelID.empty() && _activeBillboardID.empty() && _activeLampID.empty() && _activeSpeakerID.empty())
	{
		// Removing the unique number from the modelID and updating the text content
		string tempID = modelID;
		reverse(tempID.begin(), tempID.end());
		string rawID = tempID.substr(tempID.find('_') + 1);
		reverse(rawID.begin(), rawID.end());
		_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), true);
		_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), "Selected model: " + rawID, 0.025f);
	}
}

void SceneEditor::_activateModel(const string& modelID)
{
	// Set ID
	_activeModelID = modelID;

	// Update buttons hoverability
	_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("position")->setHoverable(false);
	_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("rotation")->setHoverable(true);
	_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("size")->setHoverable(true);

	// Filling writeFields
	Vec3 position = _fe3d.modelEntity_getPosition(_activeModelID);
	_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));

	// Removing the unique number from the modelID and updating the text content
	string tempID = modelID;
	reverse(tempID.begin(), tempID.end());
	string rawID = tempID.substr(tempID.find('_') + 1);
	reverse(rawID.begin(), rawID.end());
	_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), true);
	_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), "Active model: " + rawID, 0.025f);
}

void SceneEditor::_selectBillboard(const string& billboardID)
{
	// Set ID
	_selectedBillboardID = billboardID;

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine_assets\\textures\\cursor_pointing.png");

	// Check if nothing is active
	if (_activeBillboardID.empty() && _activeModelID.empty() && _activeLampID.empty() && _activeSpeakerID.empty())
	{
		// Removing the unique number from the billboardID and updating the text content
		string tempID = billboardID;
		reverse(tempID.begin(), tempID.end());
		string rawID = tempID.substr(tempID.find('_') + 1);
		reverse(rawID.begin(), rawID.end());
		_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), true);
		_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), "Selected billboard: " + rawID, 0.025f);
	}
}

void SceneEditor::_activateBillboard(const string& billboardID)
{
	// Set ID
	_activeBillboardID = billboardID;

	// Update buttons hoverability
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("position")->setHoverable(false);
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("rotation")->setHoverable(true);
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("size")->setHoverable(true);

	// Filling writeFields
	Vec3 position = _fe3d.billboardEntity_getPosition(_activeBillboardID);
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));

	// Removing the unique number from the billboardID and updating the text content
	string tempID = billboardID;
	reverse(tempID.begin(), tempID.end());
	string rawID = tempID.substr(tempID.find('_') + 1);
	reverse(rawID.begin(), rawID.end());
	_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), true);
	_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), "Active billboard: " + rawID, 0.025f);
}

void SceneEditor::_selectSound(const string& soundID)
{
	// Set ID
	_selectedSpeakerID = ("@@speaker_" + soundID);

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine_assets\\textures\\cursor_pointing.png");

	// Check if nothing is active
	if (_activeBillboardID.empty() && _activeModelID.empty() && _activeLampID.empty() && _activeSpeakerID.empty())
	{
		// Removing the unique number from the soundID and updating the text content
		string tempID = soundID;
		reverse(tempID.begin(), tempID.end());
		string rawID = tempID.substr(tempID.find('_') + 1);
		reverse(rawID.begin(), rawID.end());
		_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), true);
		_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), "Selected sound: " + rawID, 0.025f);
	}
}

void SceneEditor::_activateSound(const string& soundID)
{
	// Set ID
	_activeSpeakerID = ("@@speaker_" + soundID);

	// Filling writeFields
	Vec3 position = _fe3d.sound_getPosition(_activeSpeakerID.substr(string("@@speaker_").size()));
	float maxVolume = _fe3d.sound_getMaxVolume(_activeSpeakerID.substr(string("@@speaker_").size()));
	float maxDistance = _fe3d.sound_getMaxDistance(_activeSpeakerID.substr(string("@@speaker_").size()));
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("volume")->changeTextContent(to_string(static_cast<int>(maxVolume * 100.0f)));
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("distance")->changeTextContent(to_string(static_cast<int>(maxDistance)));

	// Removing the unique number from the soundID and updating the text content
	string tempID = soundID;
	reverse(tempID.begin(), tempID.end());
	string rawID = tempID.substr(tempID.find('_') + 1);
	reverse(rawID.begin(), rawID.end());
	_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), true);
	_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), "Active sound: " + rawID, 0.025f);
}

void SceneEditor::_deactivateModel()
{
	_activeModelID = "";
	_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), false);
}

void SceneEditor::_deactivateBillboard()
{
	_activeBillboardID = "";
	_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), false);
}

void SceneEditor::_deactivateSound()
{
	_activeSpeakerID = "";
	_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), false);
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
		for (const auto& entry : directory_iterator(directoryPath))
		{
			string sceneID = string(entry.path().u8string());
			sceneID.erase(0, directoryPath.size());
			sceneIDs.push_back(sceneID.substr(0, sceneID.size() - 5));
		}
	}
	else
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: directory `scenes\\editor\\` missing!");
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
		remove_all(filePath);
	}
	else
	{
		Logger::throwWarning("Cannot delete scene with ID \"" + sceneID + "\"!");
	}
}

void SceneEditor::_handleValueChanging(const string& screenID, string buttonID, string writeFieldID, float& value, float adder, 
	float multiplier, float minimum, float maximum)
{
	// Temporary values
	auto writeField = _gui.getViewport("right")->getWindow("main")->getScreen(screenID)->getWriteField(writeFieldID);

	// Plus & minus button handling
	if (_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_LEFT))
	{
		if (_gui.getViewport("right")->getWindow("main")->getScreen(screenID)->getButton(buttonID)->isHovered())
		{
			value += adder;
		}
	}

	// WriteField pre-update
	if (!writeField->isActive())
	{
		writeField->changeTextContent(to_string(static_cast<int>(value * multiplier)));
	}

	// WriteField handling
	if (writeField->getTextContent().empty())
	{
		value = 0.0f; // Reset value to default
	}
	else
	{
		// Check if something is filled in
		if (writeField->isActive())
		{
			value = (static_cast<float>(stoi(writeField->getTextContent())) / multiplier); // Update value in realtime
		}
	}

	// Clamp value range
	value = clamp(value, minimum, maximum);

	// WriteField post-update
	if (!writeField->isActive())
	{
		writeField->changeTextContent(to_string(static_cast<int>(value * multiplier)));
	}
}

void SceneEditor::_updateModelBlinking(const string& modelID, int& direction)
{
	// Reset multiplier if nothing active/selected
	if (modelID.empty())
	{
		direction = 1;
	}

	// Update model inversion
	if (modelID != "")
	{
		// Check if inversion reached minimum
		if (_fe3d.modelEntity_getInversion(modelID) == 0.0f)
		{
			direction *= -1;
		}

		// Check if inversion reached maximum
		if (_fe3d.modelEntity_getInversion(modelID) == 1.0f)
		{
			direction *= -1;
		}

		// Set model inversion
		float speed = (MODEL_BLINKING_SPEED * static_cast<float>(direction));
		_fe3d.modelEntity_setInversion(modelID, _fe3d.modelEntity_getInversion(modelID) + speed);
	}
}

void SceneEditor::_updateBillboardBlinking(const string& billboardID, int& direction)
{
	// Reset direction if nothing active/selected
	if (billboardID.empty())
	{
		direction = 1;
	}

	// Update billboard inversion
	if (billboardID != "")
	{
		// Check if inversion reached minimum
		if (_fe3d.billboardEntity_getInversion(billboardID) == 0.0f)
		{
			direction *= -1;
		}

		// Check if inversion reached maximum
		if (_fe3d.billboardEntity_getInversion(billboardID) == 1.0f)
		{
			direction *= -1;
		}

		// Set billboard inversion
		float speed = (BILLBOARD_BLINKING_SPEED * static_cast<float>(direction));
		_fe3d.billboardEntity_setInversion(billboardID, _fe3d.billboardEntity_getInversion(billboardID) + speed);
	}
}

void SceneEditor::_updateSpeakerAnimation(const string& modelID, int& direction)
{
	// Reset direction if nothing active/selected
	if (modelID.empty())
	{
		direction = 1;
	}

	// Update speaker animation
	if (modelID != "")
	{
		// Check if inversion reached minimum
		if (_fe3d.modelEntity_getSize(modelID).y < DEFAULT_SPEAKER_SIZE.y)
		{
			_fe3d.modelEntity_setSize(modelID, DEFAULT_SPEAKER_SIZE);
			direction *= -1;
		}

		// Check if inversion reached maximum
		if (_fe3d.modelEntity_getSize(modelID).y > (DEFAULT_SPEAKER_SIZE.y * SPEAKER_SIZE_INCREASE))
		{
			_fe3d.modelEntity_setSize(modelID, (DEFAULT_SPEAKER_SIZE * SPEAKER_SIZE_INCREASE));
			direction *= -1;
		}

		// Set new sizes
		Vec3 modelSpeed = (Vec3(SPEAKER_ANIMATION_SPEED) * Vec3(static_cast<float>(direction)));
		modelSpeed *= ((DEFAULT_SPEAKER_SIZE * SPEAKER_SIZE_INCREASE) - DEFAULT_SPEAKER_SIZE);
		_fe3d.modelEntity_setSize(modelID, _fe3d.modelEntity_getSize(modelID) + modelSpeed);
	}
}

void SceneEditor::_updateLampAnimation(const string& modelID, int& direction)
{
	// Reset direction if nothing active/selected
	if (modelID.empty())
	{
		direction = 1;
	}

	// Update lamp animation
	if (modelID != "")
	{
		// Check if inversion reached minimum
		if (_fe3d.modelEntity_getSize(modelID).y < DEFAULT_LAMP_SIZE.y)
		{
			_fe3d.modelEntity_setSize(modelID, DEFAULT_LAMP_SIZE);
			direction *= -1;
		}

		// Check if inversion reached maximum
		if (_fe3d.modelEntity_getSize(modelID).y > (DEFAULT_LAMP_SIZE.y * LAMP_SIZE_INCREASE))
		{
			_fe3d.modelEntity_setSize(modelID, (DEFAULT_LAMP_SIZE * LAMP_SIZE_INCREASE));
			direction *= -1;
		}

		// Set new sizes
		Vec3 modelSpeed = (Vec3(LAMP_ANIMATION_SPEED) * Vec3(static_cast<float>(direction)));
		modelSpeed *= ((DEFAULT_LAMP_SIZE * LAMP_SIZE_INCREASE) - DEFAULT_LAMP_SIZE);
		_fe3d.modelEntity_setSize(modelID, _fe3d.modelEntity_getSize(modelID) + modelSpeed);
	}
}