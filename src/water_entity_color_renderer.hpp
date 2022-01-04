#pragma once

#include "pointlight_entity.hpp"
#include "spotlight_entity.hpp"
#include "water_entity.hpp"
#include "shader_buffer.hpp"
#include "render_bus.hpp"

#include <unordered_map>

using std::unordered_map;

class WaterEntityColorRenderer final
{
public:
	void bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus);
	void unbind(shared_ptr<ShaderBuffer> shader);
	void processPointlightEntities(shared_ptr<ShaderBuffer> shader, const unordered_map<string, shared_ptr<PointlightEntity>>& entities);
	void processSpotlightEntities(shared_ptr<ShaderBuffer> shader, const unordered_map<string, shared_ptr<SpotlightEntity>>& entities);
	void render(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus, const shared_ptr<WaterEntity> entity);
};