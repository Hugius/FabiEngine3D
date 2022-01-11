#pragma once

#include "base_renderer.hpp"
#include "sky_entity.hpp"

class SkyEntityColorRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(const shared_ptr<SkyEntity> first, const shared_ptr<SkyEntity> second);
};