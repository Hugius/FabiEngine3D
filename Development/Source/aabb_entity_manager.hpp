#pragma once

#include "base_entity_manager.hpp"

class AabbEntityManager final :  public BaseEntityManager
{
public:
	AabbEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus);
	~AabbEntityManager() = default;

	shared_ptr<AabbEntity> getEntity(const string& ID);

	const vector<shared_ptr<AabbEntity>>& getEntities();
	
	void addAabbEntity(const string& ID, Vec3 position, Vec3 size, bool responsive);
	void bindAabbEntity(const string& ID, const string& parentID, AabbParentType parentType, Vec3 position, Vec3 size, bool responsive);

	void update() override {}
	void update(const vector<shared_ptr<GameEntity>>& gameEntities, const vector<shared_ptr<BillboardEntity>>& billboardEntities);

private:
	OpenGLBuffer* _openglBuffer = nullptr;
};