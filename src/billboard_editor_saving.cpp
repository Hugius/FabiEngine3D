#include "billboard_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool BillboardEditor::saveToFile() const
{
	// Editor must be loaded
	if(!_isEditorLoaded)
	{
		return false;
	}

	// Validate project ID
	if(_currentProjectID.empty())
	{
		Logger::throwError("BillboardEditor::saveToFile");
	}

	// Create or overwrite file
	ofstream file(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\data\\billboard.fe3d");

	// Write billboard data
	for(const auto& billboardID : _loadedBillboardIDs)
	{
		// Data to save
		auto size = _fe3d.billboard_getSize(billboardID);
		auto color = _fe3d.billboard_getColor(billboardID);
		auto diffuseMapPath = _fe3d.billboard_getDiffuseMapPath(billboardID);
		auto emissionMapPath = _fe3d.billboard_getEmissionMapPath(billboardID);
		auto fontPath = _fe3d.billboard_getFontPath(billboardID);
		auto textContent = _fe3d.billboard_getTextContent(billboardID);
		auto isFacingX = _fe3d.billboard_isFacingCameraX(billboardID);
		auto isFacingY = _fe3d.billboard_isFacingCameraY(billboardID);
		auto isReflected = _fe3d.billboard_isReflected(billboardID);
		auto isShadowed = _fe3d.billboard_isShadowed(billboardID);
		auto lightness = _fe3d.billboard_getLightness(billboardID);
		auto textureRepeat = _fe3d.billboard_getTextureRepeat(billboardID);

		// Convert to short path
		diffuseMapPath = string(diffuseMapPath.empty() ? "" : diffuseMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		emissionMapPath = string(emissionMapPath.empty() ? "" : emissionMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		fontPath = string(fontPath.empty() ? "" : fontPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

		// Convert empty string
		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
		emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;
		fontPath = (fontPath.empty()) ? "?" : fontPath;
		textContent = (textContent.empty()) ? "?" : textContent;

		// Convert spaces
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');
		replace(fontPath.begin(), fontPath.end(), ' ', '?');
		replace(textContent.begin(), textContent.end(), ' ', '?');

		// Write data to file
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

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Billboard data saved!");

	// Return
	return true;
}