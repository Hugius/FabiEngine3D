#pragma once

#include "mathematics.hpp"
#include "render_utils.hpp"
#include "texture_buffer.hpp"

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

	const BufferID getFbo() const;

	const shared_ptr<TextureBuffer> getTexture(unsigned int index) const;

private:
	ivec2 _position = ivec2(0);
	ivec2 _size = ivec2(0);

	bool _isInitialized = false;

	vector<shared_ptr<TextureBuffer>> _textures;

	BufferID _fbo = 0;
	BufferID _rbo = 0;
};