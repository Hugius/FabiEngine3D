#pragma once

#include "base_renderer.hpp"
#include "billboard_entity.hpp"

class BillboardEntityColorRenderer final : public BaseRenderer
{
public:
	using BaseRenderer::BaseRenderer;

	void bind() override;
	void unbind() override;
	void render(const shared_ptr<BillboardEntity> entity);

private:
	static inline const float MIN_TEXTURE_TRANSPARENCY = 0.25f;
};