#include <iostream>
#include <filesystem>


#include "WorldEditor.hpp"
#include "Configuration.hpp"
#include "Logger.hpp"
#include "TextureLoader.hpp"

WorldEditor::WorldEditor(vector<string> modelNames, GameEntityManager& gameEntityManager) :
	_game(gameEntityManager)
{
	for (auto & name : modelNames)
	{
		_modelNames.push_back(name);
		_modelAmounts.push_back(0);
	}
}

WorldEditor::~WorldEditor()
{

}

bool WorldEditor::checkWorld(const string& worldName)
{
	return std::filesystem::exists(string("../Game/Worlds/" + worldName + ".we3d").c_str());
}

void WorldEditor::loadWorld(const string& worldName)
{
	std::ifstream file;
	string line;

	// Open world project file
	file.open("../Game/Worlds/" + worldName + ".we3d");
	if (errno != 0)
	{
		Logger::getInst().throwError("Could not load world: " + worldName);
	}

	// Read a line from the world file
	while (std::getline(file, line))
	{
		std::stringstream iss(line);

		// Data of current line
		float tx, ty, tz, rx, ry, rz, sx, sy, sz;
		string ID, modelName;
		bool transparent, culling, lightmap, reflective, specular;

		// Get data and store into variables
		if (!(iss >> ID >> modelName >> tx >> ty >> tz >> rx >> ry >> rz >> sx >> sy >> sz >> transparent >> culling >> lightmap >> reflective >> specular))
		{
			Logger::getInst().throwError("Could not process project \'worldID\': " + ID);
		}

		unsigned int index = 0;
		for (auto& name : _modelNames)
		{
			if (modelName == name)
			{
				_modelAmounts[index]++;
			}

			index++;
		}

		// Add new entity
		//_game.addGameEntity(ID, modelName, vec3(tx, ty, tz), vec3(rx, ry, rz), vec3(sx, sy, sz), transparent, culling, lightmap, reflective, specular);
	}

	file.close();
}

void WorldEditor::exportWorld(const string& worldName)
{
	// Load file
	std::ofstream fileData(string("../Game/Worlds/" + worldName + ".we3d").c_str());

	// Write actor data to the .fabworld file
	for (auto & entity : _game.getEntities())
	{
		// Creating actor line
		string line =
			entity->getID() + " " + entity->getModelName() + " " +
			std::to_string(entity->getTranslation().x) + " " + std::to_string(entity->getTranslation().y) + " " +
			std::to_string(entity->getTranslation().z) + " " + std::to_string(entity->getRotation().x)    + " " + 
			std::to_string(entity->getRotation().y)    + " " + std::to_string(entity->getRotation().z)    + " " +
			std::to_string(entity->getScaling().x)     + " " + std::to_string(entity->getScaling().y)     + " " + 
			std::to_string(entity->getScaling().z)     + " " + std::to_string(entity->isTransparent())    + " " + 
			std::to_string(entity->isFaceCulled())     + " " + std::to_string(entity->isLightMapped())    + " " +
			std::to_string(entity->isSkyReflective())     + " " + std::to_string(entity->isSpecular());

		fileData << line << std::endl;
	}
}

bool WorldEditor::hasWorldLoadedBefore(const string & worldID)
{
	// Check if world file is loaded already
	for (auto & world : _loadedWorlds)
	{
		if (world == worldID)
		{
			_loadedWorlds.push_back(worldID);
			return true;
		}
	}

	// Add to loaded worlds
	_loadedWorlds.push_back(worldID);

	// Not loaded
	return false;
}

string WorldEditor::_getSelectedID()
{
	return _modelNames[_modelIndex] + "_" + std::to_string(_modelAmounts[_modelIndex]);
}