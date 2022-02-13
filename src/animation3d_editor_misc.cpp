#include "animation3d_editor.hpp"
#include "logger.hpp"

void Animation3dEditor::inject(shared_ptr<ModelEditor> modelEditor)
{
	_modelEditor = modelEditor;
}

const vector<string> Animation3dEditor::getLoadedAnimationIds() const
{
	return _loadedAnimationIds;
}