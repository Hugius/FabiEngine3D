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
	ofstream file(rootPath + "projects\\" + _currentProjectID + "\\data\\billboard.fe3d");

	for(const auto& quad3dID : _loadedQuad3dIDs)
	{
		auto size = _fe3d->quad3d_getSize(quad3dID);
		auto color = _fe3d->quad3d_getColor(quad3dID);
		auto diffuseMapPath = _fe3d->quad3d_getDiffuseMapPath(quad3dID);
		auto emissionMapPath = _fe3d->quad3d_getEmissionMapPath(quad3dID);
		auto isFacingX = _fe3d->quad3d_isFacingCameraX(quad3dID);
		auto isFacingY = _fe3d->quad3d_isFacingCameraY(quad3dID);
		auto isReflected = _fe3d->quad3d_isReflected(quad3dID);
		auto isShadowed = _fe3d->quad3d_isShadowed(quad3dID);
		auto lightness = _fe3d->quad3d_getLightness(quad3dID);
		auto textureRepeat = _fe3d->quad3d_getTextureRepeat(quad3dID);
		auto isBright = _fe3d->quad3d_isBright(quad3dID);
		auto emissionIntensity = _fe3d->quad3d_getEmissionIntensity(quad3dID);
		auto transparency = _fe3d->quad3d_getTransparency(quad3dID);

		diffuseMapPath = string(diffuseMapPath.empty() ? "" : diffuseMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		emissionMapPath = string(emissionMapPath.empty() ? "" : emissionMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
		emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');

		file <<
			quad3dID << " " <<
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

	Logger::throwInfo("Billboard editor data saved!");

	return true;
}