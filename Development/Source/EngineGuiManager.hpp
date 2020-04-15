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

	const vec3 _topViewportButtonColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 _leftViewportButtonColor = vec3(0.0f, 0.0f, 0.5f);
	const vec3 _rightViewportButtonColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 _bottomViewportButtonColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 _topViewportButtonHoverColor = vec3(0.0f, 0.5f, 0.0f);
	const vec3 _leftViewportButtonHoverColor = vec3(0.5f, 0.5f, 1.0f);
	const vec3 _rightViewportButtonHoverColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 _bottomViewportButtonHoverColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 _topViewportTextColor = vec3(1.0f);
	const vec3 _leftViewportTextColor = vec3(1.0f);
	const vec3 _rightViewportTextColor = vec3(1.0f);
	const vec3 _bottomViewportTextColor = vec3(1.0f);
	const vec3 _topViewportTextHoverColor = vec3(0.0f);
	const vec3 _leftViewportTextHoverColor = vec3(0.0f);
	const vec3 _rightViewportTextHoverColor = vec3(0.0f);
	const vec3 _bottomViewportTextHoverColor = vec3(0.0f);
};