#include "billboard_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> Quad3dEditor::getImagePathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("Quad3dEditor::getImagePathsFromFile");
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

	vector<string> imagePaths;
	string line;
	while(getline(file, line))
	{
		string billboardID, diffuseMapPath, emissionMapPath;
		fvec2 size;
		fvec3 color;
		bool isFacingX, isFacingY;

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

			imagePaths.push_back(diffuseMapPath);
		}

		if(!emissionMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				emissionMapPath = string("projects\\" + _currentProjectID + "\\" + emissionMapPath);
			}

			imagePaths.push_back(emissionMapPath);
		}
	}

	file.close();

	return imagePaths;
}

const bool Quad3dEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("Quad3dEditor::loadFromFile");
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
		string billboardID, diffuseMapPath, emissionMapPath;
		fvec2 size;
		fvec3 color;
		float lightness, textureRepeat, transparency, emissionIntensity;
		bool isFacingX, isFacingY, isReflected, isShadowed, isBright;

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
			lightness >>
			textureRepeat >>
			isBright >>
			emissionIntensity >>
			transparency;

		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');

		_fe3d->billboard_create(billboardID, false);

		if(_fe3d->billboard_isExisting(billboardID))
		{
			_loadedBillboardIDs.push_back(billboardID);

			_fe3d->billboard_setVisible(billboardID, false);
			_fe3d->billboard_setSize(billboardID, size);
			_fe3d->billboard_setColor(billboardID, color);
			_fe3d->billboard_setLightness(billboardID, lightness);
			_fe3d->billboard_setFacingCameraX(billboardID, isFacingX);
			_fe3d->billboard_setFacingCameraY(billboardID, isFacingY);
			_fe3d->billboard_setShadowed(billboardID, isShadowed);
			_fe3d->billboard_setReflected(billboardID, isReflected);
			_fe3d->billboard_setTextureRepeat(billboardID, textureRepeat);
			_fe3d->billboard_setBright(billboardID, isBright);
			_fe3d->billboard_setTransparency(billboardID, transparency);
			_fe3d->billboard_setEmissionIntensity(billboardID, emissionIntensity);

			if(!diffuseMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
				}

				_fe3d->billboard_setDiffuseMap(billboardID, diffuseMapPath);
			}

			if(!emissionMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					emissionMapPath = string("projects\\" + _currentProjectID + "\\" + emissionMapPath);
				}

				_fe3d->billboard_setEmissionMap(billboardID, emissionMapPath);
			}
		}
	}

	file.close();

	Logger::throwInfo("Billboard editor data loaded!");

	return true;
}