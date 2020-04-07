#pragma once

#include <GLM/glm.hpp>

using glm::ivec2;

#include "GameEntity.hpp"
#include "GameEntityManager.hpp"
#include "GuiEntityManager.hpp"
#include "TextEntityManager.hpp"
#include "InputHandler.hpp"

enum class RotationType
{
	X,
	Y,
	Z
};

class ModelEditor final
{
public:
	ModelEditor(OBJLoader& objLoader, TextureLoader& texLoader);
	~ModelEditor();

	GameEntity * getSelectedModel();

	vector<string>      & getModelNames();
	vector<GameEntity*> & getModels();

	void loadModels(GameEntityManager & gameEntityManager);
	void loadGUI(GuiEntityManager & guiEntityManager, TextEntityManager & textEntityManager);
	void update(ivec2 mousePos, InputHandler& inputHandler, float delta);

private:
	// Functions
	void p_loadFileNames();
	void p_saveModelData();
	void p_updateModelData();

	// Vectors
	vector<GameEntity*> p_models;
	vector<string> p_modelNames;

	// Other
	unsigned int p_modelIndex = 0;
	RotationType p_rotationType = RotationType::Y;
	OBJLoader& p_objLoader;
	TextureLoader& p_texLoader;
};