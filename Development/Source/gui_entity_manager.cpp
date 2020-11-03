#include "gui_entity_manager.hpp"
#include "logger.hpp"

#include <iostream>

GuiEntityManager::GuiEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(EntityType::GUI, objLoader, texLoader, renderBus),
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
		Logger::throwError("Nonexisting GUI entity with ID " + ID + " requested");
	}

	return result;
}

const vector<shared_ptr<GuiEntity>> GuiEntityManager::getEntities()
{
	return _getGuiEntities();
}

void GuiEntityManager::addGuiEntity(const string& ID, const string& texturePath, vec2 translation, float rotation, vec2 scaling, bool engine, bool isCentered)
{
	// Create entity
	_createEntity(ID);
	getEntity(ID)->addOglBuffer(isCentered ? _centeredOpenglBuffer : _nonCenteredOpenglBuffer, false);

	// Load transformation
	getEntity(ID)->setTranslation(translation);
	getEntity(ID)->setRotation(rotation);
	getEntity(ID)->setScaling(scaling);
	getEntity(ID)->setCentered(isCentered);

	// Load diffuse map
	getEntity(ID)->setDiffuseMap(_texLoader.getTexture(texturePath, true, true, false));
}

void GuiEntityManager::addGuiEntity(const string& ID, vec3 color, vec2 translation, float rotation, vec2 scaling, bool isCentered)
{
	// Create entity
	_createEntity(ID);
	getEntity(ID)->addOglBuffer(isCentered ? _centeredOpenglBuffer : _nonCenteredOpenglBuffer, false);

	// Load transformation
	getEntity(ID)->setTranslation(translation);
	getEntity(ID)->setRotation(rotation);
	getEntity(ID)->setScaling(scaling);
	getEntity(ID)->setCentered(isCentered);

	// Set color
	getEntity(ID)->setColor(color);
}

void GuiEntityManager::update()
{
	for (auto& entity : _getGuiEntities())
	{
		// Calculate model matrix
		if (entity->isVisible())
		{
			entity->updateModelMatrix();
		}
	}
}