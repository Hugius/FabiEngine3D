#include "text_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::istringstream;

const vector<string> Text2dEditor::getImagePathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("Text2dEditor::getImagePathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\text2d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `text2d.fe3d` missing!");
		return {};
	}

	vector<string> imagePaths;
	string line;
	while(getline(file, line))
	{
		string textID, fontMapPath;

		istringstream iss(line);

		iss >> textID >> fontMapPath;

		fontMapPath = (fontMapPath == "?") ? "" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), '?', ' ');

		if(!fontMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				fontMapPath = string("projects\\" + _currentProjectID + "\\" + fontMapPath);
			}

			imagePaths.push_back(fontMapPath);
		}
	}

	file.close();

	return imagePaths;
}

const bool Text2dEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("Text2dEditor::loadFromFile");
	}

	_loadedTextIDs.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\text2d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `text2d.fe3d` missing!");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string textID, fontMapPath;
		fvec3 color;
		float transparency;

		istringstream iss(line);

		iss >> textID >> fontMapPath >> color.r >> color.g >> color.b >> transparency;

		fontMapPath = (fontMapPath == "?") ? "" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), '?', ' ');

		_fe3d->text_create(textID, true);

		if(_fe3d->text_isExisting(textID))
		{
			_loadedTextIDs.push_back(textID);

			_fe3d->text_setVisible(textID, false);
			_fe3d->text_setPosition(textID, Tools::convertPositionToViewport(fvec2(0.0f)));
			_fe3d->text_setSize(textID, Tools::convertSizeToViewport(fvec2(TEXT_SIZE.x, (TEXT_SIZE.y * Tools::getWindowAspectRatio()))));
			_fe3d->text_setColor(textID, color);
			_fe3d->text_setTransparency(textID, transparency);

			if(!fontMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					fontMapPath = string("projects\\" + _currentProjectID + "\\" + fontMapPath);
				}

				_fe3d->text_setFontMap(textID, fontMapPath);
				_fe3d->text_setContent(textID, "Text123");
			}
		}
	}

	file.close();

	Logger::throwInfo("Text2D editor data loaded!");

	return true;
}