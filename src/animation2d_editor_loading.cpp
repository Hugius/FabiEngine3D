#include "animation2d_editor.hpp"
#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <sstream>

using std::istringstream;

const bool Animation2dEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\animation2d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `animation2d.fe3d` does not exist");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string animationId;
		unsigned int rowCount;
		unsigned int columnCount;
		unsigned int interval;

		istringstream iss(line);

		iss
			>> animationId
			>> rowCount
			>> columnCount
			>> interval;

		_loadedAnimationIds.push_back(animationId);
		sort(_loadedAnimationIds.begin(), _loadedAnimationIds.end());

		_fe3d->animation2d_create(animationId);
		_fe3d->animation2d_setRowCount(animationId, rowCount);
		_fe3d->animation2d_setColumnCount(animationId, columnCount);
		_fe3d->animation2d_setInterval(animationId, interval);
	}

	file.close();

	Logger::throwInfo("Animation2D editor data loaded");

	return true;
}