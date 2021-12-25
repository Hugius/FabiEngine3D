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
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("BillboardEditor::getTexturePathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\billboard.fe3d");

	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `billboard.fe3d` missing!");
		return {};
	}

	ifstream file(filePath);

	vector<string> texturePaths;
	string line;
	while(getline(file, line))
	{
		string billboardID, diffuseMapPath, emissionMapPath;
		fvec2 size;
		fvec3 color;
		bool facingX, facingY;

		istringstream iss(line);

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

		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');

		if(!diffuseMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
			}

			texturePaths.push_back(diffuseMapPath);
		}

		if(!emissionMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				emissionMapPath = string("projects\\" + _currentProjectID + "\\" + emissionMapPath);
			}

			texturePaths.push_back(emissionMapPath);
		}
	}

	file.close();

	return texturePaths;
}

const vector<string> BillboardEditor::getFontPathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("BillboardEditor::getFontPathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\billboard.fe3d");

	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `billboard.fe3d` missing!");
		return {};
	}

	ifstream file(filePath);

	vector<string> fontPaths;
	string line;
	while(getline(file, line))
	{
		string billboardID, diffuseMapPath, fontPath;
		fvec2 size;
		fvec3 color;
		bool facingX, facingY, isReflected, isShadowed;

		istringstream iss(line);

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

		fontPath = (fontPath == "?") ? "" : fontPath;

		replace(fontPath.begin(), fontPath.end(), '?', ' ');

		if(!fontPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				fontPath = string("projects\\" + _currentProjectID + "\\" + fontPath);
			}

			fontPaths.push_back(fontPath);
		}
	}

	file.close();

	return fontPaths;
}

const bool BillboardEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("BillboardEditor::loadFromFile");
	}

	_loadedBillboardIDs.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\billboard.fe3d");

	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `billboard.fe3d` missing!");
		return false;
	}

	ifstream file(filePath);

	string line;
	while(getline(file, line))
	{
		string billboardID, diffuseMapPath, emissionMapPath, fontPath, textContent;
		fvec2 size;
		fvec3 color;
		float lightness, textureRepeat;
		bool isFacingX, isFacingY, isReflected, isShadowed;

		istringstream iss(line);

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

		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;
		fontPath = (fontPath == "?") ? "" : fontPath;
		textContent = (textContent == "?") ? "" : textContent;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');
		replace(fontPath.begin(), fontPath.end(), '?', ' ');
		replace(textContent.begin(), textContent.end(), '?', ' ');

		_fe3d.billboard_create(billboardID);

		if(_fe3d.billboard_isExisting(billboardID))
		{
			_loadedBillboardIDs.push_back(billboardID);

			if(!diffuseMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
				}

				_fe3d.billboard_setDiffuseMap(billboardID, diffuseMapPath);
			}

			if(!emissionMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					emissionMapPath = string("projects\\" + _currentProjectID + "\\" + emissionMapPath);
				}

				_fe3d.billboard_setEmissionMap(billboardID, emissionMapPath);
			}

			if(!fontPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					fontPath = string("projects\\" + _currentProjectID + "\\" + fontPath);
				}

				_fe3d.billboard_setFont(billboardID, fontPath);
				_fe3d.billboard_setTextContent(billboardID, textContent);
			}

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

	file.close();

	Logger::throwInfo("Billboard data loaded!");

	return true;
}