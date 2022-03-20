#pragma once

#include "mathematics.hpp"
#include "texture_buffer.hpp"

#include <vector>

using std::vector;

class CaptureBuffer final
{
public:
	CaptureBuffer(const ivec2& position, const ivec2& size, unsigned int count, bool isTextureClamped);
	CaptureBuffer(const ivec2& position, const ivec2& size);
	~CaptureBuffer();

	void bind();
	void unbind();

	const ivec2& getPosition() const;
	const ivec2& getSize() const;

	const unsigned int getFbo() const;
	const unsigned int getRbo() const;

	const shared_ptr<TextureBuffer> getTexture(unsigned int index) const;

private:
	vector<shared_ptr<TextureBuffer>> _textures = {};

	ivec2 _position = ivec2(0);
	ivec2 _size = ivec2(0);

	unsigned int _fbo = 0;
	unsigned int _rbo = 0;
};