#include "billboard_editor.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

void BillboardEditor::loadBillboardEntitiesFromFile()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("No current project loaded!");
	}

	// Clear names list from previous loads
	_billboardNames.clear();

	// Compose full folder path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\billboard.fe3d";

	// Check if billboard file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		std::ifstream file(filePath);
		string line;

		// Read model data
		while (std::getline(file, line))
		{
			// Placeholder variables
			string name, diffusePath, fontPath, textContent;
			Vec2 size;
			Vec3 color;
			bool facingX, facingY, transparent, playing;
			int rows, columns, framestep;

			// For file extraction
			std::istringstream iss(line);

			// Extract from file
			iss >>
				name >>
				size.x >>
				size.y >>
				color.r >>
				color.g >>
				color.b >>
				facingX >>
				facingY >>
				diffusePath >>
				transparent >>
				fontPath >>
				textContent >>
				playing >>
				rows >>
				columns >>
				framestep;

			// Perform empty string & space conversions
			diffusePath = (diffusePath == "?") ? "" : diffusePath;
			fontPath = (fontPath == "?") ? "" : fontPath;
			textContent = (textContent == "?") ? "" : textContent;
			std::replace(diffusePath.begin(), diffusePath.end(), '?', ' ');
			std::replace(fontPath.begin(), fontPath.end(), '?', ' ');
			std::replace(textContent.begin(), textContent.end(), '?', ' ');

			// Add billboard name
			_billboardNames.push_back(name);

			// Determine billboard type
			if (diffusePath != "") // Textured billboard
			{
				_fe3d.billBoardEntity_add(name, diffusePath, _billboardPosition, Vec3(0.0f), size, transparent, facingX, facingY, false, false);
				_fe3d.billboardEntity_setColor(name, color);

				// Playing sprite animation
				if (playing)
				{
					_fe3d.billboardEntity_setAnimationFramestep(name, framestep);
					_fe3d.billboardEntity_setAnimationRows(name, rows);
					_fe3d.billboardEntity_setAnimationColumns(name, columns);
					_fe3d.billBoardEntity_playSpriteAnimation(name, -1);
				}
			}
			else if (fontPath != "") // Text billboard
			{
				_fe3d.billBoardEntity_add(name, textContent, fontPath, color, _billboardPosition, Vec3(0.0f), size, facingX, facingY, false);
			}
			else // Colored billboard
			{
				_fe3d.billBoardEntity_add(name, color, _billboardPosition, Vec3(0.0f), size, facingX, facingY, false);
			}
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Billboard data from project \"" + _currentProjectName + "\" loaded!");
	}
}

void BillboardEditor::saveBillboardEntitiesToFile()
{
	if (_isLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		// Create or overwrite billboard file
		std::ofstream file;
		file.open(_fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\billboard.fe3d");

		// Write billboard data into file
		for (auto& billboardName : _billboardNames)
		{
			// Retrieve all values
			auto size = _fe3d.billboardEntity_getSize(billboardName);
			auto color = _fe3d.billboardEntity_getColor(billboardName);
			auto diffusePath = _fe3d.billboardEntity_getDiffuseMapPath(billboardName);
			auto fontPath = _fe3d.billboardEntity_getFontPath(billboardName);
			auto textContent = _fe3d.billboardEntity_getTextContent(billboardName);
			auto isFacingX = _fe3d.billboardEntity_isFacingCameraX(billboardName);
			auto isFacingY = _fe3d.billboardEntity_isFacingCameraY(billboardName);
			auto isTransparent = _fe3d.billboardEntity_isTransparent(billboardName);
			auto isAnimated = _fe3d.billboardEntity_isAnimationPlaying(billboardName);
			auto animationRows = _fe3d.billboardEntity_getAnimationRows(billboardName);
			auto animationColumns = _fe3d.billboardEntity_getAnimationColumns(billboardName);
			auto animationFramestep = _fe3d.billboardEntity_getAnimationFramestep(billboardName);

			// Perform empty string & space conversions
			diffusePath = (diffusePath == "") ? "?" : diffusePath;
			fontPath = (fontPath == "") ? "?" : fontPath;
			textContent = (textContent == "") ? "?" : textContent;
			std::replace(diffusePath.begin(), diffusePath.end(), ' ', '?');
			std::replace(fontPath.begin(), fontPath.end(), ' ', '?');
			std::replace(textContent.begin(), textContent.end(), ' ', '?');

			// Export data
			file <<
				billboardName << " " <<
				size.x << " " <<
				size.y << " " <<
				color.r << " " <<
				color.g << " " <<
				color.b << " " <<
				isFacingX << " " <<
				isFacingY << " " <<
				diffusePath << " " <<
				isTransparent << " " <<
				fontPath << " " <<
				textContent << " " <<
				isAnimated << " " <<
				animationRows << " " <<
				animationColumns << " " <<
				animationFramestep << std::endl;
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Billboard data from project \"" + _currentProjectName + "\" saved!");
	}
}