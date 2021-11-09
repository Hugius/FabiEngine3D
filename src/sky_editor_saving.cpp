#include "sky_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool SkyEditor::saveSkyEntitiesToFile() const
{
	// Editor must be loaded
	if(!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("SkyEditor::saveSkyEntitiesToFile");
	}

	// Compose file path
	const string filePath = Tools::getRootDirectoryPath() + (_fe3d.application_isExported() ? "" :
														 ("projects\\" + _currentProjectID)) + "\\data\\sky.fe3d";

	// Load sky file
	ofstream file(filePath);

	// Write sky data
	for(const auto& skyID : _loadedSkyIDs)
	{
		// Values
		auto diffuseMapPaths = _fe3d.skyEntity_getDiffuseMapPaths(skyID);
		float rotationSpeed = _fe3d.skyEntity_getRotationSpeed(skyID);
		float lightness = _fe3d.skyEntity_getLightness(skyID);
		Vec3 color = _fe3d.skyEntity_getColor(skyID);

		// Perform empty string & space conversions
		for(auto& diffuseMapPath : diffuseMapPaths)
		{
			diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
			replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		}

		// Write ID to file
		file << skyID << " ";

		// Write paths to file
		for(const auto& diffuseMapPath : diffuseMapPaths)
		{
			file << diffuseMapPath << " ";
		}

		// Write data to file
		file <<
			rotationSpeed << " " <<
			lightness << " " <<
			color.r << " " <<
			color.g << " " <<
			color.b << endl;
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Sky data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}