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
		auto diffuseMapPath = _fe3d.image_getDiffuseMapPath(imageID);

		diffuseMapPath = string(diffuseMapPath.empty() ? "" : diffuseMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');

		file << imageID << " " << diffuseMapPath << endl;
	}

	file.close();

	Logger::throwInfo("Image data saved!");

	return true;
}