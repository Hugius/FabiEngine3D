#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_viewport.hpp"
#include "engine_gui_global_screen.hpp"

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

	const vec3 _topVpButtonColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 _leftVpButtonColor = vec3(0.0f, 0.0f, 0.5f);
	const vec3 _rightVpButtonColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 _bottomVpButtonColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 _topVpButtonHoverColor = vec3(0.0f, 0.5f, 0.0f);
	const vec3 _leftVpButtonHoverColor = vec3(0.5f, 0.5f, 1.0f);
	const vec3 _rightVpButtonHoverColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 _bottomVpButtonHoverColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 _topVpTextColor = vec3(1.0f);
	const vec3 _leftVpTextColor = vec3(1.0f);
	const vec3 _rightVpTextColor = vec3(1.0f);
	const vec3 _bottomVpTextColor = vec3(1.0f);
	const vec3 _topVpTextHoverColor = vec3(0.0f);
	const vec3 _leftVpTextHoverColor = vec3(0.0f);
	const vec3 _rightVpTextHoverColor = vec3(0.0f);
	const vec3 _bottomVpTextHoverColor = vec3(0.0f);
};