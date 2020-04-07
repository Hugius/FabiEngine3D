#include <WE3D/LightEntityManager.hpp>
#include <WE3D/Configuration.hpp>

LightEntityManager::LightEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus) :
	EntityManager(objLoader, texLoader, shaderBus)
{
	vector<string> lightShaders = {"GameEntityShader", "TerrainEntityShader"};

	for (auto & shader : lightShaders)
	{
		// Open
		std::ifstream inFile;
		inFile.open("../Engine/Shaders/" + shader + ".frag");

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
		lines[4] += std::to_string(Config::getInst().getMaxLights());

		// Write
		std::ofstream outFile;
		outFile.open("../Engine/Shaders/" + shader + ".frag");
		for (auto & line : lines)
		{
			outFile << line << std::endl;
		}
		outFile.close();
	}
}

LightEntity * LightEntityManager::getEntity(const string & ID)
{
	return dynamic_cast<LightEntity*>(p_getBaseEntity(ID, EntityType::LIGHT));
}

const vector<LightEntity*> LightEntityManager::getEntities()
{
	vector<LightEntity*> newVector;

	for (auto& entity : p_getBaseEntities())
	{
		newVector.push_back(dynamic_cast<LightEntity*>(entity));
	}

	return newVector;
}

void LightEntityManager::addLightEntity(const string & ID, vec3 position, vec3 color, float strength)
{
	// Create entity
	p_createEntity(EntityType::LIGHT, ID)->load(ID);

	// Fill entity
	getEntity(ID)->setPosition(position);
	getEntity(ID)->setColor(color);
	getEntity(ID)->setStrength(strength);
}