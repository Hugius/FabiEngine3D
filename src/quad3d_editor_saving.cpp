#include "quad3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool Quad3dEditor::saveQuad3dsToFile() const
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
	const auto filePath = (rootPath + "projects\\" + getCurrentProjectId() + "\\data\\quad3d.fe3d");

	auto file = ofstream(filePath);

	for(const auto & quad3dId : _loadedQuad3dIds)
	{
		const auto aabbIds = _fe3d->quad3d_getChildAabbIds(quad3dId);
		const auto size = _fe3d->quad3d_getSize(quad3dId);
		const auto color = _fe3d->quad3d_getColor(quad3dId);
		const auto isFacingCameraHorizontally = _fe3d->quad3d_isFacingCameraHorizontally(quad3dId);
		const auto isFacingCameraVertically = _fe3d->quad3d_isFacingCameraVertically(quad3dId);
		const auto isHorizontallyFlipped = _fe3d->quad3d_isHorizontallyFlipped(quad3dId);
		const auto isVerticallyFlipped = _fe3d->quad3d_isVerticallyFlipped(quad3dId);
		const auto isReflected = _fe3d->quad3d_isReflected(quad3dId);
		const auto isRefracted = _fe3d->quad3d_isRefracted(quad3dId);
		const auto isShadowed = _fe3d->quad3d_isShadowed(quad3dId);
		const auto lightness = _fe3d->quad3d_getLightness(quad3dId);
		const auto textureRepeat = _fe3d->quad3d_getTextureRepeat(quad3dId);
		const auto isBright = _fe3d->quad3d_isBright(quad3dId);
		const auto emissionIntensity = _fe3d->quad3d_getEmissionIntensity(quad3dId);
		const auto opacity = _fe3d->quad3d_getOpacity(quad3dId);
		const auto minAlpha = _fe3d->quad3d_getMinAlpha(quad3dId);
		const auto rotationOrder = static_cast<int>(_fe3d->quad3d_getRotationOrder(quad3dId));

		auto diffuseMapPath = _fe3d->quad3d_getDiffuseMapPath(quad3dId);
		auto emissionMapPath = _fe3d->quad3d_getEmissionMapPath(quad3dId);

		diffuseMapPath = (diffuseMapPath.empty() ? "" : diffuseMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
		emissionMapPath = (emissionMapPath.empty() ? "" : emissionMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
		emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');

		file
			<< "QUAD3D "
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
			<< isRefracted
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
			<< minAlpha
			<< " "
			<< rotationOrder
			<< endl;

		for(const auto & aabbId : aabbIds)
		{
			file
				<< "AABB "
				<< quad3dId
				<< " "
				<< aabbId
				<< endl;
		}
	}

	file.close();

	Logger::throwInfo("Quad3D editor data saved");

	return true;
}