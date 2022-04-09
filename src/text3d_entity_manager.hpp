#pragma once

#include "camera.hpp"
#include "text3d_entity.hpp"
#include "texture_buffer_cache.hpp"
#include "image_loader.hpp"
#include "render_storage.hpp"

#include <unordered_map>

using std::unordered_map;

class Text3dEntityManager final
{
public:
	Text3dEntityManager();

	void inject(shared_ptr<RenderStorage> renderStorage);
	void inject(shared_ptr<Camera> camera);
	void inject(shared_ptr<ImageLoader> imageLoader);
	void inject(shared_ptr<TextureBufferCache> textureBufferCache);
	void update();
	void createEntity(const string & id, const string & fontMapPath, bool isCentered);
	void deleteEntity(const string & id);
	void deleteEntities();

	const unordered_map<string, shared_ptr<Text3dEntity>> & getEntities() const;

	const shared_ptr<Text3dEntity> getEntity(const string & id) const;

	const bool isEntityExisting(const string & id) const;
	const bool isEntitiesExisting() const;

private:
	const shared_ptr<VertexBuffer> _centeredVertexBuffer;
	const shared_ptr<VertexBuffer> _standingVertexBuffer;

	unordered_map<string, shared_ptr<Text3dEntity>> _entities = {};

	shared_ptr<RenderStorage> _renderStorage = nullptr;
	shared_ptr<Camera> _camera = nullptr;
	shared_ptr<ImageLoader> _imageLoader = nullptr;
	shared_ptr<TextureBufferCache> _textureBufferCache = nullptr;
};