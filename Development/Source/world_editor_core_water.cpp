#include "world_editor.hpp"

#include <fstream>
#include <sstream>

void WorldEditor::loadWaterEntity()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	string fileFolderPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\Data\\water.fe3d";

	// Load water file
	if (_fe3d.misc_isFileExisting(fileFolderPath))
	{
		// Open file
		std::ifstream waterFile(fileFolderPath);

		// Values
		string dudvMapPath, normalMapPath, displacementMapPath;
		bool isWaving, isRippling, isSpecularLighted, isReflective, isRefractive;
		vec3 color, position;
		float size, uvRepeat, waveHeightFactor, speed, transparency, specularFactor, specularIntensity;

		// Load base data
		waterFile >>
			dudvMapPath >>
			normalMapPath >>
			displacementMapPath >>
			isWaving >>
			isRippling >>
			isSpecularLighted >>
			isReflective >>
			isRefractive >>
			color.r >>
			color.g >>
			color.b >>
			size >>
			position.x >>
			position.y >>
			position.z >>
			uvRepeat >>
			waveHeightFactor >>
			speed >>
			transparency >>
			specularFactor >>
			specularIntensity;
		
		// Perform empty string conversions
		dudvMapPath = (dudvMapPath == "-" ? "" : dudvMapPath);
		normalMapPath = (normalMapPath == "-" ? "" : normalMapPath);
		displacementMapPath = (displacementMapPath == "-" ? "" : displacementMapPath);

		// Close file
		waterFile.close();

		// Load entity
		_loadWaterEntity();
		_fe3d.waterEntity_setPosition("@water", position);
		_fe3d.waterEntity_setSize("@water", size);
		_fe3d.waterEntity_setWaving("@water", isWaving);
		_fe3d.waterEntity_setRippling("@water", isRippling);
		_fe3d.waterEntity_setSpecularLighted("@water", isSpecularLighted);
		_fe3d.waterEntity_setReflective("@water", isReflective);
		_fe3d.waterEntity_setRefractive("@water", isRefractive);
		_fe3d.waterEntity_setWaveHeightFactor("@water", waveHeightFactor);
		_fe3d.waterEntity_setSpecularLightingFactor("@water", specularFactor);
		_fe3d.waterEntity_setSpecularLightingIntensity("@water", specularIntensity);
		_fe3d.waterEntity_setTransparency("@water", transparency);
		_fe3d.waterEntity_setColor("@water", color);
		_fe3d.waterEntity_setUvRepeat("@water", uvRepeat);
		_fe3d.waterEntity_setSpeed("@water", speed);
		if (dudvMapPath != "") _fe3d.waterEntity_setDudvMap("@water", dudvMapPath);
		if (normalMapPath != "") _fe3d.waterEntity_setNormalMap("@water", normalMapPath);
		if (displacementMapPath != "") _fe3d.waterEntity_setDisplacementMap("@water", displacementMapPath);

		// Logging
		_fe3d.logger_throwInfo("Water data from project \"" + _currentProjectName + "\" loaded!");
	}
}

void WorldEditor::_saveWaterData()
{
	if (_isLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		string fileFolderPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\Data\\water.fe3d";

		// Save water dat
		if (_fe3d.waterEntity_isExisting("@water"))
		{
			// Load file
			std::ofstream waterFile(fileFolderPath);

			// Values
			string dudvMapPath = _fe3d.waterEntity_getDudvMapPath("@water");
			string normalMapPath = _fe3d.waterEntity_getNormalMapPath("@water");
			string displacementMapPath = _fe3d.waterEntity_getDisplacementMapPath("@water");
			bool isWaving = _fe3d.waterEntity_isWaving("@water");
			bool isRippling = _fe3d.waterEntity_isRippling("@water");
			bool isSpecularLighted = _fe3d.waterEntity_isSpecularLighted("@water");
			bool isReflective = _fe3d.waterEntity_isReflective("@water");
			bool isRefractive = _fe3d.waterEntity_isRefractive("@water");
			vec3 color = _fe3d.waterEntity_getColor("@water");
			float size = _fe3d.waterEntity_getSize("@water");
			vec3 position = _fe3d.waterEntity_getPosition("@water");
			float uvRepeat = _fe3d.waterEntity_getUvRepeat("@water");
			float waveHeightFactor = _fe3d.waterEntity_getWaveHeightFactor("@water");
			float speed = _fe3d.waterEntity_getSpeed("@water");
			float transparency = _fe3d.waterEntity_getTransparency("@water");
			float specularFactor = _fe3d.waterEntity_getSpecularLightingFactor("@water");
			float specularIntensity = _fe3d.waterEntity_getSpecularLightingIntensity("@water");

			// Perform empty string conversions
			dudvMapPath = (dudvMapPath == "" ? "-" : dudvMapPath);
			normalMapPath = (normalMapPath == "" ? "-" : normalMapPath);
			displacementMapPath = (displacementMapPath == "" ? "-" : displacementMapPath);

			// Write data to file
			waterFile <<
				dudvMapPath << " " << 
				normalMapPath << " " << 
				displacementMapPath << " " <<
				isWaving << " " << 
				isRippling << " " << 
				isSpecularLighted << " " << 
				isReflective << " " << 
				isRefractive << " " << 
				color.r << " " << 
				color.g << " " << 
				color.b << " " << 
				size << " " << 
				position.x << " " << 
				position.y << " " <<
				position.z << " " <<
				uvRepeat << " " << 
				waveHeightFactor << " " <<
				speed << " " << 
				transparency << " " <<
				specularFactor << " " <<
				specularIntensity << std::endl;

			// Close file
			waterFile.close();
		}
		else
		{
			// Remove file if non-existent
			if (_fe3d.misc_isFileExisting(fileFolderPath))
			{
				std::remove(fileFolderPath.c_str());
			}
		}

		// Logging
		_fe3d.logger_throwInfo("Water data from project \"" + _currentProjectName + "\" saved!");
	}
}

void WorldEditor::_loadWaterEntity()
{
	_fe3d.waterEntity_add("@water");
	_fe3d.waterEntity_select("@water");
	_fe3d.waterEntity_hide("@water");
}