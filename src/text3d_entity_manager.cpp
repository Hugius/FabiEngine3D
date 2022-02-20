#include "text3d_entity_manager.hpp"
#include "render_storage.hpp"
#include "logger.hpp"

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
	_centeredMesh(make_shared<VertexBuffer>(VertexBufferType::POS_UV, centeredBufferData, centeredBufferDataCount)),
	_standingMesh(make_shared<VertexBuffer>(VertexBufferType::POS_UV, standingBufferData, standingBufferDataCount))
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

shared_ptr<Text3dEntity> Text3dEntityManager::getEntity(const string& id)
{
	auto iterator = _entities.find(id);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Text3dEntity>>& Text3dEntityManager::getEntities()
{
	return _entities;
}

void Text3dEntityManager::createEntity(const string& id, const string& fontMapPath, bool isCentered)
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

	_entities.insert(make_pair(id, entity));

	entity->setMesh(isCentered ? _centeredMesh : _standingMesh);
	entity->setCentered(isCentered);
	entity->setFontMap(_textureBufferCache->get2dBuffer(fontMapPath));
	entity->setFontMapPath(fontMapPath);
	entity->setContent("text");
}

void Text3dEntityManager::update()
{
	for(const auto& [key, entity] : _entities)
	{
		entity->updateTarget();

		if(!entity->isVisible())
		{
			continue;
		}

		const auto isFacingCameraHorizontally = entity->isFacingCameraHorizontally();
		const auto isFacingCameraVertically = entity->isFacingCameraVertically();

		if(isFacingCameraHorizontally || isFacingCameraVertically)
		{
			auto position = (entity->getPosition() + fvec3(0.0f, (entity->getSize().y * 0.5f), 0.0f));
			auto direction = (position - _camera->getPosition());

			auto degreesX = Math::convertToDegrees(atan2f(direction.y, fabsf(direction.x) + fabsf(direction.z)));
			auto degreesY = Math::convertToDegrees(atan2f(direction.z, direction.x));

			auto rotation = entity->getRotation();
			rotation.x = (degreesX * static_cast<float>(isFacingCameraHorizontally));
			rotation.y = ((-degreesY - 90.0f) * static_cast<float>(isFacingCameraVertically));

			entity->setRotation(rotation);
		}

		entity->updateCharacterEntities();
	}
}

void Text3dEntityManager::deleteEntity(const string& id)
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

const bool Text3dEntityManager::isEntityExisting(const string& id) const
{
	return (_entities.find(id) != _entities.end());
}

const bool Text3dEntityManager::isEntitiesExisting() const
{
	return !_entities.empty();
}