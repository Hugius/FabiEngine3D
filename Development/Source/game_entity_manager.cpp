#include "game_entity_manager.hpp"

GameEntityManager::GameEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus) :
	BaseEntityManager(objLoader, texLoader, shaderBus)
{

}

GameEntity* GameEntityManager::getEntity(const string & ID)
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
	const string & ID, const string & objName,
	vec3 T, vec3 R, vec3 S
)
{
	// Load OBJ model
	auto parts = _objLoader.loadOBJ(objName);

	// Create entity
	_createEntity(EntityType::GAME, ID)->load(ID);
	getEntity(ID)->setObjPath(objName);

	// Create OpenGL buffers
	for (auto & part : parts)
	{
		vector<float> data;

		for (unsigned int i = 0; i < part.vertices.size(); i++)
		{
			data.push_back(part.vertices[i].x);
			data.push_back(part.vertices[i].y);
			data.push_back(part.vertices[i].z);

			data.push_back(part.uvCoords[i].x);
			data.push_back(part.uvCoords[i].y);

			data.push_back(part.normals[i].x);
			data.push_back(part.normals[i].y);
			data.push_back(part.normals[i].z);
		}

		// OpenGL buffer
		getEntity(ID)->addOglBuffer(new OpenGLBuffer(SHAPE_3D, &data[0], data.size()));

		// Load an OBJ part diffuse map
		if (part.diffuseMapName != "")
		{
			getEntity(ID)->addDiffuseMap(_texLoader.getTexture("User\\Assets\\Textures\\DiffuseMaps\\" + part.diffuseMapName, true, true, true));
		}
		else
		{
			getEntity(ID)->addDiffuseMap(0);
		}

		// Load an OBJ part light map
		if (part.lightMapName != "")
		{
			getEntity(ID)->setLightMapped(true);
			getEntity(ID)->addLightMap(_texLoader.getTexture("User\\Assets\\Textures\\LightMaps\\" + part.lightMapName, true, true, true));
		}
		else
		{
			getEntity(ID)->addLightMap(0);
		}

		// Load an OBJ part light map
		if (part.reflectionMapName != "")
		{
			getEntity(ID)->setSkyReflective(true);
			getEntity(ID)->addReflectionMap(_texLoader.getTexture("User\\Assets\\Textures\\ReflectionMaps\\" + part.reflectionMapName, true, true, true));
		}
		else
		{
			getEntity(ID)->addReflectionMap(0);
		}
	}

	// Load transformation
	getEntity(ID)->setTranslation(T);
	getEntity(ID)->setRotation(R);
	getEntity(ID)->setScaling(S);
}

void GameEntityManager::update()
{
	for (auto & baseEntity : _getBaseEntities())
	{
		// Create temporary game entity object
		auto * entity = getEntity(baseEntity->getID());

		// Calculate model matrix
		if (entity->isVisible())
		{
			entity->updateModelMatrix();
		}
	}
}