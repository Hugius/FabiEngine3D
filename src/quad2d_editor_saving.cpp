#include "quad2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool Quad2dEditor::saveEntitiesToFile() const
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
	auto file = ofstream(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\quad2d.fe3d");

	for(const auto & quad2dId : _loadedQuad2dIds)
	{
		auto diffuseMapPath = _fe3d->quad2d_getDiffuseMapPath(quad2dId);
		auto color = _fe3d->quad2d_getColor(quad2dId);
		auto opacity = _fe3d->quad2d_getOpacity(quad2dId);
		auto textureRepeat = _fe3d->quad2d_getTextureRepeat(quad2dId);
		auto isHorizontallyFlipped = _fe3d->quad2d_isHorizontallyFlipped(quad2dId);
		auto isVerticallyFlipped = _fe3d->quad2d_isVerticallyFlipped(quad2dId);

		diffuseMapPath = (diffuseMapPath.empty() ? "" : diffuseMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));

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
			<< endl;
	}

	file.close();

	Logger::throwInfo("Quad2D editor data saved");

	return true;
}