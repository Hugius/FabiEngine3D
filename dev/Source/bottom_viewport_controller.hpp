#pragma once

#include "base_viewport_controller.hpp"
#include "top_viewport_controller.hpp"
#include "script_editor.hpp"

class BottomViewportController final : public BaseViewportController
{
public:
	BottomViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui, TopViewportController& topViewportController, ScriptEditor& scriptEditor);

	// Voids
	void initialize() override;
	void update() override;

private:
	// Voids
	void _updateConsoleScrolling();
	void _addConsoleMessage(const string& newMessage);
	void _deleteConsoleMessage(const string& ID);

	// Strings
	vector<pair<string, string>> _consoleMessageQueue;

	// Vectors
	static inline const Vec3 FRAME_COLOR = Vec3(0.0025f);
	static inline const Vec2 CHAR_SIZE = Vec2(0.01f, 0.03f);

	// Decimals
	static inline const float Y_OFFSET = 0.2f;
	float _scrollingAcceleration = 0.0f;

	// Integers
	static inline const unsigned int MAX_CONSOLE_MESSAGES = 1000;
	static inline const unsigned int TIME_PART_LENGTH = 10;
	static inline const unsigned int SEPARATOR_PART_LENGTH = 3;

	// Miscellaneous
	TopViewportController& _topViewportController;
	ScriptEditor& _scriptEditor;
	shared_ptr<EngineGuiScreen> _statsScreen;
};