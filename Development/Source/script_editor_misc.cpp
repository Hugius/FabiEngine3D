#include "script_editor.hpp"

void ScriptEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

bool ScriptEditor::isLoaded()
{
	return _isLoaded;
}

const Script& ScriptEditor::getScript()
{
	return _script;
}