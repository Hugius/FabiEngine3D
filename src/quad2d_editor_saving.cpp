#include "quad2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool Quad2dEditor::saveToFile() const
{
	if(!_isEditorLoaded)
	{
		return false;
	}

	if(_currentProjectID.empty())
	{
		Logger::throwError("Quad2dEditor::saveToFile");
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + _currentProjectID + "\\data\\quad2d.fe3d");

	for(const auto& quadID : _loadedQuadIDs)
	{
		auto diffuseMapPath = _fe3d->quad2d_getDiffuseMapPath(quadID);
		auto color = _fe3d->quad2d_getColor(quadID);
		auto opacity = _fe3d->quad2d_getOpacity(quadID);

		diffuseMapPath = string(diffuseMapPath.empty() ? "" : diffuseMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');

		file << quadID << " " << diffuseMapPath << " " << color.r << " " << color.g << " " << color.b << " " << opacity << endl;
	}

	file.close();

	Logger::throwInfo("Quad2D editor data saved!");

	return true;
}