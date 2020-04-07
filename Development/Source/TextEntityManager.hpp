#pragma once
#include "EntityManager.hpp"

class TextEntityManager final : public EntityManager
{
public:
	TextEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus);
	~TextEntityManager() = default;

	TextEntity * getEntity(const string & ID) override;

	const vector<TextEntity*> getEntities();

	void addTextEntity
	(
		const string& ID, const string& text,
		const string& fontName, vec3 color,
		vec2 translation, float rotation, vec2 scaling,
		bool engine, bool overwrite, bool centered
	);

	void update(float delta) override;
};