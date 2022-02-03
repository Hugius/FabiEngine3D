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
	if(!Config::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\terrain.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `terrain.fe3d` missing");
		return {};
	}

	vector<string> imagePaths;
	string line;
	while(getline(file, line))
	{
		string terrainId;
		string heightMapPath;
		string diffuseMapPath;
		string normalMapPath;
		string redNormalMapPath;
		string greenNormalMapPath;
		string blueNormalMapPath;
		string blendMapPath;
		string redDiffuseMapPath;
		string greenDiffuseMapPath;
		string blueDiffuseMapPath;
		float maxHeight;
		float textureRepeat;
		float lightness;
		float redTextureRepeat;
		float greenTextureRepeat;
		float blueTextureRepeat;

		istringstream iss(line);

		iss
			>> terrainId
			>> heightMapPath
			>> diffuseMapPath
			>> maxHeight
			>> textureRepeat
			>> lightness
			>> blendMapPath
			>> redDiffuseMapPath
			>> greenDiffuseMapPath
			>> blueDiffuseMapPath
			>> redTextureRepeat
			>> greenTextureRepeat
			>> blueTextureRepeat
			>> normalMapPath
			>> redNormalMapPath
			>> greenNormalMapPath
			>> blueNormalMapPath;

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
				heightMapPath = string("projects\\" + getCurrentProjectId() + "\\" + heightMapPath);
			}

			imagePaths.push_back(heightMapPath);
		}

		if(!diffuseMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				diffuseMapPath = string("projects\\" + getCurrentProjectId() + "\\" + diffuseMapPath);
			}

			imagePaths.push_back(diffuseMapPath);
		}

		if(!normalMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				normalMapPath = string("projects\\" + getCurrentProjectId() + "\\" + normalMapPath);
			}

			imagePaths.push_back(normalMapPath);
		}

		if(!redNormalMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				redNormalMapPath = string("projects\\" + getCurrentProjectId() + "\\" + redNormalMapPath);
			}

			imagePaths.push_back(redNormalMapPath);
		}

		if(!greenNormalMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				greenNormalMapPath = string("projects\\" + getCurrentProjectId() + "\\" + greenNormalMapPath);
			}

			imagePaths.push_back(greenNormalMapPath);
		}

		if(!blueNormalMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				blueNormalMapPath = string("projects\\" + getCurrentProjectId() + "\\" + blueNormalMapPath);
			}

			imagePaths.push_back(blueNormalMapPath);
		}

		if(!blendMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				blendMapPath = string("projects\\" + getCurrentProjectId() + "\\" + blendMapPath);
			}

			imagePaths.push_back(blendMapPath);
		}

		if(!redDiffuseMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				redDiffuseMapPath = string("projects\\" + getCurrentProjectId() + "\\" + redDiffuseMapPath);
			}

			imagePaths.push_back(redDiffuseMapPath);
		}

		if(!greenDiffuseMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				greenDiffuseMapPath = string("projects\\" + getCurrentProjectId() + "\\" + greenDiffuseMapPath);
			}

			imagePaths.push_back(greenDiffuseMapPath);
		}

		if(!blueDiffuseMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				blueDiffuseMapPath = string("projects\\" + getCurrentProjectId() + "\\" + blueDiffuseMapPath);
			}

			imagePaths.push_back(blueDiffuseMapPath);
		}
	}

	file.close();

	return imagePaths;
}

const bool TerrainEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	_loadedTerrainIds.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\terrain.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `terrain.fe3d` missing");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string terrainId;
		string heightMapPath;
		string diffuseMapPath;
		string normalMapPath;
		string redNormalMapPath;
		string greenNormalMapPath;
		string blueNormalMapPath;
		string blendMapPath;
		string redDiffuseMapPath;
		string greenDiffuseMapPath;
		string blueDiffuseMapPath;
		float maxHeight;
		float textureRepeat;
		float lightness;
		float redTextureRepeat;
		float greenTextureRepeat;
		float blueTextureRepeat;
		float specularShininess;
		float specularIntensity;
		bool isSpecular;

		istringstream iss(line);

		iss
			>> terrainId
			>> heightMapPath
			>> diffuseMapPath
			>> maxHeight
			>> textureRepeat
			>> lightness
			>> blendMapPath
			>> redDiffuseMapPath
			>> greenDiffuseMapPath
			>> blueDiffuseMapPath
			>> redTextureRepeat
			>> greenTextureRepeat
			>> blueTextureRepeat
			>> normalMapPath
			>> redNormalMapPath
			>> greenNormalMapPath
			>> blueNormalMapPath
			>> isSpecular
			>> specularShininess
			>> specularIntensity;

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
			heightMapPath = string("projects\\" + getCurrentProjectId() + "\\" + heightMapPath);
		}

		_fe3d->terrain_create(terrainId, heightMapPath);

		if(_fe3d->terrain_isExisting(terrainId))
		{
			_loadedTerrainIds.push_back(terrainId);

			_fe3d->terrain_setMaxHeight(terrainId, maxHeight);
			_fe3d->terrain_setTextureRepeat(terrainId, textureRepeat);
			_fe3d->terrain_setLightness(terrainId, lightness);
			_fe3d->terrain_setRedTextureRepeat(terrainId, redTextureRepeat);
			_fe3d->terrain_setGreenTextureRepeat(terrainId, greenTextureRepeat);
			_fe3d->terrain_setBlueTextureRepeat(terrainId, blueTextureRepeat);
			_fe3d->terrain_setSpecular(terrainId, isSpecular);
			_fe3d->terrain_setSpecularShininess(terrainId, specularShininess);
			_fe3d->terrain_setSpecularIntensity(terrainId, specularIntensity);

			if(!diffuseMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					diffuseMapPath = string("projects\\" + getCurrentProjectId() + "\\" + diffuseMapPath);
				}

				_fe3d->terrain_setDiffuseMap(terrainId, diffuseMapPath);
			}

			if(!normalMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					normalMapPath = string("projects\\" + getCurrentProjectId() + "\\" + normalMapPath);
				}

				_fe3d->terrain_setNormalMap(terrainId, normalMapPath);
			}

			if(!redNormalMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					redNormalMapPath = string("projects\\" + getCurrentProjectId() + "\\" + redNormalMapPath);
				}

				_fe3d->terrain_setRedNormalMap(terrainId, redNormalMapPath);
			}

			if(!greenNormalMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					greenNormalMapPath = string("projects\\" + getCurrentProjectId() + "\\" + greenNormalMapPath);
				}

				_fe3d->terrain_setGreenNormalMap(terrainId, greenNormalMapPath);
			}

			if(!blueNormalMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					blueNormalMapPath = string("projects\\" + getCurrentProjectId() + "\\" + blueNormalMapPath);
				}

				_fe3d->terrain_setBlueNormalMap(terrainId, blueNormalMapPath);
			}

			if(!blendMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					blendMapPath = string("projects\\" + getCurrentProjectId() + "\\" + blendMapPath);
				}

				_fe3d->terrain_setBlendMap(terrainId, blendMapPath);
			}

			if(!redDiffuseMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					redDiffuseMapPath = string("projects\\" + getCurrentProjectId() + "\\" + redDiffuseMapPath);
				}

				_fe3d->terrain_setRedDiffuseMap(terrainId, redDiffuseMapPath);
			}

			if(!greenDiffuseMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					greenDiffuseMapPath = string("projects\\" + getCurrentProjectId() + "\\" + greenDiffuseMapPath);
				}

				_fe3d->terrain_setGreenDiffuseMap(terrainId, greenDiffuseMapPath);
			}

			if(!blueDiffuseMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					blueDiffuseMapPath = string("projects\\" + getCurrentProjectId() + "\\" + blueDiffuseMapPath);
				}

				_fe3d->terrain_setBlueDiffuseMap(terrainId, blueDiffuseMapPath);
			}
		}
	}

	file.close();

	Logger::throwInfo("Terrain editor data loaded");

	return true;
}