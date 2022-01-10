#include "quad_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::istringstream;

const vector<string> QuadEditor::getImagePathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("QuadEditor::getImagePathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\quad.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `quad.fe3d` missing!");
		return {};
	}

	vector<string> texturePaths;
	string line;
	while(getline(file, line))
	{
		string quadID, diffuseMapPath;

		istringstream iss(line);

		iss >> quadID >> diffuseMapPath;

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

const bool QuadEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("QuadEditor::loadFromFile");
	}

	_loadedQuadIDs.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\quad.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `quad.fe3d` missing!");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string quadID, diffuseMapPath;

		istringstream iss(line);

		iss >> quadID >> diffuseMapPath;

		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');

		_fe3d->quad_create(quadID, true);

		if(_fe3d->quad_isExisting(quadID))
		{
			_loadedQuadIDs.push_back(quadID);

			if(!diffuseMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
				}

				_fe3d->quad_setDiffuseMap(quadID, diffuseMapPath);
			}

			_fe3d->quad_setVisible(quadID, false);
		}
	}

	file.close();

	Logger::throwInfo("Quad editor data loaded!");

	return true;
}