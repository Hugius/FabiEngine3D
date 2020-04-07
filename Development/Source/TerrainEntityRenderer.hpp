#pragma once
#include "EntityRenderer.hpp"
#include "TerrainEntity.hpp"

class TerrainEntityRenderer final : public EntityRenderer
{
public:
	using EntityRenderer::EntityRenderer;
	~TerrainEntityRenderer() = default;
	
	void bind()    override;
	void unbind()  override;
	void placeLightEntity(const LightEntity * light);
	void render(const TerrainEntity * entity);

private:
	unsigned int p_lightCounter = 0;
};