#include "image_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

ImageEntityManager::ImageEntityManager(RenderBus& renderBus)
	:
	_renderBus(renderBus),
	_centeredRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 1.0f, 1.0f, true)),
	_corneredRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 1.0f, 1.0f, false))
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
	_entities.insert(make_pair(ID, make_shared<ImageEntity>(ID)));
	getEntity(ID)->setRenderBuffer(isCentered ? _centeredRenderBuffer : _corneredRenderBuffer);
	getEntity(ID)->setCentered(isCentered);
	getEntity(ID)->setDepth(_renderBus.getGuiDepth());
	_renderBus.setGuiDepth(_renderBus.getGuiDepth() + 1);
}

void ImageEntityManager::deleteEntity(const string& ID)
{
	if(!isEntityExisting(ID))
	{
		Logger::throwError("ImageEntityManager::deleteEntity");
	}

	_entities.erase(ID);
}

void ImageEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool ImageEntityManager::isEntityExisting(const string& ID)
{
	return (_entities.find(ID) != _entities.end());
}

void ImageEntityManager::update()
{
	for(const auto& [keyID, entity] : _entities)
	{
		entity->updateTransformation();

		if(entity->isVisible())
		{
			entity->updateTransformationMatrix();
		}
	}
}