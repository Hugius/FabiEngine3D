#include "sky_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::istringstream;

const vector<array<string, 6>> SkyEditor::getAllTexturePathsFromFile()
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("SkyEditor::getAllTexturePathsFromFile");
	}

	// Compose file path
	const string filePath = Tools::getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\sky.fe3d";

	// Warning checking
	if (!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `sky.fe3d` missing!");
		return {};
	}

	// Load sky file
	ifstream file(filePath);

	// Read sky data
	vector<array<string, 6>> texturePaths;
	string line;
	while (getline(file, line))
	{
		// Values
		string skyID;
		array<string, 6> diffuseMapPaths = {};

		// For file extraction
		istringstream iss(line);

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
			replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		}

		// Save file path
		texturePaths.push_back(diffuseMapPaths);
	}

	// Close file
	file.close();

	// Return
	return texturePaths;
}

bool SkyEditor::loadSkyEntitiesFromFile()
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("SkyEditor::loadSkyEntitiesFromFile");
	}

	// Clear IDs from previous loads
	_loadedSkyIDs.clear();

	// Compose file path
	const string filePath = Tools::getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\sky.fe3d";

	// Warning checking
	if (!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `sky.fe3d` missing!");
		return false;
	}

	// Load sky file
	ifstream file(filePath);

	// Read sky data
	string line;
	while (getline(file, line))
	{
		// For file extraction
		istringstream iss(line);

		// Values
		string skyID;
		array<string, 6> diffuseMapPaths{};
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
			replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		}

		// Create sky
		_fe3d.skyEntity_create(skyID);

		// Check if sky creation went well
		if (_fe3d.skyEntity_isExisting(skyID))
		{
			// Add sky ID
			_loadedSkyIDs.push_back(skyID);

			// Set properties
			_fe3d.skyEntity_setDiffuseMaps(skyID, diffuseMapPaths);
			_fe3d.skyEntity_setLightness(skyID, lightness);
			_fe3d.skyEntity_setRotationSpeed(skyID, rotationSpeed);
			_fe3d.skyEntity_setColor(skyID, color);
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Sky data from project \"" + _currentProjectID + "\" loaded!");

	// Return
	return true;
}

bool SkyEditor::saveSkyEntitiesToFile()
{
	// Editor must be loaded
	if (!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("SkyEditor::saveSkyEntitiesToFile");
	}

	// Compose file path
	const string filePath = Tools::getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\sky.fe3d";

	// Load sky file
	ofstream file(filePath);

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
			diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
			replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		}

		// Write ID to file
		file << skyID << " ";

		// Write paths to file
		for (const auto& diffuseMapPath : diffuseMapPaths)
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