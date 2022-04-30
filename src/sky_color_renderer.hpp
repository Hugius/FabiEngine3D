#pragma once

#include "base_renderer.hpp"
#include "sky.hpp"

class SkyColorRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(const shared_ptr<Sky> sky);
};