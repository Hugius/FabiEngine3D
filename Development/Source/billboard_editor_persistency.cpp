#include "billboard_editor.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

void BillboardEditor::loadBillboards()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	// Create or overwrite billboards file
	std::ifstream file(_fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\billboard.fe3d");
	string line;

	// Read model data
	while (std::getline(file, line))
	{
		// Placeholder variables
		string name, diffusePath, fontPath, textContent;
		vec2 size;
		vec3 color;
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
			_fe3d.billBoardEntity_add(name, diffusePath, _billboardPosition, vec3(0.0f), size, transparent, facingX, facingY, false, false);
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
			_fe3d.billBoardEntity_add(name, textContent, fontPath, color, _billboardPosition, vec3(0.0f), size, facingX, facingY, false);
		}
		else // Colored billboard
		{
			_fe3d.billBoardEntity_add(name, color, _billboardPosition, vec3(0.0f), size, facingX, facingY, false);
		}
	}

	// Close file
	file.close();

	// Logging
	_fe3d.logger_throwInfo("Billboard editor data from project \"" + _currentProjectName + "\" loaded!");
}

void BillboardEditor::save()
{
	if (_isLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		// Create or overwrite billboards file
		std::ofstream file;
		file.open(_fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\billboard.fe3d");

		// Write billboard data into file
		for (auto& billboardName : _billboardNames)
		{
			// Perform empty string & space conversions
			string diffusePath = _fe3d.billboardEntity_getDiffuseMapPath(billboardName);
			string fontPath = _fe3d.billboardEntity_getFontPath(billboardName);
			string textContent = _fe3d.billboardEntity_getTextContent(billboardName);
			diffusePath = (diffusePath == "") ? "?" : diffusePath;
			fontPath = (fontPath == "") ? "?" : fontPath;
			textContent = (textContent == "") ? "?" : textContent;
			std::replace(diffusePath.begin(), diffusePath.end(), ' ', '?');
			std::replace(fontPath.begin(), fontPath.end(), ' ', '?');
			std::replace(textContent.begin(), textContent.end(), ' ', '?');

			// Export data
			file << billboardName << " " <<
				_fe3d.billboardEntity_getSize(billboardName).x << " " <<
				_fe3d.billboardEntity_getSize(billboardName).y << " " <<
				_fe3d.billboardEntity_getColor(billboardName).r << " " <<
				_fe3d.billboardEntity_getColor(billboardName).g << " " <<
				_fe3d.billboardEntity_getColor(billboardName).b << " " <<
				_fe3d.billboardEntity_isFacingCameraX(billboardName) << " " <<
				_fe3d.billboardEntity_isFacingCameraY(billboardName) << " " <<
				diffusePath << " " <<
				_fe3d.billboardEntity_isTransparent(billboardName) << " " <<
				fontPath << " " <<
				textContent << " " <<
				_fe3d.billboardEntity_isAnimationPlaying(billboardName) << " " <<
				_fe3d.billboardEntity_getAnimationRows(billboardName) << " " <<
				_fe3d.billboardEntity_getAnimationColumns(billboardName) << " " <<
				_fe3d.billboardEntity_getAnimationFramestep(billboardName) << std::endl;
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Billboard editor data from project \"" + _currentProjectName + "\" saved!");
	}
}