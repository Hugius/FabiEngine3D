#pragma once

#include "base_entity_manager.hpp"
#include "render_bus.hpp"
#include "quad_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class Quad2dEntityManager final : public BaseEntityManager
{
public:
	Quad2dEntityManager();

	void inject(shared_ptr<RenderBus> renderBus);
	void update();
	void createEntity(const string& ID, bool isCentered);
	void deleteEntity(const string& ID);
	void deleteEntities();

	const bool isEntityExisting(const string& ID) const;

	const unordered_map<string, shared_ptr<Quad2dEntity>>& getEntities();
	shared_ptr<Quad2dEntity> getEntity(const string& ID);

private:
	const shared_ptr<VertexBuffer> _centeredMesh;
	const shared_ptr<VertexBuffer> _corneredMesh;

	unordered_map<string, shared_ptr<Quad2dEntity>> _entities;

	shared_ptr<RenderBus> _renderBus = nullptr;
};