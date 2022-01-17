#include "text_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool Text2dEditor::saveToFile() const
{
	if(!_isEditorLoaded)
	{
		return false;
	}

	if(_currentProjectID.empty())
	{
		Logger::throwError("Text2dEditor::saveToFile");
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + _currentProjectID + "\\data\\text2d.fe3d");

	for(const auto& textID : _loadedTextIDs)
	{
		auto fontMapPath = _fe3d->text_getFontMapPath(textID);
		auto color = _fe3d->text_getColor(textID);
		auto transparency = _fe3d->text_getTransparency(textID);

		fontMapPath = string(fontMapPath.empty() ? "" : fontMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

		fontMapPath = (fontMapPath.empty()) ? "?" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), ' ', '?');

		file << textID << " " << fontMapPath << " " << color.r << " " << color.g << " " << color.b << " " << transparency << endl;
	}

	file.close();

	Logger::throwInfo("Text2D editor data saved!");

	return true;
}