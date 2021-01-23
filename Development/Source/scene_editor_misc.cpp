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
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("No current project loaded --> SceneEditor::isSceneExisting()");
	}

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\scenes\\" + fileName + ".fe3d";

	// Check if scene file exists
	return (_fe3d.misc_isFileExisting(filePath));
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
	if (_activeModelID == "" && _activeBillboardID == "" && _activeLightBulbID == "" && _activeSpeakerID == "")
	{
		// Removing the unique number from the modelID and updating the text content
		string modelName = modelID.substr(modelID.find('@') + 1);
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
	Vec3 position = _fe3d.gameEntity_getPosition(_activeModelID);
	_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getWriteField("x")->setTextContent(to_string(static_cast<int>(position.x)));
	_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getWriteField("y")->setTextContent(to_string(static_cast<int>(position.y)));
	_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getWriteField("z")->setTextContent(to_string(static_cast<int>(position.z)));

	// Removing the unique number from the modelID and updating the text content
	string modelName = modelID.substr(modelID.find('@') + 1);
	string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
	_fe3d.textEntity_show(textEntityID);
	_fe3d.textEntity_setTextContent(textEntityID, "Active model: " + modelName, 0.025f);
}

void SceneEditor::_selectBillboard(const string& billboardID)
{
	_selectedBillboardID = billboardID;

	// Change cursor
	_fe3d.guiEntity_changeTexture("@@cursor", "engine\\textures\\cursor_pointing.png");

	// Check if nothing is active
	if (_activeBillboardID == "" && _activeModelID == "" && _activeLightBulbID == "" && _activeSpeakerID == "")
	{
		// Removing the unique number from the billboardID and updating the text content
		string billboardName = billboardID.substr(billboardID.find('@') + 1);
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
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("x")->setTextContent(to_string(static_cast<int>(position.x)));
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("y")->setTextContent(to_string(static_cast<int>(position.y)));
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("z")->setTextContent(to_string(static_cast<int>(position.z)));

	// Removing the unique number from the billboardID and updating the text content
	string billboardName = billboardID.substr(billboardID.find('@') + 1);
	string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID();
	_fe3d.textEntity_show(textEntityID);
	_fe3d.textEntity_setTextContent(textEntityID, "Active billboard: " + billboardName, 0.025f);
}

void SceneEditor::_selectAudio(const string& audioID)
{
	_selectedSpeakerID = "@speaker_" + audioID;

	// Change cursor
	_fe3d.guiEntity_changeTexture("@@cursor", "engine\\textures\\cursor_pointing.png");

	// Check if nothing is active
	if (_activeBillboardID == "" && _activeModelID == "" && _activeLightBulbID == "" && _activeSpeakerID == "")
	{
		// Removing the unique number from the audioID and updating the text content
		string audioName = audioID.substr(audioID.find('@') + 1);
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
	Vec3 position = _fe3d.audioEntity_getPosition(_activeSpeakerID.substr(string("@speaker_").size()));
	float maxVolume = _fe3d.audioEntity_getMaxVolume(_activeSpeakerID.substr(string("@speaker_").size()));
	float maxDistance = _fe3d.audioEntity_getMaxDistance(_activeSpeakerID.substr(string("@speaker_").size()));
	_gui.getViewport("right")->getWindow("main")->getScreen("audioPropertiesMenu")->getWriteField("x")->setTextContent(to_string(static_cast<int>(position.x)));
	_gui.getViewport("right")->getWindow("main")->getScreen("audioPropertiesMenu")->getWriteField("y")->setTextContent(to_string(static_cast<int>(position.y)));
	_gui.getViewport("right")->getWindow("main")->getScreen("audioPropertiesMenu")->getWriteField("z")->setTextContent(to_string(static_cast<int>(position.z)));
	_gui.getViewport("right")->getWindow("main")->getScreen("audioPropertiesMenu")->getWriteField("volume")->setTextContent(to_string(static_cast<int>(maxVolume * 100.0f)));
	_gui.getViewport("right")->getWindow("main")->getScreen("audioPropertiesMenu")->getWriteField("distance")->setTextContent(to_string(static_cast<int>(maxDistance)));

	// Removing the unique number from the billboardID and updating the text content
	string audioName = audioID.substr(audioID.find('@') + 1);
	string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedAudioName")->getEntityID();
	_fe3d.textEntity_show(textEntityID);
	_fe3d.textEntity_setTextContent(textEntityID, "Active audio: " + audioName, 0.025f);
}

vector<string> SceneEditor::_loadSceneNames()
{
	vector<string> sceneNames;

	// Compose folder path
	string sceneDirectoryPath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\scenes\\";

	// Check if scenes directory exists
	if (_fe3d.misc_isDirectory(sceneDirectoryPath))
	{
		// Get all project names
		for (const auto& entry : std::filesystem::directory_iterator(sceneDirectoryPath))
		{
			string sceneName = string(entry.path().u8string());
			sceneName.erase(0, sceneDirectoryPath.size());
			sceneNames.push_back(sceneName.substr(0, sceneName.size() - 5));
		}
	}
	else
	{
		_fe3d.logger_throwWarning("Project folder corrupted of project \"" + _currentProjectName + "\"!");
	}

	return sceneNames;
}

void SceneEditor::_deleteSceneFile(const string& sceneName)
{
	// Check if scene file is still existing
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\scenes\\" + sceneName + ".fe3d";
	if (_fe3d.misc_isFileExisting(filePath))
	{
		std::filesystem::remove_all(filePath);
	}
	else
	{
		_fe3d.logger_throwWarning("Project folder corrupted of project \"" + _currentProjectName + "\"!");
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
		if (_fe3d.gameEntity_getLightness(modelID) > _initialModelLightness[modelID] ||
			_fe3d.gameEntity_getLightness(modelID) < 0.0f)
		{
			multiplier *= -1;
		}

		// Set model lightness
		float range = _initialModelLightness[modelID];
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
		if (_fe3d.billboardEntity_getLightness(billboardID) > _initialBillboardLightness[billboardID] ||
			_fe3d.billboardEntity_getLightness(billboardID) < 0.0f)
		{
			multiplier *= -1;
		}

		// Set billboard lightness
		float range = _initialBillboardLightness[billboardID];
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
		_fe3d.gameEntity_setSize(modelID, _fe3d.gameEntity_getSize(modelID) + Vec3(speed));
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
		if (_fe3d.gameEntity_getSize(modelID).x > _defaultSpeakerSize.x * 1.5f ||
			_fe3d.gameEntity_getSize(modelID).x < _defaultSpeakerSize.x)
		{
			multiplier *= -1;
		}

		// Set model size
		float speed = (_speakerAnimationSpeed * static_cast<float>(multiplier));
		_fe3d.gameEntity_setSize(modelID, _fe3d.gameEntity_getSize(modelID) + Vec3(speed));
		_fe3d.aabbEntity_setSize(modelID, _fe3d.aabbEntity_getSize(modelID) + Vec3(speed));
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
	auto writefield = _gui.getViewport("right")->getWindow("main")->getScreen(screenID)->getWriteField(writefieldID);
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
	if (!_gui.getViewport("right")->getWindow("main")->getScreen(screenID)->getWriteField(writefieldID)->isActive())
	{
		_gui.getViewport("right")->getWindow("main")->getScreen(screenID)->getWriteField(writefieldID)->
			setTextContent(to_string(static_cast<int>(value * multiplier)));
	}
}

void SceneEditor::_updateMiscellaneous()
{
	if (_isEditorLoaded)
	{
		// Lock toggling if GUI focused or cursor not in 3D viewport
		_fe3d.input_setKeyTogglingLocked(_gui.getGlobalScreen()->isFocused() || !_fe3d.misc_isCursorInsideViewport());

		// Update bounding box visibility
		if (_fe3d.input_getKeyToggled(InputType::KEY_B))
		{
			_fe3d.misc_enableAabbFrameRendering();
		}
		else
		{
			_fe3d.misc_disableAabbFrameRendering();
		}

		// Wireframe rendering
		if (_fe3d.input_getKeyToggled(InputType::KEY_F))
		{
			_fe3d.misc_enableWireframeRendering();
		}
		else
		{
			_fe3d.misc_disableWireframeRendering();
		}

		// Debug rendering
		if (_fe3d.input_getKeyToggled(InputType::KEY_H))
		{
			_fe3d.misc_enableDebugRendering();
		}
		else
		{
			_fe3d.misc_disableDebugRendering();
		}
	}
}

void SceneEditor::clearScene()
{
	// Disable graphics
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableSpecularLighting(true);
	_fe3d.gfx_disablePointLighting(true);
	_fe3d.gfx_disableFog(true);
	_fe3d.gfx_disableSkyReflections(true);
	_fe3d.gfx_disableSceneReflections(true);
	_fe3d.gfx_disableLightMapping(true);
	_fe3d.gfx_disableNormalMapping(true);
	_fe3d.gfx_disableShadows(true);
	_fe3d.gfx_disableWaterEffects(true);
	_fe3d.gfx_disableSkyHDR(true);
	_fe3d.gfx_disableDOF(true);
	_fe3d.gfx_disableMotionBlur(true);
	_fe3d.gfx_disableLensFlare(true);

	// Check if currently in scene editor
	if (_isEditorLoaded)
	{
		// Delete sky entities
		for (auto& ID : _fe3d.skyEntity_getAllIDs())
		{
			if (ID[0] != '@')
			{
				_fe3d.skyEntity_delete(ID);
			}
		}

		// Delete TERRAIN entities
		for (auto& ID : _fe3d.terrainEntity_getAllIDs())
		{
			if (ID[0] != '@')
			{
				_fe3d.terrainEntity_delete(ID);
			}
		}

		// Delete WATER entities
		for (auto& ID : _fe3d.waterEntity_getAllIDs())
		{
			if (ID[0] != '@')
			{
				_fe3d.waterEntity_delete(ID);
			}
		}

		// Delete GAME entities
		for (auto& ID : _fe3d.gameEntity_getAllIDs())
		{
			if (_currentSceneName.empty()) // Not editing scene
			{
				if (ID[0] != '@')
				{
					_fe3d.gameEntity_delete(ID);
				}
			}
			else // Editing scene
			{
				if (ID[0] != '@' || ((ID != _previewPointlightID) && (ID != _previewSpeakerID) &&
					(_fe3d.gameEntity_getObjPath(ID) == _lightBulbModelPath) || (_fe3d.gameEntity_getObjPath(ID) == _speakerModelPath)))
				{
					_fe3d.gameEntity_delete(ID);
				}
			}
		}

		// Delete BILLBOARD entities
		for (auto& ID : _fe3d.billboardEntity_getAllIDs())
		{
			if (ID[0] != '@')
			{
				_fe3d.billboardEntity_delete(ID);
			}
			else if (ID == "@@lightSource") // Hide special "preview" entity
			{
				_fe3d.billboardEntity_hide(ID);
			}
		}

		// Delete LIGHT entities
		for (auto& ID : _fe3d.lightEntity_getAllIDs())
		{
			if (ID[0] != '@')
			{
				_fe3d.lightEntity_delete(ID);
			}
		}

		// Delete AUDIO entities
		for (auto& ID : _fe3d.audioEntity_getAllIDs())
		{
			if (ID[0] != '@')
			{
				_fe3d.audioEntity_delete(ID);
			}
		}

		// Delete music
		_fe3d.music_clearPlaylist();
	}
	else // Executing script
	{
		// Delete all sky entities except the engine background
		for (auto& ID : _fe3d.skyEntity_getAllIDs())
		{
			if (ID != "@@engineBackground")
			{
				_fe3d.skyEntity_delete(ID);
			}
		}
		_fe3d.skyEntity_mixWithSelected("");
		_fe3d.skyEntity_setMixValue(0.0f);

		// Delete all other entities
		_fe3d.terrainEntity_deleteAll();
		_fe3d.waterEntity_deleteAll();
		_fe3d.gameEntity_deleteAll();
		_fe3d.billboardEntity_deleteAll();
		_fe3d.aabbEntity_deleteAll();
		_fe3d.lightEntity_deleteAll();
		_fe3d.audioEntity_deleteAll();
		_fe3d.music_clearPlaylist();

		// Stop animations
		_animationEditor.stopAllAnimations();
	}
}