#pragma once

#include "base_entity_manager.hpp"

class ImageEntityManager final : public BaseEntityManager
{
public:
	ImageEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus);
	~ImageEntityManager();

	shared_ptr<ImageEntity> getEntity(const string& ID);

	const unordered_map<string, shared_ptr<ImageEntity>>& getEntities();

	void addImageEntity(const string& ID, const string& texturePath, Vec2 position, float rotation, Vec2 size, bool engine, bool isCentered);
	void addImageEntity(const string& ID, Vec3 color, Vec2 position, float rotation, Vec2 size, bool isCentered);
	void update() override;
	void updateSpriteAnimations();

private:
	RenderBuffer* _centeredRenderBuffer = nullptr;
	RenderBuffer* _nonCenteredRenderBuffer = nullptr;
};