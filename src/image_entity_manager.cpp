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

		// Update sprite animation
		if(!isEnginePaused)
		{
			// Update sprite animations
			if(entity->isSpriteAnimationStarted() && !entity->isSpriteAnimationPaused() &&
			   (entity->getSpriteAnimationLoops() != entity->getMaxSpriteAnimationLoops()))
			{
				if(entity->getPassedSpriteAnimationFrames() >= entity->getSpriteAnimationFramestep()) // Is allowed to update
				{
					entity->resetPassedSpriteAnimationFrames(); // Reset counter

					if(entity->getSpriteAnimationColumnIndex() >= entity->getTotalSpriteAnimationColumnCount() - 1) // Reached column count
					{
						entity->setSpriteAnimationColumnIndex(0); // Reset column index

						if(entity->getSpriteAnimationRowIndex() >= entity->getTotalSpriteAnimationRowCount() - 1) // Reached row count
						{
							entity->increaseSpriteAnimationLoops();
							entity->setSpriteAnimationRowIndex(0); // Reset row index (animation finished)
						}
						else // Next row
						{
							entity->setSpriteAnimationRowIndex(entity->getSpriteAnimationRowIndex() + 1);
						}
					}
					else // Next column
					{
						entity->setSpriteAnimationColumnIndex(entity->getSpriteAnimationColumnIndex() + 1);
					}
				}
				else // Increase counter
				{
					entity->increasePassedSpriteAnimationFrames();
				}
			}
		}

		// Update transformation matrix
		if(entity->isVisible())
		{
			entity->updateTransformationMatrix();
		}
	}
}