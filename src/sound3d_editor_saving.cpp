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
	const auto filePath = (rootPath + "projects\\" + getCurrentProjectId() + "\\domain\\sound3d.fe3d");

	auto file = ofstream(filePath);

	for(const auto & sound3dId : _loadedSound3dIds)
	{
		const auto maxVolume = _fe3d->sound3d_getMaxVolume(sound3dId);
		const auto maxDistance = _fe3d->sound3d_getMaxDistance(sound3dId);

		auto audioPath = _fe3d->sound3d_getAudioPath(sound3dId);

		if(audioPath.empty())
		{
			audioPath = audioPath.substr(("projects\\" + getCurrentProjectId() + "\\").size());
		}

		audioPath = (audioPath.empty()) ? "?" : audioPath;

		replace(audioPath.begin(), audioPath.end(), ' ', '?');

		file
			<< sound3dId
			<< " "
			<< audioPath
			<< " "
			<< maxVolume
			<< " "
			<< maxDistance
			<< endl;
	}

	file.close();

	Logger::throwInfo("Sound3d editor data saved");

	return true;
}