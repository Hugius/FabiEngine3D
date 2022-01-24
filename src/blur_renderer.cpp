#include "blur_renderer.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

using std::make_shared;

void BlurRenderer::inject(shared_ptr<CaptureBuffer> captor)
{
	_captor = captor;
}

void BlurRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_diffuseMap", 0);
}

void BlurRenderer::unbind()
{
	_shader->unbind();
}

const shared_ptr<TextureBuffer> BlurRenderer::blurTexture(const shared_ptr<Quad2dEntity> entity,
														  shared_ptr<TextureBuffer> texture, unsigned int blurCount,
														  float intensity, BlurDirection direction)
{
	_shader->uploadUniform("u_intensity", intensity);

	if((direction == BlurDirection::HORIZONTAL) || (direction == BlurDirection::BOTH))
	{
		_shader->uploadUniform("u_isHorizontal", true);

		for(unsigned int i = 0; i < blurCount; i++)
		{
			_captor->bind();
			_render(entity, texture);
			_captor->unbind();
			texture = _captor->getTexture(0);
		}
	}

	if((direction == BlurDirection::VERTICAL) || (direction == BlurDirection::BOTH))
	{
		_shader->uploadUniform("u_isHorizontal", false);

		for(unsigned int i = 0; i < blurCount; i++)
		{
			_captor->bind();
			_render(entity, texture);
			_captor->unbind();
			texture = _captor->getTexture(0);
		}
	}

	return texture;
}

void BlurRenderer::_render(const shared_ptr<Quad2dEntity> entity, shared_ptr<TextureBuffer> texture)
{
	const auto buffer = entity->getMesh();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getId());

	glBindVertexArray(buffer->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}