#include "world_editor.hpp"

void WorldEditor::_selectModel(const string & modelId)
{
	_selectedModelId = modelId;

	_gui->getOverlay()->getTextField(SELECTED_TITLE_ID)->setTextContent("Selected Model: " + _selectedModelId);
}

void WorldEditor::_selectQuad3d(const string & quad3dId)
{
	_selectedQuad3dId = quad3dId;

	_gui->getOverlay()->getTextField(SELECTED_TITLE_ID)->setTextContent("Selected Quad3D: " + _selectedQuad3dId);
}

void WorldEditor::_selectText3d(const string & text3dId)
{
	_selectedText3dId = text3dId;

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

	_gui->getOverlay()->getTextField(SELECTED_TITLE_ID)->setTextContent("Selected Pointlight: " + _selectedPointlightId);
}

void WorldEditor::_selectSpotlight(const string & spotlightId)
{
	_selectedSpotlightId = spotlightId;

	_gui->getOverlay()->getTextField(SELECTED_TITLE_ID)->setTextContent("Selected Spotlight: " + _selectedSpotlightId);
}

void WorldEditor::_selectCaptor(const string & captorId)
{
	_selectedCaptorId = captorId;

	_gui->getOverlay()->getTextField(SELECTED_TITLE_ID)->setTextContent("Selected Captor: " + _selectedCaptorId);
}

void WorldEditor::_selectSound3d(const string & sound3dId)
{
	_selectedSound3dId = sound3dId;

	_gui->getOverlay()->getTextField(SELECTED_TITLE_ID)->setTextContent("Selected Sound3D: " + _selectedSound3dId);
}

void WorldEditor::_deselectModel(const string & modelId)
{

}

void WorldEditor::_deselectQuad3d(const string & quad3dId)
{

}

void WorldEditor::_deselectText3d(const string & text3dId)
{

}

void WorldEditor::_deselectAabb(const string & aabbId)
{

}

void WorldEditor::_deselectPointlight(const string & pointlightId)
{

}

void WorldEditor::_deselectSpotlight(const string & spotlightId)
{

}

void WorldEditor::_deselectCaptor(const string & captorId)
{

}

void WorldEditor::_deselectSound3d(const string & sound3dId)
{

}