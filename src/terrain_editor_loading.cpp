#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> TerrainEditor::getTexturePathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("TerrainEditor::getTexturePathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\terrain.fe3d");

	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `terrain.fe3d` missing!");
		return {};
	}

	ifstream file(filePath);

	vector<string> texturePaths;
	string line;
	while(getline(file, line))
	{
		// Values
		string terrainID, heightMapPath, diffuseMapPath, normalMapPath,
			redNormalMapPath, greenNormalMapPath, blueNormalMapPath,
			blendMapPath, redDiffuseMapPath, greenDiffuseMapPath, blueDiffuseMapPath;
		float maxHeight, textureRepeat, lightness, redTextureRepeat, greenTextureRepeat, blueTextureRepeat;

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
			redDiffuseMapPath >>
			greenDiffuseMapPath >>
			blueDiffuseMapPath >>
			redTextureRepeat >>
			greenTextureRepeat >>
			blueTextureRepeat >>
			normalMapPath >>
			redNormalMapPath >>
			greenNormalMapPath >>
			blueNormalMapPath;

		// Convert empty string
		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
		redNormalMapPath = (redNormalMapPath == "?") ? "" : redNormalMapPath;
		greenNormalMapPath = (greenNormalMapPath == "?") ? "" : greenNormalMapPath;
		blueNormalMapPath = (blueNormalMapPath == "?") ? "" : blueNormalMapPath;
		blendMapPath = (blendMapPath == "?") ? "" : blendMapPath;
		redDiffuseMapPath = (redDiffuseMapPath == "?") ? "" : redDiffuseMapPath;
		greenDiffuseMapPath = (greenDiffuseMapPath == "?") ? "" : greenDiffuseMapPath;
		blueDiffuseMapPath = (blueDiffuseMapPath == "?") ? "" : blueDiffuseMapPath;

		// Convert spaces
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		replace(redNormalMapPath.begin(), redNormalMapPath.end(), '?', ' ');
		replace(greenNormalMapPath.begin(), greenNormalMapPath.end(), '?', ' ');
		replace(blueNormalMapPath.begin(), blueNormalMapPath.end(), '?', ' ');
		replace(blendMapPath.begin(), blendMapPath.end(), '?', ' ');
		replace(redDiffuseMapPath.begin(), redDiffuseMapPath.end(), '?', ' ');
		replace(greenDiffuseMapPath.begin(), greenDiffuseMapPath.end(), '?', ' ');
		replace(blueDiffuseMapPath.begin(), blueDiffuseMapPath.end(), '?', ' ');

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
		if(!redNormalMapPath.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				redNormalMapPath = string("projects\\" + _currentProjectID + "\\" + redNormalMapPath);
			}

			// Save path
			texturePaths.push_back(redNormalMapPath);
		}

		// Normal map G
		if(!greenNormalMapPath.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				greenNormalMapPath = string("projects\\" + _currentProjectID + "\\" + greenNormalMapPath);
			}

			// Save path
			texturePaths.push_back(greenNormalMapPath);
		}

		// Normal map B
		if(!blueNormalMapPath.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				blueNormalMapPath = string("projects\\" + _currentProjectID + "\\" + blueNormalMapPath);
			}

			// Save path
			texturePaths.push_back(blueNormalMapPath);
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
		if(!redDiffuseMapPath.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				redDiffuseMapPath = string("projects\\" + _currentProjectID + "\\" + redDiffuseMapPath);
			}

			// Save path
			texturePaths.push_back(redDiffuseMapPath);
		}

		// Blend map G
		if(!greenDiffuseMapPath.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				greenDiffuseMapPath = string("projects\\" + _currentProjectID + "\\" + greenDiffuseMapPath);
			}

			// Save path
			texturePaths.push_back(greenDiffuseMapPath);
		}

		// Blend map B
		if(!blueDiffuseMapPath.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				blueDiffuseMapPath = string("projects\\" + _currentProjectID + "\\" + blueDiffuseMapPath);
			}

			// Save path
			texturePaths.push_back(blueDiffuseMapPath);
		}
	}

	file.close();

	return texturePaths;
}

const vector<string> TerrainEditor::getBitmapPathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("TerrainEditor::getBitmapPathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\terrain.fe3d");

	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `terrain.fe3d` missing!");
		return {};
	}

	ifstream file(filePath);

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

	file.close();

	return bitmapPaths;
}

const bool TerrainEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("TerrainEditor::loadFromFile");
	}

	_loadedTerrainIDs.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\terrain.fe3d");

	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `terrain.fe3d` missing!");
		return false;
	}

	ifstream file(filePath);

	string line;
	while(getline(file, line))
	{
		// Values
		string terrainID, heightMapPath, diffuseMapPath, normalMapPath,
			redNormalMapPath, greenNormalMapPath, blueNormalMapPath,
			blendMapPath, redDiffuseMapPath, greenDiffuseMapPath, blueDiffuseMapPath;
		float maxHeight, textureRepeat, lightness, redTextureRepeat, greenTextureRepeat, blueTextureRepeat, specularShininess, specularIntensity;
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
			redDiffuseMapPath >>
			greenDiffuseMapPath >>
			blueDiffuseMapPath >>
			redTextureRepeat >>
			greenTextureRepeat >>
			blueTextureRepeat >>
			normalMapPath >>
			redNormalMapPath >>
			greenNormalMapPath >>
			blueNormalMapPath >>
			isSpecular >>
			specularShininess >>
			specularIntensity;

		// Convert empty string
		heightMapPath = (heightMapPath == "?") ? "" : heightMapPath;
		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
		redNormalMapPath = (redNormalMapPath == "?") ? "" : redNormalMapPath;
		greenNormalMapPath = (greenNormalMapPath == "?") ? "" : greenNormalMapPath;
		blueNormalMapPath = (blueNormalMapPath == "?") ? "" : blueNormalMapPath;
		blendMapPath = (blendMapPath == "?") ? "" : blendMapPath;
		redDiffuseMapPath = (redDiffuseMapPath == "?") ? "" : redDiffuseMapPath;
		greenDiffuseMapPath = (greenDiffuseMapPath == "?") ? "" : greenDiffuseMapPath;
		blueDiffuseMapPath = (blueDiffuseMapPath == "?") ? "" : blueDiffuseMapPath;

		// Convert spaces
		replace(heightMapPath.begin(), heightMapPath.end(), '?', ' ');
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		replace(redNormalMapPath.begin(), redNormalMapPath.end(), '?', ' ');
		replace(greenNormalMapPath.begin(), greenNormalMapPath.end(), '?', ' ');
		replace(blueNormalMapPath.begin(), blueNormalMapPath.end(), '?', ' ');
		replace(blendMapPath.begin(), blendMapPath.end(), '?', ' ');
		replace(redDiffuseMapPath.begin(), redDiffuseMapPath.end(), '?', ' ');
		replace(greenDiffuseMapPath.begin(), greenDiffuseMapPath.end(), '?', ' ');
		replace(blueDiffuseMapPath.begin(), blueDiffuseMapPath.end(), '?', ' ');

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
			if(!redNormalMapPath.empty())
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					redNormalMapPath = string("projects\\" + _currentProjectID + "\\" + redNormalMapPath);
				}

				// Set path
				_fe3d.terrain_setRedNormalMap(terrainID, redNormalMapPath);
			}

			// Normal map G
			if(!greenNormalMapPath.empty())
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					greenNormalMapPath = string("projects\\" + _currentProjectID + "\\" + greenNormalMapPath);
				}

				// Set path
				_fe3d.terrain_setGreenNormalMap(terrainID, greenNormalMapPath);
			}

			// Normal map B
			if(!blueNormalMapPath.empty())
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					blueNormalMapPath = string("projects\\" + _currentProjectID + "\\" + blueNormalMapPath);
				}

				// Set path
				_fe3d.terrain_setBlueNormalMap(terrainID, blueNormalMapPath);
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
			if(!redDiffuseMapPath.empty())
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					redDiffuseMapPath = string("projects\\" + _currentProjectID + "\\" + redDiffuseMapPath);
				}

				// Set path
				_fe3d.terrain_setRedDiffuseMap(terrainID, redDiffuseMapPath);
			}

			// Blend map G
			if(!greenDiffuseMapPath.empty())
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					greenDiffuseMapPath = string("projects\\" + _currentProjectID + "\\" + greenDiffuseMapPath);
				}

				// Set path
				_fe3d.terrain_setGreenDiffuseMap(terrainID, greenDiffuseMapPath);
			}

			// Blend map B
			if(!blueDiffuseMapPath.empty())
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					blueDiffuseMapPath = string("projects\\" + _currentProjectID + "\\" + blueDiffuseMapPath);
				}

				// Set path
				_fe3d.terrain_setBlueDiffuseMap(terrainID, blueDiffuseMapPath);
			}

			// Set properties
			_fe3d.terrain_setMaxHeight(terrainID, maxHeight);
			_fe3d.terrain_setTextureRepeat(terrainID, textureRepeat);
			_fe3d.terrain_setLightness(terrainID, lightness);
			_fe3d.terrain_setRedTextureRepeat(terrainID, redTextureRepeat);
			_fe3d.terrain_setGreenTextureRepeat(terrainID, greenTextureRepeat);
			_fe3d.terrain_setBlueTextureRepeat(terrainID, blueTextureRepeat);
			_fe3d.terrain_setSpecular(terrainID, isSpecular);
			_fe3d.terrain_setSpecularShininess(terrainID, specularShininess);
			_fe3d.terrain_setSpecularIntensity(terrainID, specularIntensity);
		}
	}

	file.close();

	Logger::throwInfo("Terrain data loaded!");

	return true;
}