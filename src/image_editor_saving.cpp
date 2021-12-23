#include "image_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool ImageEditor::saveToFile() const
{
	// Editor must be loaded
	if(!_isEditorLoaded)
	{
		return false;
	}

	// Validate project ID
	if(_currentProjectID.empty())
	{
		Logger::throwError("ImageEditor::saveToFile");
	}

	// Create or overwrite file
	ofstream file(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\data\\image.fe3d");

	// Write image data
	for(const auto& imageID : _loadedImageIDs)
	{
		// Data to save
		auto diffuseMapPath = _fe3d.image_getDiffuseMapPath(imageID);

		// Convert to short path
		diffuseMapPath = string(diffuseMapPath.empty() ? "" : diffuseMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

		// Convert empty string
		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;

		// Convert spaces
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');

		// Write data to file
		file << imageID << " " << diffuseMapPath << endl;
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Image data saved!");

	// Return
	return true;
}