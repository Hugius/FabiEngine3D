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

	const BufferID getFbo() const;
	const BufferID getRbo() const;

	const shared_ptr<TextureBuffer> getTexture(unsigned int index) const;

private:
	ivec2 _position = ivec2(0);
	ivec2 _size = ivec2(0);

	vector<shared_ptr<TextureBuffer>> _textures;

	BufferID _fbo = 0;
	BufferID _rbo = 0;
};