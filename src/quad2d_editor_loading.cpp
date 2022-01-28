#include "quad2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::istringstream;

const vector<string> Quad2dEditor::getImagePathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && _currentProjectId.empty())
	{
		Logger::throwError("Quad2dEditor::getImagePathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "data\\quad2d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `quad2d.fe3d` missing!");
		return {};
	}

	vector<string> imagePaths;
	string line;
	while(getline(file, line))
	{
		string quadId;
		string diffuseMapPath;

		istringstream iss(line);

		iss
			>> quadId
			>> diffuseMapPath;

		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');

		if(!diffuseMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				diffuseMapPath = string("projects\\" + _currentProjectId + "\\" + diffuseMapPath);
			}

			imagePaths.push_back(diffuseMapPath);
		}
	}

	file.close();

	return imagePaths;
}

const bool Quad2dEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && _currentProjectId.empty())
	{
		Logger::throwError("Quad2dEditor::loadFromFile");
	}

	_loadedQuadIds.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "data\\quad2d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `quad2d.fe3d` missing!");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string quadId;
		string diffuseMapPath;
		fvec3 color;
		float opacity;

		istringstream iss(line);

		iss
			>> quadId
			>> diffuseMapPath
			>> color.r
			>> color.g
			>> color.b
			>> opacity;

		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');

		_fe3d->quad2d_create(quadId, true);

		if(_fe3d->quad2d_isExisting(quadId))
		{
			_loadedQuadIds.push_back(quadId);

			_fe3d->quad2d_setVisible(quadId, false);
			_fe3d->quad2d_setPosition(quadId, Tools::convertPositionToViewport(fvec2(0.0f)));
			_fe3d->quad2d_setSize(quadId, Tools::convertSizeToViewport(fvec2(QUAD_SIZE.x, (QUAD_SIZE.y * Tools::getWindowAspectRatio()))));
			_fe3d->quad2d_setColor(quadId, color);
			_fe3d->quad2d_setOpacity(quadId, opacity);

			if(!diffuseMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					diffuseMapPath = string("projects\\" + _currentProjectId + "\\" + diffuseMapPath);
				}

				_fe3d->quad2d_setDiffuseMap(quadId, diffuseMapPath);
			}
		}
	}

	file.close();

	Logger::throwInfo("Quad2D editor data loaded!");

	return true;
}