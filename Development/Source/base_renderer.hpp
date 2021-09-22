#pragma once

#include "base_entity.hpp"
#include "shader_buffer.hpp"
#include "sky_entity.hpp"
#include "terrain_entity.hpp"
#include "water_entity.hpp"
#include "light_entity.hpp"
#include "model_entity.hpp"
#include "image_entity.hpp"
#include "render_bus.hpp"

#include <memory>
#include <unordered_map>

using std::shared_ptr;
using std::unordered_map;

class BaseRenderer
{
public:
	BaseRenderer(const string& vertexFile, const string& fragmentFile, RenderBus& renderBus);

	virtual void bind()   = 0;
	virtual void unbind() = 0;

protected:
	ShaderBuffer _shader;

	RenderBus& _renderBus;

	static inline const float MIN_TEXTURE_ALPHA = 0.25f;
};