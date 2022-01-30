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
	if(!Config::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\quad3d.fe3d");

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
		string quadId;
		string diffuseMapPath;
		string emissionMapPath;
		fvec2 size;
		fvec3 color;
		bool isFacingCameraHorizontally;
		bool isFacingCameraVertically;

		istringstream iss(line);

		iss
			>> quadId
			>> size.x
			>> size.y
			>> color.r
			>> color.g
			>> color.b
			>> isFacingCameraHorizontally
			>> isFacingCameraVertically
			>> diffuseMapPath
			>> emissionMapPath;

		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');

		if(!diffuseMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				diffuseMapPath = string("projects\\" + getCurrentProjectId() + "\\" + diffuseMapPath);
			}

			imagePaths.push_back(diffuseMapPath);
		}

		if(!emissionMapPath.empty())
		{
			if(!Config::getInst().isApplicationExported())
			{
				emissionMapPath = string("projects\\" + getCurrentProjectId() + "\\" + emissionMapPath);
			}

			imagePaths.push_back(emissionMapPath);
		}
	}

	file.close();

	return imagePaths;
}

const bool Quad3dEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	_loadedQuadIds.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\quad3d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `quad3d.fe3d` missing!");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string quadId;
		string diffuseMapPath;
		string emissionMapPath;
		fvec2 size;
		fvec3 color;
		float lightness;
		float textureRepeat;
		float opacity;
		float emissionIntensity;
		bool isFacingCameraHorizontally;
		bool isFacingCameraVertically;
		bool isReflected;
		bool isShadowed;
		bool isBright;

		istringstream iss(line);

		iss
			>> quadId
			>> size.x
			>> size.y
			>> color.r
			>> color.g
			>> color.b
			>> isFacingCameraHorizontally
			>> isFacingCameraVertically
			>> diffuseMapPath
			>> emissionMapPath
			>> isReflected
			>> isShadowed
			>> lightness
			>> textureRepeat
			>> isBright
			>> emissionIntensity
			>> opacity;

		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');

		_fe3d->quad3d_create(quadId, false);

		if(_fe3d->quad3d_isExisting(quadId))
		{
			_loadedQuadIds.push_back(quadId);

			_fe3d->quad3d_setVisible(quadId, false);
			_fe3d->quad3d_setSize(quadId, size);
			_fe3d->quad3d_setColor(quadId, color);
			_fe3d->quad3d_setLightness(quadId, lightness);
			_fe3d->quad3d_setFacingCameraHorizontally(quadId, isFacingCameraHorizontally);
			_fe3d->quad3d_setFacingCameraVertically(quadId, isFacingCameraVertically);
			_fe3d->quad3d_setShadowed(quadId, isShadowed);
			_fe3d->quad3d_setReflected(quadId, isReflected);
			_fe3d->quad3d_setTextureRepeat(quadId, textureRepeat);
			_fe3d->quad3d_setBright(quadId, isBright);
			_fe3d->quad3d_setOpacity(quadId, opacity);
			_fe3d->quad3d_setEmissionIntensity(quadId, emissionIntensity);

			if(!diffuseMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					diffuseMapPath = string("projects\\" + getCurrentProjectId() + "\\" + diffuseMapPath);
				}

				_fe3d->quad3d_setDiffuseMap(quadId, diffuseMapPath);
			}

			if(!emissionMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					emissionMapPath = string("projects\\" + getCurrentProjectId() + "\\" + emissionMapPath);
				}

				_fe3d->quad3d_setEmissionMap(quadId, emissionMapPath);
			}
		}
	}

	file.close();

	Logger::throwInfo("Quad3d editor data loaded!");

	return true;
}