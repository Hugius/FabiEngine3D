#pragma once

#include "texture_buffer.hpp"

#include <map>

using std::map;

class TextureBufferCache final
{
public:
	void storeTextureBuffer(const string& ID, shared_ptr<TextureBuffer> textureBuffer);

	const shared_ptr<TextureBuffer> getTextureBuffer(const string& ID) const;

	const map<string, shared_ptr<TextureBuffer>>& getTextureBuffers() const;

private:
	map<string, shared_ptr<TextureBuffer>> _cache;
};