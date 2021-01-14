#pragma once

#include "base_entity_renderer.hpp"
#include "sky_entity.hpp"

class SkyEntityRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;
	~SkyEntityRenderer() = default;

	void bind()   override;
	void unbind() override;
	void render(const shared_ptr<SkyEntity> first, const shared_ptr<SkyEntity> second);
};