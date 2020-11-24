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

const vector<shared_ptr<GameEntity>> GameEntityManager::getEntities()
{
	return _getGameEntities();
}

void GameEntityManager::addGameEntity(const string& ID, const string& objName, Vec3 T, Vec3 R, Vec3 S)
{
	// Create entity
	_createEntity(ID);
	
	// Load OBJ
	generateModel(ID, objName);

	// Load transformation
	getEntity(ID)->setOriginalTranslation(T);
	getEntity(ID)->setOriginalRotation(R);
	getEntity(ID)->setOriginalScaling(S);
	getEntity(ID)->setTranslation(T);
	getEntity(ID)->setRotation(R);
	getEntity(ID)->setScaling(S);
}

void GameEntityManager::generateModel(const string& ID, const string& objName)
{
	// Load OBJ model
	auto parts = _objLoader.loadOBJ(objName, false);
	getEntity(ID)->setObjPath(objName);
	getEntity(ID)->clearOglBuffers();
	getEntity(ID)->clearDiffuseMaps();
	getEntity(ID)->clearLightMaps();
	getEntity(ID)->clearReflectionMaps();
	getEntity(ID)->clearNormalMaps();

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
		}

		// OpenGL buffer
		getEntity(ID)->addOglBuffer(new OpenGLBuffer(BufferType::MODEL, &data[0], data.size()));

		// Load an OBJ part diffuse map
		if (part.diffuseMapName != "")
		{
			getEntity(ID)->addDiffuseMap(_texLoader.getTexture("user\\assets\\textures\\diffuse_maps\\" + part.diffuseMapName, true, true, true));
			getEntity(ID)->addDiffuseMapPath("user\\assets\\textures\\diffuse_maps\\" + part.diffuseMapName);
		}
		else
		{
			// Only add empty diffuse maps if multiparted model
			if (parts.size() > 1)
			{
				getEntity(ID)->addDiffuseMap(0);
			}
		}

		// Load an OBJ part light map
		if (part.lightMapName != "")
		{
			getEntity(ID)->setLightMapped(true);
			getEntity(ID)->addLightMap(_texLoader.getTexture("user\\assets\\textures\\light_maps\\" + part.lightMapName, true, true, true));
			getEntity(ID)->addLightMapPath("user\\assets\\textures\\light_maps\\" + part.lightMapName);
		}
		else
		{
			// Only add empty light maps if multiparted model
			if (parts.size() > 1)
			{
				getEntity(ID)->addLightMap(0);
			}
		}

		// Load an OBJ part normal map
		if (part.normalMapName != "")
		{
			getEntity(ID)->addNormalMap(_texLoader.getTexture("user\\assets\\textures\\normal_maps\\" + part.normalMapName, true, true, true));
			getEntity(ID)->addNormalMapPath("user\\assets\\textures\\normal_maps\\" + part.normalMapName);
		}
		else
		{
			// Only add empty normal maps if multiparted model
			if (parts.size() > 1)
			{
				getEntity(ID)->addNormalMap(0);
			}
		}

		// Load an OBJ part reflection map
		if (part.reflectionMapName != "")
		{
			getEntity(ID)->setSkyReflective(true);
			getEntity(ID)->addReflectionMap(_texLoader.getTexture("user\\assets\\textures\\reflection_maps\\" + part.reflectionMapName, true, true, true));
			getEntity(ID)->addReflectionMapPath("user\\assets\\textures\\reflection_maps\\" + part.reflectionMapName);
		}
		else
		{
			// Only add empty reflection maps if multiparted model
			if (parts.size() > 1)
			{
				getEntity(ID)->addReflectionMap(0);
			}
		}
	}
}

void GameEntityManager::loadNormalMapping(const string& ID)
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

void GameEntityManager::setLodDistance(float distance)
{
	_lodDistance = distance;
}

void GameEntityManager::update()
{
	for (auto& entity : _getGameEntities())
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

			// Calculate absolute distance between camera and entity
			Vec3 camPos = _renderBus.getCameraPosition();
			Vec3 entityPos = entity->getTranslation();
			float xDistance = fabsf(camPos.x - entityPos.x);
			float yDistance = fabsf(camPos.y - entityPos.y);
			float zDistance = fabsf(camPos.z - entityPos.z);
			float absolsuteDistance = sqrtf((xDistance * xDistance) + (yDistance * yDistance) + (zDistance * zDistance));
			bool isFarEnough = (absolsuteDistance > _lodDistance) && (!entity->getLodEntityID().empty());

			// Check if farther than LOD distance
			entity->setLevelOfDetailed(isFarEnough);
		}
	}
}

float GameEntityManager::getLodDistance()
{
	return _lodDistance;
}