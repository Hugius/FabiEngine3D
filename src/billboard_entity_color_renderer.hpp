#pragma once

#include "billboard_entity.hpp"
#include "render_bus.hpp"
#include "shader_buffer.hpp"

class BillboardEntityColorRenderer final
{
public:
	void bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus);
	void unbind(shared_ptr<ShaderBuffer> shader);
	void render(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus, const shared_ptr<BillboardEntity> entity);

private:
	static inline const float MIN_TEXTURE_TRANSPARENCY = 0.25f;
};