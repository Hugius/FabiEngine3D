#include "text_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

TextEntityManager::TextEntityManager(TextureLoader& textureLoader)
	:
	_textureLoader(textureLoader),
	_centeredRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 1.0f, 1.0f, true)),
	_nonCenteredRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 1.0f, 1.0f, false))
{

}

shared_ptr<TextEntity> TextEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

	if(iterator == _entities.end())
	{
		Logger::throwError("TextEntityManager::getEntity");
	}
	else
	{
		return iterator->second;
	}
}

const unordered_map<string, shared_ptr<TextEntity>>& TextEntityManager::getEntities()
{
	return _entities;
}

void TextEntityManager::createEntity(const string& ID, bool isCentered, bool isDynamic)
{
	_entities.insert(make_pair(ID, make_shared<TextEntity>(ID)));
	getEntity(ID)->setCentered(isCentered);
	getEntity(ID)->setDynamic(isDynamic);
	getEntity(ID)->setRenderBuffer(isCentered ? _centeredRenderBuffer : _nonCenteredRenderBuffer);
}

void TextEntityManager::deleteEntity(const string& ID)
{
	if(!isEntityExisting(ID))
	{
		Logger::throwError("TextEntityManager::deleteEntity");
	}

	_entities.erase(ID);
	_contentMap.erase(ID);
}

void TextEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool TextEntityManager::isEntityExisting(const string& ID)
{
	return (_entities.find(ID) != _entities.end());
}

void TextEntityManager::loadCharacters(const string& ID)
{
	auto entity = getEntity(ID);

	// Check if text content needs to be refreshed
	if((_contentMap.find(ID) == _contentMap.end()) || (_contentMap[ID] != entity->getContent()))
	{
		// Save text content
		_contentMap[ID] = entity->getContent();

		// Delete characters
		entity->deleteCharacterEntities();

		// Iterate through characters
		for(const auto& c : entity->getContent())
		{
			// Create new character
			auto newCharacter = make_shared<ImageEntity>("dummy");
			newCharacter->setRenderBuffer(_nonCenteredRenderBuffer);

			// Load texture
			string content = "";
			content += c;
			auto texture = _textureLoader.load2dTexture(content, entity->getFontPath());

			// Check if font loading went wrong
			if(texture == 0)
			{
				break;
			}

			// Set texture
			newCharacter->setDiffuseMap(texture);

			// Add new character
			entity->addCharacterEntity(newCharacter);
		}

		// Update characters
		entity->updateCharacterEntities();
	}
}

void TextEntityManager::update()
{
	for(const auto& [keyID, entity] : _entities)
	{
		// Update transformation
		entity->updateTransformation();

		// Update characters
		if(entity->isDynamic())
		{
			entity->updateCharacterEntities();
		}
		else
		{
			// Update transformation matrix
			if(entity->isVisible())
			{
				entity->updateTransformationMatrix();
			}
		}
	}
}