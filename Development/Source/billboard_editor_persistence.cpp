#include "billboard_editor.hpp"
#include "logger.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

const vector<string> BillboardEditor::getAllTexturePathsFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("BillboardEditor::getAllTexturePathsFromFile() ---> no current project loaded!");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\billboard.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: \"billboard.fe3d\" file missing!");
		return {};
	}

	// Load billboard file
	std::ifstream file(filePath);

	// Read billboard data
	vector<string> texturePaths;
	string line;
	while (std::getline(file, line))
	{
		// Temporary values
		string billboardID, diffuseMapPath;
		Vec2 size;
		Vec3 color;
		bool facingX, facingY;
		std::istringstream iss(line);

		// Extract data
		iss >>
			billboardID >>
			size.x >>
			size.y >>
			color.r >>
			color.g >>
			color.b >>
			facingX >>
			facingY >>
			diffuseMapPath;

		// Perform empty string & space conversions
		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');

		// Save file paths
		if (!diffuseMapPath.empty())
		{
			texturePaths.push_back(diffuseMapPath);
		}
	}

	// Close file
	file.close();

	// Return
	return texturePaths;
}

bool BillboardEditor::loadBillboardEntitiesFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("BillboardEditor::loadBillboardEntitiesFromFile() ---> no current project loaded!");
	}

	// Clear IDs from previous loads
	_loadedBillboardIDs.clear();

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\billboard.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: \"billboard.fe3d\" file missing!");
		return false;
	}

	// Load billboard file
	std::ifstream file(filePath);

	// Read billboard data
	string line;
	while (std::getline(file, line))
	{
		// Placeholder variables
		string billboardID, diffuseMapPath, fontPath, textContent;
		Vec2 size;
		Vec3 color;
		float lightness;
		bool isFacingX, isFacingY, isTransparent, isReflected, isShadowed, isAnimationStarted, isBright;
		unsigned int animationRows, animationColumns, animationFramestep;

		// For file extraction
		std::istringstream iss(line);

		// Extract from file
		iss >>
			billboardID >>
			size.x >>
			size.y >>
			color.r >>
			color.g >>
			color.b >>
			isFacingX >>
			isFacingY >>
			diffuseMapPath >>
			isTransparent >>
			isReflected >>
			isShadowed >>
			fontPath >>
			textContent >>
			isAnimationStarted >>
			animationRows >>
			animationColumns >>
			animationFramestep >>
			lightness >>
			isBright;

		// Perform empty string & space conversions
		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		fontPath = (fontPath == "?") ? "" : fontPath;
		textContent = (textContent == "?") ? "" : textContent;
		std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		std::replace(fontPath.begin(), fontPath.end(), '?', ' ');
		std::replace(textContent.begin(), textContent.end(), '?', ' ');

		// Add billboard name
		_loadedBillboardIDs.push_back(billboardID);

		// Determine billboard type
		if (diffuseMapPath != "")
		{
			// Textured billboard
			_fe3d.billboardEntity_add(billboardID, diffuseMapPath, Vec3(0.0f), Vec3(0.0f), size, isTransparent, isFacingX, isFacingY, false);
			_fe3d.billboardEntity_setColor(billboardID, color);

			// Play sprite animation
			if (isAnimationStarted)
			{
				_fe3d.billboardEntity_setSpriteAnimationFramestep(billboardID, animationFramestep);
				_fe3d.billboardEntity_setSpriteAnimationRows(billboardID, animationRows);
				_fe3d.billboardEntity_setSpriteAnimationColumns(billboardID, animationColumns);
				_fe3d.billboardEntity_startSpriteAnimation(billboardID, -1);
			}
		}
		else if (fontPath != "") // Text billboard
		{
			_fe3d.billboardEntity_add(billboardID, textContent, fontPath, color, Vec3(0.0f), Vec3(0.0f), size, isFacingX, isFacingY, false);
		}
		else // Colored billboard
		{
			_fe3d.billboardEntity_add(billboardID, color, Vec3(0.0f), Vec3(0.0f), size, isFacingX, isFacingY, false);
		}

		// Miscellaneous
		_fe3d.billboardEntity_setLightness(billboardID, lightness);
		_fe3d.billboardEntity_setShadowed(billboardID, isShadowed);
		_fe3d.billboardEntity_setReflected(billboardID, isReflected);
		_fe3d.billboardEntity_setBright(billboardID, isBright);
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Billboard data from project \"" + _currentProjectID + "\" loaded!");

	// Return
	return true;
}

bool BillboardEditor::saveBillboardEntitiesToFile()
{
	// Editor must be loaded
	if (!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("BillboardEditor::saveBillboardEntitiesToFile() ---> no current project loaded!");
	}

	// Compose file path
	const string filePath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\billboard.fe3d");

	// Create or overwrite billboard file
	std::ofstream file(filePath);

	// Write billboard data
	for (const auto& billboardID : _loadedBillboardIDs)
	{
		// Retrieve all values
		auto size = _fe3d.billboardEntity_getSize(billboardID);
		auto color = _fe3d.billboardEntity_getColor(billboardID);
		auto diffuseMapPath = _fe3d.billboardEntity_getDiffuseMapPath(billboardID);
		auto fontPath = _fe3d.billboardEntity_getFontPath(billboardID);
		auto textContent = _fe3d.billboardEntity_getTextContent(billboardID);
		auto isFacingX = _fe3d.billboardEntity_isFacingCameraX(billboardID);
		auto isFacingY = _fe3d.billboardEntity_isFacingCameraY(billboardID);
		auto isTransparent = _fe3d.billboardEntity_isTransparent(billboardID);
		auto isReflected = _fe3d.billboardEntity_isReflected(billboardID);
		auto isShadowed = _fe3d.billboardEntity_isShadowed(billboardID);
		auto isAnimationStarted = _fe3d.billboardEntity_isSpriteAnimationStarted(billboardID);
		auto animationRows = _fe3d.billboardEntity_getSpriteAnimationRows(billboardID);
		auto animationColumns = _fe3d.billboardEntity_getSpriteAnimationColumns(billboardID);
		auto animationFramestep = _fe3d.billboardEntity_getSpriteAnimationFramestep(billboardID);
		auto lightness = _fe3d.billboardEntity_getLightness(billboardID);
		auto isBright = _fe3d.billboardEntity_isBright(billboardID);

		// Perform empty string & space conversions
		diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
		fontPath = (fontPath == "") ? "?" : fontPath;
		textContent = (textContent == "") ? "?" : textContent;
		std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		std::replace(fontPath.begin(), fontPath.end(), ' ', '?');
		std::replace(textContent.begin(), textContent.end(), ' ', '?');

		// Export data
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
			isTransparent << " " <<
			isReflected << " " <<
			isShadowed << " " <<
			fontPath << " " <<
			textContent << " " <<
			isAnimationStarted << " " <<
			animationRows << " " <<
			animationColumns << " " <<
			animationFramestep << " " <<
			lightness << " " <<
			isBright << std::endl;
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Billboard data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}