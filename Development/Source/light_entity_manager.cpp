#include "light_entity_manager.hpp"
#include "configuration.hpp"

LightEntityManager::LightEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus) :
	BaseEntityManager(objLoader, texLoader, shaderBus)
{
	vector<string> lightShaders = {"game_entity_shader", "terrain_entity_shader"};

	for (auto & shader : lightShaders)
	{
		// Open
		std::ifstream inFile;
		inFile.open("..\\Engine\\Shaders\\" + shader + ".frag");

		// Read
		string temp;
		vector<string> lines;
		while (std::getline(inFile, temp))
		{
			lines.push_back(temp);
		}
		inFile.close();

		// Change
		lines[4].erase(27);
		lines[4] += std::to_string(10); // 10 IS TEMPORARILY SO IT DOESN'T CRASH!

		// Write
		std::ofstream outFile;
		outFile.open("..\\Engine\\Shaders\\" + shader + ".frag");
		for (auto & line : lines)
		{
			outFile << line << std::endl;
		}
		outFile.close();
	}
}

LightEntity * LightEntityManager::getEntity(const string & ID)
{
	return dynamic_cast<LightEntity*>(_getBaseEntity(ID, EntityType::LIGHT));
}

const vector<LightEntity*> LightEntityManager::getEntities()
{
	vector<LightEntity*> newVector;

	for (auto& entity : _getBaseEntities())
	{
		newVector.push_back(dynamic_cast<LightEntity*>(entity));
	}

	return newVector;
}

void LightEntityManager::addLightEntity(const string & ID, vec3 position, vec3 color, float strength)
{
	// Create entity
	_createEntity(EntityType::LIGHT, ID)->load(ID);

	// Fill entity
	getEntity(ID)->setPosition(position);
	getEntity(ID)->setColor(color);
	getEntity(ID)->setStrength(strength);
}