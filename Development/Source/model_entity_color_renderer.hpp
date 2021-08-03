#pragma once

#include "base_renderer.hpp"
#include "model_entity.hpp"
#include "light_entity.hpp"

class ModelEntityColorRenderer final : public BaseRenderer
{
public:
	using BaseRenderer::BaseRenderer;
	
	void bind()   override;
	void unbind() override;
	void renderLightEntities(const unordered_map<string, shared_ptr<LightEntity>>& entities);
	void render(const shared_ptr<ModelEntity> entity);
};