#include "game_entity_manager.hpp"
#include "logger.hpp"

GameEntityManager::GameEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(EntityType::GAME, objLoader, texLoader, renderBus)
{

}

shared_ptr<GameEntity> GameEntityManager::getEntity(const string& ID)
{
	auto result = _getGameEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("Nonexisting GAME entity with ID \"" + ID + "\" requested");
	}

	return result;
}

const unordered_map<string, shared_ptr<GameEntity>>& GameEntityManager::getEntities()
{
	return _getGameEntities();
}

void GameEntityManager::addGameEntity(const string& ID, const string& objName, Vec3 T, Vec3 R, Vec3 S)
{
	// Create entity
	_createEntity(ID);
	
	// Load OBJ
	generateModel(ID, objName);

	auto entity = getEntity(ID);

	// Load transformation
	entity->setOriginalTranslation(T);
	entity->setOriginalRotation(R);
	entity->setOriginalScaling(S);
	entity->setTranslation(T);
	entity->setRotation(R);
	entity->setScaling(S);
}

void GameEntityManager::generateModel(const string& ID, const string& objName)
{
	// Load OBJ model
	auto parts = _objLoader.loadOBJ(objName, false);
	auto entity = getEntity(ID);
	entity->setObjPath(objName);
	entity->clearOglBuffers();
	entity->clearDiffuseMaps();
	entity->clearLightMaps();
	entity->clearReflectionMaps();
	entity->clearNormalMaps();

	// Check if model loading failed
	if (parts.empty())
	{
		entity->addPart("");
	}
	
	// Create OpenGL buffers
	for (auto& part : parts)
	{
		// Temporary values
		vector<float> bufferData;

		// For every triangle vertex point
		for (size_t i = 0; i < part.vertices.size(); i++)
		{
			// Vertex coordinate
			bufferData.push_back(part.vertices[i].x);
			bufferData.push_back(part.vertices[i].y);
			bufferData.push_back(part.vertices[i].z);

			// UV coordinate
			bufferData.push_back(part.uvCoords[i].x);
			bufferData.push_back(part.uvCoords[i].y);

			// Normal vector
			bufferData.push_back(part.normals[i].x);
			bufferData.push_back(part.normals[i].y);
			bufferData.push_back(part.normals[i].z);
		}

		// OpenGL buffer
		entity->addOglBuffer(new OpenGLBuffer(BufferType::MODEL, &bufferData[0], bufferData.size()));

		// New transformation part
		entity->addPart(part.name);

		// Load an OBJ part diffuse map
		if (part.diffuseMapName != "")
		{
			entity->addDiffuseMap(_texLoader.getTexture("user\\assets\\textures\\diffuse_maps\\" + part.diffuseMapName, true, true, true));
			entity->addDiffuseMapPath("user\\assets\\textures\\diffuse_maps\\" + part.diffuseMapName);
		}
		else
		{
			// Only add empty diffuse maps if multiparted model
			if (parts.size() > 1)
			{
				entity->addDiffuseMap(0);
			}
		}

		// Load an OBJ part light map
		if (part.lightMapName != "")
		{
			entity->setLightMapped(true);
			entity->addLightMap(_texLoader.getTexture("user\\assets\\textures\\light_maps\\" + part.lightMapName, true, true, true));
			entity->addLightMapPath("user\\assets\\textures\\light_maps\\" + part.lightMapName);
		}
		else
		{
			// Only add empty light maps if multiparted model
			if (parts.size() > 1)
			{
				entity->addLightMap(0);
			}
		}

		// Load an OBJ part normal map
		if (part.normalMapName != "")
		{
			entity->addNormalMap(_texLoader.getTexture("user\\assets\\textures\\normal_maps\\" + part.normalMapName, true, true, true));
			entity->addNormalMapPath("user\\assets\\textures\\normal_maps\\" + part.normalMapName);
		}
		else
		{
			// Only add empty normal maps if multiparted model
			if (parts.size() > 1)
			{
				entity->addNormalMap(0);
			}
		}

		// Load an OBJ part reflection map
		if (part.reflectionMapName != "")
		{
			entity->setSkyReflective(true);
			entity->addReflectionMap(_texLoader.getTexture("user\\assets\\textures\\reflection_maps\\" + part.reflectionMapName, true, true, true));
			entity->addReflectionMapPath("user\\assets\\textures\\reflection_maps\\" + part.reflectionMapName);
		}
		else
		{
			// Only add empty reflection maps if multiparted model
			if (parts.size() > 1)
			{
				entity->addReflectionMap(0);
			}
		}
	}
}

void GameEntityManager::loadNormalMapping(const string& ID)
{
	// Check if entity has a buffer
	if (!getEntity(ID)->getOglBuffers().empty())
	{
		// Check if not already a tangent loaded model
		if (getEntity(ID)->getOglBuffer()->getBufferType() != BufferType::MODEL_TANGENT)
		{
			// Load OBJ model
			auto parts = _objLoader.loadOBJ(getEntity(ID)->getObjPath(), true);

			// Create OpenGL buffers
			for (auto& part : parts)
			{
				vector<float> data;

				// For every triangle vertex point
				for (size_t i = 0; i < part.vertices.size(); i++)
				{
					// Vertex coordinate
					data.push_back(part.vertices[i].x);
					data.push_back(part.vertices[i].y);
					data.push_back(part.vertices[i].z);

					// UV coordinate
					data.push_back(part.uvCoords[i].x);
					data.push_back(part.uvCoords[i].y);

					// Normal vector
					data.push_back(part.normals[i].x);
					data.push_back(part.normals[i].y);
					data.push_back(part.normals[i].z);

					// Tangent vector
					data.push_back(part.tangents[i].x);
					data.push_back(part.tangents[i].y);
					data.push_back(part.tangents[i].z);
				}

				// OpenGL buffer
				getEntity(ID)->clearOglBuffers();
				getEntity(ID)->addOglBuffer(new OpenGLBuffer(BufferType::MODEL_TANGENT, &data[0], data.size()));
			}
		}
	}
}

void GameEntityManager::update()
{
	for (auto& [keyID, entity] : _getGameEntities())
	{
		// Only update if visible
		if (entity->isVisible())
		{
			// Calculate model matrix
			entity->updateModelMatrix();

			// Update reflection height
			if (entity->isSceneReflective() && _renderBus.isSceneReflectionsEnabled())
			{
				_renderBus.setSceneReflectionHeight(entity->getTranslation().y);
				_renderBus.setSceneReflectionOffset(0.0000001f);
			}

			// Check if entity has LOD
			if (!entity->getLodEntityID().empty())
			{
				// Calculate absolute distance between camera and entity
				Vec3 camPos = _renderBus.getCameraPosition();
				Vec3 entityPos = entity->getTranslation();
				float xDistance = fabsf(camPos.x - entityPos.x);
				float yDistance = fabsf(camPos.y - entityPos.y);
				float zDistance = fabsf(camPos.z - entityPos.z);
				float absolsuteDistance = sqrtf((xDistance * xDistance) + (yDistance * yDistance) + (zDistance * zDistance));

				// Check if farther than LOD distance
				bool isFarEnough = (absolsuteDistance > _lodDistance) && (!entity->getLodEntityID().empty());
				entity->setLevelOfDetailed(isFarEnough);
			}
		}
	}
}

void GameEntityManager::setLodDistance(float distance)
{
	_lodDistance = distance;
}

float GameEntityManager::getLodDistance()
{
	return _lodDistance;
}