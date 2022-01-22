#pragma once

#include "base_entity_manager.hpp"
#include "render_bus.hpp"
#include "sky_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class SkyEntityManager final : public BaseEntityManager
{
public:
	SkyEntityManager();

	void inject(shared_ptr<RenderBus> renderBus);
	void update();
	void createEntity(const string& ID);
	void deleteEntity(const string& ID);
	void deleteEntities();
	void selectEntity(const string& ID);

	const bool isEntityExisting(const string& ID) const;

	const unordered_map<string, shared_ptr<SkyEntity>>& getEntities();
	shared_ptr<SkyEntity> getEntity(const string& ID);
	shared_ptr<SkyEntity> getSelectedEntity();

private:
	string _selectedEntityID = "";

	const shared_ptr<VertexBuffer> _mesh;

	unordered_map<string, shared_ptr<SkyEntity>> _entities;

	shared_ptr<RenderBus> _renderBus = nullptr;
};