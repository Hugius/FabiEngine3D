#pragma once

#include "base_entity_manager.hpp"

class PointlightEntityManager final : public BaseEntityManager
{
public:
	PointlightEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// Voids
	void createEntity(const string& ID);
	void update() override;

	// Integers
	static inline const unsigned int MAX_LIGHT_COUNT = 64;

	// Miscellaneous
	shared_ptr<PointlightEntity> getEntity(const string& ID);
	const unordered_map<string, shared_ptr<PointlightEntity>>& getEntities();
};