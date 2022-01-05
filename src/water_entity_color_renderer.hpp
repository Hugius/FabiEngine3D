#pragma once

#include "pointlight_entity.hpp"
#include "spotlight_entity.hpp"
#include "water_entity.hpp"
#include "shader_buffer.hpp"
#include "render_bus.hpp"

#include <unordered_map>

using std::unordered_map;

class WaterEntityColorRenderer final : BaseRenderer
{
public:
	void bind() override;
	void unbind() override;
	void processPointlightEntities(const unordered_map<string, shared_ptr<PointlightEntity>>& entities);
	void processSpotlightEntities(const unordered_map<string, shared_ptr<SpotlightEntity>>& entities);
	void render(const shared_ptr<WaterEntity> entity);
};