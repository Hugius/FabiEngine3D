#include "sky_entity_manager.hpp"
#include "shader_bus.hpp"
#include <iostream>

SkyEntityManager::SkyEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus) :
	BaseEntityManager(objLoader, texLoader, shaderBus)
{
	_shaderBus.setSkyBrightness(1.0f);
}

SkyEntity * SkyEntityManager::getEntity(const string & ID)
{
	return dynamic_cast<SkyEntity*>(_getBaseEntity(ID, EntityType::SKY));
}

SkyEntity * SkyEntityManager::getSelectedSky()
{
	if (_getBaseEntities().empty() || _selectedID == "")
	{
		return nullptr;
	}
	else
	{
		return getEntity(_selectedID);
	}
}

void SkyEntityManager::selectSky(const string & ID)
{
	_selectedID = ID;
}

void SkyEntityManager::addSkyEntity(const string & ID, TextureLoader& texLoader, const vector<string> texturePaths)
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
	_createEntity(EntityType::SKY, ID)->load(ID);

	// Fill entity
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(SHAPE_CUBEMAP, skybox_data, sizeof(skybox_data) / sizeof(float)));
	getEntity(ID)->setDayCubeMap(texLoader.getCubeMap(texturePaths));
	getEntity(ID)->setDayTime();
	getEntity(ID)->setTexturePaths(texturePaths);
}

void SkyEntityManager::update(float delta)
{
	// Check if any sky exists and if one selected
	if (!_getBaseEntities().empty() && getSelectedSky() != nullptr)
	{
		// Shaderbus updates
		_shaderBus.setSkyRotationMatrix(getSelectedSky()->getRotationMatrix());
		_shaderBus.setSkyReflectionCubeMapDay(getSelectedSky()->getDayCubeMap());
		_shaderBus.setSkyReflectionCubeMapNight(getSelectedSky()->getNightCubeMap());
		_shaderBus.setSkyReflectionMixValue(getSelectedSky()->getMixValue());

		// Core updates
		_updateRotation(delta);
		_updateTextureMixing(delta);
		_updateEyeAdaption(delta);
	}
}

void SkyEntityManager::_updateRotation(float delta)
{
	for (auto & baseEntity : _getBaseEntities())
	{
		// Create temporary sky object
		auto * sky = getEntity(baseEntity->getID());

		// Update
		if (sky->isEnabled())
		{
			if (sky->getRotationSpeed() != 0.0f) // Check if has to rotate at all
			{
				// Rotate matrix
				sky->setRotationMatrix(glm::rotate(
					sky->getRotationMatrix(),
					glm::radians((sky->getRotationSpeed() * delta) / 100.0f),
					vec3(0.0f, 1.0f, 0.0f)));
			}
		}
	}
}

void SkyEntityManager::_updateTextureMixing(float delta)
{
	for (auto & baseEntity : _getBaseEntities())
	{
		// Create temporary sky object
		auto * sky = getEntity(baseEntity->getID());

		// Update time of sky
		if (sky->isDayTime())
		{
			// Daytime skybox
			if (sky->getMixValue() > 0.0f)
			{
				sky->setMixValue(sky->getMixValue() - (0.0001f * delta));
			}
		}
		else
		{
			// Nighttime skybox
			if (sky->getMixValue() < 1.0f)
			{
				sky->setMixValue(sky->getMixValue() + (0.0001f * delta));
			}
		}
	}
}

void SkyEntityManager::_updateEyeAdaption(float delta)
{
	// Sky brightness changer
	static float oldIntensity = _shaderBus.getBloomIntensity();
	
	if (_shaderBus.isSkyHdrEnabled())
	{
		if (getSelectedSky()->isDayTime())
		{
			if (_shaderBus.getCameraPitch() > 10.0f) // Looking at sky
			{
				float targetIntensity = oldIntensity - ((_shaderBus.getCameraPitch() - 10.0f) / 90.0f); // Based on verticle angle

				if (_shaderBus.getBloomIntensity() > targetIntensity) // Decrease bloom intensity
				{
					_shaderBus.setBloomIntensity(_shaderBus.getBloomIntensity() - (0.005f * delta));
				}
				else if (_shaderBus.getBloomIntensity() < targetIntensity) // Increase bloom intensity
				{
					_shaderBus.setBloomIntensity(_shaderBus.getBloomIntensity() + (0.0015f * delta));
				}
			}
			else
			{
				if (_shaderBus.getBloomIntensity() < oldIntensity) // Not looking at sky
				{
					_shaderBus.setBloomIntensity(_shaderBus.getBloomIntensity() + (0.0035f * delta));
				}
			}
		}
		else
		{
			_shaderBus.setBloomIntensity(oldIntensity); // Revert bloom intensity
		}
	}
}