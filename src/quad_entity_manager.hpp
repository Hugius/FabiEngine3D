#pragma once

#include "render_bus.hpp"
#include "quad_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class QuadEntityManager final
{
public:
	QuadEntityManager();

	void update();
	void createEntity(RenderBus& renderBus, const string& ID, bool isCentered);
	void deleteEntity(const string& ID);
	void deleteEntities();

	const bool isEntityExisting(const string& ID);

	const unordered_map<string, shared_ptr<QuadEntity>>& getEntities();
	shared_ptr<QuadEntity> getEntity(const string& ID);

private:
	const shared_ptr<VertexBuffer> _centeredMesh;
	const shared_ptr<VertexBuffer> _corneredMesh;
	unordered_map<string, shared_ptr<QuadEntity>> _entities;
};