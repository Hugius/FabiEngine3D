#include "animation2d_editor.hpp"
#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <sstream>

using std::istringstream;

const bool Animation2dEditor::loadAnimationsFromFile()
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
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
		int rowCount;
		int columnCount;
		int interval;

		istringstream iss(line);

		iss
			>> animationId
			>> rowCount
			>> columnCount
			>> interval;

		_loadedAnimation2dIds.push_back(animationId);
		sort(_loadedAnimation2dIds.begin(), _loadedAnimation2dIds.end());

		_fe3d->animation2d_create(animationId);
		_fe3d->animation2d_setRowCount(animationId, rowCount);
		_fe3d->animation2d_setColumnCount(animationId, columnCount);
		_fe3d->animation2d_setInterval(animationId, interval);
	}

	file.close();

	Logger::throwInfo("Animation2D editor data loaded");

	return true;
}