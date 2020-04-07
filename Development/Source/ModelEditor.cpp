#include <filesystem>
#include <fstream>
#include <sstream>

#include <WE3D/ModelEditor.hpp>
#include <WE3D/TextureLoader.hpp>
#include <WE3D/OBJLoader.hpp>
#include <WE3D/ShaderBus.hpp>
#include <WE3D/Logger.hpp>

ModelEditor::ModelEditor(OBJLoader& objLoader, TextureLoader& texLoader) :
	p_objLoader(objLoader),
	p_texLoader(texLoader)
{
	p_loadFileNames();
}

ModelEditor::~ModelEditor()
{
	for (auto & model : p_models)
	{
		delete model;
	}

	p_models.clear();
}

void ModelEditor::p_loadFileNames()
{
	// Remove potential previous filenames
	if (!p_modelNames.empty())
	{
		p_modelNames.clear();
	}

	string path = "../Game/OBJs/";
	int endOfNameIndex = 0;

	// Get all filenames
	for (const auto & entry : std::filesystem::directory_iterator(path))
	{
		string path = string(entry.path().u8string());
		path.erase(0, 13);

		// Loop over file path
		for (unsigned int i = 0; i < path.size(); i++)
		{
			// End of file name
			if (path[i] == '.')
			{
				endOfNameIndex = i;
			}
		}
		p_modelNames.push_back(path.substr(0, endOfNameIndex));
	}
}

void ModelEditor::loadModels(GameEntityManager & gameEntityManager)
{
	// If new models added
	p_updateModelData();

	// Open models file
	string line;
	std::ifstream file(string("../Engine/Models.we3d").c_str());
	if (errno != 0)
	{
		Logger::getInst().throwError("Could not load models file");
	}

	// Load all existing models
	while(std::getline(file, line))
	{
		// Parse next line
		std::stringstream iss(line);

		// Data of current line
		string fileName;
		float scaleX, scaleY, scaleZ;
		float rotationX, rotationY, rotationZ;
		bool alpha, culled, lightMapped, reflective, specular;

		// Get data and store into variables
		if (!(iss >> fileName >> scaleX >> scaleY >> scaleZ >> rotationX >> rotationY >> rotationZ >> alpha >> culled >> lightMapped >> reflective >> specular))
		{
			Logger::getInst().throwError("Could not process model: " + fileName);
		}

		// Load OBJ model
		auto parts = p_objLoader.loadOBJ(fileName);

		// Create entity
		p_models.push_back(new GameEntity());
		p_models.back()->load(fileName);
		p_models.back()->setModelName(fileName);
		p_models.back()->setRotation(vec3(rotationX, rotationY, rotationZ));
		p_models.back()->setScaling(vec3(scaleX, scaleY, scaleZ));
		p_models.back()->setTransparent(alpha);
		p_models.back()->setFaceCulled(culled);
		p_models.back()->setLightMapped(lightMapped);
		p_models.back()->setSkyReflective(reflective);
		p_models.back()->setSpecular(specular);

		// Create OpenGL buffers
		for (auto & part : parts)
		{
			vector<float> data;
			
			for (unsigned int i = 0; i < part.vertices.size(); i++)
			{
				data.push_back(part.vertices[i].x);
				data.push_back(part.vertices[i].y);
				data.push_back(part.vertices[i].z);

				data.push_back(part.uvCoords[i].x);
				data.push_back(part.uvCoords[i].y);

				data.push_back(part.normals[i].x);
				data.push_back(part.normals[i].y);
				data.push_back(part.normals[i].z);
			}

			// OpenGL buffer
			p_models.back()->addOglBuffer(new OpenGLBuffer(SHAPE_3D, &data[0], data.size()));

			// Diffuse map
			p_models.back()->addDiffuseMap(p_texLoader.getTexture("../Game/Textures/DiffuseMaps/" + part.textureName, true, true));

			// Light map
			if (lightMapped)
			{
				p_models.back()->addLightmap(p_texLoader.getTexture("../Game/Textures/LightMaps/" + part.textureName, false, false));
			}

			// Reflection map
			if (reflective)
			{
				p_models.back()->addReflectionMap(p_texLoader.getTexture("../Game/Textures/ReflectionMaps/" + part.textureName, false, false));
			}
		}
	}

	file.close();
}

void ModelEditor::p_saveModelData()
{
	if (!p_models.empty())
	{
		// Load file
		std::ofstream file(string("../Engine/Models.we3d").c_str());

		// Write to file
		for (auto& model : p_models)
		{
			file <<
				model->getID() << " " <<
				model->getScaling().x << " " << model->getScaling().y << " " << model->getScaling().z << " " <<
				model->getRotation().x << " " << model->getRotation().y << " " << model->getRotation().z << " " <<
				model->isTransparent() << " " << model->isFaceCulled() << " " <<
				model->isLightMapped() << " " << model->isSkyReflective() << " " << model->isSpecular() << "\n";
		}

		// Close file
		file.close();

		// Log
		Logger::getInst().throwInfo("Saved model data");
	}
}

bool compareFunction(std::string a, std::string b) { return a < b; }

void ModelEditor::p_updateModelData()
{
	// Load file
	std::ifstream inFile(string("../Engine/Models.we3d").c_str());  // Read
	
	string tempLine;
	vector<string> lines;

	// All known OBJ files
	vector<string> knownFilenames;

	// Retrieving known ID's
	while (std::getline(inFile, tempLine))
	{
		lines.push_back(tempLine);
		string fileName;
		std::stringstream iss(tempLine);
		iss >> fileName;
		knownFilenames.push_back(fileName);
	}

	// Check if new model was added
	for (auto& fileName : p_modelNames)
	{
		if (std::find(knownFilenames.begin(), knownFilenames.end(), fileName) == knownFilenames.end()) // New model not known
		{
			lines.push_back(fileName + " 1 1 1 0 0 0 0 0 0 0 0"); // Add to file
		}
	}

	// Check if old model was removed
	for (auto& fileName : knownFilenames)
	{
		if (std::find(p_modelNames.begin(), p_modelNames.end(), fileName) == p_modelNames.end()) // Known model not existing anymore
		{
			// Remove from file
			for (auto& line : lines)
			{
				if (line.substr(0, fileName.size()) == fileName)
				{
					lines.erase(std::remove(lines.begin(), lines.end(), line), lines.end());
				}
			}
		}
	}

	// Sorting the file alphabetically
	std::sort(lines.begin(), lines.end(), compareFunction);

	// Closing reading file
	inFile.close();

	// Opening writing file
	std::ofstream outFile(string("../Engine/Models.we3d").c_str()); // Write

	// Write to file
	for (auto & line : lines)
	{
		outFile << line << "\n";
	}

	// Close file
	outFile.close();
}

void ModelEditor::loadGUI(GuiEntityManager & guiEntityManager, TextEntityManager & textEntityManager)
{
	guiEntityManager.addGuiEntity("title", "board", vec2(0.15f, 0.8f), 0.0f, vec2(0.85f, 0.3f), true, true);
	guiEntityManager.addGuiEntity("scroll", "scroll", vec2(-0.7f, 0.0f), 0.0f, vec2(0.6f, 2.0f), true, true);
	textEntityManager.addTextEntity("title", "Model Editor", "medieval",   vec3(0), vec2(0.15f, 0.8f), 0.0f, vec2(0.6f, 0.2f), true, true, true);
	textEntityManager.addTextEntity("move", "Move: LMB", "medieval",       vec3(0), vec2(-0.7f, 0.625f), 0.0f, vec2(0.3f, 0.1f), true, true, true);
	textEntityManager.addTextEntity("rotate", "Rotate: RMB", "medieval",   vec3(0), vec2(-0.7f, 0.5f), 0.0f, vec2(0.3f, 0.1f), true, true, true);
	textEntityManager.addTextEntity("resize", "Resize: MMB", "medieval",   vec3(0), vec2(-0.7f, 0.375f), 0.0f, vec2(0.3f, 0.1f), true, true, true);
	textEntityManager.addTextEntity("next", "Next model: E", "medieval",   vec3(0), vec2(-0.7f, 0.25f), 0.0f, vec2(0.3f, 0.1f), true, true, true);
	textEntityManager.addTextEntity("prev", "Prev model: Q", "medieval",   vec3(0), vec2(-0.7f, 0.125f), 0.0f, vec2(0.3f, 0.1f), true, true, true);
	textEntityManager.addTextEntity("dir", "Direction: D", "medieval",     vec3(0), vec2(-0.7f, 0.0f), 0.0f, vec2(0.3f, 0.1f), true, true, true);
	textEntityManager.addTextEntity("light", "Lightmap: L", "medieval",    vec3(0), vec2(-0.7f, -0.125f), 0.0f, vec2(0.3f, 0.1f), true, true, true);
	textEntityManager.addTextEntity("refl", "Reflective: R", "medieval",   vec3(0), vec2(-0.7f, -0.25f), 0.0f, vec2(0.3f, 0.1f), true, true, true);
	textEntityManager.addTextEntity("trans", "Transparent: T", "medieval", vec3(0), vec2(-0.7f, -0.375f), 0.0f, vec2(0.3f, 0.1f), true, true, true);
	textEntityManager.addTextEntity("face", "Faceculling: F", "medieval",  vec3(0), vec2(-0.7f, -0.5f), 0.0f, vec2(0.3f, 0.1f), true, true, true);
	textEntityManager.addTextEntity("spec", "Specular: S", "medieval",     vec3(0), vec2(-0.7f, -0.625f), 0.0f, vec2(0.3f, 0.1f), true, true, true);
}

GameEntity * ModelEditor::getSelectedModel()
{
	return p_models[p_modelIndex];
}

vector<string> & ModelEditor::getModelNames()
{
	return p_modelNames;
}

vector<GameEntity*> & ModelEditor::getModels()
{
	return p_models;
}