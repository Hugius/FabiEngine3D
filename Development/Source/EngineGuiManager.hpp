#pragma once

#include "FabiEngine3D.hpp"
#include "EngineGuiViewport.hpp"
#include "EngineGuiGlobalScreen.hpp"

class EngineGuiManager final
{
public:
	EngineGuiManager(FabiEngine3D& fe3d);

	void update(float delta);
	void setFocus(bool focused);

	shared_ptr<EngineGuiGlobalScreen> getGlobalScreen();
	shared_ptr<EngineGuiViewport> getViewport(const string& ID);

private:
	FabiEngine3D& _fe3d;

	shared_ptr<EngineGuiGlobalScreen> _globalScreen;
	std::vector<shared_ptr<EngineGuiViewport>> _viewports;

	bool _isFocused = false;

	const vec3 topColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 leftColor = vec3(0.0f, 0.0f, 0.5f);
	const vec3 rightColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 bottomColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 topHoverColor = vec3(0.0f, 0.5f, 0.0f);
	const vec3 leftHoverColor = vec3(0.5f, 0.5f, 1.0f);
	const vec3 rightHoverColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 bottomHoverColor = vec3(0.0f, 0.25f, 0.0f);
};