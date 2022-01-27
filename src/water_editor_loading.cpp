#include "water_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> WaterEditor::getImagePathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && _currentProjectId.empty())
	{
		Logger::throwError("WaterEditor::getImagePathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "data\\water.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `water.fe3d` missing!");
		return {};
	}

	vector<string> imagePaths;
	string line;
	while(getline(file, line))
	{
		string waterId;
		string dudvMapPath;
		string normalMapPath;
		string displacementMapPath;

		istringstream iss(line);

		iss >>
			waterId >>
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
				dudvMapPath = string("projects\\" + _currentProjectId + "\\" + dudvMapPath);
			}

			imagePaths.push_back(dudvMapPath);
		}

		if(!normalMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				normalMapPath = string("projects\\" + _currentProjectId + "\\" + normalMapPath);
			}

			imagePaths.push_back(normalMapPath);
		}

		if(!displacementMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				displacementMapPath = string("projects\\" + _currentProjectId + "\\" + displacementMapPath);
			}

			imagePaths.push_back(displacementMapPath);
		}
	}

	file.close();

	return imagePaths;
}

const bool WaterEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && _currentProjectId.empty())
	{
		Logger::throwError("WaterEditor::loadFromFile");
	}

	_loadedWaterIds.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "data\\water.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `water.fe3d` missing!");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string waterId;
		string dudvMapPath;
		string normalMapPath;
		string displacementMapPath;
		fvec3 color;
		fvec2 speed;
		float height;
		float size;
		float textureRepeat;
		float waveHeight;
		float specularShininess;
		float specularIntensity;
		float maxDepth;
		unsigned int quality;
		bool isSpecular;
		bool isReflective;
		bool isRefractive;
		bool isEdged;

		istringstream iss(line);

		iss >>
			waterId >>
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
			isEdged >>
			specularShininess >>
			specularIntensity >>
			maxDepth;

		dudvMapPath = (dudvMapPath == "?" ? "" : dudvMapPath);
		normalMapPath = (normalMapPath == "?" ? "" : normalMapPath);
		displacementMapPath = (displacementMapPath == "?" ? "" : displacementMapPath);

		replace(dudvMapPath.begin(), dudvMapPath.end(), '?', ' ');
		replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		replace(displacementMapPath.begin(), displacementMapPath.end(), '?', ' ');

		_fe3d->water_create(waterId);

		if(_fe3d->water_isExisting(waterId))
		{
			_loadedWaterIds.push_back(waterId);

			_fe3d->water_setHeight(waterId, height);
			_fe3d->water_setSize(waterId, size);
			_fe3d->water_setSpecular(waterId, isSpecular);
			_fe3d->water_setReflective(waterId, isReflective);
			_fe3d->water_setRefractive(waterId, isRefractive);
			_fe3d->water_setWaveHeight(waterId, waveHeight);
			_fe3d->water_setQuality(waterId, static_cast<WaterQuality>(quality));
			_fe3d->water_setSpecularShininess(waterId, specularShininess);
			_fe3d->water_setSpecularIntensity(waterId, specularIntensity);
			_fe3d->water_setEdged(waterId, isEdged);
			_fe3d->water_setColor(waterId, color);
			_fe3d->water_setTextureRepeat(waterId, textureRepeat);
			_fe3d->water_setSpeed(waterId, speed);
			_fe3d->water_setMaxDepth(waterId, maxDepth);

			if(!dudvMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					dudvMapPath = string("projects\\" + _currentProjectId + "\\" + dudvMapPath);
				}

				_fe3d->water_setDudvMap(waterId, dudvMapPath);
			}

			if(!normalMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					normalMapPath = string("projects\\" + _currentProjectId + "\\" + normalMapPath);
				}

				_fe3d->water_setNormalMap(waterId, normalMapPath);
			}

			if(!displacementMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					displacementMapPath = string("projects\\" + _currentProjectId + "\\" + displacementMapPath);
				}

				_fe3d->water_setDisplacementMap(waterId, displacementMapPath);
			}
		}
	}

	file.close();

	Logger::throwInfo("Water editor data loaded!");

	return true;
}