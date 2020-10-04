#pragma once

#include "base_entity_manager.hpp"

class AabbEntityManager final :  public BaseEntityManager
{
public:
	AabbEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus);
	~AabbEntityManager() = default;

	AabbEntity * getEntity(const string& ID) override;

	const vector<AabbEntity*> getEntities();
	
	void addAabbEntity(const string& ID, vec3 position, vec3 size, bool responsive);
	void bindAabbEntity(const string& ID, const string& parentID, AabbParentType parentType, vec3 position, vec3 size, bool responsive);

	void update() override {}
	void update(const vector<GameEntity*>& gameEntities, const vector<BillboardEntity*>& billboardEntities);
};