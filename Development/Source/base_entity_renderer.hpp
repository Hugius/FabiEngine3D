#pragma once

#include "base_entity.hpp"
#include "render_shader.hpp"
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

class BaseEntityRenderer
{
public:
	BaseEntityRenderer(const string& vertexFile, const string& fragmentFile, RenderBus& renderBus);
	virtual ~BaseEntityRenderer() = default;

	virtual void bind()   = 0;
	virtual void unbind() = 0;

protected:
	RenderShader _shader;

	RenderBus& _renderBus;
};