#pragma once

#include "script_interpreter.hpp"

class ScriptExecutor final
{
public:
	ScriptExecutor(FabiEngine3D& fe3d, Script& script, SceneEditor& sceneEditor, ModelEditor& modelEditor, 
		AnimationEditor& animationEditor, BillboardEditor& billboardEditor, AudioEditor& audioEditor, EnvironmentEditor& environmentEditor);

	void load();
	void update(bool debug);
	void pause();
	void resume();
	void unload();
	void setCurrentProjectID(const string& projectName);

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
	bool _wasMillisecondTimerStarted = false;
	bool _skipUpdate = false;
};