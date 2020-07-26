#include "text_entity_manager.hpp"

TextEntityManager::TextEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus) :
	BaseEntityManager(objLoader, texLoader, shaderBus)
{

}

TextEntity * TextEntityManager::getEntity(const string & ID)
{
	return dynamic_cast<TextEntity*>(_getBaseEntity(ID, EntityType::TEXT));
}

const vector<TextEntity*> TextEntityManager::getEntities()
{
	vector<TextEntity*> newVector;
	for (auto & entity : _getBaseEntities())
	{
		newVector.push_back(dynamic_cast<TextEntity*>(entity));
	}

	return newVector;
}

void TextEntityManager::addTextEntity
(
	const string & ID, const string & text,
	const string & fontPath, vec3 color,
	vec2 translation, float rotation, vec2 scaling,
	bool overwrite, bool centered
)
{
	// Optional overwrite
	if (overwrite)
	{
		if (isExisting(ID))
		{
			deleteEntity(ID, EntityType::TEXT);
		}
	}

	// Create entity
	_createEntity(EntityType::TEXT, ID)->load(ID);
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 1.0f, 1.0f, centered));
	getEntity(ID)->setTextContent(text);
	getEntity(ID)->setFontPath(fontPath);
	getEntity(ID)->setColor(color);

	// Load transformation
	getEntity(ID)->setTranslation(translation);
	getEntity(ID)->setRotation(rotation);
	getEntity(ID)->setScaling(scaling);
	getEntity(ID)->updateModelMatrix();

	// Load diffuse map
	getEntity(ID)->setDiffuseMap(_texLoader.getText(text, fontPath));
}

void TextEntityManager::update()
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