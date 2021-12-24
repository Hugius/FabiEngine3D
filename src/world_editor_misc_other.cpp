#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <algorithm>

using std::clamp;

void WorldEditor::clearEditorWorld()
{
	// Graphics
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
	_fe3d.gfx_setPlanarReflectionHeight(0.0f);
	_fe3d.gfx_setCubeReflectionQuality(Config::MIN_REFLECTION_QUALITY);
	_fe3d.gfx_setPlanarReflectionQuality(Config::MIN_REFLECTION_QUALITY);
	_fe3d.gfx_setPlanarRefractionQuality(Config::MIN_REFRACTION_QUALITY);
	_fe3d.gfx_setPlanarReflectionHeight(0.0);

	// Sky entity
	if(!_loadedSkyID.empty())
	{
		_fe3d.sky_delete(_loadedSkyID);
	}

	// Terrain entity
	if(!_loadedTerrainID.empty())
	{
		_fe3d.terrain_delete(_loadedTerrainID);
	}

	// Water entity
	if(!_loadedWaterID.empty())
	{
		_fe3d.water_delete(_loadedWaterID);
	}

	// Model entities
	for(const auto& [ID, templateID] : _loadedModelIDs)
	{
		// Delete model
		_fe3d.model_delete(ID);

		// Stop animation
		auto animationID = _animation3dEditor.getStartedModelAnimationIDs(ID);
		if(!animationID.empty())
		{
			_animation3dEditor.stopModelAnimation(animationID.back(), ID);
		}
	}

	// Billboard entities
	for(const auto& [ID, templateID] : _loadedBillboardIDs)
	{
		// Delete billboard
		_fe3d.billboard_delete(ID);

		// Stop animation
		auto animationID = _animation2dEditor.getStartedBillboardAnimationIDs(ID);
		if(!animationID.empty())
		{
			_animation2dEditor.stopBillboardAnimation(animationID.back(), ID);
		}
	}

	// Pointlight entities
	for(const auto& ID : _loadedPointlightIDs)
	{
		// Delete pointlight
		_fe3d.pointlight_delete(ID);

		// Delete corresponding lamp model
		if(!_currentWorldID.empty())
		{
			_fe3d.model_delete("@@lamp_" + ID);
		}
	}

	// Spotlight entities
	for(const auto& ID : _loadedSpotlightIDs)
	{
		// Delete spotlight
		_fe3d.spotlight_delete(ID);

		// Delete corresponding torch model
		if(!_currentWorldID.empty())
		{
			_fe3d.model_delete("@@torch_" + ID);
		}
	}

	// Reflection entities
	for(const auto& ID : _loadedReflectionIDs)
	{
		// Delete reflection
		_fe3d.reflection_delete(ID);

		// Delete corresponding camera model
		if(!_currentWorldID.empty())
		{
			_fe3d.model_delete("@@camera_" + ID);
		}
	}

	// Sounds
	for(const auto& [ID, templateID] : _loadedSoundIDs)
	{
		// Delete sound
		_fe3d.sound3d_delete(ID);

		// Delete corresponding speaker model
		if(!_currentWorldID.empty())
		{
			_fe3d.model_delete("@@speaker_" + ID);
		}
	}

	// Miscellaneous
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

void WorldEditor::clearCustomWorld()
{

}

const bool WorldEditor::isLoaded() const
{
	return _isEditorLoaded;
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