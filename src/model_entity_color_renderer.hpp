#pragma once

#include "pointlight_entity.hpp"
#include "spotlight_entity.hpp"
#include "model_entity.hpp"
#include "reflection_entity.hpp"
#include "shader_buffer.hpp"
#include "render_bus.hpp"

#include <unordered_map>

using std::unordered_map;

class ModelEntityColorRenderer final
{
public:
	void bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus);
	void unbind(shared_ptr<ShaderBuffer> shader);
	void processPointlightEntities(shared_ptr<ShaderBuffer> shader, const unordered_map<string, shared_ptr<PointlightEntity>>& entities);
	void processSpotlightEntities(shared_ptr<ShaderBuffer> shader, const unordered_map<string, shared_ptr<SpotlightEntity>>& entities);
	void render(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus, const shared_ptr<ModelEntity> entity,
				const unordered_map<string, shared_ptr<ReflectionEntity>>& reflectionEntities);

private:
	static inline const float MIN_TEXTURE_TRANSPARENCY = 0.25f;
};