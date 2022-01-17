#include "quad2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool QuadEditor::saveToFile() const
{
	if(!_isEditorLoaded)
	{
		return false;
	}

	if(_currentProjectID.empty())
	{
		Logger::throwError("QuadEditor::saveToFile");
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + _currentProjectID + "\\data\\quad.fe3d");

	for(const auto& quadID : _loadedQuadIDs)
	{
		auto diffuseMapPath = _fe3d->quad_getDiffuseMapPath(quadID);
		auto color = _fe3d->quad_getColor(quadID);
		auto transparency = _fe3d->quad_getTransparency(quadID);

		diffuseMapPath = string(diffuseMapPath.empty() ? "" : diffuseMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');

		file << quadID << " " << diffuseMapPath << " " << color.r << " " << color.g << " " << color.b << " " << transparency << endl;
	}

	file.close();

	Logger::throwInfo("Quad editor data saved!");

	return true;
}