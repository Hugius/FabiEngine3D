#include "text3d_manager.hpp"
#include "render_storage.hpp"

using std::make_shared;

constexpr float centeredBufferData[] =
{
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
};

constexpr float standingBufferData[] =
{
	-0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
	-0.5f, 1.0f, 0.0f, 0.0f, 1.0f
};

constexpr int centeredBufferDataCount = static_cast<int>(sizeof(centeredBufferData) / sizeof(float));
constexpr int standingBufferDataCount = static_cast<int>(sizeof(standingBufferData) / sizeof(float));

Text3dManager::Text3dManager()
	:
	_centeredVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS_UV, centeredBufferData, centeredBufferDataCount)),
	_standingVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS_UV, standingBufferData, standingBufferDataCount))
{

}

void Text3dManager::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

void Text3dManager::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

void Text3dManager::inject(shared_ptr<ImageLoader> imageLoader)
{
	_imageLoader = imageLoader;
}

void Text3dManager::inject(shared_ptr<TextureBufferCache> textureBufferCache)
{
	_textureBufferCache = textureBufferCache;
}

const shared_ptr<Text3d> Text3dManager::getText3d(const string & text3dId) const
{
	auto iterator = _text3ds.find(text3dId);

	if(iterator == _text3ds.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Text3d>> & Text3dManager::getText3ds() const
{
	return _text3ds;
}

void Text3dManager::createText3d(const string & text3dId, const string & fontMapPath, bool isCentered)
{
	if(isText3dExisting(text3dId))
	{
		abort();
	}

	auto texture = _textureBufferCache->get2dBuffer(fontMapPath);

	if(texture == nullptr)
	{
		auto image = _imageLoader->loadImage(fontMapPath);

		if(image == nullptr)
		{
			return;
		}

		texture = make_shared<TextureBuffer>(image);
		texture->loadAnisotropicFiltering(_renderStorage->getAnisotropicFilteringQuality());

		_textureBufferCache->store2dBuffer(fontMapPath, texture);
	}

	auto text3d = make_shared<Text3d>(text3dId);

	text3d->setVertexBuffer(isCentered ? _centeredVertexBuffer : _standingVertexBuffer);
	text3d->setCentered(isCentered);
	text3d->setFontMap(_textureBufferCache->get2dBuffer(fontMapPath));
	text3d->setFontMapPath(fontMapPath);
	text3d->setContent("text");

	_text3ds.insert({text3dId, text3d});
}

void Text3dManager::update()
{
	for(const auto & [text3dId, text3d] : _text3ds)
	{
		text3d->updateTarget();

		if(text3d->isFacingCameraHorizontally() || text3d->isFacingCameraVertically())
		{
			auto position = (text3d->getPosition() + fvec3(0.0f, (text3d->getSize().y * 0.5f), 0.0f));
			auto direction = (position - _camera->getPosition());

			auto degreesX = Mathematics::convertToDegrees(atan2f(direction.y, fabsf(direction.x) + fabsf(direction.z)));
			auto degreesY = Mathematics::convertToDegrees(atan2f(direction.z, direction.x));

			auto rotation = text3d->getRotation();
			rotation.x = (degreesX * static_cast<float>(text3d->isFacingCameraHorizontally()));
			rotation.y = ((-degreesY - 90.0f) * static_cast<float>(text3d->isFacingCameraVertically()));

			text3d->setRotation(rotation);
		}

		if(text3d->isVisible())
		{
			text3d->updateQuad3ds();
		}
	}
}

void Text3dManager::deleteText3d(const string & text3dId)
{
	if(!isText3dExisting(text3dId))
	{
		abort();
	}

	_text3ds.erase(text3dId);
}

void Text3dManager::deleteText3ds()
{
	_text3ds.clear();
}

const bool Text3dManager::isText3dExisting(const string & text3dId) const
{
	return (_text3ds.find(text3dId) != _text3ds.end());
}

const bool Text3dManager::isText3dsExisting() const
{
	return !_text3ds.empty();
}