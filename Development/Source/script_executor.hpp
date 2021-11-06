#pragma once

#include "script_interpreter.hpp"

class ScriptExecutor final
{
public:
	ScriptExecutor(FabiEngine3D& fe3d, Script& script, SkyEditor& skyEditor, TerrainEditor& terrainEditor,
				   WaterEditor& waterEditor, ModelEditor& modelEditor, AnimationEditor& animationEditor,
				   BillboardEditor& billboardEditor, AudioEditor& audioEditor, SceneEditor& sceneEditor);

	// Voids
	void setCurrentProjectID(const string& projectID);
	void load();
	void update(bool debug);
	void pause();
	void resume();
	void unload();

	// Booleans
	bool isScriptEmpty();
	bool isStarted();
	bool isRunning();

private:
	// Voids
	void _validateExecution();

	// Strings
	vector<string> _pausedSoundIDs;
	
	// Booleans
	bool _isStarted = false;
	bool _isRunning = false;
	bool _wasCursorVisible = false;
	bool _wasVsyncEnabled = false;
	bool _wasTimerStarted = false;
	bool _wasMusicPaused = false;
	bool _mustSkipUpdate = false;

	// Miscellaneous
	FabiEngine3D& _fe3d;
	Script& _script;
	ScriptInterpreter _scriptInterpreter;
};