#include "animation3d_editor.hpp"

void Animation3dEditor::inject(shared_ptr<ModelEditor> modelEditor)
{
	_modelEditor = modelEditor;
}

const vector<string> & Animation3dEditor::getLoadedAnimationIds() const
{
	return _loadedAnimation3dIds;
}

void Animation3dEditor::deleteLoadedAnimation3ds()
{
	for(const auto & animation3dId : _loadedAnimation3dIds)
	{
		_fe3d->animation3d_delete(animation3dId);
	}

	_loadedAnimation3dIds.clear();
}