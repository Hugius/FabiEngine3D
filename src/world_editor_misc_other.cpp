#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <algorithm>

using std::clamp;

void WorldEditor::_updateMiscellaneous()
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

		// Update wireframe rendering
		if(_fe3d.input_isKeyPressed(InputType::KEY_F))
		{
			if(_fe3d.misc_isWireframeRenderingEnabled())
			{
				_fe3d.misc_disableWireframeRendering();
			}
			else
			{
				_fe3d.misc_enableWireframeRendering();
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
	if(!_fe3d.terrain_getSelectedID().empty())
	{
		_fe3d.raycast_enableTerrainPointing(_fe3d.terrain_getSize(_fe3d.terrain_getSelectedID()), 0.1f);
	}
}

void WorldEditor::copyPreviewModel(const string& newID, const string& previewID, fvec3 position)
{
	_copyPreviewModel(newID, previewID, position, true);
}

void WorldEditor::copyPreviewBillboard(const string& newID, const string& previewID, fvec3 position)
{
	_copyPreviewBillboard(newID, previewID, position, true);
}

void WorldEditor::copyPreviewSound(const string& newID, const string& previewID, fvec3 position)
{
	_copyPreviewSound(newID, previewID, position, true);
}

void WorldEditor::clearCurrentWorld()
{
	// Disable world graphics
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
		if(_fe3d.gfx_isLensFlareEnabled())
		{
			_fe3d.gfx_disableLensFlare(true);
		}
		if(_fe3d.gfx_isBloomEnabled())
		{
			_fe3d.gfx_disableBloom(true);
		}
	}

	// Reset sky
	_fe3d.sky_selectMixSky("");
	_fe3d.sky_setMixValue(0.0f);

	// Delete sky entity
	if(!_loadedSkyID.empty())
	{
		// Delete sky
		if(_fe3d.sky_isExisting(_loadedSkyID))
		{
			_fe3d.sky_delete(_loadedSkyID);
		}
	}

	// Delete terrain entity
	if(!_loadedTerrainID.empty())
	{
		// Delete terrain
		if(_fe3d.terrain_isExisting(_loadedTerrainID))
		{
			_fe3d.terrain_delete(_loadedTerrainID);
		}
	}

	// Delete water entity
	if(!_loadedWaterID.empty())
	{
		// Delete water
		if(_fe3d.water_isExisting(_loadedWaterID))
		{
			_fe3d.water_delete(_loadedWaterID);
		}
	}

	// Delete model entities
	for(const auto& [ID, previewID] : _loadedModelIDs)
	{
		// Delete model
		if(_fe3d.model_isExisting(ID))
		{
			_fe3d.model_delete(ID);
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
		if(_fe3d.billboard_isExisting(ID))
		{
			_fe3d.billboard_delete(ID);
		}
	}

	// Delete AABB entities
	for(const auto& ID : _loadedAabbIDs)
	{
		// Delete AABB
		if(_fe3d.aabb_isExisting(ID))
		{
			_fe3d.aabb_delete(ID);
		}
	}

	// Delete sounds
	for(const auto& [ID, previewID] : _loadedSoundIDs)
	{
		if(_fe3d.sound3D_isExisting(ID))
		{
			// Delete sound
			_fe3d.sound3D_delete(ID);

			// Delete corresponding speaker model
			if(!_currentWorldID.empty())
			{
				_fe3d.model_delete("@@speaker_" + ID);
			}
		}
	}

	// Delete pointlight entities
	for(const auto& ID : _loadedPointlightIDs)
	{
		if(_fe3d.pointlight_isExisting(ID))
		{
			// Delete pointlight
			_fe3d.pointlight_delete(ID);

			// Delete corresponding lamp model
			if(!_currentWorldID.empty())
			{
				_fe3d.model_delete("@@lamp_" + ID);
			}
		}
	}

	// Delete spotlight entities
	for(const auto& ID : _loadedSpotlightIDs)
	{
		if(_fe3d.spotlight_isExisting(ID))
		{
			// Delete spotlight
			_fe3d.spotlight_delete(ID);

			// Delete corresponding torch model
			if(!_currentWorldID.empty())
			{
				_fe3d.model_delete("@@torch_" + ID);
			}
		}
	}

	// Delete reflection entities
	for(const auto& ID : _loadedReflectionIDs)
	{
		if(_fe3d.reflection_isExisting(ID))
		{
			// Delete reflection
			_fe3d.reflection_delete(ID);

			// Delete corresponding camera model
			if(!_currentWorldID.empty())
			{
				_fe3d.model_delete("@@camera_" + ID);
			}
		}
	}

	// Reset saved IDs
	_loadedWorldID = "";
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


const bool WorldEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const bool WorldEditor::isWorldExisting(const string& fileName) const
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("WorldEditor::isWorldExisting");
	}

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "worlds\\editor\\" + fileName + ".fe3d");

	// Check if world file exists
	return Tools::isFileExisting(filePath);
}

const string& WorldEditor::getLoadedWorldID() const
{
	return _loadedWorldID;
}

void WorldEditor::setCurrentProjectID(const string& ID)
{
	_currentProjectID = ID;
}

const vector<string> WorldEditor::_getWorldIDs() const
{
	// Temporary values
	vector<string> worldIDs;

	// Compose directory path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "worlds\\editor\\");

	// Check if worlds directory exists
	if(Tools::isDirectoryExisting(directoryPath))
	{
		// Get all world IDs
		for(const auto& fileName : Tools::getFilesFromDirectory(directoryPath))
		{
			auto nameSize = (fileName.size() - string(".fe3d").size());
			worldIDs.push_back(fileName.substr(0, nameSize));
		}
	}
	else
	{
		Logger::throwWarning("Project corrupted: directory `worlds\\editor\\` missing!");
	}

	return worldIDs;
}

void WorldEditor::_deleteWorldFile(const string& ID)
{
	// Compose full file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "worlds\\editor\\" + ID + ".fe3d");

	// Check if world file is still existing
	if(Tools::isFileExisting(filePath))
	{
		Tools::deleteFile(filePath);
	}
	else
	{
		Logger::throwWarning("Cannot delete world with ID \"" + ID + "\"!");
	}
}

void WorldEditor::_handleValueChanging(const string& screenID, string buttonID, string writeFieldID, float& value, float adder,
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