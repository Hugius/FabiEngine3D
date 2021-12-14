#pragma once

#include <unordered_map>

using std::unordered_map;

class WaterEntityManager final
{
public:
	WaterEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// VOID
	void update() override;
	void createEntity(const string& ID);
	void loadMesh(const string& ID);
	void selectWater(const string& ID);
	void deleteEntities();

	// BOOL
	const bool isEntityExisting(const string& ID);

	// MISCELLANEOUS
	const unordered_map<string, shared_ptr<WaterEntity>>& getEntities();
	shared_ptr<WaterEntity> getEntity(const string& ID);
	shared_ptr<WaterEntity> getSelectedWater();

	// UNSIGNED INT
	static inline const unsigned int MAX_SIZE = 1024;

private:
	// STRING
	string _selectedID = "";

	// MISCELLANEOUS
	unordered_map<string, shared_ptr<WaterEntity>> _entities;
};