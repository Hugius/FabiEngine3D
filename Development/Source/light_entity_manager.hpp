#pragma once

#include "base_entity_manager.hpp"

class LightEntityManager final : public BaseEntityManager
{
public:
	LightEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus);
	~LightEntityManager() = default;

	shared_ptr<LightEntity> getEntity(const string& ID);

	const vector<shared_ptr<LightEntity>> getEntities();

	void addLightEntity(const string& ID, vec3 position, vec3 color, float intensity, float distanceFactor);

	void update() override;
};