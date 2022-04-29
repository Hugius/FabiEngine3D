#pragma once

#include "image_loader.hpp"
#include "text2d_entity.hpp"
#include "texture_buffer_cache.hpp"
#include "image_loader.hpp"
#include "render_storage.hpp"

#include <unordered_map>

using std::unordered_map;

class Text2dManager final
{
public:
	Text2dManager();

	void inject(shared_ptr<RenderStorage> renderStorage);
	void inject(shared_ptr<ImageLoader> imageLoader);
	void inject(shared_ptr<TextureBufferCache> textureBufferCache);
	void update();
	void createEntity(const string & text2dId, const string & fontMapPath, bool isCentered);
	void deleteEntity(const string & text2dId);
	void deleteEntities();

	const unordered_map<string, shared_ptr<Text2d>> & getEntities() const;

	const shared_ptr<Text2d> getEntity(const string & text2dId) const;

	const bool isEntityExisting(const string & text2dId) const;
	const bool isEntitiesExisting() const;

private:
	const shared_ptr<VertexBuffer> _centeredVertexBuffer;
	const shared_ptr<VertexBuffer> _corneredVertexBuffer;

	unordered_map<string, shared_ptr<Text2d>> _entities = {};

	shared_ptr<RenderStorage> _renderStorage = nullptr;
	shared_ptr<ImageLoader> _imageLoader = nullptr;
	shared_ptr<TextureBufferCache> _textureBufferCache = nullptr;
};