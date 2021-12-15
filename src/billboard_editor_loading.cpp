#include "billboard_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> BillboardEditor::getTexturePathsFromFile() const
{
	// Validate project ID
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("BillboardEditor::getTexturePathsFromFile");
	}

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\billboard.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `billboard.fe3d` missing!");
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
		fvec2 size;
		fvec3 color;
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

		// Convert empty string
		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;

		// Convert spaces
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');

		// Diffuse map
		if(!diffuseMapPath.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
			}

			// Save path
			texturePaths.push_back(diffuseMapPath);
		}

		// Emission map
		if(!emissionMapPath.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				emissionMapPath = string("projects\\" + _currentProjectID + "\\" + emissionMapPath);
			}

			// Save path
			texturePaths.push_back(emissionMapPath);
		}
	}

	// Close file
	file.close();

	// Return
	return texturePaths;
}

const vector<string> BillboardEditor::getFontPathsFromFile() const
{
	// Validate project ID
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("BillboardEditor::getFontPathsFromFile");
	}

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\billboard.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `billboard.fe3d` missing!");
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
		fvec2 size;
		fvec3 color;
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

		// Convert empty string
		fontPath = (fontPath == "?") ? "" : fontPath;

		// Convert spaces
		replace(fontPath.begin(), fontPath.end(), '?', ' ');

		// Font
		if(!fontPath.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				fontPath = string("projects\\" + _currentProjectID + "\\" + fontPath);
			}

			// Save path
			fontPaths.push_back(fontPath);
		}
	}

	// Close file
	file.close();

	// Return
	return fontPaths;
}

const bool BillboardEditor::loadFromFile()
{
	// Validate project ID
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("BillboardEditor::loadFromFile");
	}

	// Clear IDs from previous loads
	_loadedBillboardIDs.clear();

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\billboard.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `billboard.fe3d` missing!");
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
		fvec2 size;
		fvec3 color;
		float lightness, textureRepeat;
		bool isFacingX, isFacingY, isReflected, isShadowed;

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
			lightness >>
			textureRepeat;

		// Convert empty string
		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;
		fontPath = (fontPath == "?") ? "" : fontPath;
		textContent = (textContent == "?") ? "" : textContent;

		// Convert spaces
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');
		replace(fontPath.begin(), fontPath.end(), '?', ' ');
		replace(textContent.begin(), textContent.end(), '?', ' ');

		// Create billboard
		_fe3d.billboard_create(billboardID);

		// Check if billboard creation went well
		if(_fe3d.billboard_isExisting(billboardID))
		{
			// Add billboard ID
			_loadedBillboardIDs.push_back(billboardID);

			// Diffuse map
			if(!diffuseMapPath.empty())
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
				}

				// Set path
				_fe3d.billboard_setDiffuseMap(billboardID, diffuseMapPath);
			}

			// Emission map
			if(!emissionMapPath.empty())
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					emissionMapPath = string("projects\\" + _currentProjectID + "\\" + emissionMapPath);
				}

				// Set path
				_fe3d.billboard_setEmissionMap(billboardID, emissionMapPath);
			}

			// Font
			if(!fontPath.empty())
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					fontPath = string("projects\\" + _currentProjectID + "\\" + fontPath);
				}

				// Set path
				_fe3d.billboard_setFont(billboardID, fontPath);
				_fe3d.billboard_setTextContent(billboardID, textContent);
			}

			// Set properties
			_fe3d.billboard_setVisible(billboardID, false);
			_fe3d.billboard_setSize(billboardID, size);
			_fe3d.billboard_setColor(billboardID, color);
			_fe3d.billboard_setLightness(billboardID, lightness);
			_fe3d.billboard_setFacingCameraX(billboardID, isFacingX);
			_fe3d.billboard_setFacingCameraY(billboardID, isFacingY);
			_fe3d.billboard_setShadowed(billboardID, isShadowed);
			_fe3d.billboard_setReflected(billboardID, isReflected);
			_fe3d.billboard_setTextureRepeat(billboardID, textureRepeat);
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Billboard data loaded!");

	// Return
	return true;
}