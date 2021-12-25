#pragma once

#include "mathematics.hpp"
#include "render_utils.hpp"

#include <vector>

using std::vector;

class CaptureBuffer final
{
public:
	~CaptureBuffer();

	void createColorTexture(ivec2 position, ivec2 size, unsigned int count, bool isTextureClamped);
	void createDepthTexture(ivec2 position, ivec2 size);
	void reset();
	void bind();
	void unbind();

	const ivec2 getSize() const;

	const BufferID getFBO() const;
	const TextureID getTexture(unsigned int index) const;

private:
	ivec2 _position = ivec2(0);
	ivec2 _size = ivec2(0);

	bool _isInitialized = false;

	vector<TextureID> _textures;
	BufferID _fbo = 0;
	BufferID _rbo = 0;
};