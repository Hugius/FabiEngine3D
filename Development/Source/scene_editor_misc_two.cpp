#include "scene_editor.hpp"

#include <algorithm>
#include <filesystem>

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
		if (_fe3d.modelEntity_getLightness(modelID) > _initialModelLightness[modelID] ||
			_fe3d.modelEntity_getLightness(modelID) < 0.0f)
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
			_fe3d.billboardEntity_getLightness(billboardID) < 0.0f)
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

void SceneEditor::clearCurrentScene()
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

	// Delete SKY entity
	if (!_loadedSkyID.empty())
	{
		// Delete sky
		if (_fe3d.skyEntity_isExisting(_loadedSkyID))
		{
			_fe3d.skyEntity_delete(_loadedSkyID);
		}

		// Miscellaneous
		_fe3d.skyEntity_mixWithSelected("");
		_fe3d.skyEntity_setMixValue(0.0f);
	}

	// Delete TERRAIN entity
	if (!_loadedTerrainID.empty())
	{
		// Delete terrain
		if (_fe3d.terrainEntity_isExisting(_loadedTerrainID))
		{
			_fe3d.terrainEntity_delete(_loadedTerrainID);
		}
	}

	// Delete WATER entity
	if (!_loadedWaterID.empty())
	{
		// Delete water
		if (_fe3d.waterEntity_isExisting(_loadedWaterID))
		{
			_fe3d.waterEntity_delete(_loadedWaterID);
		}
	}

	// Delete GAME entities
	for (auto& ID : _loadedModelIDs)
	{
		// Delete model
		if (_fe3d.modelEntity_isExisting(ID))
		{
			_fe3d.modelEntity_delete(ID);
		}

		// Stop animation
		auto animationID = _animationEditor.getPlayingAnimationNames(ID);
		if (!animationID.empty())
		{
			_animationEditor.stopAnimation(animationID.back(), ID);
		}
	}

	// Delete BILLBOARD entities
	for (auto& ID : _loadedBillboardIDs)
	{
		// Delete billboard
		if (_fe3d.billboardEntity_isExisting(ID))
		{
			_fe3d.billboardEntity_delete(ID);
		}
	}

	// Hide lightsource billboard
	if (_fe3d.billboardEntity_isExisting("@@lightSource"))
	{
		_fe3d.billboardEntity_hide("@@lightSource");
	}

	// Delete LIGHT entities
	for (auto& ID : _loadedLightIDs)
	{
		if (_fe3d.lightEntity_isExisting(ID))
		{
			// Delete light
			_fe3d.lightEntity_delete(ID);

			// Remove corresponding lightbulb model
			if (!_currentSceneID.empty())
			{
				_fe3d.modelEntity_delete("@" + ID);
			}
		}
	}

	// Delete AUDIO entities
	for (auto& ID : _loadedAudioIDs)
	{
		if (_fe3d.audioEntity_isExisting(ID))
		{
			// Delete audio
			_fe3d.audioEntity_delete(ID);

			// Remove corresponding speaker model
			if (!_currentSceneID.empty())
			{
				_fe3d.modelEntity_delete("@speaker_" + ID);
			}
		}
	}

	// Reset saved IDs
	_loadedSceneID = "";
	_loadedSkyID = "";
	_loadedTerrainID = "";
	_loadedWaterID = "";
	_loadedModelIDs.clear();
	_loadedBillboardIDs.clear();
	_loadedAudioIDs.clear();
	_loadedLightIDs.clear();
}

void SceneEditor::createCustomScene(const string& sceneID)
{
	_customSceneID = sceneID;
	_hasCustomSceneLighting = false;
	_hasCustomSceneGraphics = false;
	_hasCustomSceneSky = false;
	_hasCustomSceneTerrain = false;
	_hasCustomSceneWater = false;
	_hasCustomSceneGraphics = false;
	_customSceneModelIDs.clear();
	_customSceneBillboardIDs.clear();
	_customSceneLightIDs.clear();
	_customSceneAudioIDs.clear();
}

void SceneEditor::addLightingToCustomScene()
{
	if (!_customSceneID.empty())
	{
		_hasCustomSceneLighting = true;
	}
	else
	{
		_fe3d.logger_throwWarning("Cannot add lighting to custom scene!");
	}
}

void SceneEditor::addGraphicsToCustomScene()
{
	if (!_customSceneID.empty())
	{
		_hasCustomSceneGraphics = true;
	}
	else
	{
		_fe3d.logger_throwWarning("Cannot add graphics to custom scene!");
	}
}

void SceneEditor::addSkyToCustomScene()
{
	if (!_customSceneID.empty())
	{
		_hasCustomSceneSky = true;
	}
	else
	{
		_fe3d.logger_throwWarning("Cannot add sky to custom scene!");
	}
}

void SceneEditor::addTerrainToCustomScene()
{
	if (!_customSceneID.empty())
	{
		_hasCustomSceneTerrain = true;
	}
	else
	{
		_fe3d.logger_throwWarning("Cannot add terrain to custom scene!");
	}
}

void SceneEditor::addWaterToCustomScene()
{
	if (!_customSceneID.empty())
	{
		_hasCustomSceneWater = true;
	}
	else
	{
		_fe3d.logger_throwWarning("Cannot add water to custom scene!");
	}
}

void SceneEditor::addModelToCustomScene(const string& modelID)
{
	if (!_customSceneID.empty())
	{
		_customSceneModelIDs.push_back(modelID);
	}
	else
	{
		_fe3d.logger_throwWarning("Cannot add model to custom scene!");
	}
}

void SceneEditor::addBillboardToCustomScene(const string& billboardID)
{
	if (!_customSceneID.empty())
	{
		_customSceneBillboardIDs.push_back(billboardID);
	}
	else
	{
		_fe3d.logger_throwWarning("Cannot add billboard to custom scene!");
	}
}

void SceneEditor::addLightToCustomScene(const string& lightID)
{
	if (!_customSceneID.empty())
	{
		_customSceneLightIDs.push_back(lightID);
	}
	else
	{
		_fe3d.logger_throwWarning("Cannot add light to custom scene!");
	}
}

void SceneEditor::addAudioToCustomScene(const string& audioID)
{
	if (!_customSceneID.empty())
	{
		_customSceneAudioIDs.push_back(audioID);
	}
	else
	{
		_fe3d.logger_throwWarning("Cannot add audio to custom scene!");
	}
}