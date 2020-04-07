#pragma once
#include "EntityManager.hpp"

class AabbEntityManager final :  public EntityManager
{
public:
	AabbEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus);
	~AabbEntityManager() = default;

	AabbEntity * getEntity(const string & ID) override;

	const vector<AabbEntity*> getEntities();
	
	void addAabbEntity(const string & ID, vec3 T, vec3 R, vec3 S, bool rresponsiveesponse);
	void bindAabbEntity(const string & ID, const string & parentID, vec3 R, vec3 S, bool responsive);

	void update(float delta) override {}
	void update(const vector<GameEntity*> & gameEntities);
};