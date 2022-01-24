#include "quad3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool Quad3dEditor::saveToFile() const
{
	if(!_isEditorLoaded)
	{
		return false;
	}

	if(_currentProjectId.empty())
	{
		Logger::throwError("Quad3dEditor::saveToFile");
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + _currentProjectId + "\\data\\quad3d.fe3d");

	for(const auto& quadId : _loadedQuadIds)
	{
		auto size = _fe3d->quad3d_getSize(quadId);
		auto color = _fe3d->quad3d_getColor(quadId);
		auto diffuseMapPath = _fe3d->quad3d_getDiffuseMapPath(quadId);
		auto emissionMapPath = _fe3d->quad3d_getEmissionMapPath(quadId);
		auto isFacingX = _fe3d->quad3d_isFacingCameraX(quadId);
		auto isFacingY = _fe3d->quad3d_isFacingCameraY(quadId);
		auto isReflected = _fe3d->quad3d_isReflected(quadId);
		auto isShadowed = _fe3d->quad3d_isShadowed(quadId);
		auto lightness = _fe3d->quad3d_getLightness(quadId);
		auto textureRepeat = _fe3d->quad3d_getTextureRepeat(quadId);
		auto isBright = _fe3d->quad3d_isBright(quadId);
		auto emissionIntensity = _fe3d->quad3d_getEmissionIntensity(quadId);
		auto opacity = _fe3d->quad3d_getOpacity(quadId);

		diffuseMapPath = string(diffuseMapPath.empty() ? "" : diffuseMapPath.substr(string("projects\\" + _currentProjectId + "\\").size()));
		emissionMapPath = string(emissionMapPath.empty() ? "" : emissionMapPath.substr(string("projects\\" + _currentProjectId + "\\").size()));

		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
		emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');

		file <<
			quadId << " " <<
			size.x << " " <<
			size.y << " " <<
			color.r << " " <<
			color.g << " " <<
			color.b << " " <<
			isFacingX << " " <<
			isFacingY << " " <<
			diffuseMapPath << " " <<
			emissionMapPath << " " <<
			isReflected << " " <<
			isShadowed << " " <<
			lightness << " " <<
			textureRepeat << " " <<
			isBright << " " <<
			emissionIntensity << " " <<
			opacity << endl;
	}

	file.close();

	Logger::throwInfo("Quad3d editor data saved!");

	return true;
}