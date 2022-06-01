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
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "domain\\quad2d.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `domain\\quad2d.fe3d` does not exist");

		return {};
	}

	vector<string> imagePaths = {};
	string line = "";

	while(getline(file, line))
	{
		string quad2dId;
		string diffuseMapPath;

		auto iss = istringstream(line);

		iss
			>> quad2dId
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

const bool Quad2dEditor::loadQuad2dsFromFile()
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "domain\\quad2d.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `domain\\quad2d.fe3d` does not exist");

		return false;
	}

	string line = "";

	while(getline(file, line))
	{
		string quad2dId;
		string diffuseMapPath;
		fvec3 color;
		float opacity;
		float lightness;
		int textureRepeat;
		bool isHorizontallyFlipped;
		bool isVerticallyFlipped;

		auto iss = istringstream(line);

		iss
			>> quad2dId
			>> diffuseMapPath
			>> color.r
			>> color.g
			>> color.b
			>> opacity
			>> textureRepeat
			>> isHorizontallyFlipped
			>> isVerticallyFlipped
			>> lightness;

		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');

		_fe3d->quad2d_create(quad2dId, true);

		if(_fe3d->quad2d_isExisting(quad2dId))
		{
			_fe3d->quad2d_setVisible(quad2dId, false);
			_fe3d->quad2d_setPosition(quad2dId, Tools::convertPositionRelativeToDisplay(fvec2(0.0f)));
			_fe3d->quad2d_setSize(quad2dId, Tools::convertSizeRelativeToDisplay(fvec2(QUAD2D_SIZE.x, (QUAD2D_SIZE.y * Tools::getWindowAspectRatio()))));
			_fe3d->quad2d_setColor(quad2dId, color);
			_fe3d->quad2d_setOpacity(quad2dId, opacity);
			_fe3d->quad2d_setLightness(quad2dId, lightness);
			_fe3d->quad2d_setTextureRepeat(quad2dId, textureRepeat);
			_fe3d->quad2d_setHorizontallyFlipped(quad2dId, isHorizontallyFlipped);
			_fe3d->quad2d_setVerticallyFlipped(quad2dId, isVerticallyFlipped);

			if(!diffuseMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					diffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + diffuseMapPath);
				}

				_fe3d->quad2d_setDiffuseMap(quad2dId, diffuseMapPath);
			}

			_loadedQuad2dIds.push_back(quad2dId);

			sort(_loadedQuad2dIds.begin(), _loadedQuad2dIds.end());
		}
	}

	file.close();

	Logger::throwInfo("Quad2D editor data loaded");

	return true;
}