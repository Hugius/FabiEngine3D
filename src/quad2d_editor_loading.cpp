#include "quad2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::istringstream;

const vector<string> Quad2dEditor::getImagePathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("Quad2dEditor::getImagePathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\quad2d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `quad2d.fe3d` missing!");
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

const bool Quad2dEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("Quad2dEditor::loadFromFile");
	}

	_loadedQuadIDs.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\quad2d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `quad2d.fe3d` missing!");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string quadID, diffuseMapPath;
		fvec3 color;
		float transparency;

		istringstream iss(line);

		iss >> quadID >> diffuseMapPath >> color.r >> color.g >> color.b >> transparency;

		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');

		_fe3d->quad2d_create(quadID, true);

		if(_fe3d->quad2d_isExisting(quadID))
		{
			_loadedQuadIDs.push_back(quadID);

			_fe3d->quad2d_setVisible(quadID, false);
			_fe3d->quad2d_setPosition(quadID, Tools::convertPositionToViewport(fvec2(0.0f)));
			_fe3d->quad2d_setSize(quadID, Tools::convertSizeToViewport(fvec2(QUAD2D_SIZE.x, (QUAD2D_SIZE.y * Tools::getWindowAspectRatio()))));
			_fe3d->quad2d_setColor(quadID, color);
			_fe3d->quad2d_setTransparency(quadID, transparency);

			if(!diffuseMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
				}

				_fe3d->quad2d_setDiffuseMap(quadID, diffuseMapPath);
			}
		}
	}

	file.close();

	Logger::throwInfo("Quad2D editor data loaded!");

	return true;
}