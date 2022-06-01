#include "animation2d_editor.hpp"
#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <sstream>

using std::istringstream;

const bool Animation2dEditor::loadAnimation2dsFromFile()
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "domain\\animation2d.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `domain\\animation2d.fe3d` does not exist");

		return false;
	}

	string line = "";

	while(getline(file, line))
	{
		string animation2dId;
		int rowCount;
		int columnCount;
		int interval;

		auto iss = istringstream(line);

		iss
			>> animation2dId
			>> rowCount
			>> columnCount
			>> interval;

		_fe3d->animation2d_create(animation2dId);
		_fe3d->animation2d_setRowCount(animation2dId, rowCount);
		_fe3d->animation2d_setColumnCount(animation2dId, columnCount);
		_fe3d->animation2d_setInterval(animation2dId, interval);

		_loadedAnimation2dIds.push_back(animation2dId);

		sort(_loadedAnimation2dIds.begin(), _loadedAnimation2dIds.end());
	}

	file.close();

	Logger::throwInfo("Animation2D editor data loaded");

	return true;
}