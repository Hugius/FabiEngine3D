#pragma once

#include "billboard_entity.hpp"
#include "shader_buffer.hpp"
#include "render_bus.hpp"

class BillboardEntityShadowRenderer final : BaseRenderer
{
public:
	void bind() override;
	void unbind() override;
	void render(const shared_ptr<BillboardEntity> entity);

private:
	static inline const float MIN_TEXTURE_TRANSPARENCY = 0.25f;
};