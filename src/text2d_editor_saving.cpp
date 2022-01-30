#include "text2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool Text2dEditor::saveToFile() const
{
	if(!isLoaded())
	{
		return false;
	}

	if(_currentProjectId.empty())
	{
		Logger::throwError("Text2dEditor::saveToFile");
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + _currentProjectId + "\\data\\text2d.fe3d");

	for(const auto& textId : _loadedTextIds)
	{
		auto fontMapPath = _fe3d->text2d_getFontMapPath(textId);
		auto color = _fe3d->text2d_getColor(textId);
		auto opacity = _fe3d->text2d_getOpacity(textId);

		fontMapPath = string(fontMapPath.empty() ? "" : fontMapPath.substr(string("projects\\" + _currentProjectId + "\\").size()));

		fontMapPath = (fontMapPath.empty()) ? "?" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), ' ', '?');

		file << textId << " " << fontMapPath << " " << color.r << " " << color.g << " " << color.b << " " << opacity << endl;
	}

	file.close();

	Logger::throwInfo("Text2D editor data saved!");

	return true;
}