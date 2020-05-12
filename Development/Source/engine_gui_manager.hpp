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

	const vec3 leftVpButtonColor = vec3(0.0f, 0.0f, 0.5f);
	const vec3 leftVpButtonHoverColor = vec3(0.5f, 0.5f, 1.0f);
	const vec3 leftVpTextColor = vec3(1.0f);
	const vec3 leftVpTextHoverColor = vec3(0.0f);

	const vec3 rightVpButtonColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 rightVpButtonHoverColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 rightVpTextColor = vec3(1.0f);
	const vec3 rightVpTextHoverColor = vec3(0.0f);

	const vec3 topVpButtonColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 topVpButtonHoverColor = vec3(0.0f, 0.5f, 0.0f);
	const vec3 topVpTextColor = vec3(1.0f);
	const vec3 topVpTextHoverColor = vec3(0.0f);

	const vec3 bottomVpButtonColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 bottomVpButtonHoverColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 bottomVpTextColor = vec3(1.0f);
	const vec3 bottomVpTextHoverColor = vec3(0.0f);

private:
	FabiEngine3D& _fe3d;

	shared_ptr<EngineGuiGlobalScreen> _globalScreen;
	std::vector<shared_ptr<EngineGuiViewport>> _viewports;

	bool _isFocused = false;
};