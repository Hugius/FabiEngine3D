#include <WE3D/GameEntityManager.hpp>

GameEntityManager::GameEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus) :
	EntityManager(objLoader, texLoader, shaderBus)
{

}

GameEntity* GameEntityManager::getEntity(const string & ID)
{
	return dynamic_cast<GameEntity*>(p_getBaseEntity(ID, EntityType::GAME));
}

const vector<GameEntity*> GameEntityManager::getEntities()
{
	vector<GameEntity*> newVector;

	for (auto& entity : p_getBaseEntities())
	{
		newVector.push_back(dynamic_cast<GameEntity*>(entity));
	}

	return newVector;
}

void GameEntityManager::addGameEntity
(
	const string & ID, const string & modelName,
	vec3 T, vec3 R, vec3 S, 
	bool transparent, bool faceCulled, bool lightMapped, bool reflective, bool specular
)
{
	// Load OBJ model
	auto parts = p_objLoader.loadOBJ(modelName);

	// Create entity
	p_createEntity(EntityType::GAME, ID)->load(ID);
	getEntity(ID)->setModelName(modelName);

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

		// Diffuse map
		getEntity(ID)->addDiffuseMap(p_texLoader.getTexture("../Game/Textures/DiffuseMaps/" + part.textureName, true, true, false));

		// Light map
		if (lightMapped)
		{
			getEntity(ID)->addLightmap(p_texLoader.getTexture("../Game/Textures/LightMaps/" + part.textureName, false, false, false));
		}

		// Reflection map
		if (reflective)
		{
			getEntity(ID)->addReflectionMap(p_texLoader.getTexture("../Game/Textures/ReflectionMaps/" + part.textureName, false, false, false));
		}
	}

	// Load transformation
	getEntity(ID)->setTranslation(T);
	getEntity(ID)->setRotation(R);
	getEntity(ID)->setScaling(S);

	// Edit entity
	getEntity(ID)->setTransparent(transparent);
	getEntity(ID)->setFaceCulled(faceCulled);
	getEntity(ID)->setLightMapped(lightMapped);
	getEntity(ID)->setSkyReflective(reflective);
	getEntity(ID)->setSpecular(specular);
}

void GameEntityManager::addGameEntity
(
	const string & ID, const string & modelName, 
	const vector<vec3> & offsets, vec3 R, vec3 S, 
	bool transparent, bool faceCulled, bool lightMapped, bool reflective, bool specular
)
{
	// Load OBJ model
	auto parts = p_objLoader.loadOBJ(modelName);

	// Create entity
	p_createEntity(EntityType::GAME, ID)->load(ID);
	getEntity(ID)->setModelName(modelName);

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
		getEntity(ID)->addDiffuseMap(p_texLoader.getTexture("../Game/Textures/DiffuseMaps/" + part.textureName, true, true));
	}

	// Load transformation
	getEntity(ID)->setRotation(R);
	getEntity(ID)->setScaling(S);

	// Load light map
	if (lightMapped)
	{
		getEntity(ID)->addLightmap(p_texLoader.getTexture("../Game/Textures/LightMaps/" + modelName, false, false));
	}

	// Load reflection map
	if (reflective)
	{
		getEntity(ID)->addReflectionMap(p_texLoader.getTexture("../Game/Textures/ReflectionMaps/" + modelName, false, false));
	}

	// Edit entity
	getEntity(ID)->setTransparent(transparent);
	getEntity(ID)->setFaceCulled(faceCulled);
	getEntity(ID)->setLightMapped(lightMapped);
	getEntity(ID)->setSkyReflective(reflective);
	getEntity(ID)->setSpecular(specular);
}

void GameEntityManager::update(float delta)
{
	for (auto & baseEntity : p_getBaseEntities())
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