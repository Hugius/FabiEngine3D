#pragma once

#include "mathematics.hpp"
#include "render_utils.hpp"

#include <vector>

using std::vector;

class CaptureBuffer final
{
public:
	~CaptureBuffer();

	// Voids
	void createColorTexture(Ivec2 position, Ivec2 size, unsigned int count, bool isTextureClamped);
	void createDepthTexture(Ivec2 position, Ivec2 size);
	void reset();
	void bind();
	void unbind();

	// Vectors
	Ivec2 getSize();

	// Miscellaneous
	BufferID getFBO();
	TextureID getTexture(unsigned int index);

private:
	// Vectors
	Ivec2 _position = Ivec2(0);
	Ivec2 _size = Ivec2(0);

	// Booleans
	bool _isInitialized = false;

	// Miscellaneous
	vector<TextureID> _textures;
	BufferID _fbo = 0;
	BufferID _rbo = 0;
};