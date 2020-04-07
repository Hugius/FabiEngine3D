#pragma once
#include "EntityManager.hpp"

class GameEntityManager final :  public EntityManager
{
public:
	GameEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus);
	~GameEntityManager() = default;

	GameEntity * getEntity(const string & ID) override;

	const vector<GameEntity*> getEntities();

	void addGameEntity
	(
		const string & ID, const string & modelName,
		vec3 T, vec3 R, vec3 S,
		bool transparent, bool faceCulled, bool lightMapped, bool reflective, bool specular
	);

	void addGameEntity
	(
		const string & ID, const string & modelName,
		const vector<vec3> & offsets, vec3 R, vec3 S,
		bool transparent, bool faceCulled, bool lightMapped, bool reflective, bool specular
	);

	void update(float delta) override;
};