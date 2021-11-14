#include "sky_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

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

	// Create or overwrite file
	ofstream file(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\data\\sky.fe3d");

	// Write sky data
	for(const auto& skyID : _loadedSkyIDs)
	{
		// Values
		auto diffuseMapPaths = _fe3d.skyEntity_getDiffuseMapPaths(skyID);
		auto rotationSpeed = _fe3d.skyEntity_getRotationSpeed(skyID);
		auto lightness = _fe3d.skyEntity_getLightness(skyID);
		auto color = _fe3d.skyEntity_getColor(skyID);

		// Iterate through paths
		for(auto& diffuseMapPath : diffuseMapPaths)
		{
			// Convert to short path
			diffuseMapPath = string(diffuseMapPath.empty() ? "" : diffuseMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

			// Convert empty string
			diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;

			// Convert spaces
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
	Logger::throwInfo("Sky data saved!");

	// Return
	return true;
}