#include "text2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool Text2dEditor::saveEntitiesToFile() const
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
	auto file = ofstream(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\text2d.fe3d");

	for(const auto & textId : _loadedText2dIds)
	{
		auto fontMapPath = _fe3d->text2d_getFontMapPath(textId);
		auto color = _fe3d->text2d_getColor(textId);
		auto opacity = _fe3d->text2d_getOpacity(textId);
		auto isHorizontallyFlipped = _fe3d->text2d_isHorizontallyFlipped(textId);
		auto isVerticallyFlipped = _fe3d->text2d_isVerticallyFlipped(textId);

		fontMapPath = (fontMapPath.empty() ? "" : fontMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));

		fontMapPath = (fontMapPath.empty()) ? "?" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), ' ', '?');

		file
			<< textId
			<< " "
			<< fontMapPath
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< opacity
			<< " "
			<< isHorizontallyFlipped
			<< " "
			<< isVerticallyFlipped
			<< endl;
	}

	file.close();

	Logger::throwInfo("Text2D editor data saved");

	return true;
}