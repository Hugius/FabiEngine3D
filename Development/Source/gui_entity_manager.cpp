#include "gui_entity_manager.hpp"

GuiEntityManager::GuiEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus) :
	BaseEntityManager(objLoader, texLoader, shaderBus)
{

}

GuiEntity* GuiEntityManager::getEntity(const string& ID)
{
	return dynamic_cast<GuiEntity*>(_getBaseEntity(ID, EntityType::GUI));
}

const vector<GuiEntity*> GuiEntityManager::getEntities()
{
	vector<GuiEntity*> newVector;

	for (auto& entity : _getBaseEntities())
	{
		newVector.push_back(dynamic_cast<GuiEntity*>(entity));
	}

	return newVector;
}

void GuiEntityManager::addGuiEntity(const string& ID, const string& texturePath, vec2 translation, float rotation, vec2 scaling, bool engine, bool centered)
{
	// Create entity
	_createEntity(EntityType::GUI, ID)->load(ID);
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 1.0f, 1.0f, centered));

	// Load transformation
	getEntity(ID)->setTranslation(translation);
	getEntity(ID)->setRotation(rotation);
	getEntity(ID)->setScaling(scaling);
	getEntity(ID)->setCentered(centered);

	// Load diffuse map
	getEntity(ID)->setDiffuseMap(_texLoader.getTexture(texturePath, true, true, false));
}

void GuiEntityManager::addGuiEntity(const string& ID, vec3 color, vec2 translation, float rotation, vec2 scaling, bool centered)
{
	// Create entity
	_createEntity(EntityType::GUI, ID)->load(ID);
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 1.0f, 1.0f, centered));

	// Load transformation
	getEntity(ID)->setTranslation(translation);
	getEntity(ID)->setRotation(rotation);
	getEntity(ID)->setScaling(scaling);
	getEntity(ID)->setCentered(centered);

	// Set color
	getEntity(ID)->setColor(color);
}

void GuiEntityManager::update()
{
	for (auto & baseEntity : _getBaseEntities())
	{
		// Create temporary game entity object
		auto * entity = getEntity(baseEntity->getID());

		// Calculate model matrix
		if (entity->isVisible())
		{
			entity->updateModelMatrix();
		}
	}
}