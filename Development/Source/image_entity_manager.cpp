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
			// Animation is playing
			if(entity->isSpriteAnimationStarted() && !entity->isSpriteAnimationPaused())
			{
				// Amount of loops not reached yet
				if(entity->getSpriteAnimationLoops() != entity->getMaxSpriteAnimationLoops())
				{
					// Animation not finished yet
					if(entity->getPassedSpriteAnimationFrames() >= entity->getMaxSpriteAnimationFramestep())
					{
						// Reset frame counter
						entity->resetPassedSpriteAnimationFrames();

						// Reached total columns
						if(entity->getSpriteAnimationColumnIndex() >= (entity->getTotalSpriteAnimationColumns() - 1))
						{
							// Reset column index
							entity->setSpriteAnimationColumnIndex(0);

							// Reached total rows
							if(entity->getSpriteAnimationRowIndex() >= (entity->getTotalSpriteAnimationRows() - 1))
							{
								// Reset row index (animation finished)
								entity->setSpriteAnimationRowIndex(0);
								entity->increaseSpriteAnimationLoops();
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
					else // Increase frame counter
					{
						entity->increasePassedSpriteAnimationFrames();
					}
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