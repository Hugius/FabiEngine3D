#pragma once

#include "base_entity_renderer.hpp"
#include "image_entity.hpp"

class FinalRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;

	void bind()   override;
	void unbind() override;
	void render(const shared_ptr<ImageEntity> entity, GLuint sceneMap, GLuint motionblurMap);
};

