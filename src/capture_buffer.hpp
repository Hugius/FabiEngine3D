#pragma once

#include "mathematics.hpp"
#include "texture_buffer.hpp"

#include <vector>

using std::vector;

class CaptureBuffer final
{
public:
	CaptureBuffer(const ivec2 & position, const ivec2 & size, int count, bool isTextureClamped); // Color
	CaptureBuffer(const ivec2 & position, const ivec2 & size); // Depth
	~CaptureBuffer();

	void bind();
	void unbind();

	const shared_ptr<TextureBuffer> getTexture(int index) const;

	const ivec2 & getPosition() const;
	const ivec2 & getSize() const;

	const unsigned int getFboId() const;
	const unsigned int getRboId() const;

private:
	static inline constexpr float DEPTH_BORDER_COLOR[] = {1.0f, 1.0f, 1.0f, 1.0f};

	vector<shared_ptr<TextureBuffer>> _textures = {};

	ivec2 _position = ivec2(0);
	ivec2 _size = ivec2(0);

	unsigned int _fboId = 0;
	unsigned int _rboId = 0;
};