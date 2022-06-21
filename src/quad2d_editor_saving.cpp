#include "quad2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool Quad2dEditor::saveQuad2dsToFile() const
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
	const auto filePath = (rootPath + "projects\\" + getCurrentProjectId() + "\\domain\\quad2d.fe3d");

	auto file = ofstream(filePath);

	for(const auto & quad2dId : _loadedQuad2dIds)
	{
		const auto color = _fe3d->quad2d_getColor(quad2dId);
		const auto opacity = _fe3d->quad2d_getOpacity(quad2dId);
		const auto lightness = _fe3d->quad2d_getLightness(quad2dId);
		const auto textureRepeat = _fe3d->quad2d_getTextureRepeat(quad2dId);
		const auto isHorizontallyFlipped = _fe3d->quad2d_isHorizontallyFlipped(quad2dId);
		const auto isVerticallyFlipped = _fe3d->quad2d_isVerticallyFlipped(quad2dId);

		auto diffuseMapPath = _fe3d->quad2d_getDiffuseMapPath(quad2dId);

		if(!diffuseMapPath.empty())
		{
			diffuseMapPath = diffuseMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size());
		}

		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');

		file
			<< quad2dId
			<< " "
			<< diffuseMapPath
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< opacity
			<< " "
			<< textureRepeat
			<< " "
			<< isHorizontallyFlipped
			<< " "
			<< isVerticallyFlipped
			<< " "
			<< lightness
			<< endl;
	}

	file.close();

	Logger::throwInfo("Quad2D editor data saved");

	return true;
}