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

	if(_currentProjectId.empty())
	{
		Logger::throwError("WaterEditor::saveToFile");
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + _currentProjectId + "\\data\\water.fe3d");

	for(const auto& waterId : _loadedWaterIds)
	{
		auto dudvMapPath = _fe3d->water_getDudvMapPath(waterId);
		auto normalMapPath = _fe3d->water_getNormalMapPath(waterId);
		auto displacementMapPath = _fe3d->water_getDisplacementMapPath(waterId);
		auto color = _fe3d->water_getColor(waterId);
		auto height = _fe3d->water_getHeight(waterId);
		auto speed = _fe3d->water_getSpeed(waterId);
		auto size = _fe3d->water_getSize(waterId);
		auto textureRepeat = _fe3d->water_getTextureRepeat(waterId);
		auto waveHeight = _fe3d->water_getWaveHeight(waterId);
		auto opacity = _fe3d->water_getOpacity(waterId);
		auto specularShininess = _fe3d->water_getSpecularShininess(waterId);
		auto specularIntensity = _fe3d->water_getSpecularIntensity(waterId);
		auto quality = static_cast<unsigned int>(_fe3d->water_getQuality(waterId));
		auto isSpecular = _fe3d->water_isSpecular(waterId);
		auto isReflective = _fe3d->water_isReflective(waterId);
		auto isRefractive = _fe3d->water_isRefractive(waterId);

		dudvMapPath = string(dudvMapPath.empty() ? "" : dudvMapPath.substr(string("projects\\" + _currentProjectId + "\\").size()));
		normalMapPath = string(normalMapPath.empty() ? "" : normalMapPath.substr(string("projects\\" + _currentProjectId + "\\").size()));
		displacementMapPath = string(displacementMapPath.empty() ? "" : displacementMapPath.substr(string("projects\\" + _currentProjectId + "\\").size()));

		dudvMapPath = (dudvMapPath.empty() ? "?" : dudvMapPath);
		normalMapPath = (normalMapPath.empty() ? "?" : normalMapPath);
		displacementMapPath = (displacementMapPath.empty() ? "?" : displacementMapPath);

		replace(dudvMapPath.begin(), dudvMapPath.end(), ' ', '?');
		replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
		replace(displacementMapPath.begin(), displacementMapPath.end(), ' ', '?');

		file <<
			waterId << " " <<
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
			opacity << " " <<
			specularShininess << " " <<
			specularIntensity << endl;
	}

	file.close();

	Logger::throwInfo("Water editor data saved!");

	return true;
}