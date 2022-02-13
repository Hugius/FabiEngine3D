#include "animation3d_editor.hpp"
#include "logger.hpp"

void Animation3dEditor::inject(shared_ptr<ModelEditor> modelEditor)
{
	_modelEditor = modelEditor;
}

const bool Animation3dEditor::_comparePartIds(vector<string> first, vector<string> second) const
{
	if(first.size() != second.size())
	{
		return false;
	}

	for(size_t i = 0; i < first.size(); i++)
	{
		if(first[i] != second[i])
		{
			return false;
		}
	}

	return true;
}

const vector<string> Animation3dEditor::getLoadedAnimationIds() const
{
	return _loadedAnimationIds;
}