#include "sound2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool Sound2dEditor::saveSound2dsToFile() const
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
	const auto filePath = (rootPath + "projects\\" + getCurrentProjectId() + "\\domain\\sound2d.fe3d");

	auto file = ofstream(filePath);

	for(const auto & sound2dId : _loadedSound2dIds)
	{
		auto audioPath = _fe3d->sound2d_getAudioPath(sound2dId);

		if(!audioPath.empty())
		{
			audioPath = audioPath.substr(("projects\\" + getCurrentProjectId() + "\\").size());
		}

		audioPath = (audioPath.empty()) ? "?" : audioPath;

		replace(audioPath.begin(), audioPath.end(), ' ', '?');

		file
			<< sound2dId
			<< " "
			<< audioPath
			<< endl;
	}

	file.close();

	Logger::throwInfo("Sound2D editor data saved");

	return true;
}