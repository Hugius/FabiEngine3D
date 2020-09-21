#include "script_editor.hpp"

void ScriptEditor::_unloadScript()
{
	_script = nullptr;
	_scriptExecutor = nullptr;
}

shared_ptr<ScriptExecutor> ScriptEditor::getScriptExecutor()
{
	// Check if script is loaded yet
	if (_scriptExecutor == nullptr)
	{
		_loadScriptFromFile();
	}
	
	return _scriptExecutor;
}

void ScriptEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

bool ScriptEditor::isLoaded()
{
	return _isLoaded;
}

void ScriptEditor::_calibrateScriptLines()
{
	auto scriptLineIDs = _script->getAllScriptLineIDs();
	int counter = 1;

	// Change all IDs (line numbers) accordingly
	for (auto& ID : scriptLineIDs)
	{
		_script->getScriptLine(ID).ID = to_string(counter);
		counter++;
	}
}