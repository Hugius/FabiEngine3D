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
	if(!Config::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		Logger::throwError("Text3dEditor::getImagePathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\text3d.fe3d");

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
		string textId;
		string fontMapPath;
		fvec2 size;
		fvec3 color;
		bool isFacingCameraHorizontally;
		bool isFacingCameraVertically;

		istringstream iss(line);

		iss
			>> textId
			>> size.x
			>> size.y
			>> color.r
			>> color.g
			>> color.b
			>> isFacingCameraHorizontally
			>> isFacingCameraVertically
			>> fontMapPath;

		fontMapPath = (fontMapPath == "?") ? "" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), '?', ' ');

		if(!fontMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				fontMapPath = string("projects\\" + getCurrentProjectId() + "\\" + fontMapPath);
			}

			imagePaths.push_back(fontMapPath);
		}
	}

	file.close();

	return imagePaths;
}

const bool Text3dEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		Logger::throwError("Text3dEditor::loadFromFile");
	}

	_loadedTextIds.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\text3d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `text3d.fe3d` missing!");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string textId;
		string fontMapPath;
		fvec2 size;
		fvec3 color;
		float lightness;
		float opacity;
		bool isFacingCameraHorizontally;
		bool isFacingCameraVertically;
		bool isReflected;
		bool isShadowed;
		bool isBright;

		istringstream iss(line);

		iss
			>> textId
			>> size.x
			>> size.y
			>> color.r
			>> color.g
			>> color.b
			>> isFacingCameraHorizontally
			>> isFacingCameraVertically
			>> fontMapPath
			>> isReflected
			>> isShadowed
			>> lightness
			>> isBright
			>> opacity;

		fontMapPath = (fontMapPath == "?") ? "" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), '?', ' ');

		if(!Config::getInst().isApplicationExported())
		{
			fontMapPath = string("projects\\" + getCurrentProjectId() + "\\" + fontMapPath);
		}

		_fe3d->text3d_create(textId, fontMapPath, false);

		if(_fe3d->text3d_isExisting(textId))
		{
			_loadedTextIds.push_back(textId);

			_fe3d->text3d_setVisible(textId, false);
			_fe3d->text3d_setSize(textId, size);
			_fe3d->text3d_setColor(textId, color);
			_fe3d->text3d_setLightness(textId, lightness);
			_fe3d->text3d_setFacingCameraHorizontally(textId, isFacingCameraHorizontally);
			_fe3d->text3d_setFacingCameraVertically(textId, isFacingCameraVertically);
			_fe3d->text3d_setShadowed(textId, isShadowed);
			_fe3d->text3d_setReflected(textId, isReflected);
			_fe3d->text3d_setBright(textId, isBright);
			_fe3d->text3d_setOpacity(textId, opacity);
		}
	}

	file.close();

	Logger::throwInfo("Text3d editor data loaded!");

	return true;
}