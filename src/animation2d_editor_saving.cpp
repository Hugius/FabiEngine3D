#include "animation2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool Animation2dEditor::saveAnimation2dsToFile() const
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
	const auto filePath = (rootPath + "projects\\" + getCurrentProjectId() + "\\data\\animation2d.fe3d");

	auto file = ofstream(filePath);

	for(const auto & animation2dId : _loadedAnimation2dIds)
	{
		const auto rowCount = _fe3d->animation2d_getRowCount(animation2dId);
		const auto columnCount = _fe3d->animation2d_getColumnCount(animation2dId);
		const auto interval = _fe3d->animation2d_getInterval(animation2dId);

		file
			<< animation2dId
			<< " "
			<< rowCount
			<< " "
			<< columnCount
			<< " "
			<< interval << endl;
	}

	file.close();

	Logger::throwInfo("Animation2D editor data saved");

	return true;
}