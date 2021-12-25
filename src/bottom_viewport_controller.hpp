#pragma once

#include "base_viewport_controller.hpp"
#include "top_viewport_controller.hpp"
#include "script_editor.hpp"

class BottomViewportController final : public BaseViewportController
{
public:
	BottomViewportController(FabiEngine3D& fe3d, GuiManager& gui, TopViewportController& topViewportController, ScriptEditor& scriptEditor);

	void initialize() override;
	void update() override;

private:
	void _updateStatistics();
	void _updateConsole();
	void _addConsoleMessage(const string& newMessage);
	void _deleteConsoleMessage(const string& ID);

	vector<pair<string, string>> _consoleMessageQueue;

	static inline const fvec3 FRAME_COLOR = fvec3(0.0025f);

	static inline const fvec2 CHAR_SIZE = fvec2(0.01f, 0.03f);

	static inline const float Y_OFFSET = 0.2f;
	float _scrollingAcceleration = 0.0f;

	static inline const unsigned int MAX_CONSOLE_MESSAGES = 1000;
	static inline const unsigned int TIME_PART_LENGTH = 10;
	static inline const unsigned int SEPARATOR_PART_LENGTH = 3;

	TopViewportController& _topViewportController;
	ScriptEditor& _scriptEditor;
};