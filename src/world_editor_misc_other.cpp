#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <algorithm>

using std::clamp;

void WorldEditor::unloadEditorWorld()
{
	if(_fe3d->gfx_isAmbientLightingEnabled())
	{
		_fe3d->gfx_disableAmbientLighting(true);
	}
	if(_fe3d->gfx_isDirectionalLightingEnabled())
	{
		_fe3d->gfx_disableDirectionalLighting(true);
	}
	if(_fe3d->gfx_isFogEnabled())
	{
		_fe3d->gfx_disableFog(true);
	}
	if(_fe3d->gfx_isShadowsEnabled())
	{
		_fe3d->gfx_disableShadows(true);
	}
	if(_fe3d->gfx_isSkyExposureEnabled())
	{
		_fe3d->gfx_disableSkyExposure(true);
	}
	if(_fe3d->gfx_isDofEnabled())
	{
		_fe3d->gfx_disableDOF(true);
	}
	if(_fe3d->gfx_isLensFlareEnabled())
	{
		_fe3d->gfx_disableLensFlare(true);
	}
	if(_fe3d->gfx_isBloomEnabled())
	{
		_fe3d->gfx_disableBloom(true);
	}
	_fe3d->gfx_setPlanarReflectionHeight(0.0f);
	_fe3d->gfx_setCubeReflectionQuality(Config::MIN_REFLECTION_QUALITY);
	_fe3d->gfx_setPlanarReflectionQuality(Config::MIN_REFLECTION_QUALITY);
	_fe3d->gfx_setPlanarRefractionQuality(Config::MIN_REFRACTION_QUALITY);
	_fe3d->gfx_setPlanarReflectionHeight(0.0);

	if(!_loadedSkyID.empty())
	{
		_fe3d->sky_delete(_loadedSkyID);
	}

	if(!_loadedTerrainID.empty())
	{
		_fe3d->terrain_delete(_loadedTerrainID);
	}

	if(!_loadedWaterID.empty())
	{
		_fe3d->water_delete(_loadedWaterID);
	}

	for(const auto& [key, templateID] : _loadedModelIDs)
	{
		_fe3d->model_delete(key);

		auto animationID = _animation3dEditor->getStartedModelAnimationIDs(key);
		if(!animationID.empty())
		{
			_animation3dEditor->stopModelAnimation(animationID.back(), key);
		}
	}

	for(const auto& [key, templateID] : _loadedQuad3dIDs)
	{
		_fe3d->quad3d_delete(key);

		auto animationID = _animation2dEditor->getStartedQuad3dAnimationIDs(key);
		if(!animationID.empty())
		{
			_animation2dEditor->stopQuad3dAnimation(animationID.back(), key);
		}
	}

	for(const auto& ID : _loadedPointlightIDs)
	{
		_fe3d->pointlight_delete(ID);

		if(!_currentWorldID.empty())
		{
			_fe3d->model_delete("@@lamp_" + ID);
		}
	}

	for(const auto& ID : _loadedSpotlightIDs)
	{
		_fe3d->spotlight_delete(ID);

		if(!_currentWorldID.empty())
		{
			_fe3d->model_delete("@@torch_" + ID);
		}
	}

	for(const auto& ID : _loadedReflectionIDs)
	{
		_fe3d->reflection_delete(ID);

		if(!_currentWorldID.empty())
		{
			_fe3d->model_delete("@@camera_" + ID);
		}
	}

	for(const auto& [key, templateID] : _loadedSoundIDs)
	{
		_fe3d->sound3d_delete(key);

		if(!_currentWorldID.empty())
		{
			_fe3d->model_delete("@@speaker_" + key);
		}
	}

	_loadedWorldID = "";
	_loadedSkyID = "";
	_loadedTerrainID = "";
	_loadedWaterID = "";
	_loadedModelIDs.clear();
	_loadedQuad3dIDs.clear();
	_loadedSoundIDs.clear();
	_loadedPointlightIDs.clear();
	_loadedSpotlightIDs.clear();
	_loadedReflectionIDs.clear();
}

void WorldEditor::unloadCustomWorld()
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
	vector<string> worldIDs;

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "worlds\\editor\\");

	if(Tools::isDirectoryExisting(directoryPath))
	{
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
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "worlds\\editor\\" + ID + ".fe3d");

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
	auto writeField = _gui->getRightViewport()->getWindow("main")->getScreen(screenID)->getWriteField(writeFieldID);

	if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_LEFT))
	{
		if(_gui->getRightViewport()->getWindow("main")->getScreen(screenID)->getButton(buttonID)->isHovered())
		{
			value += adder;
		}
	}

	if(!writeField->isActive())
	{
		writeField->changeTextContent(to_string(static_cast<int>(value * multiplier)));
	}

	if(writeField->getTextContent().empty())
	{
		value = 0.0f;
	}
	else
	{
		if(writeField->isActive())
		{
			value = (static_cast<float>(stoi(writeField->getTextContent())) / multiplier);
		}
	}

	value = clamp(value, minimum, maximum);

	if(!writeField->isActive())
	{
		writeField->changeTextContent(to_string(static_cast<int>(value * multiplier)));
	}
}

void WorldEditor::inject(shared_ptr<SkyEditor> skyEditor)
{
	_skyEditor = skyEditor;
}

void WorldEditor::inject(shared_ptr<TerrainEditor> terrainEditor)
{
	_terrainEditor = terrainEditor;
}

void WorldEditor::inject(shared_ptr<WaterEditor> waterEditor)
{
	_waterEditor = waterEditor;
}

void WorldEditor::inject(shared_ptr<ModelEditor> modelEditor)
{
	_modelEditor = modelEditor;
}

void WorldEditor::inject(shared_ptr<Quad3dEditor> quad3dEditor)
{
	_quad3dEditor = quad3dEditor;
}

void WorldEditor::inject(shared_ptr<Animation2dEditor> animation2dEditor)
{
	_animation2dEditor = animation2dEditor;
}

void WorldEditor::inject(shared_ptr<Animation3dEditor> animation3dEditor)
{
	_animation3dEditor = animation3dEditor;
}

void WorldEditor::inject(shared_ptr<SoundEditor> soundEditor)
{
	_soundEditor = soundEditor;
}