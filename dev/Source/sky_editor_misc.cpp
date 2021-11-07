#include "sky_editor.hpp"

#include <algorithm>

void SkyEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool SkyEditor::isLoaded() const
{
	return _isEditorLoaded;
}

void SkyEditor::unloadSkyEntities()
{
	for(const auto& ID : _loadedSkyIDs)
	{
		if(_fe3d.skyEntity_isExisting(ID))
		{
			_fe3d.skyEntity_delete(ID);
		}
	}
}

const vector<string>& SkyEditor::getLoadedSkyIDs()
{
	sort(_loadedSkyIDs.begin(), _loadedSkyIDs.end());
	return _loadedSkyIDs;
}