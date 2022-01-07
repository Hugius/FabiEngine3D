#pragma once

#include "texture_buffer.hpp"

#include <map>
#include <vector>

using std::map;
using std::vector;

class TextureBufferCache final
{
public:
	void storeBuffer(const string& filePath, shared_ptr<TextureBuffer> buffer);
	void storeBuffer(const array<string, 6>& filePaths, shared_ptr<TextureBuffer> buffer);

	const shared_ptr<TextureBuffer> getBuffer(const string& filePath) const;
	const shared_ptr<TextureBuffer> getBuffer(const array<string, 6>& filePath) const;

	const vector<shared_ptr<TextureBuffer>> getBuffers() const;

private:
	map<string, shared_ptr<TextureBuffer>> _2dBuffers;
	map<array<string, 6>, shared_ptr<TextureBuffer>> _3dBuffers;
};