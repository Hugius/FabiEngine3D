#include "sound3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const bool Sound3dEditor::loadSound3dsFromFile()
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\sound3d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `sound3d.fe3d` does not exist");

		return false;
	}

	string line;
	while(getline(file, line))
	{
		string sound3dId;
		fvec3 radius;
		fvec3 color;
		float intensity;
		int shape;

		istringstream iss(line);

		iss
			>> sound3dId
			>> radius.x
			>> radius.y
			>> radius.z
			>> color.r
			>> color.g
			>> color.b
			>> intensity
			>> shape;

		_loadedSound3dIds.push_back(sound3dId);
		sort(_loadedSound3dIds.begin(), _loadedSound3dIds.end());

		_fe3d->sound3d_create(sound3dId);
		_fe3d->sound3d_setVisible(sound3dId, false);
		_fe3d->sound3d_setPosition(sound3dId, SOUND3D_POSITION);
		_fe3d->sound3d_setRadius(sound3dId, radius);
		_fe3d->sound3d_setColor(sound3dId, color);
		_fe3d->sound3d_setIntensity(sound3dId, intensity);
		_fe3d->sound3d_setShape(sound3dId, Sound3dShapeType(shape));
	}

	file.close();

	Logger::throwInfo("Sound3d editor data loaded");

	return true;
}