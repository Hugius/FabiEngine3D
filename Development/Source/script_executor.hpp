#pragma once

#include "script_interpreter.hpp"

class ScriptExecutor
{
public:
	ScriptExecutor(FabiEngine3D& fe3d, Script& script, SceneEditor& sceneEditor);

	void load();
	void update();
	void pause();
	void unpause();
	void unload();

	bool isScriptEmpty();
	bool isInitialized();
	bool isRunning();

private:
	FabiEngine3D& _fe3d;
	Script& _script;
	ScriptInterpreter _scriptInterpreter;

	bool _isInitialized = false;
	bool _isRunning = false;
};