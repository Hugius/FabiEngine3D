#include "text_entity_manager.hpp"

#include <iostream>

TextEntityManager::TextEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(objLoader, texLoader, renderBus),
	_centeredOpenglBuffer(new OpenGLBuffer(0.0f, 0.0f, 1.0f, 1.0f, true, true)),
	_nonCenteredOpenglBuffer(new OpenGLBuffer(0.0f, 0.0f, 1.0f, 1.0f, false, true))
{

}

TextEntityManager::~TextEntityManager()
{
	delete _nonCenteredOpenglBuffer;
}

TextEntity* TextEntityManager::getEntity(const string& ID)
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
	const string& ID, const string& textContent,
	const string& fontPath, vec3 color,
	vec2 translation, float rotation, vec2 scaling,
	bool overwrite, bool isCentered, bool isDynamic
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
	getEntity(ID)->setTextContent(textContent);
	getEntity(ID)->setFontPath(fontPath);
	getEntity(ID)->setColor(color);
	getEntity(ID)->setTranslation(translation);
	getEntity(ID)->setRotation(rotation);
	getEntity(ID)->setScaling(scaling);
	getEntity(ID)->setCentered(isCentered);
	getEntity(ID)->setDynamic(isDynamic);

	// Create separate character entities
	if (isDynamic)
	{
		reloadCharacters(ID);
	}
	else // Load static text as a whole
	{
		getEntity(ID)->addOglBuffer(isCentered ? _centeredOpenglBuffer : _nonCenteredOpenglBuffer, false);
		getEntity(ID)->setDiffuseMap(_texLoader.getText(textContent, getEntity(ID)->getFontPath()));
		getEntity(ID)->updateModelMatrix();
	}
}

void TextEntityManager::reloadCharacters(const string& ID)
{
	// Check if text content changed
	if ((_textContentMap.find(ID) == _textContentMap.end()) || (getEntity(ID)->getTextContent() != _textContentMap[ID]))
	{
		_textContentMap[ID] = getEntity(ID)->getTextContent();
		getEntity(ID)->deleteCharacterEntities();

		// For every character
		for (auto& c : getEntity(ID)->getTextContent())
		{
			// Create new character entity
			GuiEntity* newCharacter = new GuiEntity();
			newCharacter->addOglBuffer(_nonCenteredOpenglBuffer, false);

			// Load diffuse map
			string textContent = "";
			textContent += c;
			newCharacter->setDiffuseMap(_texLoader.getText(textContent, getEntity(ID)->getFontPath()));
			getEntity(ID)->addCharacterEntity(newCharacter);
		}

		// Synchronize
		getEntity(ID)->updateCharacterEntities();
	}
}

void TextEntityManager::update()
{
	for (auto & baseEntity : _getBaseEntities())
	{
		// Create temporary game entity object
		auto * entity = getEntity(baseEntity->getID());

		// Update entity
		if (entity->isDynamic())
		{
			entity->updateCharacterEntities(); // Individual characters
		}
		else
		{
			entity->updateModelMatrix(); // Whole word
		}
	}
}