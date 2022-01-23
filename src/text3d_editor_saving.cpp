#include "text3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool Text3dEditor::saveToFile() const
{
	if(!_isEditorLoaded)
	{
		return false;
	}

	if(_currentProjectID.empty())
	{
		Logger::throwError("Text3dEditor::saveToFile");
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + _currentProjectID + "\\data\\text3d.fe3d");

	for(const auto& textID : _loadedTextIDs)
	{
		auto size = _fe3d->text3d_getSize(textID);
		auto color = _fe3d->text3d_getColor(textID);
		auto fontMapPath = _fe3d->text3d_getFontMapPath(textID);
		auto isFacingX = _fe3d->text3d_isFacingCameraX(textID);
		auto isFacingY = _fe3d->text3d_isFacingCameraY(textID);
		auto isReflected = _fe3d->text3d_isReflected(textID);
		auto isShadowed = _fe3d->text3d_isShadowed(textID);
		auto lightness = _fe3d->text3d_getLightness(textID);
		auto isBright = _fe3d->text3d_isBright(textID);
		auto opacity = _fe3d->text3d_getOpacity(textID);

		fontMapPath = string(fontMapPath.empty() ? "" : fontMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

		fontMapPath = (fontMapPath.empty()) ? "?" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), ' ', '?');

		file <<
			textID << " " <<
			size.x << " " <<
			size.y << " " <<
			color.r << " " <<
			color.g << " " <<
			color.b << " " <<
			isFacingX << " " <<
			isFacingY << " " <<
			fontMapPath << " " <<
			isReflected << " " <<
			isShadowed << " " <<
			lightness << " " <<
			isBright << " " <<
			opacity << endl;
	}

	file.close();

	Logger::throwInfo("Text3d editor data saved!");

	return true;
}