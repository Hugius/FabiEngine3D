#pragma once

#include "base_entity_manager.hpp"
#include "image_loader.hpp"
#include "text2d_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class Text2dEntityManager final : public BaseEntityManager
{
public:
	Text2dEntityManager();

	void inject(shared_ptr<RenderBus> renderBus);
	void update();
	void createEntity(const string& ID, bool isCentered);
	void deleteEntity(const string& ID);
	void deleteEntities();

	const bool isEntityExisting(const string& ID) const;

	const unordered_map<string, shared_ptr<Text2dEntity>>& getEntities();
	shared_ptr<Text2dEntity> getEntity(const string& ID);

private:
	const shared_ptr<VertexBuffer> _mesh;

	unordered_map<string, shared_ptr<Text2dEntity>> _entities;

	shared_ptr<RenderBus> _renderBus = nullptr;
};