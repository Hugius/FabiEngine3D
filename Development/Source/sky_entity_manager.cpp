#include "sky_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp"

SkyEntityManager::SkyEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(EntityType::SKY, objLoader, texLoader, renderBus)
{
	
}

shared_ptr<SkyEntity> SkyEntityManager::getEntity(const string& ID)
{
	auto result = _getSkyEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("Nonexisting SKY entity with ID \"" + ID + "\" requested");
	}

	return result;
}

shared_ptr<SkyEntity> SkyEntityManager::getSelectedSky()
{
	if (_getSkyEntities().empty() || _selectedID == "")
	{
		return nullptr;
	}
	else
	{
		return getEntity(_selectedID);
	}
}

const unordered_map<string, shared_ptr<SkyEntity>>& SkyEntityManager::getEntities()
{
	return _getSkyEntities();
}

void SkyEntityManager::selectSky(const string& ID)
{
	_selectedID = ID;
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
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(BufferType::CUBEMAP, skybox_data, sizeof(skybox_data) / sizeof(float)));
}

void SkyEntityManager::update()
{
	// Check if any sky exists and if one selected
	if (getSelectedSky() != nullptr)
	{
		// Renderbus updates
		_renderBus.setSkyRotationMatrix(getSelectedSky()->getRotationMatrix());
		_renderBus.setSkyReflectionCubeMap(getSelectedSky()->getCubeMap());

		// Core updates
		_updateRotation();
		_updateEyeAdaption();
	}
}

void SkyEntityManager::_updateRotation()
{
	for (auto& [keyID, entity] : _getSkyEntities())
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
		const float speed = 0.0005f; // Lightness changing speed
		float lightness = getSelectedSky()->getLightness(); // Current lightness
		float pitch = std::min(_renderBus.getCameraPitch() + 30.0f, 90.0f); // Full conversion at 60 degrees pitch
		float targetLightness = getSelectedSky()->getOriginalLightness() + (((90.0f - pitch) / 90.0f) * _hdrBrightnessFactor);

		// Based on verticle angle
		if (lightness > targetLightness) // Decrease lightness
		{
			getSelectedSky()->setLightness(lightness - (speed * 3.5f));
		}
		else if (getSelectedSky()->getLightness() < targetLightness) // Increase lightness
		{
			getSelectedSky()->setLightness(lightness + speed);
		}
	}
	else // HDR not enabled
	{
		getSelectedSky()->setLightness(getSelectedSky()->getOriginalLightness()); // Revert lightness
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