#include "water_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> WaterEditor::getTexturePathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("WaterEditor::getTexturePathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\water.fe3d");

	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `water.fe3d` missing!");
		return {};
	}

	ifstream file(filePath);

	vector<string> texturePaths;
	string line;
	while(getline(file, line))
	{
		string waterID, dudvMapPath, normalMapPath, displacementMapPath;

		istringstream iss(line);

		iss >>
			waterID >>
			dudvMapPath >>
			normalMapPath >>
			displacementMapPath;

		dudvMapPath = (dudvMapPath == "?" ? "" : dudvMapPath);
		normalMapPath = (normalMapPath == "?" ? "" : normalMapPath);
		displacementMapPath = (displacementMapPath == "?" ? "" : displacementMapPath);

		replace(dudvMapPath.begin(), dudvMapPath.end(), '?', ' ');
		replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		replace(displacementMapPath.begin(), displacementMapPath.end(), '?', ' ');

		if(!dudvMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				dudvMapPath = string("projects\\" + _currentProjectID + "\\" + dudvMapPath);
			}

			texturePaths.push_back(dudvMapPath);
		}

		if(!normalMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				normalMapPath = string("projects\\" + _currentProjectID + "\\" + normalMapPath);
			}

			texturePaths.push_back(normalMapPath);
		}

		if(!displacementMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				displacementMapPath = string("projects\\" + _currentProjectID + "\\" + displacementMapPath);
			}

			texturePaths.push_back(displacementMapPath);
		}
	}

	file.close();

	return texturePaths;
}

const bool WaterEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("WaterEditor::loadFromFile");
	}

	_loadedWaterIDs.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\water.fe3d");

	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `water.fe3d` missing!");
		return false;
	}

	ifstream file(filePath);

	string line;
	while(getline(file, line))
	{
		string waterID, dudvMapPath, normalMapPath, displacementMapPath;
		fvec3 color;
		fvec2 speed;
		float height, size, textureRepeat, waveHeight, transparency, specularShininess, specularIntensity;
		unsigned int quality;
		bool isSpecular, isReflective, isRefractive;

		istringstream iss(line);

		iss >>
			waterID >>
			dudvMapPath >>
			normalMapPath >>
			displacementMapPath >>
			isSpecular >>
			isReflective >>
			isRefractive >>
			color.r >>
			color.g >>
			color.b >>
			size >>
			height >>
			textureRepeat >>
			waveHeight >>
			quality >>
			speed.x >>
			speed.y >>
			transparency >>
			specularShininess >>
			specularIntensity;

		dudvMapPath = (dudvMapPath == "?" ? "" : dudvMapPath);
		normalMapPath = (normalMapPath == "?" ? "" : normalMapPath);
		displacementMapPath = (displacementMapPath == "?" ? "" : displacementMapPath);

		replace(dudvMapPath.begin(), dudvMapPath.end(), '?', ' ');
		replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		replace(displacementMapPath.begin(), displacementMapPath.end(), '?', ' ');

		_fe3d.water_create(waterID);

		if(_fe3d.water_isExisting(waterID))
		{
			_loadedWaterIDs.push_back(waterID);

			if(!dudvMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					dudvMapPath = string("projects\\" + _currentProjectID + "\\" + dudvMapPath);
				}

				_fe3d.water_setDudvMap(waterID, dudvMapPath);
			}

			if(!normalMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					normalMapPath = string("projects\\" + _currentProjectID + "\\" + normalMapPath);
				}

				_fe3d.water_setNormalMap(waterID, normalMapPath);
			}

			if(!displacementMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					displacementMapPath = string("projects\\" + _currentProjectID + "\\" + displacementMapPath);
				}

				_fe3d.water_setDisplacementMap(waterID, displacementMapPath);
			}

			_fe3d.water_setHeight(waterID, height);
			_fe3d.water_setSize(waterID, size);
			_fe3d.water_setSpecular(waterID, isSpecular);
			_fe3d.water_setReflective(waterID, isReflective);
			_fe3d.water_setRefractive(waterID, isRefractive);
			_fe3d.water_setWaveHeight(waterID, waveHeight);
			_fe3d.water_setQuality(waterID, static_cast<WaterQuality>(quality));
			_fe3d.water_setSpecularShininess(waterID, specularShininess);
			_fe3d.water_setSpecularIntensity(waterID, specularIntensity);
			_fe3d.water_setTransparency(waterID, transparency);
			_fe3d.water_setColor(waterID, color);
			_fe3d.water_setTextureRepeat(waterID, textureRepeat);
			_fe3d.water_setSpeed(waterID, speed);
		}
	}

	file.close();

	Logger::throwInfo("Water data loaded!");

	return true;
}