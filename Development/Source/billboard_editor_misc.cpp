#include "billboard_editor.hpp"

void BillboardEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

bool BillboardEditor::isLoaded()
{
	return _isLoaded;
}

vector<string>& BillboardEditor::getBillboardNames()
{
	return _billboardNames;
}