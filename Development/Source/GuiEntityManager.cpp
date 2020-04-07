#include <WE3D/GuiEntityManager.hpp>

GuiEntityManager::GuiEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus) :
	EntityManager(objLoader, texLoader, shaderBus)
{

}

GuiEntity* GuiEntityManager::getEntity(const string & ID)
{
	return dynamic_cast<GuiEntity*>(p_getBaseEntity(ID, EntityType::GUI));
}

const vector<GuiEntity*> GuiEntityManager::getEntities()
{
	vector<GuiEntity*> newVector;

	for (auto& entity : p_getBaseEntities())
	{
		newVector.push_back(dynamic_cast<GuiEntity*>(entity));
	}

	return newVector;
}

void GuiEntityManager::addGuiEntity(const string & ID, const string & assetName, vec2 translation, float rotation, vec2 scaling, bool engine, bool centered)
{
	// Create entity
	p_createEntity(EntityType::GUI, ID)->load(ID);
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 1.0f, 1.0f, centered));

	// Load transformation
	getEntity(ID)->setTranslation(translation);
	getEntity(ID)->setRotation(rotation);
	getEntity(ID)->setScaling(scaling);

	// Load diffuse map
	if (engine)
	{
		getEntity(ID)->setDiffuseMap(p_texLoader.getTexture("../Engine/Textures/" + assetName, true, true, false));
	}
	else
	{
		getEntity(ID)->setDiffuseMap(p_texLoader.getTexture("../Game/Textures/GuiMaps/" + assetName, true, true, false));
	}
}

void GuiEntityManager::addGuiEntity(const string & ID, vec3 color, vec2 translation, float rotation, vec2 scaling, bool centered)
{
	// Create entity
	p_createEntity(EntityType::GUI, ID)->load(ID);
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 1.0f, 1.0f, centered));

	// Load transformation
	getEntity(ID)->setTranslation(translation);
	getEntity(ID)->setRotation(rotation);
	getEntity(ID)->setScaling(scaling);

	// Set color
	getEntity(ID)->setColor(color);
}

void GuiEntityManager::update(float delta)
{
	for (auto & baseEntity : p_getBaseEntities())
	{
		// Create temporary game entity object
		auto * entity = getEntity(baseEntity->getID());

		// Calculate model matrix
		if (entity->isEnabled())
		{
			entity->updateModelMatrix();
		}
	}
}