#pragma once

#include "base_viewport_controller.hpp"
#include "top_viewport_controller.hpp"
#include "script_editor.hpp"

#define BVPC BottomViewportController

class BottomViewportController final : public BaseViewportController
{
public:
	BottomViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui, TopViewportController& topViewportController, ScriptEditor& scriptEditor);

	void initialize() override;
	void update() override;

	static inline const Vec3 FRAME_COLOR = Vec3(0.0025f);

private:
	TopViewportController& _topViewportController;
	ScriptEditor& _scriptEditor;

	shared_ptr<EngineGuiScreen> _statsScreen;

	vector<pair<string, string>> _consoleMessageQueue;

	void _updateConsoleScrolling();
	void _addConsoleMessage(const string& newMessage);
	void _deleteConsoleMessage(const string& ID);

	float _scrollingAcceleration = 0.0f;

	static inline const Vec2 CHAR_SIZE = Vec2(0.01f, 0.03f);
	static inline const float Y_OFFSET = 0.2f;
	static inline const unsigned int MAX_CONSOLE_MESSAGES = 1000;
	static inline const unsigned int TIME_PART_LENGTH = 10;
	static inline const unsigned int SEPARATOR_PART_LENGTH = 3;
};