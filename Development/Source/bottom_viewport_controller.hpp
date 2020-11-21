#pragma once

#include "viewport_controller.hpp"

#define BVPC BottomViewportController

class BottomViewportController final : public ViewportController
{
public:
	using ViewportController::ViewportController;

	void initialize() override;
	void update() override;

	static inline const Vec3 frameColor = Vec3(0.05f);
	static inline const Vec3 buttonColor = Vec3(0.0f, 0.25f, 0.0f);
	static inline const Vec3 buttonHoverColor = Vec3(0.0f, 0.25f, 0.0f);
	static inline const Vec3 textColor = Vec3(1.0f);
	static inline const Vec3 textHoverColor = Vec3(0.0f);

private:
	shared_ptr<EngineGuiScreen> _statsScreen;

	vector<pair<string, string>> _consoleMessageStack;

	const Vec2 _charSize = Vec2(0.01f, 0.03f);

	void _updateConsoleScrolling();
	void _addConsoleMessage(const string& newMessage);

	float _scrollingAcceleration = 0.0f;
};