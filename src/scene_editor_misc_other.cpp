#include "scene_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <algorithm>

using std::clamp;

void SceneEditor::_updateMiscellaneous()
{
	// Check if allowed by GUI
	if(!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Update AABB frame rendering
		if(_fe3d.input_isKeyPressed(InputType::KEY_B))
		{
			if(_fe3d.misc_isAabbFrameRenderingEnabled())
			{
				_fe3d.misc_disableAabbFrameRendering();
			}
			else
			{
				_fe3d.misc_enableAabbFrameRendering();
			}

		}

		// Update wire frame rendering
		if(_fe3d.input_isKeyPressed(InputType::KEY_F))
		{
			if(_fe3d.misc_isWireFrameRenderingEnabled())
			{
				_fe3d.misc_disableWireFrameRendering();
			}
			else
			{
				_fe3d.misc_enableWireFrameRendering();
			}
		}

		// Update debug rendering
		if(_fe3d.input_isKeyPressed(InputType::KEY_H))
		{
			if(_fe3d.misc_isDebugRenderingEnabled())
			{
				_fe3d.misc_disableDebugRendering();
			}
			else
			{
				_fe3d.misc_enableDebugRendering();
			}
		}
	}

	// Disable terrain raycast pointing
	if(_fe3d.raycast_isTerrainPointingEnabled())
	{
		_fe3d.raycast_disableTerrainPointing();
	}

	// Enable terrain raycast pointing
	if(!_fe3d.terrainEntity_getSelectedID().empty())
	{
		_fe3d.raycast_enableTerrainPointing(_fe3d.terrainEntity_getSize(_fe3d.terrainEntity_getSelectedID()), 0.1f);
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

void SceneEditor::copyPreviewSound(const string& newID, const string& previewID, Vec3 position)
{
	_copyPreviewSound(newID, previewID, position, true);
}

void SceneEditor::clearCurrentScene()
{
	// Disable scene graphics
	if(_isEditorLoaded)
	{
		if(_fe3d.gfx_isAmbientLightingEnabled())
		{
			_fe3d.gfx_disableAmbientLighting(true);
		}
		if(_fe3d.gfx_isDirectionalLightingEnabled())
		{
			_fe3d.gfx_disableDirectionalLighting(true);
		}
		if(_fe3d.gfx_isFogEnabled())
		{
			_fe3d.gfx_disableFog(true);
		}
		if(_fe3d.gfx_isShadowsEnabled())
		{
			_fe3d.gfx_disableShadows(true);
		}
		if(_fe3d.gfx_isSkyExposureEnabled())
		{
			_fe3d.gfx_disableSkyExposure(true);
		}
		if(_fe3d.gfx_isDofEnabled())
		{
			_fe3d.gfx_disableDOF(true);
		}
		if(_fe3d.gfx_isMotionBlurEnabled())
		{
			_fe3d.gfx_disableMotionBlur(true);
		}
		if(_fe3d.gfx_isLensFlareEnabled())
		{
			_fe3d.gfx_disableLensFlare(true);
		}
		if(_fe3d.gfx_isBloomEnabled())
		{
			_fe3d.gfx_disableBloom(true);
		}
	}

	// Delete sky entity
	if(!_loadedSkyID.empty())
	{
		// Delete sky
		if(_fe3d.skyEntity_isExisting(_loadedSkyID))
		{
			_fe3d.skyEntity_delete(_loadedSkyID);
		}

		// Miscellaneous
		_fe3d.skyEntity_selectMixSky("");
		_fe3d.skyEntity_setMixValue(0.0f);
	}

	// Delete terrain entity
	if(!_loadedTerrainID.empty())
	{
		// Delete terrain
		if(_fe3d.terrainEntity_isExisting(_loadedTerrainID))
		{
			_fe3d.terrainEntity_delete(_loadedTerrainID);
		}
	}

	// Delete water entity
	if(!_loadedWaterID.empty())
	{
		// Delete water
		if(_fe3d.waterEntity_isExisting(_loadedWaterID))
		{
			_fe3d.waterEntity_delete(_loadedWaterID);
		}
	}

	// Delete model entities
	for(const auto& [ID, previewID] : _loadedModelIDs)
	{
		// Delete model
		if(_fe3d.modelEntity_isExisting(ID))
		{
			_fe3d.modelEntity_delete(ID);
		}

		// Stop animation
		auto animationID = _animationEditor.getStartedAnimationIDs(ID);
		if(!animationID.empty())
		{
			_animationEditor.stopAnimation(animationID.back(), ID);
		}
	}

	// Delete billboard entities
	for(const auto& [ID, previewID] : _loadedBillboardIDs)
	{
		// Delete billboard
		if(_fe3d.billboardEntity_isExisting(ID))
		{
			_fe3d.billboardEntity_delete(ID);
		}
	}

	// Hide lightsource billboard
	if(_fe3d.billboardEntity_isExisting("@@lightSource"))
	{
		_fe3d.billboardEntity_setVisible("@@lightSource", false);
	}

	// Delete AABB entities
	for(const auto& ID : _loadedAabbIDs)
	{
		// Delete AABB
		if(_fe3d.aabbEntity_isExisting(ID))
		{
			_fe3d.aabbEntity_delete(ID);
		}
	}

	// Delete sounds
	for(const auto& [ID, previewID] : _loadedSoundIDs)
	{
		if(_fe3d.sound_isExisting(ID))
		{
			// Delete sound
			_fe3d.sound_delete(ID);

			// Delete corresponding speaker model
			if(!_currentSceneID.empty())
			{
				_fe3d.modelEntity_delete("@@speaker_" + ID);
			}
		}
	}

	// Delete pointlight entities
	for(const auto& ID : _loadedPointlightIDs)
	{
		if(_fe3d.pointlightEntity_isExisting(ID))
		{
			// Delete pointlight
			_fe3d.pointlightEntity_delete(ID);

			// Delete corresponding lamp model
			if(!_currentSceneID.empty())
			{
				_fe3d.modelEntity_delete("@@lamp_" + ID);
			}
		}
	}

	// Delete spotlight entities
	for(const auto& ID : _loadedSpotlightIDs)
	{
		if(_fe3d.spotlightEntity_isExisting(ID))
		{
			// Delete spotlight
			_fe3d.spotlightEntity_delete(ID);

			// Delete corresponding torch model
			if(!_currentSceneID.empty())
			{
				_fe3d.modelEntity_delete("@@torch_" + ID);
			}
		}
	}

	// Delete reflection entities
	for(const auto& ID : _loadedReflectionIDs)
	{
		if(_fe3d.reflectionEntity_isExisting(ID))
		{
			// Delete reflection
			_fe3d.reflectionEntity_delete(ID);

			// Delete corresponding camera model
			if(!_currentSceneID.empty())
			{
				_fe3d.modelEntity_delete("@@camera_" + ID);
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
	_loadedPointlightIDs.clear();
	_loadedSpotlightIDs.clear();
	_loadedReflectionIDs.clear();
}


const bool SceneEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const bool SceneEditor::isSceneExisting(const string& fileName) const
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("SceneEditor::isSceneExisting");
	}

	// Compose full file path
	string filePath = Tools::getRootDirectoryPath() + (Config::getInst().isApplicationExported() ? "" :
												   ("game\\" + _currentProjectID)) + "\\scenes\\editor\\" + fileName + ".fe3d";

	// Check if scene file exists
	return (Tools::isFileExisting(filePath));
}

const string& SceneEditor::getLoadedSceneID() const
{
	return _loadedSceneID;
}

void SceneEditor::setCurrentProjectID(const string& ID)
{
	_currentProjectID = ID;
}


const vector<string> SceneEditor::_getSceneIDs() const
{
	// Temporary values
	vector<string> sceneIDs;
	string directoryPath = (Tools::getRootDirectoryPath() + (Config::getInst().isApplicationExported() ? "" :
							("game\\" + _currentProjectID)) + "\\scenes\\editor\\");

	// Check if scenes directory exists
	if(Tools::isDirectoryExisting(directoryPath))
	{
		// Get all scene IDs
		for(const auto& fileName : Tools::getFilesFromDirectory(directoryPath))
		{
			auto nameSize = (fileName.size() - string(".fe3d").size());
			sceneIDs.push_back(fileName.substr(0, nameSize));
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
	string filePath = Tools::getRootDirectoryPath() + (Config::getInst().isApplicationExported() ? "" :
												   ("game\\" + _currentProjectID)) + "\\scenes\\editor\\" + ID + ".fe3d";

	// Check if scene file is still existing
	if(Tools::isFileExisting(filePath))
	{
		Tools::deleteFile(filePath);
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
	if(_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_LEFT))
	{
		if(_gui.getViewport("right")->getWindow("main")->getScreen(screenID)->getButton(buttonID)->isHovered())
		{
			value += adder;
		}
	}

	// WriteField pre-update
	if(!writeField->isActive())
	{
		writeField->changeTextContent(to_string(static_cast<int>(value * multiplier)));
	}

	// WriteField handling
	if(writeField->getTextContent().empty())
	{
		value = 0.0f; // Reset value to default
	}
	else
	{
		// Check if something is filled in
		if(writeField->isActive())
		{
			value = (static_cast<float>(stoi(writeField->getTextContent())) / multiplier); // Update value in realtime
		}
	}

	// Clamp value range
	value = clamp(value, minimum, maximum);

	// WriteField post-update
	if(!writeField->isActive())
	{
		writeField->changeTextContent(to_string(static_cast<int>(value * multiplier)));
	}
}