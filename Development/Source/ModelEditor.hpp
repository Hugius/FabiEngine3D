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
	void _loadFileNames();
	void _saveModelData();
	void _updateModelData();

	// Vectors
	vector<GameEntity*> _models;
	vector<string> _modelNames;

	// Other
	unsigned int _modelIndex = 0;
	RotationType _rotationType = RotationType::Y;
	OBJLoader& _objLoader;
	TextureLoader& _texLoader;
};