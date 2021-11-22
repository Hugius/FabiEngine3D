#pragma once

#include "base_entity_manager.hpp"

class ImageEntityManager final : public BaseEntityManager
{
public:
	ImageEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// VOID
	void update() override;
	void update(bool isEnginePaused);
	void createEntity(const string& ID, bool isCentered);

	// MISCELLANEOUS
	const unordered_map<string, shared_ptr<ImageEntity>>& getEntities();
	shared_ptr<ImageEntity> getEntity(const string& ID);

private:
	// MISCELLANEOUS
	const shared_ptr<RenderBuffer> _centeredRenderBuffer;
	const shared_ptr<RenderBuffer> _nonCenteredRenderBuffer;
};