#pragma once

#include "base_entity_manager.hpp"
#include "image_loader.hpp"
#include "text2d_entity.hpp"
#include "texture_buffer_cache.hpp"
#include "image_loader.hpp"

#include <unordered_map>

using std::unordered_map;

class Text2dEntityManager final : public BaseEntityManager
{
public:
	Text2dEntityManager();

	void inject(shared_ptr<RenderStorage> renderStorage);
	void inject(shared_ptr<ImageLoader> imageLoader);
	void inject(shared_ptr<TextureBufferCache> textureBufferCache);
	void update();
	void createEntity(const string& id, const string& fontMapPath, bool isCentered);
	void deleteEntity(const string& id);
	void deleteEntities();

	const bool isEntityExisting(const string& id) const;

	const unordered_map<string, shared_ptr<Text2dEntity>>& getEntities();
	shared_ptr<Text2dEntity> getEntity(const string& id);

private:
	const shared_ptr<VertexBuffer> _centeredMesh;
	const shared_ptr<VertexBuffer> _corneredMesh;

	unordered_map<string, shared_ptr<Text2dEntity>> _entities;

	shared_ptr<RenderStorage> _renderStorage = nullptr;
	shared_ptr<ImageLoader> _imageLoader = nullptr;
	shared_ptr<TextureBufferCache> _textureBufferCache = nullptr;
};