#include "image_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

ImageEntityManager::ImageEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus)
	:
	BaseEntityManager(EntityType::IMAGE, meshLoader, textureLoader, renderBus),
	_centeredRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 1.0f, 1.0f, true)),
	_nonCenteredRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 1.0f, 1.0f, false))
{

}

shared_ptr<ImageEntity> ImageEntityManager::getEntity(const string& ID)
{
	auto result = _getImageEntity(ID);

	if(result == nullptr)
	{
		Logger::throwError("ImageEntityManager::getEntity");
	}

	return result;
}

const unordered_map<string, shared_ptr<ImageEntity>>& ImageEntityManager::getEntities()
{
	return _getImageEntities();
}

void ImageEntityManager::createEntity(const string& ID, bool isCentered)
{
	_createEntity(ID);
	getEntity(ID)->setRenderBuffer(isCentered ? _centeredRenderBuffer : _nonCenteredRenderBuffer);
	getEntity(ID)->setCentered(isCentered);
}

void ImageEntityManager::update()
{
	Logger::throwError("ImageEntityManager::update");
}

void ImageEntityManager::update(bool isEnginePaused)
{
	for(const auto& [keyID, entity] : _getImageEntities())
	{
		// Update transformation
		entity->updateTransformation();

		// Update transformation matrix
		if(entity->isVisible())
		{
			entity->updateTransformationMatrix();
		}
	}
}