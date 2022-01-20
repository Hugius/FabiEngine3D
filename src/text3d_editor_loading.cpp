#include "text3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> Text3dEditor::getImagePathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("Text3dEditor::getImagePathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\text3d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `text3d.fe3d` missing!");
		return {};
	}

	vector<string> imagePaths;
	string line;
	while(getline(file, line))
	{
		string textID, fontMapPath;
		fvec2 size;
		fvec3 color;
		bool isFacingX, isFacingY;

		istringstream iss(line);

		iss >>
			textID >>
			size.x >>
			size.y >>
			color.r >>
			color.g >>
			color.b >>
			isFacingX >>
			isFacingY >>
			fontMapPath;

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

const bool Text3dEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("Text3dEditor::loadFromFile");
	}

	_loadedTextIDs.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\text3d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `text3d.fe3d` missing!");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string textID, fontMapPath;
		fvec2 size;
		fvec3 color;
		float lightness, transparency;
		bool isFacingX, isFacingY, isReflected, isShadowed, isBright;

		istringstream iss(line);

		iss >>
			textID >>
			size.x >>
			size.y >>
			color.r >>
			color.g >>
			color.b >>
			isFacingX >>
			isFacingY >>
			fontMapPath >>
			isReflected >>
			isShadowed >>
			lightness >>
			isBright >>
			transparency;

		fontMapPath = (fontMapPath == "?") ? "" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), '?', ' ');

		if(!Config::getInst().isApplicationExported())
		{
			fontMapPath = string("projects\\" + _currentProjectID + "\\" + fontMapPath);
		}

		_fe3d->text3d_create(textID, fontMapPath, false);

		if(_fe3d->text3d_isExisting(textID))
		{
			_loadedTextIDs.push_back(textID);

			_fe3d->text3d_setVisible(textID, false);
			_fe3d->text3d_setSize(textID, size);
			_fe3d->text3d_setColor(textID, color);
			_fe3d->text3d_setLightness(textID, lightness);
			_fe3d->text3d_setFacingCameraX(textID, isFacingX);
			_fe3d->text3d_setFacingCameraY(textID, isFacingY);
			_fe3d->text3d_setShadowed(textID, isShadowed);
			_fe3d->text3d_setReflected(textID, isReflected);
			_fe3d->text3d_setBright(textID, isBright);
			_fe3d->text3d_setTransparency(textID, transparency);
		}
	}

	file.close();

	Logger::throwInfo("Text3d editor data loaded!");

	return true;
}