#pragma once

#include "base_renderer.hpp"
#include "quad_entity.hpp"

class MotionBlurRenderer final : public BaseRenderer
{
public:
	void bind() override;
	void unbind() override;
	void render(const shared_ptr<QuadEntity> entity);
};