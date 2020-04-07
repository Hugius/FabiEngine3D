#include <WE3D/SkyEntityManager.hpp>
#include <WE3D/ShaderBus.hpp>
#include <iostream>

SkyEntityManager::SkyEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus) :
	EntityManager(objLoader, texLoader, shaderBus)
{
	p_shaderBus.setSkyBrightness(1.0f);
}

SkyEntity * SkyEntityManager::getEntity(const string & ID)
{
	return dynamic_cast<SkyEntity*>(p_getBaseEntity(ID, EntityType::SKY));
}

SkyEntity * SkyEntityManager::getSelectedSky()
{
	if (p_getBaseEntities().empty() || p_selectedID == "")
	{
		return nullptr;
	}
	else
	{
		return getEntity(p_selectedID);
	}
}

void SkyEntityManager::selectSky(const string & ID)
{
	p_selectedID = ID;

	if (getSelectedSky()->getAmbStrength() != -1.0f)
	{
		p_shaderBus.setAmbLightStrength(getSelectedSky()->getAmbStrength());
	}

	if (getSelectedSky()->getDirStrength() != -1.0f)
	{
		p_shaderBus.setDirLightStrength(getSelectedSky()->getDirStrength());
	}
}

void SkyEntityManager::addSkyEntity
(
	const string & ID, const string & dayDirectory, const string & nightDirectory, float rotationSpeed, TextureLoader& texLoader
)
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
	p_createEntity(EntityType::SKY, ID)->load(ID);

	// Fill entity
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(SHAPE_CUBEMAP, skybox_data, sizeof(skybox_data) / sizeof(float)));
	getEntity(ID)->setDayCubeMap(texLoader.getCubeMap("../Game/Textures/CubeMaps/" + dayDirectory + "/"));
	getEntity(ID)->setNightCubeMap(texLoader.getCubeMap("../Game/Textures/CubeMaps/" + nightDirectory + "/"));
	getEntity(ID)->setRotationSpeed(rotationSpeed);
}

void SkyEntityManager::update(float delta)
{
	// Check if any sky exists and if one selected
	if (!p_getBaseEntities().empty() && getSelectedSky() != nullptr)
	{
		// Shaderbus updates
		p_shaderBus.setSkyRotationMatrix(getSelectedSky()->getRotationMatrix());
		p_shaderBus.setDayReflectionCubeMap(getSelectedSky()->getDayCubeMap());
		p_shaderBus.setNightReflectionCubeMap(getSelectedSky()->getNightCubeMap());
		p_shaderBus.setSkyReflectionMixValue(getSelectedSky()->getMixValue());

		// Core updates
		p_updateRotation(delta);
		p_updateBrightness(delta);
		p_updateEyeAdaption(delta);
	}
}

void SkyEntityManager::p_updateRotation(float delta)
{
	for (auto & baseEntity : p_getBaseEntities())
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

void SkyEntityManager::p_updateBrightness(float delta)
{
	for (auto & baseEntity : p_getBaseEntities())
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

	// Ambient lighting
	if (getSelectedSky()->getAmbStrength() != -1.0f)
	{
		if (p_shaderBus.getAmbLightStrength() < getSelectedSky()->getAmbStrength())
		{
			p_shaderBus.setAmbLightStrength(p_shaderBus.getAmbLightStrength() + (0.00005f * delta));
		}
		else if (p_shaderBus.getAmbLightStrength() > getSelectedSky()->getAmbStrength())
		{
			p_shaderBus.setAmbLightStrength(p_shaderBus.getAmbLightStrength() - (0.00005f * delta));
		}
	}

	// Directional lighting
	if (getSelectedSky()->getDirStrength() != -1.0f)
	{
		if (p_shaderBus.getDirLightStrength() < getSelectedSky()->getDirStrength())
		{
			p_shaderBus.setDirLightStrength(p_shaderBus.getDirLightStrength() + (0.00005f * delta));
		}
		else if (p_shaderBus.getDirLightStrength() > getSelectedSky()->getDirStrength())
		{
			p_shaderBus.setDirLightStrength(p_shaderBus.getDirLightStrength() - (0.00005f * delta));
		}
	}
}

void SkyEntityManager::p_updateEyeAdaption(float delta)
{
	// Sky brightness changer
	static float oldIntensity = p_shaderBus.getBloomIntensity();
	
	if (p_shaderBus.isSkyHdrEnabled())
	{
		if (getSelectedSky()->isDayTime())
		{
			if (p_shaderBus.getCameraPitch() > 10.0f) // Looking at sky
			{
				float targetIntensity = oldIntensity - ((p_shaderBus.getCameraPitch() - 10.0f) / 90.0f); // Based on verticle angle

				if (p_shaderBus.getBloomIntensity() > targetIntensity) // Decrease bloom intensity
				{
					p_shaderBus.setBloomIntensity(p_shaderBus.getBloomIntensity() - (0.005f * delta));
				}
				else if (p_shaderBus.getBloomIntensity() < targetIntensity) // Increase bloom intensity
				{
					p_shaderBus.setBloomIntensity(p_shaderBus.getBloomIntensity() + (0.0015f * delta));
				}
			}
			else
			{
				if (p_shaderBus.getBloomIntensity() < oldIntensity) // Not looking at sky
				{
					p_shaderBus.setBloomIntensity(p_shaderBus.getBloomIntensity() + (0.0035f * delta));
				}
			}
		}
		else
		{
			p_shaderBus.setBloomIntensity(oldIntensity); // Revert bloom intensity
		}
	}
}