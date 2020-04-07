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
	GameEntityManager& _game;

	// Getters
	string _getSelectedID();
	
	// Vectors
	vector<string>       _loadedWorlds;
	vector<string>       _modelNames;
	vector<unsigned int> _modelAmounts;

	// Other
	DirectionType _directionType           = DirectionType::Y;
	TransformationType _transformationType = TransformationType::T;
	unsigned int _modelIndex               = 0;
	bool _rotating                         = false;
};