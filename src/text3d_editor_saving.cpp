#include "text3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool Text3dEditor::saveToFile() const
{
	if(!isLoaded())
	{
		return false;
	}

	if(getCurrentProjectId().empty())
	{
		abort();
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	auto file = ofstream(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\text3d.fe3d");

	for(const auto& textId : _loadedTextIds)
	{
		auto size = _fe3d->text3d_getSize(textId);
		auto color = _fe3d->text3d_getColor(textId);
		auto fontMapPath = _fe3d->text3d_getFontMapPath(textId);
		auto isFacingCameraHorizontally = _fe3d->text3d_isFacingCameraHorizontally(textId);
		auto isFacingCameraVertically = _fe3d->text3d_isFacingCameraVertically(textId);
		auto isReflected = _fe3d->text3d_isReflected(textId);
		auto isShadowed = _fe3d->text3d_isShadowed(textId);
		auto lightness = _fe3d->text3d_getLightness(textId);
		auto isBright = _fe3d->text3d_isBright(textId);
		auto opacity = _fe3d->text3d_getOpacity(textId);

		fontMapPath = string(fontMapPath.empty() ? "" : fontMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));

		fontMapPath = (fontMapPath.empty()) ? "?" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), ' ', '?');

		file <<
			textId << " " <<
			size.x << " " <<
			size.y << " " <<
			color.r << " " <<
			color.g << " " <<
			color.b << " " <<
			isFacingCameraHorizontally << " " <<
			isFacingCameraVertically << " " <<
			fontMapPath << " " <<
			isReflected << " " <<
			isShadowed << " " <<
			lightness << " " <<
			isBright << " " <<
			opacity << endl;
	}

	file.close();

	Logger::throwInfo("Text3D editor data saved");

	return true;
}