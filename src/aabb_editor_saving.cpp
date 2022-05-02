#include "aabb_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool AabbEditor::saveAabbsToFile() const
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
	auto file = ofstream(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\aabb.fe3d");

	for(const auto & aabbId : _loadedAabbIds)
	{
		auto size = _fe3d->aabb_getBaseSize(aabbId);

		file
			<< aabbId
			<< " "
			<< size.x
			<< " "
			<< size.y
			<< " "
			<< size.z
			<< endl;
	}

	file.close();

	Logger::throwInfo("AABB editor data saved");

	return true;
}