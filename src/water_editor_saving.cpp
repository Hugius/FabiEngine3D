#include "water_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool WaterEditor::saveToFile() const
{
	if(!_isEditorLoaded)
	{
		return false;
	}

	if(_currentProjectID.empty())
	{
		Logger::throwError("WaterEditor::saveToFile");
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + _currentProjectID + "\\data\\water.fe3d");

	for(const auto& waterID : _loadedWaterIDs)
	{
		auto dudvMapPath = _fe3d.water_getDudvMapPath(waterID);
		auto normalMapPath = _fe3d.water_getNormalMapPath(waterID);
		auto displacementMapPath = _fe3d.water_getDisplacementMapPath(waterID);
		auto color = _fe3d.water_getColor(waterID);
		auto height = _fe3d.water_getHeight(waterID);
		auto speed = _fe3d.water_getSpeed(waterID);
		auto size = _fe3d.water_getSize(waterID);
		auto textureRepeat = _fe3d.water_getTextureRepeat(waterID);
		auto waveHeight = _fe3d.water_getWaveHeight(waterID);
		auto transparency = _fe3d.water_getTransparency(waterID);
		auto specularShininess = _fe3d.water_getSpecularShininess(waterID);
		auto specularIntensity = _fe3d.water_getSpecularIntensity(waterID);
		auto quality = static_cast<unsigned int>(_fe3d.water_getQuality(waterID));
		auto isSpecular = _fe3d.water_isSpecular(waterID);
		auto isReflective = _fe3d.water_isReflective(waterID);
		auto isRefractive = _fe3d.water_isRefractive(waterID);

		dudvMapPath = string(dudvMapPath.empty() ? "" : dudvMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		normalMapPath = string(normalMapPath.empty() ? "" : normalMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		displacementMapPath = string(displacementMapPath.empty() ? "" : displacementMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

		dudvMapPath = (dudvMapPath.empty() ? "?" : dudvMapPath);
		normalMapPath = (normalMapPath.empty() ? "?" : normalMapPath);
		displacementMapPath = (displacementMapPath.empty() ? "?" : displacementMapPath);

		replace(dudvMapPath.begin(), dudvMapPath.end(), ' ', '?');
		replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
		replace(displacementMapPath.begin(), displacementMapPath.end(), ' ', '?');

		file <<
			waterID << " " <<
			dudvMapPath << " " <<
			normalMapPath << " " <<
			displacementMapPath << " " <<
			isSpecular << " " <<
			isReflective << " " <<
			isRefractive << " " <<
			color.r << " " <<
			color.g << " " <<
			color.b << " " <<
			size << " " <<
			height << " " <<
			textureRepeat << " " <<
			waveHeight << " " <<
			quality << " " <<
			speed.x << " " <<
			speed.y << " " <<
			transparency << " " <<
			specularShininess << " " <<
			specularIntensity << endl;
	}

	file.close();

	Logger::throwInfo("Water editor data saved!");

	return true;
}