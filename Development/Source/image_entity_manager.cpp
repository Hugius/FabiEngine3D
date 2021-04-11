#include "image_entity_manager.hpp"
#include "logger.hpp"

ImageEntityManager::ImageEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(EntityType::IMAGE, meshLoader, texLoader, renderBus),
	_centeredRenderBuffer(new RenderBuffer(0.0f, 0.0f, 1.0f, 1.0f, true, false)),
	_nonCenteredRenderBuffer(new RenderBuffer(0.0f, 0.0f, 1.0f, 1.0f, false, false))
{
	
}

ImageEntityManager::~ImageEntityManager()
{
	delete _centeredRenderBuffer;
	delete _nonCenteredRenderBuffer;
}

shared_ptr<ImageEntity> ImageEntityManager::getEntity(const string& ID)
{
	auto result = _getImageEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("Non-existing image entity with ID \"" + ID + "\" requested");
	}

	return result;
}

const unordered_map<string, shared_ptr<ImageEntity>>& ImageEntityManager::getEntities()
{
	return _getImageEntities();
}

void ImageEntityManager::addImageEntity(const string& ID, const string& texturePath, Vec2 translation, float rotation, Vec2 scaling, bool engine, bool isCentered)
{
	// Create entity
	_createEntity(ID);
	auto entity = getEntity(ID);
	entity->addRenderBuffer(isCentered ? _centeredRenderBuffer : _nonCenteredRenderBuffer, false);

	// Load transformation
	entity->setTranslation(translation);
	entity->setRotation(rotation);
	entity->setScaling(scaling);
	entity->setCentered(isCentered);

	// Load diffuse map
	entity->setTexture(_textureLoader.getTexture2D(texturePath, true, false, false));
}

void ImageEntityManager::addImageEntity(const string& ID, Vec3 color, Vec2 translation, float rotation, Vec2 scaling, bool isCentered)
{
	// Create entity
	_createEntity(ID);
	auto entity = getEntity(ID);
	entity->addRenderBuffer(isCentered ? _centeredRenderBuffer : _nonCenteredRenderBuffer, false);

	// Load transformation
	entity->setTranslation(translation);
	entity->setRotation(rotation);
	entity->setScaling(scaling);
	entity->setCentered(isCentered);

	// Set color
	entity->setColor(color);
}

void ImageEntityManager::updateSpriteAnimations()
{
	for (auto& [keyID, entity] : _getImageEntities())
	{
		if (entity->isSpriteAnimationPlaying() && !entity->isSpriteAnimationPaused() &&
			entity->getSpriteAnimationRepeats() != entity->getMaxSpriteAnimationRepeats())
		{
			if (entity->getPassedSpriteAnimationFrames() >= entity->getMaxSpriteAnimationFramestep()) // Is allowed to update
			{
				entity->resetPassedSpriteAnimationFrames(); // Reset counter

				if (entity->getSpriteAnimationColumnIndex() >= entity->getTotalSpriteAnimationColumns() - 1) // Reached total columns
				{
					entity->setSpriteAnimationColumnIndex(0); // Reset column index

					if (entity->getSpriteAnimationRowIndex() >= entity->getTotalSpriteAnimationRows() - 1) // Reached total rows
					{
						entity->increaseSpriteAnimationRepeats();
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
}

void ImageEntityManager::update()
{
	for (auto& [keyID, entity] : _getImageEntities())
	{
		// Calculate model matrix
		if (entity->isVisible())
		{
			entity->updateModelMatrix();
		}
	}
}