#pragma once

#include "script_interpreter.hpp"

class ScriptExecutor
{
public:
	ScriptExecutor(FabiEngine3D& fe3d, Script& script, SceneEditor& sceneEditor, AnimationEditor& animationEditor);

	void load();
	void update();
	void pause();
	void unpause();
	void unload();

	bool isScriptEmpty();
	bool isInitialized();
	bool isRunning();

private:
	void _validateExecution();

	FabiEngine3D& _fe3d;
	Script& _script;
	ScriptInterpreter _scriptInterpreter;

	bool _isInitialized = false;
	bool _isRunning = false;
	bool _wasCursorVisible = false;
};