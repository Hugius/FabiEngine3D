#pragma once

#include "billboard_entity.hpp"
#include "shader_buffer.hpp"
#include "render_bus.hpp"

class BillboardEntityDepthRenderer final
{
public:
	void bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus);
	void unbind(shared_ptr<ShaderBuffer> shader);
	void render(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus, const shared_ptr<BillboardEntity> entity, float clippingY, bool isUnderWater);

private:
	static inline const float MIN_TEXTURE_TRANSPARENCY = 0.25f;
};