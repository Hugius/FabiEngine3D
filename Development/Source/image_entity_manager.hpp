#pragma once

#include "base_entity_manager.hpp"

class ImageEntityManager final : public BaseEntityManager
{
public:
	ImageEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	shared_ptr<ImageEntity> getEntity(const string& ID);

	const unordered_map<string, shared_ptr<ImageEntity>>& getEntities();

	void createEntity(const string& ID, bool isCentered);
	void update() override;
	void updateSpriteAnimations();

private:
	const shared_ptr<RenderBuffer> _centeredRenderBuffer;
	const shared_ptr<RenderBuffer> _nonCenteredRenderBuffer;
};