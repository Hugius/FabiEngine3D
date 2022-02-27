#pragma once

#include "script_interpreter.hpp"

class ScriptExecutor final
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
	void inject(shared_ptr<ScriptInterpreter> scriptInterpreter);

	void setCurrentProjectId(const string& projectId);
	void start();
	void update(bool isDebugging);
	void pause();
	void resume();
	void stop();

	const bool isStarted() const;
	const bool isRunning() const;

private:
	void _validateExecution();

	vector<string> _pausedSound3dIds;
	vector<pair<string, unsigned int>> _pausedSound2dIds;
	vector<string> _pausedClockIds;

	bool _isStarted = false;
	bool _isRunning = false;
	bool _wasVsyncEnabled = false;
	bool _wasCursorVisible = false;
	bool _wasFirstPersonEnabled = false;
	bool _wasThirdPersonEnabled = false;
	bool _mustSkipUpdate = false;

	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<ScriptInterpreter> _scriptInterpreter = nullptr;
};