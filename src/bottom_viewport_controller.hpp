#pragma once

#include "base_viewport_controller.hpp"
#include "top_viewport_controller.hpp"
#include "script_editor.hpp"

class BottomViewportController final : public BaseViewportController
{
public:
	using BaseViewportController::inject;

	void inject(shared_ptr<ScriptExecutor> scriptExecutor);
	void inject(shared_ptr<ScriptEditor> scriptEditor);
	void initialize();
	void update();

private:
	void _updateStatistics();
	void _updateConsole();
	void _createConsoleMessage(const string & newMessage);
	void _deleteConsoleMessage(const string & id);

	static inline const fvec3 FRAME_COLOR = fvec3(0.0025f);
	static inline const fvec2 CHAR_SIZE = fvec2(0.02f, 0.15f);

	static inline constexpr unsigned int MAX_CONSOLE_MESSAGES = 100;

	vector<pair<string, string>> _consoleMessageQueue;

	shared_ptr<ScriptExecutor> _scriptExecutor = nullptr;
	shared_ptr<ScriptEditor> _scriptEditor = nullptr;
};