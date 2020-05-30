#pragma once
#include "base_entity_manager.hpp"

class GuiEntityManager final : public BaseEntityManager
{
public:
	GuiEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus);
	~GuiEntityManager() = default;

	GuiEntity * getEntity(const string & ID) override;

	const vector<GuiEntity*> getEntities();

	void addGuiEntity(const string & ID, const string & assetName, vec2 translation, float rotation, vec2 scaling, bool engine, bool centered);
	void addGuiEntity(const string & ID, vec3 color, vec2 translation, float rotation, vec2 scaling, bool centered);
	void update() override;
};