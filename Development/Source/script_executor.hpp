#pragma once

#include "script_interpreter.hpp"

class ScriptExecutor final
{
public:
	ScriptExecutor(FabiEngine3D& fe3d, Script& script, SceneEditor& sceneEditor, ModelEditor& modelEditor, 
		AnimationEditor& animationEditor, BillboardEditor& billboardEditor, AudioEditor& audioEditor, EnvironmentEditor& environmentEditor);

	void setCurrentProjectID(const string& projectID);
	void load();
	void update(bool debug);
	void pause();
	void resume();
	void unload();

	bool isScriptEmpty();
	bool isStarted();
	bool isRunning();

private:
	void _validateExecution();

	FabiEngine3D& _fe3d;
	Script& _script;
	ScriptInterpreter _scriptInterpreter;

	vector<string> _pausedSoundIDs;

	bool _isStarted = false;
	bool _isRunning = false;
	bool _wasCursorVisible = false;
	bool _wasVsyncEnabled = false;
	bool _wasTimerStarted = false;
	bool _wasMusicPaused = false;
	bool _mustSkipUpdate = false;
};