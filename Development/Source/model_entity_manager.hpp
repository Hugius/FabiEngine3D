#pragma once

#include "base_entity_manager.hpp"
#include "timer.hpp"

class ModelEntityManager final : public BaseEntityManager
{
public:
	ModelEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus, Timer& timer);

	// Voids
	void createEntity(const string& ID, const string& meshPath);
	void setLevelOfDetailDistance(float distance);
	void update() override;
	void update(const unordered_map<string, shared_ptr<ReflectionEntity>>& reflectionEntities);

	// Instances
	shared_ptr<ModelEntity> getEntity(const string& ID);
	const unordered_map<string, shared_ptr<ModelEntity>>& getEntities();

	// Floats
	float getLevelOfDetailDistance();

private:
	// Instances
	Timer& _timer;

	// Floats
	static inline const float CUBE_REFLECTION_OVERLAP_SPEED = 0.01f;
	float _levelOfDetailDistance = 0.0f;
};