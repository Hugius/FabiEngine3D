#pragma once

#include "base_renderer.hpp"
#include "billboard_entity.hpp"

class BillboardEntityDepthRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(const shared_ptr<BillboardEntity> entity, float clippingY, bool isUnderWater);

private:
	static inline const float MIN_TEXTURE_TRANSPARENCY = 0.25f;
};