#pragma once

#include "texture_loader.hpp"
#include "text_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class TextEntityManager final
{
public:
	TextEntityManager(TextureLoader& textureLoader, RenderBus& renderBus);

	void update();
	void createEntity(const string& ID, bool isCentered, bool isDynamic);
	void deleteEntity(const string& ID);
	void deleteEntities();
	void loadCharacters(const string& ID);

	const bool isEntityExisting(const string& ID);

	const unordered_map<string, shared_ptr<TextEntity>>& getEntities();
	shared_ptr<TextEntity> getEntity(const string& ID);

private:
	map<string, string> _contentMap;

	const shared_ptr<RenderBuffer> _centeredRenderBuffer;
	const shared_ptr<RenderBuffer> _nonCenteredRenderBuffer;
	unordered_map<string, shared_ptr<TextEntity>> _entities;
	TextureLoader& _textureLoader;
	RenderBus& _renderBus;
};