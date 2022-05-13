#include "sound3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool Sound3dEditor::saveSound3dsToFile() const
{
	if(!isLoaded())
	{
		return false;
	}

	if(getCurrentProjectId().empty())
	{
		abort();
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	auto file = ofstream(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\sound3d.fe3d");

	for(const auto & sound3dId : _loadedSound3dIds)
	{
		auto radius = _fe3d->sound3d_getRadius(sound3dId);
		auto color = _fe3d->sound3d_getColor(sound3dId);
		auto intensity = _fe3d->sound3d_getIntensity(sound3dId);
		auto shape = static_cast<int>(_fe3d->sound3d_getShape(sound3dId));

		file
			<< sound3dId
			<< " "
			<< radius.x
			<< " "
			<< radius.y
			<< " "
			<< radius.z
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< intensity
			<< " "
			<< shape
			<< endl;
	}

	file.close();

	Logger::throwInfo("Sound3d editor data saved");

	return true;
}