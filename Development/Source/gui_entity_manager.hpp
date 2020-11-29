#pragma once

#include "base_entity_manager.hpp"

class GuiEntityManager final : public BaseEntityManager
{
public:
	GuiEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus);
	~GuiEntityManager();

	shared_ptr<GuiEntity> getEntity(const string& ID);

	const unordered_map<string, shared_ptr<GuiEntity>>& getEntities();

	void addGuiEntity(const string& ID, const string& texturePath, Vec2 translation, float rotation, Vec2 scaling, bool engine, bool isCentered);
	void addGuiEntity(const string& ID, Vec3 color, Vec2 translation, float rotation, Vec2 scaling, bool isCentered);
	void update() override;

private:
	OpenGLBuffer* _centeredOpenglBuffer = nullptr;
	OpenGLBuffer* _nonCenteredOpenglBuffer = nullptr;
};