#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> TerrainEditor::getAllTerrainTexturePathsFromFile() const
{
	// Validate project ID
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("TerrainEditor::getAllTerrainTexturePathsFromFile");
	}

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\terrain.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `terrain.fe3d` missing!");
		return {};
	}

	// Load terrain file
	ifstream file(filePath);

	// Read terrain data
	vector<string> texturePaths;
	string line;
	while(getline(file, line))
	{
		// Values
		string terrainID, heightMapPath, diffuseMapPath, normalMapPath,
			normalMapPathR, normalMapPathG, normalMapPathB,
			blendMapPath, blendMapPathR, blendMapPathG, blendMapPathB;
		float maxHeight, textureRepeat, lightness, redRepeat, greenRepeat, blueRepeat;

		// For file extraction
		istringstream iss(line);

		// Load base data
		iss >>
			terrainID >>
			heightMapPath >>
			diffuseMapPath >>
			maxHeight >>
			textureRepeat >>
			lightness >>
			blendMapPath >>
			blendMapPathR >>
			blendMapPathG >>
			blendMapPathB >>
			redRepeat >>
			greenRepeat >>
			blueRepeat >>
			normalMapPath >>
			normalMapPathR >>
			normalMapPathG >>
			normalMapPathB;

		// Convert empty string
		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
		normalMapPathR = (normalMapPathR == "?") ? "" : normalMapPathR;
		normalMapPathG = (normalMapPathG == "?") ? "" : normalMapPathG;
		normalMapPathB = (normalMapPathB == "?") ? "" : normalMapPathB;
		blendMapPath = (blendMapPath == "?") ? "" : blendMapPath;
		blendMapPathR = (blendMapPathR == "?") ? "" : blendMapPathR;
		blendMapPathG = (blendMapPathG == "?") ? "" : blendMapPathG;
		blendMapPathB = (blendMapPathB == "?") ? "" : blendMapPathB;

		// Convert spaces
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		replace(normalMapPathR.begin(), normalMapPathR.end(), '?', ' ');
		replace(normalMapPathG.begin(), normalMapPathG.end(), '?', ' ');
		replace(normalMapPathB.begin(), normalMapPathB.end(), '?', ' ');
		replace(blendMapPath.begin(), blendMapPath.end(), '?', ' ');
		replace(blendMapPathR.begin(), blendMapPathR.end(), '?', ' ');
		replace(blendMapPathG.begin(), blendMapPathG.end(), '?', ' ');
		replace(blendMapPathB.begin(), blendMapPathB.end(), '?', ' ');

		// Diffuse map
		if(!diffuseMapPath.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
			}

			// Save path
			texturePaths.push_back(diffuseMapPath);
		}

		// Normal map
		if(!normalMapPath.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				normalMapPath = string("projects\\" + _currentProjectID + "\\" + normalMapPath);
			}

			// Save path
			texturePaths.push_back(normalMapPath);
		}

		// Normal map R
		if(!normalMapPathR.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				normalMapPathR = string("projects\\" + _currentProjectID + "\\" + normalMapPathR);
			}

			// Save path
			texturePaths.push_back(normalMapPathR);
		}

		// Normal map G
		if(!normalMapPathG.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				normalMapPathG = string("projects\\" + _currentProjectID + "\\" + normalMapPathG);
			}

			// Save path
			texturePaths.push_back(normalMapPathG);
		}

		// Normal map B
		if(!normalMapPathB.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				normalMapPathB = string("projects\\" + _currentProjectID + "\\" + normalMapPathB);
			}

			// Save path
			texturePaths.push_back(normalMapPathB);
		}

		// Blend map
		if(!blendMapPath.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				blendMapPath = string("projects\\" + _currentProjectID + "\\" + blendMapPath);
			}

			// Save path
			texturePaths.push_back(blendMapPath);
		}

		// Blend map R
		if(!blendMapPathR.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				blendMapPathR = string("projects\\" + _currentProjectID + "\\" + blendMapPathR);
			}

			// Save path
			texturePaths.push_back(blendMapPathR);
		}

		// Blend map G
		if(!blendMapPathG.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				blendMapPathG = string("projects\\" + _currentProjectID + "\\" + blendMapPathG);
			}

			// Save path
			texturePaths.push_back(blendMapPathG);
		}

		// Blend map B
		if(!blendMapPathB.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				blendMapPathB = string("projects\\" + _currentProjectID + "\\" + blendMapPathB);
			}

			// Save path
			texturePaths.push_back(blendMapPathB);
		}
	}

	// Close file
	file.close();

	// Return
	return texturePaths;
}

const vector<string> TerrainEditor::getAllTerrainBitmapPathsFromFile() const
{
	// Validate project ID
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("TerrainEditor::getAllTerrainTexturePathsFromFile");
	}

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\terrain.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `terrain.fe3d` missing!");
		return {};
	}

	// Load terrain file
	ifstream file(filePath);

	// Read terrain data
	vector<string> bitmapPaths;
	string line;
	while(getline(file, line))
	{
		// Values
		string terrainID, heightMapPath;

		// For file extraction
		istringstream iss(line);

		// Load base data
		iss >>
			terrainID >>
			heightMapPath;

		// Convert empty string
		heightMapPath = (heightMapPath == "?") ? "" : heightMapPath;

		// Convert spaces
		replace(heightMapPath.begin(), heightMapPath.end(), '?', ' ');

		// Height map
		if(!heightMapPath.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				heightMapPath = string("projects\\" + _currentProjectID + "\\" + heightMapPath);
			}
			
			// Save path
			bitmapPaths.push_back(heightMapPath);
		}
	}

	// Close file
	file.close();

	// Return
	return bitmapPaths;
}

const bool TerrainEditor::loadTerrainEntitiesFromFile()
{
	// Validate project ID
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("TerrainEditor::loadTerrainEntitiesFromFile");
	}

	// Clear IDs from previous loads
	_loadedTerrainIDs.clear();

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\terrain.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `terrain.fe3d` missing!");
		return false;
	}

	// Load terrain file
	ifstream file(filePath);

	// Read terrain data
	string line;
	while(getline(file, line))
	{
		// Values
		string terrainID, heightMapPath, diffuseMapPath, normalMapPath,
			normalMapPathR, normalMapPathG, normalMapPathB,
			blendMapPath, blendMapPathR, blendMapPathG, blendMapPathB;
		float maxHeight, textureRepeat, lightness, redRepeat, greenRepeat, blueRepeat, specularShininess, specularIntensity;
		bool isSpecular;

		// For file extraction
		istringstream iss(line);

		// Load base data
		iss >>
			terrainID >>
			heightMapPath >>
			diffuseMapPath >>
			maxHeight >>
			textureRepeat >>
			lightness >>
			blendMapPath >>
			blendMapPathR >>
			blendMapPathG >>
			blendMapPathB >>
			redRepeat >>
			greenRepeat >>
			blueRepeat >>
			normalMapPath >>
			normalMapPathR >>
			normalMapPathG >>
			normalMapPathB >>
			isSpecular >>
			specularShininess >>
			specularIntensity;

		// Convert empty string
		heightMapPath = (heightMapPath == "?") ? "" : heightMapPath;
		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
		normalMapPathR = (normalMapPathR == "?") ? "" : normalMapPathR;
		normalMapPathG = (normalMapPathG == "?") ? "" : normalMapPathG;
		normalMapPathB = (normalMapPathB == "?") ? "" : normalMapPathB;
		blendMapPath = (blendMapPath == "?") ? "" : blendMapPath;
		blendMapPathR = (blendMapPathR == "?") ? "" : blendMapPathR;
		blendMapPathG = (blendMapPathG == "?") ? "" : blendMapPathG;
		blendMapPathB = (blendMapPathB == "?") ? "" : blendMapPathB;

		// Convert spaces
		replace(heightMapPath.begin(), heightMapPath.end(), '?', ' ');
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		replace(normalMapPathR.begin(), normalMapPathR.end(), '?', ' ');
		replace(normalMapPathG.begin(), normalMapPathG.end(), '?', ' ');
		replace(normalMapPathB.begin(), normalMapPathB.end(), '?', ' ');
		replace(blendMapPath.begin(), blendMapPath.end(), '?', ' ');
		replace(blendMapPathR.begin(), blendMapPathR.end(), '?', ' ');
		replace(blendMapPathG.begin(), blendMapPathG.end(), '?', ' ');
		replace(blendMapPathB.begin(), blendMapPathB.end(), '?', ' ');

		// Convert to long path
		if(!Config::getInst().isApplicationExported())
		{
			heightMapPath = string("projects\\" + _currentProjectID + "\\" + heightMapPath);
		}

		// Create terrain
		_fe3d.terrain_create(terrainID, heightMapPath);

		// Check if terrain creation went well
		if(_fe3d.terrain_isExisting(terrainID))
		{
			// Add terrain ID
			_loadedTerrainIDs.push_back(terrainID);

			// Diffuse map
			if(!diffuseMapPath.empty())
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
				}

				// Set path
				_fe3d.terrain_setDiffuseMap(terrainID, diffuseMapPath);
			}

			// Normal map
			if(!normalMapPath.empty())
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					normalMapPath = string("projects\\" + _currentProjectID + "\\" + normalMapPath);
				}

				// Set path
				_fe3d.terrain_setNormalMap(terrainID, normalMapPath);
			}

			// Normal map R
			if(!normalMapPathR.empty())
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					normalMapPathR = string("projects\\" + _currentProjectID + "\\" + normalMapPathR);
				}

				// Set path
				_fe3d.terrain_setNormalMapR(terrainID, normalMapPathR);
			}

			// Normal map G
			if(!normalMapPathG.empty())
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					normalMapPathG = string("projects\\" + _currentProjectID + "\\" + normalMapPathG);
				}

				// Set path
				_fe3d.terrain_setNormalMapG(terrainID, normalMapPathG);
			}

			// Normal map B
			if(!normalMapPathB.empty())
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					normalMapPathB = string("projects\\" + _currentProjectID + "\\" + normalMapPathB);
				}

				// Set path
				_fe3d.terrain_setNormalMapB(terrainID, normalMapPathB);
			}

			// Blend map
			if(!blendMapPath.empty())
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					blendMapPath = string("projects\\" + _currentProjectID + "\\" + blendMapPath);
				}

				// Set path
				_fe3d.terrain_setBlendMap(terrainID, blendMapPath);
			}

			// Blend map R
			if(!blendMapPathR.empty())
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					blendMapPathR = string("projects\\" + _currentProjectID + "\\" + blendMapPathR);
				}

				// Set path
				_fe3d.terrain_setDiffuseMapR(terrainID, blendMapPathR);
			}

			// Blend map G
			if(!blendMapPathG.empty())
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					blendMapPathG = string("projects\\" + _currentProjectID + "\\" + blendMapPathG);
				}

				// Set path
				_fe3d.terrain_setDiffuseMapG(terrainID, blendMapPathG);
			}

			// Blend map B
			if(!blendMapPathB.empty())
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					blendMapPathB = string("projects\\" + _currentProjectID + "\\" + blendMapPathB);
				}

				// Set path
				_fe3d.terrain_setDiffuseMapB(terrainID, blendMapPathB);
			}

			// Set properties
			_fe3d.terrain_setMaxHeight(terrainID, maxHeight);
			_fe3d.terrain_setTextureRepeat(terrainID, textureRepeat);
			_fe3d.terrain_setLightness(terrainID, lightness);
			_fe3d.terrain_setRedRepeat(terrainID, redRepeat);
			_fe3d.terrain_setGreenRepeat(terrainID, greenRepeat);
			_fe3d.terrain_setBlueRepeat(terrainID, blueRepeat);
			_fe3d.terrain_setSpecular(terrainID, isSpecular);
			_fe3d.terrain_setSpecularShininess(terrainID, specularShininess);
			_fe3d.terrain_setSpecularIntensity(terrainID, specularIntensity);
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Terrain data loaded!");

	// Return
	return true;
}