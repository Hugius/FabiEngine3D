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
	void _addConsoleMessage(const string& newMessage);
	void _deleteConsoleMessage(const string& id);

	vector<pair<string, string>> _consoleMessageQueue;

	static inline const fvec3 FRAME_COLOR = fvec3(0.0025f);

	static inline const fvec2 CHAR_SIZE = fvec2(0.01f, 0.03f);

	static inline constexpr float Y_OFFSET = 0.2f;
	float _scrollingAcceleration = 0.0f;

	static inline constexpr unsigned int MAX_CONSOLE_MESSAGES = 1000;
	static inline constexpr unsigned int TIME_PART_LENGTH = 10;
	static inline constexpr unsigned int SEPARATOR_PART_LENGTH = 3;

	shared_ptr<ScriptExecutor> _scriptExecutor = nullptr;
	shared_ptr<ScriptEditor> _scriptEditor = nullptr;
};