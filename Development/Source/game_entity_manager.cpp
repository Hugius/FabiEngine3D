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

		// Load model-specified texture
		if (part.textureName != "")
		{
			getEntity(ID)->addDiffuseMap(_texLoader.getTexture("User\\Assets\\Textures\\DiffuseMaps\\" + part.textureName, true, true, true));
		}
	}

	// Load transformation
	getEntity(ID)->setTranslation(T);
	getEntity(ID)->setRotation(R);
	getEntity(ID)->setScaling(S);
}

void GameEntityManager::addGameEntity
(
	const string & ID, const string & modelName, 
	const vector<vec3> & offsets, vec3 R, vec3 S, 
	bool transparent, bool faceCulled, bool lightMapped, bool reflective, bool specular
)
{
	// Load OBJ model
	auto parts = _objLoader.loadOBJ(modelName);

	// Create entity
	_createEntity(EntityType::GAME, ID)->load(ID);
	getEntity(ID)->setObjPath(modelName);

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

		getEntity(ID)->addOglBuffer(new OpenGLBuffer(&data[0], data.size(), offsets));
		getEntity(ID)->setDiffuseMap(_texLoader.getTexture("../User/Assets/Textures/DiffuseMaps/" + part.textureName, true, true));
	}

	// Load transformation
	getEntity(ID)->setRotation(R);
	getEntity(ID)->setScaling(S);

	// Load light map
	if (lightMapped)
	{
		getEntity(ID)->setLightMap(_texLoader.getTexture("../User/Assets/Textures/LightMaps/" + modelName, false, false));
	}

	// Load reflection map
	if (reflective)
	{
		getEntity(ID)->setReflectionMap(_texLoader.getTexture("../User/Assets/Textures/ReflectionMaps/" + modelName, false, false));
	}

	// Edit entity
	getEntity(ID)->setTransparent(transparent);
	getEntity(ID)->setFaceCulled(faceCulled);
	getEntity(ID)->setLightMapped(lightMapped);
	getEntity(ID)->setSkyReflective(reflective);
	getEntity(ID)->setSpecularLighted(specular);
}

void GameEntityManager::update()
{
	for (auto & baseEntity : _getBaseEntities())
	{
		// Create temporary game entity object
		auto * entity = getEntity(baseEntity->getID());

		// Calculate model matrix
		if (entity->isEnabled())
		{
			entity->updateModelMatrix();
		}
	}
}