#include "water_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool WaterEditor::saveToFile() const
{
	if(!isLoaded())
	{
		return false;
	}

	if(getCurrentProjectId().empty())
	{
		Logger::throwError("WaterEditor::saveToFile");
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\water.fe3d");

	for(const auto& waterId : _loadedWaterIds)
	{
		auto dudvMapPath = _fe3d->water_getDudvMapPath(waterId);
		auto normalMapPath = _fe3d->water_getNormalMapPath(waterId);
		auto displacementMapPath = _fe3d->water_getDisplacementMapPath(waterId);
		auto color = _fe3d->water_getColor(waterId);
		auto height = _fe3d->water_getHeight(waterId);
		auto rippleSpeed = _fe3d->water_getRippleSpeed(waterId);
		auto waveSpeed = _fe3d->water_getWaveSpeed(waterId);
		auto size = _fe3d->water_getSize(waterId);
		auto textureRepeat = _fe3d->water_getTextureRepeat(waterId);
		auto waveHeight = _fe3d->water_getWaveHeight(waterId);
		auto maxDepth = _fe3d->water_getMaxDepth(waterId);
		auto isEdged = _fe3d->water_isEdged(waterId);
		auto specularShininess = _fe3d->water_getSpecularShininess(waterId);
		auto specularIntensity = _fe3d->water_getSpecularIntensity(waterId);
		auto isSpecular = _fe3d->water_isSpecular(waterId);
		auto isReflective = _fe3d->water_isReflective(waterId);
		auto isRefractive = _fe3d->water_isRefractive(waterId);

		dudvMapPath = string(dudvMapPath.empty() ? "" : dudvMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));
		normalMapPath = string(normalMapPath.empty() ? "" : normalMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));
		displacementMapPath = string(displacementMapPath.empty() ? "" : displacementMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));

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
			rippleSpeed.x << " " <<
			rippleSpeed.y << " " <<
			waveSpeed.x << " " <<
			waveSpeed.y << " " <<
			isEdged << " " <<
			specularShininess << " " <<
			specularIntensity << " " <<
			maxDepth << endl;
	}

	file.close();

	Logger::throwInfo("Water editor data saved!");

	return true;
}