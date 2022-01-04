#pragma once

#include "capture_buffer.hpp"
#include "shader_buffer.hpp"
#include "texture_buffer.hpp"
#include "vertex_buffer.hpp"

class BufferManager final
{
public:


private:
	map<string, shared_ptr<CaptureBuffer>> _captureBuffers;
	map<string, shared_ptr<ShaderBuffer>> _shaderBuffers;
	map<string, shared_ptr<TextureBuffer>> _textureBuffers;
	map<string, shared_ptr<VertexBuffer>> _vertexBuffers;
};