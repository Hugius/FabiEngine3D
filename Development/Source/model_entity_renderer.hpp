#pragma once

#include "base_entity_renderer.hpp"
#include "model_entity.hpp"
#include "light_entity.hpp"

class ModelEntityRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;
	~ModelEntityRenderer() = default;
	
	void bind()   override;
	void unbind() override;
	void renderLightEntities(const unordered_map<string, shared_ptr<LightEntity>>& entities);
	void render(const shared_ptr<ModelEntity> entity);
};