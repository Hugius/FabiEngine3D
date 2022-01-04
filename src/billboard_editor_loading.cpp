#include "billboard_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> BillboardEditor::getImagePathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("BillboardEditor::getImagePathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\billboard.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `billboard.fe3d` missing!");
		return {};
	}

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

const bool BillboardEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("BillboardEditor::loadFromFile");
	}

	_loadedBillboardIDs.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\billboard.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `billboard.fe3d` missing!");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string billboardID, diffuseMapPath, emissionMapPath, fontMapPath, textContent;
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
			fontMapPath >>
			textContent >>
			lightness >>
			textureRepeat;

		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;
		fontMapPath = (fontMapPath == "?") ? "" : fontMapPath;
		textContent = (textContent == "?") ? "" : textContent;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');
		replace(fontMapPath.begin(), fontMapPath.end(), '?', ' ');
		replace(textContent.begin(), textContent.end(), '?', ' ');

		_fe3d.billboard_create(billboardID, false);

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

			if(!fontMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					fontMapPath = string("projects\\" + _currentProjectID + "\\" + fontMapPath);
				}

				_fe3d.billboard_setFont(billboardID, fontMapPath);
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