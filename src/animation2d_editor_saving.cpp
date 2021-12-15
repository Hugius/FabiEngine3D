#include "animation2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool Animation2dEditor::saveToFile() const
{
	// Editor must be loaded
	if(!_isEditorLoaded)
	{
		return false;
	}

	// Validate project ID
	if(_currentProjectID.empty())
	{
		Logger::throwError("Animation2dEditor::saveToFile");
	}

	// Create or overwrite file
	ofstream file(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\data\\animation2d.fe3d");

	// Write animation data
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

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Animation2D data saved!");

	// Return
	return true;
}