#include "script_editor.hpp"

void ScriptEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

void ScriptEditor::_loadScript()
{
	// Clear last script
	_unloadScript();

	if (false) // if script save file exists <---
	{
		// Create new script to be filled from savefile
		_script = make_shared<Script>();

		// fill script <---
	}
	else
	{
		// Create new empty script
		_script = make_shared<Script>();
	}

	// Inject into script executor
	_scriptExecutor = make_shared<ScriptExecutor>(_script);
}

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
		_loadScript();
	}
	
	return _scriptExecutor;
}

bool ScriptEditor::isLoaded()
{
	return _isLoaded;
}