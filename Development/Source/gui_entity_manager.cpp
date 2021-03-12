#include "gui_entity_manager.hpp"
#include "logger.hpp"

GuiEntityManager::GuiEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(EntityType::GUI, meshLoader, texLoader, renderBus),
	_centeredOpenglBuffer(new OpenGLBuffer(0.0f, 0.0f, 1.0f, 1.0f, true, false)),
	_nonCenteredOpenglBuffer(new OpenGLBuffer(0.0f, 0.0f, 1.0f, 1.0f, false, false))
{
	
}

GuiEntityManager::~GuiEntityManager()
{
	delete _centeredOpenglBuffer;
	delete _nonCenteredOpenglBuffer;
}

shared_ptr<GuiEntity> GuiEntityManager::getEntity(const string& ID)
{
	auto result = _getGuiEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("Nonexisting GUI entity with ID \"" + ID + "\" requested");
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
	entity->addOglBuffer(isCentered ? _centeredOpenglBuffer : _nonCenteredOpenglBuffer, false);

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
	entity->addOglBuffer(isCentered ? _centeredOpenglBuffer : _nonCenteredOpenglBuffer, false);

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
		if (entity->hasSpriteAnimation() && entity->getAnimationRepeats() != entity->getMaxAnimationRepeats())
		{
			if (entity->getPassedFrames() >= entity->getMaxFramestep()) // Is allowed to update
			{
				entity->resetPassedFrames(); // Reset counter

				if (entity->getSpriteColumnIndex() >= entity->getTotalSpriteColumns() - 1) // Reached total columns
				{
					entity->setSpriteColumnIndex(0); // Reset column index

					if (entity->getSpriteRowIndex() >= entity->getTotalSpriteRows() - 1) // Reached total rows
					{
						entity->increaseAnimationRepeats();
						entity->setSpriteRowIndex(0); // Reset row index (animation finished)
					}
					else // Next row
					{
						entity->setSpriteRowIndex(entity->getSpriteRowIndex() + 1);
					}
				}
				else // Next column
				{
					entity->setSpriteColumnIndex(entity->getSpriteColumnIndex() + 1);
				}
			}
			else // Increase counter
			{
				entity->increasePassedFrames();
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