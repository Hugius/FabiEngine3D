#include "quad2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::istringstream;

const vector<string> Quad2dEditor::getImagePathsFromFile() const
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\quad2d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `quad2d.fe3d` does not exist");
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
			if(!Configuration::getInst().isApplicationExported())
			{
				diffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + diffuseMapPath);
			}

			imagePaths.push_back(diffuseMapPath);
		}
	}

	file.close();

	return imagePaths;
}

const bool Quad2dEditor::loadEntitiesFromFile()
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\quad2d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `quad2d.fe3d` does not exist");

		return false;
	}

	string line;
	while(getline(file, line))
	{
		string quadId;
		string diffuseMapPath;
		fvec3 color;
		float opacity;
		unsigned int textureRepeat;
		bool isHorizontallyFlipped;
		bool isVerticallyFlipped;

		istringstream iss(line);

		iss
			>> quadId
			>> diffuseMapPath
			>> color.r
			>> color.g
			>> color.b
			>> opacity
			>> textureRepeat
			>> isHorizontallyFlipped
			>> isVerticallyFlipped;

		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');

		_fe3d->quad2d_create(quadId, true);

		if(_fe3d->quad2d_isExisting(quadId))
		{
			_loadedEntityIds.push_back(quadId);
			sort(_loadedEntityIds.begin(), _loadedEntityIds.end());

			_fe3d->quad2d_setVisible(quadId, false);
			_fe3d->quad2d_setPosition(quadId, Tools::convertPositionRelativeToDisplay(fvec2(0.0f)));
			_fe3d->quad2d_setSize(quadId, Tools::convertSizeRelativeToDisplay(fvec2(QUAD_SIZE.x, (QUAD_SIZE.y * Tools::getWindowAspectRatio()))));
			_fe3d->quad2d_setColor(quadId, color);
			_fe3d->quad2d_setOpacity(quadId, opacity);
			_fe3d->quad2d_setTextureRepeat(quadId, textureRepeat);
			_fe3d->quad2d_setHorizontallyFlipped(quadId, isHorizontallyFlipped);
			_fe3d->quad2d_setVerticallyFlipped(quadId, isVerticallyFlipped);

			if(!diffuseMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					diffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + diffuseMapPath);
				}

				_fe3d->quad2d_setDiffuseMap(quadId, diffuseMapPath);
			}
		}
	}

	file.close();

	Logger::throwInfo("Quad2D editor data loaded");

	return true;
}