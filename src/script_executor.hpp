#pragma once

#include "script_interpreter.hpp"

class ScriptExecutor final
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
	void inject(shared_ptr<ScriptInterpreter> scriptInterpreter);

	void setCurrentProjectID(const string& projectID);
	void load();
	void update(bool isDebugging);
	void pause();
	void resume();
	void unload();

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

	shared_ptr<EngineInterface> _fe3d;
	shared_ptr<ScriptInterpreter> _scriptInterpreter;
};