#include "sky_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp"

SkyEntityManager::SkyEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(EntityType::SKY, meshLoader, texLoader, renderBus)
{
	
}

shared_ptr<SkyEntity> SkyEntityManager::getEntity(const string& ID)
{
	auto result = _getSkyEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("Non-existing sky entity with ID \"" + ID + "\" requested");
	}

	return result;
}

shared_ptr<SkyEntity> SkyEntityManager::getSelectedMainSky()
{
	if (_getSkyEntities().empty() || _selectedMainID == "")
	{
		return nullptr;
	}
	else
	{
		return getEntity(_selectedMainID);
	}
}

shared_ptr<SkyEntity> SkyEntityManager::getSelectedMixSky()
{
	if (_getSkyEntities().empty() || _selectedMixID == "")
	{
		return nullptr;
	}
	else
	{
		return getEntity(_selectedMixID);
	}
}

const unordered_map<string, shared_ptr<SkyEntity>>& SkyEntityManager::getEntities()
{
	return _getSkyEntities();
}

void SkyEntityManager::selectMainSky(const string& ID)
{
	_selectedMainID = ID;
}

void SkyEntityManager::selectMixSky(const string& ID)
{
	_selectedMixID = ID;
}

void SkyEntityManager::addSkyEntity(const string& ID)
{
	// Skybox vertices
	float skybox_data[] =
	{
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	// Create entity
	_createEntity(ID);

	// Fill entity
	getEntity(ID)->addRenderBuffer(new RenderBuffer(BufferType::CUBEMAP, skybox_data, sizeof(skybox_data) / sizeof(float)));
}

void SkyEntityManager::update()
{
	// Check if main sky exists
	auto mainSky = getSelectedMainSky();
	if (mainSky != nullptr)
	{
		// Renderbus updates
		_renderBus.setSkyRotationMatrix(mainSky->getRotationMatrix());
		_renderBus.setMainSkyReflectionCubeMap(mainSky->getCubeMap());
		_renderBus.setMainSkyColor(mainSky->getColor());
		_renderBus.setMainSkyLightness(mainSky->getLightness());

		// Core updates
		_updateRotation();
		_updateEyeAdaption();

		// Check if mix sky exists
		auto mixSky = getSelectedMixSky();
		if (getSelectedMixSky() != nullptr)
		{
			_renderBus.setMixSkyReflectionCubeMap(getSelectedMixSky()->getCubeMap());
			_renderBus.setMixSkyColor(mixSky->getColor());
			_renderBus.setMixSkyLightness(mixSky->getLightness());
		}
	}
}

void SkyEntityManager::_updateRotation()
{
	for (const auto& [keyID, entity] : _getSkyEntities())
	{
		if (entity->isVisible())
		{
			entity->updateRotationMatrix();
		}
	}
}

void SkyEntityManager::_updateEyeAdaption()
{
	// Update sky HDR
	if (_renderBus.isSkyHdrEnabled())
	{
		// Values
		const float speed = 0.001f; // Lightness changing speed
		float lightness = getSelectedMainSky()->getLightness(); // Current lightness
		float pitch = std::min(_renderBus.getCameraPitch() + 30.0f, 90.0f); // Full conversion at 60 degrees pitch
		float targetLightness = getSelectedMainSky()->getOriginalLightness() + (((90.0f - pitch) / 90.0f) * _hdrBrightnessFactor);

		// Based on verticle angle
		if (lightness > targetLightness) // Decrease lightness
		{
			getSelectedMainSky()->setLightness(lightness - (speed * 3.5f));
		}
		else if (getSelectedMainSky()->getLightness() < targetLightness) // Increase lightness
		{
			getSelectedMainSky()->setLightness(lightness + speed);
		}
	}
	else // HDR not enabled
	{
		getSelectedMainSky()->setLightness(getSelectedMainSky()->getOriginalLightness()); // Revert lightness
	}
}

void SkyEntityManager::setBrightnessFactor(float brightnessFactor)
{
	_hdrBrightnessFactor = brightnessFactor;
}

float SkyEntityManager::getBrightnessFactor()
{
	return _hdrBrightnessFactor;
}