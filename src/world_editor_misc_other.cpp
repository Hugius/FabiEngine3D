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

	if(!_loadedSkyId.empty())
	{
		_fe3d->sky_delete(_loadedSkyId);
	}

	if(!_loadedTerrainId.empty())
	{
		_fe3d->terrain_delete(_loadedTerrainId);
	}

	if(!_loadedWaterId.empty())
	{
		_fe3d->water_delete(_loadedWaterId);
	}

	for(const auto& [key, templateId] : _loadedModelIds)
	{
		_fe3d->model_delete(key);

		auto animationId = _animation3dEditor->getStartedModelAnimationIds(key);
		if(!animationId.empty())
		{
			_animation3dEditor->stopModelAnimation(animationId.back(), key);
		}
	}

	for(const auto& [key, templateId] : _loadedQuadIds)
	{
		_fe3d->quad3d_delete(key);

		auto animationId = _animation2dEditor->getStartedQuad3dAnimationIds(key);
		if(!animationId.empty())
		{
			_animation2dEditor->stopQuad3dAnimation(animationId.back(), key);
		}
	}

	for(const auto& [key, templateId] : _loadedTextIds)
	{
		_fe3d->text3d_delete(key);
	}

	for(const auto& id : _loadedPointlightIds)
	{
		_fe3d->pointlight_delete(id);

		if(!_currentWorldId.empty())
		{
			_fe3d->model_delete("@@lamp_" + id);
		}
	}

	for(const auto& id : _loadedSpotlightIds)
	{
		_fe3d->spotlight_delete(id);

		if(!_currentWorldId.empty())
		{
			_fe3d->model_delete("@@torch_" + id);
		}
	}

	for(const auto& id : _loadedReflectionIds)
	{
		_fe3d->reflection_delete(id);

		if(!_currentWorldId.empty())
		{
			_fe3d->model_delete("@@camera_" + id);
		}
	}

	for(const auto& [key, templateId] : _loadedSoundIds)
	{
		_fe3d->sound3d_delete(key);

		if(!_currentWorldId.empty())
		{
			_fe3d->model_delete("@@speaker_" + key);
		}
	}

	_loadedWorldId = "";
	_loadedSkyId = "";
	_loadedTerrainId = "";
	_loadedWaterId = "";
	_loadedModelIds.clear();
	_loadedQuadIds.clear();
	_loadedSoundIds.clear();
	_loadedPointlightIds.clear();
	_loadedSpotlightIds.clear();
	_loadedReflectionIds.clear();
}

void WorldEditor::unloadCustomWorld()
{

}

const bool WorldEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const string& WorldEditor::getLoadedWorldId() const
{
	return _loadedWorldId;
}

void WorldEditor::setCurrentProjectId(const string& id)
{
	_currentProjectId = id;
}

const vector<string> WorldEditor::_getWorldIds() const
{
	vector<string> worldIds;

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "worlds\\editor\\");

	if(Tools::isDirectoryExisting(directoryPath))
	{
		for(const auto& fileName : Tools::getFilesFromDirectory(directoryPath))
		{
			auto nameSize = (fileName.size() - string(".fe3d").size());
			worldIds.push_back(fileName.substr(0, nameSize));
		}
	}
	else
	{
		Logger::throwWarning("Project corrupted: directory `worlds\\editor\\` missing!");
	}

	return worldIds;
}

void WorldEditor::_deleteWorldFile(const string& id)
{
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "worlds\\editor\\" + id + ".fe3d");

	if(Tools::isFileExisting(filePath))
	{
		Tools::deleteFile(filePath);
	}
	else
	{
		Logger::throwWarning("Cannot delete world with id \"" + id + "\"!");
	}
}

void WorldEditor::_handleValueChanging(const string& screenId, const string& buttonId, const string& writeFieldId, float& value, float adder, float multiplier, float minimum, float maximum)
{
	auto writeField = _gui->getRightViewport()->getWindow("main")->getScreen(screenId)->getWriteField(writeFieldId);

	if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_LEFT))
	{
		if(_gui->getRightViewport()->getWindow("main")->getScreen(screenId)->getButton(buttonId)->isHovered())
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

void WorldEditor::inject(shared_ptr<Text3dEditor> text3dEditor)
{
	_text3dEditor = text3dEditor;
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