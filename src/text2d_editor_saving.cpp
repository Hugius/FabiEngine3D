#include "text2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool Text2dEditor::saveText2dsToFile() const
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
	const auto filePath = (rootPath + "projects\\" + getCurrentProjectId() + "\\domain\\text2d.fe3d");

	auto file = ofstream(filePath);

	for(const auto & text2dId : _loadedText2dIds)
	{
		const auto color = _fe3d->text2d_getColor(text2dId);
		const auto opacity = _fe3d->text2d_getOpacity(text2dId);
		const auto lightness = _fe3d->text2d_getLightness(text2dId);
		const auto isHorizontallyFlipped = _fe3d->text2d_isHorizontallyFlipped(text2dId);
		const auto isVerticallyFlipped = _fe3d->text2d_isVerticallyFlipped(text2dId);

		auto fontMapPath = _fe3d->text2d_getFontMapPath(text2dId);

		if(!fontMapPath.empty())
		{
			fontMapPath = fontMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size());
		}

		fontMapPath = (fontMapPath.empty()) ? "?" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), ' ', '?');

		file
			<< text2dId
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
			<< " "
			<< lightness
			<< endl;
	}

	file.close();

	Logger::throwInfo("Text2D editor data saved");

	return true;
}