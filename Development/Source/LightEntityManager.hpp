#pragma once
#include "EntityManager.hpp"

class LightEntityManager final : public EntityManager
{
public:
	LightEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus);
	~LightEntityManager() = default;

	LightEntity * getEntity(const string & ID) override;

	const vector<LightEntity*> getEntities();

	void addLightEntity(const string & ID, vec3 position, vec3 color, float strength);

	void update(float delta) override {}
};