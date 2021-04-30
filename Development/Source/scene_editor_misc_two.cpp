#include "scene_editor.hpp"

#include <algorithm>
#include <filesystem>

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

void SceneEditor::copyPreviewModel(const string& newID, const string& previewID, Vec3 position)
{
	_copyPreviewModel(newID, previewID, position, true);
}

void SceneEditor::copyPreviewBillboard(const string& newID, const string& previewID, Vec3 position)
{
	_copyPreviewBillboard(newID, previewID, position, true);
}

void SceneEditor::copyPreviewAudio(const string& newID, const string& previewID, Vec3 position)
{
	_copyPreviewAudio(newID, previewID, position, true);
}

void SceneEditor::clearCurrentScene()
{
	// Disable scene graphics
	if (_isEditorLoaded)
	{
		_fe3d.gfx_disableAmbientLighting(true);
		_fe3d.gfx_disableDirectionalLighting(true);
		_fe3d.gfx_disableFog(true);
		_fe3d.gfx_disableShadows(true);
		_fe3d.gfx_disableSkyHDR(true);
		_fe3d.gfx_disableDOF(true);
		_fe3d.gfx_disableMotionBlur(true);
		_fe3d.gfx_disableLensFlare(true);
	}

	// Delete sky entity
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

	// Delete terrain entity
	if (!_loadedTerrainID.empty())
	{
		// Delete terrain
		if (_fe3d.terrainEntity_isExisting(_loadedTerrainID))
		{
			_fe3d.terrainEntity_delete(_loadedTerrainID);
		}
	}

	// Delete water entity
	if (!_loadedWaterID.empty())
	{
		// Delete water
		if (_fe3d.waterEntity_isExisting(_loadedWaterID))
		{
			_fe3d.waterEntity_delete(_loadedWaterID);
		}
	}

	// Delete GAME entities
	for (const auto& [ID, previewID] : _loadedModelIDs)
	{
		// Delete model
		if (_fe3d.modelEntity_isExisting(ID))
		{
			_fe3d.modelEntity_delete(ID);
		}

		// Stop animation
		auto animationID = _animationEditor.getStartedAnimationIDs(ID);
		if (!animationID.empty())
		{
			_animationEditor.stopAnimation(animationID.back(), ID);
		}
	}

	// Delete billboard entities
	for (const auto& [ID, previewID] : _loadedBillboardIDs)
	{
		// Delete billboard
		if (_fe3d.billboardEntity_isExisting(ID))
		{
			_fe3d.billboardEntity_delete(ID);
		}
	}

	// Delete AABB entities
	for (const auto& ID : _loadedAabbIDs)
	{
		// Delete AABB
		if (_fe3d.aabbEntity_isExisting(ID))
		{
			_fe3d.aabbEntity_delete(ID);
		}
	}

	// Delete sounds
	for (const auto& [ID, previewID] : _loadedSoundIDs)
	{
		if (_fe3d.soundEntity_isExisting(ID))
		{
			// Delete sound
			_fe3d.soundEntity_delete(ID);

			// Delete corresponding speaker model
			if (!_currentSceneID.empty())
			{
				_fe3d.modelEntity_delete("@speaker_" + ID);
			}
		}
	}

	// Hide lightsource billboard
	if (_fe3d.billboardEntity_isExisting("@@lightSource"))
	{
		_fe3d.billboardEntity_hide("@@lightSource");
	}

	// Delete light entities
	for (const auto& ID : _loadedLightIDs)
	{
		if (_fe3d.lightEntity_isExisting(ID))
		{
			// Delete light
			_fe3d.lightEntity_delete(ID);

			// Delete corresponding lightbulb model
			if (!_currentSceneID.empty())
			{
				_fe3d.modelEntity_delete("@" + ID);
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
	_loadedSoundIDs.clear();
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
	_customSceneAabbIDs.clear();
	_customSceneSoundIDs.clear();
	_customSceneLightIDs.clear();
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

void SceneEditor::addAabbToCustomScene(const string& aabbID)
{
	if (!_customSceneID.empty())
	{
		_customSceneAabbIDs.push_back(aabbID);
	}
	else
	{
		_fe3d.logger_throwWarning("Cannot add AABB to custom scene!");
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

void SceneEditor::addSoundToCustomScene(const string& soundID)
{
	if (!_customSceneID.empty())
	{
		_customSceneSoundIDs.push_back(soundID);
	}
	else
	{
		_fe3d.logger_throwWarning("Cannot add sound to custom scene!");
	}
}