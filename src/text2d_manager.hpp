#pragma once

#include "image_loader.hpp"
#include "text2d.hpp"
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
	void createText2d(const string & text2dId, const string & fontMapPath, bool isCentered);
	void deleteText2d(const string & text2dId);
	void deleteText2ds();

	const unordered_map<string, shared_ptr<Text2d>> & getText2ds() const;

	const shared_ptr<Text2d> getText2d(const string & text2dId) const;

	const bool isText2dExisting(const string & text2dId) const;
	const bool isText2dsExisting() const;

private:
	const shared_ptr<VertexBuffer> _centeredVertexBuffer;
	const shared_ptr<VertexBuffer> _corneredVertexBuffer;

	unordered_map<string, shared_ptr<Text2d>> _text2ds = {};

	shared_ptr<RenderStorage> _renderStorage = nullptr;
	shared_ptr<ImageLoader> _imageLoader = nullptr;
	shared_ptr<TextureBufferCache> _textureBufferCache = nullptr;
};