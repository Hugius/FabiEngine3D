#pragma once

#include "base_entity_manager.hpp"

class PointlightEntityManager final : public BaseEntityManager
{
public:
	PointlightEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// VOID
	void update() override;
	void createEntity(const string& ID);

	// MISCELLANEOUS
	const unordered_map<string, shared_ptr<PointlightEntity>>& getEntities();
	shared_ptr<PointlightEntity> getEntity(const string& ID);

	// UNSIGNED INT
	static inline const unsigned int MAX_LIGHT_COUNT = 64;
};