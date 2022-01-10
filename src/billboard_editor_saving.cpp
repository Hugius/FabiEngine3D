#include "billboard_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool BillboardEditor::saveToFile() const
{
	if(!_isEditorLoaded)
	{
		return false;
	}

	if(_currentProjectID.empty())
	{
		Logger::throwError("BillboardEditor::saveToFile");
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + _currentProjectID + "\\data\\billboard.fe3d");

	for(const auto& billboardID : _loadedBillboardIDs)
	{
		auto size = _fe3d->billboard_getSize(billboardID);
		auto color = _fe3d->billboard_getColor(billboardID);
		auto diffuseMapPath = _fe3d->billboard_getDiffuseMapPath(billboardID);
		auto emissionMapPath = _fe3d->billboard_getEmissionMapPath(billboardID);
		auto fontPath = _fe3d->billboard_getFontPath(billboardID);
		auto textContent = _fe3d->billboard_getTextContent(billboardID);
		auto isFacingX = _fe3d->billboard_isFacingCameraX(billboardID);
		auto isFacingY = _fe3d->billboard_isFacingCameraY(billboardID);
		auto isReflected = _fe3d->billboard_isReflected(billboardID);
		auto isShadowed = _fe3d->billboard_isShadowed(billboardID);
		auto lightness = _fe3d->billboard_getLightness(billboardID);
		auto textureRepeat = _fe3d->billboard_getTextureRepeat(billboardID);

		diffuseMapPath = string(diffuseMapPath.empty() ? "" : diffuseMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		emissionMapPath = string(emissionMapPath.empty() ? "" : emissionMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		fontPath = string(fontPath.empty() ? "" : fontPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
		emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;
		fontPath = (fontPath.empty()) ? "?" : fontPath;
		textContent = (textContent.empty()) ? "?" : textContent;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');
		replace(fontPath.begin(), fontPath.end(), ' ', '?');
		replace(textContent.begin(), textContent.end(), ' ', '?');

		file <<
			billboardID << " " <<
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
			fontPath << " " <<
			textContent << " " <<
			lightness << " " <<
			textureRepeat << endl;
	}

	file.close();

	Logger::throwInfo("Billboard editor data saved!");

	return true;
}