#pragma once

#include "CameraManager.hpp"
#include "GameEntityManager.hpp"
#include "TextEntityManager.hpp"
#include "InputHandler.hpp"

enum class TransformationType
{
	T,
	R,
	S
};

enum class DirectionType
{
	X,
	Y,
	Z
};

class WorldEditor final
{
public:
	WorldEditor(vector<string> modelNames, GameEntityManager& gameEntityManager);
	~WorldEditor();

	bool checkWorld(const string& worldName);
	void loadWorld(const string & worldName);
	void exportWorld(const string& worldName);
	void update
	(
		ivec2 mousePos, vec3 terrainPoint, 
		bool placementMode, vector<GameEntity*> & models,
		CameraManager& camera, TextEntityManager& text, InputHandler& input, float delta
	);

	bool hasWorldLoadedBefore(const string& worldID);

private:
	GameEntityManager& p_game;

	// Getters
	string p_getSelectedID();
	
	// Vectors
	vector<string>       p_loadedWorlds;
	vector<string>       p_modelNames;
	vector<unsigned int> p_modelAmounts;

	// Other
	DirectionType p_directionType           = DirectionType::Y;
	TransformationType p_transformationType = TransformationType::T;
	unsigned int p_modelIndex               = 0;
	bool p_rotating                         = false;
};