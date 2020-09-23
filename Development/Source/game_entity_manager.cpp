#include "game_entity_manager.hpp"

#include <iostream>

GameEntityManager::GameEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(objLoader, texLoader, renderBus)
{

}

GameEntity* GameEntityManager::getEntity(const string& ID)
{
	return dynamic_cast<GameEntity*>(_getBaseEntity(ID, EntityType::GAME));
}

const vector<GameEntity*> GameEntityManager::getEntities()
{
	vector<GameEntity*> newVector;

	for (auto& entity : _getBaseEntities())
	{
		newVector.push_back(dynamic_cast<GameEntity*>(entity));
	}

	return newVector;
}

void GameEntityManager::addGameEntity
(
	const string& ID, const string& objName,
	vec3 T, vec3 R, vec3 S
)
{
	// Load OBJ model
	auto parts = _objLoader.loadOBJ(objName, false);

	// Create entity
	_createEntity(EntityType::GAME, ID)->load(ID);
	getEntity(ID)->setObjPath(objName);

	// Create OpenGL buffers
	for (auto & part : parts)
	{
		vector<float> data;

		// For every triangle vertex point
		for (unsigned int i = 0; i < part.vertices.size(); i++)
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
			getEntity(ID)->addDiffuseMap(_texLoader.getTexture("User\\assets\\textures\\diffuse_maps\\" + part.diffuseMapName, true, true, true));
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
			getEntity(ID)->addLightMap(_texLoader.getTexture("User\\assets\\textures\\light_maps\\" + part.lightMapName, true, true, true));
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
			getEntity(ID)->addNormalMap(_texLoader.getTexture("User\\assets\\textures\\normal_maps\\" + part.normalMapName, true, true, true));
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
			getEntity(ID)->addReflectionMap(_texLoader.getTexture("User\\assets\\textures\\reflection_maps\\" + part.reflectionMapName, true, true, true));
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

	// Load transformation
	getEntity(ID)->setTranslation(T);
	getEntity(ID)->setRotation(R);
	getEntity(ID)->setScaling(S);
}

void GameEntityManager::loadNormalMapping(const string& ID)
{
	// Check if not already a tangent loaded model
	if (getEntity(ID)->getOglBuffer()->getBufferType() != BufferType::MODEL_TANGENT)
	{
		// Load OBJ model
		_objLoader.clearOBJCache(getEntity(ID)->getObjPath());
		auto parts = _objLoader.loadOBJ(getEntity(ID)->getObjPath(), true);

		// Create OpenGL buffers
		for (auto& part : parts)
		{
			vector<float> data;

			// For every triangle vertex point
			for (unsigned int i = 0; i < part.vertices.size(); i++)
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

void GameEntityManager::update()
{
	for (auto & baseEntity : _getBaseEntities())
	{
		// Create temporary game entity object
		auto * entity = getEntity(baseEntity->getID());

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
			vec3 camPos = _renderBus.getCameraPosition();
			vec3 entityPos = entity->getTranslation();
			float xDistance = fabsf(camPos.x - entityPos.x);
			float yDistance = fabsf(camPos.y - entityPos.y);
			float zDistance = fabsf(camPos.z - entityPos.z);
			float absolsuteDistance = sqrtf((xDistance * xDistance) + (yDistance * yDistance) + (zDistance * zDistance));

			// Check if farther than LOD distance
			entity->setLevelOfDetailed(absolsuteDistance > 100.0f && entity->getLodEntityID() != "");
		}
	}
}