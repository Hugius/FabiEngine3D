#include "billboard_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> BillboardEditor::getAllTexturePathsFromFile() const
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("BillboardEditor::getAllTexturePathsFromFile");
	}

	// Compose file path
	const string filePath = (Tools::getRootDirectoryPath() + (_fe3d.application_isExported() ? "" :
														 ("projects\\" + _currentProjectID)) + "\\data\\billboard.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `billboard.fe3d` missing!");
		return {};
	}

	// Load billboard file
	ifstream file(filePath);

	// Read billboard data
	vector<string> texturePaths;
	string line;
	while(getline(file, line))
	{
		// Data placeholders
		string billboardID, diffuseMapPath, emissionMapPath;
		Vec2 size;
		Vec3 color;
		bool facingX, facingY;

		// For file extraction
		istringstream iss(line);

		// Read data from file
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
			emissionMapPath;

		// Perform empty string & space conversions
		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');

		// Save diffuse map path
		if(!diffuseMapPath.empty())
		{
			texturePaths.push_back(diffuseMapPath);
		}

		// Save emission map path
		if(!emissionMapPath.empty())
		{
			texturePaths.push_back(emissionMapPath);
		}
	}

	// Close file
	file.close();

	// Return
	return texturePaths;
}

const vector<string> BillboardEditor::getAllFontPathsFromFile() const
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("BillboardEditor::getAllFontPathsFromFile");
	}

	// Compose file path
	const string filePath = Tools::getRootDirectoryPath() + (_fe3d.application_isExported() ? "" :
														 ("projects\\" + _currentProjectID)) + "\\data\\billboard.fe3d";

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `billboard.fe3d` missing!");
		return {};
	}

	// Load billboard file
	ifstream file(filePath);

	// Read billboard data
	vector<string> fontPaths;
	string line;
	while(getline(file, line))
	{
		// Data placeholders
		string billboardID, diffuseMapPath, fontPath;
		Vec2 size;
		Vec3 color;
		bool facingX, facingY, isReflected, isShadowed;

		// For file extraction
		istringstream iss(line);

		// Read data from file
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
			isReflected >>
			isShadowed >>
			fontPath;

		// Perform empty string & space conversions
		fontPath = (fontPath == "?") ? "" : fontPath;
		replace(fontPath.begin(), fontPath.end(), '?', ' ');

		// Save file path
		if(!fontPath.empty())
		{
			fontPaths.push_back(fontPath);
		}
	}

	// Close file
	file.close();

	// Return
	return fontPaths;
}

const bool BillboardEditor::loadBillboardEntitiesFromFile()
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("BillboardEditor::loadBillboardEntitiesFromFile");
	}

	// Clear IDs from previous loads
	_loadedBillboardIDs.clear();

	// Compose file path
	const string filePath = Tools::getRootDirectoryPath() + (_fe3d.application_isExported() ? "" :
														 ("projects\\" + _currentProjectID)) + "\\data\\billboard.fe3d";

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `billboard.fe3d` missing!");
		return false;
	}

	// Load billboard file
	ifstream file(filePath);

	// Read billboard data
	string line;
	while(getline(file, line))
	{
		// Data placeholders
		string billboardID, diffuseMapPath, emissionMapPath, fontPath, textContent;
		Vec2 size;
		Vec3 color;
		float lightness, textureRepeat;
		bool isFacingX, isFacingY, isReflected, isShadowed, isAnimationStarted;
		unsigned int animationRows, animationColumns, animationFramestep;

		// For file extraction
		istringstream iss(line);

		// Read from file
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
			emissionMapPath >>
			isReflected >>
			isShadowed >>
			fontPath >>
			textContent >>
			isAnimationStarted >>
			animationRows >>
			animationColumns >>
			animationFramestep >>
			lightness >>
			textureRepeat;

		// Perform empty string & space conversions
		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;
		fontPath = (fontPath == "?") ? "" : fontPath;
		textContent = (textContent == "?") ? "" : textContent;
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');
		replace(fontPath.begin(), fontPath.end(), '?', ' ');
		replace(textContent.begin(), textContent.end(), '?', ' ');

		// Create billboard
		_fe3d.billboardEntity_create(billboardID);

		// Check if billboard creation went well
		if(_fe3d.billboardEntity_isExisting(billboardID))
		{
			// Add billboard ID
			_loadedBillboardIDs.push_back(billboardID);

			// Diffuse map
			if(!diffuseMapPath.empty())
			{
				// Set diffuse map
				_fe3d.billboardEntity_setDiffuseMap(billboardID, diffuseMapPath);

				// Play sprite animation
				if(isAnimationStarted)
				{
					_fe3d.billboardEntity_setSpriteAnimationFramestep(billboardID, animationFramestep);
					_fe3d.billboardEntity_setSpriteAnimationRows(billboardID, animationRows);
					_fe3d.billboardEntity_setSpriteAnimationColumns(billboardID, animationColumns);
					_fe3d.billboardEntity_startSpriteAnimation(billboardID, -1);
				}
			}

			// Emission map
			if(!emissionMapPath.empty())
			{
				_fe3d.billboardEntity_setEmissionMap(billboardID, emissionMapPath);
			}

			// Text
			if(!fontPath.empty())
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
			_fe3d.billboardEntity_setShadowed(billboardID, isShadowed);
			_fe3d.billboardEntity_setReflected(billboardID, isReflected);
			_fe3d.billboardEntity_setTextureRepeat(billboardID, textureRepeat);
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Billboard data from project \"" + _currentProjectID + "\" loaded!");

	// Return
	return true;
}