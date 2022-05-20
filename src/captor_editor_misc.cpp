#include "captor_editor.hpp"

#include <algorithm>

const vector<string> & CaptorEditor::getLoadedCaptorIds() const
{
	return _loadedCaptorIds;
}

void CaptorEditor::deleteLoadedCaptors()
{
	for(const auto & captorId : _loadedCaptorIds)
	{
		_fe3d->captor_delete(captorId);
	}

	_loadedCaptorIds.clear();
}