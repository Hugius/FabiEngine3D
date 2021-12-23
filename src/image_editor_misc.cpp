#include "image_editor.hpp"

#include <algorithm>

void ImageEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool ImageEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& ImageEditor::getLoadedIDs()
{
	sort(_loadedImageIDs.begin(), _loadedImageIDs.end());
	return _loadedImageIDs;
}