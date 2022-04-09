#pragma once

#include "base_renderer.hpp"
#include "model_entity.hpp"
#include "pointlight_entity.hpp"
#include "spotlight_entity.hpp"
#include "reflection_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class ModelEntityColorRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void processPointlightEntities(const unordered_map<string, shared_ptr<PointlightEntity>> & entities);
	void processSpotlightEntities(const unordered_map<string, shared_ptr<SpotlightEntity>> & entities);
	void render(const shared_ptr<ModelEntity> entity, const unordered_map<string, shared_ptr<ReflectionEntity>> & reflectionEntities);
};