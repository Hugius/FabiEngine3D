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
		string quad3dID, diffuseMapPath, emissionMapPath;
		fvec2 size;
		fvec3 color;
		bool isFacingX, isFacingY;

		istringstream iss(line);

		iss >>
			quad3dID >>
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

	_loadedQuad3dIDs.clear();

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
		string quad3dID, diffuseMapPath, emissionMapPath;
		fvec2 size;
		fvec3 color;
		float lightness, textureRepeat, transparency, emissionIntensity;
		bool isFacingX, isFacingY, isReflected, isShadowed, isBright;

		istringstream iss(line);

		iss >>
			quad3dID >>
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

		_fe3d->quad3d_create(quad3dID, false);

		if(_fe3d->quad3d_isExisting(quad3dID))
		{
			_loadedQuad3dIDs.push_back(quad3dID);

			_fe3d->quad3d_setVisible(quad3dID, false);
			_fe3d->quad3d_setSize(quad3dID, size);
			_fe3d->quad3d_setColor(quad3dID, color);
			_fe3d->quad3d_setLightness(quad3dID, lightness);
			_fe3d->quad3d_setFacingCameraX(quad3dID, isFacingX);
			_fe3d->quad3d_setFacingCameraY(quad3dID, isFacingY);
			_fe3d->quad3d_setShadowed(quad3dID, isShadowed);
			_fe3d->quad3d_setReflected(quad3dID, isReflected);
			_fe3d->quad3d_setTextureRepeat(quad3dID, textureRepeat);
			_fe3d->quad3d_setBright(quad3dID, isBright);
			_fe3d->quad3d_setTransparency(quad3dID, transparency);
			_fe3d->quad3d_setEmissionIntensity(quad3dID, emissionIntensity);

			if(!diffuseMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
				}

				_fe3d->quad3d_setDiffuseMap(quad3dID, diffuseMapPath);
			}

			if(!emissionMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					emissionMapPath = string("projects\\" + _currentProjectID + "\\" + emissionMapPath);
				}

				_fe3d->quad3d_setEmissionMap(quad3dID, emissionMapPath);
			}
		}
	}

	file.close();

	Logger::throwInfo("Billboard editor data loaded!");

	return true;
}