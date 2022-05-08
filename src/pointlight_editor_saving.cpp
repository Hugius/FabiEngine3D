#include "pointlight_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool PointlightEditor::savePointlightsToFile() const
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
	auto file = ofstream(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\pointlight.fe3d");

	for(const auto & pointlightId : _loadedPointlightIds)
	{
		auto size = _fe3d->pointlight_getBaseSize(pointlightId);
		auto color = _fe3d->pointlight_getColor(pointlightId);

		file
			<< pointlightId
			<< " "
			<< size.x
			<< " "
			<< size.y
			<< " "
			<< size.z
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< endl;
	}

	file.close();

	Logger::throwInfo("Pointlight editor data saved");

	return true;
}