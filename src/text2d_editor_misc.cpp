#include "text2d_editor.hpp"

#include <algorithm>

const vector<string> & Text2dEditor::getLoadedEntityIds() const
{
	return _loadedText2dIds;
}

void Text2dEditor::deleteLoadedText2ds()
{
	for(const auto & text2dId : _loadedText2dIds)
	{
		_fe3d->text2d_delete(text2dId);
	}

	_loadedText2dIds.clear();
}