#pragma once

#include "base_renderer.hpp"
#include "water_entity.hpp"

class WaterDepthRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(const shared_ptr<Water> entity);
};