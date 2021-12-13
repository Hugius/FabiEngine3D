#include "text_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

TextEntityManager::TextEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus)
	:
	BaseEntityManager(EntityType::TEXT, meshLoader, textureLoader, renderBus),
	_centeredRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 1.0f, 1.0f, true)),
	_nonCenteredRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 1.0f, 1.0f, false))
{

}

shared_ptr<TextEntity> TextEntityManager::getEntity(const string& ID)
{
	auto result = _getTextEntity(ID);

	if(result == nullptr)
	{
		Logger::throwError("TextEntityManager::getEntity");
	}

	return result;
}

const unordered_map<string, shared_ptr<TextEntity>>& TextEntityManager::getEntities()
{
	return _getTextEntities();
}

void TextEntityManager::createEntity(const string& ID, bool isCentered, bool isDynamic)
{
	_createEntity(ID);
	getEntity(ID)->setCentered(isCentered);
	getEntity(ID)->setDynamic(isDynamic);
	getEntity(ID)->setRenderBuffer(isCentered ? _centeredRenderBuffer : _nonCenteredRenderBuffer);
}

void TextEntityManager::loadCharacters(const string& ID)
{
	auto entity = getEntity(ID);

	// Check if text content changed
	if((_contentMap.find(ID) == _contentMap.end()) || (entity->getContent() != _contentMap[ID]))
	{
		// Temporary values
		bool isInvalidFont = false;
		_contentMap[ID] = entity->getContent();
		entity->deleteCharacterEntities();

		// Iterate through characters
		for(const auto& c : entity->getContent())
		{
			if(!isInvalidFont)
			{
				// Create new character entity
				auto newCharacter = make_shared<ImageEntity>("uselessID");
				newCharacter->setRenderBuffer(_nonCenteredRenderBuffer);

				// Load text map
				string content = "";
				content += c;
				auto texture = _textureLoader.load2dTexture(content, entity->getFontPath());

				// Check if font loading went well
				if(texture != 0)
				{
					newCharacter->setDiffuseMap(texture);
					entity->addCharacterEntity(newCharacter);
				}
				else
				{
					isInvalidFont = true;
				}
			}
		}

		// Synchronize
		entity->updateCharacterEntities();
	}
}

void TextEntityManager::deleteDynamicTextEntity(const string& ID)
{
	_contentMap.erase(ID);
	deleteEntity(ID);
}

void TextEntityManager::update()
{
	for(const auto& [keyID, entity] : _getTextEntities())
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