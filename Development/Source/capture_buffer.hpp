#pragma once

#include "mathematics.hpp"
#include "render_utils.hpp"

#include <vector>

using std::vector;

class CaptureBuffer final
{
public:
	~CaptureBuffer();

	void createColorTexture(Ivec2 position, Ivec2 size, unsigned int count, bool isTextureClamped);
	void createDepthTexture(Ivec2 position, Ivec2 size);
	void reset();

	void bind();
	void unbind();

	Ivec2 getSize();

	BufferID getFBO();
	TextureID getTexture(unsigned int index);

private:
	BufferID _fbo = 0;
	BufferID _rbo = 0;

	vector<TextureID> _textures;

	Ivec2 _position = Ivec2(0);
	Ivec2 _size = Ivec2(0);

	bool _isInitialized = false;
};