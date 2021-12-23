#include "image_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::istringstream;

const vector<string> ImageEditor::getTexturePathsFromFile() const
{
	// Validate project ID
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("ImageEditor::getTexturePathsFromFile");
	}

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\image.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `image.fe3d` missing!");
		return {};
	}

	// Load image file
	ifstream file(filePath);

	// Read image data
	vector<string> texturePaths;
	string line;
	while(getline(file, line))
	{
		// Data placeholders
		string imageID, texturePath;

		// For file extraction
		istringstream iss(line);

		// Read from file
		iss >> imageID >> texturePath;

		// Convert empty string
		texturePath = (texturePath == "?") ? "" : texturePath;

		// Convert spaces
		replace(texturePath.begin(), texturePath.end(), '?', ' ');

		// Convert to long path
		if(!Config::getInst().isApplicationExported())
		{
			texturePath = string("projects\\" + _currentProjectID + "\\" + texturePath);
		}

		// Save path
		texturePaths.push_back(texturePath);
	}

	// Close file
	file.close();

	return texturePaths;
}

const bool ImageEditor::loadFromFile()
{
	// Validate project ID
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("ImageEditor::loadFromFile");
	}

	// Clear IDs from previous loads
	_loadedImageIDs.clear();

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\image.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `image.fe3d` missing!");
		return false;
	}

	// Load image file
	ifstream file(filePath);

	// Read image data
	string line;
	while(getline(file, line))
	{
		// Data placeholders
		string imageID, texturePath;

		// For file extraction
		istringstream iss(line);

		// Read from file
		iss >> imageID >> texturePath;

		// Convert empty string
		texturePath = (texturePath == "?") ? "" : texturePath;

		// Convert spaces
		replace(texturePath.begin(), texturePath.end(), '?', ' ');

		// Convert to long path
		if(!Config::getInst().isApplicationExported())
		{
			texturePath = string("projects\\" + _currentProjectID + "\\" + texturePath);
		}

		// Create image
		_fe3d.image_create(imageID, true);
		_fe3d.image_setDiffuseMap(imageID, texturePath);

		// Check if image creation went well
		if(_fe3d.image_isExisting(imageID))
		{
			// Add image ID
			_loadedImageIDs.push_back(imageID);
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Image data loaded!");

	// Return
	return true;
}