#pragma once

#include "base_entity_manager.hpp"

class GuiEntityManager final : public BaseEntityManager
{
public:
	GuiEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus);
	~GuiEntityManager();

	GuiEntity * getEntity(const string& ID) override;

	const vector<GuiEntity*> getEntities();

	void addGuiEntity(const string& ID, const string& texturePath, vec2 translation, float rotation, vec2 scaling, bool engine, bool isCentered);
	void addGuiEntity(const string& ID, vec3 color, vec2 translation, float rotation, vec2 scaling, bool isCentered);
	void update() override;

private:
	OpenGLBuffer* _centeredOpenglBuffer = nullptr;
	OpenGLBuffer* _nonCenteredOpenglBuffer = nullptr;
};