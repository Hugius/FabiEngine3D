#pragma once

#include "base_viewport_controller.hpp"
#include "top_viewport_controller.hpp"
#include "script_editor.hpp"

class BottomViewportController final : public BaseViewportController
{
public:
	BottomViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui, TopViewportController& topViewportController, ScriptEditor& scriptEditor);

	// VOID
	void initialize() override;
	void update() override;

private:
	// VOID
	void _updateConsoleScrolling();
	void _addConsoleMessage(const string& newMessage);
	void _deleteConsoleMessage(const string& ID);

	// STRING
	vector<pair<string, string>> _consoleMessageQueue;

	// FVEC3
	static inline const fvec3 FRAME_COLOR = fvec3(0.0025f);

	// FVEC2
	static inline const fvec2 CHAR_SIZE = fvec2(0.01f, 0.03f);

	// FLOAT
	static inline const float Y_OFFSET = 0.2f;
	float _scrollingAcceleration = 0.0f;

	// UNSIGNED INT
	static inline const unsigned int MAX_CONSOLE_MESSAGES = 1000;
	static inline const unsigned int TIME_PART_LENGTH = 10;
	static inline const unsigned int SEPARATOR_PART_LENGTH = 3;

	// Miscellaneous
	TopViewportController& _topViewportController;
	ScriptEditor& _scriptEditor;
	shared_ptr<EngineGuiScreen> _statsScreen = nullptr;
};