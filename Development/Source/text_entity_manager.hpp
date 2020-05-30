#pragma once
#include "base_entity_manager.hpp"

class TextEntityManager final : public BaseEntityManager
{
public:
	TextEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus);
	~TextEntityManager() = default;

	TextEntity * getEntity(const string & ID) override;

	const vector<TextEntity*> getEntities();

	void addTextEntity
	(
		const string& ID, const string& text,
		const string& fontPath, vec3 color,
		vec2 translation, float rotation, vec2 scaling,
		bool overwrite, bool centered
	);

	void update() override;
};