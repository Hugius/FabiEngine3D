#include "animation3d_editor.hpp"

void Animation3dEditor::inject(shared_ptr<ModelEditor> modelEditor)
{
	_modelEditor = modelEditor;
}

const vector<string> & Animation3dEditor::getLoadedAnimationIds() const
{
	return _loadedAnimation3dIds;
}

void Animation3dEditor::deleteLoadedAnimations()
{
	for(const auto & id : _loadedAnimation3dIds)
	{
		_fe3d->animation3d_delete(id);
	}

	_loadedAnimation3dIds.clear();
}