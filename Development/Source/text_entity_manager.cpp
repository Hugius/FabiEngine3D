#include "text_entity_manager.hpp"
#include "logger.hpp"

TextEntityManager::TextEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus)
	:
	BaseEntityManager(EntityType::TEXT, meshLoader, texLoader, renderBus),
	_centeredRenderBuffer(std::make_shared<RenderBuffer>(0.0f, 0.0f, 1.0f, 1.0f, true, false)),
	_nonCenteredRenderBuffer(std::make_shared<RenderBuffer>(0.0f, 0.0f, 1.0f, 1.0f, false, false))
{

}

shared_ptr<TextEntity> TextEntityManager::getEntity(const string& ID)
{
	auto result = _getTextEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("Non-existing text entity with ID \"" + ID + "\" requested!");
	}

	return result;
}

const unordered_map<string, shared_ptr<TextEntity>>& TextEntityManager::getEntities()
{
	return _getTextEntities();
}

void TextEntityManager::createEntity
(
	const string& ID, const string& textContent,
	const string& fontPath, Vec3 color,
	Vec2 position, float rotation, Vec2 size,
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
	entity->setPosition(position);
	entity->setRotation(rotation);
	entity->setSize(size);
	entity->setCentered(isCentered);
	entity->setDynamic(isDynamic);

	// Create separate character entities
	if (isDynamic)
	{
		reloadCharacters(ID);
	}
	else // Load static text as a whole
	{
		entity->setRenderBuffer(isCentered ? _centeredRenderBuffer : _nonCenteredRenderBuffer);
		entity->setDiffuseMap(_textureLoader.getText(textContent, entity->getFontPath()));
		entity->updateModelMatrix();
	}
}

void TextEntityManager::reloadCharacters(const string& ID)
{
	auto entity = getEntity(ID);

	// Check if text content changed
	if ((_textContentMap.find(ID) == _textContentMap.end()) || (entity->getTextContent() != _textContentMap[ID]))
	{
		// Temporary values
		bool invalidFont = false;
		_textContentMap[ID] = entity->getTextContent();
		entity->deleteCharacterEntities();

		// For every character
		for (const auto& c : entity->getTextContent())
		{
			if (!invalidFont)
			{
				// Create new character entity
				auto newCharacter = std::make_shared<ImageEntity>("uselessID");
				newCharacter->setRenderBuffer(_nonCenteredRenderBuffer);

				// Load text map
				string textContent = "";
				textContent += c;
				auto texture = _textureLoader.getText(textContent, entity->getFontPath());

				// Check if font loading went well
				if (texture != 0)
				{
					newCharacter->setDiffuseMap(texture);
					entity->addCharacterEntity(newCharacter);
				}
				else
				{
					invalidFont = true;
				}
			}
		}

		// Synchronize
		entity->updateCharacterEntities();
	}
}

void TextEntityManager::deleteDynamicTextEntity(const string& ID)
{
	_textContentMap.erase(ID);
	deleteEntity(ID);
}

void TextEntityManager::update()
{
	for (const auto& [keyID, entity] : _getTextEntities())
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