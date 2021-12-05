#pragma once

#include "base_entity_manager.hpp"
#include "timer.hpp"

class ModelEntityManager final : public BaseEntityManager
{
public:
	ModelEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus, Timer& timer);

	// VOID
	void update() override;
	void update(const unordered_map<string, shared_ptr<ReflectionEntity>>& reflectionEntities);
	void createEntity(const string& ID, const string& meshPath);

	// MISCELLANEOUS
	const unordered_map<string, shared_ptr<ModelEntity>>& getEntities();
	shared_ptr<ModelEntity> getEntity(const string& ID);

private:
	// FLOAT
	static inline const float CUBE_REFLECTION_OVERLAP_SPEED = 0.01f;

	// MISCELLANEOUS
	Timer& _timer;
};