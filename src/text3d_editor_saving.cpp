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

	if(_currentProjectID.empty())
	{
		Logger::throwError("Quad3dEditor::saveToFile");
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + _currentProjectID + "\\data\\quad3d.fe3d");

	for(const auto& quadID : _loadedQuadIDs)
	{
		auto size = _fe3d->quad3d_getSize(quadID);
		auto color = _fe3d->quad3d_getColor(quadID);
		auto diffuseMapPath = _fe3d->quad3d_getDiffuseMapPath(quadID);
		auto emissionMapPath = _fe3d->quad3d_getEmissionMapPath(quadID);
		auto isFacingX = _fe3d->quad3d_isFacingCameraX(quadID);
		auto isFacingY = _fe3d->quad3d_isFacingCameraY(quadID);
		auto isReflected = _fe3d->quad3d_isReflected(quadID);
		auto isShadowed = _fe3d->quad3d_isShadowed(quadID);
		auto lightness = _fe3d->quad3d_getLightness(quadID);
		auto textureRepeat = _fe3d->quad3d_getTextureRepeat(quadID);
		auto isBright = _fe3d->quad3d_isBright(quadID);
		auto emissionIntensity = _fe3d->quad3d_getEmissionIntensity(quadID);
		auto transparency = _fe3d->quad3d_getTransparency(quadID);

		diffuseMapPath = string(diffuseMapPath.empty() ? "" : diffuseMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		emissionMapPath = string(emissionMapPath.empty() ? "" : emissionMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
		emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');

		file <<
			quadID << " " <<
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
			transparency << endl;
	}

	file.close();

	Logger::throwInfo("Quad3d editor data saved!");

	return true;
}