#pragma once
#include "base_entity_manager.hpp"

class LightEntityManager final : public BaseEntityManager
{
public:
	LightEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus);
	~LightEntityManager() = default;

	LightEntity * getEntity(const string & ID) override;

	const vector<LightEntity*> getEntities();

	void addLightEntity(const string & ID, vec3 position, vec3 color, float strength);

	void update() override {}
};