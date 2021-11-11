#include "water_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool WaterEditor::saveWaterEntitiesToFile() const
{
	// Editor must be loaded
	if(!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("WaterEditor::saveWaterEntitiesToFile");
	}

	// Create or overwrite file
	ofstream file;
	if(Config::getInst().isApplicationExported())
	{
		file.open(Tools::getRootDirectoryPath() + "data\\water.fe3d");
	}
	else
	{
		file.open(Tools::getRootDirectoryPath() + "game\\" + _currentProjectID + "\\data\\water.fe3d");
	}

	// Write water data
	for(const auto& waterID : _loadedWaterIDs)
	{
		// Values
		auto dudvMapPath = _fe3d.waterEntity_getDudvMapPath(waterID);
		auto normalMapPath = _fe3d.waterEntity_getNormalMapPath(waterID);
		auto displacementMapPath = _fe3d.waterEntity_getDisplacementMapPath(waterID);
		auto color = _fe3d.waterEntity_getColor(waterID);
		auto height = _fe3d.waterEntity_getHeight(waterID);
		auto speed = _fe3d.waterEntity_getSpeed(waterID);
		auto size = _fe3d.waterEntity_getSize(waterID);
		auto textureRepeat = _fe3d.waterEntity_getTextureRepeat(waterID);
		auto waveHeight = _fe3d.waterEntity_getWaveHeight(waterID);
		auto transparency = _fe3d.waterEntity_getTransparency(waterID);
		auto specularShininess = _fe3d.waterEntity_getSpecularShininess(waterID);
		auto specularIntensity = _fe3d.waterEntity_getSpecularIntensity(waterID);
		auto quality = static_cast<unsigned int>(_fe3d.waterEntity_getQuality(waterID));
		auto isSpecular = _fe3d.waterEntity_isSpecular(waterID);
		auto isReflective = _fe3d.waterEntity_isReflective(waterID);
		auto isRefractive = _fe3d.waterEntity_isRefractive(waterID);

		// Convert to short path
		dudvMapPath = string(dudvMapPath.empty() ? "" : dudvMapPath.substr(string("game\\" + _currentProjectID + "\\").size()));
		normalMapPath = string(normalMapPath.empty() ? "" : normalMapPath.substr(string("game\\" + _currentProjectID + "\\").size()));
		displacementMapPath = string(displacementMapPath.empty() ? "" : displacementMapPath.substr(string("game\\" + _currentProjectID + "\\").size()));

		// Convert empty string
		dudvMapPath = (dudvMapPath.empty() ? "?" : dudvMapPath);
		normalMapPath = (normalMapPath.empty() ? "?" : normalMapPath);
		displacementMapPath = (displacementMapPath.empty() ? "?" : displacementMapPath);

		// Convert spaces
		replace(dudvMapPath.begin(), dudvMapPath.end(), ' ', '?');
		replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
		replace(displacementMapPath.begin(), displacementMapPath.end(), ' ', '?');

		// Write data to file
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

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Water data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}