#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <algorithm>

using std::clamp;

void WorldEditor::clearLoadedWorld()
{
	if(_loadedWorldId.empty())
	{
		abort();
	}

	_fe3d->graphics_setAmbientLightingEnabled(false);
	_fe3d->graphics_setDirectionalLightingEnabled(false);
	_fe3d->graphics_setFogEnabled(false);
	_fe3d->graphics_setShadowsEnabled(false);
	_fe3d->graphics_setSkyExposureEnabled(false);
	_fe3d->graphics_setDofEnabled(false);
	_fe3d->graphics_setLensFlareEnabled(false);
	_fe3d->graphics_setBloomEnabled(false);
	_fe3d->graphics_setAmbientLightingColor(fvec3(0.0f));
	_fe3d->graphics_setAmbientLightingIntensity(0.0f);
	_fe3d->graphics_setDirectionalLightingPosition(fvec3(0.0f));
	_fe3d->graphics_setDirectionalLightingColor(fvec3(0.0f));
	_fe3d->graphics_setDirectionalLightingIntensity(0.0f);
	_fe3d->graphics_setFogColor(fvec3(0.0f));
	_fe3d->graphics_setFogThickness(0.0f);
	_fe3d->graphics_setFogMinDistance(0.0f);
	_fe3d->graphics_setFogMaxDistance(0.0f);
	_fe3d->graphics_setShadowCircleEnabled(false);
	_fe3d->graphics_setShadowPositionOffset(fvec3(0.0f));
	_fe3d->graphics_setShadowLookatOffset(fvec3(0.0f));
	_fe3d->graphics_setShadowSize(0.0f);
	_fe3d->graphics_setShadowLightness(0.0f);
	_fe3d->graphics_setShadowQuality(0);
	_fe3d->graphics_setShadowInterval(0);
	_fe3d->graphics_setShadowFollowingCameraX(false);
	_fe3d->graphics_setShadowFollowingCameraY(false);
	_fe3d->graphics_setShadowFollowingCameraZ(false);
	_fe3d->graphics_setBloomIntensity(0.0f);
	_fe3d->graphics_setBloomBlurCount(0);
	_fe3d->graphics_setBloomType(BloomType::EVERYTHING);
	_fe3d->graphics_setBloomQuality(0);
	_fe3d->graphics_setSkyExposureIntensity(0.0f);
	_fe3d->graphics_setSkyExposureSpeed(0.0f);
	_fe3d->graphics_setDofDynamicDistance(0.0f);
	_fe3d->graphics_setDofBlurDistance(0.0f);
	_fe3d->graphics_setDofDynamic(false);
	_fe3d->graphics_setDofQuality(0);
	_fe3d->graphics_setLensFlareMap("");
	_fe3d->graphics_setLensFlareIntensity(0.0f);
	_fe3d->graphics_setLensFlareSensitivity(0.0f);
	_fe3d->graphics_setCubeReflectionQuality(0);
	_fe3d->graphics_setPlanarReflectionQuality(0);
	_fe3d->graphics_setPlanarRefractionQuality(0);
	_fe3d->graphics_setPlanarReflectionHeight(0.0f);

	if(!_fe3d->sky_getSelectedId().empty())
	{
		_fe3d->sky_delete(_fe3d->sky_getSelectedId());
	}

	if(!_fe3d->terrain_getSelectedId().empty())
	{
		_fe3d->terrain_delete(_fe3d->terrain_getSelectedId());
	}

	if(!_fe3d->water_getSelectedId().empty())
	{
		_fe3d->water_delete(_fe3d->water_getSelectedId());
	}

	for(const auto & [placedModelId, templateModelId] : _loadedModelIds)
	{
		_fe3d->model_delete(placedModelId);
	}

	for(const auto & [placedQuad3dId, templateQuad3d] : _loadedQuad3dIds)
	{
		_fe3d->quad3d_delete(placedQuad3dId);
	}

	for(const auto & [placedText3dId, templateText3dId] : _loadedText3dIds)
	{
		_fe3d->text3d_delete(placedText3dId);
	}

	for(const auto & pointlightId : _loadedPointlightIds)
	{
		_fe3d->pointlight_delete(pointlightId);

		if(isLoaded())
		{
			_fe3d->model_delete("@@pointlight_" + pointlightId);
		}
	}

	for(const auto & spotlightId : _loadedSpotlightIds)
	{
		_fe3d->spotlight_delete(spotlightId);

		if(isLoaded())
		{
			_fe3d->model_delete("@@spotlight_" + spotlightId);
		}
	}

	for(const auto & captorId : _loadedCaptorIds)
	{
		_fe3d->captor_delete(captorId);

		if(isLoaded())
		{
			_fe3d->model_delete("@@captor_" + captorId);
		}
	}

	for(const auto & [placedSound3dId, templateSound3dId] : _loadedSound3dIds)
	{
		_fe3d->sound3d_delete(placedSound3dId);

		if(isLoaded())
		{
			_fe3d->model_delete("@@sound3d_" + placedSound3dId);
		}
	}

	_loadedModelIds.clear();
	_loadedQuad3dIds.clear();
	_loadedText3dIds.clear();
	_loadedPointlightIds.clear();
	_loadedSpotlightIds.clear();
	_loadedCaptorIds.clear();
	_loadedSound3dIds.clear();
	_loadedWorldId = "";
	_idCounter = 0;
}

const string & WorldEditor::getLoadedWorldId() const
{
	return _loadedWorldId;
}

const vector<string> WorldEditor::_getWorldIds() const
{
	vector<string> worldIds;

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "worlds\\editor\\");

	if(Tools::isDirectoryExisting(directoryPath))
	{
		for(const auto & fileName : Tools::getFileNamesFromDirectory(directoryPath))
		{
			auto nameSize = (fileName.size() - string(".fe3d").size());
			worldIds.push_back(fileName.substr(0, nameSize));
		}
	}
	else
	{
		Logger::throwWarning("Project corrupted: directory `worlds\\editor\\` does not exist");
	}

	return worldIds;
}

void WorldEditor::_deleteWorldFile(const string & worldId)
{
	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "worlds\\editor\\" + worldId + ".fe3d");

	Tools::deleteFile(filePath);
}

void WorldEditor::_handleInputBox(const string & screenId, const string & leftButtonId, const string & inputBoxId, const string & rightButtonId, float & value, float delta, float multiplier, float minimum, float maximum)
{
	const auto inputBox = _gui->getRightViewport()->getWindow("main")->getScreen(screenId)->getInputBox(inputBoxId);

	if(inputBox->isHovered())
	{
		if(inputBox->getTextContent().empty() || (inputBox->getTextContent() == "-"))
		{
			value = 0.0f;
		}
		else
		{
			const auto content = static_cast<float>(Tools::parseInteger(inputBox->getTextContent()));

			value = clamp((content / multiplier), minimum, maximum);

			inputBox->setTextContent(to_string(static_cast<int>(value * multiplier)));
		}
	}
	else
	{
		if(_gui->getRightViewport()->getWindow("main")->getScreen(screenId)->getButton(leftButtonId)->isHovered() && _fe3d->input_isMouseHeld(MouseButtonType::BUTTON_LEFT))
		{
			value = clamp((value - delta), minimum, maximum);
		}
		if(_gui->getRightViewport()->getWindow("main")->getScreen(screenId)->getButton(rightButtonId)->isHovered() && _fe3d->input_isMouseHeld(MouseButtonType::BUTTON_LEFT))
		{
			value = clamp((value + delta), minimum, maximum);
		}

		inputBox->setTextContent(to_string(static_cast<int>(value * multiplier)));
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

void WorldEditor::inject(shared_ptr<Sound2dEditor> sound2dEditor)
{
	_sound2dEditor = sound2dEditor;
}

void WorldEditor::inject(shared_ptr<AabbEditor> aabbEditor)
{
	_aabbEditor = aabbEditor;
}

void WorldEditor::inject(shared_ptr<WorldHelper> worldHelper)
{
	_worldHelper = worldHelper;
}