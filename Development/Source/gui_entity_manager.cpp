#include "gui_entity_manager.hpp"
#include "logger.hpp"

GuiEntityManager::GuiEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(EntityType::GUI, meshLoader, texLoader, renderBus),
	_centeredRenderBuffer(new RenderBuffer(0.0f, 0.0f, 1.0f, 1.0f, true, false)),
	_nonCenteredRenderBuffer(new RenderBuffer(0.0f, 0.0f, 1.0f, 1.0f, false, false))
{
	
}

GuiEntityManager::~GuiEntityManager()
{
	delete _centeredRenderBuffer;
	delete _nonCenteredRenderBuffer;
}

shared_ptr<GuiEntity> GuiEntityManager::getEntity(const string& ID)
{
	auto result = _getGuiEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("Non-existing gui entity with ID \"" + ID + "\" requested");
	}

	return result;
}

const unordered_map<string, shared_ptr<GuiEntity>>& GuiEntityManager::getEntities()
{
	return _getGuiEntities();
}

void GuiEntityManager::addGuiEntity(const string& ID, const string& texturePath, Vec2 translation, float rotation, Vec2 scaling, bool engine, bool isCentered)
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

void GuiEntityManager::addGuiEntity(const string& ID, Vec3 color, Vec2 translation, float rotation, Vec2 scaling, bool isCentered)
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

void GuiEntityManager::updateSpriteAnimations()
{
	for (auto& [keyID, entity] : _getGuiEntities())
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

void GuiEntityManager::update()
{
	for (auto& [keyID, entity] : _getGuiEntities())
	{
		// Calculate model matrix
		if (entity->isVisible())
		{
			entity->updateModelMatrix();
		}
	}
}