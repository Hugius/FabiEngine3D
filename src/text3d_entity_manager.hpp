#pragma once

#include "camera.hpp"
#include "text3d_entity.hpp"
#include "texture_buffer_cache.hpp"
#include "image_loader.hpp"
#include "render_storage.hpp"

#include <unordered_map>

using std::unordered_map;

class Text3dManager final
{
public:
	Text3dManager();

	void inject(shared_ptr<RenderStorage> renderStorage);
	void inject(shared_ptr<Camera> camera);
	void inject(shared_ptr<ImageLoader> imageLoader);
	void inject(shared_ptr<TextureBufferCache> textureBufferCache);
	void update();
	void createText3d(const string & text3dId, const string & fontMapPath, bool isCentered);
	void deleteText3d(const string & text3dId);
	void deleteText3ds();

	const unordered_map<string, shared_ptr<Text3d>> & getText3ds() const;

	const shared_ptr<Text3d> getText3d(const string & text3dId) const;

	const bool isText3dExisting(const string & text3dId) const;
	const bool isText3dsExisting() const;

private:
	const shared_ptr<VertexBuffer> _centeredVertexBuffer;
	const shared_ptr<VertexBuffer> _standingVertexBuffer;

	unordered_map<string, shared_ptr<Text3d>> _text3ds = {};

	shared_ptr<RenderStorage> _renderStorage = nullptr;
	shared_ptr<Camera> _camera = nullptr;
	shared_ptr<ImageLoader> _imageLoader = nullptr;
	shared_ptr<TextureBufferCache> _textureBufferCache = nullptr;
};