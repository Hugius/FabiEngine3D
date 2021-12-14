#pragma once

#include <unordered_map>

using std::unordered_map;

class ReflectionEntityManager final
{
public:
	ReflectionEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// VOID
	void update() override;
	void createEntity(const string& ID);
	void deleteEntity(const string& ID);
	void deleteEntities();

	// BOOL
	const bool isEntityExisting(const string& ID);

	// MISCELLANEOUS
	const unordered_map<string, shared_ptr<ReflectionEntity>>& getEntities();
	shared_ptr<ReflectionEntity> getEntity(const string& ID);

private:
	// MISCELLANEOUS
	unordered_map<string, shared_ptr<ReflectionEntity>> _entities;
};