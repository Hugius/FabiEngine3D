#include "sound_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool SoundEditor::saveToFile() const
{
	if(!isLoaded())
	{
		return false;
	}

	if(getCurrentProjectId().empty())
	{
		Logger::throwError("SoundEditor::saveToFile");
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\sound.fe3d");

	for(const auto& soundId : _loadedSoundIds)
	{
		auto audioPath = _fe3d->sound2d_getAudioPath(soundId);

		audioPath = string(audioPath.empty() ? "" : audioPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));

		audioPath = (audioPath.empty()) ? "?" : audioPath;

		replace(audioPath.begin(), audioPath.end(), ' ', '?');

		file << soundId << " " << audioPath << endl;
	}

	file.close();

	Logger::throwInfo("Sound editor data saved!");

	return true;
}