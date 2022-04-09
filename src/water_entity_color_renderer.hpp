#pragma once

#include "base_renderer.hpp"
#include "water_entity.hpp"
#include "pointlight_entity.hpp"
#include "spotlight_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class WaterEntityColorRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void processPointlightEntities(const unordered_map<string, shared_ptr<PointlightEntity>> & entities);
	void processSpotlightEntities(const unordered_map<string, shared_ptr<SpotlightEntity>> & entities);
	void render(const shared_ptr<WaterEntity> entity);
};