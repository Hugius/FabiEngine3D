#include "quad2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool Quad2dEditor::saveToFile() const
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
	auto file = ofstream(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\quad2d.fe3d");

	for(const auto& quadId : _loadedEntityIds)
	{
		auto diffuseMapPath = _fe3d->quad2d_getDiffuseMapPath(quadId);
		auto color = _fe3d->quad2d_getColor(quadId);
		auto opacity = _fe3d->quad2d_getOpacity(quadId);

		diffuseMapPath = (diffuseMapPath.empty() ? "" : diffuseMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));

		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');

		file
			<< quadId
			<< " "
			<< diffuseMapPath
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< opacity
			<< endl;
	}

	file.close();

	Logger::throwInfo("Quad2D editor data saved");

	return true;
}