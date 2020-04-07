#include "TextEntityManager.hpp"

TextEntityManager::TextEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus) :
	EntityManager(objLoader, texLoader, shaderBus)
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
	const string & fontName, vec3 color,
	vec2 translation, float rotation, vec2 scaling,
	bool engine, bool overwrite, bool centered
)
{
	// Optional overwrite
	if (overwrite)
	{
		if (isExisting(ID))
		{
			deleteEntity(ID);
		}
	}

	// Create entity
	_createEntity(EntityType::TEXT, ID)->load(ID);
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 1.0f, 1.0f, centered));
	getEntity(ID)->setText(text);
	getEntity(ID)->setFontName(fontName);
	getEntity(ID)->setColor(color);

	// Load transformation
	getEntity(ID)->setTranslation(translation);
	getEntity(ID)->setRotation(rotation);
	getEntity(ID)->setScaling(scaling);
	getEntity(ID)->updateModelMatrix();

	// Load diffuse map
	if (engine)
	{
		getEntity(ID)->setDiffuseMap(_texLoader.getText(text, "../Engine/Fonts/" + fontName));
	}
	else
	{
		getEntity(ID)->setDiffuseMap(_texLoader.getText(text, "../Game/Fonts/" + fontName));
	}
}

void TextEntityManager::update(float delta)
{
	for (auto & baseEntity : _getBaseEntities())
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