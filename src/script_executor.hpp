#pragma once

#include "script_interpreter.hpp"

class ScriptExecutor final
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
	void inject(shared_ptr<ScriptInterpreter> scriptInterpreter);
	void setCurrentProjectId(const string & projectId);
	void start();
	void update(bool isDebugging);
	void stop();

	const bool isStarted() const;

private:
	void _stop();

	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<ScriptInterpreter> _scriptInterpreter = nullptr;

	bool _isStarted = false;
	bool _mustSkipUpdate = false;
	bool _wasCursorVisible = false;
	bool _wasCursorInsideDisplay = false;
};