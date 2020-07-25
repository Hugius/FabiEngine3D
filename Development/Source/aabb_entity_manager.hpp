#pragma once

#include "base_entity_manager.hpp"

class AabbEntityManager final :  public BaseEntityManager
{
public:
	AabbEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus);
	~AabbEntityManager() = default;

	AabbEntity * getEntity(const string & ID) override;

	const vector<AabbEntity*> getEntities();
	
	void addAabbEntity(const string & ID, vec3 T, vec3 R, vec3 S, bool rresponsiveesponse);
	void bindAabbEntity(const string & ID, const string & parentID, vec3 R, vec3 S, bool responsive);

	void update() override {}
	void update(const vector<GameEntity*> & gameEntities);
};