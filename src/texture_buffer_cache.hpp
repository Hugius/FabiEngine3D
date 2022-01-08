#pragma once

#include "texture_buffer.hpp"

#include <map>
#include <vector>

using std::map;
using std::vector;

class TextureBufferCache final
{
public:
	void store2dBuffer(const string& filePath, shared_ptr<TextureBuffer> buffer);
	void store3dBuffer(const array<string, 6>& filePaths, shared_ptr<TextureBuffer> buffer);
	void delete2dBuffer(const string& filePath);
	void delete3dBuffer(const array<string, 6>& filePaths);
	void clear2dBuffers();
	void clear3dBuffers();

	const shared_ptr<TextureBuffer> get2dBuffer(const string& filePath) const;
	const shared_ptr<TextureBuffer> get3dBuffer(const array<string, 6>& filePath) const;

	const map<string, shared_ptr<TextureBuffer>>& get2dBuffers() const;
	const map<array<string, 6>, shared_ptr<TextureBuffer>>& get3dBuffers() const;

private:
	map<string, shared_ptr<TextureBuffer>> _2dBuffers;
	map<array<string, 6>, shared_ptr<TextureBuffer>> _3dBuffers;
};