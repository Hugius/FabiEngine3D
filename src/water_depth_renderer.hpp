#pragma once

#include "base_renderer.hpp"
#include "water.hpp"

class WaterDepthRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(shared_ptr<Water> water);
};