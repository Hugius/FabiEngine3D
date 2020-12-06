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
	_billboardIDs.clear();

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
			string billboardID, diffusePath, fontPath, textContent;
			Vec2 size;
			Vec3 color;
			bool facingX, facingY, transparent, playing;
			int rows, columns, framestep;

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
			_billboardIDs.push_back(billboardID);

			// Determine billboard type
			if (diffusePath != "") // Textured billboard
			{
				_fe3d.billBoardEntity_add(billboardID, diffusePath, _billboardPosition, Vec3(0.0f), size, transparent, facingX, facingY, false, false);
				_fe3d.billboardEntity_setColor(billboardID, color);

				// Playing sprite animation
				if (playing)
				{
					_fe3d.billboardEntity_setAnimationFramestep(billboardID, framestep);
					_fe3d.billboardEntity_setAnimationRows(billboardID, rows);
					_fe3d.billboardEntity_setAnimationColumns(billboardID, columns);
					_fe3d.billBoardEntity_playSpriteAnimation(billboardID, -1);
				}
			}
			else if (fontPath != "") // Text billboard
			{
				_fe3d.billBoardEntity_add(billboardID, textContent, fontPath, color, _billboardPosition, Vec3(0.0f), size, facingX, facingY, false);
			}
			else // Colored billboard
			{
				_fe3d.billBoardEntity_add(billboardID, color, _billboardPosition, Vec3(0.0f), size, facingX, facingY, false);
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
		for (auto& billboardID : _billboardIDs)
		{
			// Retrieve all values
			auto size = _fe3d.billboardEntity_getSize(billboardID);
			auto color = _fe3d.billboardEntity_getColor(billboardID);
			auto diffusePath = _fe3d.billboardEntity_getDiffuseMapPath(billboardID);
			auto fontPath = _fe3d.billboardEntity_getFontPath(billboardID);
			auto textContent = _fe3d.billboardEntity_getTextContent(billboardID);
			auto isFacingX = _fe3d.billboardEntity_isFacingCameraX(billboardID);
			auto isFacingY = _fe3d.billboardEntity_isFacingCameraY(billboardID);
			auto isTransparent = _fe3d.billboardEntity_isTransparent(billboardID);
			auto isAnimated = _fe3d.billboardEntity_isAnimationPlaying(billboardID);
			auto animationRows = _fe3d.billboardEntity_getAnimationRows(billboardID);
			auto animationColumns = _fe3d.billboardEntity_getAnimationColumns(billboardID);
			auto animationFramestep = _fe3d.billboardEntity_getAnimationFramestep(billboardID);

			// Perform empty string & space conversions
			diffusePath = (diffusePath == "") ? "?" : diffusePath;
			fontPath = (fontPath == "") ? "?" : fontPath;
			textContent = (textContent == "") ? "?" : textContent;
			std::replace(diffusePath.begin(), diffusePath.end(), ' ', '?');
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