#include "animation2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool Animation2dEditor::saveToFile() const
{
	if(!_isEditorLoaded)
	{
		return false;
	}

	if(_currentProjectID.empty())
	{
		Logger::throwError("Animation2dEditor::saveToFile");
	}

	ofstream file(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\data\\animation2d.fe3d");

	for(const auto& animation : _animations)
	{
		// Data to save
		auto animationID = animation->getID();
		auto previewTexturePath = animation->getPreviewTexturePath();
		auto rowCount = animation->getRowCount();
		auto columnCount = animation->getColumnCount();
		auto framestep = animation->getFramestep();

		// Only if animation has data
		if(!previewTexturePath.empty())
		{
			// Convert to short path
			previewTexturePath = string(previewTexturePath.empty() ? "" : previewTexturePath.substr(string("projects\\" + _currentProjectID + "\\").size()));

			// Convert empty string
			previewTexturePath = (previewTexturePath.empty()) ? "?" : previewTexturePath;

			// Convert spaces
			replace(previewTexturePath.begin(), previewTexturePath.end(), ' ', '?');

			// Write data to file
			file <<
				animationID << " " <<
				previewTexturePath << " " <<
				rowCount << " " <<
				columnCount << " " <<
				framestep << endl;
		}
	}

	file.close();

	Logger::throwInfo("Animation2D data saved!");

	return true;
}