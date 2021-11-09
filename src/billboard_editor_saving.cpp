#include "billboard_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool BillboardEditor::saveBillboardEntitiesToFile() const
{
	// Editor must be loaded
	if(!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("BillboardEditor::saveBillboardEntitiesToFile");
	}

	// Compose file path
	const string filePath = (Tools::getRootDirectoryPath() + (_fe3d.application_isExported() ? "" :
							 ("projects\\" + _currentProjectID)) + "\\data\\billboard.fe3d");

	// Create or overwrite billboard file
	ofstream file(filePath);

	// Write billboard data
	for(const auto& billboardID : _loadedBillboardIDs)
	{
		// Retrieve all values
		auto size = _fe3d.billboardEntity_getSize(billboardID);
		auto color = _fe3d.billboardEntity_getColor(billboardID);
		auto diffuseMapPath = _fe3d.billboardEntity_getDiffuseMapPath(billboardID);
		auto emissionMapPath = _fe3d.billboardEntity_getEmissionMapPath(billboardID);
		auto fontPath = _fe3d.billboardEntity_getFontPath(billboardID);
		auto textContent = _fe3d.billboardEntity_getTextContent(billboardID);
		auto isFacingX = _fe3d.billboardEntity_isFacingCameraX(billboardID);
		auto isFacingY = _fe3d.billboardEntity_isFacingCameraY(billboardID);
		auto isReflected = _fe3d.billboardEntity_isReflected(billboardID);
		auto isShadowed = _fe3d.billboardEntity_isShadowed(billboardID);
		auto isAnimationStarted = _fe3d.billboardEntity_isSpriteAnimationStarted(billboardID);
		auto animationRows = _fe3d.billboardEntity_getSpriteAnimationRows(billboardID);
		auto animationColumns = _fe3d.billboardEntity_getSpriteAnimationColumns(billboardID);
		auto animationFramestep = _fe3d.billboardEntity_getSpriteAnimationFramestep(billboardID);
		auto lightness = _fe3d.billboardEntity_getLightness(billboardID);
		auto textureRepeat = _fe3d.billboardEntity_getTextureRepeat(billboardID);

		// Perform empty string & space conversions
		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
		emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;
		fontPath = (fontPath.empty()) ? "?" : fontPath;
		textContent = (textContent.empty()) ? "?" : textContent;
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
			isAnimationStarted << " " <<
			animationRows << " " <<
			animationColumns << " " <<
			animationFramestep << " " <<
			lightness << " " <<
			textureRepeat << endl;
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Billboard data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}