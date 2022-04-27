#include "text3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool Text3dEditor::saveEntitiesToFile() const
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

	for(const auto & text3dId : _loadedText3dIds)
	{
		auto size = _fe3d->text3d_getSize(text3dId);
		auto color = _fe3d->text3d_getColor(text3dId);
		auto fontMapPath = _fe3d->text3d_getFontMapPath(text3dId);
		auto isFacingCameraHorizontally = _fe3d->text3d_isFacingCameraHorizontally(text3dId);
		auto isFacingCameraVertically = _fe3d->text3d_isFacingCameraVertically(text3dId);
		auto isHorizontallyFlipped = _fe3d->text3d_isHorizontallyFlipped(text3dId);
		auto isVerticallyFlipped = _fe3d->text3d_isVerticallyFlipped(text3dId);
		auto isReflected = _fe3d->text3d_isReflected(text3dId);
		auto isShadowed = _fe3d->text3d_isShadowed(text3dId);
		auto lightness = _fe3d->text3d_getLightness(text3dId);
		auto isBright = _fe3d->text3d_isBright(text3dId);
		auto opacity = _fe3d->text3d_getOpacity(text3dId);
		auto minTextureAlpha = _fe3d->text3d_getMinTextureAlpha(text3dId);
		auto rotationOrder = static_cast<int>(_fe3d->text3d_getRotationOrder(text3dId));
		auto hasAabb = _fe3d->aabb_isExisting(text3dId);

		fontMapPath = (fontMapPath.empty() ? "" : fontMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));

		fontMapPath = (fontMapPath.empty()) ? "?" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), ' ', '?');

		file
			<< text3dId
			<< " "
			<< fontMapPath
			<< " "
			<< size.x
			<< " "
			<< size.y
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< isFacingCameraHorizontally
			<< " "
			<< isFacingCameraVertically
			<< " "
			<< isHorizontallyFlipped
			<< " "
			<< isVerticallyFlipped
			<< " "
			<< isReflected
			<< " "
			<< isShadowed
			<< " "
			<< lightness
			<< " "
			<< isBright
			<< " "
			<< opacity
			<< " "
			<< minTextureAlpha
			<< " "
			<< rotationOrder
			<< " "
			<< hasAabb
			<< endl;
	}

	file.close();

	Logger::throwInfo("Text3D editor data saved");

	return true;
}