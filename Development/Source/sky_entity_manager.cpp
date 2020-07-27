#include "sky_entity_manager.hpp"
#include "shader_bus.hpp"

#include <iostream>

SkyEntityManager::SkyEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus) :
	BaseEntityManager(objLoader, texLoader, shaderBus)
{
	
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

void SkyEntityManager::addSkyEntity(const string & ID)
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
}

void SkyEntityManager::update()
{
	// Check if any sky exists and if one selected
	if (!_getBaseEntities().empty() && getSelectedSky() != nullptr)
	{
		// Shaderbus updates
		_shaderBus.setSkyRotationMatrix(getSelectedSky()->getRotationMatrix());
		_shaderBus.setSkyReflectionCubeMap(getSelectedSky()->getCubeMap());

		// Core updates
		_updateRotation();
		_updateEyeAdaption();
	}
}

void SkyEntityManager::_updateRotation()
{
	for (auto & baseEntity : _getBaseEntities())
	{
		// Create temporary sky object
		auto * sky = getEntity(baseEntity->getID());

		// Update
		if (sky->isVisible())
		{
			if (sky->getRotationSpeed() != 0.0f) // Check if has to rotate at all
			{
				// Rotate matrix
				sky->setRotationMatrix(glm::rotate(
					sky->getRotationMatrix(),
					glm::radians((sky->getRotationSpeed()) / 100.0f),
					vec3(0.0f, 1.0f, 0.0f)));
			}
		}
	}
}

void SkyEntityManager::_updateEyeAdaption()
{
	// Sky brightness changer
	static float oldIntensity = _shaderBus.getBloomIntensity();

	if (_shaderBus.isSkyHdrEnabled())
	{
		if (_shaderBus.getCameraPitch() > 10.0f) // Looking at sky
		{
			float targetIntensity = oldIntensity - ((_shaderBus.getCameraPitch() - 10.0f) / 90.0f); // Based on verticle angle

			if (_shaderBus.getBloomIntensity() > targetIntensity) // Decrease bloom intensity
			{
				_shaderBus.setBloomIntensity(_shaderBus.getBloomIntensity() - 0.005f);
			}
			else if (_shaderBus.getBloomIntensity() < targetIntensity) // Increase bloom intensity
			{
				_shaderBus.setBloomIntensity(_shaderBus.getBloomIntensity() + 0.0015f);
			}
		}
		else
		{
			if (_shaderBus.getBloomIntensity() < oldIntensity) // Not looking at sky
			{
				_shaderBus.setBloomIntensity(_shaderBus.getBloomIntensity() + 0.0035f);
			}
		}
	}
	else
	{
		_shaderBus.setBloomIntensity(oldIntensity); // Revert bloom intensity
	}
}