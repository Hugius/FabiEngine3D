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

void SceneEditor::setCurrentProjectID(const string& ID)
{
	_currentProjectID = ID;
}

void SceneEditor::_selectModel(const string& ID)
{
	// Set ID
	_selectedModelID = ID;

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine_assets\\textures\\cursor_pointing.png");

	// Check if nothing is active
	if (_activeModelID.empty() && _activeBillboardID.empty() && _activeSpeakerID.empty() && _activeLampID.empty() && _activeCameraID.empty())
	{
		// Removing the unique number from the modelID and updating the text content
		string tempID = ID;
		reverse(tempID.begin(), tempID.end());
		string rawID = tempID.substr(tempID.find('_') + 1);
		reverse(rawID.begin(), rawID.end());
		_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), true);
		_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), "Selected model: " + rawID, 0.025f);
	}
}

void SceneEditor::_activateModel(const string& ID)
{
	// Set ID
	_activeModelID = ID;

	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	auto position = _fe3d.modelEntity_getBasePosition(_activeModelID);

	// Update buttons hoverability
	rightWindow->getScreen("modelPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("modelPropertiesMenu")->getButton("rotation")->setHoverable(true);
	rightWindow->getScreen("modelPropertiesMenu")->getButton("size")->setHoverable(true);

	// Filling write fields
	rightWindow->getScreen("modelPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("modelPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("modelPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));

	// Removing the unique number from the modelID and updating the text content
	string tempID = ID;
	reverse(tempID.begin(), tempID.end());
	string rawID = tempID.substr(tempID.find('_') + 1);
	reverse(rawID.begin(), rawID.end());
	_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), true);
	_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), "Active model: " + rawID, 0.025f);
}

void SceneEditor::_selectBillboard(const string& ID)
{
	// Set ID
	_selectedBillboardID = ID;

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine_assets\\textures\\cursor_pointing.png");

	// Check if nothing is active
	if (_activeModelID.empty() && _activeBillboardID.empty() && _activeSpeakerID.empty() && _activeLampID.empty() && _activeCameraID.empty())
	{
		// Removing the unique number from the billboardID and updating the text content
		string tempID = ID;
		reverse(tempID.begin(), tempID.end());
		string rawID = tempID.substr(tempID.find('_') + 1);
		reverse(rawID.begin(), rawID.end());
		_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), true);
		_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), "Selected billboard: " + rawID, 0.025f);
	}
}

void SceneEditor::_activateBillboard(const string& ID)
{
	// Set ID
	_activeBillboardID = ID;

	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	auto position = _fe3d.billboardEntity_getPosition(_activeBillboardID);

	// Update buttons hoverability
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("position")->setHoverable(false);
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("rotation")->setHoverable(true);
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("size")->setHoverable(true);

	// Filling write fields
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));

	// Removing the unique number from the billboardID and updating the text content
	string tempID = ID;
	reverse(tempID.begin(), tempID.end());
	string rawID = tempID.substr(tempID.find('_') + 1);
	reverse(rawID.begin(), rawID.end());
	_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), true);
	_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), "Active billboard: " + rawID, 0.025f);
}

void SceneEditor::_selectSound(const string& ID)
{
	// Set ID
	_selectedSpeakerID = ("@@speaker_" + ID);

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine_assets\\textures\\cursor_pointing.png");

	// Check if nothing is active
	if (_activeModelID.empty() && _activeBillboardID.empty() && _activeSpeakerID.empty() && _activeLampID.empty() && _activeCameraID.empty())
	{
		// Removing the unique number from the soundID and updating the text content
		string tempID = ID;
		reverse(tempID.begin(), tempID.end());
		string rawID = tempID.substr(tempID.find('_') + 1);
		reverse(rawID.begin(), rawID.end());
		_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), true);
		_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), "Selected sound: " + rawID, 0.025f);
	}
}

void SceneEditor::_selectLight(const string& ID)
{
	// Set ID
	_selectedLampID = ("@@lamp_" + ID);

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine_assets\\textures\\cursor_pointing.png");
}

void SceneEditor::_selectReflection(const string& ID)
{
	// Set ID
	_selectedCameraID = ("@@camera_" + ID);

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine_assets\\textures\\cursor_pointing.png");
}

void SceneEditor::_activateSound(const string& ID)
{
	// Set ID
	_activeSpeakerID = ("@@speaker_" + ID);

	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	auto position = _fe3d.sound_getPosition(_activeSpeakerID.substr(string("@@speaker_").size()));
	auto maxVolume = _fe3d.sound_getMaxVolume(_activeSpeakerID.substr(string("@@speaker_").size()));
	auto maxDistance = _fe3d.sound_getMaxDistance(_activeSpeakerID.substr(string("@@speaker_").size()));

	// Filling write fields
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("volume")->changeTextContent(to_string(static_cast<int>(maxVolume * 100.0f)));
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("distance")->changeTextContent(to_string(static_cast<int>(maxDistance)));

	// Removing the unique number from the soundID and updating the text content
	string tempID = ID;
	reverse(tempID.begin(), tempID.end());
	string rawID = tempID.substr(tempID.find('_') + 1);
	reverse(rawID.begin(), rawID.end());
	_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), true);
	_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), "Active sound: " + rawID, 0.025f);
}

void SceneEditor::_activateLight(const string& ID)
{
	// Set ID
	_activeLampID = ("@@lamp_" + ID);

	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	auto position = _fe3d.modelEntity_getBasePosition(_activeLampID);

	// Update buttons hoverability
	rightWindow->getScreen("lightPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("lightPropertiesMenu")->getButton("radius")->setHoverable(true);
	rightWindow->getScreen("lightPropertiesMenu")->getButton("color")->setHoverable(true);

	// Filling writeFields
	rightWindow->getScreen("lightPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("lightPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("lightPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
}

void SceneEditor::_activateReflection(const string& ID)
{
	// Set ID
	_activeCameraID = ("@@camera_" + ID);

	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	auto position = _fe3d.modelEntity_getBasePosition(_activeCameraID);

	// Filling writeFields
	rightWindow->getScreen("reflectionPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("reflectionPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("reflectionPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
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

void SceneEditor::_deactivateLight()
{
	_activeLampID = "";
}

void SceneEditor::_deactivateReflection()
{
	_activeCameraID = "";
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
			string sceneID = string(entry.path().string());
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

void SceneEditor::_deleteSceneFile(const string& ID)
{
	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
		("projects\\" + _currentProjectID)) + "\\scenes\\editor\\" + ID + ".fe3d";

	// Check if scene file is still existing
	if (_fe3d.misc_isFileExisting(filePath))
	{
		remove_all(filePath);
	}
	else
	{
		Logger::throwWarning("Cannot delete scene with ID \"" + ID + "\"!");
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

void SceneEditor::_updateModelBlinking(const string& ID, int& direction)
{
	// Reset multiplier if nothing active/selected
	if (ID.empty())
	{
		direction = 1;
	}

	// Update model inversion
	if (!ID.empty())
	{
		// Update all parts
		auto partIDs = _fe3d.modelEntity_getPartIDs(ID);
		for (size_t i = 0; i < partIDs.size(); i++)
		{
			// Check if inversion reached minimum
			if ((_fe3d.modelEntity_getColorInversion(ID, partIDs[i]) == 0.0f) && (i == 0))
			{
				direction *= -1;
			}

			// Check if inversion reached maximum
			if ((_fe3d.modelEntity_getColorInversion(ID, partIDs[i]) == 1.0f) && (i == 0))
			{
				direction *= -1;
			}

			// Set model inversion
			float speed = (MODEL_BLINKING_SPEED * static_cast<float>(direction));
			_fe3d.modelEntity_setColorInversion(ID, partIDs[i], (_fe3d.modelEntity_getColorInversion(ID, partIDs[i]) + speed));
		}
	}
}

void SceneEditor::_updateBillboardBlinking(const string& ID, int& direction)
{
	// Reset direction if nothing active/selected
	if (ID.empty())
	{
		direction = 1;
	}

	// Update billboard inversion
	if (ID != "")
	{
		// Check if inversion reached minimum
		if (_fe3d.billboardEntity_getColorInversion(ID) == 0.0f)
		{
			direction *= -1;
		}

		// Check if inversion reached maximum
		if (_fe3d.billboardEntity_getColorInversion(ID) == 1.0f)
		{
			direction *= -1;
		}

		// Set billboard inversion
		float speed = (BILLBOARD_BLINKING_SPEED * static_cast<float>(direction));
		_fe3d.billboardEntity_setColorInversion(ID, _fe3d.billboardEntity_getColorInversion(ID) + speed);
	}
}

void SceneEditor::_updateSpeakerAnimation(const string& ID, int& direction)
{
	// Reset direction if nothing active/selected
	if (ID.empty())
	{
		direction = 1;
	}

	// Update speaker animation
	if (ID != "")
	{
		// Check if inversion reached minimum
		if (_fe3d.modelEntity_getBaseSize(ID).y < DEFAULT_SPEAKER_SIZE.y)
		{
			_fe3d.modelEntity_setBaseSize(ID, DEFAULT_SPEAKER_SIZE);
			direction *= -1;
		}

		// Check if inversion reached maximum
		if (_fe3d.modelEntity_getBaseSize(ID).y > (DEFAULT_SPEAKER_SIZE.y * SPEAKER_SIZE_INCREASE))
		{
			_fe3d.modelEntity_setBaseSize(ID, (DEFAULT_SPEAKER_SIZE * SPEAKER_SIZE_INCREASE));
			direction *= -1;
		}

		// Set new sizes
		Vec3 modelSpeed = (Vec3(SPEAKER_ANIMATION_SPEED) * Vec3(static_cast<float>(direction)));
		modelSpeed *= ((DEFAULT_SPEAKER_SIZE * SPEAKER_SIZE_INCREASE) - DEFAULT_SPEAKER_SIZE);
		_fe3d.modelEntity_setBaseSize(ID, (_fe3d.modelEntity_getBaseSize(ID) + modelSpeed));
	}
}

void SceneEditor::_updateLampAnimation(const string& ID, int& direction)
{
	// Reset direction if nothing active/selected
	if (ID.empty())
	{
		direction = 1;
	}

	// Update lamp animation
	if (ID != "")
	{
		// Check if inversion reached minimum
		if (_fe3d.modelEntity_getBaseSize(ID).y < DEFAULT_LAMP_SIZE.y)
		{
			_fe3d.modelEntity_setBaseSize(ID, DEFAULT_LAMP_SIZE);
			direction *= -1;
		}

		// Check if inversion reached maximum
		if (_fe3d.modelEntity_getBaseSize(ID).y >(DEFAULT_LAMP_SIZE.y * LAMP_SIZE_INCREASE))
		{
			_fe3d.modelEntity_setBaseSize(ID, (DEFAULT_LAMP_SIZE * LAMP_SIZE_INCREASE));
			direction *= -1;
		}

		// Set new sizes
		Vec3 modelSpeed = (Vec3(LAMP_ANIMATION_SPEED) * Vec3(static_cast<float>(direction)));
		modelSpeed *= ((DEFAULT_LAMP_SIZE * LAMP_SIZE_INCREASE) - DEFAULT_LAMP_SIZE);
		_fe3d.modelEntity_setBaseSize(ID, (_fe3d.modelEntity_getBaseSize(ID) + modelSpeed));
	}
}

void SceneEditor::_updateCameraAnimation(const string& ID, int& direction)
{
	// Reset direction if nothing active/selected
	if (ID.empty())
	{
		direction = 1;
	}

	// Update reflection animation
	if (ID != "")
	{
		// Check if inversion reached minimum
		if (_fe3d.modelEntity_getBaseSize(ID).y < DEFAULT_CAMERA_SIZE.y)
		{
			_fe3d.modelEntity_setBaseSize(ID, DEFAULT_CAMERA_SIZE);
			direction *= -1;
		}

		// Check if inversion reached maximum
		if (_fe3d.modelEntity_getBaseSize(ID).y >(DEFAULT_CAMERA_SIZE.y * CAMERA_SIZE_INCREASE))
		{
			_fe3d.modelEntity_setBaseSize(ID, (DEFAULT_CAMERA_SIZE * CAMERA_SIZE_INCREASE));
			direction *= -1;
		}

		// Set new sizes
		Vec3 modelSpeed = (Vec3(CAMERA_ANIMATION_SPEED) * Vec3(static_cast<float>(direction)));
		modelSpeed *= ((DEFAULT_CAMERA_SIZE * CAMERA_SIZE_INCREASE) - DEFAULT_CAMERA_SIZE);
		_fe3d.modelEntity_setBaseSize(ID, _fe3d.modelEntity_getBaseSize(ID) + modelSpeed);
	}
}