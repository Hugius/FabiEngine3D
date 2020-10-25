#pragma once

#include "script.hpp"
#include "scene_editor.hpp"
#include "script_type.hpp"
#include "script_value.hpp"

class ScriptInterpreter
{
public:
	ScriptInterpreter(FabiEngine3D& fe3d, Script& script, SceneEditor& sceneEditor);

	void load();
	void executeInitialization();
	void executeUpdate();
	void executeDestruction();
	void unload();

private:
	FabiEngine3D& _fe3d;
	Script& _script;
	SceneEditor& _sceneEditor;

	void _executeScript(const string& scriptID, ScriptType scriptType);
	void _throwSyntaxError(const string& scriptName, unsigned int lineIndex, const string& message);
	vector<ScriptValue> _extractArguments(string argumentString);

	vector<string> _initScriptIDs;
	vector<string> _updateScriptIDs;
	vector<string> _destroyScriptIDs;

	string _initEntryID = "";
	string _updateEntryID = "";
	string _destroyEntryID = "";
};