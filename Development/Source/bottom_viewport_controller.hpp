#pragma once

#include "viewport_controller.hpp"
#include "top_viewport_controller.hpp"
#include "script_editor.hpp"

#define BVPC BottomViewportController

class BottomViewportController final : public ViewportController
{
public:
	BottomViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui, TopViewportController& topViewportController, ScriptEditor& scriptEditor);

	void initialize() override;
	void update() override;

	static inline const Vec3 FRAME_COLOR = Vec3(0.05f);
	static inline const Vec3 BUTTON_COLOR = Vec3(0.0f, 0.25f, 0.0f);
	static inline const Vec3 BUTTON_HOVER_COLOR = Vec3(0.0f, 0.25f, 0.0f);
	static inline const Vec3 TEXT_COLOR = Vec3(1.0f);
	static inline const Vec3 TEXT_HOVER_COLOR = Vec3(0.0f);

private:
	TopViewportController& _topViewportController;
	ScriptEditor& _scriptEditor;

	shared_ptr<EngineGuiScreen> _statsScreen;

	vector<pair<string, string>> _consoleMessageStack;

	const Vec2 _charSize = Vec2(0.01f, 0.03f);

	void _updateConsoleScrolling();
	void _addConsoleMessage(const string& newMessage);
	void _deleteConsoleMessage(const string& ID);

	float _scrollingAcceleration = 0.0f;

	const unsigned int _maxConsoleMessages = 1000;
};