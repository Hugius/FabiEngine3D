#include "quad3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool Quad3dEditor::saveEntitiesToFile() const
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
	auto file = ofstream(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\quad3d.fe3d");

	for(const auto & quad3dId : _loadedEntityIds)
	{
		auto size = _fe3d->quad3d_getSize(quad3dId);
		auto color = _fe3d->quad3d_getColor(quad3dId);
		auto diffuseMapPath = _fe3d->quad3d_getDiffuseMapPath(quad3dId);
		auto emissionMapPath = _fe3d->quad3d_getEmissionMapPath(quad3dId);
		auto isFacingCameraHorizontally = _fe3d->quad3d_isFacingCameraHorizontally(quad3dId);
		auto isFacingCameraVertically = _fe3d->quad3d_isFacingCameraVertically(quad3dId);
		auto isHorizontallyFlipped = _fe3d->quad3d_isHorizontallyFlipped(quad3dId);
		auto isVerticallyFlipped = _fe3d->quad3d_isVerticallyFlipped(quad3dId);
		auto isReflected = _fe3d->quad3d_isReflected(quad3dId);
		auto isShadowed = _fe3d->quad3d_isShadowed(quad3dId);
		auto lightness = _fe3d->quad3d_getLightness(quad3dId);
		auto textureRepeat = _fe3d->quad3d_getTextureRepeat(quad3dId);
		auto isBright = _fe3d->quad3d_isBright(quad3dId);
		auto emissionIntensity = _fe3d->quad3d_getEmissionIntensity(quad3dId);
		auto opacity = _fe3d->quad3d_getOpacity(quad3dId);
		auto minTextureAlpha = _fe3d->quad3d_getMinTextureAlpha(quad3dId);
		auto rotationOrder = static_cast<int>(_fe3d->quad3d_getRotationOrder(quad3dId));
		auto hasAabb = _fe3d->aabb_isExisting(quad3dId);

		diffuseMapPath = (diffuseMapPath.empty() ? "" : diffuseMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
		emissionMapPath = (emissionMapPath.empty() ? "" : emissionMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));

		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
		emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');

		file
			<< quad3dId
			<< " "
			<< diffuseMapPath
			<< " "
			<< emissionMapPath
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
			<< textureRepeat
			<< " "
			<< isBright
			<< " "
			<< emissionIntensity
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

	Logger::throwInfo("Quad3D editor data saved");

	return true;
}