#include "sky_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp"

using std::make_shared;
using std::min;

const float bufferData[] =
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

SkyEntityManager::SkyEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus)
	:
	BaseEntityManager(EntityType::SKY, meshLoader, texLoader, renderBus),
	_renderBuffer(make_shared<RenderBuffer>(RenderBufferType::VERTEX, bufferData, static_cast<unsigned int>(sizeof(bufferData) / sizeof(float))))
{

}

shared_ptr<SkyEntity> SkyEntityManager::getEntity(const string& ID)
{
	auto result = _getSkyEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("SkyEntityManager::getEntity");
	}

	return result;
}

shared_ptr<SkyEntity> SkyEntityManager::getSelectedMainSky()
{
	if (_getSkyEntities().empty() || _selectedMainID.empty())
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
	if (_getSkyEntities().empty() || _selectedMixID.empty())
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
	if (isExisting(ID) || ID.empty())
	{
		_selectedMainID = ID;
	}
	else
	{
		Logger::throwError("SkyEntityManager::selectMainSky");
	}
}

void SkyEntityManager::selectMixSky(const string& ID)
{
	if (isExisting(ID) || ID.empty())
	{
		_selectedMixID = ID;
	}
	else
	{
		Logger::throwError("SkyEntityManager::selectMixSky");
	}
}

void SkyEntityManager::createEntity(const string& ID)
{
	_createEntity(ID);
	getEntity(ID)->setRenderBuffer(_renderBuffer);
}

void SkyEntityManager::update()
{
	// Temporary values
	auto mainSky = getSelectedMainSky();
	auto mixSky = getSelectedMixSky();

	// Check if main sky exists
	if (mainSky != nullptr)
	{
		// Update rotation
		if (mainSky->isVisible())
		{
			mainSky->updateRotation();
		}

		// Update sky exposure
		if (_renderBus.isSkyExposureEnabled())
		{
			// Values
			float lightness = mainSky->getLightness(); // Current lightness
			float pitch = min(_renderBus.getCameraPitch() + 30.0f, 90.0f); // Full conversion at 60 degrees pitch
			float targetLightness = mainSky->getOriginalLightness() + (((90.0f - pitch) / 90.0f) * _exposureFactor);

			// Based on verticle angle
			if (lightness > targetLightness) // Decrease lightness
			{
				mainSky->setLightness(lightness - (_exposureSpeed * 3.5f));
			}
			else if (mainSky->getLightness() < targetLightness) // Increase lightness
			{
				mainSky->setLightness(lightness + _exposureSpeed);
			}
		}
		else
		{
			mainSky->setLightness(mainSky->getOriginalLightness()); // Revert lightness
		}
	}
}

void SkyEntityManager::setExposureFactor(float skyExposureFactor)
{
	_exposureFactor = skyExposureFactor;
}

void SkyEntityManager::setExposureSpeed(float speed)
{
	_exposureSpeed = speed;
}

float SkyEntityManager::getSkyExposureFactor()
{
	return _exposureFactor;
}

float SkyEntityManager::getSkyExposureSpeed()
{
	return _exposureSpeed;
}