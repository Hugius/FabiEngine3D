#include "text_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

TextEntityManager::TextEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(EntityType::TEXT, objLoader, texLoader, renderBus),
	_centeredOpenglBuffer(new OpenGLBuffer(0.0f, 0.0f, 1.0f, 1.0f, true, true)),
	_nonCenteredOpenglBuffer(new OpenGLBuffer(0.0f, 0.0f, 1.0f, 1.0f, false, true))
{

}

TextEntityManager::~TextEntityManager()
{
	delete _nonCenteredOpenglBuffer;
}

shared_ptr<TextEntity> TextEntityManager::getEntity(const string& ID)
{
	auto result = _getTextEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("Nonexisting TEXT entity with ID \"" + ID + "\" requested");
	}

	return result;
}

const unordered_map<string, shared_ptr<TextEntity>>& TextEntityManager::getEntities()
{
	return _getTextEntities();
}

void TextEntityManager::addTextEntity
(
	const string& ID, const string& textContent,
	const string& fontPath, Vec3 color,
	Vec2 translation, float rotation, Vec2 scaling,
	bool overwrite, bool isCentered, bool isDynamic
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
	_createEntity(ID);
	auto entity = getEntity(ID);
	entity->setTextContent(textContent);
	entity->setFontPath(fontPath);
	entity->setColor(color);
	entity->setTranslation(translation);
	entity->setRotation(rotation);
	entity->setScaling(scaling);
	entity->setCentered(isCentered);
	entity->setDynamic(isDynamic);

	// Create separate character entities
	if (isDynamic)
	{
		reloadCharacters(ID);
	}
	else // Load static text as a whole
	{
		entity->addOglBuffer(isCentered ? _centeredOpenglBuffer : _nonCenteredOpenglBuffer, false);
		entity->setDiffuseMap(_texLoader.getText(textContent, entity->getFontPath()));
		entity->updateModelMatrix();
	}
}

void TextEntityManager::reloadCharacters(const string& ID)
{
	auto entity = getEntity(ID);

	// Check if text content changed
	if ((_textContentMap.find(ID) == _textContentMap.end()) || (entity->getTextContent() != _textContentMap[ID]))
	{
		_textContentMap[ID] = entity->getTextContent();
		entity->deleteCharacterEntities();

		// For every character
		for (auto& c : entity->getTextContent())
		{
			// Create new character entity
			auto newCharacter = make_shared<GuiEntity>("uselessID");
			newCharacter->addOglBuffer(_nonCenteredOpenglBuffer, false);

			// Load diffuse map
			string textContent = "";
			textContent += c;
			newCharacter->setDiffuseMap(_texLoader.getText(textContent, entity->getFontPath()));
			entity->addCharacterEntity(newCharacter);
		}

		// Synchronize
		entity->updateCharacterEntities();
	}
}

void TextEntityManager::update()
{
	for (auto& [keyID, entity] : _getTextEntities())
	{
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