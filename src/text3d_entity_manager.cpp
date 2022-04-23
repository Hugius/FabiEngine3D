#include "text3d_entity_manager.hpp"
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

constexpr unsigned int centeredBufferDataCount = static_cast<unsigned int>(sizeof(centeredBufferData) / sizeof(float));
constexpr unsigned int standingBufferDataCount = static_cast<unsigned int>(sizeof(standingBufferData) / sizeof(float));

Text3dEntityManager::Text3dEntityManager()
	:
	_centeredVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS_UV, centeredBufferData, centeredBufferDataCount)),
	_standingVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS_UV, standingBufferData, standingBufferDataCount))
{

}

void Text3dEntityManager::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

void Text3dEntityManager::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

void Text3dEntityManager::inject(shared_ptr<ImageLoader> imageLoader)
{
	_imageLoader = imageLoader;
}

void Text3dEntityManager::inject(shared_ptr<TextureBufferCache> textureBufferCache)
{
	_textureBufferCache = textureBufferCache;
}

const shared_ptr<Text3dEntity> Text3dEntityManager::getEntity(const string & id) const
{
	auto iterator = _entities.find(id);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Text3dEntity>> & Text3dEntityManager::getEntities() const
{
	return _entities;
}

void Text3dEntityManager::createEntity(const string & id, const string & fontMapPath, bool isCentered)
{
	if(isEntityExisting(id))
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

	auto entity = make_shared<Text3dEntity>(id);

	entity->setVertexBuffer(isCentered ? _centeredVertexBuffer : _standingVertexBuffer);
	entity->setCentered(isCentered);
	entity->setFontMap(_textureBufferCache->get2dBuffer(fontMapPath));
	entity->setFontMapPath(fontMapPath);
	entity->setContent("text");

	_entities.insert({id, entity});
}

void Text3dEntityManager::update()
{
	for(const auto & [entityId, entity] : _entities)
	{
		entity->updateTarget();

		if(entity->isFacingCameraHorizontally() || entity->isFacingCameraVertically())
		{
			auto position = (entity->getPosition() + fvec3(0.0f, (entity->getSize().y * 0.5f), 0.0f));
			auto direction = (position - _camera->getPosition());

			auto degreesX = Mathematics::convertToDegrees(atan2f(direction.y, fabsf(direction.x) + fabsf(direction.z)));
			auto degreesY = Mathematics::convertToDegrees(atan2f(direction.z, direction.x));

			auto rotation = entity->getRotation();
			rotation.x = (degreesX * static_cast<float>(entity->isFacingCameraHorizontally()));
			rotation.y = ((-degreesY - 90.0f) * static_cast<float>(entity->isFacingCameraVertically()));

			entity->setRotation(rotation);
		}

		if(entity->isVisible())
		{
			entity->updateCharacterEntities();
		}
	}
}

void Text3dEntityManager::deleteEntity(const string & id)
{
	if(!isEntityExisting(id))
	{
		abort();
	}

	_entities.erase(id);
}

void Text3dEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool Text3dEntityManager::isEntityExisting(const string & id) const
{
	return (_entities.find(id) != _entities.end());
}

const bool Text3dEntityManager::isEntitiesExisting() const
{
	return !_entities.empty();
}