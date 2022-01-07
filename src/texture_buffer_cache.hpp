#pragma once

#include "texture_buffer.hpp"

#include <map>

using std::map;

class TextureBufferCache final
{
public:
	void storeTextureBuffer(const string& filePath, shared_ptr<TextureBuffer> textureBuffer);

	const shared_ptr<TextureBuffer> getTextureBuffer(const string& filePath) const;

	const map<string, shared_ptr<TextureBuffer>>& getTextureBuffers() const;

private:
	map<string, shared_ptr<TextureBuffer>> _cache;
};