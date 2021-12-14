#include "image_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

ImageEntityManager::ImageEntityManager()
	:
	_centeredRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 1.0f, 1.0f, true)),
	_nonCenteredRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 1.0f, 1.0f, false))
{

}

shared_ptr<ImageEntity> ImageEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

	if(iterator == _entities.end())
	{
		Logger::throwError("ImageEntityManager::getEntity");
	}
	else
	{
		return iterator->second;
	}
}

const unordered_map<string, shared_ptr<ImageEntity>>& ImageEntityManager::getEntities()
{
	return _entities;
}

void ImageEntityManager::createEntity(const string& ID, bool isCentered)
{
	_getTextEntity(ID)->setDepth(_guiDepth);
	_guiDepth++;
	_createEntity(ID);
	getEntity(ID)->setRenderBuffer(isCentered ? _centeredRenderBuffer : _nonCenteredRenderBuffer);
	getEntity(ID)->setCentered(isCentered);
}

void ImageEntityManager::update()
{
	for(const auto& [keyID, entity] : _entities)
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