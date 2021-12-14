#pragma once

#include "script_interpreter.hpp"

class ScriptExecutor final
{
public:
	ScriptExecutor(FabiEngine3D& fe3d, Script& script, SkyEditor& skyEditor, TerrainEditor& terrainEditor,
				   WaterEditor& waterEditor, ModelEditor& modelEditor, BillboardEditor& billboardEditor,
				   Animation3dEditor& animation3dEditor, AudioEditor& audioEditor, WorldEditor& worldEditor);

	// VOID
	void setCurrentProjectID(const string& projectID);
	void load();
	void update(bool debug);
	void pause();
	void resume();
	void unload();

	// BOOL
	const bool isScriptEmpty() const;
	const bool isStarted() const;
	const bool isRunning() const;

private:
	// VOID
	void _validateExecution();

	// STRING
	vector<string> _pausedSoundIDs;
	
	// BOOL
	bool _isStarted = false;
	bool _isRunning = false;
	bool _wasCursorVisible = false;
	bool _wasVsyncEnabled = false;
	bool _wasTimerStarted = false;
	bool _mustSkipUpdate = false;

	// MISCELLANEOUS
	FabiEngine3D& _fe3d;
	Script& _script;
	ScriptInterpreter _scriptInterpreter;
};