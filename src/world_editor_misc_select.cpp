#include "world_editor.hpp"

void WorldEditor::_selectModel(const string & modelId)
{
	_selectedModelId = modelId;

	if(!_isAabbModeEnabled)
	{
		for(const auto & childAabbId : _fe3d->model_getChildAabbIds(_selectedModelId))
		{
			_fe3d->aabb_setVisible(childAabbId, true);
		}
	}

	_gui->getOverlay()->getTextField(SELECTED_TITLE_ID)->setTextContent("Selected Model: " + _selectedModelId);
}

void WorldEditor::_selectQuad3d(const string & quad3dId)
{
	_selectedQuad3dId = quad3dId;

	if(!_isAabbModeEnabled)
	{
		for(const auto & childAabbId : _fe3d->quad3d_getChildAabbIds(_selectedQuad3dId))
		{
			_fe3d->aabb_setVisible(childAabbId, true);
		}
	}

	_gui->getOverlay()->getTextField(SELECTED_TITLE_ID)->setTextContent("Selected Quad3D: " + _selectedQuad3dId);
}

void WorldEditor::_selectText3d(const string & text3dId)
{
	_selectedText3dId = text3dId;

	if(!_isAabbModeEnabled)
	{
		for(const auto & childAabbId : _fe3d->text3d_getChildAabbIds(_selectedText3dId))
		{
			_fe3d->aabb_setVisible(childAabbId, true);
		}
	}

	_gui->getOverlay()->getTextField(SELECTED_TITLE_ID)->setTextContent("Selected Text3D: " + _selectedText3dId);
}

void WorldEditor::_selectAabb(const string & aabbId)
{
	_selectedAabbId = aabbId;

	_gui->getOverlay()->getTextField(SELECTED_TITLE_ID)->setTextContent("Selected AABB: " + _selectedAabbId);
}

void WorldEditor::_selectPointlight(const string & pointlightId)
{
	_selectedPointlightId = pointlightId;

	if(!_isAabbModeEnabled)
	{
		_fe3d->aabb_setVisible(("@@lamp_" + pointlightId), true);
	}

	_gui->getOverlay()->getTextField(SELECTED_TITLE_ID)->setTextContent("Selected Pointlight: " + _selectedPointlightId);
}

void WorldEditor::_selectSpotlight(const string & spotlightId)
{
	_selectedSpotlightId = spotlightId;

	if(!_isAabbModeEnabled)
	{
		_fe3d->aabb_setVisible(("@@torch_" + spotlightId), true);
	}

	_gui->getOverlay()->getTextField(SELECTED_TITLE_ID)->setTextContent("Selected Spotlight: " + _selectedSpotlightId);
}

void WorldEditor::_selectCaptor(const string & captorId)
{
	_selectedCaptorId = captorId;

	if(!_isAabbModeEnabled)
	{
		_fe3d->aabb_setVisible(("@@lens_" + captorId), true);
	}

	_gui->getOverlay()->getTextField(SELECTED_TITLE_ID)->setTextContent("Selected Captor: " + _selectedCaptorId);
}

void WorldEditor::_selectSound3d(const string & sound3dId)
{
	_selectedSound3dId = sound3dId;

	if(!_isAabbModeEnabled)
	{
		_fe3d->aabb_setVisible(("@@speaker_" + sound3dId), true);
	}

	_gui->getOverlay()->getTextField(SELECTED_TITLE_ID)->setTextContent("Selected Sound3D: " + _selectedSound3dId);
}

void WorldEditor::_deselectModel(const string & modelId)
{
	if(!_isAabbModeEnabled)
	{
		for(const auto & childAabbId : _fe3d->model_getChildAabbIds(modelId))
		{
			_fe3d->aabb_setVisible(childAabbId, false);
		}
	}
}

void WorldEditor::_deselectQuad3d(const string & quad3dId)
{
	if(!_isAabbModeEnabled)
	{
		for(const auto & childAabbId : _fe3d->quad3d_getChildAabbIds(quad3dId))
		{
			_fe3d->aabb_setVisible(childAabbId, false);
		}
	}
}

void WorldEditor::_deselectText3d(const string & text3dId)
{
	if(!_isAabbModeEnabled)
	{
		for(const auto & childAabbId : _fe3d->text3d_getChildAabbIds(text3dId))
		{
			_fe3d->aabb_setVisible(childAabbId, false);
		}
	}
}

void WorldEditor::_deselectAabb(const string & aabbId)
{

}

void WorldEditor::_deselectPointlight(const string & pointlightId)
{
	if(!_isAabbModeEnabled)
	{
		_fe3d->aabb_setVisible(("@@lamp_" + pointlightId), false);
	}
}

void WorldEditor::_deselectSpotlight(const string & spotlightId)
{
	if(!_isAabbModeEnabled)
	{
		_fe3d->aabb_setVisible(("@@torch_" + spotlightId), false);
	}
}

void WorldEditor::_deselectCaptor(const string & captorId)
{
	if(!_isAabbModeEnabled)
	{
		_fe3d->aabb_setVisible(("@@lens_" + captorId), false);
	}
}

void WorldEditor::_deselectSound3d(const string & sound3dId)
{
	if(!_isAabbModeEnabled)
	{
		_fe3d->aabb_setVisible(("@@speaker_" + sound3dId), false);
	}
}