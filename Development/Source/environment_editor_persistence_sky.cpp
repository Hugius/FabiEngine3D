#include "environment_editor.hpp"
#include "logger.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

const vector<array<string, 6>> EnvironmentEditor::getAllSkyTexturePathsFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("EnvironmentEditor::getAllSkyTexturePathsFromFile() --> no current project loaded!");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\sky.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: \"sky.fe3d\" file missing!");
		return {};
	}

	// Load sky file
	std::ifstream file(filePath);

	// Read sky data
	vector<array<string, 6>> texturePaths;
	string line;
	while (std::getline(file, line))
	{
		// Temporary values
		string skyID;
		array<string, 6> diffuseMapPaths = {};
		std::istringstream iss(line);

		// Load base data
		iss >>
			skyID >>
			diffuseMapPaths[0] >>
			diffuseMapPaths[1] >>
			diffuseMapPaths[2] >>
			diffuseMapPaths[3] >>
			diffuseMapPaths[4] >>
			diffuseMapPaths[5];

		// Perform empty string & space conversions
		for (auto& diffuseMapPath : diffuseMapPaths)
		{
			diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
			std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		}

		// Save file paths
		texturePaths.push_back(diffuseMapPaths);
	}

	// Close file
	file.close();

	// Return
	return texturePaths;
}

bool EnvironmentEditor::loadSkyEntitiesFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("EnvironmentEditor::loadSkyEntitiesFromFile() --> no current project loaded!");
	}

	// Clear IDs from previous loads
	_loadedSkyIDs.clear();

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\sky.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: \"sky.fe3d\" file missing!");
		return false;
	}

	// Load sky file
	std::ifstream file(filePath);

	// Read sky data
	string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);

		// Values
		string skyID;
		std::array<string, 6> diffuseMapPaths{};
		float rotationSpeed, lightness;
		Vec3 color;

		// Load base data
		iss >>
			skyID >>
			diffuseMapPaths[0] >>
			diffuseMapPaths[1] >>
			diffuseMapPaths[2] >>
			diffuseMapPaths[3] >>
			diffuseMapPaths[4] >>
			diffuseMapPaths[5] >>
			rotationSpeed >>
			lightness >>
			color.r >>
			color.g >>
			color.b;

		// Perform empty string & space conversions
		for (auto& diffuseMapPath : diffuseMapPaths)
		{
			diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
			std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		}

		// Load entity
		_loadedSkyIDs.push_back(skyID);
		_fe3d.skyEntity_add(skyID);
		_fe3d.skyEntity_setDiffuseMaps(skyID, diffuseMapPaths);
		_fe3d.skyEntity_setLightness(skyID, lightness);
		_fe3d.skyEntity_setRotationSpeed(skyID, rotationSpeed);
		_fe3d.skyEntity_setColor(skyID, color);
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Sky data from project \"" + _currentProjectID + "\" loaded!");

	// Return
	return true;
}

bool EnvironmentEditor::saveSkyEntitiesToFile()
{
	// Editor must be loaded
	if (!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("EnvironmentEditor::saveSkyEntitiesToFile() --> no current project loaded!");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\sky.fe3d";

	// Load sky file
	std::ofstream file(filePath);

	// Write sky data
	for (const auto& skyID : _loadedSkyIDs)
	{
		// Values
		auto diffuseMapPaths = _fe3d.skyEntity_getDiffuseMapPaths(skyID);
		float rotationSpeed = _fe3d.skyEntity_getRotationSpeed(skyID);
		float lightness = _fe3d.skyEntity_getLightness(skyID);
		Vec3 color = _fe3d.skyEntity_getColor(skyID);

		// Perform empty string & space conversions
		for (auto& diffuseMapPath : diffuseMapPaths)
		{
			diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
			std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		}

		// Write name to file
		file << skyID << " ";

		// Write paths to file
		for (const auto& diffuseMapPath : diffuseMapPaths)
		{
			file << diffuseMapPath << " ";
		}

		// Write options to file
		file <<
			rotationSpeed << " " <<
			lightness << " " <<
			color.r << " " <<
			color.g << " " <<
			color.b << std::endl;
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Sky data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}