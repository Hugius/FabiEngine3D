#include "billboard_editor.hpp"
#include "logger.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::istringstream;

const vector<string> BillboardEditor::getAllTexturePathsFromFile()
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("BillboardEditor::getAllTexturePathsFromFile");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\billboard.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `billboard.fe3d` missing!");
		return {};
	}

	// Load billboard file
	ifstream file(filePath);

	// Read billboard data
	vector<string> texturePaths;
	string line;
	while (getline(file, line))
	{
		// Values
		string billboardID, diffuseMapPath;
		Vec2 size;
		Vec3 color;
		bool facingX, facingY;

		// For file extraction
		istringstream iss(line);

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
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');

		// Save file path
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

const vector<string> BillboardEditor::getAllFontPathsFromFile()
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("BillboardEditor::getAllFontPathsFromFile");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\billboard.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `billboard.fe3d` missing!");
		return {};
	}

	// Load billboard file
	ifstream file(filePath);

	// Read billboard data
	vector<string> fontPaths;
	string line;
	while (getline(file, line))
	{
		// Values
		string billboardID, diffuseMapPath, fontPath;
		Vec2 size;
		Vec3 color;
		bool facingX, facingY, isTransparent, isReflected, isShadowed;

		// For file extraction
		istringstream iss(line);

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
			diffuseMapPath >>
			isTransparent >>
			isReflected >>
			isShadowed >>
			fontPath;

		// Perform empty string & space conversions
		fontPath = (fontPath == "?") ? "" : fontPath;
		replace(fontPath.begin(), fontPath.end(), '?', ' ');

		// Save file path
		if (!fontPath.empty())
		{
			fontPaths.push_back(fontPath);
		}
	}

	// Close file
	file.close();

	// Return
	return fontPaths;
}

bool BillboardEditor::loadBillboardEntitiesFromFile()
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("BillboardEditor::loadBillboardEntitiesFromFile");
	}

	// Clear IDs from previous loads
	_loadedBillboardIDs.clear();

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\billboard.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `billboard.fe3d` missing!");
		return false;
	}

	// Load billboard file
	ifstream file(filePath);

	// Read billboard data
	string line;
	while (getline(file, line))
	{
		// Placeholder variables
		string billboardID, diffuseMapPath, fontPath, textContent;
		Vec2 size;
		Vec3 color;
		float lightness, uvRepeat;
		bool isFacingX, isFacingY, isTransparent, isReflected, isShadowed, isAnimationStarted, isBright;
		unsigned int animationRows, animationColumns, animationFramestep;

		// For file extraction
		istringstream iss(line);

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
			isBright >>
			uvRepeat;

		// Perform empty string & space conversions
		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		fontPath = (fontPath == "?") ? "" : fontPath;
		textContent = (textContent == "?") ? "" : textContent;
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(fontPath.begin(), fontPath.end(), '?', ' ');
		replace(textContent.begin(), textContent.end(), '?', ' ');

		// Create billboard
		_fe3d.billboardEntity_create(billboardID);

		// Check if billboard creation went well
		if (_fe3d.billboardEntity_isExisting(billboardID))
		{
			// Add billboard ID
			_loadedBillboardIDs.push_back(billboardID);

			// Diffuse map
			if (!diffuseMapPath.empty())
			{
				// Set diffuse map
				_fe3d.billboardEntity_setDiffuseMap(billboardID, diffuseMapPath);

				// Play sprite animation
				if (isAnimationStarted)
				{
					_fe3d.billboardEntity_setSpriteAnimationFramestep(billboardID, animationFramestep);
					_fe3d.billboardEntity_setSpriteAnimationRows(billboardID, animationRows);
					_fe3d.billboardEntity_setSpriteAnimationColumns(billboardID, animationColumns);
					_fe3d.billboardEntity_startSpriteAnimation(billboardID, -1);
				}
			}

			// Text
			if (!fontPath.empty())
			{
				_fe3d.billboardEntity_setFont(billboardID, fontPath);
				_fe3d.billboardEntity_setTextContent(billboardID, textContent);
			}

			// Set properties
			_fe3d.billboardEntity_setVisible(billboardID, false);
			_fe3d.billboardEntity_setSize(billboardID, size);
			_fe3d.billboardEntity_setColor(billboardID, color);
			_fe3d.billboardEntity_setLightness(billboardID, lightness);
			_fe3d.billboardEntity_setCameraFacingX(billboardID, isFacingX);
			_fe3d.billboardEntity_setCameraFacingY(billboardID, isFacingY);
			_fe3d.billboardEntity_setTransparent(billboardID, isTransparent);
			_fe3d.billboardEntity_setShadowed(billboardID, isShadowed);
			_fe3d.billboardEntity_setReflected(billboardID, isReflected);
			_fe3d.billboardEntity_setBright(billboardID, isBright);
			_fe3d.billboardEntity_setUvRepeat(billboardID, uvRepeat);
		}
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
	if (_currentProjectID.empty())
	{
		Logger::throwError("BillboardEditor::saveBillboardEntitiesToFile");
	}

	// Compose file path
	const string filePath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\billboard.fe3d");

	// Create or overwrite billboard file
	ofstream file(filePath);

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
		auto uvRepeat = _fe3d.billboardEntity_getUvRepeat(billboardID);

		// Perform empty string & space conversions
		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
		fontPath = (fontPath.empty()) ? "?" : fontPath;
		textContent = (textContent.empty()) ? "?" : textContent;
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		replace(fontPath.begin(), fontPath.end(), ' ', '?');
		replace(textContent.begin(), textContent.end(), ' ', '?');

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
			isBright << " " <<
			uvRepeat << endl;
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Billboard data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}