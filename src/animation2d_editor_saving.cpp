#include "animation2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool Animation2dEditor::saveToFile() const
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
	auto file = ofstream(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\animation2d.fe3d");

	for(const auto& animationId : _loadedAnimationIds)
	{
		auto rowCount = _fe3d->animation2d_getRowCount(animationId);
		auto columnCount = _fe3d->animation2d_getColumnCount(animationId);
		auto interval = _fe3d->animation2d_getInterval(animationId);

		file
			<< animationId
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