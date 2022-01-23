#include "quad3d_editor.hpp"
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
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\quad3d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `quad3d.fe3d` missing!");
		return {};
	}

	vector<string> imagePaths;
	string line;
	while(getline(file, line))
	{
		string quadID;
		string diffuseMapPath;
		string emissionMapPath;
		fvec2 size;
		fvec3 color;
		bool isFacingX;
		bool isFacingY;

		istringstream iss(line);

		iss >>
			quadID >>
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

	_loadedQuadIDs.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\quad3d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `quad3d.fe3d` missing!");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string quadID;
		string diffuseMapPath;
		string emissionMapPath;
		fvec2 size;
		fvec3 color;
		float lightness;
		float textureRepeat;
		float opacity;
		float emissionIntensity;
		bool isFacingX;
		bool isFacingY;
		bool isReflected;
		bool isShadowed;
		bool isBright;

		istringstream iss(line);

		iss >>
			quadID >>
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
			opacity;

		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');

		_fe3d->quad3d_create(quadID, false);

		if(_fe3d->quad3d_isExisting(quadID))
		{
			_loadedQuadIDs.push_back(quadID);

			_fe3d->quad3d_setVisible(quadID, false);
			_fe3d->quad3d_setSize(quadID, size);
			_fe3d->quad3d_setColor(quadID, color);
			_fe3d->quad3d_setLightness(quadID, lightness);
			_fe3d->quad3d_setFacingCameraX(quadID, isFacingX);
			_fe3d->quad3d_setFacingCameraY(quadID, isFacingY);
			_fe3d->quad3d_setShadowed(quadID, isShadowed);
			_fe3d->quad3d_setReflected(quadID, isReflected);
			_fe3d->quad3d_setTextureRepeat(quadID, textureRepeat);
			_fe3d->quad3d_setBright(quadID, isBright);
			_fe3d->quad3d_setOpacity(quadID, opacity);
			_fe3d->quad3d_setEmissionIntensity(quadID, emissionIntensity);

			if(!diffuseMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
				}

				_fe3d->quad3d_setDiffuseMap(quadID, diffuseMapPath);
			}

			if(!emissionMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					emissionMapPath = string("projects\\" + _currentProjectID + "\\" + emissionMapPath);
				}

				_fe3d->quad3d_setEmissionMap(quadID, emissionMapPath);
			}
		}
	}

	file.close();

	Logger::throwInfo("Quad3d editor data loaded!");

	return true;
}