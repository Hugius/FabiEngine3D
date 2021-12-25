#include "image_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::istringstream;

const vector<string> ImageEditor::getTexturePathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("ImageEditor::getTexturePathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\image.fe3d");

	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `image.fe3d` missing!");
		return {};
	}

	ifstream file(filePath);

	vector<string> texturePaths;
	string line;
	while(getline(file, line))
	{
		string imageID, diffuseMapPath;

		istringstream iss(line);

		iss >> imageID >> diffuseMapPath;

		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');

		if(!diffuseMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
			}

			texturePaths.push_back(diffuseMapPath);
		}
	}

	file.close();

	return texturePaths;
}

const bool ImageEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("ImageEditor::loadFromFile");
	}

	_loadedImageIDs.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\image.fe3d");

	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `image.fe3d` missing!");
		return false;
	}

	ifstream file(filePath);

	string line;
	while(getline(file, line))
	{
		string imageID, diffuseMapPath;

		istringstream iss(line);

		iss >> imageID >> diffuseMapPath;

		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');

		_fe3d.image_create(imageID, true);

		if(_fe3d.image_isExisting(imageID))
		{
			_loadedImageIDs.push_back(imageID);

			if(!diffuseMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
				}

				_fe3d.image_setDiffuseMap(imageID, diffuseMapPath);
			}

			_fe3d.image_setVisible(imageID, false);
		}
	}

	file.close();

	Logger::throwInfo("Image data loaded!");

	return true;
}