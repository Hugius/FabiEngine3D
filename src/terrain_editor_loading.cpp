#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> TerrainEditor::getImagePathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("TerrainEditor::getImagePathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\terrain.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `terrain.fe3d` missing!");
		return {};
	}

	vector<string> imagePaths;
	string line;
	while(getline(file, line))
	{
		string terrainID, heightMapPath, diffuseMapPath, normalMapPath,
			redNormalMapPath, greenNormalMapPath, blueNormalMapPath,
			blendMapPath, redDiffuseMapPath, greenDiffuseMapPath, blueDiffuseMapPath;
		float maxHeight, textureRepeat, lightness, redTextureRepeat, greenTextureRepeat, blueTextureRepeat;

		istringstream iss(line);

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

		if(!heightMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				heightMapPath = string("projects\\" + _currentProjectID + "\\" + heightMapPath);
			}

			imagePaths.push_back(heightMapPath);
		}

		if(!diffuseMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
			}

			imagePaths.push_back(diffuseMapPath);
		}

		if(!normalMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				normalMapPath = string("projects\\" + _currentProjectID + "\\" + normalMapPath);
			}

			imagePaths.push_back(normalMapPath);
		}

		if(!redNormalMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				redNormalMapPath = string("projects\\" + _currentProjectID + "\\" + redNormalMapPath);
			}

			imagePaths.push_back(redNormalMapPath);
		}

		if(!greenNormalMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				greenNormalMapPath = string("projects\\" + _currentProjectID + "\\" + greenNormalMapPath);
			}

			imagePaths.push_back(greenNormalMapPath);
		}

		if(!blueNormalMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				blueNormalMapPath = string("projects\\" + _currentProjectID + "\\" + blueNormalMapPath);
			}

			imagePaths.push_back(blueNormalMapPath);
		}

		if(!blendMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				blendMapPath = string("projects\\" + _currentProjectID + "\\" + blendMapPath);
			}

			imagePaths.push_back(blendMapPath);
		}

		if(!redDiffuseMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				redDiffuseMapPath = string("projects\\" + _currentProjectID + "\\" + redDiffuseMapPath);
			}

			imagePaths.push_back(redDiffuseMapPath);
		}

		if(!greenDiffuseMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				greenDiffuseMapPath = string("projects\\" + _currentProjectID + "\\" + greenDiffuseMapPath);
			}

			imagePaths.push_back(greenDiffuseMapPath);
		}

		if(!blueDiffuseMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				blueDiffuseMapPath = string("projects\\" + _currentProjectID + "\\" + blueDiffuseMapPath);
			}

			imagePaths.push_back(blueDiffuseMapPath);
		}
	}

	file.close();

	return imagePaths;
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
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\terrain.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `terrain.fe3d` missing!");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string terrainID, heightMapPath, diffuseMapPath, normalMapPath,
			redNormalMapPath, greenNormalMapPath, blueNormalMapPath,
			blendMapPath, redDiffuseMapPath, greenDiffuseMapPath, blueDiffuseMapPath;
		float maxHeight, textureRepeat, lightness, redTextureRepeat, greenTextureRepeat, blueTextureRepeat, specularShininess, specularIntensity;
		bool isSpecular;

		istringstream iss(line);

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

		if(!Config::getInst().isApplicationExported())
		{
			heightMapPath = string("projects\\" + _currentProjectID + "\\" + heightMapPath);
		}

		_fe3d->terrain_create(terrainID, heightMapPath);

		if(_fe3d->terrain_isExisting(terrainID))
		{
			_loadedTerrainIDs.push_back(terrainID);

			_fe3d->terrain_setMaxHeight(terrainID, maxHeight);
			_fe3d->terrain_setTextureRepeat(terrainID, textureRepeat);
			_fe3d->terrain_setLightness(terrainID, lightness);
			_fe3d->terrain_setRedTextureRepeat(terrainID, redTextureRepeat);
			_fe3d->terrain_setGreenTextureRepeat(terrainID, greenTextureRepeat);
			_fe3d->terrain_setBlueTextureRepeat(terrainID, blueTextureRepeat);
			_fe3d->terrain_setSpecular(terrainID, isSpecular);
			_fe3d->terrain_setSpecularShininess(terrainID, specularShininess);
			_fe3d->terrain_setSpecularIntensity(terrainID, specularIntensity);

			if(!diffuseMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
				}

				_fe3d->terrain_setDiffuseMap(terrainID, diffuseMapPath);
			}

			if(!normalMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					normalMapPath = string("projects\\" + _currentProjectID + "\\" + normalMapPath);
				}

				_fe3d->terrain_setNormalMap(terrainID, normalMapPath);
			}

			if(!redNormalMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					redNormalMapPath = string("projects\\" + _currentProjectID + "\\" + redNormalMapPath);
				}

				_fe3d->terrain_setRedNormalMap(terrainID, redNormalMapPath);
			}

			if(!greenNormalMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					greenNormalMapPath = string("projects\\" + _currentProjectID + "\\" + greenNormalMapPath);
				}

				_fe3d->terrain_setGreenNormalMap(terrainID, greenNormalMapPath);
			}

			if(!blueNormalMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					blueNormalMapPath = string("projects\\" + _currentProjectID + "\\" + blueNormalMapPath);
				}

				_fe3d->terrain_setBlueNormalMap(terrainID, blueNormalMapPath);
			}

			if(!blendMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					blendMapPath = string("projects\\" + _currentProjectID + "\\" + blendMapPath);
				}

				_fe3d->terrain_setBlendMap(terrainID, blendMapPath);
			}

			if(!redDiffuseMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					redDiffuseMapPath = string("projects\\" + _currentProjectID + "\\" + redDiffuseMapPath);
				}

				_fe3d->terrain_setRedDiffuseMap(terrainID, redDiffuseMapPath);
			}

			if(!greenDiffuseMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					greenDiffuseMapPath = string("projects\\" + _currentProjectID + "\\" + greenDiffuseMapPath);
				}

				_fe3d->terrain_setGreenDiffuseMap(terrainID, greenDiffuseMapPath);
			}

			if(!blueDiffuseMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					blueDiffuseMapPath = string("projects\\" + _currentProjectID + "\\" + blueDiffuseMapPath);
				}

				_fe3d->terrain_setBlueDiffuseMap(terrainID, blueDiffuseMapPath);
			}
		}
	}

	file.close();

	Logger::throwInfo("Terrain editor data loaded!");

	return true;
}