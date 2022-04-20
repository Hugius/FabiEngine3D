#pragma once

#include "base_viewport_controller.hpp"
#include "top_viewport_controller.hpp"
#include "script_editor.hpp"
#include "logger_message.hpp"

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
	void _fillConsole();
	void _clearConsole();

	static inline const fvec3 FRAME_COLOR = fvec3(0.0025f, 0.0025f, 0.0025f);
	static inline const fvec3 TIMESTAMP_COLOR = fvec3(0.8f, 0.4f, 0.1f);
	static inline const fvec3 INFO_COLOR = fvec3(1.0f, 1.0f, 1.0f);
	static inline const fvec3 WARN_COLOR = fvec3(1.0f, 0.0f, 0.0f);

	static inline const fvec2 CHAR_SIZE = fvec2(0.02f, 0.15f);

	static inline constexpr unsigned int MAX_MESSAGE_COUNT = 100;
	static inline constexpr unsigned int TIMESTAMP_SIZE = 10;

	vector<shared_ptr<LoggerMessage>> _messageQueue = {};
	vector<shared_ptr<LoggerMessage>> _messageHistory = {};

	shared_ptr<ScriptExecutor> _scriptExecutor = nullptr;
	shared_ptr<ScriptEditor> _scriptEditor = nullptr;

	float _scrollingOffset = 0.0f;
};