#include "sky_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp"

using std::make_shared;
using std::min;

const float bufferData[] =
{
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};

SkyEntityManager::SkyEntityManager(RenderBus& renderBus)
	:
	_renderBus(renderBus),
	_renderBuffer(make_shared<RenderBuffer>(RenderBufferType::VERTEX, bufferData, static_cast<unsigned int>(sizeof(bufferData) / sizeof(float))))
{

}

shared_ptr<SkyEntity> SkyEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

	if(iterator == _entities.end())
	{
		Logger::throwError("SkyEntityManager::getEntity");
	}
	else
	{
		return iterator->second;
	}
}

shared_ptr<SkyEntity> SkyEntityManager::getSelectedMainSky()
{
	if(_entities.empty() || _selectedMainID.empty())
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
	if(_entities.empty() || _selectedMixID.empty())
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
	return _entities;
}

void SkyEntityManager::selectMainSky(const string& ID)
{
	if(isEntityExisting(ID) || ID.empty())
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
	if(isEntityExisting(ID) || ID.empty())
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
	_entities.insert(make_pair(ID, make_shared<SkyEntity>(ID)));
	getEntity(ID)->setRenderBuffer(_renderBuffer);
}

void SkyEntityManager::update()
{
	auto mainSky = getSelectedMainSky();
	auto mixSky = getSelectedMixSky();

	if(mainSky != nullptr)
	{
		if(_isExposureEnabled)
		{
			float lightness = mainSky->getLightness();
			float pitch = min(_renderBus.getCameraPitch() + 30.0f, 90.0f);
			float targetLightness = mainSky->getInitialLightness() + (((90.0f - pitch) / 90.0f) * _exposureIntensity);

			if(lightness > targetLightness)
			{
				mainSky->setLightness(lightness - (_exposureSpeed * 3.5f));
			}
			else if(mainSky->getLightness() < targetLightness)
			{
				mainSky->setLightness(lightness + _exposureSpeed);
			}
		}
		else
		{
			mainSky->setLightness(mainSky->getInitialLightness());
		}

		if(mainSky->isVisible())
		{
			mainSky->updateRotationMatrix();
		}
	}
}

void SkyEntityManager::setExposureIntensity(float value)
{
	_exposureIntensity = value;
}

void SkyEntityManager::setExposureSpeed(float value)
{
	_exposureSpeed = value;
}

void SkyEntityManager::setExposureEnabled(bool value)
{
	_isExposureEnabled = value;
}

const float SkyEntityManager::getExposureIntensity() const
{
	return _exposureIntensity;
}

const float SkyEntityManager::getExposureSpeed() const
{
	return _exposureSpeed;
}

const bool SkyEntityManager::isExposureEnabled() const
{
	return _isExposureEnabled;
}

void SkyEntityManager::deleteEntity(const string& ID)
{
	if(!isEntityExisting(ID))
	{
		Logger::throwError("SkyEntityManager::deleteEntity");
	}

	_entities.erase(ID);
}

void SkyEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool SkyEntityManager::isEntityExisting(const string& ID)
{
	return (_entities.find(ID) != _entities.end());
}