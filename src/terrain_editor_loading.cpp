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
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\terrain.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `terrain.fe3d` does not exist");


		return {};
	}

	vector<string> imagePaths = {};
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

		auto iss = istringstream(line);

		iss
			>> terrainId
			>> heightMapPath
			>> diffuseMapPath
			>> blendMapPath
			>> redDiffuseMapPath
			>> greenDiffuseMapPath
			>> blueDiffuseMapPath
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
			if(!Configuration::getInst().isApplicationExported())
			{
				heightMapPath = ("projects\\" + getCurrentProjectId() + "\\" + heightMapPath);
			}

			imagePaths.push_back(heightMapPath);
		}

		if(!diffuseMapPath.empty())
		{
			if(!Configuration::getInst().isApplicationExported())
			{
				diffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + diffuseMapPath);
			}

			imagePaths.push_back(diffuseMapPath);
		}

		if(!normalMapPath.empty())
		{
			if(!Configuration::getInst().isApplicationExported())
			{
				normalMapPath = ("projects\\" + getCurrentProjectId() + "\\" + normalMapPath);
			}

			imagePaths.push_back(normalMapPath);
		}

		if(!redNormalMapPath.empty())
		{
			if(!Configuration::getInst().isApplicationExported())
			{
				redNormalMapPath = ("projects\\" + getCurrentProjectId() + "\\" + redNormalMapPath);
			}

			imagePaths.push_back(redNormalMapPath);
		}

		if(!greenNormalMapPath.empty())
		{
			if(!Configuration::getInst().isApplicationExported())
			{
				greenNormalMapPath = ("projects\\" + getCurrentProjectId() + "\\" + greenNormalMapPath);
			}

			imagePaths.push_back(greenNormalMapPath);
		}

		if(!blueNormalMapPath.empty())
		{
			if(!Configuration::getInst().isApplicationExported())
			{
				blueNormalMapPath = ("projects\\" + getCurrentProjectId() + "\\" + blueNormalMapPath);
			}

			imagePaths.push_back(blueNormalMapPath);
		}

		if(!blendMapPath.empty())
		{
			if(!Configuration::getInst().isApplicationExported())
			{
				blendMapPath = ("projects\\" + getCurrentProjectId() + "\\" + blendMapPath);
			}

			imagePaths.push_back(blendMapPath);
		}

		if(!redDiffuseMapPath.empty())
		{
			if(!Configuration::getInst().isApplicationExported())
			{
				redDiffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + redDiffuseMapPath);
			}

			imagePaths.push_back(redDiffuseMapPath);
		}

		if(!greenDiffuseMapPath.empty())
		{
			if(!Configuration::getInst().isApplicationExported())
			{
				greenDiffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + greenDiffuseMapPath);
			}

			imagePaths.push_back(greenDiffuseMapPath);
		}

		if(!blueDiffuseMapPath.empty())
		{
			if(!Configuration::getInst().isApplicationExported())
			{
				blueDiffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + blueDiffuseMapPath);
			}

			imagePaths.push_back(blueDiffuseMapPath);
		}
	}

	file.close();

	return imagePaths;
}

const bool TerrainEditor::loadTerrainsFromFile()
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\terrain.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `terrain.fe3d` does not exist");

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
		fvec3 color;
		float maxHeight;
		float lightness;
		float specularShininess;
		float specularIntensity;
		int textureRepeat;
		int redTextureRepeat;
		int greenTextureRepeat;
		int blueTextureRepeat;
		bool isSpecular;

		auto iss = istringstream(line);

		iss
			>> terrainId
			>> heightMapPath
			>> diffuseMapPath
			>> blendMapPath
			>> redDiffuseMapPath
			>> greenDiffuseMapPath
			>> blueDiffuseMapPath
			>> normalMapPath
			>> redNormalMapPath
			>> greenNormalMapPath
			>> blueNormalMapPath
			>> maxHeight
			>> textureRepeat
			>> lightness
			>> color.r
			>> color.g
			>> color.b
			>> redTextureRepeat
			>> greenTextureRepeat
			>> blueTextureRepeat
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

		if(!Configuration::getInst().isApplicationExported())
		{
			heightMapPath = ("projects\\" + getCurrentProjectId() + "\\" + heightMapPath);
		}

		_fe3d->terrain_create(terrainId, heightMapPath);

		if(_fe3d->terrain_isExisting(terrainId))
		{
			_fe3d->terrain_setMaxHeight(terrainId, maxHeight);
			_fe3d->terrain_setTextureRepeat(terrainId, textureRepeat);
			_fe3d->terrain_setLightness(terrainId, lightness);
			_fe3d->terrain_setColor(terrainId, color);
			_fe3d->terrain_setRedTextureRepeat(terrainId, redTextureRepeat);
			_fe3d->terrain_setGreenTextureRepeat(terrainId, greenTextureRepeat);
			_fe3d->terrain_setBlueTextureRepeat(terrainId, blueTextureRepeat);
			_fe3d->terrain_setSpecular(terrainId, isSpecular);
			_fe3d->terrain_setSpecularShininess(terrainId, specularShininess);
			_fe3d->terrain_setSpecularIntensity(terrainId, specularIntensity);

			if(!diffuseMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					diffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + diffuseMapPath);
				}

				_fe3d->terrain_setDiffuseMap(terrainId, diffuseMapPath);
			}

			if(!normalMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					normalMapPath = ("projects\\" + getCurrentProjectId() + "\\" + normalMapPath);
				}

				_fe3d->terrain_setNormalMap(terrainId, normalMapPath);
			}

			if(!redNormalMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					redNormalMapPath = ("projects\\" + getCurrentProjectId() + "\\" + redNormalMapPath);
				}

				_fe3d->terrain_setRedNormalMap(terrainId, redNormalMapPath);
			}

			if(!greenNormalMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					greenNormalMapPath = ("projects\\" + getCurrentProjectId() + "\\" + greenNormalMapPath);
				}

				_fe3d->terrain_setGreenNormalMap(terrainId, greenNormalMapPath);
			}

			if(!blueNormalMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					blueNormalMapPath = ("projects\\" + getCurrentProjectId() + "\\" + blueNormalMapPath);
				}

				_fe3d->terrain_setBlueNormalMap(terrainId, blueNormalMapPath);
			}

			if(!blendMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					blendMapPath = ("projects\\" + getCurrentProjectId() + "\\" + blendMapPath);
				}

				_fe3d->terrain_setBlendMap(terrainId, blendMapPath);
			}

			if(!redDiffuseMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					redDiffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + redDiffuseMapPath);
				}

				_fe3d->terrain_setRedDiffuseMap(terrainId, redDiffuseMapPath);
			}

			if(!greenDiffuseMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					greenDiffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + greenDiffuseMapPath);
				}

				_fe3d->terrain_setGreenDiffuseMap(terrainId, greenDiffuseMapPath);
			}

			if(!blueDiffuseMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					blueDiffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + blueDiffuseMapPath);
				}

				_fe3d->terrain_setBlueDiffuseMap(terrainId, blueDiffuseMapPath);
			}

			_loadedTerrainIds.push_back(terrainId);

			sort(_loadedTerrainIds.begin(), _loadedTerrainIds.end());
		}
	}

	file.close();

	Logger::throwInfo("Terrain editor data loaded");

	return true;
}