#pragma once
#include "base_entity_renderer.hpp"
#include "terrain_entity.hpp"

class TerrainEntityRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;
	~TerrainEntityRenderer() = default;
	
	void bind()    override;
	void unbind()  override;
	void placeLightEntity(const LightEntity * light);
	void render(const TerrainEntity * entity);

private:
	unsigned int _lightCounter = 0;
};