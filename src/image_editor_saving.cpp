#include "image_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool ImageEditor::saveToFile() const
{
	if(!_isEditorLoaded)
	{
		return false;
	}

	if(_currentProjectID.empty())
	{
		Logger::throwError("ImageEditor::saveToFile");
	}

	ofstream file(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\data\\image.fe3d");

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

	file.close();

	Logger::throwInfo("Image data saved!");

	return true;
}