#include "text2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::istringstream;

const vector<string> Text2dEditor::getImagePathsFromFile() const
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\text2d.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `text2d.fe3d` does not exist");

		return {};
	}

	vector<string> imagePaths = {};
	string line = "";

	while(getline(file, line))
	{
		string text2dId;
		string fontMapPath;

		auto iss = istringstream(line);

		iss
			>> text2dId
			>> fontMapPath;

		fontMapPath = (fontMapPath == "?") ? "" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), '?', ' ');

		if(!fontMapPath.empty())
		{
			if(!Configuration::getInst().isApplicationExported())
			{
				fontMapPath = ("projects\\" + getCurrentProjectId() + "\\" + fontMapPath);
			}

			imagePaths.push_back(fontMapPath);
		}
	}

	file.close();

	return imagePaths;
}

const bool Text2dEditor::loadText2dsFromFile()
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\text2d.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `text2d.fe3d` does not exist");

		return false;
	}

	string line = "";

	while(getline(file, line))
	{
		string text2dId;
		string fontMapPath;
		fvec3 color;
		float opacity;
		bool isHorizontallyFlipped;
		bool isVerticallyFlipped;

		auto iss = istringstream(line);

		iss
			>> text2dId
			>> fontMapPath
			>> color.r
			>> color.g
			>> color.b
			>> opacity
			>> isHorizontallyFlipped
			>> isVerticallyFlipped;

		fontMapPath = (fontMapPath == "?") ? "" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), '?', ' ');

		if(!Configuration::getInst().isApplicationExported())
		{
			fontMapPath = ("projects\\" + getCurrentProjectId() + "\\" + fontMapPath);
		}

		_fe3d->text2d_create(text2dId, fontMapPath, true);

		if(_fe3d->text2d_isExisting(text2dId))
		{
			_fe3d->text2d_setVisible(text2dId, false);
			_fe3d->text2d_setPosition(text2dId, Tools::convertPositionRelativeToDisplay(fvec2(0.0f)));
			_fe3d->text2d_setSize(text2dId, Tools::convertSizeRelativeToDisplay(fvec2(TEXT2D_SIZE.x, (TEXT2D_SIZE.y * Tools::getWindowAspectRatio()))));
			_fe3d->text2d_setColor(text2dId, color);
			_fe3d->text2d_setOpacity(text2dId, opacity);
			_fe3d->text2d_setHorizontallyFlipped(text2dId, isHorizontallyFlipped);
			_fe3d->text2d_setVerticallyFlipped(text2dId, isVerticallyFlipped);

			_loadedText2dIds.push_back(text2dId);

			sort(_loadedText2dIds.begin(), _loadedText2dIds.end());
		}
	}

	file.close();

	Logger::throwInfo("Text2D editor data loaded");

	return true;
}