#pragma once

#include "texture_loader.hpp"
#include "text_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class TextEntityManager final
{
public:
	TextEntityManager(TextureLoader& textureLoader);

	// VOID
	void update();
	void createEntity(const string& ID, bool isCentered, bool isDynamic);
	void deleteEntity(const string& ID);
	void deleteEntities();
	void loadCharacters(const string& ID);

	// BOOL
	const bool isEntityExisting(const string& ID);

	// MISCELLANEOUS
	const unordered_map<string, shared_ptr<TextEntity>>& getEntities();
	shared_ptr<TextEntity> getEntity(const string& ID);

private:
	// STRING
	map<string, string> _contentMap;

	// MISCELLANEOUS
	const shared_ptr<RenderBuffer> _centeredRenderBuffer;
	const shared_ptr<RenderBuffer> _nonCenteredRenderBuffer;
	unordered_map<string, shared_ptr<TextEntity>> _entities;
	TextureLoader& _textureLoader;
};