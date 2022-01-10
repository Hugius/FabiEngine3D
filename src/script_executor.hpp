#pragma once

#include "script_interpreter.hpp"

class ScriptExecutor final
{
public:
	ScriptExecutor(EngineInterface& fe3d,
				   Script& script,
				   SkyEditor& skyEditor,
				   TerrainEditor& terrainEditor,
				   WaterEditor& waterEditor,
				   ModelEditor& modelEditor,
				   BillboardEditor& billboardEditor,
				   QuadEditor& quadEditor,
				   Animation2dEditor& animation2dEditor,
				   Animation3dEditor& animation3dEditor,
				   SoundEditor& soundEditor,
				   WorldEditor& worldEditor);

	void setCurrentProjectID(const string& projectID);
	void load();
	void update(bool debug);
	void pause();
	void resume();
	void unload();

	const bool isScriptEmpty() const;
	const bool isStarted() const;
	const bool isRunning() const;

private:
	void _validateExecution();

	vector<string> _pausedSoundIDs;

	bool _isStarted = false;
	bool _isRunning = false;
	bool _wasCursorVisible = false;
	bool _wasVsyncEnabled = false;
	bool _wasTimerStarted = false;
	bool _mustSkipUpdate = false;

	EngineInterface& _fe3d;
	Script& _script;
	ScriptInterpreter _scriptInterpreter;
};