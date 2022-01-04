#pragma once

#include "image_loader.hpp"
#include "text_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class TextEntityManager final
{
public:
	TextEntityManager(ImageLoader& textureLoader, RenderBus& renderBus);

	void update();
	void createEntity(const string& ID, bool isCentered);
	void deleteEntity(const string& ID);
	void deleteEntities();

	const bool isEntityExisting(const string& ID);

	const unordered_map<string, shared_ptr<TextEntity>>& getEntities();
	shared_ptr<TextEntity> getEntity(const string& ID);

private:
	const shared_ptr<VertexBuffer> _mesh;
	unordered_map<string, shared_ptr<TextEntity>> _entities;
	ImageLoader& _textureLoader;
	RenderBus& _renderBus;
};